/*******************************************************************************
 * ��Ȩ���� (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� parameter.h
 * �ļ���ʶ��
 * ����ժҪ�� parameter config
 * ����˵���� ��
 * ��ǰ�汾�� V1.0
 * ��    �ߣ� Andrew kong, Howlet Li
 * ������ڣ� 2020��8��18��
 *
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "basic.h"
#include "hardware_config.h"
/* ---------------------------------������ض���------------------------------ */
#define ENABLE_FUNCTION                1           /* �������� */
#define DISABLE_FUNCTION               0           /* �رչ��� */

/* -------------------------- LKSSCOPE��λ������/�������� ------------------------ */
#define LKSSCOPE_START_FUNCTION      DISABLE_FUNCTION       /* Lksscope���Ƶ����ͣ���� */
#define MANUAL_SPEED                 120                    /* ���������źţ����뷶Χ��START_THRESHOLD_ADC-1400  */
                                                            /* С�� START_THRESHOLD_ADC ����رգ�
                                                            ����START_THRESHOLD_ADCС��SPEED_UP_ADC��������У�
                                                            ����SPEED_UP_ADC��ʼ���٣�����1600�������� */
/* -------------------------- ����Զ���ͣ���� ------------------------ */
#define START_UP_TEST_FUNCTION      DISABLE_FUNCTION      /* ����Զ���ͣ���� */
#define START_TEST_TIME             2000                  /* �����ͣ���Դ��� */
#define START_DELAY_TIME            2000                  /* ��λ��ms,������ʱʱ�� */
#define START_WORK_TIME             2500                  /* ��λ��ms,������������ʱ�� */
 
/* --------------------------------- ˳���������� ------------------------------ */
#define ON_FLY_START_FUNCTION         DISABLE_FUNCTION       /* ˳������ */

#define ON_FLY_RUN_TIME               (u16)5  //˳��ʱ�����ã���λ��ms

#define ON_FLY_MAX_DUTY               (u16)(0.8 * PWM_PERIOD)
#define ON_FLY_MIN_DUTY               (u16)(0.1 * PWM_PERIOD)

#define MOTOR_MIN_SPEED               (u32)200//4915  //��͵�ѹ����С����ת��
#define PER_ONE_DUTY_ADD_SPEED        (u32)200//500   //ÿ����1%ռ�ձȵ��������ת��

#define ON_FLY_MAX_POWER              (u16)(ON_FLY_MAX_DUTY * 32767/PWM_PERIOD)
#define ON_FLY_MIN_POWER              (u16)(ON_FLY_MIN_DUTY * 32767/PWM_PERIOD)

#define ON_FLY_VOL                    (u16)1    //(˳�����ж��ż�����λ��V)
#define ON_FLY_ADC_THD                (u16)(ON_FLY_VOL * BEMF_SHUNT_RATIO*32767/ADC_SUPPLY_VOLTAGE) 
/* --------------------------------- EABS����������� ------------------------------ */
#define EABS_FUNCTION                 DISABLE_FUNCTION        /* Eabsɲ������ */

#define EABS_HARD                     ENABLE_FUNCTION         /* ʹ�ܺ�ɲ���������¹ܣ�����Ϊ��ɲ���������¹���һ��ռ�ձ�����̽� */
                                                              /* PS:������ѹ��Դ������ɲ��ʱ����Դ���ܻ�����������������õ�ذ����һЩ */
																															/* PS:����ʹ��Ӳɲ */
#define EABS_SLIP_TIME               (u16)100                  /* ɲ��ǰ����ʱ������ */
#define EABS_RUN_TIME                (u16)100                 /* ɲ��ʱ������ */
#define EABS_TOTAL_TIME              (u16)(EABS_SLIP_TIME + EABS_RUN_TIME)
#define SOFT_EABS_STEP               (u16)50                  /* ��ɲ�����ٲ�����ռ�ձ�һֱ�Ӵ�ֱ������ */
#define SOFT_EABS_MIN_DUTY           (u16)1000                /* ��ɲ������ռ�ձ� */

/* --------------------------------- �ٶȻ��������� -------------------------------------- */
#define SPEED_LOOP_FUNCTION            DISABLE_FUNCTION          /* �ٶȻ����� (֧�����ٱջ�)*/
#define EXPECTED_MACHINE_SPEED         (u32)250                  /* ��λ��RPM����еת��Ŀ��ֵ */  
#define SPEED_LOOP_MIN_SPEED           (u32)200                  /* ��λ��RPM���ٶȻ�ģʽ����С��е�ٶ� */
#define EXPECTED_ELECT_SPEED           (u32)(MOTOR_POLE_NUMBER*EXPECTED_MACHINE_SPEED)   /* ��λ��HZ����ת��Ŀ��ֵ����ʵ�ʵ�ת�ٵ�60�� */

///* --------------------------------- ���ʻ��������� -------------------------------------- */
//#define POWER_LOOP_FUNCTION            DISABLE_FUNCTION          /* ���ʻ����� */
//#define EXPECTED_POWER                 (u32)50                  /* ��λ��W��Ŀ�깦��ֵ */  
//#define EXPECTED_POWER_MIN             (u32)10                  /* ��λ��W�����ʻ�ģʽ����С���� */


/*------------------------------------�����������-----------------------------------------*/
#define START_THRESHOLD_ADC     100        //��������ź�ADCֵ 
#define START_POWER             1200       //���������Сռ�ձȣ�START_POWER/32767
#define TRIGGER_DUTY_CONTROL              0     //���ռ�ձȵ���ģʽ
#define TRIGGER_SPEED_CONTROL             1     //����ٶȻ�����ģʽ
#define TRIGGER_CONTROL_MODE             TRIGGER_DUTY_CONTROL        //�������ģʽѡ��

#define SPEED_UP_ADC            400        //��������ź�ADCֵ  ���뷶Χ�� ����START_THRESHOLD_ADC��С��1600
#define SPEED_UP_RATIO          19         //���ٱ��ʣ��ɸ��ݰ��ADC�ɼ���Χ������
#define SPEED_UP_UNIT      (u32)((100000*(MOTOR_MACHINE_SPEED_MAX - SPEED_LOOP_MIN_SPEED))/(U12_MAX - SPEED_UP_ADC))  //������ٱ���  1.602 

/*******************************************************************************
 ����ģʽ�� ���ռ�ձȵ���ģʽ
 ���������� 1��ģʽ�°�����ٽ����������ռ�ձȣ���СֵΪSTART_POWER�����ֵΪ32767��
            2�����ADC����ֵ��Speed_value������ START_THRESHOLD_ADC �������������SPEED_UP_ADC ������١�
		    3����ģʽ�µĵ�������ٶ�ȡ������ڵ�ǰռ�ձ��µ����������
 *******************************************************************************/

/*******************************************************************************
 ����ģʽ�� ����ٶȻ�����ģʽ(֧�����ٱջ�)
 ���������� 1��ģʽ�°������ֱ�ӿ��Ƶ���Ļ�еת�٣���СֵΪSTART_POWER�¶�Ӧ�Ļ�еת�٣����ֵΪMOTOR_MACHINE_SPEED_MAX��
            2�����ADC����ֵ��Speed_value������ START_THRESHOLD_ADC �������������SPEED_UP_ADC ������١�
		    3��һ��Ϊ�˵�������ȶ������������������ת���º�����ٶȻ�����ģʽ
 *******************************************************************************/



 //�����ŵ�� ����ת
/* --------------------------------- ������� -------------------------------------------- */
#define MOTOR_POLE_NUMBER               5                         /* ��������� */
#define MOTOR_MACHINE_SPEED_MAX        (u32)4000                  /* ��λ��RPM���������еת�� */
#define MOTOR_ELECT_SPEED              (u32)(MOTOR_POLE_NUMBER*MOTOR_MACHINE_SPEED/60)    /* ��λ��HZ��������ת�ٵ�Ƶ�� */

