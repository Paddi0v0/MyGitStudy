/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： BLDC_Communication.c
 * 文件标识：
 * 内容摘要： 换相控制相关函数
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
			    Invers_GPIO(GPIO0,GPIO_Pin_14);  //FG输出，每完成6次换相为一个周期，输出转速=(IO口输出方波频率*60)/2              
			}
		}	
		
		BLDC_SensorlessCtr.oldCommunicateStep = BLDC_SensorlessCtr.communicateStep;	
	

    switch (BLDC_SensorlessCtr.communicateStep) {
    case 1: {
        // A相悬空，B相PWM C相ON ；检测下降沿过零事件
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
        // A相ON，B相PWM C相悬空 ；检测上升沿过零事件
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
        // A相ON，B相悬空 C相PWM ；检测下降沿过零事件
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
        // A相悬空，B相ON C相PWM  ；检测上升沿过零事件
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
        // A相PWM，B相ON C相悬空  ；检测下降沿过零事件
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
        // A相PWM，B相悬空 C ON；检测上升沿过零事件
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
        // A相悬空，B相PWM C相ON ；检测下降沿过零事件
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
        // A相ON，B相PWM C相悬空 ；检测上升沿过零事件
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
        // A相ON，B相悬空 C相PWM ；检测下降沿过零事件
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
        // A相悬空，B相ON C相PWM  ；检测上升沿过零事件
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
        // A相PWM，B相ON C相悬空  ；检测下降沿过零事件
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
        // A相PWM，B相悬空 C ON；检测上升沿过零事件
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
