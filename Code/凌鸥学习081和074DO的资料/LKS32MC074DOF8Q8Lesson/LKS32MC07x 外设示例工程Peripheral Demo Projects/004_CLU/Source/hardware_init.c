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
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/
#include "LKS32MC07x_lib.h" // Device header

void CLU_init(void);
void GPIO_init(void);
void SoftDelay(u32 cnt);
/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq(); /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;
    FLASH_CFG |= 0x00080000; /* enable prefetch */
    IWDG_DISABLE();          /* 关闭看门狗*/

    CLU_init();
    GPIO_init();
    SoftDelay(100);       /* 等待硬件初始化完毕*/
    SYS_WR_PROTECT = 0x0; /* 关闭系统寄存器写操作*/
    __enable_irq();       /* 开启总中断 */
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
 2015/11/5      V1.0           Howlet Li          创建

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/4/17      V1.1           Howlet Li          增加延时函数，等待PLL稳定
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;  /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 = BIT15;     /* BIT15:PLLPDN 开PLL */
    SoftDelay(100);           /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG = 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
    SYS_WR_PROTECT = 0;       /* 关闭系统寄存器写操作*/
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

void CLU_init(void)
{
    CLU_InitTypeDef cluconfig;

    CLU_StructInit(&cluconfig);

    cluconfig.EN = ENABLE;                        ///< 模块使能 0关闭模块 1打开模块
    cluconfig.FIE = DISABLE;                      ///< 下降沿中断使能
    cluconfig.RIE = DISABLE;                      ///< 上升沿中断使能
    cluconfig.MXA = CLU_MXA_CLU0_P1_0;            ///< A输入复用选择 格式 CLU_MXA_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    cluconfig.MXB = CLU_MXB_CLU0_P0_15;           ///< B输入复用选择 格式 CLU_MXB_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    cluconfig.FN = CLU_FN_NOTA_B | CLU_FN_A_NOTB; ///< 真值表 格式 CLU_FN_x x取值范围为[A NOTA A_NOTB ...]对应为最简与或式下的最小相 例如 y=a+bc+!c 表示为 CLU_FN_A|CLU_FN_B_C|CLU_FN_NOTC
    cluconfig.OUTSEL = 1;                         ///< 输出选择 0: D 触发器输出 1: LUT 输出
    cluconfig.OEN = 1;                            ///< 输出使能 0: 关闭 1: 使能
    cluconfig.CLKINV = 0;                         ///< D 触发器时钟电平 0: 同相 1: 反向
    cluconfig.CLKSEL = 0;                         ///< D 触发器时钟选择 0x0: 进位输入 0x1: MXA 输入 0x2: ALTCLK0 0x3: ALTCLK1
    CLU_Init(CLU, CLU_MODEL_CLU0, &cluconfig);
}
void GPIO_init(void)
{
    // CLO输出
    GPIO_InitTypeDef gpioconfig;
    gpioconfig.GPIO_Pin = GPIO_Pin_14;    // 要配置的引脚
    gpioconfig.GPIO_Mode = GPIO_Mode_OUT; // GPIO模式
    gpioconfig.GPIO_PuPd = DISABLE;       // 上拉使能
    gpioconfig.GPIO_PODEna = DISABLE;     // 开漏使能
    GPIO_Init(GPIO0, &gpioconfig);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, 12); // 复用为CL

    // CLO的两个输入信号，这里用gpio输出一两个随机的信号进行测试
    gpioconfig.GPIO_Pin = GPIO_Pin_0;    // 要配置的引脚
    gpioconfig.GPIO_Mode = GPIO_Mode_IN; // GPIO模式
    gpioconfig.GPIO_PuPd = DISABLE;      // 上拉使能
    gpioconfig.GPIO_PODEna = DISABLE;    // 开漏使能
    GPIO_Init(GPIO1, &gpioconfig);

    gpioconfig.GPIO_Pin = GPIO_Pin_15;   // 要配置的引脚
    gpioconfig.GPIO_Mode = GPIO_Mode_IN; // GPIO模式
    gpioconfig.GPIO_PuPd = DISABLE;      // 上拉使能
    gpioconfig.GPIO_PODEna = DISABLE;    // 开漏使能
    GPIO_Init(GPIO0, &gpioconfig);

    GPIO1->POE |= BIT0;
    GPIO0->POE |= BIT15;
}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}
