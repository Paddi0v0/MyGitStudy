/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� interrupt.c
 * �ļ���ʶ��
 * ����ժҪ�� �жϷ�������ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet
 * ������ڣ� 2020��8��5��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�2020��8��5��
 * �� �� �ţ�V 1.0
 * �� �� �ˣ�Howlet
 * �޸����ݣ�����
 *
 *******************************************************************************/
#include "hardware_init.h"
#include "hardware_config.h"
#include "Global_Variable.h"
#include "main.h"

void PWM_Duty_Setting(void);
void bus_current_limPro(void);
/*******************************************************************************
 �������ƣ�    void ADC0_IRQHandler(void)
 ����������    ADC0�жϴ�����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void ADC0_IRQHandler(void)
{
    ADC0_IF = BIT1 | BIT0;
	
	mBLDC_CtrProc.nSys_TimerPWM++;
	
	if(ADC0_DAT0 & BIT15)
	{/*ĸ�ߵ�ѹ*/
	  mBLDC_CtrProc.nBUS_Vol_ADC = 0;   //����ɳ��ĸ�ֵ��ѹ
	}
    else
	{
      mBLDC_CtrProc.nBUS_Vol_ADC = (mBLDC_CtrProc.nBUS_Vol_ADC + ADC0_DAT0) >> 1;		
	}	

	if(ADC0_DAT2 & BIT15)
	{/*�������*/
	   mBLDC_CtrProc.nSpeed_ADC = 0;   //����ɳ��ĸ�ֵ��ѹ
	}
	else
	{
	   mBLDC_CtrProc.nSpeed_ADC = (ADC0_DAT2 >> 4);	
	}		

}

void ADC1_IRQHandler(void)
{
    ADC1_IF = BIT1 | BIT0;
		
    getBemfValue();		           /* ���綯��&ĸ�ߵ�����ȡ */	
	
    BLDC_CommProcess();           /* ������д���  */ 

//	bus_current_limPro();         /* ������� */
		
	PWM_Duty_Setting();              /* PWMռ�ձȸ��� */	
		
}
/*******************************************************************************
 �������ƣ�    void CMP_IRQHandler(void)
 ����������    �Ƚ����жϴ�����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void CMP_IRQHandler(void)
{
    CMP_IF = BIT0 | BIT1;
	BLDC_CMP_ModeControl();
}
/*******************************************************************************
 �������ƣ�    void SysTick_Handler(void)
 ����������    ϵͳ�δ�ʱ�ж�
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void SysTick_Handler(void)
{
   BLDC_DelayCommunication();
}
/*******************************************************************************
 �������ƣ�    void MCPWM0_IRQHandler(void)
 ����������    MCPWM�жϴ�����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 2023/3/9      V1.0           Zhujie             �޸�
 *******************************************************************************/
void MCPWM0_IRQHandler(void)
{
  if(MCPWM0_EIF & BIT5)
  {
	 StopMotorImmdly();
     mBLDC_CtrProc.sys_error_flg |= SHORT_ERROR;
     MCPWM0_EIF = BIT5;
  }  
	
}
/*******************************************************************************
 �������ƣ�    void TIMER0_IRQHandler(void)
 ����������    TIMER0�жϴ�����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void TIMER0_IRQHandler(void)
{
    /* ʱ��500us */
    UTIMER0_IF = BIT2;
    /* ʱ��1ms */
    struTaskScheduler.bTimeCnt1ms++;
    struTaskScheduler.nTimeCnt10ms ++;
    struTaskScheduler.nTimeCnt100ms ++;
    struTaskScheduler.nTimeCnt500ms++;

}
/*******************************************************************************
 �������ƣ�    void HALL_IRQHandler(void)
 ����������    HALL�жϴ�����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void HALL0_IRQHandler(void)
{
//    HALL->INFO = HALL->INFO;    // ���־λ
}
/*******************************************************************************
 �������ƣ�    void TIMER1_IRQHandler(void)
 ����������    TIMER1�жϴ�����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void TIMER1_IRQHandler(void)
{

}

void TIMER2_IRQHandler(void)
{

}

void TIMER3_IRQHandler(void)
{
    
}

void ENCODER0_IRQHandler(void)
{

}

void ENCODER1_IRQHandler(void)
{

}


void UART0_IRQHandler(void)
{

}

void UART1_IRQHandler(void)
{
  

}

void SleepTimer_IRQHandler(void)
{
    while(1);
}


void GPIO_IRQHandler(void)
{

}

void QEP0_IRQHandler(void)
{
}
void QEP1_IRQHandler(void)
{
}

void I2C0_IRQHandler(void)
{

}

void SPI0_IRQHandler(void)
{

}

void DSP0_IRQHandler(void)
{
}



void MCPWM1_IRQHandler(void)
{
}

void SIF0_IRQHandler  (void)
{
}
void WAKE_IRQHandler  (void)
{
}
void SW_IRQHandler    (void)
{
}
void PWRDN_IRQHandler (void)
{
}
void CL0_IRQHandler   (void)
{
}
/*******************************************************************************
 �������ƣ�    void HardFault_Handler(void)
 ����������    Ӳ�������жϺ���
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
volatile u32 hardFault;
void HardFault_Handler(void)
{
	StopMotorImmdly();
    hardFault++;
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */


