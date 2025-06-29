/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� hardware_config.h
 * �ļ���ʶ��
 * ����ժҪ�� Ӳ������ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet
 * ������ڣ� 2020��8��20��
 *
 * �޸ļ�¼1��
 * �޸����ڣ� 2020��8��20��
 * �� �� �ţ� V 2.0
 * �� �� �ˣ� Howlet
 * �޸����ݣ� ����
 *
 *******************************************************************************/

/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "lks32mc07x.h"
#include "lks32mc07x_MCPWM.h"
#include "lks32mc07x_sys.h"
#include "lks32mc07x_adc.h"
#include "lks32mc07x_MCPWM.h"
#include "lks32mc07x_flash.h"
#include "lks32mc07x_gpio.h"
#include "lks32mc07x_DMA.h"
#include "lks32mc07x_cmp.h"
#include "lks32mc07x_uart.h"
#include "lks32mc07x_hall.h"
#include "lks32mc07x_tim.h"
#include "lks32mc07x_NVR.h"
//#include "lks32mc07x_iwdg.h"
#include "basic.h"
#include "PID.h"	

#include "hardware_init.h"
#include "Global_Variable.h"
#include "MC_Parameter.h"

#define LKS32MC070          1
#define LKS32MC071          2
#define LKS32MC072          3
#define LKS32MC073          4
#define LKS32MC074D         5
#define LKS32MC074DO        6
#define LKS32MC076D         7
#define LKS32MC077          8
#define LKS32MC077D         9
#define LKS32MC078          10
#define LKS32MC079          11
/* ----------------------PWM Ƶ�ʼ���������----------------------------------- */
#define MCU_MCLK                       (96000000LL)       /* PWMģ��������Ƶ */ 

#define PWM_MCLK                       ((u32)MCU_MCLK)    /* PWMģ��������Ƶ */
#define PWM_PRSC                       ((u8)0)            /* PWMģ������Ԥ��Ƶ�� */
#define PWM_FREQ                       ((u16)15000)        /* PWMն��Ƶ�� */

/* �������PWM ���ڼ�����ֵ */
#define PWM_PERIOD                     ((u16) (PWM_MCLK / (u32)(2 * PWM_FREQ *(PWM_PRSC+1))))

#define MCU_SYS_TIME                   (10.42)

#define DEADTIME_NS                    ((u16)1800)      //1500                        /* ����ʱ�� */
#define DEADTIME                       (u16)(((unsigned long long)PWM_MCLK * (unsigned long long)DEADTIME_NS)/1000000000uL)

/* -------------------------------- ϵͳ�����붨�� ------------------------------ */
#define SHORT_ERROR                    BIT0  /* ��·���� 1*/
#define LOW_VOL_ERROR                  BIT1  /* ��ѹ���� 2*/
#define HIG_VOL_ERROR                  BIT2  /* ��ѹ���� 4*/
#define BLOCK_ERROR                    BIT3  /* ��ת���� 8*/
#define DC_OFFSET_ERROR                BIT4  /* ֱ��ƫ�ù��� 16*/
#define MOS_OVER_ERROR                 BIT5  /* MOS���¹��� 32*/
#define MOS_LOW_ERROR                  BIT6  /* MOS���¹��� 64*/
#define BAT_OVER_ERROR                 BIT7  /* ��ع��¹��� 128*/
#define BAT_LOW_ERROR                  BIT8  /* ��ص��¹��� 256*/
#define OVER_LOAD_ERROR                BIT9  /* �������� 512*/
#define PHASE_DROP_ERROR               BIT10 /* ȱ����� 1024*/

/* ----------------------оƬ�ͺż�Ԥ����������----------------------------------- */
#define  CHIP_PART_NUMBER              LKS32MC074D         /* оƬ�ͺ�ѡ��ѡ����ȷ��Ӱ��оƬģ��ĳ�ʼ�� */
#define  P_HIGH__N_HIGH                0
#define  P_HIGH__N_LOW                 1

