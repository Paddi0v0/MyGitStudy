/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： interrupt.c
 * 文件标识：
 * 内容摘要： 中断服务程序文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：2020年8月5日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet
 * 修改内容：创建
 *
 *******************************************************************************/

#include "hardware_config.h"
#include "global_variable.h"
#include "fault_detection.h"
#include "PowerCalculation.h"
#include "SEGGER_RTT.h"

#if (RTT_FUNCTION == FUNCTION_ON)
struct {
    s16 data0;
    s16 data1;
    s16 data2;
//    s16 data3;
} Rttstru;
#endif

#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)\
     ||(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
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

    struFOC_CtrProc.nSys_TimerPWM++;          /* PWM时基计数器 */

    struTaskScheduler.bPWM_UpdateFlg = 1;     /* PWM更新标志 */ 

    struFOC_CurrLoop.nBusVoltage = GET_BUS_VOL_ADC_RESULT; /* 母线电压采样 */

	  struAppCommData.nVspADC = (s16)ADC0_DAT5; /*电位器信号采样结果*/
	
#if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR)   
    Hall_ElecAnglePWM_Process(&struHallProcess); /* HALL角度处理 */
#endif
  
    FOC_Model(&struFOC_CtrProc);              /* FOC电流内环 */

    if(struFOC_CtrProc.eSysState == RUN)
    {
        FaultCurrentCheck(&struFOC_CurrLoop.mStatCurrUVW);  //过流检测
        PowerCalc(&struFOC_CurrLoop.mStatCurrDQ, &struFOC_CurrLoop.mStatVoltDQ, &struPower);
        struCurrentAmplitude.bTheta = (struFluxOB_Param.wElectAngle >> 16);
        CurrentAmplitudeCalc(&struFOC_CurrLoop.mStatCurrUVW, &struCurrentAmplitude, &struImaxCurrent);
    }   
    
	  if((MCPWM_EIF & BIT4) || (MCPWM_EIF & BIT5))//MCPWM_FALL事件 硬件过流判断
		{
       MCPWM_EIF = BIT4|BIT5;
       stru_Faults.B.HardCurretError = 1;// 硬件过流标志位置1
		}
		
    #if(RTT_FUNCTION == FUNCTION_ON)
    {
        Rttstru.data0 = (struFluxOB_Param.wElectAngleOpen >> 16);   //开环角度   
        Rttstru.data1 = (struFluxOB_Param.wElectAngleEst >> 16);    //观察器角度
//			  Rttstru.data0 = (struFOC_CurrLoop.mStatCurrUVW.nPhaseU);    //U相电流角度
//			  Rttstru.data1 = (struFOC_CurrLoop.mStatCurrUVW.nPhaseV);    //U相电流角度
        Rttstru.data2 = (struFOC_CurrLoop.mStatCurrUVW.nPhaseW);    //U相电流角度
        
        SEGGER_RTT_Write(1, &Rttstru, 6);
    }
    #endif

}
#endif

#if(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
/*******************************************************************************
 函数名称：    void MCPWM_IRQHandler(void)
 功能描述：    MCPWM中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM_IRQHandler(void)
{

    MCPWM_IF = BIT1 | BIT0;
  
    struFOC_CtrProc.nSys_TimerPWM++;          /* PWM时基计数器 */

    struTaskScheduler.bPWM_UpdateFlg = 1;     /* PWM更新标志 */ 

    struFOC_CurrLoop.nBusVoltage = GET_BUS_VOL_ADC_RESULT; /* 母线电压采样 */

	  struAppCommData.nVspADC = (s16)ADC0_DAT5; /*电位器信号采样结果*/
	
#if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR)   
    Hall_ElecAnglePWM_Process(&struHallProcess); /* HALL角度处理 */
