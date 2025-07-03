/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： HAL_DEF.c
 * 文件标识：
 * 内容摘要： 电机控制MCU硬件接口层，定义硬件操作的共用函数
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： LKS/MC TEAM
 * 完成日期： 2022年12月13日
 *******************************************************************************/
#include "project_config.h"
#include "PubData_DriverInstance.h"
#include "hardware_config.h"
#include "HALDrv.h"

extern void MCPWM_init(void);
extern void ADC0_init(void);
const STR_HALDrvHandle	 gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED] = {Motor_HALDrv_EPWM0};																   


u16		g_hDriverPolarity[MAX_DRV_MODULE_USED];		
// MAX_DRV_MODULE_USED > 1时  0 --- EPWM0， 1 --- EPWM0
// MAX_DRV_MODULE_USED = 1时  0 --- 为所用的EPWM

/*******************************************************************************
 函数名称：    void ADC_1Shunt_NormalModeCFG(void)
 功能描述：    单电阻ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ADC_1Shunt_NormalModeCFG(void)
{ 
  ADC0_CHN0 = ADC_1SHUNT_CURR_CH | (ADC_1SHUNT_CURR_CH<<8);
  ADC0_CHN1 = ADC_1SHUNT_CURR_CH | (ADC_1SHUNT_CURR_CH<<8);
  ADC0_CHN2 = ADC_BUS_VOL_CHANNEL | (ADC0_TEMP_CHANNEL<<8);  
  ADC0_CHN3 = ADC0_TEMP_CHANNEL | (BEMF_CH_A<<8); 
  ADC0_CHN4 = BEMF_CH_B | (BEMF_CH_C<<8);  
}

/*******************************************************************************
 函数名称：    void ADC_2Shunt_NormalModeCFG(void)
 功能描述：    双电阻ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ADC_2Shunt_NormalModeCFG(void)
{
    ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
    ADC0_CHN1 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
    ADC0_CHN2 = ADC_BUS_VOL_CHANNEL | (ADC_BUS_VOL_CHANNEL << 8);  //
    ADC0_CHN3 = ADC0_TEMP_CHANNEL | (BEMF_CH_A<<8); 
  	ADC0_CHN4 = BEMF_CH_B | (BEMF_CH_C<<8); 
 
    MCPWM_TMR0 = (s16)(100-PWM_PERIOD_M0); // 100-PWM_PERIOD
}

/*******************************************************************************
 函数名称：    void ADC_3Shunt_NormalModeCFG(void)
 功能描述：    三电阻ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ADC_3Shunt_NormalModeCFG(void)
{
    ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
    ADC0_CHN1 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
    ADC0_CHN2 = ADC_BUS_VOL_CHANNEL | (M0_ADC_BUS_CURR_CH << 8);  
	ADC0_CHN3 = ADC0_TEMP_CHANNEL | (BEMF_CH_A<<8); 
  	ADC0_CHN4 = BEMF_CH_B | (BEMF_CH_C<<8); 
}


/*******************************************************************************
 函数名称：    void AcquireCurSamplingResults(STR_PubDatHDMD* tS_pCurAdcRes)
 功能描述：    get adc sample result
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void AcquireCurSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nSampCurDat0 = GET_ADC0_DATA_M0;
	tS_pCurAdcRes->nSampCurDat1 = GET_ADC1_DATA_M0;
}


void AcquireVdcSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nDcVolAdcDat = GET_M0_BUS_VOL_ADC_RESULT;
}


void AcquireNTCSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes)
{
	tS_pAdcRes->nNTCVolAdcDat	= GET_M0_TEMP_DATA_A;	
}


void AcquireBmefSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes)
{
	#if (DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)
	tS_pAdcRes->nBmefUVolAdcDat = GET_M0_BEMF_DATA_A - tS_pAdcRes->nBmefUOffset;
	tS_pAdcRes->nBmefVVolAdcDat = GET_M0_BEMF_DATA_B - tS_pAdcRes->nBmefVOffset;
	tS_pAdcRes->nBmefWVolAdcDat = GET_M0_BEMF_DATA_C - tS_pAdcRes->nBmefWOffset;
	#endif
}

/*******************************************************************************
 函数名称：    void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
 功能描述：    AD采样通道切换
 输入参数：    tS_pMdToHd
 输出参数：    无
 返 回 值：    无
 其它说明：		三电阻采样时动态切换采样通道
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建 
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{

}


#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{

}

#else

void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{
	if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_B)
	{
		ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
		ADC0_CHN1 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_B_C)
	{
		ADC0_CHN0 = ADC0_CURRETN_B_CHANNEL | (ADC0_CURRETN_C_CHANNEL << 8);
		ADC0_CHN1 = ADC0_CURRETN_B_CHANNEL | (ADC0_CURRETN_C_CHANNEL << 8);
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_C)
	{
		ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_C_CHANNEL << 8);
		ADC0_CHN1 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_C_CHANNEL << 8);
	}
}
#endif

/*******************************************************************************
 函数名称：    void GetEPWM0_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
 功能描述：    读取breakin信号
 输入参数：    tS_pHd2Md
 输出参数：    无
 返 回 值：    无
 其它说明：	   查看是否存在过流事件
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void GetEPWM0_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
{  // (MCPWM_EIF & BIT4)对应FALL0事件，BIT5对应FALL1事件
    tS_pHd2Md->bBreakInStatus = (MCPWM_EIF & BIT5);  
}

/*******************************************************************************
 函数名称：    void ClrEPWM0_breakInStatus(void)
 功能描述：    清除breakin信号
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ClrEPWM0_breakInStatus(void)
{
    MCPWM_EIF = (MCPWM_EIF | BIT5);
}

/*******************************************************************************
 函数名称：    void registerEPWM0_DrvLevel(void)
 功能描述：    记录驱动极性
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void registerEPWM0_DrvLevel(void)
{
	g_hDriverPolarity[0] = MCPWM_IO01;		/* 读出驱动极性 */
}

