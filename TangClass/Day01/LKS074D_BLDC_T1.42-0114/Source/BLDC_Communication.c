/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� BLDC_Communication.c
 * �ļ���ʶ��
 * ����ժҪ�� ���������غ���
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
 *******************************************************************************/
#include "hardware_config.h"
#include "Global_Variable.h"
#include "MC_Parameter.h"

uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

volatile u32 CMP_delay,CMP_speed,SYSTICK_flg;
void BLDC_Communication(void)
{
    CMP_IE &= ~BIT0;
    MCPWM0_PRT = 0x0000DEAD;
    SYS_WR_PROTECT = 0x7a83;
    HALL0_CNT = 0; 

		if(Speedgetting.oldCommunicateStep != BLDC_SensorlessCtr.communicateStep)
		{
	    if(Speedgetting.communicate_cnt < 5)
		  {
		    Speedgetting.communicate_cnt++;
		  }
		  else
		  {			
				Speedgetting.Provid_time = UTIMER2_CNT;
				Speedgetting.communicate_cnt = 0;
				UTIMER2_CNT = 0;
			    Invers_GPIO(GPIO0,GPIO_Pin_14);  //FG�����ÿ���6�λ���Ϊһ�����ڣ����ת��=(IO���������Ƶ��*60)/2              
			}
		}	
		
		BLDC_SensorlessCtr.oldCommunicateStep = BLDC_SensorlessCtr.communicateStep;	
	

    switch (BLDC_SensorlessCtr.communicateStep) {
    case 1: {
        // A�����գ�B��PWM C��ON ������½��ع����¼�
        // A float | B PWM | C ON

        if(BLDC_SensorlessCtr.motorDirect == 0)
        {
            MCPWM0_UPDATE = 0;
            MCPWM0_TH20 = 0;
            MCPWM0_TH21 = 0;
            MCPWM0_UPDATE = 0xff;
            
            MCPWM0_IO01 = DRIVER_POLARITY | 0x1c;
            MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;
            while(HALL0_CNT < RE_COMM_CNT) {;}
        }



        MCPWM0_IO01 = DRIVER_POLARITY | (0x00c);
				
        if((BLDC_SensorlessCtr.lowSpeedFlg) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
        {
            MCPWM0_IO23 = DRIVER_POLARITY;
        }
        else
        {
            MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;                        
        }
				
        SYS_AFE_REG3 = (CMP0_SELN_SET << 2) | (CMP1_SELN_SET << 4) | (CMP_IP_A << 8) | (CMP1_SELP_SET << 12)| CMP2_SELN_SET | (DAC0_OUT_SET << 11) | (DAC1_OUT_SET << 15);
        BLDC_SensorlessCtr.BEMF_edgeFlg = BLDC_SensorlessCtr.BEMF_edgeSetting;
			
        BLDC_SensorlessCtr.bemfDetectFlg = 1;
		BLDC_SensorlessCtr.PWMDetectFlg = 2;
        BLDC_SensorlessCtr.LOWDetectFlg = 3;						
        BLDC_SensorlessCtr.insPhaseFlg = 3;


        break;
    }
    case 2: {
        // A��ON��B��PWM C������ ����������ع����¼�
        // A ON | B PWM | C float

        if(BLDC_SensorlessCtr.motorDirect)
        {
            MCPWM0_UPDATE = 0;
            MCPWM0_TH00 = 0;
            MCPWM0_TH01 = 0;
            MCPWM0_UPDATE = 0xff;

            MCPWM0_IO01 = DRIVER_POLARITY | 0x1c;
            MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;
            while(HALL0_CNT < RE_COMM_CNT) {;}
        }



        if((BLDC_SensorlessCtr.lowSpeedFlg) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
        {
            MCPWM0_IO01 = DRIVER_POLARITY;
        }
        else
        {
            MCPWM0_IO01 = DRIVER_POLARITY | 0x1c;

        }

        SYS_AFE_REG3 = (CMP0_SELN_SET << 2) | (CMP1_SELN_SET << 4) | (CMP_IP_C << 8) | (CMP1_SELP_SET << 12)| CMP2_SELN_SET | (DAC0_OUT_SET << 11) | (DAC1_OUT_SET << 15);
        MCPWM0_IO23 = DRIVER_POLARITY | (0x0c);
        BLDC_SensorlessCtr.BEMF_edgeFlg = !BLDC_SensorlessCtr.BEMF_edgeSetting;

        BLDC_SensorlessCtr.bemfDetectFlg = 3;
		BLDC_SensorlessCtr.PWMDetectFlg = 2;
        BLDC_SensorlessCtr.LOWDetectFlg = 1;		
				
        BLDC_SensorlessCtr.insPhaseFlg = 1;


        break;
    }
    case 3: {
        // A��ON��B������ C��PWM ������½��ع����¼�
        // A ON | B float | C PWM

        if(BLDC_SensorlessCtr.motorDirect == 0)
        {
            MCPWM0_UPDATE = 0;
            MCPWM0_TH00 = 0;
            MCPWM0_TH01 = 0;
            MCPWM0_UPDATE = 0xff;

            MCPWM0_IO01 = DRIVER_POLARITY | 0x1c1c;
            MCPWM0_IO23 = DRIVER_POLARITY;
            while(HALL0_CNT < RE_COMM_CNT) {;}
        }



        if((BLDC_SensorlessCtr.lowSpeedFlg) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
        {
            MCPWM0_IO01 = DRIVER_POLARITY | (0x0c00);
        }
        else
        {
            MCPWM0_IO01 = DRIVER_POLARITY | (0x0c1c);

        }
        SYS_AFE_REG3 = (CMP0_SELN_SET << 2) | (CMP1_SELN_SET << 4) | (CMP_IP_B << 8) | (CMP1_SELP_SET << 12)| CMP2_SELN_SET | (DAC0_OUT_SET << 11) | (DAC1_OUT_SET << 15);
        MCPWM0_IO23 = DRIVER_POLARITY | 0x0;
        BLDC_SensorlessCtr.BEMF_edgeFlg = BLDC_SensorlessCtr.BEMF_edgeSetting;
				
        BLDC_SensorlessCtr.bemfDetectFlg = 2;
		BLDC_SensorlessCtr.PWMDetectFlg = 3;
        BLDC_SensorlessCtr.LOWDetectFlg = 1;				
        BLDC_SensorlessCtr.insPhaseFlg = 1;


        break;
    }
    case 4: {
        // A�����գ�B��ON C��PWM  ����������ع����¼�
        // A float | B ON | C PWM
        if(BLDC_SensorlessCtr.motorDirect)
        {
            MCPWM0_UPDATE = 0;
            MCPWM0_TH10 = 0;
            MCPWM0_TH11 = 0;
            MCPWM0_UPDATE = 0xff;

            MCPWM0_IO01 = DRIVER_POLARITY | (0x1c1c);
            MCPWM0_IO23 = DRIVER_POLARITY | 0x0;
            while(HALL0_CNT < RE_COMM_CNT) {;}
        }


        MCPWM0_IO23 = DRIVER_POLARITY | 0x0;
        if((BLDC_SensorlessCtr.lowSpeedFlg) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
        {
            MCPWM0_IO01 = DRIVER_POLARITY | (0x000c);
        }
        else
        {
            MCPWM0_IO01 = DRIVER_POLARITY | (0x1c0c);
        }

        SYS_AFE_REG3 = (CMP0_SELN_SET << 2) | (CMP1_SELN_SET << 4) | (CMP_IP_A << 8) | (CMP1_SELP_SET << 12)| CMP2_SELN_SET | (DAC0_OUT_SET << 11) | (DAC1_OUT_SET << 15);
        BLDC_SensorlessCtr.BEMF_edgeFlg = !BLDC_SensorlessCtr.BEMF_edgeSetting;

        BLDC_SensorlessCtr.bemfDetectFlg = 1;
		BLDC_SensorlessCtr.PWMDetectFlg = 3;
        BLDC_SensorlessCtr.LOWDetectFlg = 2;									
        BLDC_SensorlessCtr.insPhaseFlg = 2;

        break;
    }
    case 5: {
        // A��PWM��B��ON C������  ������½��ع����¼�
        // A PWM | B on | C float
        if(BLDC_SensorlessCtr.motorDirect == 0)
        {
            MCPWM0_UPDATE = 0;
            MCPWM0_TH10 = 0;
            MCPWM0_TH11 = 0;
            MCPWM0_UPDATE = 0xff;


            MCPWM0_IO01 = DRIVER_POLARITY | 0x1c00;
            MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;

            while(HALL0_CNT < RE_COMM_CNT) {;}
        }


        MCPWM0_IO23 = DRIVER_POLARITY | (0x0c);
        if((BLDC_SensorlessCtr.lowSpeedFlg) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
        {
            MCPWM0_IO01 = DRIVER_POLARITY;
        }
        else
        {
            MCPWM0_IO01 = DRIVER_POLARITY | 0x1c00;

        }

        SYS_AFE_REG3 = (CMP0_SELN_SET << 2) | (CMP1_SELN_SET << 4) | (CMP_IP_C << 8) | (CMP1_SELP_SET << 12)| CMP2_SELN_SET | (DAC0_OUT_SET << 11) | (DAC1_OUT_SET << 15);

        BLDC_SensorlessCtr.BEMF_edgeFlg = BLDC_SensorlessCtr.BEMF_edgeSetting;

        BLDC_SensorlessCtr.bemfDetectFlg = 3;
		BLDC_SensorlessCtr.PWMDetectFlg = 1;
        BLDC_SensorlessCtr.LOWDetectFlg = 2;						
				
        BLDC_SensorlessCtr.insPhaseFlg = 2;

        break;
    }
    case 6: {
        // A��PWM��B������ C ON����������ع����¼�
        // A pwm | B float | C ON

        if(BLDC_SensorlessCtr.motorDirect)
        {
            MCPWM0_UPDATE = 0;
            MCPWM0_TH20 = 0;
            MCPWM0_TH21 = 0;
            MCPWM0_UPDATE = 0xff;

            MCPWM0_IO01 = DRIVER_POLARITY | (0x1c00);
            MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;

            while(HALL0_CNT < RE_COMM_CNT) {;}
        }

        MCPWM0_IO01 = DRIVER_POLARITY | (0x0c00);
				
        if((BLDC_SensorlessCtr.lowSpeedFlg) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
        {
            MCPWM0_IO23 = DRIVER_POLARITY;
        }
        else
        {
            MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;

        }
        SYS_AFE_REG3 = (CMP0_SELN_SET << 2) | (CMP1_SELN_SET << 4) | (CMP_IP_B << 8) | (CMP1_SELP_SET << 12) | CMP2_SELN_SET | (DAC0_OUT_SET << 11) | (DAC1_OUT_SET << 15);

        BLDC_SensorlessCtr.BEMF_edgeFlg = !BLDC_SensorlessCtr.BEMF_edgeSetting;
				
        BLDC_SensorlessCtr.bemfDetectFlg = 2;
		BLDC_SensorlessCtr.PWMDetectFlg = 1;
        BLDC_SensorlessCtr.LOWDetectFlg = 3;	
				
		BLDC_SensorlessCtr.insPhaseFlg = 3;

        break;
    }            
    }             



    if(BLDC_SensorlessCtr.BEMF_edgeFlg)
    {
        CMP_CFG |= BIT0;
    }
    else
    {
        CMP_CFG &= (~BIT0);
    }

                     

    HALL0_CNT = 0;
		
	SYS_WR_PROTECT = 0;
    MCPWM0_PRT = 0x0000ABCD;

   if(mBLDC_CtrProc.nWork_mode == BLDC_MODE_ADC )
    {

        BLDC_SensorlessCtr.state = 0;
        BLDC_SensorlessCtr.blankEndTimeValue = 0;

            
    }
    else
    {
			  CMP_delay = BLDC_SensorlessCtr.SpeedTimerCnt >> 1;
	
			  SYSTICK_flg = 1;			
				SysTick->CTRL = 0x0;
				SysTick->VAL = 0;
				SysTick->LOAD = 0;
				SysTick->LOAD = CMP_delay;
				SysTick->VAL = 0;
				SysTick->CTRL = 0x07;

    }


    if(BLDC_SensorlessCtr.sCommmStabCnt < 12)
    {
        BLDC_SensorlessCtr.sCommmStabCnt++;
    }

    BLDC_SensorlessCtr.focusCommCnt = 0;

    mBLDC_CtrProc.MotorBlockCnt = 0;
}




void BLDC_CommunicationOnly(void)
{
    CMP_IE &= ~BIT0;
    MCPWM0_PRT = 0x0000DEAD;

    switch (BLDC_SensorlessCtr.communicateStep) {
    case 1: {
        // A�����գ�B��PWM C��ON ������½��ع����¼�
        // A float | B PWM | C ON
        MCPWM0_IO01 = DRIVER_POLARITY | 0x000c;
        MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;

        BLDC_SensorlessCtr.insPhaseFlg = 3;		
        BLDC_SensorlessCtr.bemfDetectFlg = 1;
		BLDC_SensorlessCtr.PWMDetectFlg = 2;
        BLDC_SensorlessCtr.LOWDetectFlg = 3;

        break;
    }
    case 2: {
        // A��ON��B��PWM C������ ����������ع����¼�
        // A ON | B PWM | C float
        MCPWM0_IO01 = DRIVER_POLARITY | 0x001c;      
        MCPWM0_IO23 = DRIVER_POLARITY | 0x0c;

        BLDC_SensorlessCtr.insPhaseFlg = 1;
        BLDC_SensorlessCtr.bemfDetectFlg = 3;
		BLDC_SensorlessCtr.PWMDetectFlg = 2;
        BLDC_SensorlessCtr.LOWDetectFlg = 1;			

        break;
    }
    case 3: {
        // A��ON��B������ C��PWM ������½��ع����¼�
        // A ON | B float | C PWM
        MCPWM0_IO01 = DRIVER_POLARITY | 0x0c1c;
        MCPWM0_IO23 = DRIVER_POLARITY | 0x0;

        BLDC_SensorlessCtr.insPhaseFlg = 1;
        BLDC_SensorlessCtr.bemfDetectFlg = 2;
		BLDC_SensorlessCtr.PWMDetectFlg = 3;
        BLDC_SensorlessCtr.LOWDetectFlg = 1;

        break;
    }
    case 4: {
        // A�����գ�B��ON C��PWM  ����������ع����¼�
        // A float | B ON | C PWM
        MCPWM0_IO01 = DRIVER_POLARITY | 0x1c0c;
        MCPWM0_IO23 = DRIVER_POLARITY | 0x0;

        BLDC_SensorlessCtr.insPhaseFlg = 2;
        BLDC_SensorlessCtr.bemfDetectFlg = 1;
		BLDC_SensorlessCtr.PWMDetectFlg = 3;
        BLDC_SensorlessCtr.LOWDetectFlg = 2;			

        break;
    }
    case 5: {
        // A��PWM��B��ON C������  ������½��ع����¼�
        // A PWM | B on | C float
        MCPWM0_IO01 = DRIVER_POLARITY | 0x1c00;
        MCPWM0_IO23 = DRIVER_POLARITY | 0x0c;

        BLDC_SensorlessCtr.insPhaseFlg = 2;
        BLDC_SensorlessCtr.bemfDetectFlg = 3;
	    BLDC_SensorlessCtr.PWMDetectFlg = 1;
        BLDC_SensorlessCtr.LOWDetectFlg = 2;			

        break;
    }
    case 6: {
        // A��PWM��B������ C ON����������ع����¼�
        // A pwm | B float | C ON
        MCPWM0_IO01 = DRIVER_POLARITY | 0x0c00;
        MCPWM0_IO23 = DRIVER_POLARITY | 0x1c;

        BLDC_SensorlessCtr.insPhaseFlg = 3;
        BLDC_SensorlessCtr.bemfDetectFlg = 2;
		BLDC_SensorlessCtr.PWMDetectFlg = 1;
        BLDC_SensorlessCtr.LOWDetectFlg = 3;			

        break;
    }
    }
		
		MCPWM0_PRT = 0x0000ABCD;

}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