#endif
	
    FOC_Model(&struFOC_CtrProc);              /* FOC电流内环 */


    if(struFOC_CtrProc.eSysState == RUN)
    {
        FaultCurrentCheck(&struFOC_CurrLoop.mStatCurrUVW);  //过流检测
        PowerCalc(&struFOC_CurrLoop.mStatCurrDQ, &struFOC_CurrLoop.mStatVoltDQ, &struPower);
        struCurrentAmplitude.bTheta = (struFluxOB_Param.wElectAngle >> 16);
        CurrentAmplitudeCalc(&struFOC_CurrLoop.mStatCurrUVW, &struCurrentAmplitude, &struImaxCurrent);
    }
	  if((MCPWM_EIF & BIT4) || (MCPWM_EIF & BIT5))//MCPWM_FALL事件 硬件过流判断
		{		   
       MCPWM_EIF = BIT4|BIT5;
       stru_Faults.B.HardCurretError = 1;// 硬件过流标志位置1
		}
    
    #if(RTT_FUNCTION == FUNCTION_ON)
    {
        Rttstru.data0 = (struFluxOB_Param.wElectAngleOpen >> 16);   //开环角度   
        Rttstru.data1 = (struFluxOB_Param.wElectAngleEst >> 16);    //观察器角度
        Rttstru.data2 = (struFOC_CurrLoop.mStatCurrUVW.nPhaseU);    //U相电流角度
        
        SEGGER_RTT_Write(1, &Rttstru, 6);
    }
    #endif
}
#endif

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
#if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR)    
    HALL_IRQProcess(HALL, &struHallProcess);
#endif  

}


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
{
    /* 时基500us */
    UTIMER_IF |= TIMER_IF_ZERO;

    struTaskScheduler.bTimeCnt1ms++;
    struTaskScheduler.nTimeCnt10ms ++;
    struTaskScheduler.nTimeCnt500ms++;
}

/*******************************************************************************
 函数名称：    void TIMER1_IRQHandler(void)
 功能描述：    TIMER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTIMER1_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void TIMER2_IRQHandler(void)
 功能描述：    TIMER2中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTIMER2_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void TIMER3_IRQHandler(void)
 功能描述：    TIMER3中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTIMER3_IRQHandler(void)
{

}
/*******************************************************************************
 函数名称：    void ENCODER0_IRQHandler(void)
 功能描述：    ENCODER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ENCODER0_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void ENCODER0_IRQHandler(void)
 功能描述：    ENCODER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ENCODER1_IRQHandler(void)
{

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
    CMP_IF = BIT0 | BIT1;

    if(CMP_IF & (BIT1))
    {
        volatile u8 t_bi, t_bcnt;

        t_bcnt = 0;
        for(t_bi = 0; t_bi < 5; t_bi++)
        {
            if(SYS_AFE_CMP & BIT15) /* BIT14 CMP0 OUT Flag| BIT15 CMP1 OUT Flag */
            {   
                t_bcnt ++;
            }
        }

        if(t_bcnt > 3)
        {
            PWMOutputs(DISABLE);
            MCPWM_EIF = BIT4|BIT5;
            stru_Faults.B.HardCurretError = 1;// 硬件过流标志位置1
        }
    }
}



/*******************************************************************************
 函数名称：    void UART0_IRQHandler(void)
 功能描述：    UART0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART0_IRQHandler(void)
{
}

/*******************************************************************************
 函数名称：    void UART1_IRQHandler(void)
 功能描述：    UART1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART1_IRQHandler(void)
{
  

}

/*******************************************************************************
 函数名称：    void SysTick_Handler(void)
 功能描述：    系统滴答定时中断
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SysTick_Handler(void)
{

}

/*******************************************************************************
 函数名称：    void SleepTimer_IRQHandler(void)
 功能描述：    休眠唤醒中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SleepTimer_IRQHandler(void)
{
    while(1);
}

/*******************************************************************************
 函数名称：    void GPIO_IRQHandler(void)
 功能描述：    GPIO中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void GPIO_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void I2C0_IRQHandler(void)
 功能描述：    I2C0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void I2C0_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void SPI0_IRQHandler(void)
 功能描述：    SPI0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SPI0_IRQHandler(void)
{

}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */


