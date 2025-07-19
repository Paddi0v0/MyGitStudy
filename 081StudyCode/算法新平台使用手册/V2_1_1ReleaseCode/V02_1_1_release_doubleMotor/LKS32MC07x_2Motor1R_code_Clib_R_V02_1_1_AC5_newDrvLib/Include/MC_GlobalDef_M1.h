/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： parameter.h
 * 文件标识：
 * 内容摘要： parameter config
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Andrew kong, Howlet Li
 * 完成日期： 2020年8月18日
 *
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __MC_GLOBAL_DEF_M1_H
#define __MC_GLOBAL_DEF_M1_H

#include "basic.h"
#include "MC_Type.h"

//以下编译宏被修改时，需要重新编译代码?
//全局配置信息被修改时，同样需要重新编译。

/* -----------------------------Hardware Parameter---------------------------- */

/* ----------------------PWM 频率及死区定义----------------------------------- */
#define MCU_MCLK_M1                       (MCU_MCLK_USED)       /* PWM模块运行主频 */
#define PWM_MCLK_M1                       ((u32)MCU_MCLK_M1)    /* PWM模块运行主频 */
#define PWM_PRSC_M1                       (0)				/* PWM模块运行预分频器 */
#define PWM_FREQ_M1                       ((u16)16000)			/* PWM斩波频率 */

#define CURRENT_SAMPLE_TYPE_M1				(DRV1_CUR_SAMP_TYPE)	/* 电流采样方式选择 */
#define ROTOR_SENSOR_TYPE_M1				ROTOR_SENSORLESS		/* 电机位置传感器类型选择 */

#define SVPWM_TYPE_M1						(0)						/* 0 --- 7seg  1--- 5seg */
																	/* 目前仅支持7seg， 部分SVPWM函数过调制时 7seg/5seg 自动切换*/
#define PWM_USED_ID_M1						(DRV1_PWM_ID)
#define OPA_SELECT_M1						(0)						/*	运算放大倍数 选择 */

#define CUR_LOOP_FREQUENCY_M1				((u16)16000)		/*单位: HZ 当前未用，预留*/
#define OBSVR_LOOP_FREQUENCY_M1				((u16)16000)		/*单位: HZ 当前未用，预留*/
#define SPD_LOOP_FREQUENCY_M1				((u16)1000)			/*单位: HZ*/

#define OVER_MODU_FACTOR_M1					((s16)21845)		/*单位: Q15, 过调制系数*/


/* 电机控制PWM 周期计数器值 */
#if (PWM_PRSC_M1 == 0)
#define PWM_PERIOD_M1                        ((u16) (PWM_MCLK_M1 * 1000000 / (u32)(2 * PWM_FREQ_M1 *(PWM_PRSC_M1+1))))
#elif (PWM_PRSC_M1 == 1)
#define PWM_PERIOD_M1                        ((u16) (PWM_MCLK_M1 * 1000000 / (u32)(2 * PWM_FREQ_M1 *(2))))
#elif (PWM_PRSC_M1 == 2)
#define PWM_PERIOD_M1                        ((u16) (PWM_MCLK_M1 * 1000000 / (u32)(2 * PWM_FREQ_M1 *(4))))
#elif (PWM_PRSC_M1 == 3)
#define PWM_PERIOD_M1                        ((u16) (PWM_MCLK_M1 * 1000000 / (u32)(2 * PWM_FREQ_M1 *(8))))
#else
#error "Don't support PWM_PRSC_M"
#endif

/*Motor0 Deadtime config*/
#define DEADTIME_NS_M1						((u16)1200)                              /* 死区时间500--1000 */
#define DEADTIME_M1							(u16)(((unsigned long long)PWM_MCLK_M1 * (unsigned long long)DEADTIME_NS_M1)/1000000000uL)

#define ADC_COV_TIME_M1						(200)   /* 预留的ADC转换时间，单位：500--200ns*/
#define SAMP_STABLE_TIME_SHUNT_M1			(1800)  /* 1000--1800单电阻采样，信号稳定时间设置| 单位 nS */
#define SAMP_PROPAGATE_TIME_M1				(200)   /* 传输延时时间，单位：500--200ns*/

