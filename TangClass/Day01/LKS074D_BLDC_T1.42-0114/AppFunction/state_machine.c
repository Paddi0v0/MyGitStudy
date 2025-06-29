/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� state_machine.c
 * �ļ���ʶ��
 * ����ժҪ�� state machine
 * ����˵���� ��
 * ��ǰ�汾�� V1.0
 * ��    �ߣ� LSL
 * ������ڣ� 2022/5/30
 *
 *******************************************************************************/
#include "state_machine.h"
#include "MC_parameter.h"
#include "Global_Variable.h"
#include "hardware_init.h"
#include "bldc_control.h"
#include "ON_fly_start.h"

void ON_fly_Duty_cala(void);
void ON_fly_Start(void);
void RUN_StateProper(void);
void Phase_Drop_Protect(void);
void Eabs_Control(void);

/*******************************************************************************
 �������ƣ�    void Sys_State_Machine(stru_FOC_CtrProcDef *this)
 ����������    ϵͳ״̬�� ���״̬��״̬�л�����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Sys_State_Machine(void)
{
  switch (mBLDC_CtrProc.eSysState)
  {
    case IDLE:
    {/* ����״̬ */

        if (mBLDC_CtrProc.bMC_RunFlg)
        {
            BLDC_Init();
			
			#if ON_FLY_START_FUNCTION
				mBLDC_CtrProc.eSysState = ONFLY_START; /* ����˳����״̬ */
			#else
                mBLDC_CtrProc.eSysState = POS_SEEK;    /* ���붨λ״̬ */
			#endif			
        }
        break;
    }
    case ONFLY_START:
    {/* ˳���� */
		__disable_irq();
		
		ON_FLY_Handle();	
		BLDC_SensorlessCtr.onTheFlyFlg = ON_fly.MC_Fly_flg;			
		
        if(BLDC_SensorlessCtr.onTheFlyFlg)
		{
		  ON_fly_Duty_cala();			
		  ON_fly_Start();	
          PWMOutputs(ENABLE);
	      CMP0_IE_ENABLE();
          mBLDC_CtrProc.eSysState = RUN;						
		}
		else
		{					  
          mBLDC_CtrProc.eSysState = POS_SEEK; /* ���붨λ״̬ */						
		}
		__enable_irq();
		
        break;
    }	
    case CHARGE:
    {/* Ԥ��� */
        StateCharge();                         //Ԥ��紦����
        break;
    }
    case INIT:
    {/* ��ʼ��״̬ */

        StateInit();
        RUN_StateProper();
        PWMOutputs(ENABLE);
        mBLDC_CtrProc.eSysState = ALIGN;

        break;
    }
    case POS_SEEK:                            //��ʼλ�ü��״̬
    {

        StatePosSeek();
//		Phase_Drop_Protect();  ȱ�ౣ��
		
		if(mBLDC_CtrProc.sys_error_flg)
		{
		  PWMOutputs(DISABLE);
		  mBLDC_CtrProc.eSysState = WAIT;	
		}
		else
		{
          RUN_StateProper();
          PWMOutputs(ENABLE);
          mBLDC_CtrProc.eSysState = RUN;		
		}

        break ;
    }
    case RUN:
    {   /* ����״̬  */
        StateRun();                           //�ջ�������
        break;
    }
    case BRAKE:
    {   /* ���ɲ��״̬ */
        Eabs_Control();                          //ֹͣ�ж�������
        break;
    }
    case WAIT:
    {   /* �ȴ�״̬ */
		StopMotorImmdly();
        mBLDC_CtrProc.eSysState = IDLE;
        break;
    }
    case FAULT:
    {   /* ����״̬ */
        StateFault();                         //���ϴ�����
        break;
    }
    default:
    {
        mBLDC_CtrProc.eSysState = IDLE; 
        break;
    }
  }

}


/*****************************************************************************
 * ������   : void StateInit()
 * ˵��     : ״̬��ʼ��
 * ���˼· ��1.������ʼ��
 * ����     ����
 * ����ֵ   ����
 * �޸�ʱ�� ��2020.08.17
 *****************************************************************************/
void StateInit(void)
{
    BLDC_Init();
}


/*****************************************************************************
 * ������   : void StateCharge(void)
 * ˵��     : Ԥ��纯�������Ծٵ��ݽ���Ԥ��磬���ڲ�ͬ��Ӳ��Ҫע�����Ԥ���ʱ��
 * ���˼· �����δ�A�ࡢB�ࡢC�����ţ����Ծٵ��ݳ�硣
 * ����     ����
 * ����ֵ   ����
 * �޸�ʱ�� ��2020.08.17
 *****************************************************************************/
void StateCharge(void)
{

}

/*****************************************************************************
 * ������   : void StatePosSeek(void)
 * ˵��     : ��ʼλ�ü����򣬵����ֹ״̬�������Ƕ�
 * ���˼· ����������ע�뷽ʽ���������ֹ״̬�ĵ�Ƕ�
 * ����     ����
 * ����ֵ   ����
 * �޸�ʱ�� ��2020.08.17
 *****************************************************************************/
void StatePosSeek(void)
{
    mIPD_CtrProc.bIPD_State = 2;
    mIPD_CtrProc.bIPD_StepFlg = 0;
	  mIPD_CtrProc.Seek_result = 0;

    mIPD_CtrProc.wIPD_PlusWidthSet = IPD_PLUS_TIME_WIDTH;    /* ����ע���� */
    mIPD_CtrProc.wIPD_IdleWaitSet = IPD_PLUS_WAIT_TIME;      /* ����ע��󣬵���˥������ȴ�ʱ������ */
    mIPD_CtrProc.nPWM_PERIOD = PWM_PERIOD;

    ADC1_SOFTWARE_TRIG_ONLY();          
    ADC1_STATE_RESET(); 
    
    __disable_irq();                  /* �ر��ж� �ж��ܿ��� */
    BLDC_SensorlessCtr.lowSpeedFlg = 0;
    IPD_RotorPosEst();                /* 6����ע�룬��ʼλ�ü�� */
	if(MCPWM0_EIF & BIT5)
	{
	  mBLDC_CtrProc.sys_error_flg |= SHORT_ERROR;  
	}
    __enable_irq();                  /* �������ж� */

    ADC_init();                      /* ADC��ʼ�� */
    MCPWM_init();                    /* PWM��ʼ�� */


}


void RUN_StateProper(void)
{
    
    BLDC_SensorlessCtr.ctrState = 0;
    BLDC_SensorlessCtr.minCommcationTime = STARTUP_HAlL_COMM_TIME;


    BLDC_SensorlessCtr.focusCommCnt = 0;
    BLDC_SensorlessCtr.SpeedTimerCnt = 5000;
    BLDC_SensorlessCtr.state = 0;
    BLDC_SensorlessCtr.lowSpeedFlg = 1;
	
	  BLDC_SensorlessCtr.HallState = mIPD_CtrProc.Seek_result;

    BLDC_SensorlessCtr.current_commStep = BLDC_SensorlessCtr.HallState;
    BLDC_SensorlessCtr.communicateStep = BLDC_SensorlessCtr.current_commStep;
    BLDC_SensorlessCtr.HfiCurrStep = BLDC_SensorlessCtr.current_commStep;
//    calcNextComm_BefComm(BLDC_SensorlessCtr.current_commStep);
	Speedgetting.Provid_time = 300000000;
	UTIMER1_CNT = 0;
    Speedgetting.communicate_cnt = 0;
    BLDC_Communication();

    BLDC_SensorlessCtr.blankEndFlg = 1;
    BLDC_SensorlessCtr.OpenLoopStepCnt = 0;

}


/*****************************************************************************
 * ������   : void StateOpen(void)
 * ˵��     : ���run״̬�������һ��Ϊ�ٶȻ������ʻ��Ĵ���
 * ���˼· ��1.����ʵ�ʸ��ؼ����ٶ�/����/���������¡��ٶȻ�/���ʻ���PI       \
 * ����     ����
 * ����ֵ   ����
 * �޸�ʱ�� ��2020.08.17
 *****************************************************************************/
void StateRun(void)
{
    if((mBLDC_CtrProc.bMC_RunFlg)== 0)
    {
        mBLDC_CtrProc.eSysState = WAIT;
    }
}

/*****************************************************************************
 * ������   : void StateFault(void)
 * ˵��     : ����״̬����Ҫ�ǽ��й���״̬����������
 * ���˼· ��1.�ڹ���״̬�������⵽������ʧ��������stru_Faults��Ӧ����λ��\
 * ����     ����
 * ����ֵ   ����
 * �޸�ʱ�� ��2020.08.17
 *****************************************************************************/
void StateFault(void)
{
    PWMOutputs(DISABLE);


}

/*****************************************************************************
 * ������   : void StateStop(void)
 * ˵��     : ���ֹͣ�������жϵ���Ƿ�ֹ״̬
 * ���˼· ��1.ͨ��mOnTheFlyDetect.bMotorStopDecFlag��״̬���жϵ���Ƿ��ھ�ֹ״̬�����ж����
                ��ֹ��ȥ���г�ʼλ�ü�����Ԥ��λ����
 * ����     ����
 * ����ֵ   ����
 * �޸�ʱ�� ��2020.08.17
 *****************************************************************************/
void StateStop(void)
{


}


void ON_fly_Start(void)
{  
    BLDC_SensorlessCtr.minCommcationTime = ON_fly.fly_step_time >> 2;
    BLDC_SensorlessCtr.SpeedTimerCnt = BLDC_SensorlessCtr.minCommcationTime;
	
	BLDC_SensorlessCtr.focusCommCnt = 0;
    BLDC_SensorlessCtr.state = 0;

//    calcNextComm_BefComm(BLDC_SensorlessCtr.current_commStep);
	BLDC_SensorlessCtr.lowSpeedFlg = 0;
    ON_fly.ON_Fly_delay_time = HALL0_CNT;
	
	if(ON_fly.ON_Fly_delay_time < ON_fly.fly_step_time)
	{
	  ON_fly.communicate_delay_time = ON_fly.fly_step_time - ON_fly.ON_Fly_delay_time  - 1000;
	  BLDC_SensorlessCtr.current_commStep = ON_fly.fly_start_step;
	  bldc_comm_process(0);		
      HALL0_CNT = 0;
	  while(HALL0_CNT < ON_fly.communicate_delay_time)
	  {
	    ;
	  }
      		
	}
	else
	{
	  BLDC_SensorlessCtr.current_commStep = ON_fly.fly_start_step;
	  bldc_comm_process(0);	  
	}
		
	BLDC_SensorlessCtr.HallState = BLDC_SensorlessCtr.current_commStep;	
    BLDC_SensorlessCtr.current_commStep = BLDC_SensorlessCtr.HallState;
    BLDC_SensorlessCtr.communicateStep = BLDC_SensorlessCtr.current_commStep;
    BLDC_SensorlessCtr.HfiCurrStep = BLDC_SensorlessCtr.current_commStep;	
    BLDC_Communication();	
	mBLDC_CtrProc.nWork_mode = BLDC_MODE_CMP;
    BLDC_SensorlessCtr.blankEndFlg = 1;
    BLDC_SensorlessCtr.OpenLoopStepCnt = 6;	
	
}


void ON_fly_Duty_cala(void)
{ 
  if(BLDC_SensorlessCtr.onTheFlyFlg)
  {
	if(ON_fly.fly_Speed < MOTOR_MIN_SPEED) 
    {
	  ON_fly.duty = ON_fly.ON_Fly_Min_DUTY;	
	}
    else
    {
	  ON_fly.duty_fly = ((ON_fly.fly_Speed - MOTOR_MIN_SPEED) *0.01*PWM_PERIOD)/PER_ONE_DUTY_ADD_SPEED;
	  ON_fly.duty = ON_fly.ON_Fly_Min_DUTY + ON_fly.duty_fly;
	}		
	
	ON_fly.duty = Limit_Output(ON_fly.duty,ON_fly.ON_Fly_Min_DUTY,ON_fly.ON_Fly_Max_DUTY);	  
	  
	mBLDC_CtrProc.nBLDC_PWM_value = ON_fly.duty;

    MCPWM0_PRT = 0x0000DEAD;
    MCPWM0_UPDATE = 0;	
	
    MCPWM0_TH00 = -mBLDC_CtrProc.nBLDC_PWM_value;
    MCPWM0_TH01 = mBLDC_CtrProc.nBLDC_PWM_value;

    MCPWM0_TH10 = -mBLDC_CtrProc.nBLDC_PWM_value;
    MCPWM0_TH11 = mBLDC_CtrProc.nBLDC_PWM_value;

    MCPWM0_TH20 = -mBLDC_CtrProc.nBLDC_PWM_value;
    MCPWM0_TH21 = mBLDC_CtrProc.nBLDC_PWM_value;	
	
	MCPWM0_UPDATE = 0xff;
	MCPWM0_PRT = 0x0000ABCD;
	
	ON_fly.power = ON_fly.duty * 32767/PWM_PERIOD;
	
	mBLDC_CtrProc.nRequestPower = ON_fly.power;			
		
	ON_fly.power = Limit_Output(ON_fly.power, ON_FLY_MIN_POWER, ON_FLY_MAX_POWER);
  }
}


/*****************************************************************************
 * ������   : void Eabs_Control(void)
 * ˵��     : ����ɲ������
 * ���˼· ��
 * ����     ����
 * ����ֵ   ����
 * �޸�ʱ�� ��2022/5/30
 *****************************************************************************/
void Eabs_Control(void)
{
  if(BLDC_SensorlessCtr.Eabs_Founction_Flg)
  {
	
    if((BLDC_SensorlessCtr.EabsFlg) && (mBLDC_CtrProc.nPower == 0))
    {
        BLDC_SensorlessCtr.EabsCnt ++;

        if(BLDC_SensorlessCtr.EabsCnt > EABS_TOTAL_TIME)
        {//�ػ���ɲ��ʱ������
			PWMOutputs(DISABLE);
            BLDC_SensorlessCtr.EabsFlg = 0;					  
        }
        else
        {/*�ػ�����ɲ��*/	
					
		  if(BLDC_SensorlessCtr.Eabs_Slip_Cnt < EABS_SLIP_TIME)
		  {//���ɻ��У�ʱ�䵽�˺���ɲ��
			BLDC_SensorlessCtr.Eabs_Slip_Cnt++;
			PWMOutputs(DISABLE);
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
							  
			BLDC_SensorlessCtr.Eabs_duty = SOFT_EABS_MIN_DUTY;
		  }
		 else
		 {
			if(BLDC_SensorlessCtr.Eabs_Hard_Flg)
			{
				BLDC_SensorlessCtr.EabsPWM = 0;
			}				
			else
            {				
                if(BLDC_SensorlessCtr.Eabs_duty < SOFT_EABS_STEP * 2)			
              	{
				  BLDC_SensorlessCtr.Eabs_duty = 0;
				}		
                else
                {
				  BLDC_SensorlessCtr.Eabs_duty -=  SOFT_EABS_STEP;								
				}			
								
				BLDC_SensorlessCtr.EabsPWM = BLDC_SensorlessCtr.Eabs_duty;
			}
							
			BLDC_SensorlessCtr.EabsPWM = Limit_Output(BLDC_SensorlessCtr.EabsPWM,0,PWM_PERIOD);													
			PWMOutputs(ENABLE);
		}

      }
    }
    else
    {			
	  StopMotorImmdly();
      BLDC_SensorlessCtr.EabsFlg = 0;		
      mBLDC_CtrProc.eSysState = IDLE;			
    }
  }	
  else
  {
    CMP_IE &= ~BIT0;
    StopMotorImmdly();
    BLDC_SensorlessCtr.EabsFlg = 0;					  
    mBLDC_CtrProc.eSysState  = IDLE;
  }	
	
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

