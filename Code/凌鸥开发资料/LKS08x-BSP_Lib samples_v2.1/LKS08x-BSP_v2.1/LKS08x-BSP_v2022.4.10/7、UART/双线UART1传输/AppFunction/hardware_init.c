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
  GPIO_init();             /* GPIO初始化 */
  UART_init();
  NVIC_EnableIRQ(UART1_IRQn);      //打开串口1中断
  NVIC_SetPriority(UART1_IRQn, 1); //中断优先级配置

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


  //配置UART1_RXD  P2.4
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO2, &GPIO_InitStruct);
  //配置UART1_TXD  P2.5

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO2, &GPIO_InitStruct);

  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF4_UART);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF4_UART);
}


/*******************************************************************************
 函数名称：    void UART_init(void)
 功能描述：    UART0寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART_init(void)
{
  UART_InitTypeDef UART_InitStruct;

  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.BaudRate = 2400;                                     /* 设置波特率38400 */
  UART_InitStruct.WordLength = UART_WORDLENGTH_8b;                     /* 发送数据长度8位 */
  UART_InitStruct.StopBits = UART_STOPBITS_1b;                         /* 停止位1位 */
  UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;                      /* 先发送LSB */
  UART_InitStruct.ParityMode = UART_Parity_NO;                         /* 无奇偶校验 */
  UART_InitStruct.IRQEna = UART_IRQEna_SendOver | UART_IRQEna_RcvOver; /* 串口中断使能 */
  UART_Init(UART1, &UART_InitStruct);
  UART1_IF = 0xff;
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
 函数名称：    void UART0_SENDDATA(void)
 功能描述：    UART0发送程序
 输入参数：    n：需要发送的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART0_SENDDATA(UINT8 n)
{
  UART0_BUFF = n;
}

/*******************************************************************************
 函数名称：    void UART1_SENDDATA(void)
 功能描述：    UART1发送程序
 输入参数：    n：需要发送的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART1_SENDDATA(UINT8 n)
{
  UART1_BUFF = n;
}



