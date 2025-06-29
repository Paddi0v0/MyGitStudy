/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� BLDC_CMP_ModeControl.c
 * �ļ���ʶ��
 * ����ժҪ�� �Ƚ���ģʽ��BLDC SensorLess���������غ���
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

void blank_Check(void);
extern volatile u32 CMP_delay,CMP_speed,SYSTICK_flg;
void BLDC_CMP_ModeControl(void)
{
   u32 t_zeroCrossValue;  /* ��ǰ����ʱ�䣬�ֲ����� */
    volatile u8 t_i;
    s16 t_ealyComm_Time;  /* ��ǰ����ʱ�� */

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
    {   /* �Ƚ���0�жϱ�־ */
        CMP_IF = BIT0;

        if(CMP0_IE_STATE()) /* �жϵ�ǰ�Ƚ����ж��Ƿ�� */
        {   // �������

            t_zeroCrossValue = (u32)(HALL0_CNT);

            if( mBLDC_CtrProc.nWork_mode == BLDC_MODE_CMP )
            {

                if (t_zeroCrossValue > (BLDC_SensorlessCtr.minCommcationTime))
                {
                    if (CMP0_POL_STATE()) // �Ƚ���0����ѡ��
                    {
                        for (t_i = 0; t_i < 15; t_i++)
                        {
                            if (CMP0_OUT_LEVEL() == 0)
                            {   /* �Ƚ���0������ */
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
                                // ��ǰ�����Ƕ�λ��
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
                        CMP0_IE_DISABLE(); /* �Ƚ����ж�ʹ�ܹر� */
                    }

                }
            }
            else if( mBLDC_CtrProc.nWork_mode == BLDC_MODE_ADC )
            {
                CMP0_IE_DISABLE() ; /* �Ƚ����ж�ʹ�ܹر� */
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

