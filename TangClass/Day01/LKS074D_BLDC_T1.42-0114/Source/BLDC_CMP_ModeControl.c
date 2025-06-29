/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： BLDC_CMP_ModeControl.c
 * 文件标识：
 * 内容摘要： 比较器模式下BLDC SensorLess换相控制相关函数
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

void blank_Check(void);
extern volatile u32 CMP_delay,CMP_speed,SYSTICK_flg;
void BLDC_CMP_ModeControl(void)
{
   u32 t_zeroCrossValue;  /* 当前换相时间，局部变量 */
    volatile u8 t_i;
    s16 t_ealyComm_Time;  /* 提前换相时间 */

    u8 t_CMP_FailCnt;
	
//	  u8 CMP_fail_cnt = 0;

    if(CMP_IF & BIT1)
    {
        CMP_IF = BIT1;
//        CMP_fail_cnt = 0;
//        for (t_i = 0; t_i < 4; t_i++)
//        {
//            if (CMP_DATA & BIT1)
//            {
//                CMP_fail_cnt++;
//            }
//        }
//        if (CMP_fail_cnt > 2)
//        {
//            StopMotorImmdly();
//            mBLDC_CtrProc.sys_error_flg |= SHORT_ERROR;
//        }
    }


    t_CMP_FailCnt = 0;
    if(CMP_IF & BIT0)
    {   /* 比较器0中断标志 */
        CMP_IF = BIT0;

        if(CMP0_IE_STATE()) /* 判断当前比较器中断是否打开 */
        {   // 过零点检测

            t_zeroCrossValue = (u32)(HALL0_CNT);

            if( mBLDC_CtrProc.nWork_mode == BLDC_MODE_CMP )
            {

                if (t_zeroCrossValue > (BLDC_SensorlessCtr.minCommcationTime))
                {
                    if (CMP0_POL_STATE()) // 比较器0极性选择
                    {
                        for (t_i = 0; t_i < 15; t_i++)
                        {
                            if (CMP0_OUT_LEVEL() == 0)
                            {   /* 比较器0输出结果 */
                                t_CMP_FailCnt++;
                            }
                        }

                        t_ealyComm_Time = EALY_COMM_TIME_RISE;
                    }
                    else
                    {
                        for (t_i = 0; t_i < 15; t_i++)
                        {
                            if(CMP0_OUT_LEVEL())
                            {
                                t_CMP_FailCnt++;
                            }
                        }

                        t_ealyComm_Time = EALY_COMM_TIME_FALL;
                    }
                    if ( t_CMP_FailCnt >= 10)
                    {
                        s32 t_crossAdjValue;


                        t_crossAdjValue = t_zeroCrossValue;
                        BLDC_SensorlessCtr.minCommcationTime = t_zeroCrossValue >> 1;

                        BLDC_SensorlessCtr.blankEndFlg = 0;

                        t_crossAdjValue += t_ealyComm_Time;


                        t_zeroCrossValue = (HALL0_CNT - BLDC_SensorlessCtr.SpeedTimerCnt);

                        t_crossAdjValue -= t_zeroCrossValue;

                        t_crossAdjValue -= BLDC_SensorlessCtr.wBlankTime;


                        t_crossAdjValue = Limit_Output(t_crossAdjValue, 200, 200000);


                        if(t_crossAdjValue > STARTUP_HAlL_COMM_TIMEEX)
                        {
                            t_crossAdjValue = STARTUP_HAlL_COMM_TIMEEX;
                            BLDC_SensorlessCtr.minCommcationTime = STARTUP_HAlL_COMM_TIME;
                        }
												
						SYSTICK_flg = 0;
												
                        SysTick->CTRL = 0x0;
                        SysTick->VAL = 0;
                        SysTick->LOAD = 0;
                        SysTick->LOAD = t_crossAdjValue;
                        SysTick->VAL = 0;
                        SysTick->CTRL = 0x07;



                        BLDC_SensorlessCtr.SpeedTimerCnt = (BLDC_SensorlessCtr.SpeedTimerCnt + HALL0_CNT) >> 1;

                        if(BLDC_SensorlessCtr.motorDirect == 0)
                        {
                            if (BLDC_SensorlessCtr.communicateStep > 1)
                            {
                                BLDC_SensorlessCtr.communicateStep--;
                            }
                            else
                            {
                                BLDC_SensorlessCtr.communicateStep = 6;
                                // 当前换相电角度位置
                            }
                        }
                        else
                        {
                            if (BLDC_SensorlessCtr.communicateStep < 6)
                            {
                                BLDC_SensorlessCtr.communicateStep++;
                            }
                            else
                            {
                                BLDC_SensorlessCtr.communicateStep = 1;
                            }
                        }

                        if((mBLDC_CtrProc.eSysState != RUN) && (BLDC_SensorlessCtr.onTheFlyFlg == 0))
                        {
                            mBLDC_CtrProc.nWork_mode = BLDC_MODE_ADC;
                            BLDC_SensorlessCtr.OpenLoopStepCnt = 0;
                        }
                        CMP0_IE_DISABLE(); /* 比较器中断使能关闭 */
                    }

                }
            }
            else if( mBLDC_CtrProc.nWork_mode == BLDC_MODE_ADC )
            {
                CMP0_IE_DISABLE() ; /* 比较器中断使能关闭 */
            }
        }
    }
}

void BLDC_DelayCommunication(void)
{
    SysTick->CTRL = 0x0;
	
	  if(SYSTICK_flg == 1)
	  {						
		CMP_speed = BLDC_SensorlessCtr.SpeedTimerCnt;
		BLDC_SensorlessCtr.SpeedTimerCnt = 2;
			 
		blank_Check();
				
		CMP_IF = BIT0;
        if(BLDC_SensorlessCtr.EabsFlg == 0)
        {
            CMP_IE |= BIT0;
        }
				
	    BLDC_SensorlessCtr.SpeedTimerCnt = CMP_speed;
				
		BLDC_SensorlessCtr.blankEndFlg = 1;
				
		SYSTICK_flg = 0;
					
	  }
	  else
	  {
		if(BLDC_SensorlessCtr.ctrState == 0)
		{
		  BLDC_SensorlessCtr.ctrState = 1;
		}

		BLDC_Communication();
		if(BLDC_SensorlessCtr.ctrState == 1)
		{
		  BLDC_SensorlessCtr.ctrState = 2;
		}
	  }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

