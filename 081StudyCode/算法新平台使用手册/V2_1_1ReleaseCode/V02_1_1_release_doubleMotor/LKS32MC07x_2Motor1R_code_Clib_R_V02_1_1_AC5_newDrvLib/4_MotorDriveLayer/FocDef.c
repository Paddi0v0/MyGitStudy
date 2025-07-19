/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： FocDef.c
 * 文件标识：
 * 内容摘要： Define the basic function of motor vector control
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： LKS/MC TEAM
 * 完成日期： 2022年8月11日
 *******************************************************************************/

/* Standard include ----------------------------------------------------------*/
#include "mc_declaration.h"
#include "MathLIB_Inlines.h"
#include "math.h"
#include "MC_type.h"
#include "MC_Math.h"
#include "hardware_config.h"
#include "PubData_DriverInstance.h"

// 各层控制对象下标对齐
// 编译宏静态实现

// 动态实现方式后续完善

/*******************************************************************************/
//全局变量定义区

STR_MotorFoc 						gS_FocObjM[MAX_DRV_MODULE_USED];			// FOC 控制对象定义
STR_MotorFocElement					gS_FocElementObjM[MAX_DRV_MODULE_USED];		// FOC 变量定义
u8									g_buMdPWMONDelay[MAX_DRV_MODULE_USED];		// PWM ON delay 计数
#if (MAX_DRV_MODULE_USED == 1)
const STR_MotorFocHandle			gS_MotorFocHandleM[MAX_DRV_MODULE_USED] = {		// FOC 模块实现函数，目前仅为SVPWM函数
																	Motor_FocMethod_M0
																	};
#elif (MAX_DRV_MODULE_USED == 2)
STR_MotorFocHandle					gS_MotorFocHandleM[MAX_DRV_MODULE_USED] = {
																	Motor_FocMethod_M0,
																	Motor_FocMethod_M1
																	};

#endif
STR_RC_Def							STR_EstSpeedFilt[MAX_DRV_MODULE_USED];
extern const STR_HALDrvHandle	 	gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED];		//	硬件驱动实现函数数据结构

void SVPWM_1ShuntGetPhaseIcNIa(PSTR_CurSamplingRes this);
void SVPWM_2ShuntGetPhaseIaIb(PSTR_CurSamplingRes this);
void SVPWM_3ShuntGetPhaseIaIb(PSTR_CurSamplingRes this);


/*******************************************************************************/
//外部函数引用区
extern	PSTR_ControlObject	getCtrlObjectPtr(u8 objID);
extern	STR_ControlObject	gS_PhyObjInstanceM[MAX_DRV_MODULE_USED];

extern	void				RegisterObsDatStr(PSTR_MotorFoc tS_pMotorFoc);

extern	s16					Sqrt_Functions(s16 x,s16 y);
extern	void				setObserPLLKpKi(u8 t_bObjId,u16 Kp, u16 Ki);
extern	s32					User2AppFreqTrans(STR_TransCoefElement* pUser2App,float val);

extern	bool				getCurLoopCloseStatusFromOB(u8 t_bObjId);
extern	s16					getVdcCirCleLim(u8 tobjId);

#if (MAX_DRV_MODULE_USED == 1)
extern	s16					getEpwm0DefaultSampoint0(void);
extern	s16					getEpwm0DefaultSampoint1(void);

#elif (MAX_DRV_MODULE_USED == 2)
extern	s16					getEpwm0DefaultSampoint0(void);
extern	s16					getEpwm0DefaultSampoint1(void);
extern	s16					getEpwm1DefaultSampoint0(void);
extern	s16					getEpwm1DefaultSampoint1(void);
#endif

/*******************************************************************************/
//静态局部函数区

static	void				RegisterObsDat2Lib(u8 t_bObjId);

/*****************************************************************************************/	 
static void InitTmr(PSTR_MotorFoc tS_pFocObj);
static void InitTmrDefault(PSTR_MotorFoc tS_pFocObj);

