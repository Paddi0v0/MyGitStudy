/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Task_Scheduler.c
 * 文件标识：
 * 内容摘要： 任务调度相关函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： LSL
 * 完成日期： 2023年6月8日
 *******************************************************************************/
#include "basic.h"
#include "global_variable.h"
#include "absacc.h"
#include "MC_Parameter.h"

void LED_flicker_setting(void);
/*******************************************************************************
 函数名称：    u16 procHander(u16 hallbarADvalue)
 功能描述：    扳机输入滤波
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          创建
 *******************************************************************************/
u16 procHander(u16 hallbarADvalue)
{   /* 返回手把信号的值*/
    static u16 adjFilter1;
    u16 tempChar;

    hallbarADvalue = hallbarADvalue & 0xfff;
    if(hallbarADvalue & 0x800)
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
 2023/6/8      V1.0        LSL          创建
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
	  {//启动信号滤波
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
 函数名称：    void speed_ref_ramp(void)
 功能描述：    占空比给定函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          创建
 *******************************************************************************/
volatile u16 power_DEC_STEP = POWER_DEC_STEP, power_UP_STEP = POWER_ADD_STEP;

void speed_ref_ramp(void)
{
    u16 t_power;
    s16 t_value;
	
	if(mBLDC_CtrProc.sys_error_flg)
	{/*系统故障，禁止输出*/
	   mBLDC_CtrProc.nPower = 0;
	}
	
    t_power = mBLDC_CtrProc.nPower;

    if (mBLDC_CtrProc.nRequestPower > t_power)
    {   /* 功率给定斜坡信号加入*/
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
//			t_value -= BACK_PWM_WIDTH;      /* 反向脉冲补偿，增加停止注入反向脉冲时的速度稳定性 */	
//		#endif		

    if(BLDC_SensorlessCtr.EabsFlg == 0)
    {
        if(BLDC_SensorlessCtr.lowSpeedFlg)
        {
            if(BLDC_SensorlessCtr.sCommmStabCnt < 3)
            {   /* 启动前几拍脉冲增大  */
//                t_value += 100;
                t_value = sat(t_value, PWM_PERIOD * 0.12, PWM_PERIOD * 0.35); /* 最小0.18 */
            }
            else
            {
                t_value = sat(t_value, PWM_PERIOD * MIN_DUTY, PWM_PERIOD * 0.75); /* 最小0.18 */
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
 函数名称：    void Clear_error(void)
 功能描述：    故障清除函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          创建
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
// 函数名称：    void Vol_protect(void)
// 功能描述：    故障清除函数
// *******************************************************************************/
//void Vol_protect(void)
//{
//    static u16 LowVolatageCnt;
//	  static u16 LowVolatageCnt_1;
//	  static u16 OvrVolatageCnt;		
//		
//	if(mBLDC_CtrProc.bMC_RunFlg)
//	{/*运行过程中欠压*/
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
//		{/*开机之前欠压*/
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
//		{/*过压保护*/
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
 函数名称：    void Motor_Block_Protect(void)
 功能描述：    电机堵转保护函数
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
						{/* 2s报堵转*/
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
 函数名称：    void key_in_proc(void)
 功能描述：    按键输入滤波函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          创建
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
    {/* A端口输入处理 */
      if(PORTA_InputCnt < KEYIN_FILTER_TIME)
      {
         PORTA_InputCnt++;
      }
      else
      {
        if(hInputPort_State != old_PortA_State)
        {/* 捕捉信号跳变时刻 */
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
// 函数名称：    void Dely_Turn_Off(void)
// 功能描述：    延时断电    
// *******************************************************************************/
//void Dely_Turn_Off(void)
//{
//  static u16 turn_off_cnt;
//	if(( mBLDC_CtrProc.Power_on_flg == 0) && (mBLDC_CtrProc.eSysState == IDLE))
//	{//扳机松掉后延时断电
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
// 函数名称：    OVER_current_protect(void)
// 功能描述：    分级限流
// *******************************************************************************/
//volatile u16 over_current_time1,over_current_time2;
//void OVER_current_protect(void)
//{
//   if(mBLDC_CtrProc.eSysState == RUN)
//	 {
//	    if(BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_FIRST_THD)
//			{/*第一级限流*/
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
//			{/*第二级限流*/
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
// 函数名称：    LED_display(void)
// 功能描述：    LED显示
// *******************************************************************************/
//volatile u8  LED_flicker_flg,LED_state_flg;
//volatile u16 Light_ON_cnt,Light_OFF_cnt;
//volatile u16 Light_OFF_time; 
//volatile u8  LED_light_cnt;//LED闪烁次数计数
//void LED_display(void)
//{
//	if(mBLDC_CtrProc.Power_on_flg == 0)
//	{//开关关闭状态时LED常亮
//	   LED_ON();
//		 LED_state_flg = 1;
//		 LED_flicker_flg = 0;
//		 Light_OFF_time = LED_OFF_TIME;
//	}
//	else
//	{/*开关闭合时有故障，LED闪烁报警，若无故障，LED常亮*/		
//	
//			LED_flicker_setting();
//		
//	   if(mBLDC_CtrProc.sys_error_flg)
//		 {//开关关闭状态有故障，LED闪烁指示
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
//		 {//开关闭合状态无故障，常亮		 
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
//	 {/*LED熄灭时间计时*/
//	   Light_OFF_cnt++;
//		 LED_OFF();
//     LED_state_flg = 0;
//     Light_ON_cnt = 0;		 
//	 }
//	 else
//	 {
//		  if(Light_ON_cnt < LED_ON_TIME)
//			{/*LED亮计时*/
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
//					 Light_OFF_time = LED_OFF_TIME;   /* 闪烁周期内LED熄灭时间 */
//				 }
//         else
//         {
//				   LED_light_cnt = 0;
//					 Light_OFF_time = LED_PERIOD_DELAY; /* 完成闪烁周期后LED熄灭时间 */
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
// 函数名称：    void MOS_TEMP_protect(void)
// 功能描述：    MOS温度保护函数
// *******************************************************************************/
//volatile u16 Over_MOStemp_Cnt,Over_BATtemp_Cnt;
//volatile u32 mos_tmp_test,mos_RSM_test;
//void MOS_TEMP_protect(void)
//{
////	mos_tmp_test = MOS_TEMP_OVER_THD;
////	mos_RSM_test = RSM_MOS_TEMP_OVER_THD;
//    if(mBLDC_CtrProc.nMOS_NTC_ADC < MOS_TEMP_OVER_THD)
//    {   /* MOS过温 */
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
//        {   /* 扳机不松，过温故障不清零 */
//            mBLDC_CtrProc.sys_error_flg &= ~MOS_OVER_ERROR;
//        }
//    }	

//}

///*******************************************************************************
// 函数名称：    void BAT_TEMP_protect(void)
// 功能描述：    电池包温度保护函数
// *******************************************************************************/
//void BAT_TEMP_protect(void)
//{
///* BAT过温保护 */		
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
//        {   /* 扳机不松，过温故障不清零 */
//            mBLDC_CtrProc.sys_error_flg &= ~BAT_OVER_ERROR;
//        }
//    }	
//		
//}

///*******************************************************************************
// 函数名称：    void LKS_Viewer_Init(void)
// 功能描述：    LKS_Viewer初始化
// 修改日期      版本号          修改人            修改内容
// -----------------------------------------------------------------------------
// 2022/5/30      V1.0            LSL               创建
// *******************************************************************************/
//u8 ch1Buffer[512] = {0};
//u8 ch2Buffer[512] = {0};
//int theta = 0;
//int theta2 = 0;

//void LKS_Viewer_Init(void)
//{
//	PRINTF("start lksviewer demo project...\r\n");
//	// 必要代码，初始化使用的缓冲区。通道 0 用于打印输出，这里不用初始化。
//	LKS_VIEWER_DeInit();
//	LKS_VIEWER_InitBuffer(1, ch1Buffer, 512);
//	LKS_VIEWER_InitBuffer(2, ch2Buffer, 512);
//	// 可选。初始化缓冲变量对象，可通过上位机动态修改。?2022 版权归凌鸥创芯所有 机密文件未经许可不得扩散 25
//	LKS_VIEWER_InitVar(1, &theta, sizeof(theta));
//	LKS_VIEWER_InitVar(2, &theta2, sizeof(theta2));

//}



///************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
///* ------------------------------END OF FILE------------------------------------ */
