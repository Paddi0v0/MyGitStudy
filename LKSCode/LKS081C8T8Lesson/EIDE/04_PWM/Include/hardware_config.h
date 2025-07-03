/*******************************************************************************

 * 本文件说明：
 * 1. 该文件集中存放与硬件电路紧耦合且在各功能模块（PWM / ADC / OPA / DAC 等）
 *    中都会用到的宏定义与常量，属于板级支持包(BSP)的一部分。
 * 2. 当仅进行 GPIO 点灯等简单实验时，可不包含此头文件；
 *    当开始使用 PWM、ADC 或电机控制算法时，需要包含并根据实际硬件改值。
 * 3. 修改原则：
 *    – 更换 MCU 或 PCB 原理图后，只需在这里调整时钟、引脚通道映射等宏，
 *      业务层代码无需改动即可移植。
 *    – 若不清楚宏含义，请参考每行结尾的中文注释。
 *******************************************************************************/

/*------------------------------prevent recursive inclusion
 * -------------------*/
#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "lks32mc08x_lib.h"

#define P_HIGH__N_HIGH 0 /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#define P_HIGH__N_LOW 1  /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */

#define CHIP_PART_NUMBER                                                       \
  LKS32MC081 /* 芯片型号选择，选择不正确将影响芯片模块的初始化 */

#if ((CHIP_PART_NUMBER == LKS32MC084D) || (CHIP_PART_NUMBER == LKS32MC086D) || \
     (CHIP_PART_NUMBER == LKS32MC087D))
#define MCPWM_SWAP_FUNCTION                                                    \
  1 /* 使能/禁用 MCPWM 通道 P/N 交换功能，1 表示使能 */
#define PRE_DRIVER_POLARITY                                                    \
  P_HIGH__N_HIGH /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#else
#define PRE_DRIVER_POLARITY                                                    \
  P_HIGH__N_LOW /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */
#endif

/* ----------------------PWM 频率及死区定义-----------------------------------
 */
#define MCU_MCLK (96000000LL)    /* PWM模块运行主频 */
#define PWM_MCLK ((u32)MCU_MCLK) /* PWM模块运行主频 */
#define PWM_PRSC ((u8)0)         /* PWM模块运行预分频器 */
#define PWM_FREQ ((u16)16000)    /* PWM斩波频率 */

/* 电机控制PWM 周期计数器值 */
#define PWM_PERIOD                                                             \
  ((u16)(PWM_MCLK /                                                            \
         (u32)(2 * PWM_FREQ * (PWM_PRSC + 1)))) /* 电机 PWM 的周期计数值 */
/* PFC控制PWM 周期计数器值 */
#define PFC_PERIOD                                                             \
  ((u16)(PWM_MCLK /                                                            \
         (u32)(2 * PFC_FREQ * (PWM_PRSC + 1)))) /* PFC PWM 的周期计数值 */

#define DEADTIME_NS ((u16)1200) /* 死区时间 */
#define DEADTIME                                                               \
  (u16)(((unsigned long long)PWM_MCLK * (unsigned long long)DEADTIME_NS) /     \
        1000000000uL)

#define DEADTIMECOMPVOLTAGE                                                    \
  (u16)(DEADTIME_NS / (1000000000.0 / PWM_FREQ) * MAX_MODULE_VALUE)

/* --------------------------------ADC通道号定义------------------------------
 */
#define ADC0_CHANNEL_OPA0 ADC_CHANNEL_0 /* ADC0—OPA0 对应硬件通道 0 */
#define ADC0_CHANNEL_OPA1 ADC_CHANNEL_1 /* ADC0—OPA1 对应硬件通道 1 */
#define ADC0_CHANNEL_OPA2 ADC_CHANNEL_2 /* ADC0—OPA2 对应硬件通道 2 */
#define ADC0_CHANNEL_OPA3 ADC_CHANNEL_3 /* ADC0—OPA3 对应硬件通道 3 */

