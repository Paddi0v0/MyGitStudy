/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� BLDC_Control.c
 * �ļ���ʶ��
 * ����ժҪ�� BLDC sensorless������غ���
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet
 * ������ڣ� 2019��11��5��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�2019��11��5��
 * �� �� �ţ�V 1.0
 * �� �� �ˣ�Howlet
 * �޸����ݣ�����
 *
 *
 *******************************************************************************/
#ifndef __BLDC_CONTROL_H__
#define __BLDC_CONTROL_H__

#include "basic.h"

typedef struct
{
    u8 ctrState;          /* ����״̬ */
    u8 ctrMode;           /* ����ģʽ */

    u8 communicateFlg;    /* �����־ */
    u8 check_Zerocross;   /* ��������ʾ */
    u8 communicateStep;   /* ��ǰ�����Ƕ�λ�� */
    u8 oldCommunicateStep;/* �ϴλ����Ƕ�λ�� */
    u8 onTheFlyFlg;       /* ˳�����������־ */
    u8 HallState;         /* Hall �Ƕ� */
    u8 motorDirect;       /* ���������� */
    u8 BEMF_edgeFlg;      /* �����Ƽ�ⷽ�� */
    u8 BEMF_edgeSetting;
    u8 PWM_CommCnt;
    u8 blankEndFlg;       /* ����������־ */
    u16 blankEndTimeValue;/* ��������ʱʱ��� */
    u32 SpeedTimerCnt;    /* ��ǰ�ٶ� */

    u16 actPWM_Value;
    u32 minCommcationTime;
    u16 BLDC_CommTime;    /* �ϴλ���ʱTimer���� */
    u8 OpenLoopStepCnt;   /* ����ģʽ�»��ಽ������ */

    s16 nHalfVoltage;     /* �����Ƶ�·���İ�ĸ�ߵ�ѹֵ */
    s16 BEMF_adcValue;    /* ������ADCֵ */

    s16 last_BEMF_adcValue;/* �ϴη�����ADCֵ */
	
    s16 Float_adcValue;    /* ������ADCֵ */
    s16 PWM_adcValue;      /* ������ADCֵ1 */
    s16 LOW_adcValue;      /* ������ADCֵ2 */		
		
	u8 PWMDetectFlg;       /* PWM�� */
	u8 LOWDetectFlg;       /* ��ͨ�� */	
    u8 bemfDetectFlg;      /* �����Ʋ����� */
    u8 insPhaseFlg;        /* ��ѹע���� */

    s16 Phase_A_ADC;      /* ������ADCֵ */
    s16 Phase_B_ADC;      /* ������ADCֵ1 */
    s16 Phase_C_ADC;      /* ������ADCֵ2 */	
		
    s16 PhaseA_offset;    /* A������ADC offsetֵ */
    s16 PhaseB_offset;    /* B������ADC offsetֵ */
    s16 PhaseC_offset;    /* C������ADC offsetֵ */

    s16 BusCurrentOffset; /* ����ƫ�� */
    s16 PeakCurrOffset;   /* ��ֵ����ƫ�� */

    u8 lowSpeedFlg;       /* ���ٱ�־ */
    u16 lastCommTime;     /* �ϴλ���ʱ�� */
    u16 focusCommCnt;     /* ǿ�ƻ������ */
    u8 current_commStep;  /* ��ǰ���ಽ�� */
    u16 bankCommTime;     /* ����ʱ�� */
    s16 secBemfADC_Value; /* �ڶ���ADC������ֵ */
    u8 sCommmStabCnt;     /* �ߵ����л� */

    s16 phase_current;    /* ��ǰ���ߵ���ֵ */
    s16 peakBusCurrent;   /* ��ֵ���� */

    s16 BusCur_lim_cof;   /* �˲�ϵ�� */

    u8 commCurrentCmpFlg;

    u8 state;

    u8 Eabs_Founction_Flg; /* EABS��־ */
	u8 Eabs_Hard_Flg;      /* EABS��־ */
    u8 EabsFlg;           /* EABS��־ */
    u16 EabsCnt;           /* EABSʱ�� */
	u16 Eabs_Slip_Cnt;    /* EABS����ʱ�� */
    s16 EabsPWM;          /* EABSռ�ձ� */
    s16 Eabs_duty;			  /* EABS PWM���� */		

    u16 focusCommTime;    /* ǿ�ƻ���ʱ�� */
    u8 totalFocusCommCnt;

    u8 negCommFlg;
    u8 HfiStep;
    
    volatile u8 bRevCnt;  /* ��ת���� */

    s16 HFI_pwm_Min;      /* ����ע����Сֵ,PWM����� */
    s16 HFI_pwm_plus;     /* ����ע����,PWM�ұ��� */
    u8 HfiFlg;
    u8 HfiCurrStep;
    u16 motor_RunCnt;

    u8 comm_dec_cnt;      /* ��ǰ������ע����� */
    u8 comm_dec_thd;      /* ��ǰ������ע���������� */

    u8 current_commCnt;   /* ��ǰ������ע������ */
    u8 last_commCnt;      /* ��һ������ע������ */
    u8 nextCommStep;
    u8 befCommStep;
    u8 secBemfUpdateFlg;  /* �ڶ������Ʋ�����־ */
    u16 PhaseVoltage;     /* ���ѹ */
    s16 lastPhaseBemf;    /* �ϴη�����ֵ */

    s16 ADC_valueH_thd;   /* �����ż� */
    s16 halfVol_cof;      /* �����Ƶ�ѹ�е�У��ֵ */

    u16 BLDC_RunAngle;    /* BLDCģʽ�£���ӦFOC�Ƕ� */

    u32 fir_speed;        /* �˲�����ٶ� */
    
    u32 wBlankTime;       /* �������� ����ʱ��*/

	s16 OPAOUT_offset;     /* �˷����ADC offsetֵ */
	s16 MAX_ADC_offset;    /* ADC ��ֵ*/
	u16 OPA_OUT_REF;       /* �˷����������ѹ ��λmv */

} stru_BLDC_sensorlessCtr;


void BLDC_Communication( void);
void BLDC_CommProcess(void);
void BLDC_Init(void);
void speed_ref_ramp(void);
void BLDC_CMP_ModeControl(void);
void BLDC_DelayCommunication(void);
void getBemfValue(void);


#define BLDC_MODE_CMP        0              /* �Ƚ�������ģʽ */
#define BLDC_MODE_ADC        1              /* ADC����ģʽ */

#endif
