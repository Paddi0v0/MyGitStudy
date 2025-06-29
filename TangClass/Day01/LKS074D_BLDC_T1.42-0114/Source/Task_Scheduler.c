/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� Task_Scheduler.c
 * �ļ���ʶ��
 * ����ժҪ�� ���������غ���
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� LSL
 * ������ڣ� 2023��6��8��
 *******************************************************************************/
#include "basic.h"
#include "global_variable.h"
#include "absacc.h"
#include "MC_Parameter.h"

void LED_flicker_setting(void);
/*******************************************************************************
 �������ƣ�    u16 procHander(u16 hallbarADvalue)
 ����������    ��������˲�
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
u16 procHander(u16 hallbarADvalue)
{   /* �����ְ��źŵ�ֵ*/
    static u16 adjFilter1;
    u16 tempChar;

    hallbarADvalue = hallbarADvalue & 0xfff;
    if(hallbarADvalue & 0x800)
    {
       hallbarADvalue = 0;
    }
    tempChar = (u16)(((hallbarADvalue + (u32) adjFilter1 * 7)) >> 3); /* �����˲� */
		adjFilter1 = tempChar;
    return (tempChar);
}

/*******************************************************************************
 �������ƣ�    void Speed_control(void)
 ����������    ���������ռ�ձ�֮��ת��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
volatile u16 Speed_ADC;
volatile u32 Powr_value;
volatile u16 Start_cnt;

void Speed_control(void)
{
    u16 Speed_value;
	
	Speed_ADC = procHander((u16) mBLDC_CtrProc.nSpeed_ADC);
	
	if(Speed_ADC > START_THRESHOLD_ADC)
	{
	  if(Start_cnt < 30)
	  {//�����ź��˲�
		Start_cnt++; 
	  }
	  else
	  {
		Start_cnt = 0;
		mBLDC_CtrProc.Power_on_flg = 1;
	  }			
	}
	else
	{
	   mBLDC_CtrProc.Power_on_flg = 0;
	}
		
	if(mBLDC_CtrProc.Power_on_flg)
	{		
	   if(Speed_ADC < SPEED_REGULATION_MIN_ADC)
	   {
		  Powr_value = MIN_POWER;
	   }
	   else
	   {				
		  Speed_value = Speed_ADC - SPEED_REGULATION_MIN_ADC;				
		  Powr_value = Speed_value * ZOOM_FACTOR + MIN_POWER;
	   }
							
//        Powr_value = 15000;			
	   if(Powr_value > S16_MAX)
	   {
		  mBLDC_CtrProc.nPower = 32768;
	   }
	   else
	   {
		  mBLDC_CtrProc.nPower = Powr_value;
	   }
				
	   mBLDC_CtrProc.nPower = sat(mBLDC_CtrProc.nPower,0,32768);
   }
	else
	{
		mBLDC_CtrProc.nPower = 0;		
	}
		
}
/*******************************************************************************
 �������ƣ�    void speed_ref_ramp(void)
 ����������    ռ�ձȸ�������
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
volatile u16 power_DEC_STEP = POWER_DEC_STEP, power_UP_STEP = POWER_ADD_STEP;

void speed_ref_ramp(void)
{
    u16 t_power;
    s16 t_value;
	
	if(mBLDC_CtrProc.sys_error_flg)
	{/*ϵͳ���ϣ���ֹ���*/
	   mBLDC_CtrProc.nPower = 0;
	}
	
    t_power = mBLDC_CtrProc.nPower;

    if (mBLDC_CtrProc.nRequestPower > t_power)
    {   /* ���ʸ���б���źż���*/
        if ((mBLDC_CtrProc.nRequestPower - t_power) > power_DEC_STEP)
        {
            mBLDC_CtrProc.nRequestPower -= power_DEC_STEP;
        }
        else
        {
            mBLDC_CtrProc.nRequestPower = t_power;
        }
    }
    else if (mBLDC_CtrProc.nRequestPower < t_power)
    {
			
			if((mBLDC_CtrProc.eSysState == RUN) || (mBLDC_CtrProc.nRequestPower < 100))
      {
        if ((t_power - mBLDC_CtrProc.nRequestPower) > power_UP_STEP)
        {
            mBLDC_CtrProc.nRequestPower += power_UP_STEP;

        }
        else
        {
            mBLDC_CtrProc.nRequestPower = t_power;
        }
			}	
			
			if(mBLDC_CtrProc.nRequestPower > 30)
			{
					if(BLDC_SensorlessCtr.EabsFlg == 0)
					{
						mBLDC_CtrProc.bMC_RunFlg = 1;
					}
			}	
    }
		
		if((t_power == 0) && (BLDC_SensorlessCtr.EabsFlg == 0) && (mBLDC_CtrProc.eSysState == RUN))
		{		
		    PWMOutputs(DISABLE);			
		}
		

    t_value = (((s32)(mBLDC_CtrProc.nRequestPower) * PWM_PERIOD) >> 15);
		