s16 PT1_filter(STR_RC_Def *rc, s16 signal)
{
    s32 wkg;
    wkg = (signal - (s16)(rc->yk_1 >> 16)) * (rc->coef);
    rc->yk_1 += wkg;
    return(rc->yk_1 >> 16);
}
/*******************************************************************************
 函数名称：    RegisterMdGlobal
 功能描述：    注册控制对象数据结构
 输入参数：    按控制对象指针tS_pMotorFoc，全局数据指针tS_pControlObject
 输出参数：    无
 返 回 值：    无
 其它说明：    MD层控制对象数据结构注册，数据交换区、标幺变换系数、FOC参数

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterMdGlobal(PSTR_MotorFoc tS_pMotorFoc,PSTR_ControlObject tS_pControlObject)
{
	tS_pMotorFoc->m_bPWM_ID			= tS_pControlObject->m_bPWM_Id;							//PWM ID
	tS_pMotorFoc->m_bSampType		= (u8)tS_pControlObject->m_pDrvCfgPara->mS_GlobalCfg.m_bSampType; //电流采样方式
	tS_pMotorFoc->pHdToMd			= &tS_pControlObject->mGlobalDatPackage.mHdToMd;		//Hd层到Md层Data指针 赋值
	tS_pMotorFoc->pMdToHd			= &tS_pControlObject->mGlobalDatPackage.mMdToHd;		//Md层到Hd层Data指针 赋值
	
	tS_pMotorFoc->pMaToMd			= &tS_pControlObject->mGlobalDatPackage.mMaToMd;		//Ma层到Md层Data指针 赋值
	tS_pMotorFoc->pMdToMa			= &tS_pControlObject->mGlobalDatPackage.mMdToMa;		//Md层到Ma层Data指针 赋值
	
	tS_pMotorFoc->m_pTransCoef		= &tS_pControlObject->mTransCoef;						//标幺系数指针赋值
	
	tS_pMotorFoc->m_pMotorFocPar	= tS_pControlObject->m_pMotorFocPar;					//FOC参数指针赋值
		
}

/*******************************************************************************
 函数名称：    RegisterMethodHandle
 功能描述：    FOC控制实现方法指针函数
 输入参数：    按控制对象指针tS_pFocObj，全局数据指针tS_pMotorFocHandle
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterMethodHandle(PSTR_MotorFoc tS_pFocObj, PSTR_MotorFocHandle tS_pMotorFocHandle)
{
	tS_pFocObj->m_pHandle		= tS_pMotorFocHandle;
}

/*******************************************************************************
 函数名称：    RegisterHalDrvHandle
 功能描述：    MD2HD驱动调用函数接口
 输入参数：    按控制对象指针tS_pFocObj，全局数据指针tS_pMotorHalDrvHandle
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterHalDrvHandle(PSTR_MotorFoc tS_pFocObj, PSTR_HALDrvHandle tS_pMotorHalDrvHandle)
{
	tS_pFocObj->m_pHALHandle	= tS_pMotorHalDrvHandle;
}

/*******************************************************************************
 函数名称：    RegisterMdLocal
 功能描述：    注册控制对象本地数据结构
 输入参数：    按控制对象指针tS_pMotorFoc，local数据指针tS_pMotorFocElement
 输出参数：    无
 返 回 值：    无
 其它说明：    MD层控制对象数据结构注册，MD层FOC控制local数据

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterMdLocal(PSTR_MotorFoc tS_pMotorFoc,PSTR_MotorFocElement tS_pMotorFocElement)
{
	tS_pMotorFoc->m_pCmpr			= &tS_pMotorFoc->pMdToHd->mMcPwm;				//电机驱动层返回值
	tS_pMotorFoc->m_pTmr			= &tS_pMotorFoc->pMdToHd->mMcTmr;				//电机驱动层返回值

	tS_pMotorFoc->m_pFluxObsGain	= &tS_pMotorFocElement->mFluxObsGain;			//观测器参数变量定义
	
	tS_pMotorFoc->m_pSvpwmPar		= &tS_pMotorFoc->m_pMotorFocPar->mSvpwmPar;		//SvPwm参数
	tS_pMotorFoc->m_pFocObjPar		= &tS_pMotorFoc->m_pMotorFocPar->mObjPar;		//FOC硬件参数
	tS_pMotorFoc->m_pFocObsPar		= &tS_pMotorFoc->m_pMotorFocPar->mObsPar;		//FOC观测器参数
	
	tS_pMotorFoc->mCurSamplingRes.pAdcRes	= tS_pMotorFoc->pHdToMd;				//采样值
	InitTmrDefault(tS_pMotorFoc);
	
}

/*******************************************************************************
 函数名称：    InitCmpr
 功能描述：    比较器数据初始化
 输入参数：    按控制对象指针tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化PWM比较器数据为默认值

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void InitCmpr(PSTR_MotorFoc tS_pFocObj)
{
	u16 t_cmpr;
	t_cmpr = tS_pFocObj->m_pSvpwmPar->nuPwmPrd>>1;
	tS_pFocObj->m_pCmpr->nuTimePhA  =  t_cmpr;    //PhA 赋值
	tS_pFocObj->m_pCmpr->nuTimePhB  =  t_cmpr;    //PhB 赋值
	tS_pFocObj->m_pCmpr->nuTimePhC  =  t_cmpr;    //PhC 赋值
	tS_pFocObj->m_pCmpr->nuTimePhAN = -t_cmpr;    //PhAN 赋值
	tS_pFocObj->m_pCmpr->nuTimePhBN = -t_cmpr;    //PhBN 赋值
	tS_pFocObj->m_pCmpr->nuTimePhCN = -t_cmpr;    //PhCN 赋值
}

#if 0
static void InitTmr(PSTR_MotorFoc tS_pFocObj)
{
	u16 t_cmpr;
	t_cmpr = tS_pFocObj->m_pSvpwmPar->nuPwmPrd;
	tS_pFocObj->m_pTmr->nuPoint0	= 100 - t_cmpr;
	tS_pFocObj->m_pTmr->nuPoint1	= 800 - t_cmpr;
}
#endif

#if (MAX_DRV_MODULE_USED == 1)
static void InitTmrDefault(PSTR_MotorFoc tS_pFocObj)
{
	#if (DRV0_PWM_ID == PLANTFORM_EPWM0)
	{
		tS_pFocObj->m_pTmr->nuPoint0	= getEpwm0DefaultSampoint0();
		tS_pFocObj->m_pTmr->nuPoint1	= getEpwm0DefaultSampoint1();
	}
	#endif

	#if (DRV0_PWM_ID == PLANTFORM_EPWM1)
	{
		tS_pFocObj->m_pTmr->nuPoint0	= getEpwm1DefaultSampoint0();
		tS_pFocObj->m_pTmr->nuPoint1	= getEpwm1DefaultSampoint1();
	}
	#endif
}
#else

static void InitTmrDefault(PSTR_MotorFoc tS_pFocObj)
{
	u8 PWMId;
	PWMId	= tS_pFocObj->m_bPWM_ID;

	if(PWMId == 0)
	{
		tS_pFocObj->m_pTmr->nuPoint0	= getEpwm0DefaultSampoint0();
		tS_pFocObj->m_pTmr->nuPoint1	= getEpwm0DefaultSampoint1();
	}
	
	if(PWMId == 1)
	{
		tS_pFocObj->m_pTmr->nuPoint0	= getEpwm1DefaultSampoint0();
		tS_pFocObj->m_pTmr->nuPoint1	= getEpwm1DefaultSampoint1();
	}
}


#endif



/*******************************************************************************
 函数名称：    InitMotorDriveLayer
 功能描述：    MD电机驱动层初始化函数
 输入参数：    void
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化MD层数据结构等

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 2023/2/19      V1.01          Tonghua Li           修改部分功能
 *******************************************************************************/
