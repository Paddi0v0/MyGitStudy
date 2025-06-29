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
  PGA_Init();              /*OPA初始化 */
  __enable_irq();          /* 开启中断 */
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
 函数名称：    void PGA_Init(void)
 功能描述：    PGA初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/15      V1.0           Howlet Li          创建
 *******************************************************************************/
void PGA_Init(void)
{
	
	OPA_InitTypeDef OPA_InitStruct;
	OPA_StructInit(&OPA_InitStruct);
	
	
	OPA_InitStruct.OPA_CLEna = ENABLE;
	OPA_InitStruct.OPA_Gain = PGA_GAIN_20;
	OPA_Init(OPA0 ,&OPA_InitStruct);
	
	OPA_InitStruct.OPA_CLEna = ENABLE;
	OPA_InitStruct.OPA_Gain = PGA_GAIN_9P5;
	OPA_Init(OPA1 ,&OPA_InitStruct);
	
	OPA_InitStruct.OPA_CLEna = ENABLE;
	OPA_InitStruct.OPA_Gain = PGA_GAIN_6;
	OPA_Init(OPA2 ,&OPA_InitStruct);
	
	OPA_InitStruct.OPA_CLEna = ENABLE;
	OPA_InitStruct.OPA_Gain = PGA_GAIN_4P25;
	OPA_Init(OPA3 ,&OPA_InitStruct);
	
	
  OPA_OUT(OPA3 , ENABLE);              //OPA3信号输出至P2.7脚
}