/* -----------------------------------����Ӳ������----------------------------------- */
#define ADC_SUPPLY_VOLTAGE             (3.6)              //��λ: V  ADC��׼��ѹ��3.6����2.4,�󲿷�Ӧ��ѡ��3.6
#define AMPLIFICATION_GAIN             (21.33)            //�˷ŷŴ���
#define RSHUNT                         (0.003)            //��λ: ��  ����������ֵ
#define VOLTAGE_SHUNT_RATIO            (1.0/(22.0+1.0))   //ĸ�ߵ�ѹ��ѹ��
#define BEMF_SHUNT_RATIO               (1.0/(22.0+1.0))   //�����Ƶ�ѹ��ѹ��  (1.0/(22.0+1.0)) 


/* ----------------------------------�����������----------------------------- */
#define MAX_BUS_CURRENT_SETTINT        (u16)5 /* ��λ��A���������������ֵ */
#define CURRENT_ADC_PER_A              (RSHUNT * AMPLIFICATION_GAIN * 32752/3.6) /* ÿ������ADCֵ */ 
#define CURRENT_LIM_VALUE              (u16)(MAX_BUS_CURRENT_SETTINT * CURRENT_ADC_PER_A) /* ������ADCֵ */


/* ----------------------------------Ӳ��������������---------------------------- */
#define SHORT_BUS_CURRENT              (u16)80 /* ĸ�ߵ�����ֵ */
#define SHORT_CURRENT_VOL              (SHORT_BUS_CURRENT * RSHUNT * AMPLIFICATION_GAIN *10000)   /* ��λ: 0.1mv,��·��ѹ */
#define SHORT_CURRENT_DAC              (u16)((SHORT_BUS_CURRENT * RSHUNT * 4096)/4.85 )     /* ��·��ѹ��ӦDACֵ */

//#define SHORT_PROTECT_DAC              (u16)(OPA_OUT_BASE_DAC + SHORT_CURRENT_DAC) /* ��·������Ӧ��DACֵ = �˷Ż������ + �趨�Ķ�·��������Ӧ��DAC */
/* ----------------------------------�ּ�������������----------------------------- */
#define BUS_CURRENT_FIRST              (u16)5    /* һ������ */
#define BUS_CURRENT_SECOND             (u16)10   /* �������� */
#define BUS_CURRENT_THRED              (u16)15   /* �������� */

#define CURRENT_ADC_PER_A              (RSHUNT * AMPLIFICATION_GAIN * 32752/3.6) /* ÿ������ADCֵ */ 

#define OVER_CURRENT_FIRST_THD         (u16)(BUS_CURRENT_FIRST * CURRENT_ADC_PER_A)  /* ��һ����������ADCֵ */
#define OVER_CURRENT_SECOND_THD        (u16)(BUS_CURRENT_SECOND * CURRENT_ADC_PER_A) /* �ڶ�����������ADCֵ */
#define OVER_CURRENT_THRED_THD         (u16)(BUS_CURRENT_THRED * CURRENT_ADC_PER_A) /* �ڶ�����������ADCֵ */

#define TIME_LIMIT_FIRST               2000  /* һ������ʱ�� */
#define TIME_LIMIT_SECOND              500   /* ��������ʱ�� */
#define TIME_LIMIT_THRED               100   /* ��������ʱ�� */


/* ----------------------------------��ѹ��������------------------------------- */
#define LOW_VOLATAGE_THD                  11   /* Ƿѹ��ѹ */
#define RSM_LO_VOLATAGE_THD               10.5 /* Ƿѹ�ָ���ѹ */
#define OV_VOLTAGE_THD                    55   /* ��ѹ�ż� */
#define RSM_OV_VOLTAGE_THD                30   /* ��ѹ�ָ��ż� */

#define LOW_VOLATAGE_THD_1                11.0   /* ��һ��Ƿѹ��ѹ:���й�����Ƿѹ */
#define LOW_VOLATAGE_THD_2                11.0   /* �ڶ���Ƿѹ��ѹ:����֮ǰǷѹ */

#define FIRST_LOW_TIME                    300    /* ��һ��Ƿѹʱ�� ��λ��ms */

#define LOW_VOLATAGE_FIRST                (u16)(LOW_VOLATAGE_THD_1 * VOLTAGE_SHUNT_RATIO/3.6*32768)  
#define LOW_VOLATAGE_SECOND               (u16)(LOW_VOLATAGE_THD_2 * VOLTAGE_SHUNT_RATIO/3.6*32768)  
 