//		#if BACK_INSERT_FUN
//			t_value -= BACK_PWM_WIDTH;      /* �������岹��������ֹͣע�뷴������ʱ���ٶ��ȶ��� */	
//		#endif		

    if(BLDC_SensorlessCtr.EabsFlg == 0)
    {
        if(BLDC_SensorlessCtr.lowSpeedFlg)
        {
            if(BLDC_SensorlessCtr.sCommmStabCnt < 3)
            {   /* ����ǰ������������  */
//                t_value += 100;
                t_value = sat(t_value, PWM_PERIOD * 0.12, PWM_PERIOD * 0.35); /* ��С0.18 */
            }
            else
            {
                t_value = sat(t_value, PWM_PERIOD * MIN_DUTY, PWM_PERIOD * 0.75); /* ��С0.18 */
            }

        }
        else
        {
            t_value = sat(t_value, 0, PWM_PERIOD);
        }			
				
    }
		
//	#if ON_FLY_START_FUNCTION	
//		if(BLDC_SensorlessCtr.onTheFlyFlg)
//		{
//			if(ON_fly.ON_fly_cnt < 50)
//			{
//			  ON_fly.ON_fly_cnt++;
//			}
//			else
//			{
//				ON_fly.ON_fly_cnt = 0;
//			  BLDC_SensorlessCtr.onTheFlyFlg = 0;
//			}
//			t_value = ON_fly.duty;

//      ON_fly.power = ON_fly.duty * 32767/PWM_PERIOD;
//			
//      mBLDC_CtrProc.nRequestPower = ON_fly.power;			
//      			
//			ON_fly.power = sat(ON_fly.power, 5000, 30000);
//		}
//	#endif
		

    mBLDC_CtrProc.nBLDC_PWM_value = t_value;
}

/*******************************************************************************
 �������ƣ�    void Clear_error(void)
 ����������    �����������
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
void Clear_error(void)
{
   if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.nPower == 0))
	 {	 
		 mBLDC_CtrProc.sys_error_flg &= ~(SHORT_ERROR | BLOCK_ERROR | HIG_VOL_ERROR | LOW_VOL_ERROR
		                                  | OVER_LOAD_ERROR | PHASE_DROP_ERROR | MOSFET_ERROR);
	 
	 }	 
}

///*******************************************************************************
// �������ƣ�    void Vol_protect(void)
// ����������    �����������
// *******************************************************************************/
//void Vol_protect(void)
//{
//    static u16 LowVolatageCnt;
//	  static u16 LowVolatageCnt_1;
//	  static u16 OvrVolatageCnt;		
//		
//	if(mBLDC_CtrProc.bMC_RunFlg)
//	{/*���й�����Ƿѹ*/
//	  if(mBLDC_CtrProc.nBUS_Vol_ADC < LOW_VOLATAGE_FIRST)
//		{
//				if(LowVolatageCnt_1 < FIRST_LOW_TIME)
//				{
//						LowVolatageCnt_1++;
//				}
//				else
//				{
//						mBLDC_CtrProc.sys_error_flg |= LOW_VOL_ERROR;
//					  StopMotorImmdly();
//				}	
//		}
//		else
//		{
//				if(LowVolatageCnt_1)
//				{
//					 LowVolatageCnt_1 --;
//				}
//		}
//	}
//	else
//	{
//		if (mBLDC_CtrProc.nBUS_Vol_ADC < LOW_VOLATAGE_SECOND)
//		{/*����֮ǰǷѹ*/
//				if(LowVolatageCnt < 5)
//				{
//						LowVolatageCnt++;
//				}
//				else
//				{
//						mBLDC_CtrProc.sys_error_flg |= LOW_VOL_ERROR;
//					  StopMotorImmdly();
//				}
//		}
//		else
//		{  
//				if(mBLDC_CtrProc.Power_on_flg == 0)
//				{
//					 mBLDC_CtrProc.sys_error_flg &= ~LOW_VOL_ERROR;
//					 LowVolatageCnt = 0;
//				}
//		}
//	
//	}
//				
//    if (mBLDC_CtrProc.nBUS_Vol_ADC > OV_VOLTAGE_ADC)
//		{/*��ѹ����*/
//			if(OvrVolatageCnt < 3)
//			{
//			  OvrVolatageCnt++;			
//			}
//			else
//			{
//        mBLDC_CtrProc.sys_error_flg |= HIG_VOL_ERROR;
//        StopMotorImmdly();
//			}
//    }
//    else 
//		{
//			if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.nBUS_Vol_ADC < RSM_OV_VOLTAGE_ADC))
//			{
//        mBLDC_CtrProc.sys_error_flg &= ~HIG_VOL_ERROR;
//			  OvrVolatageCnt = 0;
//			}
//		}

