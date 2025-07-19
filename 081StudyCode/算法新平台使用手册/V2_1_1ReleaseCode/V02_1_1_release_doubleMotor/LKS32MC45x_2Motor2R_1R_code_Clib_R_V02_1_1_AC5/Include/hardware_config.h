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

#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "project_mcu.h"
#include "project_config.h"
#include "MC_Parameter_M0.h"
#include "MC_Parameter_M1.h"
#include "PubData_DriverInstance.h"


#define  LKS32MC451              1
#define  LKS32MC453              2
#define  LKS32MC455              3

#define  CHIP_PART_NUMBER              LKS32MC453			/* 芯片型号 */
#define  P_HIGH__N_HIGH                1
#define  P_HIGH__N_LOW                 2

#if (0)														/* 预留给带预驱的芯片 */
#define  MCPWM_SWAP_FUNCTION           1
#define  PRE_DRIVER_POLARITY           P_HIGH__N_HIGH		
#else
#define  PRE_DRIVER_POLARITY           P_HIGH__N_LOW		/* 上管高电平 下管低电平有效 */
#endif
/* ----------------------应用PWM 模块定义----------------------------------- */


/* ----------------------ADC通道号定义----------------------- */
#define ADC_CHANNEL_OPA0					ADC_CHANNEL_0
#define ADC_CHANNEL_OPA1					ADC_CHANNEL_1
#define ADC_CHANNEL_OPA2					ADC_CHANNEL_2
#define ADC_CHANNEL_OPA3					ADC_CHANNEL_3
#define ADC_CHANNEL_OPA4					ADC_CHANNEL_4
#define ADC_CHANNEL_OPA5					ADC_CHANNEL_5

/* ADC相电流采样时序，硬件相关 -------------------------------- */
/* Porting Application Notice 注意采样序列 -------------------- */
#define M0_ADC0_CURRETN_A_CH				(ADC_CHANNEL_OPA5)      /* 电机1 A相电流经ADC0 Channel 5采样 */
#define M0_ADC0_CURRETN_C_CH				(ADC_CHANNEL_2)         /* 电机1 B相电流经ADC0 Channel 2采样 未使用*/
#define M0_ADC0_CURRETN_B_CH				(ADC_CHANNEL_OPA4)      /* 电机1 C相电流经ADC0 Channel 4采样 */

#define M0_ADC1_CURRETN_A_CH				(ADC_CHANNEL_OPA5)      /* 电机1 A相电流经ADC1 Channel 5采样 */
#define M0_ADC1_CURRETN_C_CH				(ADC_CHANNEL_2)			/* 电机1 B相电流经ADC1 Channel 2采样   未使用*/
#define M0_ADC1_CURRETN_B_CH				(ADC_CHANNEL_OPA4)      /* 电机1 C相电流经ADC1 Channel 4采样 */

#define M0_ADC0_BUS_CURR_CH					(ADC_CHANNEL_OPA3)		/* 电机0 母线电流经 OPA3采样 */
#define M0_SPEED_ADC_CH						(ADC_CHANNEL_10)		/* 电机0速度指令 采用ADC0 Channel 10  */
#define M0_BUS_VOL_ADC_CH					(ADC_CHANNEL_14)		/* 电机0母线电压 采用ADC0 Channel 14  */

/*反电动势*/
#define M0_BEMF_CH_A                         ADC_CHANNEL_13			/* ADC1_13 */
#define M0_BEMF_CH_B                         ADC_CHANNEL_12			/* ADC1_12 */
#define M0_BEMF_CH_C                         ADC_CHANNEL_14			/* 453 DEMO板不可用 */


/*Motor1*/
#define M1_ADC2_CURRETN_A_CH				(ADC_CHANNEL_OPA1)      /* 电机1 B相电流经ADC1 Channel 1采样 */
#define M1_ADC2_CURRETN_C_CH				(ADC_CHANNEL_4)         /* 电机1 B相电流经ADC1 Channel 4采样 未使用*/
#define M1_ADC2_CURRETN_B_CH				(ADC_CHANNEL_OPA0)      /* 电机1 C相电流经ADC1 Channel 0采样 */

/*转速指令*/
#define M1_SPEED_ADC_CH						(ADC_CHANNEL_8)			/* 电机1速度指令 采用ADC1 Channel 8  */
#define M1_BUS_VOL_ADC_CH					(ADC_CHANNEL_7)			/* 电机1母线电压 采用ADC2 Channel 7  */

/*母线电流*/
#define M1_ADC2_BUS_CURR_CH					(ADC_CHANNEL_OPA2)		/* 电机1 母线电流经 OPA2采样 */

/*反电动势*/
#define M1_BEMF_CH_A                         ADC_CHANNEL_13			/* 453 DEMO板不可用 */
#define M2_BEMF_CH_B                         ADC_CHANNEL_12			/* 453 DEMO板不可用 */
#define M3_BEMF_CH_C                         ADC_CHANNEL_13			/* ADC2_13 */


/* 电流内环相电流采样，ADC通道采样结果宏定义 */
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
//M0 第一个采样数据，第二个采样数据
#define GET_ADC_DATA0_M0					(ADC0_DAT0)   
#define GET_ADC_DATA1_M0					(ADC0_DAT1)
#else
#define GET_ADC_DATA0_M0					(ADC0_DAT0)
#define GET_ADC_DATA1_M0					(ADC1_DAT0)
#endif


/* 电流内环相电流采样，ADC通道采样结果宏定义 */
#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
//M1 第一个采样数据，第二个采样数据
#define GET_ADC_DATA0_M1					(ADC2_DAT0)   
#define GET_ADC_DATA1_M1					(ADC2_DAT1)

#else
#define GET_ADC_DATA0_M1					(ADC2_DAT0)
#define GET_ADC_DATA1_M1					(ADC2_DAT1)
#endif

#define GET_M0_BUS_VOL_ADC_RESULT			(ADC0_DAT2)		/* 母线电压ADC通道采样结果宏定义 */

#define GET_M0_TEMP_DATA_A					(ADC0_DAT6)
#define GET_M0_BEMF_DATA_A					(ADC0_DAT7)
#define GET_M0_BEMF_DATA_B					(ADC0_DAT8)
#define GET_M0_BEMF_DATA_C					(ADC0_DAT9)


#define GET_M1_BUS_VOL_ADC_RESULT			(ADC2_DAT2)		/* 母线电压ADC通道采样结果宏定义 */

#define GET_M1_TEMP_DATA_A					(ADC2_DAT6)
#define GET_M1_BEMF_DATA_A					(ADC2_DAT7)
#define GET_M1_BEMF_DATA_B					(ADC2_DAT8)
#define GET_M1_BEMF_DATA_C					(ADC2_DAT9)


#define ADC0_STATE_RESET()					{ADC0_CFG |= BIT11;}   /* ADC0 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC1_STATE_RESET()					{ADC1_CFG |= BIT11;}   /* ADC0 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC2_STATE_RESET()					{ADC2_CFG |= BIT11;}   /* ADC0 状态机复位,用以极限情况下确定ADC工作状态 */

/* ------------------------------FPU操作相关定义 ------------------------------------------- */
#define FPU_ENABLE()						{SCB->CPACR |= (0x0F<<20);}//{SCB->CPACR |= SCB_CPACR_FPU;} /* FPU Enable */
#define ADC_SOFTWARE_TRIG_ONLY()			{ADC0_CFG = 0;}       /* ADC设置为仅软件触发 */


/* ------------------------------PGA操作相关定义 ------------------------------------------- */
#define PGA_GAIN_2P0						0                   /* 反馈电阻20:10 */
#define PGA_GAIN_4P0						1                   /* 反馈电阻40:10 */
#define PGA_GAIN_8P0						2                   /* 反馈电阻80:10 */
#define PGA_GAIN_16P0						3                   /* 反馈电阻160:10 */
#define PGA_GAIN_32P0						4                   /* 反馈电阻320:10 */
#define PGA_GAIN_64P0						5                   /* 反馈电阻320:5 */
#define PGA_GAIN_32P_1						6                   /* 反馈电阻320:10  同4*/
#define PGA_GAIN_32P_2						7                   /* 反馈电阻320:10  同4*/


#define OPA0_GIAN							PGA_GAIN_8P0//(PGA_GAIN_64P0)         //配置SYS_AFE_REG0
#define OPA1_GIAN							(PGA_GAIN_8P0 << 4)    //配置SYS_AFE_REG0
#define OPA2_GIAN							(PGA_GAIN_16P0 << 8)    //配置SYS_AFE_REG0 单电阻
#define OPA3_GIAN							(PGA_GAIN_16P0 << 12)   //配置SYS_AFE_REG0 单电阻

#define OPA4_GIAN							(PGA_GAIN_16P0)         //配置SYS_AFE_REG1
#define OPA5_GIAN							(PGA_GAIN_16P0 << 4)    //配置SYS_AFE_REG1


/* ------------------------------编译器选项--------------------------------------- */
#define RUN_IN_RAM_FUNC  __attribute__ ((used, section ("ram3functions")))

#endif  /* __HARDWARE_CONFIG_H_ */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

