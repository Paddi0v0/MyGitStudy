#include "Global_Variable.h"
#include "time_process.h"
#include "function_config.h"
#include "hardware_config.h"

/*******************************************************************************
 函数名称：    void Sys_State_Machine(void)
 功能描述：    系统状态机
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/16      V1.0           Howlet Li          创建
 *******************************************************************************/

void Sys_State_Machine(void)
{
    switch (struFOC_CtrProc.eSysState)
    {
    case IDLE:
    {
        if ((struFOC_CtrProc.bMC_RunFlg) && (stru_Faults.R == 0) && (strubreak_eabs.break_flg == 0))
        {
            struFOC_CtrProc.eSysState = INIT;
        }

        struFOC_CtrProc.nQVoltageFir = 0;
        break;
    }

    case INIT:
    {
        MCL_Init(&struFOC_CtrProc);
        PWMOutputs(ENABLE);
        struFOC_CtrProc.eSysState = RUN;
        break;
    }

    case RUN:
    {
        if ((struFOC_CtrProc.bMC_RunFlg == 0) || (stru_Faults.R))
        {
            struFOC_CtrProc.eSysState = STOP;
        }

        break;
    }

    case STOP:
    {
        StopMotorImmdly();
        struFOC_CtrProc.eSysState = WAIT;
        SetTime_TimeOut_Counter(300);
        break;
    }

    case WAIT:
    {
        if (SetTime_IsElapsed() == TRUE)
        {
            struFOC_CtrProc.eSysState = IDLE;
        }

        break;
    }

    default:
        break;
    }
}

/*******************************************************************************
 函数名称：    Task_Scheduler(void)
 功能描述：    任务调度函数
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/2/25      V1.0           Howlet Li          创建
 *******************************************************************************/

void Task_Scheduler(void)
{
    if (struTaskScheduler.nTimeBaseFlg)
    {
        struTaskScheduler.nTimeBaseFlg = 0;

        if (++struTaskScheduler.bTimeCnt1ms == TASK_SCHEDU_1MS) 			/* 一毫秒进一次 */
        {
            struTaskScheduler.bTimeCnt1ms = 0;

            Speed_Power_Pro(&strucontrol_handle); 							/* 转把处理 */

			power_zero_Pro(); 												/* 油门为0 */

			break_state_Pro(); 												/* 刹车 */

			speed_ref_ramp(); 												/* 电机运行处理 */

            Sys_State_Machine(); 											/* 系统状态机 */

            if (strupower_up.power_up_time > 10)
            {
                key_in_proc(); 												/* 外部功能端口 */

                check_Vol_Temp(&stru_VoltageProtect); 						/* 电压检测 */
            }
        }

        if (++struTaskScheduler.nTimeCnt10ms == TASK_SCHEDU_10MS)
        {
            struTaskScheduler.nTimeCnt10ms = 0;

            Motor_Block_Protect(); 											/* 堵转函数处理 */

            Power_Up_Init(); 												/* 上电后初始四秒处理 */
			
            if (MCPWM_EIF & FAIL0_ERROR)
            {
                MCPWM_EIF = 0xffff;
                stru_Faults.B.HardCurretError = 1;
            }

            VoltageRampControl(&struFOC_CtrProc);							/* 母线电压 */

            Flash_Write_Pro(); 												/* flash存储 */
        }
    }
    else
    {
        if (struTaskScheduler.bPWM_UpdateFlg)
        {
            struTaskScheduler.bPWM_UpdateFlg = 0;

            Verify_Hall_State(&struHallProcess);
        }
    }
}