#if ((CHIP_PART_NUMBER == LKS32MC074D) || (CHIP_PART_NUMBER == LKS32MC074DO) ||(CHIP_PART_NUMBER == LKS32MC076D))
    #define  MCPWM_SWAP_SETTING        1                  /* оƬ����Ԥ������ã�оƬ������Ԥ�����˾����μ���*/
    #define  PRE_DRIVER_POLARITY       P_HIGH__N_HIGH     /* Ԥ��Ԥ���������� �Ϲܸߵ�ƽ��Ч���¹ܸߵ�ƽ��Ч */
	  #define  DRIVER_POLARITY           0x0000             // ȡMCPWM_IO1��MCPWIO23��������CHxN��CHxP�ļ��Ե�����
#else
    #define  MCPWM_SWAP_SETTING        0                  /* оƬ����Ԥ������ã�оƬ������Ԥ�����˾����μ���*/
    #define  PRE_DRIVER_POLARITY       P_HIGH__N_LOW      /* Ԥ��Ԥ���������� �Ϲܸߵ�ƽ��Ч���¹ܵ͵�ƽ��Ч */
	  #define  DRIVER_POLARITY           0x0101             // ȡMCPWM_IO1��MCPWIO23��������CHxN��CHxP�ļ��Ե�����		
#endif

/* --------------------------------ADCͨ���Ŷ���------------------------------ */
#define ADC0_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC0_CHANNEL_OPA1              ADC_CHANNEL_1
#define ADC0_CHANNEL_OPA2              ADC_CHANNEL_2
#define ADC0_CHANNEL_OPA3              ADC_CHANNEL_3

#define ADC1_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC1_CHANNEL_OPA1              ADC_CHANNEL_1
#define ADC1_CHANNEL_OPA2              ADC_CHANNEL_2
#define ADC1_CHANNEL_OPA3              ADC_CHANNEL_3
/* ADC���������ʱ��Ӳ����� ------------------------------------------------ */
/* Porting Application Notice ע��������� ------------------------------------ */
#define BEMF_CH_A                      ADC_CHANNEL_13        /* A�෴�綯�Ʋ���ͨ�� */
#define BEMF_CH_B                      ADC_CHANNEL_12        /* B�෴�綯�Ʋ���ͨ�� */
#define BEMF_CH_C                      ADC_CHANNEL_11        /* C�෴�綯�Ʋ���ͨ�� */

#define ADC_BUS_CUR_CHANNEL            ADC1_CHANNEL_OPA3     /* ĸ��ƽ����������ͨ�� */
#define ADC_PEAK_CUR_CHANNEL           ADC1_CHANNEL_OPA3     /* ĸ�߷�ֵ��������ͨ�� */

#define ADC_BUS_VOL_CHANNEL            ADC_CHANNEL_8        /* ĸ�ߵ�ѹ */
#define ADC_SPEED_CHANNEL              ADC_CHANNEL_7         /* �ٶ��ź� */

#define ADC_MOS_TEMP_CHANNEL           ADC_CHANNEL_3         /* MOS�¶� */
#define ADC_BAT_TEMP_CHANNEL           ADC_CHANNEL_10        /* ����¶� */

#define ADC_OPA_OUT_CHANNEL            ADC_CHANNEL_11         /* �˷�������� */

#define ADC0_STATE_RESET()             {ADC0_CFG |= BIT11;}   /* ADC1 ״̬����λ,���Լ��������ȷ��ADC����״̬ */
#define ADC0_SOFTWARE_TRIG_ONLY()     {ADC0_TRIG = 0;}      /* ADC����Ϊ��������� */

#define ADC1_STATE_RESET()             {ADC1_CFG |= BIT11;}   /* ADC1 ״̬����λ,���Լ��������ȷ��ADC����״̬ */
#define ADC1_SOFTWARE_TRIG_ONLY()      {ADC1_TRIG = 0;}      /* ADC����Ϊ��������� */
/* ---------------------------CMP�Ƚ���������ض��� --------------------------- */
#define CMP0_SELN_SET                  CMP0_SELN_HALL0_MID       /* �Ƚ���0����ѡ��HALL MID */
#define CMP0_SELP_SET                  CMP0_SELP_IP1       /* �Ƚ���0����ѡ��IP0 */