/*******************************************************************************
 函数名称：    void EPWM0_OutPut(FuncState t_state) 
 功能描述：    MOE操作函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM0_OutPut(FuncState t_state)
{
    PWMOutputs(t_state);
}

/*******************************************************************************
 函数名称：    void EPWM0_Charge(u8 t_bPhaseABC) 
 功能描述：    预充电极性控制
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM0_Charge(u8 t_bPhaseABC)
{
	MCPWM_PRT		= 0x0000DEAD;
	
	if(t_bPhaseABC == 1)			//A相下桥PWM
	{
		MCPWM_IO01		= 0x0C08 | g_hDriverPolarity[0];
		MCPWM_IO23		= 0x000C | g_hDriverPolarity[0];
	}
	else if(t_bPhaseABC == 2)		//B相下桥PWM
	{
		MCPWM_IO01		= 0x080C | g_hDriverPolarity[0];
	}
	else if(t_bPhaseABC == 3)		//C相下桥PWM
	{
		MCPWM_IO23		= 0x08 | g_hDriverPolarity[0];;
	}

	MCPWM_PRT		= 0x0000;
}

/*******************************************************************************
 函数名称：    void InitEPWM0ChargeEnd(void)
 
 功能描述：    预充电完成后初始化硬件(PWM和ADC)
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void InitEPWM0ChargeEnd(void)
{
	__disable_irq();
	ADC0_init();
	MCPWM_init();					/* PWM初始化 */
	ADC_STATE_RESET();
	__enable_irq();
}

/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_RegUpdate(STR_PubDatMDHD* tS_pMdToHd)
{
	MCPWM_TH00 = tS_pMdToHd->mMcPwm.nuTimePhBN;
    MCPWM_TH01 = tS_pMdToHd->mMcPwm.nuTimePhB;
    
    MCPWM_TH10 = tS_pMdToHd->mMcPwm.nuTimePhAN;
    MCPWM_TH11 = tS_pMdToHd->mMcPwm.nuTimePhA;

    MCPWM_TH20 = tS_pMdToHd->mMcPwm.nuTimePhCN;
    MCPWM_TH21 = tS_pMdToHd->mMcPwm.nuTimePhC;

    MCPWM_TMR0 = tS_pMdToHd->mMcTmr.nuPoint0;	// 第一个采样点
    MCPWM_TMR1 = tS_pMdToHd->mMcTmr.nuPoint1;	// 第二个采样点	
}


