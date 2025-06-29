#include "global_variable.h"
#include "hardware_config.h"
void ADC0_IRQHandler(void);
void PendSV_Handler(void);

/*******************************************************************************
 函数名称：    int ADC0_IRQHandler(void)
 功能描述：    ADC中断函数
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void ADC0_IRQHandler(void)
{
    ADC0_IF |= BIT1 | BIT0;
    struFOC_CtrProc.nBusVoltage = ADC0_DAT2; 
	
    if (struFOC_CtrProc.eSysState == RUN)
    {
		FOC_Model(&struFOC_CtrProc);
    }
    struFOC_CtrProc.nSys_TimerPWM++;        // 16分频进行状态机处理
    if(struFOC_CtrProc.nSys_TimerPWM >= 16)
    {
        struFOC_CtrProc.nSys_TimerPWM = 0;
        SCB->ICSR |= BIT28;
    }
}
/*******************************************************************************
 函数名称：    void PendSV_Handler(void)
 功能描述：    ADC中断函数
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void PendSV_Handler(void)
{
    Sys_State_Machine(&struFOC_CtrProc);    // 状态机
    Key_in(&struFOC_CtrProc);    // 状态机
}
