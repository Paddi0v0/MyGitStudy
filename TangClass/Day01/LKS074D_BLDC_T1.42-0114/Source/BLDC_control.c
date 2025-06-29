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

#include "hardware_config.h"
#include "Global_Variable.h"
#include "BLDC_Control.h"
#include "MC_Parameter.h"
#include "hardware_init.h"
#include "SEGGER_RTT.h"

void bldc_comm_process(u8 flg);

//#if (RTT_FUNCTION == FUNCTION_ON)
struct {
    s16 data0;
    s16 data1;
//    s16 data2;
//    s16 data3;
} Rttstru;
//#endif

void StopMotorImmdly(void);
//void bus_current_protect(void);
//s16 lowPass_filter(stru_RC_Def *rc, s16 signal);
//void bldc_comm_process(u8 flg);
//void PWMOutputs(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state);
void ADC_CrossPointDetect(void);
//void calcNextComm_BefComm(u8 currentComm);
//void BLDC_CommunicationOnly(void);

void force_CommProcess(void)
{
    if(BLDC_SensorlessCtr.bankCommTime < 255)
    {
        BLDC_SensorlessCtr.bankCommTime++;
    }

    if(BLDC_SensorlessCtr.focusCommCnt < 1500)
    {
        BLDC_SensorlessCtr.focusCommCnt++;

    }
    else
    {
#ifndef BEMF_DBG_FUN
//        if(BLDC_SensorlessCtr.totalFocusCommCnt < 2)
//        {
//            BLDC_SensorlessCtr.totalFocusCommCnt ++;
//            bldc_comm_process(0);
//        }
//        else
//        {
//            StopMotorImmdly();
//            mBLDC_CtrProc.sys_error_flg |= BLOCK_ERROR;
//            BLDC_SensorlessCtr.totalFocusCommCnt = 0;
//        }
//				 
//		mBLDC_CtrProc.nBLDC_PWM_value = Limit_Output(mBLDC_CtrProc.nBLDC_PWM_value,0,PWM_PERIOD * 0.2);
#endif
        BLDC_SensorlessCtr.focusCommCnt = 0;
        BLDC_SensorlessCtr.bankCommTime = 200;
        BLDC_SensorlessCtr.lastCommTime = 200;
        return;
    }
}     

void getBemfValue(void)          
{
	  BLDC_SensorlessCtr.Phase_A_ADC = (s16)(ADC1_DAT0 - BLDC_SensorlessCtr.PhaseA_offset);    
	  BLDC_SensorlessCtr.Phase_B_ADC = (s16)(ADC1_DAT1 - BLDC_SensorlessCtr.PhaseB_offset);
	  BLDC_SensorlessCtr.Phase_C_ADC = (s16)(ADC1_DAT2 - BLDC_SensorlessCtr.PhaseC_offset);

		BLDC_SensorlessCtr.peakBusCurrent = (s16)(ADC1_DAT3 - BLDC_SensorlessCtr.PeakCurrOffset); //电流值读取   
	
	  if(BLDC_SensorlessCtr.bemfDetectFlg == 1)
		{//反电动势相
      BLDC_SensorlessCtr.BEMF_adcValue  = BLDC_SensorlessCtr.Phase_A_ADC;				
		}
		else if(BLDC_SensorlessCtr.bemfDetectFlg == 2)
		{
      BLDC_SensorlessCtr.BEMF_adcValue  = BLDC_SensorlessCtr.Phase_B_ADC;			
		}
		else if(BLDC_SensorlessCtr.bemfDetectFlg == 3)
		{
      BLDC_SensorlessCtr.BEMF_adcValue  = BLDC_SensorlessCtr.Phase_C_ADC;			
		}
	
	  if(BLDC_SensorlessCtr.PWMDetectFlg == 1)		
		{//PWM导通相
      BLDC_SensorlessCtr.PWM_adcValue = BLDC_SensorlessCtr.Phase_A_ADC;			
		}
		else if(BLDC_SensorlessCtr.PWMDetectFlg == 2)		
		{
      BLDC_SensorlessCtr.PWM_adcValue = BLDC_SensorlessCtr.Phase_B_ADC;			
		}
		else if(BLDC_SensorlessCtr.PWMDetectFlg == 3)	
		{
      BLDC_SensorlessCtr.PWM_adcValue = BLDC_SensorlessCtr.Phase_C_ADC;				
		}
		
	  if(BLDC_SensorlessCtr.LOWDetectFlg == 1)		
		{//下桥常开相
      BLDC_SensorlessCtr.LOW_adcValue = BLDC_SensorlessCtr.Phase_A_ADC;			
		}
		else if(BLDC_SensorlessCtr.LOWDetectFlg == 2)		
		{
      BLDC_SensorlessCtr.LOW_adcValue = BLDC_SensorlessCtr.Phase_B_ADC;			
		}
		else if(BLDC_SensorlessCtr.LOWDetectFlg == 3)	
		{
      BLDC_SensorlessCtr.LOW_adcValue = BLDC_SensorlessCtr.Phase_C_ADC;				
		}
		
//        Rttstru.data0 = (BLDC_SensorlessCtr.Phase_A_ADC);   
//        Rttstru.data1 = (BLDC_SensorlessCtr.Phase_B_ADC);    
//	    Rttstru.data2 = (BLDC_SensorlessCtr.Phase_C_ADC);     
//		Rttstru.data3 = (BLDC_SensorlessCtr.peakBusCurrent); 

        Rttstru.data0 = (BLDC_SensorlessCtr.peakBusCurrent);   
        Rttstru.data1 = (mBLDC_CtrProc.sys_error_flg);    
//	    Rttstru.data2 = (BLDC_SensorlessCtr.Phase_C_ADC);     
//		Rttstru.data3 = (BLDC_SensorlessCtr.peakBusCurrent); 		
					
        SEGGER_RTT_Write(1, &Rttstru, 4);		
		
}

