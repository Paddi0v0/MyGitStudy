/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� Protect.c
 * �ļ���ʶ��
 * ����ժҪ�� ���򱣻�����
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet Li
 * ������ڣ� 2020��8��16��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�2020��8��16��
 * �� �� �ţ�V 1.0
 * �� �� �ˣ�Howlet Li
 * �޸����ݣ�����
 *
 *******************************************************************************/
#include "basic.h"
#include "global_variable.h"
#include "absacc.h"
#include "MC_Parameter.h"

void LED_flicker_setting(void);
void Trigger_Speedloop_Control(void);
stru_Fault_Stall_Rev Fault_Stall_Rev;

/*******************************************************************************
 �������ƣ�    u16 procHander(u16 hallbarADvalue)
 ����������    ��������˲�
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
u16 procHander(u16 hallbarADvalue)
{   /* �����ְ��źŵ�ֵ*/
    static u16 adjFilter1;
    u16 tempChar;

    hallbarADvalue = hallbarADvalue & 0xfff;
    if (hallbarADvalue & 0x800)
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
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
volatile u16 Speed_value;
volatile u32 Powr_value;

//volatile u32 KEYSET=2;


volatile u16 Start_cnt;
volatile u32 Expected_elect_speed;    //�ٶȻ���ת��Ŀ��ֵ EXPECTED_ELECT_SPEED
volatile u32 Expected_Machine_Speed;  //�ٶȻ���еת��Ŀ��ֵ
void Speed_control(void)
{
	  Speed_value = procHander((u16) mBLDC_CtrProc.nSpeed_ADC);
	
#if (LKSSCOPE_START_FUNCTION == ENABLE_FUNCTION)		
			if(mBLDC_CtrProc.bMC_RunFlg == 1 )      //��λ�������������ֶ��� bMC_RunFlg ��1
			{
				 mBLDC_CtrProc.Power_on_flg = 1;
				 Speed_value= MANUAL_SPEED ;          //�ֶ�����ת��
			}
			else 
			{
			mBLDC_CtrProc.Power_on_flg = 0;
			Speed_value=10;	
			}
#endif	

if(DirChange_Ctr.DirChange_Flag == 0)  //����ת�����
{	
//��ť����

#if (START_UP_TEST_FUNCTION == ENABLE_FUNCTION)
  Start_Up_Test();
#endif 
	
	  if(Speed_value > START_THRESHOLD_ADC)
		{
			if(Start_cnt < 30)
			{//�����ź��˲�
				Start_cnt++; 
			}
			else
			{
		    mBLDC_CtrProc.Power_on_flg = 1;
			}			
		}
		else
		{
		  mBLDC_CtrProc.Power_on_flg = 0;
		}
}	

		
		if(mBLDC_CtrProc.Power_on_flg)
		{	
//			//˳������
			if(BLDC_SensorlessCtr.onTheFlyFlg)
			{
			  if(ON_fly.ON_fly_cnt < ON_FLY_RUN_TIME)
			  {
			    ON_fly.ON_fly_cnt++;
			  }
			  else
			  {
			    ON_fly.ON_fly_cnt = 0;
			    BLDC_SensorlessCtr.onTheFlyFlg = 0;
			  }
			  
	         ON_fly.power = ON_fly.duty * 32767/PWM_PERIOD;
	         ON_fly.power = Limit_Output(ON_fly.power, ON_FLY_MIN_POWER, ON_FLY_MAX_POWER);
			  
			 Powr_value =  ON_fly.power;	
			 mBLDC_CtrProc.nPower = ON_fly.power;
	     mBLDC_CtrProc.nRequestPower = ON_fly.power;			
				//˳�������
			}
			else
			{
		
				if(Speed_value < SPEED_UP_ADC)
				{
				 Powr_value = START_POWER;
				}
				else
				{	
//�������ռ�ձ�ģʽ					
#if (TRIGGER_CONTROL_MODE == TRIGGER_DUTY_CONTROL)								
			Speed_value = Speed_value - SPEED_UP_ADC;					
			Powr_value = Speed_value * SPEED_UP_RATIO;  //���ٲ���ͣ���������
			Powr_value += (s32)((Speed_value * FRAC16(0.06))) >> 15;
			Powr_value += START_POWER;
#endif


//�����ٶȻ�					
#if (SPEED_LOOP_FUNCTION == ENABLE_FUNCTION)			 //�����ٶȻ�			
			      PIParmS.qInMeas = Speedgetting.Elect_Speed;   //�����ת�ٵ�ǰֵ, ��λ��HZ
					  Expected_elect_speed = EXPECTED_ELECT_SPEED;//�ٶȻ���ת��Ŀ��ֵ, ��λ��HZ
						Expected_Machine_Speed = EXPECTED_MACHINE_SPEED; //�ٶȻ���еת��Ŀ��ֵ, ��λ��RPM
#if (TRIGGER_CONTROL_MODE == TRIGGER_SPEED_CONTROL)		 //����ٶȻ�����ģʽ  						
            Trigger_Speedloop_Control();
#endif							
			      PIParmS.qInRef  = Expected_elect_speed;   
			      CalcPI(&PIParmS); 					
					  PIParmS.qOut = Limit_Output(PIParmS.qOut, MIN_DUTY, MAX_DUTY);  //����޷�:	������	 MIN_DUTY-MAX_DUTY ֮��   
		        Powr_value = PIParmS.qOut;
#endif	
					
				}
//#endif						
			}
								
				if (Powr_value > S16_MAX)
				{
						mBLDC_CtrProc.nPower = S16_MAX;
				}
				else
				{
						mBLDC_CtrProc.nPower = Powr_value;
				}
				
				
		}
		else
		{
			mBLDC_CtrProc.nPower = 0;		
		}
		
}


//u16 power_DEC_STEP = 30, power_UP_STEP = 100;   /*ռ�ձȼ���/���ٲ��� */
//volatile u16 closePowerCnt; /* �ػ�ʱ����� */
void speed_ref_ramp(void)
{
    u16 t_power;
    s16 t_value;

	
	if(mBLDC_CtrProc.sys_error_flg)
	{/*ϵͳ���ϣ���ֹ���*/
       StopMotorImmdly();
	   mBLDC_CtrProc.nPower = 0;
	}
	
    t_power = mBLDC_CtrProc.nPower;

    if (mBLDC_CtrProc.nRequestPower > t_power)
    {   /* ���ʸ���б���źż���*/
        if ((mBLDC_CtrProc.nRequestPower - t_power) > POWER_DEC_STEP)
        {
            mBLDC_CtrProc.nRequestPower -= POWER_DEC_STEP;
        }
        else
        {
            mBLDC_CtrProc.nRequestPower--;
        }
    }
    else if (mBLDC_CtrProc.nRequestPower < t_power)
    {
			
	  if((mBLDC_CtrProc.eSysState == RUN) || (mBLDC_CtrProc.nRequestPower < 100))
      {
        if ((t_power - mBLDC_CtrProc.nRequestPower) > POWER_UP_STEP)
        {
            mBLDC_CtrProc.nRequestPower += POWER_UP_STEP;

        }
        else
        {
            mBLDC_CtrProc.nRequestPower++;
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
	
    if((t_power == 0) && (mBLDC_CtrProc.eSysState == RUN) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
    {
       BLDC_SensorlessCtr.EabsFlg = 1;		
	   mBLDC_CtrProc.eSysState = BRAKE;
	   BLDC_SensorlessCtr.Eabs_Slip_Cnt = 0;
       BLDC_SensorlessCtr.EabsCnt = 0;
		
	   CMP_IE &= ~BIT0;
       StopMotorImmdly();
    }	

    t_value = (((s32)(mBLDC_CtrProc.nRequestPower) * PWM_PERIOD) >> 15);

    if(BLDC_SensorlessCtr.EabsFlg == 0)
    {
        if(BLDC_SensorlessCtr.lowSpeedFlg)
        {
            t_value += BASIC_PWM_VALUE;
            if(BLDC_SensorlessCtr.sCommmStabCnt < 3)
            {   /* ����ǰ������������  */
                t_value += HEAVY_LOAD_START;     //֧����������
                t_value = Limit_Output(t_value, PWM_PERIOD * FIRST_START_MIN_DUTY, PWM_PERIOD * 0.75);   //����ǰ���ĵ�ռ�ձ�
            }
            else
            {
                BLDC_SensorlessCtr.lowSpeedFlg  = 1;
                t_value = Limit_Output(t_value, PWM_PERIOD * ADC_MODE_MIN_DUTY, PWM_PERIOD * 0.75);    //������ADCģʽռ�ձ�
            }

            BLDC_SensorlessCtr.HFI_pwm_plus = -PWM_PERIOD;
        }
        else
        {
            t_value += BASIC_PWM_VALUE;
            t_value = Limit_Output(t_value, 0, PWM_PERIOD);   //CMPģʽռ�ձ�
        }
    }
    mBLDC_CtrProc.nBLDC_PWM_value = t_value;
}

/*******************************************************************************
 �������ƣ�    void Clear_error(void)
 ����������    �����������
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
void Clear_error(void)
{
   if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.nPower == 0))
	 {	 
		 mBLDC_CtrProc.sys_error_flg &= ~(SHORT_ERROR | BLOCK_ERROR | HIG_VOL_ERROR | LOW_VOL_ERROR
		                                  | OVER_LOAD_ERROR | PHASE_DROP_ERROR);
	 
	 }	 
}

/*******************************************************************************
 �������ƣ�    void Vol_protect(void)
 ����������    �����������
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
void Vol_protect(void)
{
    static u16 LowVolatageCnt;
	  static u16 LowVolatageCnt_1;
	  static u16 OvrVolatageCnt;		
		
	if(mBLDC_CtrProc.bMC_RunFlg)
	{/*���й�����Ƿѹ*/
	  if(mBLDC_CtrProc.nBUS_Vol_ADC < LOW_VOLATAGE_FIRST)
		{
				if(LowVolatageCnt_1 < FIRST_LOW_TIME)
				{
						LowVolatageCnt_1++;
				}
				else
				{
						mBLDC_CtrProc.sys_error_flg |= LOW_VOL_ERROR;
					  StopMotorImmdly();
				}	
		}
		else
		{
				if(LowVolatageCnt_1)
				{
					 LowVolatageCnt_1 --;
				}
		}
	}
	else
	{
		if (mBLDC_CtrProc.nBUS_Vol_ADC < LOW_VOLATAGE_SECOND)
		{/*����֮ǰǷѹ*/
				if(LowVolatageCnt < 5)
				{
						LowVolatageCnt++;
				}
				else
				{
						mBLDC_CtrProc.sys_error_flg |= LOW_VOL_ERROR;
					  StopMotorImmdly();
				}
		}
		else
		{  
				if(mBLDC_CtrProc.Power_on_flg == 0)
				{
					 mBLDC_CtrProc.sys_error_flg &= ~LOW_VOL_ERROR;
					 LowVolatageCnt = 0;
				}
		}
	
	}
				
    if (mBLDC_CtrProc.nBUS_Vol_ADC > OV_VOLTAGE_ADC)
		{/*��ѹ����*/
			if(OvrVolatageCnt < 3)
			{
			  OvrVolatageCnt++;			
			}
			else
			{
        mBLDC_CtrProc.sys_error_flg |= HIG_VOL_ERROR;
        StopMotorImmdly();
			}
    }
    else 
		{
			if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.nBUS_Vol_ADC < RSM_OV_VOLTAGE_ADC))
			{
        mBLDC_CtrProc.sys_error_flg &= ~HIG_VOL_ERROR;
			  OvrVolatageCnt = 0;
			}
		}

}