#if (MAX_DRV_MODULE_USED == 1)
/* 单电机MD层初始化函数 */
void InitMotorDriveLayer(void)
{
	s16 factor;
	gS_FocObjM[0].m_bFOCObj_ID	= 0;
	gS_FocElementObjM[0].m_bObj_ID = 0;
	RegisterMdGlobal(&gS_FocObjM[0],&gS_PhyObjInstanceM[0]); //注册控制对象全局数据结构
	#if (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_1SHUNT)        //单电阻采样方式
		gS_FocObjM[0].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_1ShuntGetPhaseIcNIa;
	#elif (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_2SHUNT)	    //双电阻采样方式	
		gS_FocObjM[0].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_2ShuntGetPhaseIaIb;
	#else                                                   //三电阻或MOS内阻采样方式
		gS_FocObjM[0].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_3ShuntGetPhaseIaIb;
	#endif
	
	RegisterMdLocal(&gS_FocObjM[0],&gS_FocElementObjM[0]);  //注册控制对象本地数据结构
	RegisterMethodHandle(&gS_FocObjM[0],(PSTR_MotorFocHandle)&gS_MotorFocHandleM[0]);   //注册FOC控制实现方法指针函数

	RegisterObsDat2Lib(0);                      //注册观测器数据指针

	RegisterHalDrvHandle(&gS_FocObjM[0],(PSTR_HALDrvHandle)&gS_MotorHalDrvHandleM[0]);  //注册MD2HD驱动调用函数接口

	factor = gS_PhyObjInstanceM[0].m_pDrvCfgPara->mS_GlobalCfg.m_nOverModuFactor;
	setOverModuFac(0, factor);
}

PSTR_MotorFoc getFocObject(u8 t_bPWMId)
{
	return &gS_FocObjM[0];	
}


#else
/* 双电机MD层初始化函数 */
void InitMotorDriveLayer(void)
{
	u8 objID = 0;
	s16 factor;

	for(objID =0; objID < MAX_DRV_MODULE_USED; objID++)
	{
		gS_FocObjM[objID].m_bFOCObj_ID	= objID;
		gS_FocElementObjM[objID].m_bObj_ID = objID;

		RegisterMdGlobal(&gS_FocObjM[objID],&gS_PhyObjInstanceM[objID]); //注册控制对象全局数据结构

		if (gS_FocObjM[objID].m_bSampType == CURRENT_SAMPLE_1SHUNT)      //单电阻采样方式
		{
			gS_FocObjM[objID].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_1ShuntGetPhaseIcNIa;
		}
		else if (gS_FocObjM[objID].m_bSampType == CURRENT_SAMPLE_2SHUNT) //双电阻采样方式
		{
			gS_FocObjM[objID].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_2ShuntGetPhaseIaIb;
		}
		else                                                            //三电阻或MOS内阻采样方式
		{
			gS_FocObjM[objID].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_3ShuntGetPhaseIaIb;
		}		
		RegisterMdLocal(&gS_FocObjM[objID],&gS_FocElementObjM[objID]);  //注册控制对象本地数据结构
		RegisterMethodHandle(&gS_FocObjM[objID],(PSTR_MotorFocHandle)&gS_MotorFocHandleM[objID]);  //注册FOC控制实现方法指针函数

		RegisterObsDat2Lib(objID);                      //注册观测器数据指针                          //注册观测器数据指针

		RegisterHalDrvHandle(&gS_FocObjM[objID],(PSTR_HALDrvHandle)&gS_MotorHalDrvHandleM[objID]);   //注册MD2HD驱动调用函数接口
		factor = gS_PhyObjInstanceM[objID].m_pDrvCfgPara->mS_GlobalCfg.m_nOverModuFactor;
		setOverModuFac(objID, factor);
	}
}

PSTR_MotorFoc getFocObject(u8 t_bPWMId)
{
	u8 objID = 0;

	for(objID = 0; objID < MAX_DRV_MODULE_USED; objID++)
	{
		if(gS_FocObjM[objID].m_bPWM_ID == t_bPWMId)
		{
			return &gS_FocObjM[objID];
		}
	}

	return NULL;	
}
#endif

/*******************************************************************************
 函数名称：    void setCurrentPIParameter(u8 t_ObjId, u16 Kp_D,u16 Ki_d, u16 Kp_Q,u16 Ki_Q)
 功能描述：    FOC电路环数据初始化
 输入参数：    按控制对象 t_ObjId
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化电流环PI参数，需要执行在InitFocVar函数值之后

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/10/19     V1.1          Tonghua Li           修改部分功能 memset
 *******************************************************************************/
void setCurrentPIParameter(u8 t_ObjId, u16 Kp_D,u16 Ki_D, u16 Kp_Q,u16 Ki_Q)
{
	PSTR_MotorFocElement	tS_pFocElememt	= &gS_FocElementObjM[t_ObjId];

	tS_pFocElememt->mAcrD.KP		= Kp_D;  //d轴电流环Kp初始化
	tS_pFocElememt->mAcrD.KI		= Ki_D;  //d轴电流环Ki初始化
	
	tS_pFocElememt->mAcrQ.KP		= Kp_Q;  //q轴电流环Kp初始化
	tS_pFocElememt->mAcrQ.KI		= Ki_Q;  //q轴电流环Ki初始化
}