#define LOW_VOLATAGE_ADC                  (u16)(LOW_VOLATAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768)   
#define RSM_LO_VOLATAGE_ADC               (u16)(RSM_LO_VOLATAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768)   
#define OV_VOLTAGE_ADC                    (u16)(OV_VOLTAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768)   
#define RSM_OV_VOLTAGE_ADC                (u16)(RSM_OV_VOLTAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768) 

/* ----------------------IPD ת�ӳ�ʼλ�ü�� ����ע��ʱ������---------------- */
#define SEEK_POSITION_STATUS           (TRUE)            //��ʼλ�ü��״̬ TRUEΪʹ��, FALSEΪ��ʹ��
#define U_START_ANGLE_COMP             (0)               //��λ:�� ��ʼλ�ü�ⲹ���Ƕ�

#define IPD_PLUS_TIME_SETTING          (50)      //80         /* ����ע��ʱ�������� ��λus */
#define IPD_WAIT_TIME_SETTING          (400)     //400       /* ������еȴ�ʱ�������� ��λus */

#define IPD_PLUS_TIME_WIDTH            (u32)(IPD_PLUS_TIME_SETTING*(MCU_MCLK/1000000))   /* ����ע��ʱ�������� ��λclk */
#define IPD_PLUS_WAIT_TIME             (u32)(IPD_WAIT_TIME_SETTING*(MCU_MCLK/1000000))   /* ������еȴ�ʱ�������� ��λclk */

/* -----------------------------------������������----------------------------------------- */
#define STARTUP_HAlL_COMM_TIME         20000     //20000       /* ����ʱ����С����ʱ�� ��λ��HALLģ��ʱ�������� */
#define STARTUP_HAlL_COMM_TIMEEX       1000000          /* �Ƚ�������ģʽ�������ʱ�� ��λ��HALLģ��ʱ�������� */
#define OVERFOLLW_HAlL_COMM_TIME       500000           /* ��ʱ����ʱ������ ��λ��HALLģ��ʱ�������� */

/* ----------------------------------����ģʽ�л�----------------------------------------- */
#define WORK_MODE_THRESHLD             185000           /* ADCģʽ�л��Ƚ���ģʽ�ٶ���ֵ */ 
#define QUIT_CMP_THRESHLD              200000           /* �Ƚ���ģʽ�л�ADCģʽ�ٶ���ֵ */

/* ----------------------------------������������----------------------------------------- */
#define HEAVY_LOAD_START                 0               /* ������������ */
#define FIRST_START_MIN_DUTY             (float)0.24      /* ǰ����������Сռ�ձ� */
#define ADC_MODE_MIN_DUTY                (float)0.24      /* ADCģʽ��������Сռ�ձ� */

/* ----------------------------------PWM����/���ٲ���-------------------------------------- */
#define BASIC_PWM_VALUE   200                        /* PWM�������ֵ*/
#define POWER_UP_STEP     (u16)150                   /* PWM���ٲ��� */
#define POWER_DEC_STEP    (u16)30                    /* PWM���ٲ��� */

/* -----------------------------���������й�������----------------------------------- */
#define ULTRA_LOW_SPEED_FUNCTION       ENABLE_FUNCTION  /* ���������й��ܣ������²���180�ȷ�������*/
#define HFI_PWM_WIDTH                  50               /* ����ע���� */
#define HFI_PWM_MIN                    ((s16)(-PWM_PERIOD + 2))
#define HFI_PWM_PLUS                   ((s16)(-PWM_PERIOD + HFI_PWM_WIDTH))
////�ٶȻ���ѡһ��ռ�ձȺ����Ż�����������ȡ��ADC�Ż������㣬���ʻ�

/* --------------------------------�ص�����ʱ������---------------------------- */
#define RE_COMM_TIME                   1                 /* �ص�����ʱ�� ��λ��us */
#define RE_COMM_CNT                    (RE_COMM_TIME*MCU_MCLK/1000000) /* ���ۻ����ص�����ʱ�� ��λ��Clk */

