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

#define P_HIGH__N_HIGH                   0                 /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#define P_HIGH__N_LOW                    1                 /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */

#define  CHIP_PART_NUMBER              LKS32MC081         /* 芯片型号选择，选择不正确将影响芯片模块的初始化 */

#if ((CHIP_PART_NUMBER == LKS32MC084D)||(CHIP_PART_NUMBER == LKS32MC086D)||(CHIP_PART_NUMBER == LKS32MC087D)) 
#define  MCPWM_SWAP_FUNCTION           1
#define  PRE_DRIVER_POLARITY           P_HIGH__N_HIGH     /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#else
#define  PRE_DRIVER_POLARITY           P_HIGH__N_LOW      /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */
#endif

/* ----------------------PWM 频率及死区定义----------------------------------- */
#define MCU_MCLK                       (96000000LL)       /* PWM模块运行主频 */

#define ALL_ON          1 //全亮
#define ALL_OFF         2 //全灭

//LED1 2 3输出低
#define LED1_OFF  GPIO_ResetBits(GPIO0 , GPIO_Pin_6)
#define LED2_OFF  GPIO_ResetBits(GPIO0 , GPIO_Pin_7)
#define LED3_OFF  GPIO_SetBits(GPIO0 , GPIO_Pin_3)

//LED1 2 3输出高
#define LED1_ON  GPIO_SetBits(GPIO0 , GPIO_Pin_6)
#define LED2_ON  GPIO_SetBits(GPIO0 , GPIO_Pin_7)
#define LED3_ON  GPIO_ResetBits(GPIO0 , GPIO_Pin_3)

void GPIO_LED(u8 mode);
void Invers_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);//GPIO电平翻转函数

void Delay(u32 cnt);
	
#endif  /* __HARDWARE_CONFIG_H_ */

 
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
 