/*******************************************************************************
 函数名称：    InitFocVar
 功能描述：    FOC数据初始化
 输入参数：    按控制 t_bObjId
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化PWM比较器数据为默认值

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0          WenCai Zhao          创建
 2023/10/19     V1.1          Tonghua Li           修改部分功能 memset
 *******************************************************************************/
void InitFocVar(u8 t_bObjId)
{
	PSTR_MotorFoc			tS_pFocObj		= &gS_FocObjM[t_bObjId];
	PSTR_MotorFocElement	tS_pFocElememt	= &gS_FocElementObjM[t_bObjId];
	
	tS_pFocObj->eMotorStatusAck			= E_MOTOR_RESET;		//初始化状态机
	
	STR_PIRegulator*	tS_pAcrD		= &tS_pFocElememt->mAcrD;  //d轴电流环指针传递
	STR_PIRegulator*	tS_pAcrQ		= &tS_pFocElememt->mAcrQ;  //q轴电流环指针传递



	memset(tS_pAcrD,0,sizeof(STR_PIRegulator));           //清空d轴PI调节器各变量
	// if necessary,	manual change currentloop PI parameter 
	tS_pAcrD->KP						= tS_pFocObj->m_pFluxObsGain->nD_CurrLoopKP;	//可重新赋值电流环PI
	tS_pAcrD->KI						= tS_pFocObj->m_pFluxObsGain->nD_CurrLoopKI;	
	tS_pAcrD->wLowerLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVdMin<<16;		//积分下限限幅
	tS_pAcrD->wUpperLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVdMax<<16;		//积分上限限幅
	
	
	memset(tS_pAcrQ,0,sizeof(STR_PIRegulator));           //清空q轴PI调节器各变量
	// if necessary,	manual change currentloop PI parameter 
	tS_pAcrQ->KP						= tS_pFocObj->m_pFluxObsGain->nQ_CurrLoopKP;	//可重新赋值电流环PI
	tS_pAcrQ->KI						= tS_pFocObj->m_pFluxObsGain->nQ_CurrLoopKI;
	tS_pAcrQ->wLowerLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVqMin<<16;		//积分下限限幅
	tS_pAcrQ->wUpperLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVqMax<<16;		//积分上限限幅
	


	tS_pFocElememt->mAcrOutDQ.nAxisD			= 0;				//d轴电压初始化
	tS_pFocElememt->mAcrOutDQ.nAxisQ			= 0;				//q轴电压初始化

	memset(&tS_pFocElememt->mMotorAngle,0,sizeof(STR_MotorFocAngle));	//清空电机角度变量


	tS_pFocElememt->mSinCosFocAngle.hSin		= 0;				//角度sin值初始化
	tS_pFocElememt->mSinCosFocAngle.hCos		= 32767;			//角度cos值初始化

//	tS_pFocElememt->mStatCurrAB.nAlph			= 0;				//Alph轴电流初始化
//	tS_pFocElememt->mStatCurrAB.nBeta			= 0;				//Beta轴电流初始化

	tS_pFocElememt->mStatCurDQ.nAxisD			= 0;				//d轴电流初始化
	tS_pFocElememt->mStatCurDQ.nAxisQ			= 0;				//q轴电流初始化
	
	tS_pFocElememt->mMotorSpeed.wSpeedRef		= 0;				//给定转速初始化
	tS_pFocElememt->mMotorSpeed.wSpeedEst		= 0;				//观测转速初始化
	
	tS_pFocElememt->mStatCurDQCmd.nAxisD		= 0;				//给定d轴电流初始化
	tS_pFocElememt->mStatCurDQCmd.nAxisQ		= 0;				//给定q轴电流初始化
	
	tS_pFocElememt->mStatVolAB.nAlph			= 0;				//Alph轴电压初始化
	tS_pFocElememt->mStatVolAB.nBeta			= 0;				//Beta轴电压初始化

	tS_pFocObj->m_bIPDFinsh						= 0;				//IPD标志位初始化

	InitCmpr(tS_pFocObj);                                  //比较器数据初始化
	STR_EstSpeedFilt[t_bObjId].yk_1				= 0;
	STR_EstSpeedFilt[t_bObjId].coef				= 32767.0/(50+1);

	InitTmrDefault(tS_pFocObj);
}


/*****************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////
///////////////////init funcs loc///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************/	 




	 
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////
///////////////////init funcs..end///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************/	 	 

/*******************************************************************************
 函数名称：    void SVPWM_GetPhaseCurrent(PSTR_CurSamplingRes this)
 功能描述：    电流采样函数
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：	   优化为通过函数指针调用实现，缩小采样时间
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0           Tonghua Li          创建
 *******************************************************************************/
void SVPWM_GetPhaseCurrent(PSTR_CurSamplingRes this)
{
    this->mCurSamplingEvent.pAdcSamp(this);
}

/*******************************************************************************
 函数名称：    void SVPWM_1ShuntGetPhaseCurrentxx(PSTR_CurSamplingRes this)
 功能描述：    单电阻采样算法根据SVPWM调制扇区，得到U, V相电流
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：	   优化为通过函数指针调用实现，缩小采样时间
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0           Tonghua Li          创建
 *******************************************************************************/
//sector 1 ic---Nia
void SVPWM_1ShuntGetPhaseIcNIa(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatW + this->pAdcRes->nSampDatU);
}

void SVPWM_1ShuntGetPhaseOldIcNIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIcNOldIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIcNOldIa(PSTR_CurSamplingRes this)
{
	return;
}

