///*******************************************************************************
// * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
// *
// * 文件名称： HALDrv.h
// * 文件标识：
// * 内容摘要： 硬件驱动层驱动接口全局变量声明文件
// * 其它说明： 无
// * 当前版本： V 1.0
// * 作    者： Tonghua Li
// * 完成日期： 2022年12月13日
// *
// *******************************************************************************/
#ifndef __HAL_DRV_DEFINE__
#define __HAL_DRV_DEFINE__


#include "basic.h"
#include "PubData_DriverInstance.h"

extern void AcquireCurSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes);
extern void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd);
extern void AcquireVdcSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes);
extern void AcquireNTCSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes);
extern void AcquireBmefSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes);

extern void MCPWM0_RegUpdate(STR_PubDatMDHD* tS_pMdToHd);
extern void EPWM0_OutPut(FuncState t_state);
extern void EPWM0_Charge(u8 t_bPhaseABC);
extern void InitEPWM0ChargeEnd(void);
extern void GetEPWM0_breakInStatus(STR_PubDatHDMD* tS_pHd2Md);
extern void ClrEPWM0_breakInStatus(void);




#define Motor_HALDrv_EPWM0   \
{  		/* DRV handle */									\
	AcquireCurSamplingResultsM0,	/* 读取电流AD采样	*/	\
	AcquireVdcSamplingResultsM0,	/* 读取母线AD采样	*/	\
	AcquireNTCSamplingResultsM0,	/* 读取NTC AD采样	*/	\
	AcquireBmefSamplingResultsM0,	/* 读取BMEF AD采样	*/	\
	ChangeADChanelCFGM0,			/* 切换AD采样通道	*/	\
	MCPWM0_RegUpdate,				/* PWM加载			*/	\
	EPWM0_OutPut,					/* PWM输出使能		*/	\
	EPWM0_Charge,					/* PWM预充电		*/	\
	InitEPWM0ChargeEnd,				/* PWM预充电初始化	*/	\
	GetEPWM0_breakInStatus,			/* 读取 BreakIn 状态*/	\
	ClrEPWM0_breakInStatus			/* 清除 BreakIn 状态*/	\
}


// for inline function
static inline void AcquireCurSamplingResultsDRV0(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nSampCurDat0 = GET_ADC0_DATA_M0;
	tS_pCurAdcRes->nSampCurDat1 = GET_ADC1_DATA_M0;
}

static inline void AcquireVdcSamplingResultsDRV0(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nDcVolAdcDat = GET_M0_BUS_VOL_ADC_RESULT;
}

static inline void HAL_DRV0_MCPWM_RegUpdate(STR_PubDatMDHD* tS_pMdToHd)
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


#endif
