/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_config.h
 * 文件标识：
 * 内容摘要： 硬件相关文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月20日
 *
 * 修改记录1：
 * 修改日期： 2020年8月20日
 * 版 本 号： V 2.0
 * 修 改 人： Howlet
 * 修改内容： 创建
 *
 *******************************************************************************/

/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "lks32mc08x.h"
#include "lks32mc08x_MCPWM.h"
#include "lks32mc08x_sys.h"
#include "lks32mc08x_adc.h"
#include "lks32mc08x_MCPWM.h"
#include "lks32mc08x_flash.h"
#include "lks32mc08x_Gpio.h"
#include "lks32mc08x_cmp.h"
#include "lks32mc08x_uart.h"
#include "lks32mc08x_hall.h"
#include "lks32mc08x_tim.h"
#include "hardware_init.h"
#include "lks32mc08x_NVR.h"
#include "delay.h"

#define  WAKE_EN  REG32(0x40012114)
#define  WAKE_PO  REG32(0x40012110)
#define GPIO0_0_POL BIT0 //P0.0作为唤醒IO
#define GPIO0_1_POL BIT1 //P0.1作为唤醒IO
#define GPIO1_0_POL BIT2 //P1.0作为唤醒IO
#define GPIO1_1_POL BIT3 //P1.1作为唤醒IO

#define High_Level  1    //IO唤醒高电平
#define Low_Level   0    //IO唤醒低电平
/* ----------------------PWM 频率及死区定义----------------------------------- */
#define MCU_MCLK                       (96000000LL)       /* PWM模块运行主频 */
void SYS_UtimerFallSleep(void);
void InversP_Test(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SYS_SetWakeIO(uint32_t nInterval, u8 POL);
void SYS_FallSleepMode(void);
#include "delay.h"

#endif  /* __HARDWARE_CONFIG_H_ */

 
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
 
