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
#include "i2c_driver.h"
void SoftDelay(u32 cnt);
void gpio_init(void);
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
	  __disable_irq();                  /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; 
    FLASH_CFG |= 0x00080000;          /* enable prefetch */
    IWDG_DISABLE();                   /* 关闭看门狗*/
    i2c_DriverInit(I2C0, DMA_CHN0, 10000, 2); // I2C驱动库初始化
    gpio_init();
    SoftDelay(100);                   /* 等待硬件初始化完毕*/
    NVIC_SetPriority(I2C0_IRQn, 1);
    NVIC_EnableIRQ(I2C0_IRQn);               
	  SYS_WR_PROTECT = 0x0;             /* 关闭系统寄存器写操作*/
	  __enable_irq();                   /* 开启总中断 */
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
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 = BIT15;      /* BIT15:PLLPDN 开PLL */
    SoftDelay(100);            /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG = 0x000001ff;  /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
	  SYS_WR_PROTECT = 0;        /* 关闭系统寄存器写操作*/
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
    Clock_Init();  /* 时钟初始化 */
}


void gpio_init(void)
{
    GPIO_InitTypeDef gpioconfig;
    gpioconfig.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15; // 要配置的引脚
    gpioconfig.GPIO_Mode = GPIO_Mode_IN;             // GPIO模式
    gpioconfig.GPIO_PuPd = DISABLE;                  // 上拉使能
    gpioconfig.GPIO_PODEna = DISABLE;                // 开漏使能
    GPIO_Init(GPIO0, &gpioconfig);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, 6); // 复用为I2C
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, 6); // 复用为I2C
    
    
    gpioconfig.GPIO_Pin = GPIO_Pin_5; // 要配置的引脚
    gpioconfig.GPIO_Mode = GPIO_Mode_OUT;             // GPIO模式
    gpioconfig.GPIO_PuPd = DISABLE;                  // 上拉使能
    gpioconfig.GPIO_PODEna = DISABLE;                // 开漏使能
    GPIO_Init(GPIO0, &gpioconfig);
    GPIO_ResetBits(GPIO0,GPIO_Pin_5);
    
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

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}