#define ADC1_CHANNEL_OPA0 ADC_CHANNEL_0 /* ADC1—OPA0 对应硬件通道 0 */
#define ADC1_CHANNEL_OPA1 ADC_CHANNEL_1 /* ADC1—OPA1 对应硬件通道 1 */
#define ADC1_CHANNEL_OPA2 ADC_CHANNEL_2 /* ADC1—OPA2 对应硬件通道 2 */
#define ADC1_CHANNEL_OPA3 ADC_CHANNEL_3 /* ADC1—OPA3 对应硬件通道 3 */

/* ADC相电流采样时序，硬件相关 ------------------------------------------------
 */
/* Porting Application Notice 注意采样序列 ------------------------------------
 */
#define ADC0_CURRETN_A_CHANNEL (ADC0_CHANNEL_OPA0)
#define ADC0_CURRETN_B_CHANNEL (ADC0_CHANNEL_OPA1)
#define ADC0_CURRETN_C_CHANNEL (ADC0_CHANNEL_OPA2)

#define ADC_1SHUNT_CURR_CH (ADC0_CHANNEL_OPA3) /* 单电阻采样电流通道 */

#define ADC_BUS_VOL_CHANNEL (ADC_CHANNEL_4)    /* 母线电压ADC采样通道 */
#define M0_ADC_BUS_CURR_CH (ADC0_CHANNEL_OPA3) /* 母线电流ADC采样通道 */

#define ADC0_TEMP_CHANNEL (ADC_CHANNEL_7) /* 温度检测 */

#define BEMF_CH_A ADC_CHANNEL_17 /* A相反电势检测ADC通道号 */
#define BEMF_CH_B ADC_CHANNEL_16 /* B相反电势检测ADC通道号 */
#define BEMF_CH_C ADC_CHANNEL_15 /* C相反电势检测ADC通道号 */

/* 电流内环相电流采样，ADC通道采样结果宏定义 */
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
#define GET_ADC0_DATA(value)                                                   \
  {                                                                            \
    value.nData0 = (s16)ADC0_DAT0;                                             \
  }
#define GET_ADC1_DATA(value)                                                   \
  {                                                                            \
    value.nData0 = (s16)ADC0_DAT2;                                             \
  }
#else
#define GET_ADC0_DATA(value)                                                   \
  {                                                                            \
    value.nData0 = (s16)ADC0_DAT0;                                             \
  }
#define GET_ADC1_DATA(value)                                                   \
  {                                                                            \
    value.nData0 = (s16)ADC0_DAT1;                                             \
  }
#endif

/* 母线电压ADC通道采样结果宏定义 */
#define GET_BUS_VOL_ADC_RESULT (ADC0_DAT4)

#define ADC_STATE_RESET()                                                      \
  {                                                                            \
    ADC0_CFG |= BIT2;                                                          \
  } /* ADC0 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC_SOFTWARE_TRIG_ONLY()                                               \
  {                                                                            \
    ADC0_TRIG = 0;                                                             \
  } /* ADC设置为仅软件触发 */

/* ------------------------------PGA操作相关定义 ------------------------------
 */
#define OPA0_GIAN (PGA_GAIN_20)      /* OPA0 放大倍数 = 20 */
#define OPA1_GIAN (PGA_GAIN_20 << 2) /* OPA1 放大倍数 = 20 */
#define OPA2_GIAN (PGA_GAIN_20 << 4) /* OPA2 放大倍数 = 20 */
#define OPA3_GIAN (PGA_GAIN_20 << 6) /* OPA3 放大倍数 = 20 */

/* ------------------------------DAC操作相关定义 ------------------------------
 */
#define DAC_RANGE_1V2 1  /* DAC 1.2V量程 */
#define DAC_RANGE_3V0 0  /* DAC 3.0V量程 */
#define DAC_RANGE_4V85 2 /* DAC 4.85V量程 */

#endif
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR
 * **********************/
/* ------------------------------END OF FILE------------------------------------
 */