/*******************************************************************************
 �������ƣ�    void Block_error(void)
 ����������    �����������
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/	 
void Block_error_Rev(void)
{
	  //��ת��������ת��ͣ�� STALL_FAULT_RECOVER_TIME �룬�����ת����׼����һ��������
	  //�����ת�������ʼ��ת������һ������ STALL_NUMBER �Σ�������޴���������ʧ�ܣ���������ֶ�ת���󣬲�������
    if(mBLDC_CtrProc.sys_error_flg == BLOCK_ERROR)
        {

				if((Fault_Stall_Rev.RecoverTime < STALL_NUMBER) || (STALL_NUMBER_STATUS) )   //
				{
					if(Fault_Stall_Rev.RecoverCnt < STALL_FAULT_RECOVER_TIME)   //2s�������ת���ϱ�־λ
						
						{
								Fault_Stall_Rev.RecoverCnt ++;
						}
						else
						{	  
							  Fault_Stall_Rev.RecoverTime++;
								mBLDC_CtrProc.sys_error_flg = 0;
							
						}
						
				}
//				else
//				{
//					 Fault_Stall_Rev.RecoverTime = 0;  //��ת��������
//					 Fault_Stall_Rev.RecoverCnt = 0;   //��������λ
//				}	
				
	    }
	 	
		else
		{
			Fault_Stall_Rev.RecoverTime = 0;  //��ת��������
			Fault_Stall_Rev.RecoverCnt = 0;   //��������λ
		}	

}


/*******************************************************************************
 �������ƣ�    void Motor_Block_Protect(void)
 ����������    �����ת��������
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
void Motor_Block_Protect(void)
{
    u16 block_THD;

    if (mBLDC_CtrProc.eSysState == RUN)
    {
        if((BLDC_SensorlessCtr.communicateStep == BLDC_SensorlessCtr.oldCommunicateStep) && (BLDC_SensorlessCtr.EabsFlg == 0))
        {
					  if(mBLDC_CtrProc.nBLDC_PWM_value > PWM_PERIOD * 0.25)
						{
							 block_THD = 100;
						}						
						else
						{/* 2s����ת*/
							 block_THD = 2000;
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
            BLDC_SensorlessCtr.oldCommunicateStep = BLDC_SensorlessCtr.communicateStep;
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
 2020/9/20      V1.0           Howlet Li          ����
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
    {   /* A�˿����봦�� */
        if(PORTA_InputCnt < KEYIN_FILTER_TIME)
        {
            PORTA_InputCnt++;
        }
        else
        {
            if(hInputPort_State != old_PortA_State)
            {   /* ��׽�ź�����ʱ�� */
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
        if (BLDC_SensorlessCtr.motorDirect == 1)
        {
            if (mBLDC_CtrProc.eSysState == IDLE)
            {
                BLDC_SensorlessCtr.motorDirect = 0;
            }
        }

    }
    else
    {
        if (BLDC_SensorlessCtr.motorDirect == 0)
        {
            if (mBLDC_CtrProc.eSysState == IDLE)
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


/*******************************************************************************
 �������ƣ�    void Dely_Turn_Off(void)
 ����������    ��ʱ�ϵ�
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
void Dely_Turn_Off(void)
{
  static u16 turn_off_cnt;
	if(( mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.eSysState == IDLE))
	{//����ɵ�����ʱ�ϵ�
		if(turn_off_cnt < LED_DELAY_TIME)
		{
	     turn_off_cnt++;
		}
		else 
		{
		  LOCK_POWER_OFF();
		}
	}
	else
	{
	  turn_off_cnt = 0;
	}
}	

/*******************************************************************************
 �������ƣ�    void Flash_write(void)
 ����������    Flash��д����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
typedef struct
{   
    u32 test1; /* falshд������*/
    u32 test2;
	  u32 test3;
	  u8 buffer[500];
}FlashParamaStruct;

//volatile u32 flash_ts1,flash_ts2,flash_ts3;

//volatile u16 test_1,test_cnt;
//volatile const FlashParamaStruct struFlashParama __at(MEMORY_DATA_ADDR) =
//{
//    20,30,40, /*��ʼֵ*/
//};
//u32 t_FlashBuf[3] = {0,0,0,};  //�趨u32����

//void Flash_write(void)
//{
///*falsh write test*/		
//			t_FlashBuf[0] = 220;
//			t_FlashBuf[1] = 360;
//			t_FlashBuf[2] = 1048;
//			
//			if(test_1)
//			{
//				if(test_cnt < 30000)
//				{
//			    test_cnt++;
//				}
//			}
//			
//			if(test_cnt == 5000)
//			{
//					__disable_irq();
//					EraseSector(MEMORY_DATA_ADDR);
//					ProgramPage(MEMORY_DATA_ADDR, 512, (unsigned char*) (&t_FlashBuf[0]));	
//					__enable_irq(); /* FLASHд�뺯��*/
//				
//			}
//			flash_ts1 = struFlashParama.test1;
//			flash_ts2 = struFlashParama.test2;
//			flash_ts3 = struFlashParama.test3;
///*falsh write test*/
//}

/*******************************************************************************
 �������ƣ�    OVER_current_protect(void)
 ����������    �ּ�����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
volatile u16 over_current_time1,over_current_time2,over_current_time3;
void OVER_current_protect(void)
{
   if(mBLDC_CtrProc.eSysState == RUN)
	 {
	    if(BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_FIRST_THD)
			{/*��һ������*/
			  if(over_current_time1 < TIME_LIMIT_FIRST)
				{
				  over_current_time1++;
				}
				else
				{
				  mBLDC_CtrProc.sys_error_flg |= OVER_LOAD_ERROR;
				  StopMotorImmdly();
				}			
			}
			else
			{
			   if(over_current_time1)
				 {
				   over_current_time1--;
				 }
			}
	 
	    if(BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_SECOND_THD)
			{/*�ڶ�������*/
			  if(over_current_time2 < TIME_LIMIT_SECOND)
				{
				  over_current_time2++;
				}
				else
				{
				  mBLDC_CtrProc.sys_error_flg |= OVER_LOAD_ERROR;
				  StopMotorImmdly();
				}			
			}
			else
			{
			   if(over_current_time2)
				 {
				   over_current_time2--;
				 }
			}	

		if (BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_THRED_THD)
		{ /*����������*/
			if (over_current_time3 < TIME_LIMIT_THRED)
			{
				over_current_time3++;
			}
			else
			{
				mBLDC_CtrProc.sys_error_flg |= OVER_LOAD_ERROR;
				StopMotorImmdly();
			}
		}
		else
		{
			if (over_current_time3)
			{
				over_current_time3--;
			}
		}			
					
	 }
	 else
	 {
		  over_current_time1 = 0;
	    over_current_time2 = 0;
		  over_current_time3 = 0 ;
	 }
}

/*******************************************************************************
 �������ƣ�    LED_display(void)
 ����������    LED��ʾ
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
volatile u8  LED_flicker_flg,LED_state_flg;
volatile u16 Light_ON_cnt,Light_OFF_cnt;
volatile u16 Light_OFF_time; 
volatile u8  LED_light_cnt;//LED��˸��������
void LED_display(void)
{
	if(mBLDC_CtrProc.Power_on_flg == 0)
	{//���عر�״̬ʱLED����
	   LED_ON();
		 LED_state_flg = 1;
		 LED_flicker_flg = 0;
		 Light_OFF_time = LED_OFF_TIME;
	}
	else
	{/*���رպ�ʱ�й��ϣ�LED��˸���������޹��ϣ�LED����*/		
	
			LED_flicker_setting();
		
	   if(mBLDC_CtrProc.sys_error_flg)
		 {//���عر�״̬�й��ϣ�LED��˸ָʾ
		   if(mBLDC_CtrProc.sys_error_flg & SHORT_ERROR)
			 {
			   LED_flicker_flg = 1;
			 }
			 else if(mBLDC_CtrProc.sys_error_flg & LOW_VOL_ERROR)
			 {
			   LED_flicker_flg = 2;
			 }
			 else if(mBLDC_CtrProc.sys_error_flg & HIG_VOL_ERROR)
			 {
			   LED_flicker_flg = 3;
			 }			 
			 else if(mBLDC_CtrProc.sys_error_flg & BLOCK_ERROR)
			 {
			   LED_flicker_flg = 4;
			 }			 
			 else if(mBLDC_CtrProc.sys_error_flg & OVER_LOAD_ERROR)
			 {
			   LED_flicker_flg = 5;
			 }	
			 else if(mBLDC_CtrProc.sys_error_flg & MOS_OVER_ERROR)
			 {
			   LED_flicker_flg = 6;
			 }			 
		 }
		 else
		 {//���رպ�״̬�޹��ϣ�����		 
		   LED_ON();
			 LED_state_flg = 1;
			 LED_flicker_flg = 0;
		 }
		 
	}
}

