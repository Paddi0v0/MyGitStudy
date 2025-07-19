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

extern void MCPWM_ch012_init(void);
extern void MCPWM_ch345_init(void);

extern void ADC0_init(void);
extern void ADC1_init(void);



#if (MAX_DRV_MODULE_USED == 1)
	#if (EPWM0_USED == FUNCTION_ON)
	const STR_HALDrvHandle	 gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED] = {Motor_HALDrv_EPWM0																	   
																	   };
	#elif (EPWM1_USED == FUNCTION_ON)
	const STR_HALDrvHandle	 gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED] = {Motor_HALDrv_EPWM1
																	   };
	#endif
	
#elif (MAX_DRV_MODULE_USED == 2)

	#if ( (DRV0_PWM_ID == PLANTFORM_EPWM0) && (DRV1_PWM_ID == PLANTFORM_EPWM1) )
	const STR_HALDrvHandle	 gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED] = {Motor_HALDrv_EPWM0,
																	   Motor_HALDrv_EPWM1
																	   };
	#elif ( (DRV0_PWM_ID == PLANTFORM_EPWM1) && (DRV1_PWM_ID == PLANTFORM_EPWM0) )
	const STR_HALDrvHandle	 gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED] = {Motor_HALDrv_EPWM1,
																	   Motor_HALDrv_EPWM0
																	   };
	#else
	#error "Check EPWM driver configure in 2 DRV module"
	#endif
	
#endif

u16		g_hDriverPolarity[MAX_DRV_MODULE_USED];		
// MAX_DRV_MODULE_USED > 1时  0 --- EPWM0， 1 --- EPWM0
// MAX_DRV_MODULE_USED = 1时  0 --- 为所用的EPWM

///*******************************************************************************
// 函数名称：    void ADC0_1Shunt_NormalModeCFG(void)
// 功能描述：    ADC正常工作模式通道配置
// 输入参数：    无
// 输出参数：    无
// 返 回 值：    无
// 其它说明：
// 修改日期      版本号          修改人            修改内容
// -----------------------------------------------------------------------------
// 2020/8/5      V1.0           Howlet Li          创建
// *******************************************************************************/
void ADC0_1Shunt_NormalModeCFG(void)
{
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第0次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第1次采样通道配置*/

    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第2次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第3次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
	ADC_CHN_GAIN_CFG(ADC0, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/

    ADC_CHN_GAIN_CFG(ADC0, CHN7, BEMF_CH_A_M0, ADC_GAIN3V6);			/*ADC第7次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN8, BEMF_CH_A_M0, ADC_GAIN3V6);			/*ADC第8次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN9, BEMF_CH_B_M0, ADC_GAIN3V6);			/*ADC第9次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN10, BEMF_CH_C_M0, ADC_GAIN3V6);			/*ADC第10次采样通道配置*/
	
}

void ADC1_1Shunt_NormalModeCFG(void)
{
    ADC_CHN_GAIN_CFG(ADC1, CHN0, ADC1_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第0次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN1, ADC1_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第1次采样通道配置*/

    ADC_CHN_GAIN_CFG(ADC1, CHN2, ADC1_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第2次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN3, ADC1_1SHUNT_CURR_CH, ADC_GAIN3V6);		/*ADC第3次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第4次采样通道配置*/
	ADC_CHN_GAIN_CFG(ADC1, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/

    ADC_CHN_GAIN_CFG(ADC1, CHN7, BEMF_CH_A_M1, ADC_GAIN3V6);			/*ADC第7次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN8, BEMF_CH_A_M1, ADC_GAIN3V6);			/*ADC第8次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN9, BEMF_CH_B_M1, ADC_GAIN3V6);			/*ADC第9次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN10, BEMF_CH_C_M1, ADC_GAIN3V6);			/*ADC第10次采样通道配置*/	
}

/*******************************************************************************
 函数名称：    void ADC0_2Shunt_NormalModeCFG(void)
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
void ADC0_2Shunt_NormalModeCFG(void)
{
	 //ADC0
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/
	
    ADC_CHN_GAIN_CFG(ADC0, CHN7, BEMF_CH_A_M0, ADC_GAIN3V6);			/*ADC第7次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN8, BEMF_CH_A_M0, ADC_GAIN3V6);			/*ADC第8次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN9, BEMF_CH_B_M0, ADC_GAIN3V6);			/*ADC第9次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN10, BEMF_CH_C_M0, ADC_GAIN3V6);			/*ADC第10次采样通道配置*/
	
	MCPWM0_TMR0 = (s16)(100-PWM_PERIOD_M0);

}

/*******************************************************************************
 函数名称：    void ADC1_2Shunt_NormalModeCFG(void)
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
void ADC1_2Shunt_NormalModeCFG(void)
{
	 //ADC1
    ADC_CHN_GAIN_CFG(ADC1, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/
	
    ADC_CHN_GAIN_CFG(ADC1, CHN7, BEMF_CH_A_M1, ADC_GAIN3V6);			/*ADC第7次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN8, BEMF_CH_A_M1, ADC_GAIN3V6);			/*ADC第8次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN9, BEMF_CH_B_M1, ADC_GAIN3V6);			/*ADC第9次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN10, BEMF_CH_C_M1, ADC_GAIN3V6);			/*ADC第10次采样通道配置*/

	MCPWM0_TMR2 = (s16)(100-PWM_PERIOD_M0);
}

/*******************************************************************************
 函数名称：    void ADC0_3Shunt_NormalModeCFG(void)
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
void ADC0_3Shunt_NormalModeCFG(void)
{
	 //ADC0
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/
	
    ADC_CHN_GAIN_CFG(ADC0, CHN7, BEMF_CH_A_M0, ADC_GAIN3V6);			/*ADC第7次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN8, BEMF_CH_A_M0, ADC_GAIN3V6);			/*ADC第8次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN9, BEMF_CH_B_M0, ADC_GAIN3V6);			/*ADC第9次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN10, BEMF_CH_C_M0, ADC_GAIN3V6);			/*ADC第10次采样通道配置*/

	MCPWM0_TMR0 = (s16)(100-PWM_PERIOD_M0);

}