#define CMP1_SELN_SET                  CMP_SELN_DAC0            /* �Ƚ���1����ѡ��DAC */
#define CMP1_SELP_SET                  CMP1_SELP_OPA3_OUT       /* �Ƚ���1����ѡ���˷�1������ */

#define CMP2_SELN_SET                  CMP_SELN_IN       /* �Ƚ���0����ѡ��HALL MID */
#define CMP2_SELP_SET                  CMP2_SELP_IP0       /* �Ƚ���0����ѡ��IP0 */

#define DAC0_OUT_SET                   DISABLE             /* DAC0���ʹ�� */
#define DAC1_OUT_SET                   DISABLE             /* DAC1���ʹ�� */

#define CMP_IP_A                       CMP0_SELP_IP3        /* A�෴���Ƶ�ѹ�Ƚ���ͨ�� */
#define CMP_IP_B                       CMP0_SELP_IP2        /* B�෴���Ƶ�ѹ�Ƚ���ͨ�� */
#define CMP_IP_C                       CMP0_SELP_IP1        /* C�෴���Ƶ�ѹ�Ƚ���ͨ�� */

#define CMP0_IE_ENABLE()              {CMP_IE |= BIT0;}   /* �Ƚ���0�ر�ʹ�� */
#define CMP0_IE_DISABLE()             {CMP_IE &= ~BIT0;}  /* �Ƚ���0�ر�ʹ�� */
#define CMP0_IE_STATE()               (CMP_IE & BIT0)     /* �жϵ�ǰ�Ƚ���0״̬ */

#define CMP0_OUT_LEVEL()              (CMP_DATA & BIT0)   /* �Ƚ���0�����ƽԭʼ�ź�״̬ */

#define CMP0_POL_STATE()              (CMP_CFG & BIT0)    /* ��ǰ�Ƚ���0�������ѡ�� */ 

/* ------------------------------������ѡ��------------------------------------ */
#define RUN_IN_RAM_FUNC  __attribute__ ((used, section ("ram3functions")))

/* ------------------------------Ӳ��IO���ƽӿ�-------------------------------- */
#define LED_DELAY_TIME                 60000       /* �ɰ������ʱ�ػ�ʱ�� */ 

#define LOCK_POWER_ON()                {GPIO2_PDO |= BIT6;}         
#define LOCK_POWER_OFF()               {GPIO2_PDO &= ~BIT6;}

#define KEY_DIRECT_CTRL                GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_10)   //����ת�л�����,��ȡP2.10�����ƽ


#define LED_OFF_TIME                   500         /*LED������˸ʱ������*/
#define LED_ON_TIME                    500
#define LED_PERIOD_DELAY               1000        /*LED������˸������ʱʱ������*/

#define LED_ON()                       {GPIO0_PDO &= ~BIT15;}
#define LED_OFF()                      {GPIO0_PDO |= BIT15;}

#define KEYIN_FILTER_TIME              30 /* ���������˲�ʱ�� */

#define SWITCH_INPUT_MASK              (GPIO2_PDI & BIT13)
#define DIRECT_INPUT_MASK              (GPIO2_PDI & BIT10)

#define SWITCH_INPUT                   (BIT0)  /* ���� */
#define DIRECT_INPUT                   (BIT1)  /* ���� */

typedef struct
{
    s32 yk_1;
    u16 coef;
} stru_RC_Def;


