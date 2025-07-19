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
 #include "lks32mc03x.h"
 #include "lks32mc03x_MCPWM.h"
 #include "lks32mc03x_sys.h"
 #include "lks32mc03x_adc.h"
 #include "lks32mc03x_MCPWM.h"
 #include "lks32mc03x_flash.h"
 #include "lks32mc03x_gpio.h"
 #include "lks32mc03x_cmp.h"
 #include "lks32mc03x_uart.h"
 #include "lks32mc03x_hall.h"
 #include "lks32mc03x_timer.h"
 #include "lks32mc03x_NVR.h"
 #include "MC_Parameter_M0.h"
 #include "PubData_DriverInstance.h"

#define  LKS32MC031              1 
#define  LKS32MC031D             2
#define  LKS32MC032              3
#define  LKS32MC033              4
#define  LKS32MC034D             5
#define  LKS32MC035              6
#define  LKS32MC036              7
#define  LKS32MC037              8
#define  LKS32MC037D             9
#define  LKS32MC037E             10
#define  LKS32MC037D_V0          11

#define  CHIP_PART_NUMBER              LKS32MC037         /* 芯片型号选择，选择不正确将影响芯片模块的初始化 */
#define  P_HIGH__N_HIGH                1
#define  P_HIGH__N_LOW                 2

#if ((CHIP_PART_NUMBER == LKS32MC037E)||(CHIP_PART_NUMBER == LKS32MC037F)||(CHIP_PART_NUMBER == LKS32MC034D) \
     ||(CHIP_PART_NUMBER == LKS32MC037D_V0)) 
    #define  MCPWM_SWAP_FUNCTION           1                  /* 芯片内置预驱需调用，芯片无内置预驱将此句屏蔽即可*/
    #define  PRE_DRIVER_POLARITY           P_HIGH__N_HIGH     /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#else
    #define  PRE_DRIVER_POLARITY           P_HIGH__N_LOW      /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */
#endif

/* ----------------------应用PWM 模块定义----------------------------------- */



/* --------------------------------ADC通道号定义------------------------------ */
#define ADC0_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC0_CHANNEL_OPA1              ADC_CHANNEL_8

/* ADC相电流采样时序，硬件相关 ------------------------------------------------ */
/* Porting Application Notice 注意采样序列 ------------------------------------ */
#define ADC0_CURRETN_A_CHANNEL			(ADC0_CHANNEL_OPA0)
#define ADC0_CURRETN_B_CHANNEL			(ADC0_CHANNEL_OPA1)

#define ADC_1SHUNT_CURR_CH				(ADC0_CHANNEL_OPA1)		/* 单电阻采样电流通道 */

#define ADC_BUS_VOL_CHANNEL				(ADC_CHANNEL_5)			/* 母线电压ADC采样通道 */
#define M0_ADC_BUS_CURR_CH				(ADC_CHANNEL_8)			/* 母线电流ADC采样通道 */

#define ADC0_TEMP_CHANNEL				(ADC_CHANNEL_11)		/* 温度检测 */
#define ADC0_SPIN_CHANNEL				(ADC_CHANNEL_1)			/* 速度输入检测 */


#define INTERNAL_VSS_CHANNEL			(ADC_CHANNEL_12)		//内部GND AD通道
#define INTERNAL_REF_CHANNEL			(ADC_CHANNEL_13)		//内部REF通道


/* ------------------------------反电动势采样序列 ------------------------------ */
#define BEMF_CH_A                      ADC_CHANNEL_1       /* A相反电势检测ADC通道号 */
#define BEMF_CH_B                      ADC_CHANNEL_2       /* B相反电势检测ADC通道号 */
#define BEMF_CH_C                      ADC_CHANNEL_3       /* C相反电势检测ADC通道号 */

//036D 采样通道
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
//M0 第一个采样数据，第二个采样数据
#define GET_ADC0_DATA_M0					(ADC_DAT0)   
#define GET_ADC1_DATA_M0					(ADC_DAT2)
#else
#define GET_ADC0_DATA_M0					(ADC_DAT0)
#define GET_ADC1_DATA_M0					(ADC_DAT1)
#endif

/* 036d 母线电压ADC通道采样结果宏定义 */
// /* 母线电压ADC通道采样结果宏定义 */
#define GET_M0_BUS_VOL_ADC_RESULT		(ADC_DAT4)

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
#define GET_M0_BEMF_DATA_A					(ADC_DAT5)
#define GET_M0_BEMF_DATA_B					(ADC_DAT6)
#define GET_M0_BEMF_DATA_C					(ADC_DAT7)
#define GET_SPIN_VOL_ADC_RESULT			(ADC_DAT5)
#else
#define GET_M0_BEMF_DATA_A					(ADC_DAT2)
#define GET_M0_BEMF_DATA_B					(ADC_DAT3)
#define GET_M0_BEMF_DATA_C					(ADC_DAT5)
#define GET_SPIN_VOL_ADC_RESULT				(ADC_DAT6)
#endif


#define GET_M0_TEMP_DATA_A					(ADC_DAT6)

#define GET_MCU_VSS							(ADC_DAT8)
#define GET_MCU_VREF						(ADC_DAT9)



#define ADC_STATE_RESET()              {ADC_CFG |= BIT11;}   /* ADC0 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC_SOFTWARE_TRIG_ONLY()       {ADC_CFG = 0;}        /* ADC设置为仅软件触发 */


/* ------------------------------PGA操作相关定义 ------------------------------ */
//只存在一个OPA
#define OPA0_GIAN                     (PGA_GAIN_6) //放大倍数宏定义在lks32mc03x_opa.h文件内(PGA_GAIN_9P5)/(PGA_GAIN_6)/(PGA_GAIN_4P25)

/* ------------------------------DAC操作相关定义 ------------------------------ */
#define DAC_RANGE_1V2                  1                   /* DAC 1.2V量程 */
#define DAC_RANGE_3V0                  0                   /* DAC 3.0V量程 */
#define DAC_RANGE_4V85                 2                   /* DAC 4.85V量程 */

#endif  /* __HARDWARE_CONFIG_H_ */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