void ADC1_3Shunt_NormalModeCFG(void)
{
	 //ADC1
    ADC_CHN_GAIN_CFG(ADC1, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/
	
    ADC_CHN_GAIN_CFG(ADC1, CHN7, BEMF_CH_A_M1, ADC_GAIN3V6);			/*ADC第7次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN8, BEMF_CH_A_M1, ADC_GAIN3V6);			/*ADC第8次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN9, BEMF_CH_B_M1, ADC_GAIN3V6);			/*ADC第9次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN10, BEMF_CH_C_M1, ADC_GAIN3V6);			/*ADC第10次采样通道配置*/
	
	MCPWM0_TMR2 = (s16)(100-PWM_PERIOD_M0);
}

/*******************************************************************************
 函数名称：    void AcquireCurSamplingResults(STR_PubDatHDMD* tS_pCurAdcRes)
 功能描述：    get adc sample result
 输入参数：    GET_ADC0_DATA_M0,GET_ADC1_DATA_M0 @hardware_congfig.h
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void AcquireCurSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)//(s16 dat0,s16 dat1)
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
	#if ( (PLANTFORM_DRV_MODULE_NUM>1) || ((PLANTFORM_DRV_MODULE_NUM==1) &&(DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)) )
	tS_pAdcRes->nBmefUVolAdcDat = GET_M0_BEMF_DATA_A - tS_pAdcRes->nBmefUOffset;
	tS_pAdcRes->nBmefVVolAdcDat = GET_M0_BEMF_DATA_B - tS_pAdcRes->nBmefVOffset;
	tS_pAdcRes->nBmefWVolAdcDat = GET_M0_BEMF_DATA_C - tS_pAdcRes->nBmefWOffset;
	#endif
}
/*******************************************************************************
 函数名称：    void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)		   
 功能描述：    adc 通道动态调整
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
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
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    	ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_B_C)
	{		
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
		ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_C)
	{		
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
		ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);
	}
}
#endif


void AcquireCurSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)//(s16 dat0,s16 dat1)
{
	tS_pCurAdcRes->nSampCurDat0 = GET_ADC0_DATA_M1;
	tS_pCurAdcRes->nSampCurDat1 = GET_ADC1_DATA_M1;
}

void AcquireVdcSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nDcVolAdcDat = GET_M1_BUS_VOL_ADC_RESULT;
}


void AcquireNTCSamplingResultsM1(STR_PubDatHDMD* tS_pAdcRes)
{
	tS_pAdcRes->nNTCVolAdcDat	= GET_M1_TEMP_DATA_A;
}

void AcquireBmefSamplingResultsM1(STR_PubDatHDMD* tS_pAdcRes)
{
	#if ( (PLANTFORM_DRV_MODULE_NUM>1) || ((PLANTFORM_DRV_MODULE_NUM==1) &&(DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)) )
	tS_pAdcRes->nBmefUVolAdcDat = GET_M1_BEMF_DATA_A - tS_pAdcRes->nBmefUOffset;
	tS_pAdcRes->nBmefVVolAdcDat = GET_M1_BEMF_DATA_B - tS_pAdcRes->nBmefVOffset;
	tS_pAdcRes->nBmefWVolAdcDat = GET_M1_BEMF_DATA_C - tS_pAdcRes->nBmefWOffset;
	#endif

}
/*******************************************************************************
 函数名称：    void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)		   
 功能描述：    adc 通道动态调整
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{

}


#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{

}

#else

void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{
	if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_B)
	{
		ADC_CHN_GAIN_CFG(ADC1, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    	ADC_CHN_GAIN_CFG(ADC1, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_B_C)
	{		
		ADC_CHN_GAIN_CFG(ADC1, CHN0, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
		ADC_CHN_GAIN_CFG(ADC1, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_C)
	{		
		ADC_CHN_GAIN_CFG(ADC1, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
		ADC_CHN_GAIN_CFG(ADC1, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);
	}
}
#endif



#if	(EPWM0_USED == 1)
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
{
    tS_pHd2Md->bBreakInStatus = (MCPWM0_EIF & BIT4);
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
    MCPWM0_EIF = (MCPWM0_EIF | BIT4);
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
	g_hDriverPolarity[0] = MCPWM0_IO01;		/* 读出驱动极性 */
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
    MCPWM0_PRT = 0xDEAD;
    if(t_state == DISABLE)
    {
        MCPWM0_FAIL012 &= ~BIT6;
    }
    else
    {
        MCPWM0_FAIL012 |= BIT6;
    }
    MCPWM0_PRT = 0;
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
	volatile u16 hDriverPolarity;
	volatile u16 hDriverPolarity0;
	MCPWM0_PRT		= 0x0000DEAD;
	
	if(t_bPhaseABC == 1)			//A相下桥PWM
	{
		MCPWM0_IO01			= 0x0C08 | g_hDriverPolarity[0];
		
		hDriverPolarity		= MCPWM0_IO23 & 0xFF00;
		hDriverPolarity0	= 0x0C | g_hDriverPolarity[0];
		hDriverPolarity		|= hDriverPolarity0;			
		MCPWM0_IO23		= hDriverPolarity;
	}
	else if(t_bPhaseABC == 2)		//B相下桥PWM
	{
		MCPWM0_IO01		= 0x080C | g_hDriverPolarity[0];
	}
	else if(t_bPhaseABC == 3)		//C相下桥PWM
	{
		MCPWM0_IO01		= 0x0C0C | g_hDriverPolarity[0];

		hDriverPolarity		= MCPWM0_IO23 & 0xFF00;
		hDriverPolarity0	= 0x08 | g_hDriverPolarity[0];
		hDriverPolarity		|= hDriverPolarity0;
		MCPWM0_IO23			= hDriverPolarity;
	}

	MCPWM0_PRT		= 0x0000;
}

void RestoreEPWM0Cfg(void)
{
	volatile u16 hDriverPolarity;
	
	MCPWM0_PRT 	= 0x0000DEAD;
	MCPWM0_IO01	= g_hDriverPolarity[0];

	hDriverPolarity = MCPWM0_IO23 & 0xFF00;
	hDriverPolarity |= (g_hDriverPolarity[0] & 0x00FF);
	
	MCPWM0_IO23	= hDriverPolarity;
	MCPWM0_PRT 	= 0x0000;	
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
	//ADC0_init();
	//MCPWM_ch012_init();			/* PWM初始化 */
	//ADC0_STATE_RESET();
	RestoreEPWM0Cfg();				/* EPWM0恢复配置 */
	__enable_irq();
}

s16 getEpwm0DefaultSampoint0(void)
{
	s16 pwmPeriod;
	pwmPeriod	= MCPWM0_TH0;
	return (100- pwmPeriod);
}

s16 getEpwm0DefaultSampoint1(void)
{
	s16 pwmPeriod;
	pwmPeriod	= MCPWM0_TH0;
	return (800- pwmPeriod);
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
	MCPWM0_TH00 = tS_pMdToHd->mMcPwm.nuTimePhBN;
    MCPWM0_TH01 = tS_pMdToHd->mMcPwm.nuTimePhB;
    
    MCPWM0_TH10 = tS_pMdToHd->mMcPwm.nuTimePhAN;
    MCPWM0_TH11 = tS_pMdToHd->mMcPwm.nuTimePhA;

    MCPWM0_TH20 = tS_pMdToHd->mMcPwm.nuTimePhCN;
    MCPWM0_TH21 = tS_pMdToHd->mMcPwm.nuTimePhC;

    MCPWM0_TMR0 = tS_pMdToHd->mMcTmr.nuPoint0;	// 第一个采样点
    MCPWM0_TMR1 = tS_pMdToHd->mMcTmr.nuPoint1;	// 第二个采样点	
}
#endif

#if	(EPWM1_USED == 1)
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
void GetEPWM1_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
{
    tS_pHd2Md->bBreakInStatus = (MCPWM0_EIF & BIT7);
}

/*******************************************************************************
 函数名称：    void ClrEPWM1_breakInStatus(void)
 功能描述：    清除breakin信号
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ClrEPWM1_breakInStatus(void)
{
    MCPWM0_EIF = (MCPWM0_EIF | BIT7);
}

/*******************************************************************************
 函数名称：    void registerEPWM1_DrvLevel(void)
 功能描述：    记录驱动极性
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void registerEPWM1_DrvLevel(void)
{
	#if (PLANTFORM_DRV_MODULE_NUM == 1)
	g_hDriverPolarity[0] = MCPWM0_IO45;		/* 读出驱动极性 */
	#else
	g_hDriverPolarity[1] = MCPWM0_IO45;		/* 读出驱动极性 */
	#endif
}

/*******************************************************************************
 函数名称：    void EPWM1_OutPut(FuncState t_state) 
 功能描述：    MOE操作函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM1_OutPut(FuncState t_state)
{
    MCPWM0_PRT = 0xDEAD;
    if(t_state == DISABLE)
    {
        MCPWM0_FAIL345 &= ~BIT6;
    }
    else
    {
        MCPWM0_FAIL345 |= BIT6;
    }
    MCPWM0_PRT = 0; 
}

/*******************************************************************************
 函数名称：    void EPWM1_Charge(u8 t_bPhaseABC) 
 功能描述：    预充电极性控制
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM1_Charge(u8 t_bPhaseABC)
{
	volatile u16 hDriverPolarity;
	volatile u16 hDriverPolarity0;
	MCPWM0_PRT		= 0x0000DEAD;
	
	if(t_bPhaseABC == 1)			//A相下桥PWM
	{
		hDriverPolarity		= MCPWM0_IO23 & 0xFF;
		hDriverPolarity0	= g_hDriverPolarity[1] & 0xFF00;
		hDriverPolarity0	= 0x0800 | hDriverPolarity0;
		hDriverPolarity		|= hDriverPolarity0;			
		MCPWM0_IO23		= hDriverPolarity;		
		MCPWM0_IO45		= 0x0C0C | g_hDriverPolarity[1];
	}
	else if(t_bPhaseABC == 2)		//B相下桥PWM
	{
		hDriverPolarity		= MCPWM0_IO23 & 0xFF;
		hDriverPolarity0	= g_hDriverPolarity[1] & 0xFF00;
		hDriverPolarity0	= 0x0C00 | hDriverPolarity0;
		hDriverPolarity		|= hDriverPolarity0;	
		MCPWM0_IO23			= hDriverPolarity;
		MCPWM0_IO45			= 0x0C08 | g_hDriverPolarity[1];
	}
	else if(t_bPhaseABC == 3)		//C相下桥PWM
	{
		hDriverPolarity		= MCPWM0_IO23 & 0xFF;
		hDriverPolarity0	= g_hDriverPolarity[1] & 0xFF00;
		hDriverPolarity0	= 0x0C00 | hDriverPolarity0;
		hDriverPolarity		|= hDriverPolarity0;	
		MCPWM0_IO23			= hDriverPolarity;
		MCPWM0_IO45			= 0x080C | g_hDriverPolarity[1];
	}

	MCPWM0_PRT		= 0x0000;
}

void RestoreEPWM1Cfg(void)
{
	volatile u16 hDriverPolarity;
	volatile u16 hDriverPolarity0;

	MCPWM0_PRT 	= 0x0000DEAD;
	
	hDriverPolarity = MCPWM0_IO23 & 0x00FF;

	hDriverPolarity0 = (g_hDriverPolarity[1] & 0xFF00);
	hDriverPolarity |= hDriverPolarity0;	
	MCPWM0_IO23	= hDriverPolarity;
	
	MCPWM0_IO45	= g_hDriverPolarity[1];
	MCPWM0_PRT 	= 0x0000;	
}



/*******************************************************************************
 函数名称：    void InitEPWM1ChargeEnd(void) 
 功能描述：    预充电完成后初始化硬件(PWM和ADC)
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void InitEPWM1ChargeEnd(void)
{
	__disable_irq();   					//  关掉全部中断，会影响另一个ad进中断
	//ADC1_init();
    //MCPWM_ch345_init();				/* PWM初始化 */
	//ADC1_STATE_RESET();
	RestoreEPWM1Cfg();					/* EPWM1恢复配置 */
	__enable_irq();
}

s16 getEpwm1DefaultSampoint0(void)
{
	s16 pwmPeriod;
	pwmPeriod	= MCPWM0_TH1;
	return (100- pwmPeriod);
}

s16 getEpwm1DefaultSampoint1(void)
{
	s16 pwmPeriod;
	pwmPeriod	= MCPWM0_TH1;
	return (800- pwmPeriod);
}

/*******************************************************************************
 函数名称：    void MCPWM1_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM1_RegUpdate(STR_PubDatMDHD* tS_pMdToHd)
{
	MCPWM0_TH30 = tS_pMdToHd->mMcPwm.nuTimePhBN;
    MCPWM0_TH31 = tS_pMdToHd->mMcPwm.nuTimePhB;
    
    MCPWM0_TH40 = tS_pMdToHd->mMcPwm.nuTimePhAN;
    MCPWM0_TH41 = tS_pMdToHd->mMcPwm.nuTimePhA;

    MCPWM0_TH50 = tS_pMdToHd->mMcPwm.nuTimePhCN;
    MCPWM0_TH51 = tS_pMdToHd->mMcPwm.nuTimePhC;

    MCPWM0_TMR2 = tS_pMdToHd->mMcTmr.nuPoint0;	// 第一个采样点
    MCPWM0_TMR3 = tS_pMdToHd->mMcTmr.nuPoint1;	// 第二个采样点	
}

#endif
PSTR_HALDrvHandle	getHDDrvHandle(u8 tObj)
{
	return (PSTR_HALDrvHandle)&gS_MotorHalDrvHandleM[tObj];
}



