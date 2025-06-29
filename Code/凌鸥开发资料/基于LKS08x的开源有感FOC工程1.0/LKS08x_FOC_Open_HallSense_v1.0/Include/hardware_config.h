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
#include "lks32mc08x_NVR.h"

/* ==============================PWM 频率及死区定义=========================== */

#define MCU_MCLK							((u32)96000000uL) 										/* PWM模块运行主频 */
#define PWM_MCLK							((u32)MCU_MCLK) 										/* PWM模块运行主频 */
#define PWM_PRSC 							((u8)0) 												/* PWM模块运行预分频器 */
#define PWM_FREQ 							((u16)15625) 											/* PWM斩波频率 */

#define PWM_PERIOD         					((u16) (PWM_MCLK / (u32)(2 * PWM_FREQ *(PWM_PRSC+1)))) 	/* PWM 周期计数器值 */

#define DEADTIME_NS        					((u16)1300)												/* 死区时间 */
#define DEADTIME           					(u16)(((unsigned long long)PWM_MCLK * (unsigned long long)DEADTIME_NS)/1000000000uL)
 
/* ******************************输入输出端口定义****************************************** */

#define BREAK_INPUT_MASK                  	(GPIO0_PDI & BIT3)  									/* 刹车信号输入 */ 

#define BREAK_INPUT                       	(BIT1)    												/* 刹车信号 */

/* ******************************ADC通道号定义****************************************** */

#define ADC0_CHANNEL_OPA0            		ADC_CHANNEL_0
#define ADC0_CHANNEL_OPA1            		ADC_CHANNEL_1
#define ADC0_CHANNEL_OPA2            		ADC_CHANNEL_2
#define ADC0_CHANNEL_OPA3            		ADC_CHANNEL_3

#define ADC0_CURRETN_A_CHANNEL       		(ADC0_CHANNEL_OPA0) 
#define ADC0_CURRETN_B_CHANNEL       		(ADC0_CHANNEL_OPA1)
#define ADC0_CURRETN_C_CHANNEL       		(ADC0_CHANNEL_OPA2)

#define ADC0_BUS_CUR_CHANNEL         		(ADC0_CHANNEL_OPA3) 

//#define PGA_GAIN_20                    		0                   							/* 反馈电阻200:10 */
//#define PGA_GAIN_9P5                   		1                   							/* 反馈电阻190:20 */
//#define PGA_GAIN_6                     		2                   							/* 反馈电阻180:30 */
//#define PGA_GAIN_4P25                  		3                   							/* 反馈电阻170:40 */
                                                                                  
#define OPA0_GIAN                      		(PGA_GAIN_20)
#define OPA1_GIAN                      		(PGA_GAIN_20 << 2)
#define OPA2_GIAN                      		(PGA_GAIN_20 << 4)
#define OPA3_GIAN                      		(PGA_GAIN_9P5 << 6)

/* ----------------------- 第一次采样顺序MSK -------------------------------- */

#define ADC0_CUR_A_1ST_MSK      			(u16)(ADC0_CURRETN_A_CHANNEL) 					/* ADC先采样A相电流 */
#define ADC0_CUR_B_1ST_MSK      			(u16)(ADC0_CURRETN_B_CHANNEL) 					/* ADC先采样B相电流 */
#define ADC0_CUR_C_1ST_MSK      			(u16)(ADC0_CURRETN_C_CHANNEL) 					/* ADC先采样B相电流 */

#define ADC1_CUR_A_1ST_MSK      			(u16)(ADC0_CURRETN_A_CHANNEL<<8) 				/* ADC先采样B相电流 */
#define ADC1_CUR_C_1ST_MSK      			(u16)(ADC0_CURRETN_C_CHANNEL<<8) 				/* ADC先采样C相电流 */
#define ADC1_CUR_B_1ST_MSK      			(u16)(ADC0_CURRETN_B_CHANNEL<<8) 				/* ADC先采样B相电流 */

/* ----------------------- 第三次采样顺序MSK -------------------------------- */

#define ADC0_3th_MSK            			(u16)(ADC_CHANNEL_8) 							/* ADC采样母线电压 */
#define ADC1_3th_MSK            			(u16)(ADC0_BUS_CUR_CHANNEL<<8)  				/* ADC采样母线电流 */

/* ----------------------- 第四次采样顺序MSK -------------------------------- */

#define ADC0_4th_MSK            			(u16)(ADC_CHANNEL_11) 							/* B相反电动势 */
#define ADC1_4th_MSK            			(u16)(ADC_CHANNEL_9<<8) 						/* 转把电压 */  

#define ADC_STATE_RESET()                 	{ADC0_CFG |= BIT2;}

