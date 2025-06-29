/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： BLDC_Control.c
 * 文件标识：
 * 内容摘要： BLDC sensorless控制相关函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2019年11月5日
 *
 * 修改记录1：
 * 修改日期：2019年11月5日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet
 * 修改内容：创建
 *
 *
 *******************************************************************************/
#ifndef __BLDC_CONTROL_H__
#define __BLDC_CONTROL_H__

#include "basic.h"

typedef struct
{
    u8 ctrState;          /* 控制状态 */
    u8 ctrMode;           /* 控制模式 */

    u8 communicateFlg;    /* 换相标志 */
    u8 check_Zerocross;   /* 检查过零点标示 */
    u8 communicateStep;   /* 当前换相电角度位置 */
    u8 oldCommunicateStep;/* 上次换相电角度位置 */
    u8 onTheFlyFlg;       /* 顺风逆风启动标志 */
    u8 HallState;         /* Hall 角度 */
    u8 motorDirect;       /* 电机方向控制 */
    u8 BEMF_edgeFlg;      /* 反电势检测方向 */
    u8 BEMF_edgeSetting;
    u8 PWM_CommCnt;
    u8 blankEndFlg;       /* 消隐结束标志 */
    u16 blankEndTimeValue;/* 消隐结束时时间戳 */
    u32 SpeedTimerCnt;    /* 当前速度 */

    u16 actPWM_Value;
    u32 minCommcationTime;
    u16 BLDC_CommTime;    /* 上次换相时Timer计数 */
    u8 OpenLoopStepCnt;   /* 开环模式下换相步数计数 */

    s16 nHalfVoltage;     /* 反电势电路检测的半母线电压值 */
    s16 BEMF_adcValue;    /* 反电势ADC值 */

    s16 last_BEMF_adcValue;/* 上次反电势ADC值 */
	
    s16 Float_adcValue;    /* 反电势ADC值 */
    s16 PWM_adcValue;      /* 反电势ADC值1 */
    s16 LOW_adcValue;      /* 反电势ADC值2 */		
		
	u8 PWMDetectFlg;       /* PWM相 */
	u8 LOWDetectFlg;       /* 导通相 */	
    u8 bemfDetectFlg;      /* 反电势采样相 */
    u8 insPhaseFlg;        /* 电压注入相 */

    s16 Phase_A_ADC;      /* 反电势ADC值 */
    s16 Phase_B_ADC;      /* 反电势ADC值1 */
    s16 Phase_C_ADC;      /* 反电势ADC值2 */	
		
    s16 PhaseA_offset;    /* A反电势ADC offset值 */
    s16 PhaseB_offset;    /* B反电势ADC offset值 */
    s16 PhaseC_offset;    /* C反电势ADC offset值 */

    s16 BusCurrentOffset; /* 电流偏置 */
    s16 PeakCurrOffset;   /* 峰值电流偏置 */

    u8 lowSpeedFlg;       /* 低速标志 */
    u16 lastCommTime;     /* 上次换相时间 */
    u16 focusCommCnt;     /* 强制换相计数 */
    u8 current_commStep;  /* 当前换相步数 */
    u16 bankCommTime;     /* 消隐时间 */
    s16 secBemfADC_Value; /* 第二相ADC反电势值 */
    u8 sCommmStabCnt;     /* 高低速切换 */

    s16 phase_current;    /* 当前相线电流值 */
    s16 peakBusCurrent;   /* 峰值电流 */

    s16 BusCur_lim_cof;   /* 滤波系数 */

    u8 commCurrentCmpFlg;

    u8 state;

    u8 Eabs_Founction_Flg; /* EABS标志 */
	u8 Eabs_Hard_Flg;      /* EABS标志 */
    u8 EabsFlg;           /* EABS标志 */
    u16 EabsCnt;           /* EABS时间 */
	u16 Eabs_Slip_Cnt;    /* EABS滑行时间 */
    s16 EabsPWM;          /* EABS占空比 */
    s16 Eabs_duty;			  /* EABS PWM给定 */		

    u16 focusCommTime;    /* 强制换相时间 */
    u8 totalFocusCommCnt;

    u8 negCommFlg;
    u8 HfiStep;
    
    volatile u8 bRevCnt;  /* 反转计数 */

    s16 HFI_pwm_Min;      /* 脉冲注入最小值,PWM左边沿 */
    s16 HFI_pwm_plus;     /* 脉冲注入宽度,PWM右边沿 */
    u8 HfiFlg;
    u8 HfiCurrStep;
    u16 motor_RunCnt;

    u8 comm_dec_cnt;      /* 当前拍脉冲注入计数 */
    u8 comm_dec_thd;      /* 当前拍脉冲注入数量门限 */

    u8 current_commCnt;   /* 当前拍脉冲注入数量 */
    u8 last_commCnt;      /* 上一拍脉冲注入数量 */
    u8 nextCommStep;
    u8 befCommStep;
    u8 secBemfUpdateFlg;  /* 第二反电势采样标志 */
    u16 PhaseVoltage;     /* 相电压 */
    s16 lastPhaseBemf;    /* 上次反电势值 */

    s16 ADC_valueH_thd;   /* 换相门槛 */
    s16 halfVol_cof;      /* 反电势电压中点校正值 */

    u16 BLDC_RunAngle;    /* BLDC模式下，对应FOC角度 */

    u32 fir_speed;        /* 滤波后的速度 */
    
    u32 wBlankTime;       /* 换相续流 消隐时间*/

	s16 OPAOUT_offset;     /* 运放输出ADC offset值 */
	s16 MAX_ADC_offset;    /* ADC 满值*/
	u16 OPA_OUT_REF;       /* 运放输出基础电压 单位mv */

} stru_BLDC_sensorlessCtr;


void BLDC_Communication( void);
void BLDC_CommProcess(void);
void BLDC_Init(void);
void speed_ref_ramp(void);
void BLDC_CMP_ModeControl(void);
void BLDC_DelayCommunication(void);
void getBemfValue(void);


#define BLDC_MODE_CMP        0              /* 比较器工作模式 */
#define BLDC_MODE_ADC        1              /* ADC工作模式 */

#endif