//sector 2 Ib NIa
void SVPWM_1ShuntGetPhaseIbNIa(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIbNIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseIbNOldIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIbNOldIa(PSTR_CurSamplingRes this)
{
	return;
}

//sector 3 Ib NIc
void SVPWM_1ShuntGetPhaseIbNIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIbNIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIbNOldIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIbNOldIc(PSTR_CurSamplingRes this)
{
	return;
}

//sector 4 Ic NIb
void SVPWM_1ShuntGetPhaseIcNIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIcNIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIcNOldIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIcNOldIb(PSTR_CurSamplingRes this)
{
	return;
}

//sector 5 Ia NIb
void SVPWM_1ShuntGetPhaseIaNIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIaNIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseIaNOldIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIaNOldIb(PSTR_CurSamplingRes this)
{
	return;
}

//sector 6 Ia NIc
void SVPWM_1ShuntGetPhaseIaNIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIaNIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIaNOldIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIaNOldIc(PSTR_CurSamplingRes this)
{
	return;
}

/*******************************************************************************
 函数名称：    void SVPWM_2ShuntGetPhaseCurrent(PSTR_CurSamplingRes this)
 功能描述：    双电阻采样算法根据SVPWM调制扇区，得到U, V相电流
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：    优化为通过函数指针调用实现，缩小采样时间
 修改日期	   版本号		   修改人			 修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0 		  Tonghua Li		  创建
 *******************************************************************************/
void SVPWM_2ShuntGetPhaseCurrent(PSTR_CurSamplingRes this)
{
    this->mCurSamplingEvent.pAdcSamp(this);
}

void SVPWM_2ShuntGetPhaseIaIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = (s32)(this->pAdcRes->nPhaseUOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatV = (s32)(this->pAdcRes->nPhaseVOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}


/*******************************************************************************
 函数名称：    void SVPWM_3ShuntGetPhasexx(PSTR_CurSamplingRes this)
 功能描述：    三电阻采样算法根据SVPWM调制扇区，得到U, V相电流
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：    优化为通过函数指针调用实现，缩小采样时间
 修改日期	   版本号		   修改人			 修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0 		  Tonghua Li		  创建
 *******************************************************************************/
void SVPWM_3ShuntGetPhaseIaIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = (s32)(this->pAdcRes->nPhaseUOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatV = (s32)(this->pAdcRes->nPhaseVOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_3ShuntGetPhaseOldIaOldIb(PSTR_CurSamplingRes this)
{	
	return;
}


void SVPWM_3ShuntGetPhaseIaIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = (s32)(this->pAdcRes->nPhaseUOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatW = (s32)(this->pAdcRes->nPhaseWOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_3ShuntGetPhaseOldIaOldIc(PSTR_CurSamplingRes this)
{	
	return;
}

void SVPWM_3ShuntGetPhaseIbIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatV = (s32)(this->pAdcRes->nPhaseVOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatW = (s32)(this->pAdcRes->nPhaseWOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_3ShuntGetPhaseOldIbOldIc(PSTR_CurSamplingRes this)
{	
	return;
}

//////////////////////////////////
///////////////////////////////////////////////////

/*******************************************************************************
 函数名称：    s16 CurrentPIRegulator(stru_PIRegulator *Regulator)
 功能描述：    电流环PI  增量式PI
 输入参数：    stru_PIRegulator *Regulator 结构体指针
 输出参数：    PI调节结果
 返 回 值：    无
 其它说明：		Ki -Q16 /Kp -Q12
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           WenCai Zhao          创建
 *******************************************************************************/
s16 CurrentPIRegulator(STR_PIRegulator* tS_pAcr)
{
    s32		ACC;
	s32		wTemp;
    s32		AX;
	
    ACC = (tS_pAcr->nError - tS_pAcr->nLastError) * tS_pAcr->KP;	/* 比例项计算 */
    ACC = (ACC << 4) + (s32)(tS_pAcr->nError) * tS_pAcr->KI;		/* 积分项计算 */
    tS_pAcr->wIntegral = ACC + tS_pAcr->wIntegral;
	
	wTemp					= (((s32)tS_pAcr->nComp) << 16) + tS_pAcr->wIntegral;
	
	if(wTemp > tS_pAcr->wUpperLimitOutput)                /* 输出最大值限幅 */
    {        
		wTemp				= tS_pAcr->wUpperLimitOutput;
		tS_pAcr->wIntegral	= tS_pAcr->wUpperLimitOutput - (((s32)tS_pAcr->nComp) << 16);
		
    }
    else if(wTemp < tS_pAcr->wLowerLimitOutput)         /* 输出最小值限幅 */
    {
        wTemp				= tS_pAcr->wLowerLimitOutput;
		tS_pAcr->wIntegral	= tS_pAcr->wLowerLimitOutput - (((s32)tS_pAcr->nComp) << 16);
    }
	AX = wTemp >> 16;

    tS_pAcr->nLastError = tS_pAcr->nError;				/* 记录上次误差值 */

    return(AX);                                                          
}

/*******************************************************************************
 函数名称：    void SetCmprDuty(PSTR_McpwmCmpr tS_Cmpr,u16 nuTime)
 功能描述：    设置PWM比较装在数值
 输入参数：    PSTR_McpwmCmpr tS_Cmpr  结构体指针
 			   u16 nuTime
 			   
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/15      V1.0          			          创建
 *******************************************************************************/
void SetCmprDuty(PSTR_McpwmCmpr tS_Cmpr,u16 nuTime)
{
	tS_Cmpr->nuTimePhA		= nuTime;
	tS_Cmpr->nuTimePhB		= nuTime;
	tS_Cmpr->nuTimePhC		= nuTime;
	
	tS_Cmpr->nuTimePhAN		= -nuTime;
	tS_Cmpr->nuTimePhBN		= -nuTime;
	tS_Cmpr->nuTimePhCN		= -nuTime;
}

/*******************************************************************************
 函数名称：    updateObserPLLVar1msLoop(PSTR_MotorFoc tS_pMotorFoc)
 功能描述：    PLL Kp Ki计算
 输入参数：    PSTR_MotorFoc tS_pMotorFoc  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/1/20      V1.0           Li Tonghua          创建
 *******************************************************************************/
void updateObserPLLVar1msLoop(PSTR_MotorFoc tS_pMotorFoc)
{
	s16 PLLKp;
	s16 PLLKi;

	s32 FreqStart;
	s32 FreqRef;	
	s32 deltHz;
	s32 deltFreq;
	u8 tObjId = tS_pMotorFoc->m_bFOCObj_ID;
	PSTR_MotorFocElement	pElememt = &gS_FocElementObjM[tObjId];
	
	STR_TransCoefElement *PCoreToApp	= &(tS_pMotorFoc->m_pTransCoef->mCoreToApp);  //标幺化系数CoreToApp指针传递
	PSTR_FocObsPar			 t_pFocObsPar = tS_pMotorFoc->m_pFocObsPar;                 //观测器变量指针传递

	// 数据格式0.1Hz
	deltFreq	= (s32)t_pFocObsPar->nPLLFreq1 - t_pFocObsPar->nPLLFreq0;
	FreqStart	= t_pFocObsPar->nPLLFreq0;
	
	PLLKp		= t_pFocObsPar->nPLLKp1 - t_pFocObsPar->nPLLKp0;
	PLLKi		= t_pFocObsPar->nPLLKi1 - t_pFocObsPar->nPLLKi0;

	// user to app 表示为0.01Hz      ------> 0.1Hz
	FreqRef			= Core2AppFreqTrans(PCoreToApp,pElememt->mMotorSpeed.wSpeedRef);
	FreqRef			= (FreqRef * _IQ15(0.1)) >> 15;
	FreqRef			= ABS(FreqRef);
	
	if(FreqRef >= FreqStart)
	{
		deltHz		= (FreqRef - FreqStart);
		deltHz		= deltHz << 15;
	
		deltFreq	= deltHz/deltFreq;
		
		PLLKp		= (deltFreq  * PLLKp) >> 15;		
		PLLKi		= (deltFreq  * PLLKi) >> 15;
	}
	else
	{
		PLLKp		= 0;
		PLLKi		= 0;
	}

	/* 分段式PI计算函数 */
	PLLKp		= t_pFocObsPar->nPLLKp0 + PLLKp;
	PLLKi		= t_pFocObsPar->nPLLKi0 + PLLKi;	

	PLLKp		= PLLKp > t_pFocObsPar->nPLLKp1 ? t_pFocObsPar->nPLLKp1: PLLKp;
	PLLKp		= PLLKp < t_pFocObsPar->nPLLKp0 ? t_pFocObsPar->nPLLKp0: PLLKp;

	PLLKi		= PLLKi > t_pFocObsPar->nPLLKi1 ? t_pFocObsPar->nPLLKi1: PLLKi;
	PLLKi		= PLLKi < t_pFocObsPar->nPLLKi0 ? t_pFocObsPar->nPLLKi0: PLLKi;

	setObserPLLKpKi(tS_pMotorFoc->m_bFOCObj_ID,PLLKp,PLLKi);
}

/*******************************************************************************
 函数名称：    bool	getIPD_CW_AngComp(PSTR_MotorFoc tS_pFocObj)
 			   bool	getIPD_CCW_AngComp(PSTR_MotorFoc tS_pFocObj)
 功能描述：    IPD 补偿角度 CW/CCW判断
 输入参数：    PSTR_MotorFoc tS_pMotorFoc  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：    库函数调用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/12/20      V1.0           Li Tonghua          创建
 *******************************************************************************/
bool	getIPD_CW_AngComp(PSTR_MotorFoc tS_pFocObj)
{
	return (tS_pFocObj->pMaToMd->nuFineCmd == E_FC_IPD_CW_START);    //  CW IPD 补偿角度判断
}

bool	getIPD_CCW_AngComp(PSTR_MotorFoc tS_pFocObj)
{
	return (tS_pFocObj->pMaToMd->nuFineCmd == E_FC_IPD_CCW_START);   // CCW IPD 补偿角度判断
}

/*******************************************************************************
 函数名称：    s16 getMotorCurFromObjId(u8 t_bObjId)
 			   s16 getPhaseCur_U(u8 t_bObjId)
 			   s16 getPhaseCur_V(u8 t_bObjId)
 			   s16 getPhaseRawCur_U(u8 t_bObjId)
 			   s16 getPhaseRawCur_V(u8 t_bObjId)
 			   
 功能描述：    读取电流封装函数
 输入参数：    u8 t_bObjId      控制对象ID
 输出参数：    无
 返 回 值：    无
 其它说明：    库函数调用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/12/10      V1.0           Li Tonghua          创建
 *******************************************************************************/
s16 getMotorCurFromObjId(u8 t_bObjId)
{
	s16 t_nTmp;
	t_nTmp = Sqrt_Functions(gS_FocElementObjM[t_bObjId].mStatCurrAB.nAlph,gS_FocElementObjM[t_bObjId].mStatCurrAB.nBeta);
	return t_nTmp;
}

s16 getMotorCurFromObjId1ms(u8 t_bObjId)			// return Q15
{	
	s32 t_nTmp;
	t_nTmp	= (s32)gS_FocElementObjM[t_bObjId].mStatCurrAB.nAlph * gS_FocElementObjM[t_bObjId].mStatCurrAB.nAlph
				+ (s32)gS_FocElementObjM[t_bObjId].mStatCurrAB.nBeta* gS_FocElementObjM[t_bObjId].mStatCurrAB.nBeta;

	t_nTmp = IQ15SqrtIQ31(t_nTmp);

	t_nTmp = (t_nTmp * 23170) >> 14;			// 1.414

	if(t_nTmp > 32767)
	{
		t_nTmp = 32767;
	}
	
	return (s16)t_nTmp;
}

s16 getMotorActVoltFromObjId1ms(u8 t_bObjId)		// return Q15
{
	s32 t_nTmp;
	t_nTmp	= (s32)getMotorDaxisVoltFormObjId(t_bObjId) * getMotorDaxisVoltFormObjId(t_bObjId) 
					+ (s32)getMotorQaxisVoltFormObjId(t_bObjId) * getMotorQaxisVoltFormObjId(t_bObjId);

	t_nTmp = IQ15SqrtIQ31(t_nTmp);

	t_nTmp = (t_nTmp * 23170) >> 14;			// 1.414

	if(t_nTmp > 32767)
	{
		t_nTmp = 32767;
	}
	
	return (s16)t_nTmp;
}




s16 getPhaseCur_U(u8 t_bObjId)   //获取U相电流值
{
	return (s16)(gS_FocElementObjM[t_bObjId].mStatCurrUVW.nPhaseU);
}

s16 getPhaseCur_V(u8 t_bObjId)   //获取V相电流值
{
	return (s16)(gS_FocElementObjM[t_bObjId].mStatCurrUVW.nPhaseV);
}

s16 getPhaseCur_W(u8 t_bObjId)   //获取W相电流值
{
	return (s16)(gS_FocElementObjM[t_bObjId].mStatCurrUVW.nPhaseW);
}

s16 getiq_ref(u8 t_bObjId)   //获取iqRef电流值
{
	return (s16)(gS_FocElementObjM[t_bObjId].mStatCurDQCmd.nAxisQ);
}
 s16 getid_ref(u8 t_bObjId)   //获取idRef电流值
{
	return (s16)(gS_FocElementObjM[t_bObjId].mStatCurDQCmd.nAxisD);
}


s16 getPWMstatus(u8 t_bObjId)   
{
	return (s16)gS_PhyObjInstanceM[t_bObjId].mGlobalDatPackage.mMdToMa.ePwmStatus;
}

s16 getUd(u8 t_bObjId)   //获取Ud
{
	return (s16)(gS_FocElementObjM[t_bObjId].mAcrOutDQ.nAxisD);
}

s16 getUq(u8 t_bObjId)   //获取Uq
{
	return (s16)(gS_FocElementObjM[t_bObjId].mAcrOutDQ.nAxisQ);
}

s16 getVdc(u8 t_bObjId)   //获取Vdc
{
	return (s16)(gS_PhyObjInstanceM[t_bObjId].mGlobalDatPackage.mMaToUa.wVdcDec);
}

s16 getid(u8 t_bObjId)   //获取id
{
	return (s16)(gS_FocElementObjM[t_bObjId].mStatCurDQ.nAxisD);
}

s16 getiq(u8 t_bObjId)   //获取iq
{
	return (s16)(gS_FocElementObjM[t_bObjId].mStatCurDQ.nAxisQ);
}

s16 getPhaseRawCur_U(u8 t_bObjId) //获取U相电流采样原始值
{
	return (s16)(gS_FocObjM[t_bObjId].pHdToMd->nSampCurDat0);
}

s16 getPhaseRawCur_V(u8 t_bObjId) //获取V相电流采样原始值
{
	return (s16)(gS_FocObjM[t_bObjId].pHdToMd->nSampCurDat1);
}
s16 getMotorStatus(u8 t_bObjId) 
{
  return (s16)(gS_FocObjM[t_bObjId].pMaToMd->eMotorStatus);
}
/*******************************************************************************
 函数名称：    s16 getEstSpeed(u8 t_bObjId)
 			         s16 getRefSpeed(u8 t_bObjId)
 功能描述：    读取转速封装函数
 输入参数：    u8 t_bObjId      控制对象ID
 输出参数：    无
 返 回 值：    无
 其它说明：    库函数调用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/12/10      V1.0           Li Tonghua          创建
 *******************************************************************************/
s16 getEstSpeed(u8 t_bObjId)    //获取观测转速
{
	return (s16)(gS_FocElementObjM[t_bObjId].mMotorSpeed.wSpeedEst);
}

s16 getRefSpeed(u8 t_bObjId)    //获取给定转速
{
	return (s16)(gS_FocElementObjM[t_bObjId].mMotorSpeed.wSpeedRef);
}

u16 getFocObjStatus(u8 t_bObjId)
{
	return (s16)(gS_FocObjM[t_bObjId].eMotorStatusAck);
}

u16 getFocObjMAStatus(u8 t_bObjId)
{
	return (s16)(gS_FocObjM[t_bObjId].pMaToMd->eMotorStatus);
}


/*******************************************************************************
 函数名称：    void RegisterObsDat2Lib(u8 t_bObjId)
 功能描述：    观测器变量初始化
 输入参数：    u8 t_bObjId   			------ FOC 对象 ID
 输出参数：    无
 返 回 值：    无
 其它说明：	   注册FOC对象变量等到库观测器对象变量中
 				库函数中引用 ----- 应用到的数据结构不能更改
 				
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/08/09      V1.0           Tonghua Li       创建
 *******************************************************************************/
extern void RegisterObjPar(u8 t_bObjId,PSTR_FocObjPar tS_pMdObjPar);
extern void RegisterObsPar(u8 t_bObjId,PSTR_FocObsPar tS_pObsPar);
extern void RegisterSvpwmParObj(u8 t_bObjId,PSTR_FocSvpwmPar tS_pSvpwmPar);
extern void RegisterObsAngleObj(u8 t_bObjId,PSTR_MotorFocAngle tS_pMotorFocAngle);
extern void RegisterObsSpeedObj(u8 t_bObjId,PSTR_MotorFocSpeed tS_pMotorFocSpeed);
extern void RegisterObsCurObj(u8 t_bObjId,PSTR_VectorDQ tS_pCurDqRef,PSTR_VectorDQ tS_pCurDq);
extern void RegisterObsVolObj(u8 t_bObjId,PSTR_VectorDQ tS_pVolDq);
extern void RegisterObsAcrObj(u8 t_bObjId,PSTR_PIRegulator tS_pAcrM,PSTR_PIRegulator tS_pAcrT);
extern void RegisterObsTcObj(u8 t_bObjId,PSTR_TransCoef tS_pTransCoef);
extern void RegisterObsGainObj(u8 t_bObjId,PSTR_FluxObsGainCoefDef tS_pFluxObsGainCoef);
extern void RegisterSamplingEv(u8 t_bObjId,PSTR_CurSamplingEvent tS_pCurSamplingEvent);
extern void RegisterSvpwmPar(u8 t_bObjId,PSTR_FocSvpwmPar tS_pSvpwmPar);
extern void RegisterSvpwmCmprTmr(u8 t_bObjId,PSTR_McpwmCmpr tS_pMcpwmCmpr,PSTR_McpwmTmr tS_pMcpwmTmr);
extern void RegisterObsHalDrvHandle(u8 t_bObjId, PSTR_HALDrvHandle tS_pMotorHalDrvHandle);
extern void RegisterObsStatorCurObj(u8 t_bObjId,PSTR_VectorUVW tS_pUVW,PSTR_VectorAB tS_pCurAB);
extern void RegisterObsHDMDInfor(u8 t_bObjId, STR_PubDatHDMD *pHdToMd, STR_PubDatMDHD *pMdToHd);
extern void RegisterSamplingStru(u8 t_bObjId,PSTR_CurSamplingRes tS_pADCurRes);
extern void RegisterObsMAMDInfor(u8 t_bObjId, STR_PubDatMAMD *pMaToMd,	STR_PubDatMDMA *pMdToHa);


extern PSTR_HALDrvHandle	getHDDrvHandle(u8 tObj);

static void RegisterObsDat2Lib(u8 t_bObjId)
{
	PSTR_MotorFocElement		tS_pFocElememt	= &gS_FocElementObjM[t_bObjId];	
	PSTR_MotorFoc				tS_pMotorFoc	= &gS_FocObjM[t_bObjId];
	// gS_MotorObsM 指针初始化
	RegisterObsPar(t_bObjId,tS_pMotorFoc->m_pFocObsPar);				//注册 FOC 配置参数数据结构
	RegisterObsAngleObj(t_bObjId,&tS_pFocElememt->mMotorAngle);			//注册 FOC 角度信息数据结构
	RegisterObsSpeedObj(t_bObjId,&tS_pFocElememt->mMotorSpeed);			//注册 FOC 速度信息数据结构
	RegisterObsStatorCurObj(t_bObjId,&tS_pFocElememt->mStatCurrUVW, &tS_pFocElememt->mStatCurrAB);
																		//注册 FOC 定子iu iv iw电流、iAlph/iBeta
	
	RegisterObsCurObj(t_bObjId,&tS_pFocElememt->mStatCurDQCmd,&tS_pFocElememt->mStatCurDQ);
																		//注册 FOC dq电流给定、idq
																		
	RegisterObsAcrObj(t_bObjId,&tS_pFocElememt->mAcrD,&tS_pFocElememt->mAcrQ);
																		//注册 FOC dq控制数据结构
																		
	RegisterObsVolObj(t_bObjId,&tS_pFocElememt->mAcrOutDQ);				//注册 FOC dq输出电压

	RegisterObsTcObj(t_bObjId,tS_pMotorFoc->m_pTransCoef);				//注册 标幺变换系数
	RegisterObsGainObj(t_bObjId,tS_pMotorFoc->m_pFluxObsGain);			//注册 观测器配置参数
	RegisterSvpwmParObj(t_bObjId,tS_pMotorFoc->m_pSvpwmPar);			//注册 SVPWM配置参数	
	RegisterObjPar(t_bObjId,tS_pMotorFoc->m_pFocObjPar);				//注册 电机及board硬件参数

	RegisterSamplingStru(t_bObjId,&tS_pMotorFoc->mCurSamplingRes);		//注册 AD采样时间及函数，以及采样结果	

	RegisterSamplingEv(t_bObjId,&tS_pMotorFoc->mCurSamplingRes.mCurSamplingEvent);	//注册 AD采样时间及函数	
	RegisterSvpwmCmprTmr(t_bObjId,tS_pMotorFoc->m_pCmpr,tS_pMotorFoc->m_pTmr);		//注册 PWM变量指针
																					//		(脉宽输出、采样通道配置)
	
	RegisterObsHalDrvHandle(t_bObjId,getHDDrvHandle(t_bObjId));						//注册 硬件驱动函数
	RegisterObsHDMDInfor(t_bObjId,tS_pMotorFoc->pHdToMd,tS_pMotorFoc->pMdToHd);		//注册 MD与HD交换信息

	RegisterObsMAMDInfor(t_bObjId,tS_pMotorFoc->pMaToMd,tS_pMotorFoc->pMdToMa);
}


/******************** (C) COPYRIGHT 2019, Bright Power Semiconductor Co.ltd*******************/