typedef enum
{
    IDLE       = 0,   /* ����״̬ */
    INIT       = 1,   /* ��ʼ��״̬ */
    CHARGE     = 2,   /* ���״̬ */
    ALIGN      = 3,   /* Ԥ��λ */
    OPEN_RUN   = 4,   /* ��������״̬ */
    ONFLY_START  = 5,   /* ˳����� */
    POS_SEEK   = 6,   /* ��ʼλ�ü�� */
    RUN        = 7,   /* ��������״̬ */
    STOP       = 8,   /* ֹͣ״̬ */
    BRAKE      = 9,   /* ɲ��״̬ */
    WAIT       = 10,  /* �ȴ�״̬ */
    FAULT      = 11,  /* ����״̬ */
    SEEK_POS   = 12,  /* λ�ü��״̬ */
} enum_SystStatus;


typedef struct
{
	u8 oldCommunicateStep;/* �ϴλ����Ƕ�λ�� */
	u8 communicate_cnt;	  
	u32 Provid_time;	    /* �ٶȼ�������ʱ��  */	
	u32 Elect_Speed;      /* ��ת�� */
	u32 Machine_Speed;    /* ��еת�� */	
} stru_Speedgetting_Ctr;

extern stru_Speedgetting_Ctr Speedgetting; /* �ٶȻ�ȡ�ṹ�� */


typedef struct
{
	u8 Last_key_status;     /* �ϴΰ���״̬ */
	u8 DirChange_Flag;	    /* ����ת�л���־ */
	u8 MotorRun_Dir;	      /* ����������з��� */	
	u32 DirChange_Cnt;      /* ����ת�л���ʱʱ�� */

} stru_DirChange_Ctr;	     

extern stru_DirChange_Ctr DirChange_Ctr; /* ����ת�л��ṹ�� */

typedef struct
{
	u32 RecoverCnt;         /* ��ת�ָ�ʱ������� */
    u32 RecoverTime;	      /* ��ת�ָ����� */

} stru_Fault_Stall_Rev;	     

extern stru_Fault_Stall_Rev Fault_Stall_Rev; /* ��ת�ָ��ṹ�� */





typedef struct
{
    volatile u16 nSys_TimerPWM;                  /* PWM���ڼ���Cnt */ 
    u8 bMotorDirtionCtrl;                        /* �������Ƶĵ�����з��� */
    u8 bMC_RunFlg;                               /* �������ָ�� */
    enum_SystStatus eSysState;                   /* ��ǰ�������״̬�� */
    u16 nSetTimeLeftCnt;                         /* ״̬���ȴ�ʱ������� */

    stru_RC_Def struBusCurr_RC;                  /* ĸ�ߵ���RC�˲��ṹ��  */
  
    u16 nSpeed_ADC;                              /* �ٶȿ���ADCֵ */
    s16 nBUS_Vol_ADC;                            /* ĸ�ߵ�ѹADCֵ */
  
    s16 nPower;                                  /* ��ѹ����ֵ(ռ�ձ�Ŀ��ֵ) */
  
    s16 nRequestPower;                           /* ʵ�ʵ�ѹ����ֵ(ʵ��ռ�ձ�) */
  
    s16 nBLDC_PWM_value;                         /* PWM�������ֵ */
  
    s16 nBusCurrLimit_Value;                     /* �������ƹ������ֵ */
  
    u8 nWork_mode;                               /* ��ǰ����ģʽ��ADC or �Ƚ��� */
	  
    u16 nNTC_Vol_ADC;                            /* NTC�¶�ADCֵ */
		
	u32 sys_error_flg;                           /* ϵͳ����״̬��־ */
		
	u8 get_offset_flg;                           /* offset�����־ */
		
	u16 MotorBlockCnt;                           /* ��תʱ����� */

  	u8 Power_on_flg;                            /* ��������־��1��������0�ػ� */
		
    u16 BAT_NTC_adc;                            /* ����¶Ȳ���ADC */
		
	u16 NVR_OPAx_Vol;                            /* ��ģ��ѹֵ */		
		
} stru_BLDC_CtrProcDef;


extern stru_BLDC_CtrProcDef mBLDC_CtrProc;           /* BLDC���̿��ƽṹ�� */



#endif  /* __HARDWARE_CONFIG_H_ */

 
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
 
 