void LED_flicker_setting(void)
{ 
  if(LED_flicker_flg)	
	{
	 if(Light_OFF_cnt < Light_OFF_time)
	 {/*LEDϨ��ʱ���ʱ*/
	   Light_OFF_cnt++;
		 LED_OFF();
     LED_state_flg = 0;
     Light_ON_cnt = 0;		 
	 }
	 else
	 {
		  if(Light_ON_cnt < LED_ON_TIME)
			{/*LED����ʱ*/
				 Light_ON_cnt++;
				 LED_ON();
			   LED_state_flg = 1;			   
			}
	    else
			{
				 Light_OFF_cnt = 0;;
		     LED_OFF();
         LED_state_flg = 0;
         
         if(LED_light_cnt < (LED_flicker_flg - 1))
         {
				   LED_light_cnt++;
					 Light_OFF_time = LED_OFF_TIME;   /* ��˸������LEDϨ��ʱ�� */
				 }
         else
         {
				   LED_light_cnt = 0;
					 Light_OFF_time = LED_PERIOD_DELAY; /* �����˸���ں�LEDϨ��ʱ�� */
				 }					 
			}	 
	  }
	}
	else
	{
		Light_OFF_cnt = 0;
	  LED_light_cnt = 0;
		Light_OFF_time = LED_OFF_TIME;	
	}

}
/*******************************************************************************
 �������ƣ�    void TEMP_protect(void)
 ����������    MOS�¶ȱ�������
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
volatile u16 Over_MOStemp_Cnt,Over_BATtemp_Cnt;
volatile u32 mos_tmp_test,mos_RSM_test;
void TEMP_protect(void)
{
//	mos_tmp_test = MOS_TEMP_OVER_THD;
//	mos_RSM_test = RSM_MOS_TEMP_OVER_THD;
    if(mBLDC_CtrProc.nNTC_Vol_ADC < MOS_TEMP_OVER_THD)
    {   /* MOS���� */
        if(Over_MOStemp_Cnt < MOS_TEMP_OVER_TIME)
        {
            Over_MOStemp_Cnt++;
        }
        else
        {
            mBLDC_CtrProc.sys_error_flg |= MOS_OVER_ERROR;
            StopMotorImmdly();
        }
    }
    else
    {
				Over_MOStemp_Cnt = 0;
						
        if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.nNTC_Vol_ADC > RSM_MOS_TEMP_OVER_THD))
        {   /* ������ɣ����¹��ϲ����� */
            mBLDC_CtrProc.sys_error_flg &= ~MOS_OVER_ERROR;
        }
    }
		
    if(mBLDC_CtrProc.BAT_NTC_adc < BAT_TEMP_OVER_THD)
    {   /* BAT���� */
        if(Over_BATtemp_Cnt < BAT_TEMP_OVER_TIME)
        {
            Over_BATtemp_Cnt++;
        }
        else
        {
            mBLDC_CtrProc.sys_error_flg |= BAT_OVER_ERROR;
            StopMotorImmdly();
        }
    }
    else
    {
				Over_BATtemp_Cnt = 0;
						
        if((mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.BAT_NTC_adc > RSM_BAT_TEMP_OVER_THD))
        {   /* ������ɣ����¹��ϲ����� */
            mBLDC_CtrProc.sys_error_flg &= ~BAT_OVER_ERROR;
        }
    }				

}