//}
/*******************************************************************************
 �������ƣ�    void Motor_Block_Protect(void)
 ����������    �����ת��������
 *******************************************************************************/
volatile u8 last_communicateStep;
void Motor_Block_Protect(void)
{
    u16 block_THD;

    if(mBLDC_CtrProc.eSysState == RUN)
    {
        if((BLDC_SensorlessCtr.communicateStep == last_communicateStep) && (BLDC_SensorlessCtr.EabsFlg == 0))
        {
					  if(mBLDC_CtrProc.nBLDC_PWM_value > PWM_PERIOD * 0.25)
						{
							 block_THD = 100;
						}						
						else
						{/* 2s����ת*/
							 block_THD = 1000;
						}
            if(mBLDC_CtrProc.MotorBlockCnt < block_THD)
            {
                mBLDC_CtrProc.MotorBlockCnt++;
            }
            else
            {
              mBLDC_CtrProc.sys_error_flg |= BLOCK_ERROR;
							StopMotorImmdly();
            }
        }
        else
        {
            mBLDC_CtrProc.MotorBlockCnt = 0;
            last_communicateStep = BLDC_SensorlessCtr.communicateStep;
        }
    }
    else
    {
        mBLDC_CtrProc.MotorBlockCnt = 0;
    }
}

/*******************************************************************************
 �������ƣ�    void key_in_proc(void)
 ����������    ���������˲�����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
void key_in_proc(void)
{
    volatile static u8 PORTA_InputCnt;
    volatile static u16 old_PortA_State, hInputPort_State;
    u16 t_PortA_State;
	
	  t_PortA_State = 0;

    if(SWITCH_INPUT_MASK)
        t_PortA_State |= SWITCH_INPUT;

    if(DIRECT_INPUT_MASK)
        t_PortA_State |= DIRECT_INPUT;


    if(t_PortA_State == old_PortA_State)
    {/* A�˿����봦�� */
      if(PORTA_InputCnt < KEYIN_FILTER_TIME)
      {
         PORTA_InputCnt++;
      }
      else
      {
        if(hInputPort_State != old_PortA_State)
        {/* ��׽�ź�����ʱ�� */
           hInputPort_State = old_PortA_State;
        }
      }
    }
    else
    {
       old_PortA_State = t_PortA_State;
       PORTA_InputCnt = 0;
    }

    if((hInputPort_State & DIRECT_INPUT) == 0)
    {
      if(BLDC_SensorlessCtr.motorDirect == 1)
      {
        if(mBLDC_CtrProc.eSysState == IDLE)
        {
           BLDC_SensorlessCtr.motorDirect = 0;
        }
      }
    }
    else
    {
      if(BLDC_SensorlessCtr.motorDirect == 0)
      {
        if(mBLDC_CtrProc.eSysState == IDLE)
        {
           BLDC_SensorlessCtr.motorDirect = 1;
        }
      }
    }

    if(BLDC_SensorlessCtr.motorDirect)
    {
        BLDC_SensorlessCtr.BEMF_edgeSetting = 0xff;
    }
    else
    {
        BLDC_SensorlessCtr.BEMF_edgeSetting = 0x00;
    }

}


///*******************************************************************************
// �������ƣ�    void Dely_Turn_Off(void)
// ����������    ��ʱ�ϵ�    
// *******************************************************************************/
//void Dely_Turn_Off(void)
//{
//  static u16 turn_off_cnt;
//	if(( mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.eSysState == IDLE))
//	{//����ɵ�����ʱ�ϵ�
//		if(turn_off_cnt < LED_DELAY_TIME)
//		{
//	     turn_off_cnt++;
//		}
//		else 
//		{
//		  LOCK_POWER_OFF();
//		}
//	}
//	else
//	{
//	  turn_off_cnt = 0;
//	}
//}	