/* 母线电压ADC通道采样结果宏定义 */
#define GET_BUS_VOL_ADC_RESULT         		(ADC0_DAT4)

/* 转把电压ADC通道采样结果宏定义 */
#define GET_SPEED_ADC_RESULT           		(ADC0_DAT7) 

/* 母线电流ADC通道采样结果宏定义 */
#define GET_BUS_ADC_RESULT             		(ADC0_DAT5)

/* 芯片温度ADC通道采样结果宏定义 */
#define GET_TEMPERTURE_ADC             		(ADC0_DAT11 >> 4)

/* ******************************PGA及最大限流定义****************************************** */

#define BUS_PGA_GAIN                      	9.05   											/* 母线放大倍数 */
#define RESIS_NUMBER						1												/* 母线取样电阻个数 */
#define RESISTANCE	                    	0.003 											/* 单个取样电阻阻值 */
#define SHUNT_RESISTOR                    	(RESISTANCE / RESIS_NUMBER) 					/* 取样电阻阻值 */
#define MAX_BUS_CURRENT_SETTINT           	(u16)16 										/* 最大限流电流 */
#define ABS_CURRENT_SETTINT               	(u16)12 										/* ABS限流 */

#define CURRENT_ADC_PER_A                 	(u16)(SHUNT_RESISTOR*BUS_PGA_GAIN*32752/3.6) 	/* 每安电流ADC值 */
#define CURRENT_ADC_PER_1_8A              	(u16)(CURRENT_ADC_PER_A >> 3) 					/* 每八分之一安电流ADC值 */
#define CURRENT_LIM_VALUE                 	(u16)(MAX_BUS_CURRENT_SETTINT*SHUNT_RESISTOR*BUS_PGA_GAIN*32752/3.6) 	/* 最大电流ADC值 */
#define ABS_CURRENT_VALUE                 	(u16)(ABS_CURRENT_SETTINT*SHUNT_RESISTOR*BUS_PGA_GAIN*32752/3.6)  		/* 最小电流ADC值 */
 
#define PHASE_MAX_CURRENT                  	(u16)(15000 / RESIS_NUMBER)						/* 最大相线电流 */

/* ------------------------------DAC操作相关定义 ------------------------------ */
#define DAC_RANGE_1V2                  		1                   							/* DAC 1.2V量程 */
#define DAC_RANGE_3V0                  		0                   							/* DAC 3.0V量程 */
#define DAC_RANGE_4V85                 		2                   							/* DAC 4.85V量程 */

/* ******************************欠压  过压 设定部分 ****************************************** */

#define VOLTAGE_SHUNT_RATIO                 (1.0/(40+1.0))									/* 分压比 */

#define VOLATAGE_0_2V                       (u16)(1 * VOLTAGE_SHUNT_RATIO/18*32752) 
#define VOLATAGE_0_5V                       (u16)(1 * VOLTAGE_SHUNT_RATIO/7.2*32752)  

#define LOW_VOLATAGE_THD                    (u16)(32 * VOLTAGE_SHUNT_RATIO/3.6*32752)

/////////////////////////////      48V工作电压相关宏定义    ////////////////////////////////

#define VOLATAGE_42V                        (u16)(41.8 * VOLTAGE_SHUNT_RATIO/3.6*32752)  
#define VOLATAGE_60V                      	(u16)(60 * VOLTAGE_SHUNT_RATIO/3.6*32752)
#define VOLATAGE_62V                      	(u16)(62 * VOLTAGE_SHUNT_RATIO/3.6*32752)

#define VOLATAGE_RAMP                  		15  											/* 电压滤波斜率控制 0.3V/S */


/* ****************************** BLDC相关配置 ****************************************** */

		/* 当前硬件使用的过流比较器：0：比较器0，1：比较器1 */
		
#define CMP_CHOICE                 			0 
#define PWM_FAIL_IO   						0x1500											/* 默认驱动电平设置 */

#if (CMP_CHOICE == 0) 
#define PWM_FAIL_CMPEN   					0x0091											/* FALL触发来源使能 */
#else
#define PWM_FAIL_CMPEN   					0x00a2											/* FALL触发来源使能 */
#endif

#define PWM_FAIL_CMPDIS   					0x0081											/* FALL触发来源关闭 */
#define MCPWM_FAIL_IO_CMPEN       	  		(PWM_FAIL_IO | PWM_FAIL_CMPEN)
#define MCPWM_FAIL_IO_CMPDIS       	  		(PWM_FAIL_IO | PWM_FAIL_CMPDIS)

#define PWM_01   							0x4141											/* 驱动极性设置 */
#define PWM_23   							0x4141											/* 驱动极性设置 */

