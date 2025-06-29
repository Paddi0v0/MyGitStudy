#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "lks32mc08x_lib.h"

/* ==============================PWM 频率及死区定义=========================== */

#define MCU_MCLK							((u32)96000000uL) 										/* PWM模块运行主频 */
#define PWM_MCLK							((u32)MCU_MCLK) 										/* PWM模块运行主频 */
#define PWM_PRSC 							((u8)0) 												/* PWM模块运行预分频器 */
#define PWM_FREQ 							((u16)20000) 											/* PWM斩波频率 */

#define PWM_PERIOD         					((u16) (PWM_MCLK / (u32)(2 * PWM_FREQ *(PWM_PRSC+1)))) 	/* PWM 周期计数器值 */

#define DEADTIME_NS        					((u16)800)												/* 死区时间 */
#define DEADTIME           					(u16)(((unsigned long long)PWM_MCLK * (unsigned long long)DEADTIME_NS)/1000000000uL)
 
/* ============================== 电机参数定义 =========================== */

#define RS                              (double)(0.444273)   // 单位Ω  相电阻
#define LS                              (double)(0.000280 )   // 单位H   相电感
#define PHASE_RSHUNT                    (double)(0.05 )   // 单位Ω  相电流采样电阻
#define ADC_SUPPLY_VOLTAGE              (double)(3.6 )   // 单位V   ADC量程
#define AMPLIFICATION_GAIN              (200.0/(10.4+2))          /* 运放放大倍数 */   //17.543859     17.5439
#define U_RATED_VOLTAGE                 (24)               /* 单位:V, 电机额定工作电压，设置为正常工作电压 */



/* ---------------------------------PID参数设置------------------------------- */

#define PLL_KP_GAIN 1000
#define PLL_KI_GAIN 100

#define PLL_KPDIV 15
#define PLL_KIDIV 15


#define MAX_VQ_LIM             		(u16)30000    /* Q轴最大输出限制，Q15格式，取值范围0~32767 */
#define MAX_VD_LIM             		(u16)30000    /* D轴最大输出限制，Q15格式，取值范围0~32767 */  


#define PID_FLUX_KP_DEFAULT  		(s16)50
#define FLUX_KPDIV 					((u16)12)
#define PID_FLUX_KI_DEFAULT  		(s16)20
#define FLUX_KIDIV 					((u16)12)

#define PID_TORQUE_KP_DEFAULT  		(s16)50
#define TF_KPDIV 					((u16)12)
#define PID_TORQUE_KI_DEFAULT  		(s16)20
#define TF_KIDIV 					((u16)12)


#define PID_SPEED_KP_DEFAULT      	(s16)4000
#define SP_KPDIV 					((u16)10)
#define PID_SPEED_KI_DEFAULT      	(s16)200
#define SP_KIDIV 					((u16)15)


/* ******************************ADC通道号定义****************************************** */

#define ADC0_CURRETN_A_CHANNEL       		(ADC_CHANNEL_2)                             /* A相电流采样通道 */
#define ADC0_CURRETN_B_CHANNEL       		(ADC_CHANNEL_1)                             /* B相电流采样通道 */
#define ADC0_BUS_VOL_MSK                    (ADC_CHANNEL_12)                            /* 母线电压采样通道 */
#define ADC0_TEMP_MSK                       (ADC_CHANNEL_8)                             /* 温度采样通道 */

#define ADC_STATE_RESET()                 	{ADC0_CFG |= BIT2;}

#endif
 
 
