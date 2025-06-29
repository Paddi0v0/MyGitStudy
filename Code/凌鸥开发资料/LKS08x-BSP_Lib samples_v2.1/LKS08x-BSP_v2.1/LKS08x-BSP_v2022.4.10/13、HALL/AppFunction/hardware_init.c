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
#include "basic.h"
#include "hardware_config.h"
#include "gpio_led.h"
#include "gpio_key.h"
#include "utimer.h"
#include "WDT.h"
#include "lks32mc08x_MCPWM.h"

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
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Hardware_init(void)
{
  __disable_irq();         /* 关闭中断 中断总开关 */
  SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
  FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/

  GPIO_init(); /* GPIO初始化 */
  HALL_Perip_Init();
  NVIC_EnableIRQ(HALL_IRQn); //使能MCPWM中断
  NVIC_SetPriority(HALL_IRQn, 3);

  __enable_irq(); /* 开启中断 */
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


  //GPIO_P2.4/P2.5/P2.6设置为HALL_IN0/HALL_IN1/HALL_IN2模拟通道
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_Init(GPIO2, &GPIO_InitStruct);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF2_HALL);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF2_HALL);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_6, AF2_HALL);

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

  SYS_WR_PROTECT = 0x7a83;      /* 解除系统寄存器写保护 */
  SYS_AFE_REG5 |= BIT15 | BIT0; /* BIT15:PLLPDN  BIT0:ADC_Clock*/
  SYS_CLK_CFG |= 0x000001ff;    /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 ; 开启所有时钟*/
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
 函数名称：    void HALL_Init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2018/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void HALL_Perip_Init(void)
{

  HALL_InitTypeDef HALL_InitStruct;

  HALL_StructInit(&HALL_InitStruct);
  HALL_InitStruct.FilterLen = 512;               /* Hall信号数字滤波长度 512个时钟周期 */
  HALL_InitStruct.ClockDivision = HALL_CLK_DIV1; /* 设置Hall模块时钟分频系数 */
  HALL_InitStruct.Filter75_Ena = DISABLE;        /* Hall信号滤波方式，7判5模式或者全1有效模式 */
  HALL_InitStruct.HALL_Ena = ENABLE;             /* 模块使能 */
  HALL_InitStruct.Capture_IRQ_Ena = ENABLE;      /* 捕捉中断使能 */
  HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;     /* 超时中断使能 */
  HALL_InitStruct.softIE = ENABLE;               /* 软件中断使能 */
  HALL_InitStruct.CountTH = 9600000;             /* Hall模块计数模值，计数超过模值会产生超时中断 */

  HALL_Init(&HALL_InitStruct);
}


