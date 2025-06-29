/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Protect.c
 * 文件标识：
 * 内容摘要： 程序保护函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
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
 函数名称：    u16 procHander(u16 hallbarADvalue)
 功能描述：    扳机输入滤波
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
u16 procHander(u16 hallbarADvalue)
{   /* 返回手把信号的值*/
    static u16 adjFilter1;
    u16 tempChar;

    hallbarADvalue = hallbarADvalue & 0xfff;
    if (hallbarADvalue & 0x800)
    {
        hallbarADvalue = 0;
    }
    tempChar = (u16)(((hallbarADvalue + (u32) adjFilter1 * 7)) >> 3); /* 数据滤波 */
		adjFilter1 = tempChar;
    return (tempChar);
}

/*******************************************************************************
 函数名称：    void Speed_control(void)
 功能描述：    扳机输入与占空比之间转换
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
volatile u16 Speed_value;
volatile u32 Powr_value;

//volatile u32 KEYSET=2;


volatile u16 Start_cnt;
volatile u32 Expected_elect_speed;    //速度环电转速目标值 EXPECTED_ELECT_SPEED
volatile u32 Expected_Machine_Speed;  //速度环机械转速目标值
void Speed_control(void)
{
	  Speed_value = procHander((u16) mBLDC_CtrProc.nSpeed_ADC);
	
#if (LKSSCOPE_START_FUNCTION == ENABLE_FUNCTION)		
			if(mBLDC_CtrProc.bMC_RunFlg == 1 )      //上位机控制启动，手动将 bMC_RunFlg 置1
			{
				 mBLDC_CtrProc.Power_on_flg = 1;
				 Speed_value= MANUAL_SPEED ;          //手动控制转速
			}
			else 
			{
			mBLDC_CtrProc.Power_on_flg = 0;
			Speed_value=10;	
			}
#endif	

if(DirChange_Ctr.DirChange_Flag == 0)  //正反转已完成
{	
//旋钮启动

#if (START_UP_TEST_FUNCTION == ENABLE_FUNCTION)
  Start_Up_Test();
#endif 
	
	  if(Speed_value > START_THRESHOLD_ADC)
		{
			if(Start_cnt < 30)
			{//启动信号滤波
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
//			//顺风起功能
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
				//顺风起结束
			}
			else
			{
		
				if(Speed_value < SPEED_UP_ADC)
				{
				 Powr_value = START_POWER;
				}
				else
				{	
//扳机调速占空比模式					
#if (TRIGGER_CONTROL_MODE == TRIGGER_DUTY_CONTROL)								
			Speed_value = Speed_value - SPEED_UP_ADC;					
			Powr_value = Speed_value * SPEED_UP_RATIO;  //调速不柔和，线性上升
			Powr_value += (s32)((Speed_value * FRAC16(0.06))) >> 15;
			Powr_value += START_POWER;
#endif


//定速速度环					
#if (SPEED_LOOP_FUNCTION == ENABLE_FUNCTION)			 //定速速度环			
			      PIParmS.qInMeas = Speedgetting.Elect_Speed;   //电机电转速当前值, 单位：HZ
					  Expected_elect_speed = EXPECTED_ELECT_SPEED;//速度环电转速目标值, 单位：HZ
						Expected_Machine_Speed = EXPECTED_MACHINE_SPEED; //速度环机械转速目标值, 单位：RPM
#if (TRIGGER_CONTROL_MODE == TRIGGER_SPEED_CONTROL)		 //扳机速度环调速模式  						
            Trigger_Speedloop_Control();
#endif							
			      PIParmS.qInRef  = Expected_elect_speed;   
			      CalcPI(&PIParmS); 					
					  PIParmS.qOut = Limit_Output(PIParmS.qOut, MIN_DUTY, MAX_DUTY);  //输出限幅:	限制在	 MIN_DUTY-MAX_DUTY 之间   
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


//u16 power_DEC_STEP = 30, power_UP_STEP = 100;   /*占空比减速/加速步长 */
//volatile u16 closePowerCnt; /* 关机时间计数 */
void speed_ref_ramp(void)
{
    u16 t_power;
    s16 t_value;

	
	if(mBLDC_CtrProc.sys_error_flg)
	{/*系统故障，禁止输出*/
       StopMotorImmdly();
	   mBLDC_CtrProc.nPower = 0;
	}
	
    t_power = mBLDC_CtrProc.nPower;

    if (mBLDC_CtrProc.nRequestPower > t_power)
    {   /* 功率给定斜坡信号加入*/
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
            {   /* 启动前几拍脉冲增大  */
                t_value += HEAVY_LOAD_START;     //支持重载启动
                t_value = Limit_Output(t_value, PWM_PERIOD * FIRST_START_MIN_DUTY, PWM_PERIOD * 0.75);   //启动前三拍的占空比
            }
            else
            {
                BLDC_SensorlessCtr.lowSpeedFlg  = 1;
                t_value = Limit_Output(t_value, PWM_PERIOD * ADC_MODE_MIN_DUTY, PWM_PERIOD * 0.75);    //启动后ADC模式占空比
            }

            BLDC_SensorlessCtr.HFI_pwm_plus = -PWM_PERIOD;
        }
        else
        {
            t_value += BASIC_PWM_VALUE;
            t_value = Limit_Output(t_value, 0, PWM_PERIOD);   //CMP模式占空比
        }
    }
    mBLDC_CtrProc.nBLDC_PWM_value = t_value;
}

/*******************************************************************************
 函数名称：    void Clear_error(void)
 功能描述：    故障清除函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
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
 函数名称：    void Vol_protect(void)
 功能描述：    故障清除函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
void Vol_protect(void)
{
    static u16 LowVolatageCnt;
	  static u16 LowVolatageCnt_1;
	  static u16 OvrVolatageCnt;		
		
	if(mBLDC_CtrProc.bMC_RunFlg)
	{/*运行过程中欠压*/
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
		{/*开机之前欠压*/
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
		{/*过压保护*/
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
 函数名称：    void Block_error(void)
 功能描述：    故障清除函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/	 
void Block_error_Rev(void)
{
	  //堵转重启，堵转后停机 STALL_FAULT_RECOVER_TIME 秒，清除堵转错误，准备第一次重启，
	  //如果堵转则继续开始堵转重启，一共重启 STALL_NUMBER 次，如果有限次数都启动失败，则继续保持堵转错误，不再重启
    if(mBLDC_CtrProc.sys_error_flg == BLOCK_ERROR)
        {

				if((Fault_Stall_Rev.RecoverTime < STALL_NUMBER) || (STALL_NUMBER_STATUS) )   //
				{
					if(Fault_Stall_Rev.RecoverCnt < STALL_FAULT_RECOVER_TIME)   //2s后清零堵转故障标志位
						
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
//					 Fault_Stall_Rev.RecoverTime = 0;  //堵转次数归零
//					 Fault_Stall_Rev.RecoverCnt = 0;   //计数器复位
//				}	
				
	    }
	 	
		else
		{
			Fault_Stall_Rev.RecoverTime = 0;  //堵转次数归零
			Fault_Stall_Rev.RecoverCnt = 0;   //计数器复位
		}	

}


/*******************************************************************************
 函数名称：    void Motor_Block_Protect(void)
 功能描述：    电机堵转保护函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
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
						{/* 2s报堵转*/
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
 函数名称：    void key_in_proc(void)
 功能描述：    按键输入滤波函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
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
    {   /* A端口输入处理 */
        if(PORTA_InputCnt < KEYIN_FILTER_TIME)
        {
            PORTA_InputCnt++;
        }
        else
        {
            if(hInputPort_State != old_PortA_State)
            {   /* 捕捉信号跳变时刻 */
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
 函数名称：    void Dely_Turn_Off(void)
 功能描述：    延时断电
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
void Dely_Turn_Off(void)
{
  static u16 turn_off_cnt;
	if(( mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.eSysState == IDLE))
	{//扳机松掉后延时断电
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
 函数名称：    void Flash_write(void)
 功能描述：    Flash擦写函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
typedef struct
{   
    u32 test1; /* falsh写入数据*/
    u32 test2;
	  u32 test3;
	  u8 buffer[500];
}FlashParamaStruct;

//volatile u32 flash_ts1,flash_ts2,flash_ts3;

//volatile u16 test_1,test_cnt;
//volatile const FlashParamaStruct struFlashParama __at(MEMORY_DATA_ADDR) =
//{
//    20,30,40, /*初始值*/
//};
//u32 t_FlashBuf[3] = {0,0,0,};  //需定u32类型

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
//					__enable_irq(); /* FLASH写入函数*/
//				
//			}
//			flash_ts1 = struFlashParama.test1;
//			flash_ts2 = struFlashParama.test2;
//			flash_ts3 = struFlashParama.test3;
///*falsh write test*/
//}

/*******************************************************************************
 函数名称：    OVER_current_protect(void)
 功能描述：    分级限流
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
volatile u16 over_current_time1,over_current_time2,over_current_time3;
void OVER_current_protect(void)
{
   if(mBLDC_CtrProc.eSysState == RUN)
	 {
	    if(BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_FIRST_THD)
			{/*第一级限流*/
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
			{/*第二级限流*/
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
		{ /*第三级限流*/
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
 函数名称：    LED_display(void)
 功能描述：    LED显示
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
volatile u8  LED_flicker_flg,LED_state_flg;
volatile u16 Light_ON_cnt,Light_OFF_cnt;
volatile u16 Light_OFF_time; 
volatile u8  LED_light_cnt;//LED闪烁次数计数
void LED_display(void)
{
	if(mBLDC_CtrProc.Power_on_flg == 0)
	{//开关关闭状态时LED常亮
	   LED_ON();
		 LED_state_flg = 1;
		 LED_flicker_flg = 0;
		 Light_OFF_time = LED_OFF_TIME;
	}
	else
	{/*开关闭合时有故障，LED闪烁报警，若无故障，LED常亮*/		
	
			LED_flicker_setting();
		
	   if(mBLDC_CtrProc.sys_error_flg)
		 {//开关关闭状态有故障，LED闪烁指示
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
		 {//开关闭合状态无故障，常亮		 
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
	 {/*LED熄灭时间计时*/
	   Light_OFF_cnt++;
		 LED_OFF();
     LED_state_flg = 0;
     Light_ON_cnt = 0;		 
	 }
	 else
	 {
		  if(Light_ON_cnt < LED_ON_TIME)
			{/*LED亮计时*/
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
					 Light_OFF_time = LED_OFF_TIME;   /* 闪烁周期内LED熄灭时间 */
				 }
         else
         {
				   LED_light_cnt = 0;
					 Light_OFF_time = LED_PERIOD_DELAY; /* 完成闪烁周期后LED熄灭时间 */
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
 函数名称：    void TEMP_protect(void)
 功能描述：    MOS温度保护函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
 *******************************************************************************/
volatile u16 Over_MOStemp_Cnt,Over_BATtemp_Cnt;
volatile u32 mos_tmp_test,mos_RSM_test;
void TEMP_protect(void)
{
//	mos_tmp_test = MOS_TEMP_OVER_THD;
//	mos_RSM_test = RSM_MOS_TEMP_OVER_THD;
    if(mBLDC_CtrProc.nNTC_Vol_ADC < MOS_TEMP_OVER_THD)
    {   /* MOS过温 */
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
        {   /* 扳机不松，过温故障不清零 */
            mBLDC_CtrProc.sys_error_flg &= ~MOS_OVER_ERROR;
        }
    }
		
    if(mBLDC_CtrProc.BAT_NTC_adc < BAT_TEMP_OVER_THD)
    {   /* BAT过温 */
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
        {   /* 扳机不松，过温故障不清零 */
            mBLDC_CtrProc.sys_error_flg &= ~BAT_OVER_ERROR;
        }
    }				

}

/*******************************************************************************
 函数名称：  void Speed_Getting(void)
 功能描述：  速度获取    S=60F/N    
 其它说明：  N=60F/S    N： 极对数   F：电机速度电频率   S：电机机械速度    
 修改日期    版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/5/26      V1.0           LSL
 *******************************************************************************/
stru_Speedgetting_Ctr Speedgetting; /* 速度获取结构体 */ 

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
 函数名称：    void Phase_Drop_Protect(void)
 功能描述：    缺相检测函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Howlet Li          创建
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
 函数名称：    void Trigger_Speedloop_Control(void)
 功能描述：    扳机速度环调速模式
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/6/5      V1.0           Dutch             创建
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
 函数名称：    void Directions_Control(void)
 功能描述：    正反转切换
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/6/20      V1.0          Dutch          创建
 *******************************************************************************/
stru_DirChange_Ctr DirChange_Ctr; /* 正反转切换结构体 */

void Directions_Control(void)
{
	//按下按键先刹车，刹停电机，然后判断是否停下,停下后方向控制标志位取反，1000ms后启动，否则不变
	
		DirChange_Ctr.Last_key_status = KEY_DIRECT_CTRL;
//	    DirChange_Ctr.Last_key_status = 1;
	
	  if(DirChange_Ctr.DirChange_Flag == 1)
	{
			DirChange_Ctr.DirChange_Cnt ++;
			if(DirChange_Ctr.DirChange_Cnt > DIR_CHANGE_WAIT_TIME)  //换向延时,等待刹车
			{
				DirChange_Ctr.DirChange_Cnt = 0;
				DirChange_Ctr.DirChange_Flag = 0;
				mBLDC_CtrProc.bMC_RunFlg = 1;
        mBLDC_CtrProc.Power_on_flg = 1;    //上电指令	
			}
	}

//标志位等于0时不判断
if(DirChange_Ctr.DirChange_Flag == 0)
 {	
		DirChange_Ctr.MotorRun_Dir = KEY_DIRECT_CTRL;  //读取按键状态
		
		if(DirChange_Ctr.MotorRun_Dir != BLDC_SensorlessCtr.motorDirect)
		   {
			    DirChange_Ctr.DirChange_Cnt ++;
		   }
	  else 
		{
			DirChange_Ctr.DirChange_Cnt = 0;		
		}

		
    if(DirChange_Ctr.DirChange_Cnt > 100)  //滤波100ms
		{
			mBLDC_CtrProc.bMC_RunFlg = 0;      //开机指令
			mBLDC_CtrProc.Power_on_flg = 0;    //上电指令
			
			DirChange_Ctr.DirChange_Flag = 1;
			DirChange_Ctr.DirChange_Cnt = 0;

			BLDC_SensorlessCtr.motorDirect = DirChange_Ctr.MotorRun_Dir;  //更改方向
			
		}

 }
		
}

/*******************************************************************************
 函数名称：    uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 功能描述：    GPIO电平反转函数
 输入参数：    需要反转的指定引脚
 输出参数：    无
 返 回 值：    无
 其它说明：
 
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg;
    reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); //读GPIO电平
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
 函数名称：    void Start_Up_Test(void)
功能描述：    自动启停函数:单次测试启动后4S后关机，4S后开机，往复循环
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2025/1/10      V1.0           Dutch              创建
 *******************************************************************************/
u32 Start_Test_CNT;  //计数器
u32 StartUp_Test_Time; //计数测试次数
u32 StartUp_Error_Time; //启动失败次数
void Start_Up_Test(void)
{
    if((StartUp_Test_Time < START_TEST_TIME)&&(mBLDC_CtrProc.sys_error_flg == 0))
  {
    
    if((mBLDC_CtrProc.sys_error_flg == 0)&&(mBLDC_CtrProc.eSysState == RUN))  //已经启动
    {
       Start_Test_CNT++;      
       if(Start_Test_CNT > START_WORK_TIME)
       {
           Speed_value = 50;
           Start_Test_CNT = 0;
//           StartUp_Test_Time++; 
       }           
    }
    
    if((mBLDC_CtrProc.sys_error_flg == 0)&&(mBLDC_CtrProc.eSysState == IDLE))  //已经关机
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
    Speed_value = 50 ;  //关机
//    StartUp_Test_Time = 0;   不清零
    StartUp_Error_Time++;
    
  }
    
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