/*******************************************************************************
 �������ƣ�  void Speed_Getting(void)
 ����������  �ٶȻ�ȡ    S=60F/N    
 ����˵����  N=60F/S    N�� ������   F������ٶȵ�Ƶ��   S�������е�ٶ�    
 �޸�����    �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/5/26      V1.0           LSL
 *******************************************************************************/
stru_Speedgetting_Ctr Speedgetting; /* �ٶȻ�ȡ�ṹ�� */ 

void Speed_Getting(void)
{
   if(mBLDC_CtrProc.eSysState == RUN)
   {		
     Speedgetting.Elect_Speed = 60000000000/(Speedgetting.Provid_time * MCU_SYS_TIME); //60*1000*1000*1000/(Speedgetting.Provid_time * 10.8);
   }
   else
   {                                
	 Speedgetting.Provid_time = 300000000;
	 Speedgetting.Elect_Speed = 0;
	 UTIMER1_CNT = 0;
	 Speedgetting.communicate_cnt = 0;
   }
   
   Speedgetting.Machine_Speed = Speedgetting.Elect_Speed / MOTOR_POLE_NUMBER;			
}

/*******************************************************************************
 �������ƣ�    void Phase_Drop_Protect(void)
 ����������    ȱ���⺯��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          ����
 *******************************************************************************/