void BLDC_CommProcess(void)
{
    u32 t_zeroCrossValue;

//    BLDC_SensorlessCtr.focusCommCnt++; //换相补偿计数 190928

    if((HALL0_CNT > QUIT_CMP_THRESHLD) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
    {
        if(BLDC_SensorlessCtr.lowSpeedFlg == 0)
        {
            if(mBLDC_CtrProc.nBLDC_PWM_value < PWM_PERIOD * 0.35)
            {
                BLDC_SensorlessCtr.lowSpeedFlg = 2;
            }
            else
            {
                BLDC_SensorlessCtr.lowSpeedFlg = 2;
            }

            CMP_IE &= ~BIT0;
            SysTick->CTRL = 0x0;
            mBLDC_CtrProc.nWork_mode = BLDC_MODE_ADC;
            SysTick->CTRL = 0x0;

            BLDC_SensorlessCtr.state = 0;
            BLDC_SensorlessCtr.blankEndTimeValue = 0;
            BLDC_SensorlessCtr.SpeedTimerCnt = (HALL0_CNT);
            BLDC_SensorlessCtr.current_commStep = BLDC_SensorlessCtr.communicateStep;
            BLDC_SensorlessCtr.HfiCurrStep = BLDC_SensorlessCtr.current_commStep;
//            calcNextComm_BefComm(BLDC_SensorlessCtr.current_commStep);

            BLDC_Communication();
            BLDC_SensorlessCtr.secBemfUpdateFlg = 0;
            BLDC_SensorlessCtr.comm_dec_cnt = 0;
            BLDC_SensorlessCtr.HfiFlg = 0;
            BLDC_SensorlessCtr.OpenLoopStepCnt = 0;

        }
        BLDC_SensorlessCtr.motor_RunCnt = 0;
    }

    if(BLDC_SensorlessCtr.HfiCurrStep == BLDC_SensorlessCtr.current_commStep)
    {

        if(BLDC_SensorlessCtr.OpenLoopStepCnt)
        {
            BLDC_SensorlessCtr.PhaseVoltage = (3 * (s32)BLDC_SensorlessCtr.PhaseVoltage +  BLDC_SensorlessCtr.PWM_adcValue) / 4; //母线电压
        }
        else
        {
            BLDC_SensorlessCtr.PhaseVoltage =  BLDC_SensorlessCtr.PWM_adcValue;
        }
        BLDC_SensorlessCtr.secBemfUpdateFlg |= BIT0;               
    }
    else
    {
        BLDC_SensorlessCtr.secBemfUpdateFlg &= ~BIT0;
        BLDC_SensorlessCtr.lastPhaseBemf = BLDC_SensorlessCtr.BEMF_adcValue ;  //上一次相电压
        BLDC_SensorlessCtr.secBemfUpdateFlg |= BIT1;
    }

    t_zeroCrossValue = (u32)(HALL0_CNT - BLDC_SensorlessCtr.BLDC_CommTime);
		
				
    if((mBLDC_CtrProc.eSysState != RUN) && (BLDC_SensorlessCtr.EabsFlg == 0) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))       
    {
        mBLDC_CtrProc.nWork_mode = BLDC_MODE_ADC;
        BLDC_SensorlessCtr.fir_speed = OVERFOLLW_HAlL_COMM_TIME;

        BLDC_SensorlessCtr.comm_dec_cnt = 8;

        BLDC_SensorlessCtr.PhaseVoltage =  BLDC_SensorlessCtr.PWM_adcValue;

    }
    else
    {

        if((BLDC_SensorlessCtr.lowSpeedFlg) && (BLDC_SensorlessCtr.EabsFlg == 0) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
        {   // 速度低的时候采用脉冲注入法
#ifndef BEMF_DBG_FUN

            force_CommProcess();
            ADC_CrossPointDetect();

            if(BLDC_SensorlessCtr.communicateStep != BLDC_SensorlessCtr.current_commStep)
            {
                BLDC_SensorlessCtr.SpeedTimerCnt = HALL0_CNT;

                BLDC_SensorlessCtr.minCommcationTime = BLDC_SensorlessCtr.SpeedTimerCnt / 2;

                BLDC_SensorlessCtr.HfiStep = BLDC_SensorlessCtr.communicateStep;
                BLDC_SensorlessCtr.communicateStep = BLDC_SensorlessCtr.current_commStep;

                BLDC_SensorlessCtr.fir_speed = ( t_zeroCrossValue + BLDC_SensorlessCtr.fir_speed  ) >> 1; // 数据滤波

                if(BLDC_SensorlessCtr.OpenLoopStepCnt < 6)
                {   /* 低速至少运行6次换相才允许切换到比较器模式 */
                    BLDC_SensorlessCtr.OpenLoopStepCnt++;
                }
                else
                {

                    if(mBLDC_CtrProc.nWork_mode == BLDC_MODE_ADC)
                    {
                        if( BLDC_SensorlessCtr.fir_speed <= WORK_MODE_THRESHLD)
                        {
                            mBLDC_CtrProc.nWork_mode = BLDC_MODE_CMP;
                            BLDC_SensorlessCtr.lowSpeedFlg = 0;

                            BLDC_SensorlessCtr.SpeedTimerCnt = BLDC_SensorlessCtr.SpeedTimerCnt / 2;

                            BLDC_SensorlessCtr.minCommcationTime = BLDC_SensorlessCtr.SpeedTimerCnt / 2;
                        }
                        else
                        {
                            BLDC_SensorlessCtr.OpenLoopStepCnt = 0;
                        }
                    }
                }

                BLDC_SensorlessCtr.HfiCurrStep = BLDC_SensorlessCtr.current_commStep;
                BLDC_Communication();
                BLDC_SensorlessCtr.secBemfUpdateFlg = 0;
                BLDC_SensorlessCtr.comm_dec_cnt = 0;
//                calcNextComm_BefComm(BLDC_SensorlessCtr.current_commStep);

            }
            else
#endif
            {

#ifdef BEMF_DBG_FUN
                BLDC_SensorlessCtr.communicateStep = testComm; //测试反电势项
                BLDC_SensorlessCtr.current_commStep = testComm;
#endif
                if(BLDC_SensorlessCtr.comm_dec_cnt < BLDC_SensorlessCtr.comm_dec_thd)
                {
                    BLDC_SensorlessCtr.comm_dec_cnt ++;
                }
                else
                {
                    BLDC_SensorlessCtr.comm_dec_cnt = 0;
                    if(BLDC_SensorlessCtr.HfiCurrStep == BLDC_SensorlessCtr.current_commStep)
                    {

                        if(BLDC_SensorlessCtr.HfiFlg)
                        {
                            BLDC_SensorlessCtr.communicateStep = BLDC_SensorlessCtr.HfiStep;
                            BLDC_SensorlessCtr.comm_dec_thd = BLDC_SensorlessCtr.last_commCnt;
                        }
                        else
                        {
                            BLDC_SensorlessCtr.comm_dec_thd = BLDC_SensorlessCtr.current_commCnt;
                        }
                    }
                    else
                    {
                        BLDC_SensorlessCtr.communicateStep = BLDC_SensorlessCtr.current_commStep;
                        BLDC_SensorlessCtr.comm_dec_thd = BLDC_SensorlessCtr.current_commCnt;
                    }

                    BLDC_SensorlessCtr.HfiCurrStep = 	BLDC_SensorlessCtr.communicateStep;

                    BLDC_SensorlessCtr.communicateStep = BLDC_SensorlessCtr.current_commStep;
                }
            }
        }
        else
        {
            BLDC_SensorlessCtr.comm_dec_cnt = 8;
        }
    }

}
/*******************************************************************************
 函数名称：    void PWM_Duty_Setting(void)
 功能描述：    PWM占空比设置
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/5/26      V1.0           LSL
 *******************************************************************************/
void PWM_Duty_Setting(void)
{
    s32 t_pwmValue;
	
   t_pwmValue = (s32)(mBLDC_CtrProc.nBLDC_PWM_value - (((s32)(mBLDC_CtrProc.nBusCurrLimit_Value) * PWM_PERIOD) >> 15));

    t_pwmValue = Limit_Output(t_pwmValue, 0, PWM_PERIOD);

    if(BLDC_SensorlessCtr.EabsFlg)
    {

  	  if(BLDC_SensorlessCtr.Eabs_Founction_Flg)
      {
	    if(BLDC_SensorlessCtr.Eabs_Hard_Flg)
		{
        MCPWM0_PRT = 0x0000DEAD;
        MCPWM0_IO01 = DRIVER_POLARITY;
        MCPWM0_IO23 = DRIVER_POLARITY;
        MCPWM0_PRT = 0x0000;
			
        MCPWM0_TH00 = 0;
        MCPWM0_TH01 = 0;

        MCPWM0_TH10 = 0;
        MCPWM0_TH11 = 0;

        MCPWM0_TH20 = 0;
        MCPWM0_TH21 = 0;
		}
		else
		{
        MCPWM0_PRT = 0x0000DEAD;
        MCPWM0_IO01 = DRIVER_POLARITY | 0x0808;
        MCPWM0_IO23 = DRIVER_POLARITY | 0x08;
        MCPWM0_PRT = 0x0000;
			
        MCPWM0_TH00 = -BLDC_SensorlessCtr.EabsPWM;
        MCPWM0_TH01 =  BLDC_SensorlessCtr.EabsPWM;

        MCPWM0_TH10 = -BLDC_SensorlessCtr.EabsPWM;
        MCPWM0_TH11 =  BLDC_SensorlessCtr.EabsPWM;

        MCPWM0_TH20 = -BLDC_SensorlessCtr.EabsPWM;
        MCPWM0_TH21 =  BLDC_SensorlessCtr.EabsPWM;   
		}			
		
	}		

    }
    else if(mBLDC_CtrProc.nPower)
    {
		
//			  if((t_pwmValue < PWM_PERIOD * 0.25) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
//				{
////				BLDC_SensorlessCtr.HFI_pwm_Min = HFI_PWM_MIN;
////				BLDC_SensorlessCtr.HFI_pwm_plus = HFI_PWM_PLUS;					
////				  BLDC_SensorlessCtr.Back_pwm_Min = BACK_PWM_MIN;
////				  BLDC_SensorlessCtr.Back_pwm_Max = BACK_PWM_MAX;
//				}
//				else
//				{
////				  BLDC_SensorlessCtr.Back_pwm_Min = 0;
////				  BLDC_SensorlessCtr.Back_pwm_Max = 0;		
//				}

		
/*超低速运行模式*/
#if (ULTRA_LOW_SPEED_FUNCTION == ENABLE_FUNCTION)		
				BLDC_SensorlessCtr.HFI_pwm_Min = HFI_PWM_MIN;
				BLDC_SensorlessCtr.HFI_pwm_plus = HFI_PWM_PLUS;
#else
				BLDC_SensorlessCtr.HFI_pwm_Min = 0;
				BLDC_SensorlessCtr.HFI_pwm_plus = 0;
#endif

        if(mBLDC_CtrProc.nWork_mode == BLDC_MODE_ADC )
        {
            if(BLDC_SensorlessCtr.insPhaseFlg == 1)
            {
                MCPWM0_TH00 = BLDC_SensorlessCtr.HFI_pwm_Min;
                MCPWM0_TH01 = BLDC_SensorlessCtr.HFI_pwm_plus;
            }
            else
            {
                MCPWM0_TH00 = -t_pwmValue;
                MCPWM0_TH01 = t_pwmValue;
            }

            if(BLDC_SensorlessCtr.insPhaseFlg == 2)
            {
                MCPWM0_TH10 = BLDC_SensorlessCtr.HFI_pwm_Min;
                MCPWM0_TH11 = BLDC_SensorlessCtr.HFI_pwm_plus;
            }
            else
            {
                MCPWM0_TH10 = -t_pwmValue;
                MCPWM0_TH11 = t_pwmValue;
            }

            if(BLDC_SensorlessCtr.insPhaseFlg == 3)
            {
                MCPWM0_TH20 = BLDC_SensorlessCtr.HFI_pwm_Min;
                MCPWM0_TH21 = BLDC_SensorlessCtr.HFI_pwm_plus;
            }
            else
            {
                MCPWM0_TH20 = -t_pwmValue;
                MCPWM0_TH21 = t_pwmValue;
            }
						
						if(t_pwmValue > 300)
						{
						  MCPWM0_TMR0 =  t_pwmValue - 200;   //ADC采样设置，在PWM完成mos震荡并关断前200个计数值前采样，
						}
						else
						{
						  MCPWM0_TMR0 = 50;
						}
        }
        else
        {

            MCPWM0_TH00 = -t_pwmValue;
            MCPWM0_TH01 = t_pwmValue;

            MCPWM0_TH10 = -t_pwmValue;
            MCPWM0_TH11 = t_pwmValue;

            MCPWM0_TH20 = -t_pwmValue;
            MCPWM0_TH21 = t_pwmValue;

            MCPWM0_TMR0 = t_pwmValue - 150;
        }
    }                                                                                                                                          

    BLDC_SensorlessCtr.actPWM_Value = t_pwmValue;	
	
}
/*******************************************************************************
 函数名称：    void Digital_Value_Getting(void)
 功能描述：    ADC值获取
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/5/26      V1.0           LSL
 *******************************************************************************/
void Digital_Value_Getting(void)
{/* ADC值读取 */
	
		if(ADC0_DAT4 & BIT15)
		{/*扳机输入*/
			mBLDC_CtrProc.nSpeed_ADC = 0;
		}
		else
		{
			mBLDC_CtrProc.nSpeed_ADC = (ADC0_DAT4 >> 4);	
		}
		
		if(ADC0_DAT5 & BIT15)
		{/*母线电压*/
		  mBLDC_CtrProc.nBUS_Vol_ADC = 0;
		}
    else
		{
      mBLDC_CtrProc.nBUS_Vol_ADC = (mBLDC_CtrProc.nBUS_Vol_ADC + ADC0_DAT5) >> 1;		
		}
		
		if(ADC0_DAT6 & BIT15)
		{/*MOS NTC温度*/
		  mBLDC_CtrProc.nNTC_Vol_ADC = 0;
		}
		else
		{
		  mBLDC_CtrProc.nNTC_Vol_ADC = ADC0_DAT6;
		}

		if(ADC0_DAT7 & BIT15)
		{/*电池 NTC温度*/
		  mBLDC_CtrProc.BAT_NTC_adc = 0;
		}
		else
		{
		  mBLDC_CtrProc.BAT_NTC_adc = ADC0_DAT6;
		}

}

/*******************************************************************************
 函数名称：    void Speed_Getting(void)
 功能描述：    速度获取
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/5/26      V1.0           LSL
 *******************************************************************************/
//void Speed_Getting(void)
//{
//		if(mBLDC_CtrProc.eSysState == RUN)
//		{		
//			BLDC_SensorlessCtr.Elect_Speed = 60000000000/(BLDC_SensorlessCtr.Provid_time * 20.8); //60*1000*1000*1000/(Per_provid_time * 20.8);
//		}
//		else
//		{
//			BLDC_SensorlessCtr.Provid_time = 20000000;
//			BLDC_SensorlessCtr.Elect_Speed = 0;
//			UTIMER1_CNT = 0;
//			BLDC_SensorlessCtr.communicate_cnt = 0;
//		}
//		BLDC_SensorlessCtr.Machine_Speed = BLDC_SensorlessCtr.Elect_Speed / POLE_NUMBLE;			
//}


void bldc_comm_process(u8 flg)
{
    u8 t_commFlg;


    t_commFlg = BLDC_SensorlessCtr.motorDirect;


    if(flg)
    {
        if(t_commFlg)
        {
            t_commFlg = 0;
        }
        else
        {
            t_commFlg = 1;
        }


        {

            {
                if(BLDC_SensorlessCtr.SpeedTimerCnt < 200000)
                {
                    BLDC_SensorlessCtr.bRevCnt++;
                    if(BLDC_SensorlessCtr.bRevCnt > 2)
                    {
//                        sys_errorFlg |= BLOCK_ERROR;
//						Block_flg = 4;
                    }


                }
                else
                {
                    BLDC_SensorlessCtr.bRevCnt = 0;
                }
            }
        }



        BLDC_SensorlessCtr.motor_RunCnt = 0;

    }
    else
    {
        BLDC_SensorlessCtr.bRevCnt = 0;
        BLDC_SensorlessCtr.motor_RunCnt ++;

//        BLDC_SensorlessCtr.totalFocusCommCnt = 0;
    }

    if(t_commFlg == 0)
    {
        if(BLDC_SensorlessCtr.current_commStep > 1)
        {
            BLDC_SensorlessCtr.current_commStep --;
        }
        else
        {
            BLDC_SensorlessCtr.current_commStep = 6;
        }
    }
    else
    {
        if(BLDC_SensorlessCtr.current_commStep < 6)
        {
            BLDC_SensorlessCtr.current_commStep ++;
        }
        else
        {
            BLDC_SensorlessCtr.current_commStep = 1;
        }
    }

    BLDC_SensorlessCtr.lastCommTime = (BLDC_SensorlessCtr.lastCommTime + BLDC_SensorlessCtr.bankCommTime) / 2;
    if(BLDC_SensorlessCtr.lastCommTime < 50)
    {
        BLDC_SensorlessCtr.lastCommTime = 50;
    }
    BLDC_SensorlessCtr.bankCommTime = 0;


}



/*******************************************************************************
 函数名称：    bus_current_limPro(void)
 功能描述：    限流输出
 其他说明：    若当前电流值大于所设定的恒流输出值，降低占空比限制电流大小
 *******************************************************************************/
void bus_current_limPro(void)
{
    s32 wAux;
    s16 t_Error;
    t_Error = (s16)(BLDC_SensorlessCtr.peakBusCurrent - CURRENT_LIM_VALUE);

    wAux = (t_Error * BLDC_SensorlessCtr.BusCur_lim_cof) >> 11;
    mBLDC_CtrProc.nBusCurrLimit_Value = Limit_Output(wAux, 0, S16_MAX);

    if(mBLDC_CtrProc.nBusCurrLimit_Value)
    {
        t_Error = mBLDC_CtrProc.nBusCurrLimit_Value >> 4;
        if(mBLDC_CtrProc.nRequestPower > t_Error)
        {
            mBLDC_CtrProc.nRequestPower -= t_Error;
        }
        mBLDC_CtrProc.nBLDC_PWM_value = (((s32)(mBLDC_CtrProc.nRequestPower) * PWM_PERIOD) >> 15);
    }

}


void BLDC_Init(void)
{
    BLDC_SensorlessCtr.BusCur_lim_cof = FRAC16(0.25);

    BLDC_SensorlessCtr.lowSpeedFlg = 1;
	
	ON_fly.MC_Fly_flg = 0;
	ON_fly.ON_fly_cnt = 0;

	ON_fly.ON_FLY_Start_THD = ON_FLY_ADC_THD;
	ON_fly.ON_Fly_Max_DUTY = ON_FLY_MAX_DUTY;
	ON_fly.ON_Fly_Min_DUTY= ON_FLY_MIN_DUTY;

	BLDC_SensorlessCtr.onTheFlyFlg = 0;
	BLDC_SensorlessCtr.EabsFlg = 0;
	
//	InitPI();
	
	PIParmS.qdSum      = 0;
	PIParmS.qInMeas    = 0;
	PIParmS.qOut       = MIN_DUTY;

    BLDC_SensorlessCtr.ctrState = 0;
    BLDC_SensorlessCtr.ctrMode = 0;

    BLDC_SensorlessCtr.state = 0;
    BLDC_SensorlessCtr.bankCommTime = 0;

    mBLDC_CtrProc.nBusCurrLimit_Value = 0;
    mBLDC_CtrProc.nRequestPower = 0;
    BLDC_SensorlessCtr.sCommmStabCnt = 0;

    BLDC_SensorlessCtr.ADC_valueH_thd = FRAC16(0.10);  /* 换相门槛 */   //0.10
    BLDC_SensorlessCtr.halfVol_cof = FRAC16(0.48);     /* 反电势电压中点校正值 */

    BLDC_SensorlessCtr.current_commCnt = 8;
    BLDC_SensorlessCtr.last_commCnt = 3;

    BLDC_SensorlessCtr.HFI_pwm_Min = -PWM_PERIOD;
    BLDC_SensorlessCtr.HFI_pwm_plus = -PWM_PERIOD;

    if(BLDC_SensorlessCtr.motorDirect)
    {
        BLDC_SensorlessCtr.BEMF_edgeSetting = 0xff;
    }
    else
    {
        BLDC_SensorlessCtr.BEMF_edgeSetting = 0x00;
    }


}

/*******************************************************************************
 函数名称：    void StopMotorImmdly(void)
 功能描述：    停机函数
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/

void StopMotorImmdly(void)
{
	  PWMOutputs(DISABLE);
	  mBLDC_CtrProc.bMC_RunFlg = 0;
	  mBLDC_CtrProc.nRequestPower = 0;   
}

void PWM_Output_Control(u8 output_flg)
{
  if(output_flg)
  {
    PWMOutputs(ENABLE);  
  }
  else
  {
    PWMOutputs(DISABLE); 
  }   
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

