/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： state_machine.c
 * 文件标识：
 * 内容摘要： state machine
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： LSL
 * 完成日期： 2022/5/30
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
 函数名称：    void Sys_State_Machine(stru_FOC_CtrProcDef *this)
 功能描述：    系统状态机 电机状态各状态切换调度
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Sys_State_Machine(void)
{
  switch (mBLDC_CtrProc.eSysState)
  {
    case IDLE:
    {/* 空闲状态 */

        if (mBLDC_CtrProc.bMC_RunFlg)
        {
            BLDC_Init();
			
			#if ON_FLY_START_FUNCTION
				mBLDC_CtrProc.eSysState = ONFLY_START; /* 进入顺风启状态 */
			#else
                mBLDC_CtrProc.eSysState = POS_SEEK;    /* 进入定位状态 */
			#endif			
        }
        break;
    }
    case ONFLY_START:
    {/* 顺风起 */
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
          mBLDC_CtrProc.eSysState = POS_SEEK; /* 进入定位状态 */						
		}
		__enable_irq();
		
        break;
    }	
    case CHARGE:
    {/* 预充电 */
        StateCharge();                         //预充电处理函数
        break;
    }
    case INIT:
    {/* 初始化状态 */

        StateInit();
        RUN_StateProper();
        PWMOutputs(ENABLE);
        mBLDC_CtrProc.eSysState = ALIGN;

        break;
    }
    case POS_SEEK:                            //初始位置检测状态
    {

        StatePosSeek();
//		Phase_Drop_Protect();  缺相保护
		
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
    {   /* 运行状态  */
        StateRun();                           //闭环处理函数
        break;
    }
    case BRAKE:
    {   /* 电机刹车状态 */
        Eabs_Control();                          //停止判定处理函数
        break;
    }
    case WAIT:
    {   /* 等待状态 */
		StopMotorImmdly();
        mBLDC_CtrProc.eSysState = IDLE;
        break;
    }
    case FAULT:
    {   /* 故障状态 */
        StateFault();                         //故障处理函数
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
 * 函数名   : void StateInit()
 * 说明     : 状态初始化
 * 设计思路 ：1.变量初始化
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
void StateInit(void)
{
    BLDC_Init();
}


/*****************************************************************************
 * 函数名   : void StateCharge(void)
 * 说明     : 预充电函数，对自举电容进行预充电，对于不同的硬件要注意调整预充电时间
 * 设计思路 ：依次打开A相、B相、C相下桥，对自举电容充电。
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
void StateCharge(void)
{

}

/*****************************************************************************
 * 函数名   : void StatePosSeek(void)
 * 说明     : 初始位置检测程序，电机静止状态检测电机电角度
 * 设计思路 ：采用脉冲注入方式，检测电机静止状态的电角度
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
void StatePosSeek(void)
{
    mIPD_CtrProc.bIPD_State = 2;
    mIPD_CtrProc.bIPD_StepFlg = 0;
	  mIPD_CtrProc.Seek_result = 0;

    mIPD_CtrProc.wIPD_PlusWidthSet = IPD_PLUS_TIME_WIDTH;    /* 脉冲注入宽度 */
    mIPD_CtrProc.wIPD_IdleWaitSet = IPD_PLUS_WAIT_TIME;      /* 脉冲注入后，电流衰减到零等待时间设置 */
    mIPD_CtrProc.nPWM_PERIOD = PWM_PERIOD;

    ADC1_SOFTWARE_TRIG_ONLY();          
    ADC1_STATE_RESET(); 
    
    __disable_irq();                  /* 关闭中断 中断总开关 */
    BLDC_SensorlessCtr.lowSpeedFlg = 0;
    IPD_RotorPosEst();                /* 6脉冲注入，初始位置检测 */
	if(MCPWM0_EIF & BIT5)
	{
	  mBLDC_CtrProc.sys_error_flg |= SHORT_ERROR;  
	}
    __enable_irq();                  /* 开启总中断 */

    ADC_init();                      /* ADC初始化 */
    MCPWM_init();                    /* PWM初始化 */


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
 * 函数名   : void StateOpen(void)
 * 说明     : 电机run状态处理程序，一般为速度环、功率环的处理
 * 设计思路 ：1.根据实际负载计算速度/功率/电流的爬坡、速度环/功率环的PI       \
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
void StateRun(void)
{
    if((mBLDC_CtrProc.bMC_RunFlg)== 0)
    {
        mBLDC_CtrProc.eSysState = WAIT;
    }
}

/*****************************************************************************
 * 函数名   : void StateFault(void)
 * 说明     : 故障状态，主要是进行故障状态的重启处理
 * 设计思路 ：1.在故障状态，如果检测到故障消失，则清零stru_Faults对应故障位。\
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
void StateFault(void)
{
    PWMOutputs(DISABLE);


}

/*****************************************************************************
 * 函数名   : void StateStop(void)
 * 说明     : 电机停止函数，判断电机是否静止状态
 * 设计思路 ：1.通过mOnTheFlyDetect.bMotorStopDecFlag的状态来判断电机是否在静止状态，在判定电机
                静止后去进行初始位置检测或者预定位动作
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
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
 * 函数名   : void Eabs_Control(void)
 * 说明     : 电子刹车控制
 * 设计思路 ：
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2022/5/30
 *****************************************************************************/
void Eabs_Control(void)
{
  if(BLDC_SensorlessCtr.Eabs_Founction_Flg)
  {
	
    if((BLDC_SensorlessCtr.EabsFlg) && (mBLDC_CtrProc.nPower == 0))
    {
        BLDC_SensorlessCtr.EabsCnt ++;

        if(BLDC_SensorlessCtr.EabsCnt > EABS_TOTAL_TIME)
        {//关机后刹车时间设置
			PWMOutputs(DISABLE);
            BLDC_SensorlessCtr.EabsFlg = 0;					  
        }
        else
        {/*关机后开启刹车*/	
					
		  if(BLDC_SensorlessCtr.Eabs_Slip_Cnt < EABS_SLIP_TIME)
		  {//自由滑行，时间到了后再刹车
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