void Phase_Drop_Protect(void)
{
  u8 i;
	
  for(i=1;i<7;i++)
  {
	if((mIPD_CtrProc.AdcSampCurr[i] - BLDC_SensorlessCtr.PeakCurrOffset) < 300)
	{
	   mBLDC_CtrProc.sys_error_flg |= PHASE_DROP_ERROR;
	}
  }
	
}

/*******************************************************************************
 �������ƣ�    void Trigger_Speedloop_Control(void)
 ����������    ����ٶȻ�����ģʽ
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2024/6/5      V1.0           Dutch             ����
 *******************************************************************************/
void Trigger_Speedloop_Control(void)
{

					if((Speed_value > SPEED_UP_ADC) && (Speed_value < U12_MAX))
				{
					Speed_value = Speed_value - SPEED_UP_ADC;					
					Expected_Machine_Speed = SPEED_LOOP_MIN_SPEED + (Speed_value * SPEED_UP_UNIT) /100000;										
				}
    else
		{
		   Expected_Machine_Speed = 0;
		}			

		Expected_elect_speed = Expected_Machine_Speed * MOTOR_POLE_NUMBER;

}

/*******************************************************************************
 �������ƣ�    void Directions_Control(void)
 ����������    ����ת�л�
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2024/6/20      V1.0          Dutch          ����
 *******************************************************************************/
stru_DirChange_Ctr DirChange_Ctr; /* ����ת�л��ṹ�� */

void Directions_Control(void)
{
	//���°�����ɲ����ɲͣ�����Ȼ���ж��Ƿ�ͣ��,ͣ�º�����Ʊ�־λȡ����1000ms�����������򲻱�
	
		DirChange_Ctr.Last_key_status = KEY_DIRECT_CTRL;
//	    DirChange_Ctr.Last_key_status = 1;
	
	  if(DirChange_Ctr.DirChange_Flag == 1)
	{
			DirChange_Ctr.DirChange_Cnt ++;
			if(DirChange_Ctr.DirChange_Cnt > DIR_CHANGE_WAIT_TIME)  //������ʱ,�ȴ�ɲ��
			{
				DirChange_Ctr.DirChange_Cnt = 0;
				DirChange_Ctr.DirChange_Flag = 0;
				mBLDC_CtrProc.bMC_RunFlg = 1;
        mBLDC_CtrProc.Power_on_flg = 1;    //�ϵ�ָ��	
			}
	}

//��־λ����0ʱ���ж�
if(DirChange_Ctr.DirChange_Flag == 0)
 {	
		DirChange_Ctr.MotorRun_Dir = KEY_DIRECT_CTRL;  //��ȡ����״̬
		
		if(DirChange_Ctr.MotorRun_Dir != BLDC_SensorlessCtr.motorDirect)
		   {
			    DirChange_Ctr.DirChange_Cnt ++;
		   }
	  else 
		{
			DirChange_Ctr.DirChange_Cnt = 0;		
		}

		
    if(DirChange_Ctr.DirChange_Cnt > 100)  //�˲�100ms
		{
			mBLDC_CtrProc.bMC_RunFlg = 0;      //����ָ��
			mBLDC_CtrProc.Power_on_flg = 0;    //�ϵ�ָ��
			
			DirChange_Ctr.DirChange_Flag = 1;
			DirChange_Ctr.DirChange_Cnt = 0;

			BLDC_SensorlessCtr.motorDirect = DirChange_Ctr.MotorRun_Dir;  //���ķ���
			
		}

 }
		
}

/*******************************************************************************
 �������ƣ�    uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 ����������    GPIO��ƽ��ת����
 ���������    ��Ҫ��ת��ָ������
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg;
    reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); //��GPIO��ƽ
    if (reg)
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin);
        return 0;
    }
    else
    {
        GPIO_SetBits(GPIOx, GPIO_Pin);
        return 1;
    }
}

/*******************************************************************************
 �������ƣ�    void Start_Up_Test(void)
����������    �Զ���ͣ����:���β���������4S��ػ���4S�󿪻�������ѭ��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2025/1/10      V1.0           Dutch              ����
 *******************************************************************************/
u32 Start_Test_CNT;  //������
u32 StartUp_Test_Time; //�������Դ���
u32 StartUp_Error_Time; //����ʧ�ܴ���
void Start_Up_Test(void)
{
    if((StartUp_Test_Time < START_TEST_TIME)&&(mBLDC_CtrProc.sys_error_flg == 0))
  {
    
    if((mBLDC_CtrProc.sys_error_flg == 0)&&(mBLDC_CtrProc.eSysState == RUN))  //�Ѿ�����
    {
       Start_Test_CNT++;      
       if(Start_Test_CNT > START_WORK_TIME)
       {
           Speed_value = 50;
           Start_Test_CNT = 0;
//           StartUp_Test_Time++; 
       }           
    }
    
    if((mBLDC_CtrProc.sys_error_flg == 0)&&(mBLDC_CtrProc.eSysState == IDLE))  //�Ѿ��ػ�
    {
       Start_Test_CNT++;      
       if(Start_Test_CNT > START_DELAY_TIME)
       {
           Speed_value= MANUAL_SPEED;
           Start_Test_CNT = 0;
           StartUp_Test_Time++; 
       }           
    }
    
        
  }
  
  else 
  { 
    Speed_value = 50 ;  //�ػ�
//    StartUp_Test_Time = 0;   ������
    StartUp_Error_Time++;
    
  }
    
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
