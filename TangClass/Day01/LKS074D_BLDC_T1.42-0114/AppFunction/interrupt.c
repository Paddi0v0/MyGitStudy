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
#include "hardware_init.h"
#include "hardware_config.h"
#include "Global_Variable.h"
#include "main.h"

void PWM_Duty_Setting(void);
void bus_current_limPro(void);
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
    ADC0_IF = BIT1 | BIT0;
	
	mBLDC_CtrProc.nSys_TimerPWM++;
	
	if(ADC0_DAT0 & BIT15)
	{/*母线电压*/
	  mBLDC_CtrProc.nBUS_Vol_ADC = 0;   //舍掉采出的负值电压
	}
    else
	{
      mBLDC_CtrProc.nBUS_Vol_ADC = (mBLDC_CtrProc.nBUS_Vol_ADC + ADC0_DAT0) >> 1;		
	}	

	if(ADC0_DAT2 & BIT15)
	{/*扳机输入*/
	   mBLDC_CtrProc.nSpeed_ADC = 0;   //舍掉采出的负值电压
	}
	else
	{
	   mBLDC_CtrProc.nSpeed_ADC = (ADC0_DAT2 >> 4);	
	}		

}

void ADC1_IRQHandler(void)
{
    ADC1_IF = BIT1 | BIT0;
		
    getBemfValue();		           /* 反电动势&母线电流读取 */	
	
    BLDC_CommProcess();           /* 电机运行处理  */ 

//	bus_current_limPro();         /* 限流输出 */
		
	PWM_Duty_Setting();              /* PWM占空比更新 */	
		
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
	BLDC_CMP_ModeControl();
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
   BLDC_DelayCommunication();
}
/*******************************************************************************
 函数名称：    void MCPWM0_IRQHandler(void)
 功能描述：    MCPWM中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 2023/3/9      V1.0           Zhujie             修改
 *******************************************************************************/
void MCPWM0_IRQHandler(void)
{
  if(MCPWM0_EIF & BIT5)
  {
	 StopMotorImmdly();
     mBLDC_CtrProc.sys_error_flg |= SHORT_ERROR;
     MCPWM0_EIF = BIT5;
  }  
	
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
void TIMER0_IRQHandler(void)
{
    /* 时基500us */
    UTIMER0_IF = BIT2;
    /* 时基1ms */
    struTaskScheduler.bTimeCnt1ms++;
    struTaskScheduler.nTimeCnt10ms ++;
    struTaskScheduler.nTimeCnt100ms ++;
    struTaskScheduler.nTimeCnt500ms++;

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
void HALL0_IRQHandler(void)
{
//    HALL->INFO = HALL->INFO;    // 清标志位
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
void TIMER1_IRQHandler(void)
{

}

void TIMER2_IRQHandler(void)
{

}

void TIMER3_IRQHandler(void)
{
    
}

void ENCODER0_IRQHandler(void)
{

}

void ENCODER1_IRQHandler(void)
{

}


void UART0_IRQHandler(void)
{

}

void UART1_IRQHandler(void)
{
  

}

void SleepTimer_IRQHandler(void)
{
    while(1);
}


void GPIO_IRQHandler(void)
{

}

void QEP0_IRQHandler(void)
{
}
void QEP1_IRQHandler(void)
{
}

void I2C0_IRQHandler(void)
{

}

void SPI0_IRQHandler(void)
{

}

void DSP0_IRQHandler(void)
{
}



void MCPWM1_IRQHandler(void)
{
}

void SIF0_IRQHandler  (void)
{
}
void WAKE_IRQHandler  (void)
{
}
void SW_IRQHandler    (void)
{
}
void PWRDN_IRQHandler (void)
{
}
void CL0_IRQHandler   (void)
{
}
/*******************************************************************************
 函数名称：    void HardFault_Handler(void)
 功能描述：    硬件故障中断函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/6/8      V1.0        LSL          创建
 *******************************************************************************/
volatile u32 hardFault;
void HardFault_Handler(void)
{
	StopMotorImmdly();
    hardFault++;
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */


