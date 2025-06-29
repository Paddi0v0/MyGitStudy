/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� System_init.c
 * �ļ���ʶ��
 * ����ժҪ�� ϵͳ��ʼ������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� ������
 * ������ڣ� 2023��6��8��
 *******************************************************************************/
#include "hardware_config.h"
#include "function_config.h"
#include "MC_parameter.h"

void CurrentOffsetCalibration(void);
void BLDC_Init(void);
void key_in_proc(void);
void DC_offset_protect(void);

void DebugPWM_OutputFunction(void);
void Short_DAC_Setting(void);
void Multiplex_SWD(void);

volatile u16 ADC_VOL_test;
volatile u16 OPA_OFFSET_VOL_test;
volatile u16 test_OPA_DAC;
volatile u16 test_short_DAC,test_sys_afe_dac;
/*******************************************************************************
 �������ƣ�    sys_init(void)
 ����������    ϵͳ������ʼ��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
void sys_init(void)
{	
//	u8 i;
	
    while(mBLDC_CtrProc.nSys_TimerPWM < 1000){;} /* ��ʱ150ms */
		
//	  Multiplex_SWD(); /* �ر�ע�⣬�˺��������������س���ʱ��������Ÿר������������ */
	mBLDC_CtrProc.sys_error_flg = 0;
	BLDC_SensorlessCtr.motorDirect = 1;        //������з������  CW/CCW
		
    CurrentOffsetCalibration();
	  DC_offset_protect();
					
//		Short_DAC_Setting();
 
    BLDC_Init();
    InitPI();
	  
//	for(i=0;i<100;i++)
//	{
//	  key_in_proc();
//	}
	
#if (EABS_FUNCTION	== ENABLE_FUNCTION)
   BLDC_SensorlessCtr.Eabs_Founction_Flg = 1;
#else	
   BLDC_SensorlessCtr.Eabs_Founction_Flg = 0;
#endif

#if(EABS_HARD	== ENABLE_FUNCTION)
   BLDC_SensorlessCtr.Eabs_Hard_Flg	= 1;
#else	
   BLDC_SensorlessCtr.Eabs_Hard_Flg	= 0; //��ɲ��ѹ�ϴ��Ƽ���
#endif
	
#if (DEBUG_PWM_OUTPUT == TEST_ON)
    DebugPWM_OutputFunction(); /* ���Ե�ʱ�����25%��PWM���� */
#endif
  
}

/*******************************************************************************
 �������ƣ�    CurrentOffsetCalibration(void)
 ����������    ��ʼ��ֱ��ƫ�ö�ȡ
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
void CurrentOffsetCalibration(void)
{
    volatile u32 t_dlay;
    volatile u16 t_cnt;
    volatile s32 t_offset1, t_offset2, t_offset3,t_offset4,t_offset5;

    __disable_irq();

    ADC0_SOFTWARE_TRIG_ONLY();
    ADC0_STATE_RESET();
	
    ADC1_SOFTWARE_TRIG_ONLY();
    ADC1_STATE_RESET();	

    MCPWM0_TH00 = 0;
    MCPWM0_TH01 = 0;

    MCPWM0_TH10 = 0;
    MCPWM0_TH11 = 0;

    MCPWM0_TH20 = 0;
    MCPWM0_TH21 = 0;
  
    for (t_dlay = 0; t_dlay < 0xffff; t_dlay++)  
        ; //��ʱ680us
    PWMOutputs(ENABLE);
		
    for (t_dlay = 0; t_dlay < 0x2ffff; t_dlay++)
        ;//��ʱ2ms

    t_offset1 = 0;
    t_offset2 = 0;
    t_offset3 = 0;
    t_offset4 = 0;
	t_offset5 = 0;

    ADC1_IF = 0x1f;

    ADC1_SWT = 0x00005AA5;

    for(t_cnt = 0; t_cnt < CALIB_SAMPLES; t_cnt++)
    {
        while((ADC1_IF & BIT0) == 0)
		{
		  ;
		} 
				
        ADC1_IF = BIT1 | BIT0;
        t_offset1 += (s16)((ADC1_DAT0));
        t_offset2 += (s16)((ADC1_DAT1));
        t_offset3 += (s16)((ADC1_DAT2));
        t_offset4 += (s16)((ADC1_DAT3));

        /* Clear the ADC0 JEOC pending flag */
        ADC1_SWT = 0x00005AA5;
    }
	
//    ADC0_IF = 0x1f;

//    ADC0_SWT = 0x00005AA5;

//    for(t_cnt = 0; t_cnt < CALIB_SAMPLES; t_cnt++)
//    {
//        while((ADC0_IF & BIT0) == 0)
//		{
//		  ;
//		} 
//				
//        ADC0_IF = BIT1 | BIT0;
//        t_offset5 += (s16)((ADC0_DAT1));

//        /* Clear the ADC0 JEOC pending flag */
//        ADC0_SWT = 0x00005AA5;
//    }	
        
    PWMOutputs(DISABLE);
		
    BLDC_SensorlessCtr.PhaseA_offset = (s16)(t_offset1 >> 9);
    BLDC_SensorlessCtr.PhaseB_offset = (s16)(t_offset2 >> 9);
    BLDC_SensorlessCtr.PhaseC_offset = (s16)(t_offset3 >> 9);		
    BLDC_SensorlessCtr.PeakCurrOffset = (s16)(t_offset4 >> 9);	
//	BLDC_SensorlessCtr.OPAOUT_offset =  (s16)(t_offset5 >> 9);
		                      
    ADC_init();
    MCPWM_init();
    __enable_irq();

}
/*******************************************************************************
 �������ƣ�    void DC_offset_protect(void)
 ����������    ֱ��ƫ�ñ���
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
void DC_offset_protect(void)
{
  if((BLDC_SensorlessCtr.PeakCurrOffset  > OFFSET_THD) || (BLDC_SensorlessCtr.PeakCurrOffset  < -OFFSET_THD))
  {
     mBLDC_CtrProc.sys_error_flg |= DC_OFFSET_ERROR;
  }	
}
/*******************************************************************************
 �������ƣ�    void Short_DAC_Setting(void)
 ����������    Ӳ��������OPA_OUT��ʱ����ֵDAC���ñ���
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
volatile u16 OPA_base_DAC,DAC_Short_Value_1,Short_set_vol,Short_set_DAC;
void Short_DAC_Setting(void)
{
	
	 BLDC_SensorlessCtr.OPA_OUT_REF = (BLDC_SensorlessCtr.OPAOUT_offset * 36000)/32767;  //��λ��mv
		
	 OPA_base_DAC = (BLDC_SensorlessCtr.OPA_OUT_REF * 4096)/48500;

	 Short_set_vol = SHORT_CURRENT_VOL;
	
	 Short_set_DAC = SHORT_CURRENT_VOL /2 * 4096/48500;
	
     DAC_Short_Value_1	= OPA_base_DAC + Short_set_DAC;
	
	 DAC_OutputValue(DAC_Channel_0,DAC_Short_Value_1);
	 

}
/*******************************************************************************
 �������ƣ�    void Multiplex_SWD(void)
 ����������    SWD����,��SWD��IO����ʱһ������һ�ϵ�Ϳ�����Ҫ����һ����ʱ������ڲ����ó���رո��ã���ֹ���ز��˳���
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
void Multiplex_SWD(void)
{			
	SYS_PROTECT = 0x7a83;	
	SYS_IO_CFG |= BIT6;         /* SWD����������GPIO�� */	
	
//	GPIO2_PIE &= ~(BIT14 | BIT15);
//	GPIO2_POE &= ~(BIT14 | BIT15);	
//	GPIO2_PUE &= ~(BIT14 | BIT15);
	
	SYS_PROTECT = 0;
}

/*******************************************************************************
 �������ƣ�    void DebugPWM_OutputFunction(void)
 ����������    PWM������ܵ���   ���25%ռ�ձ�
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
void DebugPWM_OutputFunction(void)
{
	
    MCPWM0_PRT = 0x0000DEAD;           
	  MCPWM0_IO01 = DRIVER_POLARITY | 0x0000;
    MCPWM0_IO23 = DRIVER_POLARITY | 0x00;	
	
    MCPWM0_TH00 = (u16)(-PWM_PERIOD >> 2);
    MCPWM0_TH01 = (PWM_PERIOD >> 2);
    MCPWM0_TH10 = (u16)(-PWM_PERIOD >> 2);
    MCPWM0_TH11 = (PWM_PERIOD >> 2);
    MCPWM0_TH20 = (u16)(-PWM_PERIOD >> 2);
    MCPWM0_TH21 = (PWM_PERIOD >> 2);

    PWMOutputs(ENABLE);
    while(1)
    {
    }
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