///*******************************************************************************
// �������ƣ�    OVER_current_protect(void)
// ����������    �ּ�����
// *******************************************************************************/
//volatile u16 over_current_time1,over_current_time2;
//void OVER_current_protect(void)
//{
//   if(mBLDC_CtrProc.eSysState == RUN)
//	 {
//	    if(BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_FIRST_THD)
//			{/*��һ������*/
//			  if(over_current_time1 < TIME_LIMIT_FIRST)
//				{
//				  over_current_time1++;
//				}
//				else
//				{
//				  mBLDC_CtrProc.sys_error_flg |= OVER_LOAD_ERROR;
//				  StopMotorImmdly();
//				}			
//			}
//			else
//			{
//			   if(over_current_time1)
//				 {
//				   over_current_time1--;
//				 }
//			}
//	 
//	    if(BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_SECOND_THD)
//			{/*�ڶ�������*/
//			  if(over_current_time2 < TIME_LIMIT_SECOND)
//				{
//				  over_current_time2++;
//				}
//				else
//				{
//				  mBLDC_CtrProc.sys_error_flg |= OVER_LOAD_ERROR;
//				  StopMotorImmdly();
//				}			
//			}
//			else
//			{
//			   if(over_current_time2)
//				 {
//				   over_current_time2--;
//				 }
//			}			
//					
//	 }
//	 else
//	 {
//		  over_current_time1 = 0;
//	    over_current_time2 = 0;
//	 }
//}

///*******************************************************************************
// �������ƣ�    LED_display(void)
// ����������    LED��ʾ
// *******************************************************************************/
//volatile u8  LED_flicker_flg,LED_state_flg;
//volatile u16 Light_ON_cnt,Light_OFF_cnt;
//volatile u16 Light_OFF_time; 
//volatile u8  LED_light_cnt;//LED��˸��������
//void LED_display(void)
//{
//	if(mBLDC_CtrProc.Power_on_flg == 0)
//	{//���عر�״̬ʱLED����
//	   LED_ON();
//		 LED_state_flg = 1;
//		 LED_flicker_flg = 0;
//		 Light_OFF_time = LED_OFF_TIME;
//	}
//	else
//	{/*���رպ�ʱ�й��ϣ�LED��˸���������޹��ϣ�LED����*/		
//	
//			LED_flicker_setting();
//		
//	   if(mBLDC_CtrProc.sys_error_flg)
//		 {//���عر�״̬�й��ϣ�LED��˸ָʾ
//		   if(mBLDC_CtrProc.sys_error_flg & SHORT_ERROR)
//			 {
//			   LED_flicker_flg = 1;
//			 }
//			 else if(mBLDC_CtrProc.sys_error_flg & LOW_VOL_ERROR)
//			 {
//			   LED_flicker_flg = 2;
//			 }
//			 else if(mBLDC_CtrProc.sys_error_flg & HIG_VOL_ERROR)
//			 {
//			   LED_flicker_flg = 3;
//			 }			 
//			 else if(mBLDC_CtrProc.sys_error_flg & BLOCK_ERROR)
//			 {
//			   LED_flicker_flg = 4;
//			 }			 
//			 else if(mBLDC_CtrProc.sys_error_flg & OVER_LOAD_ERROR)
//			 {
//			   LED_flicker_flg = 5;
//			 }	
//			 else if(mBLDC_CtrProc.sys_error_flg & MOS_OVER_ERROR)
//			 {
//			   LED_flicker_flg = 6;
//			 }			 
//		 }
//		 else
//		 {//���رպ�״̬�޹��ϣ�����		 
//		   LED_ON();
//			 LED_state_flg = 1;
//			 LED_flicker_flg = 0;
//		 }
//		 
//	}
//}

//void LED_flicker_setting(void)
//{ 
//  if(LED_flicker_flg)	
//	{
//	 if(Light_OFF_cnt < Light_OFF_time)
//	 {/*LEDϨ��ʱ���ʱ*/
//	   Light_OFF_cnt++;
//		 LED_OFF();
//     LED_state_flg = 0;
//     Light_ON_cnt = 0;		 
//	 }
//	 else
//	 {
//		  if(Light_ON_cnt < LED_ON_TIME)
//			{/*LED����ʱ*/
//				 Light_ON_cnt++;
//				 LED_ON();
//			   LED_state_flg = 1;			   
//			}
//	    else
//			{
//				 Light_OFF_cnt = 0;;
//		     LED_OFF();
//         LED_state_flg = 0;
//         
//         if(LED_light_cnt < (LED_flicker_flg - 1))
//         {
//				   LED_light_cnt++;
//					 Light_OFF_time = LED_OFF_TIME;   /* ��˸������LEDϨ��ʱ�� */
//				 }
//         else
//         {
//				   LED_light_cnt = 0;
//					 Light_OFF_time = LED_PERIOD_DELAY; /* �����˸���ں�LEDϨ��ʱ�� */
//				 }					 
//			}	 
//	  }
//	}
//	else
//	{
//		Light_OFF_cnt = 0;
//	  LED_light_cnt = 0;
//		Light_OFF_time = LED_OFF_TIME;	
//	}

//}
///*******************************************************************************
// �������ƣ�    void MOS_TEMP_protect(void)
// ����������    MOS�¶ȱ�������
// *******************************************************************************/
//volatile u16 Over_MOStemp_Cnt,Over_BATtemp_Cnt;
//volatile u32 mos_tmp_test,mos_RSM_test;
//void MOS_TEMP_protect(void)
//{
////	mos_tmp_test = MOS_TEMP_OVER_THD;
////	mos_RSM_test = RSM_MOS_TEMP_OVER_THD;
//    if(mBLDC_CtrProc.nMOS_NTC_ADC < MOS_TEMP_OVER_THD)
//    {   /* MOS���� */
//        if(Over_MOStemp_Cnt < MOS_TEMP_OVER_TIME)
//        {
//            Over_MOStemp_Cnt++;
//        }
//        else
//        {
//            mBLDC_CtrProc.sys_error_flg |= MOS_OVER_ERROR;
//            StopMotorImmdly();
//        }
//    }
//    else
//    {
//				Over_MOStemp_Cnt = 0;
//						
//        if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.nMOS_NTC_ADC > RSM_MOS_TEMP_OVER_THD))
//        {   /* ������ɣ����¹��ϲ����� */
//            mBLDC_CtrProc.sys_error_flg &= ~MOS_OVER_ERROR;
//        }
//    }	

//}

///*******************************************************************************
// �������ƣ�    void BAT_TEMP_protect(void)
// ����������    ��ذ��¶ȱ�������
// *******************************************************************************/
//void BAT_TEMP_protect(void)
//{
///* BAT���±��� */		
//    if(mBLDC_CtrProc.nBAT_NTC_ADC < BAT_TEMP_OVER_THD)
//    {   
//        if(Over_BATtemp_Cnt < BAT_TEMP_OVER_TIME)
//        {
//            Over_BATtemp_Cnt++;
//        }
//        else
//        {
//            mBLDC_CtrProc.sys_error_flg |= BAT_OVER_ERROR;
//            StopMotorImmdly();
//        }
//    }
//    else
//    {
//				Over_BATtemp_Cnt = 0;
//						
//        if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.nBAT_NTC_ADC > RSM_BAT_TEMP_OVER_THD))
//        {   /* ������ɣ����¹��ϲ����� */
//            mBLDC_CtrProc.sys_error_flg &= ~BAT_OVER_ERROR;
//        }
//    }	
//		
//}

///*******************************************************************************
// �������ƣ�    void LKS_Viewer_Init(void)
// ����������    LKS_Viewer��ʼ��
// �޸�����      �汾��          �޸���            �޸�����
// -----------------------------------------------------------------------------
// 2022/5/30      V1.0            LSL               ����
// *******************************************************************************/
//u8 ch1Buffer[512] = {0};
//u8 ch2Buffer[512] = {0};
//int theta = 0;
//int theta2 = 0;

//void LKS_Viewer_Init(void)
//{
//	PRINTF("start lksviewer demo project...\r\n");
//	// ��Ҫ���룬��ʼ��ʹ�õĻ�������ͨ�� 0 ���ڴ�ӡ��������ﲻ�ó�ʼ����
//	LKS_VIEWER_DeInit();
//	LKS_VIEWER_InitBuffer(1, ch1Buffer, 512);
//	LKS_VIEWER_InitBuffer(2, ch2Buffer, 512);
//	// ��ѡ����ʼ������������󣬿�ͨ����λ����̬�޸ġ�?2022 ��Ȩ����Ÿ��о���� �����ļ�δ����ɲ�����ɢ 25
//	LKS_VIEWER_InitVar(1, &theta, sizeof(theta));
//	LKS_VIEWER_InitVar(2, &theta2, sizeof(theta2));

//}



///************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
///* ------------------------------END OF FILE------------------------------------ */
