/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2015年11月5日
 *
 * 修改记录1：
 * 修改日期： 2021年8月25日
 * 版 本 号：
 * 修 改 人： HMG
 * 修改内容：
 *
 *******************************************************************************/
#include "hardware_init.h"

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
    关键初始化步骤（针对凌鸥LKS32MC08x芯片的固定写法）：
      1. 关闭总中断：防止初始化过程被中断打断
      2. 解除寄存器写保护：使用厂商固定密码0x7a83解锁系统寄存器
      3. 使能FLASH预取：加速代码执行，高主频下必须开启
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();
    SYS_WR_PROTECT = 0x7a83;
    FLASH_CFG |= 0x00080000;

    // 只保留P0.3引脚初始化
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

    // 配置P0.3为输出低电平
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_ResetBits(GPIO0, GPIO_Pin_3); // 输出低电平

    /* 注释掉其他不必要的外设初始化
    SoftDelay(100);
    SYS_WR_PROTECT = 0x0;
    #if POWER_MODE
        SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);
    #else
        SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);
    #endif
    */
    __enable_irq();
}

/*******************************************************************************
 函数名称：    void Clock_Init(void)
 功能描述：    时钟配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/10/23      V2.0         HuangMG        增加MCU电源检测功能
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83; /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;   /* BIT15:PLLPDN */
#if POWER_MODE
    SYS_VolSelModule(MCU_POWER_5v0); /* MCU供电电压：1：5V，0;3.3V*/
#else
    SYS_VolSelModule(MCU_POWER_3v3); /* MCU供电电压：1：5V，0;3.3V*/
#endif
    SoftDelay(100);           /* 等待PLL稳定*/
    SYS_WR_PROTECT = 0x7a83;  /* 解除系统寄存器写保护 */
    SYS_CLK_CFG = 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
    SYS_WR_PROTECT = 0x0;     /*关闭系统寄存器写操作*/
}

/*******************************************************************************
 函数名称：    void SystemInit(void)
 功能描述：    硬件系统初始化，调用时钟初始化函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/14      V1.0           Howlet Li          创建
 *******************************************************************************/
void SystemInit(void)
{
    Clock_Init(); /* 时钟初始化 */
}

/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体

    //配置按键 start：P2.11
    GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    //配置按键 stop：P2.12
    GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    //配置LED1：P0.6
    GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    //配置LED2：P0.7
    GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
}

/*******************************************************************************
 函数名称：    int GPIO_KEY_Scan(u8 mode)
 功能描述：    按键处理函数
 输入参数：    mode:0,不支持连续按;1,支持连续按;
 输出参数：    无
 返 回 值：    0，没有任何按键按下；1，开始按键按下；2，停止按键按下
 其它说明：
    实现逻辑：
      1. 定义静态变量key_up记录按键松开状态（1为松开，0为按下）
      2. 如果mode=1（支持连按），则每次调用都将key_up置1（即支持连续检测）
      3. 如果当前按键处于松开状态（key_up=1）且检测到有按键按下（key_start或key_stop为0）
          - 延时消抖（10个空循环）
          - 设置key_up=0（表示按键已按下）
          - 判断具体是哪个按键按下，返回对应的按键值（start_PRES或stop_PRES）
      4. 如果检测到两个按键都释放（key_start和key_stop都为1），则设置key_up=1（标记按键已松开）
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/6/8      V1.0           HuangMG            创建
 *******************************************************************************/
int GPIO_KEY_Scan(u8 mode)
{
    static u8 key_up = 1; // 按键松开标志（静态变量，保持状态）
    if (mode) key_up = 1; // 如果支持连按，则每次调用都重置key_up为1（即允许连续检测）

    if (key_up && (key_start == 0 || key_stop == 0)) // 如果按键处于松开状态且有按键被按下
    {
        SoftDelay(10);          // 延时10个空循环（消抖）
        key_up = 0;             // 标记按键已按下（防止重复触发）
        if (key_start == 0)     // 再次检测开始按键是否按下（消抖后确认）
            return start_PRES;  // 返回开始按键按下的状态值
        else if (key_stop == 0) // 检测停止按键是否按下
            return stop_PRES;   // 返回停止按键按下的状态值
    }
    else if (key_start == 1 && key_stop == 1) // 如果两个按键都处于释放状态
        key_up = 1;                           // 标记按键已松开（允许下次检测）

    return 0; // 无按键按下
}

/*******************************************************************************
 函数名称：    void SoftDelay(u32 cnt)
 功能描述：    软件延时函数
 输入参数：    cnt - 延时循环次数（值越大延时越长）
 输出参数：    无
 返 回 值：    无
 其它说明：
    实现原理：
      1. 使用volatile修饰计数器变量（防止编译器优化）
      2. 通过空循环消耗CPU时间实现延时
      3. 每次循环执行__NOP()指令（无操作指令）
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt; // volatile防止编译器优化掉这个变量

    for (t_cnt = 0; t_cnt < cnt; t_cnt++) // 循环cnt次
    {
        __NOP(); // 执行无操作指令（消耗一个时钟周期）
    }
}

/*******************************************************************************
 函数名称：    uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 功能描述：    GPIO电平翻转函数
 输入参数：    
     - GPIOx: GPIO端口（如GPIO0）
     - GPIO_Pin: 引脚号（如GPIO_Pin_6）
 输出参数：    无
 返 回 值：    翻转后的引脚电平状态（0-低电平，1-高电平）
 其它说明：
    实现逻辑：
      1. 读取当前引脚电平状态
      2. 如果当前为高电平，则设置为低电平
      3. 如果当前为低电平，则设置为高电平
      4. 返回翻转后的电平状态
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg;
    reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); // 读取当前引脚电平状态
    if (reg)                                       // 如果当前是高电平
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin); // 设置为低电平
        return 0;                        // 返回低电平状态
    }
    else // 如果当前是低电平
    {
        GPIO_SetBits(GPIOx, GPIO_Pin); // 设置为高电平
        return 1;                      // 返回高电平状态
    }
}
