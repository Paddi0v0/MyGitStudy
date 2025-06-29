/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.h
 * 文件标识：
 * 内容摘要： 硬件初始化头文件定义
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/
#ifndef __HARDWARE_INIT_H
#define __HARDWARE_INIT_H

#include "basic.h"
#include "lks32mc07x_lib.h"

#define P_HIGH__N_HIGH                   0                 /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#define P_HIGH__N_LOW                    1                 /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */

#define  CHIP_PART_NUMBER              LKS32MC071         /* 芯片型号选择，选择不正确将影响芯片模块的初始化 */

#if ((CHIP_PART_NUMBER == LKS32MC074D)||(CHIP_PART_NUMBER == LKS32MC076D)||(CHIP_PART_NUMBER == LKS32MC077D)) 
#define  MCPWM_SWAP_FUNCTION           1
     /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#else
#define  PRE_DRIVER_POLARITY           P_HIGH__N_LOW      /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */
#endif

#define  CNT0_PRE_DRIVER_POLARITY           P_HIGH__N_HIGH
#define  CNT1_PRE_DRIVER_POLARITY           P_HIGH__N_LOW

/* ----------------------PWM 频率及死区定义----------------------------------- */
#define MCU_MCLK                       (96000000LL)       /**<  PWM模块运行主频 */
#define PWM_MCLK                       ((u32)MCU_MCLK)    /**<  PWM模块运行主频 */
#define PWM_PRSC                       ((u8)0)            /**< *< *<  PWM模块运行预分频器 */
#define PWM_FREQ0                      ((u16)16000)       /**< *<  MCPWM_CNT0PWM斩波频率 */
#define PWM_FREQ1                      ((u16)20000)       /**<  MCPWM_CNT1PWM斩波频率 */


/**<  电机控制PWM 周期计数器值 */
#define MCPWM_PERIOD0                    ((u16) (PWM_MCLK / (u32)(2 * PWM_FREQ0 *(PWM_PRSC+1))))
#define MCPWM_PERIOD1                    ((u16) (PWM_MCLK / (u32)(2 * PWM_FREQ1 *(PWM_PRSC+1))))
/**<  PFC控制PWM 周期计数器值 */
#define PFC_PERIOD                     ((u16) (PWM_MCLK / (u32)(2 * PFC_FREQ *(PWM_PRSC+1))))

#define DEADTIME_NS                    ((u16)1200)       /**<  死区时间 */
#define DEADTIME                       (u16)(((unsigned long long)PWM_MCLK * (unsigned long long)DEADTIME_NS)/1000000000uL)



void MCPWM_init(void);
void UTimer_init(void);
void GPIO_init(void);
void ADC0_init(void);
void Clock_Init(void);
void Hardware_init(void);

void Motor0_ADC_SampleSetting(void);
void Motor1_ADC_SampleSetting(void);
void AlternateOut_CH012_CH3(void);
void MCPWM1_CH3_RegUpdate(void);

void ADC_NormalModeCFG(void);
void SoftDelay(u32 cnt);
#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