#define H_PWM_L_LOW   						0x04											/* 上管斩波下管关闭 */
#define H_PWM_L_PWM   						0x00											/* 上管下管互补输出 */
#define H_LOW_L_HIG   						0x1c											/* 上管关闭下管置高 */
#define H_LOW_L_PWM   						0x08											/* 上管关闭下管斩波 */
#define H_LOW_L_LOW   						0x0c											/* 上管下管同时关闭 */
#define H_HIG_L_LOW   						0x2c											/* 上管置高下管关闭 */

#define A_H_PWM_L_LOW   					(H_PWM_L_LOW << 0)
#define A_H_PWM_L_PWM   					(H_PWM_L_PWM << 0)
#define A_H_LOW_L_HIG   					(H_LOW_L_HIG << 0)
#define A_H_LOW_L_PWM   					(H_LOW_L_PWM << 0)
#define A_H_LOW_L_LOW   					(H_LOW_L_LOW << 0)
#define A_H_HIG_L_LOW   					(H_HIG_L_LOW << 0)

#define B_H_PWM_L_LOW   					(H_PWM_L_LOW << 8)
#define B_H_PWM_L_PWM   					(H_PWM_L_PWM << 8)
#define B_H_LOW_L_HIG   					(H_LOW_L_HIG << 8)
#define B_H_LOW_L_PWM   					(H_LOW_L_PWM << 8)
#define B_H_LOW_L_LOW   					(H_LOW_L_LOW << 8)
#define B_H_HIG_L_LOW   					(H_HIG_L_LOW << 8)

#define C_H_PWM_L_LOW   					(H_PWM_L_LOW << 0)
#define C_H_PWM_L_PWM   					(H_PWM_L_PWM << 0)
#define C_H_LOW_L_HIG   					(H_LOW_L_HIG << 0)
#define C_H_LOW_L_PWM   					(H_LOW_L_PWM << 0)
#define C_H_LOW_L_LOW   					(H_LOW_L_LOW << 0)
#define C_H_HIG_L_LOW   					(H_HIG_L_LOW << 0)

#define EN_HPWM_FUNC()                    	{MCPWM_PRT = 0x0000DEAD;MCPWM_IO01 = PWM_01;MCPWM_IO23 = PWM_23;MCPWM_PRT = 0x0000CAFE;}

											/* 1_step A相悬空，B相PWM C相ON ；检测下降沿过零事件 */
#define A_OFF__B_PWM__C_ON()      			{MCPWM_IO01 = PWM_01 | (A_H_LOW_L_LOW | B_H_PWM_L_LOW); MCPWM_IO23 = PWM_23 | C_H_LOW_L_HIG;} 	

											/* 2_step A相ON，B相PWM C相悬空 ；检测上升沿过零事件 */
#define A_ON__B_PWM__C_OFF()      			{MCPWM_IO01 = PWM_01 | (A_H_LOW_L_HIG | B_H_PWM_L_LOW); MCPWM_IO23 = PWM_23 | C_H_LOW_L_LOW;}

											/* 3_step A相ON，B相悬空 C相PWM ；检测下降沿过零事件 */
#define A_ON__B_OFF__C_PWM()      			{MCPWM_IO01 = PWM_01 | (A_H_LOW_L_HIG | B_H_LOW_L_LOW); MCPWM_IO23 = PWM_23 | C_H_PWM_L_LOW;}

											/* 4_step A相悬空，B相ON C相PWM  ；检测上升沿过零事件*/
#define A_OFF__B_ON__C_PWM()      			{MCPWM_IO01 = PWM_01 | (A_H_LOW_L_LOW | B_H_LOW_L_HIG); MCPWM_IO23 = PWM_23 | C_H_PWM_L_LOW;}

											/* 5_step A相PWM，B相ON C相悬空  ；检测下降沿过零事件*/
#define A_PWM__B_ON__C_OFF()      			{MCPWM_IO01 = PWM_01 | (A_H_PWM_L_LOW | B_H_LOW_L_HIG); MCPWM_IO23 = PWM_23 | C_H_LOW_L_LOW;}

											/* 6_step A相PWM，B相悬空 C ON；检测上升沿过零事件 */
#define A_PWM__B_OFF__C_ON()      			{MCPWM_IO01 = PWM_01 | (A_H_PWM_L_LOW | B_H_LOW_L_LOW); MCPWM_IO23 = PWM_23 | C_H_LOW_L_HIG;}


#define FAIL0_ERROR          				0x10  											/* FALL0触发保护 */
#define FAIL1_ERROR          				0x20  											/* FALL1触发保护 */

#endif
 
 
