#include "Global_Variable.h"
#include "hardware_config.h"
#include "MC_hall.h"
#include "function_config.h" 

/*******************************************************************************
 函数名称：    void TIMER0_IRQHandler(void)
 功能描述：    TIMER0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void UTIMER0_IRQHandler(void)
{	/* 时基500us */
    UTIMER_IF = 0x07;

    if (struFOC_CtrProc.nSetTimeLeftCnt)
    {
        struFOC_CtrProc.nSetTimeLeftCnt--;
    }

    struTaskScheduler.nTimeBaseFlg = 1;
}

/*******************************************************************************
 函数名称：    void HALL_IRQHandler(void)
 功能描述：    HALL中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void HALL_IRQHandler(void)
{
	HALL_IRQProcess(&struHallProcess);
}

/*******************************************************************************
 函数名称：    void ADC0_IRQHandler(void)
 功能描述：    ADC0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void ADC0_IRQHandler(void)
{
    ADC0_IF |= BIT1 | BIT0;

    struFOC_CtrProc.nSys_TimerPWM++;

    struHallProcess.wHallPWMTimerCnt++;

    struTaskScheduler.bPWM_UpdateFlg = 1; 									/* PWM更新标志 */

    struFOC_CtrProc.struFOC_CurrLoop.nBusCurrentadc = ((s16)(GET_BUS_ADC_RESULT) - struFOC_CtrProc.struFOC_CurrLoop.nBusCurrentOffset);  	/* 母线电流 */
    struFOC_CtrProc.struFOC_CurrLoop.nBusCurrentadcfir = lowPass_filter(&struFOC_CtrProc.struBusCurr_RC, struFOC_CtrProc.struFOC_CurrLoop.nBusCurrentadc);

    struFOC_CtrProc.struFOC_CurrLoop.nBusVoltage = GET_BUS_VOL_ADC_RESULT; 	/* 母线电压 */

    strucontrol_handle.hand_speed_adc = GET_SPEED_ADC_RESULT; 				/* 转把电压 */
	
	Hall_ElecAnglePWM_Process(&struHallProcess); 							/* HALL角度处理 */

    if (struFOC_CtrProc.eSysState == RUN)
    {
		FOC_Model(&struFOC_CtrProc);
    }
    else
    {  
        ADC0_CHN2 = ADC0_3th_MSK | ADC1_3th_MSK;
        ADC0_CHN3 = ADC0_4th_MSK | ADC1_4th_MSK;
		
		if (struHallProcess.bCloseLoopAngleFlg)
		{
			closeLoopAnglePLL(&struHallProcess);
		}
		else
		{
			reduceToqueAnglePll(&struHallProcess);
		}
    }
}

/*******************************************************************************
 函数名称：    void CMP_IRQHandler(void)
 功能描述：    比较器中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void CMP_IRQHandler(void)
{
    if(CMP_IF & (BIT0 | BIT1))
    {
        volatile u8 t_i, t_cnt;

        CMP_IF = BIT0 | BIT1;
        t_cnt = 0;
        for(t_i = 0; t_i < 5; t_i++)
        {
#if (CMP_CHOICE == 0)
			if(SYS_AFE_CMP & BIT14)
            {
                t_cnt ++;
            }
#else
#if (CMP_CHOICE == 1) 
			if(SYS_AFE_CMP & BIT15)
            {
                t_cnt ++;
            }
#endif   
#endif
        }

        if(t_cnt > 3)
        {
            StopMotorImmdly();
            stru_Faults.B.SoftCurretError = 1;
        }
		
#if (CMP_CHOICE == 0)
		MCPWM_EIF = BIT4;
#else
#if (CMP_CHOICE == 1) 
		MCPWM_EIF = BIT5;
#endif  
#endif
    }
}

/*******************************************************************************
 函数名称：    u8 SetTime_IsElapsed(void)
 功能描述：    判断等待时间是否到
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

u8 SetTime_IsElapsed(void)
{
    if (struFOC_CtrProc.nSetTimeLeftCnt == 0)
    {
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}

/*******************************************************************************
 函数名称：    void HardFault_Handler(void)
 功能描述：    HardFault_Handler中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void HardFault_Handler(void)
{
    MCPWM_PRT       = 0x0000DEAD;
    MCPWM_FAIL &= MCPWM_MOE_DISABLE_MASK;

    NVIC_SystemReset();
}

/*******************************************************************************
 函数名称：    void SetTimeOut_Counter(u16 hTimeout)
 功能描述：    设置等待函数等待时间
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void SetTime_TimeOut_Counter(u16 hTimeout)
{
    struFOC_CtrProc.nSetTimeLeftCnt = hTimeout;
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/