#define VF_DEADZONE_COMP_FACTOR_M1			(950)		// Q15格式: 0~32767 	0----- 根据死区时间自动计算


/* ----------------------DEBUG INFORMATION ---------------- */
#if (DRV1_BEMF_CHECK_EABLE == FUNCTION_ON)
#define DIR_EMF_CHECK_ENABLE_M1			(TRUE)   			/* 反电势顺逆风检测 TRUE = 使能, FALSE = 关闭 */
#else
#define DIR_EMF_CHECK_ENABLE_M1			(FALSE)
#endif
/* ----------------------IPD 转子初始位置检测 脉冲注入时间设置---------------- */
#define SEEK_POSITION_STATUS_M1			(TRUE)				/* 初始位置检测状态 TRUE 为使能, FALSE 为不使能 */

/* ----------------------顺逆风检测是否是能---------------- */
#define DIR_CHECK_STATUS_M1				(TRUE)				/* 顺逆风检测状态 TRUE 为使能, FALSE 为不使能 */

/* ----------------------allign 对相是否是能---------------- */
#define ALLIGN_STATUS_M1				(TRUE)				/* ALLIGN对相状态 TRUE 为使能, FALSE 为不使能 */

/* ----------------------VF 启动是否是能---------------- */
#define VF_START_STATUS_M1					(FALSE)			/* VF 启动状态 TRUE 为使能, FALSE 为不使能 当前未用，预留 */

/* ----------------------AC检测及保护是否是能---------------- */
#define AC_SENOR_PROTECT_STATUS_M1			(FALSE)			/* AC检测及保护状态 TRUE 为使能, FALSE 为不使能 当前未用，预留 */

/* ----------------------NTC检测及保护是否是能---------------- */
#define NTC_SENOR_PROTECT_STATUS_M1		(FALSE)					/* NTC检测及保护状态 TRUE 为使能, FALSE 为不使能 */

/* ----------------------预充电是否是能---------------- */
#define CHARGE_STATUS_M1					(TRUE)				/* CHARGE对相状态 TRUE 为使能, FALSE 为不使能 */



/* ------------------------------ADC校准相关参数设置---------------------------- */
#define CALIB_SAMPLES_M1                  (512)              /* ADC偏置校准次数，不可修改 */
#define ADC_OFFSET_ERROR_M1               (3500)             /* ADC偏置误差阈值，不用修改 */

/* ----------------------------预驱自举电容预充电参数--------------------------- */
#define CHARGE_TIME_M1                    (30)              /* 每相预充电时间，根据实际硬件参数修改 */


/*-----------------------------------环路选择----------------------------------*/

#define CLOSE_LOOP_M1                     (SPEED_LOOP)      /* 环路选择 */


/*----------------------------------速度环参数-------------------------------*/
#define POWER_LIMIT_STATUS_M1             (FALSE)            /* 限功率状态，TRUE = 使能，FALSE = 不使能 */


/*------------------------------------功率环参数-------------------------------*/
#define SPPED_LIMIT_STATUS_M1            (FALSE)            /*  限转速状态，TRUE = 使能，FALSE = 不使能 */

/*------------------------------------弱磁控制-------------------------------*/
#define WEAKEN_FLUX_STATUS_M1             (FALSE)            /*  弱磁控制状态，TRUE = 使能，FALSE = 不使能 */

/*------------------------------------PWM使能控制-------------------------------*/
#define PWM_ENABLE_STOP_M1				(FALSE)				/*  PWM状态使能，TRUE = 使能，FALSE = 不使能 */
#define STOP_MODE_M1					(0)					/*  停止方式，0 = 关闭MOE，1-- 零电流  2--- 短接 */


#define FAULT_AUTO_CLR_M1				(TRUE)				/*  故障自动清除使能 */
#define FAULT_CLR_PRIOD_M1				(2000)				/*  故障清除周期 ms*/

#endif  /* __MC_GLOBAL_DEF_M1_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* -----------------------------------END OF FILE------------------------------- */

