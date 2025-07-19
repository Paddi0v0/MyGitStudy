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
#include "project_mcu.h"

#include "PubData_DriverInstance.h"
#include "hardware_config.h"
#include "HALDrv.h"



extern void EPWM0_MCPWM_init(void);
extern void EPWM1_MCPWM_init(void);
extern void M0_ADC_init(void);
extern void M1_ADC_init(void);


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
// 函数名称：    void ADC0_1ShuntNormalModeCFG(void)
// 功能描述：    ADC正常工作模式通道配置
// 输入参数：    无
// 输出参数：    无
// 返 回 值：    无
// 其它说明：
// 修改日期      版本号          修改人            修改内容
// -----------------------------------------------------------------------------
// 2020/8/5      V1.0           Howlet Li          创建
// *******************************************************************************/

void M0_1ShuntNormalModeCFG(void)
{
	ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_BUS_CURR_CH);		// 通道 0
	ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_BUS_CURR_CH);		// 通道 1
	ADC_SetPChanne(ADC0, ADC_DAT_2, M0_BUS_VOL_ADC_CH);			// 通道 2
	ADC_SetPChanne(ADC0, ADC_DAT_3, M0_SPEED_ADC_CH);			// 通道 3
}

void M0_2ShuntNormalModeCFG(void)
{	 
	ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
	ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_CURRETN_A_CH);		// 通道 1
	ADC_SetPChanne(ADC0, ADC_DAT_2, M0_BUS_VOL_ADC_CH);			// 通道 2
	ADC_SetPChanne(ADC0, ADC_DAT_3, M0_SPEED_ADC_CH);			// 通道 3

	ADC_SetPChanne(ADC1, ADC_DAT_0, M0_ADC1_CURRETN_B_CH);		// 通道 0
	ADC_SetPChanne(ADC1, ADC_DAT_1, M0_ADC1_CURRETN_B_CH);		// 通道 1
	ADC_SetPChanne(ADC1, ADC_DAT_2, M0_SPEED_ADC_CH);			// 通道 2
	ADC_SetPChanne(ADC1, ADC_DAT_3, M0_SPEED_ADC_CH);			// 通道 3  
}

void M0_3Shunt_NormalModeCFG(void)
{
	ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
	ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_CURRETN_A_CH);		// 通道 1
	ADC_SetPChanne(ADC0, ADC_DAT_2, M0_BUS_VOL_ADC_CH); 		// 通道 2
	ADC_SetPChanne(ADC0, ADC_DAT_3, M0_SPEED_ADC_CH);			// 通道 3

	ADC_SetPChanne(ADC1, ADC_DAT_0, M0_ADC1_CURRETN_B_CH);		// 通道 0
	ADC_SetPChanne(ADC1, ADC_DAT_1, M0_ADC1_CURRETN_B_CH);		// 通道 1
	ADC_SetPChanne(ADC1, ADC_DAT_2, M0_SPEED_ADC_CH);			// 通道 2
	ADC_SetPChanne(ADC1, ADC_DAT_3, M0_SPEED_ADC_CH);			// 通道 3  
}

void M1_1ShuntNormalModeCFG(void)
{	
	ADC_SetPChanne(ADC2, ADC_DAT_0, M1_ADC2_BUS_CURR_CH);		// 通道 0
	ADC_SetPChanne(ADC2, ADC_DAT_1, M1_ADC2_BUS_CURR_CH);		// 通道 1
	ADC_SetPChanne(ADC2, ADC_DAT_2, M1_BUS_VOL_ADC_CH);			// 通道 2
	ADC_SetPChanne(ADC2, ADC_DAT_3, M0_SPEED_ADC_CH);			// 通道 3
}

void M1_2ShuntNormalModeCFG(void)
{	
	ADC_SetPChanne(ADC2, ADC_DAT_0, M1_ADC2_CURRETN_A_CH);		// 通道 0
	ADC_SetPChanne(ADC2, ADC_DAT_1, M1_ADC2_CURRETN_B_CH);		// 通道 1
	ADC_SetPChanne(ADC2, ADC_DAT_2, M1_BUS_VOL_ADC_CH);			// 通道 2
	ADC_SetPChanne(ADC2, ADC_DAT_3, M1_SPEED_ADC_CH);			// 通道 3
}

void M1_3ShuntNormalModeCFG(void)
{	
	ADC_SetPChanne(ADC2, ADC_DAT_0, M1_ADC2_CURRETN_A_CH);		// 通道 0
	ADC_SetPChanne(ADC2, ADC_DAT_1, M1_ADC2_CURRETN_B_CH);		// 通道 1
	ADC_SetPChanne(ADC2, ADC_DAT_2, M1_BUS_VOL_ADC_CH);			// 通道 2
	ADC_SetPChanne(ADC2, ADC_DAT_3, M0_SPEED_ADC_CH);			// 通道 3
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
	tS_pCurAdcRes->nSampCurDat0 = GET_ADC_DATA0_M0;
	tS_pCurAdcRes->nSampCurDat1 = GET_ADC_DATA1_M0;
}

void AcquireCurSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)//(s16 dat0,s16 dat1)
{
	tS_pCurAdcRes->nSampCurDat0 = GET_ADC_DATA0_M1;
	tS_pCurAdcRes->nSampCurDat1 = GET_ADC_DATA1_M1;
}



void AcquireVdcSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nDcVolAdcDat = GET_M0_BUS_VOL_ADC_RESULT;
}

void AcquireVdcSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nDcVolAdcDat = GET_M1_BUS_VOL_ADC_RESULT;
}


void AcquireNTCSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes)
{
	tS_pAdcRes->nNTCVolAdcDat	= GET_M1_TEMP_DATA_A;
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
#if (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_1SHUNT)
void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{

}
#elif (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_2SHUNT)
void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{

}
#else
void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{
	if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_B)
	{
		ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_CURRETN_A_CH);		// 通道 1

		ADC_SetPChanne(ADC1, ADC_DAT_0, M0_ADC1_CURRETN_B_CH);		// 通道 0
		ADC_SetPChanne(ADC1, ADC_DAT_1, M0_ADC1_CURRETN_B_CH);		// 通道 1
		
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_B_C)
	{
		ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_CURRETN_B_CH);		// 通道 0
		ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_CURRETN_B_CH);		// 通道 1

		ADC_SetPChanne(ADC1, ADC_DAT_0, M0_ADC1_CURRETN_C_CH);		// 通道 0
		ADC_SetPChanne(ADC1, ADC_DAT_1, M0_ADC1_CURRETN_C_CH);		// 通道 1
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_C)
	{
		ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_CURRETN_A_CH);		// 通道 1

		ADC_SetPChanne(ADC1, ADC_DAT_0, M0_ADC1_CURRETN_C_CH);		// 通道 0
		ADC_SetPChanne(ADC1, ADC_DAT_1, M0_ADC1_CURRETN_C_CH);		// 通道 1	
	}
}
#endif


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
#if (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_1SHUNT)
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{

}
#elif (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_2SHUNT)
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{

}
#else
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{
	if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_B)
	{
		ADC_SetPChanne(ADC2, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC2, ADC_DAT_1, M0_ADC0_CURRETN_B_CH);		// 通道 1		
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_B_C)
	{
		ADC_SetPChanne(ADC2, ADC_DAT_0, M0_ADC0_CURRETN_B_CH);		// 通道 0
		ADC_SetPChanne(ADC2, ADC_DAT_1, M0_ADC0_CURRETN_C_CH);		// 通道 1	
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_C)
	{
		ADC_SetPChanne(ADC2, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC2, ADC_DAT_1, M0_ADC0_CURRETN_C_CH);		// 通道 1	
	}
}
#endif



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


#if	(EPWM0_USED == FUNCTION_ON)
void GetEPWM0_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
{
    tS_pHd2Md->bBreakInStatus = (MCPWM0_EIF & MCPWM_FAIL0_IF);
}
void ClrEPWM0_breakInStatus(void)
{
    MCPWM0_EIF = (MCPWM0_EIF & MCPWM_FAIL0_IF);
}

void registerEPWM0_DrvLevel(void)
{
	g_hDriverPolarity[0] = MCPWM0->IO01;
}

void EPWM0_OutPut(FuncState t_state)
{

	MCPWM_OutputMode(MCPWM0,MCPWM_OUT_CHN_012,t_state);
	
}

void EPWM0_Charge(u8 t_bPhaseABC)
{
	volatile u16 hDriverPolarity;
	MCPWM_REG_TypeDef *MCPWMx;

	MCPWMx			= MCPWM0;

	hDriverPolarity	= g_hDriverPolarity[0];
	
	if(t_bPhaseABC == 1)			//A相下桥PWM
	{
		MCPWMx->PRT		= 0x0000DEAD;
		MCPWMx->IO01	= 0x0C08 | hDriverPolarity;
		MCPWMx->IO23	= 0x000C | hDriverPolarity;
		MCPWMx->PRT		= 0x0000;
	}
	else if(t_bPhaseABC == 2)		//B相下桥PWM
	{
		MCPWMx->PRT		= 0x0000DEAD;
		MCPWMx->IO01	= 0x080C | hDriverPolarity;
		MCPWMx->PRT		= 0x0000;
	}
	else if(t_bPhaseABC == 3)		//C相下桥PWM
	{
		MCPWMx->PRT		= 0x0000DEAD;
		MCPWMx->IO01	= 0x0C0C | hDriverPolarity;
		MCPWMx->IO23	= 0x08 | hDriverPolarity;;
		MCPWMx->PRT		= 0x0000;
	}	
}

void RestoreEPWM0Cfg(void)
{
	volatile u16 hDriverPolarity;
	MCPWM_REG_TypeDef *MCPWMx;

	MCPWMx			= MCPWM0;

	hDriverPolarity = g_hDriverPolarity[0];

	MCPWMx->PRT 	= 0x0000DEAD;
	MCPWMx->IO01	= hDriverPolarity;
	MCPWMx->IO23	= hDriverPolarity;
	MCPWMx->PRT 	= 0x0000;
	
}

#if (PLANTFORM_DRV_MODULE_NUM == 1)

void InitEPWM0ChargeEnd(void)
{
	__disable_irq();
	M0_ADC_init();
	EPWM0_MCPWM_init();                     /* PWM初始化 */
	ADC0_STATE_RESET();
	ADC1_STATE_RESET();	
	__enable_irq();
}
#else
void InitEPWM0ChargeEnd(void)
{
	__disable_irq();
	//EPWM0_MCPWM_init();                     /* PWM初始化 */
	RestoreEPWM0Cfg();
	//ADC0_STATE_RESET();
	//ADC1_STATE_RESET();
	__enable_irq();
}
#endif

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
    MCPWM0_TH00 = tS_pMdToHd->mMcPwm.nuTimePhAN;
    MCPWM0_TH01 = tS_pMdToHd->mMcPwm.nuTimePhA;

    MCPWM0_TH10 = tS_pMdToHd->mMcPwm.nuTimePhCN;
    MCPWM0_TH11 = tS_pMdToHd->mMcPwm.nuTimePhC;

    MCPWM0_TH20 = tS_pMdToHd->mMcPwm.nuTimePhBN;
    MCPWM0_TH21 = tS_pMdToHd->mMcPwm.nuTimePhB;

    MCPWM0_TMR0 = tS_pMdToHd->mMcTmr.nuPoint0;		// 第一个采样点
    MCPWM0_TMR1 = tS_pMdToHd->mMcTmr.nuPoint1;		// 第二个采样点	
}
#endif

#if	(EPWM1_USED == FUNCTION_ON)
void GetEPWM1_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
{
    tS_pHd2Md->bBreakInStatus = (MCPWM1_EIF & MCPWM_FAIL0_IF);
}

void ClrEPWM1_breakInStatus(void)
{
    MCPWM1_EIF = (MCPWM1_EIF & MCPWM_FAIL0_IF);
}

void registerEPWM1_DrvLevel(void)
{
	#if (PLANTFORM_DRV_MODULE_NUM == 1)
		g_hDriverPolarity[0] = MCPWM1->IO01;
	#else		
		g_hDriverPolarity[1] = MCPWM1->IO01;
	#endif
}

void EPWM1_OutPut(FuncState t_state)
{
	MCPWM_OutputMode(MCPWM1,MCPWM_OUT_CHN_012,t_state);
}

void EPWM1_Charge(u8 t_bPhaseABC)
{
	volatile u16 hDriverPolarity;
	MCPWM_REG_TypeDef *MCPWMx;

	MCPWMx			= MCPWM1;

	#if (PLANTFORM_DRV_MODULE_NUM == 1)
	hDriverPolarity	= g_hDriverPolarity[0];
	#else
	hDriverPolarity	= g_hDriverPolarity[1];
	#endif
	
	if(t_bPhaseABC == 1)			//A相下桥PWM
	{
		MCPWMx->PRT		= 0x0000DEAD;
		MCPWMx->IO01	= 0x0C08 | hDriverPolarity;
		MCPWMx->IO23	= 0x000C | hDriverPolarity;
		MCPWMx->PRT		= 0x0000;
	}
	else if(t_bPhaseABC == 2)		//B相下桥PWM
	{
		MCPWMx->PRT		= 0x0000DEAD;
		MCPWMx->IO01	= 0x080C | hDriverPolarity;
		MCPWMx->PRT		= 0x0000;
	}
	else if(t_bPhaseABC == 3)		//C相下桥PWM
	{
		MCPWMx->PRT		= 0x0000DEAD;
		MCPWMx->IO01	= 0x0C0C | hDriverPolarity;
		MCPWMx->IO23	= 0x08 | hDriverPolarity;;
		MCPWMx->PRT		= 0x0000;
	}	
}

void RestoreEPWM1Cfg(void)
{
	volatile u16 hDriverPolarity;
	MCPWM_REG_TypeDef *MCPWMx;

	MCPWMx			= MCPWM1;

	hDriverPolarity = g_hDriverPolarity[1];

	MCPWMx->PRT 	= 0x0000DEAD;
	MCPWMx->IO01	= hDriverPolarity;
	MCPWMx->IO23	= hDriverPolarity;
	MCPWMx->PRT 	= 0x0000;
	
}

#if (PLANTFORM_DRV_MODULE_NUM == 1)
void InitEPWM1ChargeEnd(void)
{
	__disable_irq();
	M1_ADC_init();
	EPWM1_MCPWM_init();
	ADC2_STATE_RESET();
	__enable_irq();
}

#else
void InitEPWM1ChargeEnd(void)
{
	__disable_irq();
	RestoreEPWM1Cfg();
	//EPWM1_MCPWM_init();
	//ADC2_STATE_RESET();
	__enable_irq();
}
#endif


s16 getEpwm1DefaultSampoint0(void)
{
	s16 pwmPeriod;
	pwmPeriod	= MCPWM1_TH0;
	return (100- pwmPeriod);
}

s16 getEpwm1DefaultSampoint1(void)
{
	s16 pwmPeriod;
	pwmPeriod	= MCPWM1_TH0;
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
    MCPWM1_TH00 = tS_pMdToHd->mMcPwm.nuTimePhAN;
    MCPWM1_TH01 = tS_pMdToHd->mMcPwm.nuTimePhA;

    MCPWM1_TH10 = tS_pMdToHd->mMcPwm.nuTimePhCN;
    MCPWM1_TH11 = tS_pMdToHd->mMcPwm.nuTimePhC;

    MCPWM1_TH20 = tS_pMdToHd->mMcPwm.nuTimePhBN;
    MCPWM1_TH21 = tS_pMdToHd->mMcPwm.nuTimePhB;

    MCPWM1_TMR0 = tS_pMdToHd->mMcTmr.nuPoint0;		// 第一个采样点
    MCPWM1_TMR1 = tS_pMdToHd->mMcTmr.nuPoint1;		// 第二个采样点
}

#endif
PSTR_HALDrvHandle	getHDDrvHandle(u8 tObj)
{
	return (PSTR_HALDrvHandle)&gS_MotorHalDrvHandleM[tObj];
}



