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
#include "hardware_config.h"
#include "gpio_led.h"
#include "gpio_key.h"
#include "utimer.h"

void UART_init(void);

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/25      V1.0          HMG               创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();                  /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;          /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000;          /* enable prefetch ，FLASH预取加速使能*/
    GPIO_init();                      /* GPIO初始化 */
    UTimer_init();                    /* UTimer初始化 */
    NVIC_SetPriority(TIMER0_IRQn, 0); /*TIMER0中断优先级配置*/
    NVIC_EnableIRQ(TIMER0_IRQn);      /*使能UTimer定时器中断*/
    __enable_irq();                   /* 开启中断 */
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
 2021/8/25      V1.0           HMG              创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体

    //配置按键 start：P2.11  stop:P2.11
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    //配置LED1：P0.6  LED2：P0.7  LED3: P0.3
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    /* 配置UTimer0  TIM0_CH1: P0.14   TIM0_CH0: P0.15 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    GPIO0_AF_MODE = GPIO0_F2_6_10_14_AF7 | GPIO0_F3_7_11_15_AF7; // P0.14,P0.15复用为timer0_CH1和timer0_CH0的输入捕获模式
                                                                 // GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF7_TIMER01);//复用P0.14
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
 *******************************************************************************/
void Clock_Init(void)
{

    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;     /* BIT15:PLLPDN */
    SYS_CLK_CFG |= 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
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
 函数名称：    void UTimer_init(void)
 功能描述：    UTimer硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTimer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerCmd(TIMER0, ENABLE); /* Timer0 模块使能 */

    TIM_TimerStrutInit(&TIM_InitStruct);                                                   //Timer结构体初始化
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP;                                  /* 设置Timer0 CH0 为捕获模式 */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_Fall;                                 /*下降沿捕获*/
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CAP;                                  /* 设置Timer0 CH1 为捕获模式 */
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_Rise;                                 /*上升沿捕获*/
    TIM_InitStruct.Timer_TH = 48000;                                                       /* 定时器计数门限初始值1000*/
    TIM_InitStruct.Timer_Filter0 = 0;                                                      /*CH0滤波，滤波宽度为Timer_Filter0*8个时钟周期*/
    TIM_InitStruct.Timer_Filter1 = 0;                                                      /*CH0滤波，滤波宽度为Timer_Filter0*8个时钟周期*/
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1;                                          /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | Timer_IRQEna_Zero; /* 开启Timer模块比较中断*/
    TIM_TimerInit(TIMER0, &TIM_InitStruct);
}


