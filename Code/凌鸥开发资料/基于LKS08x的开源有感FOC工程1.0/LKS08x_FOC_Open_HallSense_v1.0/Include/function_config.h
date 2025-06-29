#ifndef __FUNCTION_CFG_PARAM_H
#define __FUNCTION_CFG_PARAM_H

/* ****************************** 基础参数 ****************************************** */

#define ROTOR_SPEED_FACTOR_1US         			(s32)(1048576)						 	/* 1个时钟节拍速度值标幺，360度对应65536 */
/* 最低速标幺值，对应一个Hall周期只计数1个时钟周期的情况 */
/* 角速度计数系数,为计算角速度的被除数: 一个PWM周期内角度累加值 = ROTOR_SPEED_FACTOR/Hall变化周期, 用以Hall PLL锁相和当前转子速度值计算 */
#define ROTOR_SPEED_FACTOR             			(s32)(ROTOR_SPEED_FACTOR_1US*(1000000/PWM_FREQ))

#define ROTOR_SPEED_FACTOR_PER_UNIT    			(s16)(MCU_MCLK/PWM_FREQ)              	/* PWM周期对应主时钟周期，角速度系数关系 */
#define ROTOR_FACTOR_REDUCE_PER_UNIT   			(s16)(ROTOR_SPEED_FACTOR_PER_UNIT)    	/* 低速时, 角速度系数处理关系 */

#define MAX_SPEED_DPP                  			(ROTOR_SPEED_FACTOR/4000)			 	/* 系统限制的最大Dpp值 */

/* ****************************** 数据存储 ****************************************** */

#define HALL_LEARN_ADDR                			0x7800 							/* Hall学习存储存地址 */

#define HALL0                 					2
#define HALL1                 					6
#define HALL2                 					4
#define HALL3                 					5
#define HALL4                 					1
#define HALL5                 					3								 /* Hall相位 */

#define MOTORTYPE0             					1								 /* 电机绕组类型 */

#define HALLTYPE              					120								 /* 电机角度 */
#define VERSION0              					0
#define VERSION1              					3
#define VERSION2              					0
#define VERSION3              					1								 /* 程序版本 */
#define BEMFCOE               					0
#define HALL_OFFSET           					1600
#if (SPEED_CLOSED_LOOP == 1) 								 					 /* 速度环选择 */
#define NUL1                  					1								 /* 速度闭环 */								
#else
#define NUL1                  					0								 /* 速度开环 */								
#endif
#define NUL11              						0								 /* 自主定义使用 */

/* ****************************** 转把处理 ****************************************** */

#define HAND_BASE                 				(20.0/(20+10.0)) 									/* 转把分压比 */

#define HBSPD_BASE		    					(u16)(32767 / 3.6 * 1.1 * HAND_BASE)				/* 转把启动电压阀值 */	
#define HBSPD_MAX_EFFECTIVE		    			(u16)(32767 / 3.6 * 3.25 * HAND_BASE)				/* 转把最大有效电压 */	

#define HBSPD_EFFECTIVE_AMPLITUDE		    	(HBSPD_MAX_EFFECTIVE - HBSPD_BASE)					/* 转把有效ADC幅值 */	

		/* 档位最大速度占空比 32760为电机的额定转速 大于32760后进入弱磁提速 最大到34660 */
#define FIRST_GEAR                 				(32000 * 128 / HBSPD_EFFECTIVE_AMPLITUDE + 1) 		/* 一档速度 最大34660 */
#define SECOND_GEAR                 			(32000 * 128 / HBSPD_EFFECTIVE_AMPLITUDE + 1) 		/* 二档速度 最大34660 */
#define THIRD_GEAR                 				(32000 * 128 / HBSPD_EFFECTIVE_AMPLITUDE + 1) 		/* 三档速度 最大34660 */
#define BACK_UP_GEAR                 			(3200 * 128 / HBSPD_EFFECTIVE_AMPLITUDE + 1) 		/* 倒车档速度 最大34660 */

#define HBSPD_LOW		    					(u16)(32767 / 3.6 * 0.3 * HAND_BASE)				/* 转把低压判断阀值 */	
#define HBSPD_OVERHIGH 	    					(u16)(32767 / 3.6 * 3.95 * HAND_BASE)				/* 转把过压判断阀值 */	

/* ****************************** 加减速处理 ****************************************** */

#define POWER_UP_STEP_STRONG           			12    							/* 硬启动加速步距 */

/* ****************************** 堵转 端口输入 ****************************************** */

#define TIME_1S6_BASE  							((u16)160)						/* 堵转时间计数 */

#define KEYIN_FILTER_TIME             			60  							/* 输入端口消抖滤波时间 */  
#define KEYIN_FILTER_TIME1            			-60  							/* 输入端口消抖滤波时间 */

/* ****************************** 偏置采样 ****************************************** */

#define PHASE_OFFSET_MAX        				2000
#define PHASE_OFFSET_MIN        				-2000
#define ADC_GET_OFFSET_CNT      				512
#define TIME_5S_BASE_20MS       				250u

#endif /* __CONTROL_PARAM_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

