/* ------------------------- BLDC SensorLess��ǰ����ʱ�� ---------------------- */
#define EALY_COMM_TIME_RISE            (s16)(-200)       /* ������������ʱ��ǰ����ʱ�� ��λ��HALLģ��ʱ�������� */  //��ֵ��ǰ���࣬��ֵ�Ӻ���
#define EALY_COMM_TIME_FALL            (s16)(-200)       /* �������½���ʱ��ǰ����ʱ�� ��λ��HALLģ��ʱ�������� */  //��Χ��(-32767,32767)

/* -----------------------------------���ת�����----------------------------- */
#define DIR_CHANGE_WAIT_TIME           (u32)(1000)          /* �������ת�л���ʱʱ�� ��λ��ms*/
#define CW                             (0)                /* ���ת��˳ʱ�� */ 
#define CCW                            (1)                /* ���ת����ʱ��*/

/* ------------------------------ADCУ׼��ز�������---------------------------- */
#define CALIB_SAMPLES                  (512)              //ADCƫ��У׼�����������޸�
#define OFFSET_THD                     (3500)             //ADCƫ�������ֵ�������޸�

/* ----------------------------Ԥ���Ծٵ���Ԥ������--------------------------- */
#define CHARGE_TIME                    (100)              //ÿ��Ԥ���ʱ�䣬����ʵ��Ӳ�������޸�


/****************************MOS�¶ȱ���*************************************/
#define MOS_TEMP_UP_VOL              5     //MOS�¶ȼ��������ѹ����λ��V  
#define MOS_TEMP_UP_RES              10    //MOS�¶ȼ���������裬��λ��K�� 

#define MOS_TEMP_OVER_TIME           500   //MOS����ʱ��

#define MOS_TEMP_OVER_RES            1.11  //MOS����ʱNTC��ֵ��80���Ӧ1.67K  6512
#define RSM_MOS_TEMP_OVER_RES        1.2   //MOS���»ָ�NTC��ֵ��75���Ӧ1.98K  7520
   
#define MOS_TEMP_OVER_THD            (u32)((MOS_TEMP_OVER_RES * MOS_TEMP_UP_VOL * 32767)/((MOS_TEMP_OVER_RES + MOS_TEMP_UP_RES) * 3.6))
#define RSM_MOS_TEMP_OVER_THD        (u32)((RSM_MOS_TEMP_OVER_RES * MOS_TEMP_UP_VOL * 32767)/((RSM_MOS_TEMP_OVER_RES + MOS_TEMP_UP_RES) * 3.6))

/****************************BAT�¶ȱ���*************************************/
#define BAT_TEMP_UP_VOL              5     //����¶ȼ��������ѹ����λ��V  
#define BAT_TEMP_UP_RES              10    //MOS�¶ȼ���������裬��λ��K�� 

#define BAT_TEMP_OVER_TIME           500  

#define BAT_TEMP_OVER_RES            1.11  //��ع���ʱNTC��ֵ��80���Ӧ1.67K  6512
#define RSM_BAT_TEMP_OVER_RES        1.2   //��ع��»ָ�NTC��ֵ��75���Ӧ1.98K  7520
   
#define BAT_TEMP_OVER_THD            (u32)((BAT_TEMP_OVER_RES * BAT_TEMP_UP_VOL * 32767)/((BAT_TEMP_OVER_RES + BAT_TEMP_UP_RES) * 3.6))
#define RSM_BAT_TEMP_OVER_THD        (u32)((RSM_BAT_TEMP_OVER_RES * BAT_TEMP_UP_VOL * 32767)/((RSM_BAT_TEMP_OVER_RES + BAT_TEMP_UP_RES) * 3.6))

/****************************��ת�ָ�����*************************************/
#define STALL_NUMBER_STATUS            (FALSE)            /* ��ת�ָ�״̬����, TRUE = ���޻ָ��� 
                                                           FALSE = STALL_NUMBER �λָ�����*/
#define STALL_NUMBER                   (200)             /* ��ת�ָ�����*/
#define STALL_FAULT_RECOVER_TIME       (400)             /* ��λ��ms  ��ת�ָ�ʱ�� */

#endif  /* __PARAMETER_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* -----------------------------------END OF FILE------------------------------- */

