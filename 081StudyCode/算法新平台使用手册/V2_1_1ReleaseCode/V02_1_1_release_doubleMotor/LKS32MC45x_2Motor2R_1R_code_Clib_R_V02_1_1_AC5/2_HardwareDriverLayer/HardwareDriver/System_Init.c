/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Time_Process.c
 * 文件标识：
 * 内容摘要： 定时相关函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
#include "project_mcu.h"
#include "hardware_config.h"

#include "MC_Parameter_M0.h"
#include "MC_Parameter_M1.h"

#include "math.h"

#include "hardware_init.h"
#include "PubData_DriverInstance.h"
#include "segger_rtt.h"

void M0_1ShuntNormalModeCFG(void);
void M1_1ShuntNormalModeCFG(void);
void CurrentOffsetCalibration(void);
#if (DEBUG_PWM_OUTPUT == TEST_ON)
void DebugPWM_OutputFunction(void); /* 调试的时候输出50%的PWM波形 */
#endif

extern PSTR_ControlObject getCtrlObjectPtr(u8 objID);
extern u8 getLibMaxObjNumber(void);

/*******************************************************************************
 函数名称：    bool ConfigData_check(void)
 功能描述：    配置数据及支持库检查
 输入参数：    无
 输出参数：    无
 返 回 值：    TRUE ------- 匹配   FALSE ----- 不匹配
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/1/15      V1.0           Li Tonghua          创建
 *******************************************************************************/
bool ConfigData_check(void)
{
	if(checkParaCfgValid())				//	检查配置参数版本号等是否有效，主要用于LMSMotor下载参数校验
	{
		BondingMotorDrvObject();		//	校验通过，绑定控制对象
	}
	else
	{
		return FALSE;					//	参数无效，调用函数需要进行出错处理
	}
	
	//	校验库是否匹配?
	if(getLibMaxObjNumber() < PLANTFORM_DRV_MODULE_NUM)
	{
		return FALSE;					//	库对象数小于当前代码的对象个数，库不支持
	}
	return TRUE;
}


/*******************************************************************************
 函数名称：    int sys_init(void)
 功能描述：    系统变量初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void sys_init(void)
{
	InitMotorDriveLayer();
	InitMotorAppLayer();
	InitUsrAppLayer();

	CurrentOffsetCalibration();                 /* 读取电流采样通道偏置 */
	
	//gS_TaskScheduler.sVersion = &sVersion[0];/* 初始化版本号 */

	#if (RTT_FUNCTION == FUNCTION_ON)
    /* JScope RTT模式初始化 */    
    SEGGER_RTT_ConfigUpBuffer(1, "JScope_i2i2i2i2", bRttBuf, 2048, SEGGER_RTT_MODE_NO_BLOCK_SKIP);    
	#endif

	#if (DEBUG_PWM_OUTPUT == TEST_ON)
    //DebugPWM_OutputFunction(); /* 调试的时候输出50%的PWM波形 */
	#endif
}

/*******************************************************************************
 函数名称：    static void CurrentOffsetReadPWM0(STR_PubDatHDMD* tS_pHdToMd, u16 t_nuCalPeriod)
 功能描述：    读PWM0模块对应的电流Offset值
 操作的表：    无
 输入参数：    操作结果指针
 输出参数：    操作结果指针回传
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    涉及硬件操作，须根据硬件配置
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/01 	 V1.0			Tonghua Li		  据历史版本更新
 *******************************************************************************/
#if ((PLANTFORM_DRV_MODULE_NUM>1) || ((DRV0_PWM_ID==PLANTFORM_EPWM0) && (PLANTFORM_DRV_MODULE_NUM==1)))
static void CurrentOffsetReadPWM0(STR_PubDatHDMD* tS_pHdToMd, u16 t_nuCalPeriod)
{

    volatile s32 t_offset1, t_offset2, t_offset3;
    volatile s32 t_offset4, t_offset5;
    volatile s32 t_offset6, t_offset7;

    volatile s32 t_error, t_error1, t_error2;

    volatile u32 t_dlay;
    volatile u16 t_cnt;

    volatile s16 last_ADC0_DAT0, last_ADC0_DAT1, last_ADC1_DAT1;

    __disable_irq();


    MCPWM0_PRT = 0x0000DEAD; /* enter password to unlock write protection */
    MCPWM0_TH00 = 0x00;
    MCPWM0_TH01 = 0x00;
    MCPWM0_TH10 = 0x00;
    MCPWM0_TH11 = 0x00;
    MCPWM0_TH20 = 0x00;
    MCPWM0_TH21 = 0x00;
    MCPWM0_UPDATE = 0xff;    /* write whatever value to trigger update */
    MCPWM0_PRT = 0x0000CAFE; //write any value other than 0xDEAD to enable write protection

    MCPWM_OutputMode(MCPWM0,MCPWM_OUT_CHN_012,ENABLE); //对于非MOS内阻采样，可使能也可不使能
    
	ADC0_CHNT = 4;			//采样4个通道
    ADC0_CFG = 0;			/* ADC设置为仅软件触发 */
    ADC0_TRIG = 0;

	ADC1_CHNT = 4;			//采样4个通道
	ADC1_CFG = 0;
	ADC1_TRIG = 0;

    //单电阻Offset
	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		M0_1ShuntNormalModeCFG();
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
		ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_CURRETN_A_CH);		// 通道 1
		ADC_SetPChanne(ADC1, ADC_DAT_0, M0_ADC0_CURRETN_B_CH);		// 通道 0
		ADC_SetPChanne(ADC1, ADC_DAT_1, M0_ADC0_CURRETN_B_CH);		// 通道 1
	#elif  (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
	    ADC_SetPChanne(ADC0, ADC_DAT_0, M0_ADC0_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC0, ADC_DAT_1, M0_ADC0_CURRETN_A_CH);		// 通道 1
		ADC_SetPChanne(ADC1, ADC_DAT_0, M0_ADC0_CURRETN_B_CH);		// 通道 0
		ADC_SetPChanne(ADC1, ADC_DAT_1, M0_ADC0_CURRETN_C_CH);		// 通道 1
	#endif


    ADC0_CFG |= BIT11;  //状态机复位控制信号。软件写入 1 产生复位，
    
    #if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) ||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT))
    ADC1_CFG |= BIT11;  //状态机复位控制信号。软件写入 1 产生复位，
    #endif

    for (t_dlay = 0; t_dlay < 0x2ffff; t_dlay++)
        ;

    t_offset1 = 0;
    t_offset2 = 0;
    t_offset3 = 0;
    t_offset4 = 0;
    t_offset5 = 0;
    t_offset6 = 0;
    t_offset7 = 0;
    t_error = 0;
    t_error1 = 0;
    t_error2 = 0;

    last_ADC0_DAT0 = 0;
    last_ADC0_DAT1 = 0;
    last_ADC1_DAT1 = 0;

    ADC0_SWT = 0x00005AA5; //产生软件触发一次  触发ADC0

	#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) ||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT))
	ADC1_IF = 0x1f;  //
	ADC1_SWT = 0x00005AA5; //产生软件触发一次  触发ADC1
	#endif

    /* get PGA offset */
    for (t_cnt = 0; t_cnt < t_nuCalPeriod; t_cnt++)    //ADC_GET_OFFSET_AVG_TIMES==512
    {
    	#if 0
        t_dlay = 0;
        for (t_dlay = 0; t_dlay < 1000; t_dlay++);
        ADC0_IF |= BIT1 | BIT0;

        ADC1_IF |= BIT1 | BIT0;
		#else

		while(!(ADC0_IF & BIT0));
		ADC0_IF		|= BIT1 | BIT0;
		ADC0_CFG	|= BIT11;
		#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) ||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT))
	
		while(!(ADC1_IF & BIT0));        
        ADC1_IF		|= BIT1 | BIT0;		
		ADC1_CFG	|= BIT11;
		#endif

		#endif
		

        t_offset1 += (s16)((ADC0_DAT0));
        t_offset2 += (s16)((ADC0_DAT1));
        t_offset3 += (s16)((ADC1_DAT0));
        t_offset4 += (s16)((ADC1_DAT1));

        ADC0_SWT = 0x00005AA5;  //产生软件触发一次  触发ADC0

		#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) ||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT))
		ADC1_SWT = 0x00005AA5;  //产生软件触发一次  触发ADC1
		#endif
    }

//    ADC_init();
	M0_ADC_init();
	MCPWM_OutputMode(MCPWM0,MCPWM_OUT_CHN_012,DISABLE);

	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		tS_pHdToMd->nBusShuntOffset = (s16)(t_offset1/t_nuCalPeriod);
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
		tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
		tS_pHdToMd->nPhaseVOffset=(s16)(t_offset3/t_nuCalPeriod);
	#elif((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
		tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
		tS_pHdToMd->nPhaseVOffset=(s16)(t_offset3/t_nuCalPeriod);
		tS_pHdToMd->nPhaseWOffset=(s16)(t_offset4/t_nuCalPeriod);
	#endif
		
}
#endif
/*******************************************************************************
 函数名称：    static void CurrentOffsetReadPWM1(void)
 功能描述：    读PWM1模块对应的电流Offset值
 操作的表：    无
 输入参数：    操作结果指针
 输出参数：    操作结果指针回传
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：	   涉及硬件操作，须根据硬件配置
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/01 	 V1.0			Tonghua Li		  据历史版本更新
 *******************************************************************************/
#if ((PLANTFORM_DRV_MODULE_NUM>1) || ((DRV0_PWM_ID==PLANTFORM_EPWM1) && (PLANTFORM_DRV_MODULE_NUM==1)))
static void CurrentOffsetReadPWM1(STR_PubDatHDMD* tS_pHdToMd,u16 t_nuCalPeriod)
{
    volatile s32 t_offset1, t_offset2, t_offset3;
    volatile s32 t_offset4, t_offset5;
    volatile s32 t_offset6, t_offset7;

    volatile s32 t_error, t_error1, t_error2;

    volatile u32 t_dlay;
    volatile u16 t_cnt;

    volatile s16 last_ADC0_DAT0, last_ADC0_DAT1, last_ADC1_DAT1;

    __disable_irq();

    MCPWM1_PRT = 0x0000DEAD; /* enter password to unlock write protection */
    MCPWM1_TH00 = 0x00;
    MCPWM1_TH01 = 0x00;
    MCPWM1_TH10 = 0x00;
    MCPWM1_TH11 = 0x00;
    MCPWM1_TH20 = 0x00;
    MCPWM1_TH21 = 0x00;

    MCPWM1_UPDATE = 0xff;    /* write whatever value to trigger update */
    MCPWM1_PRT = 0x0000CAFE; //write any value other than 0xDEAD to enable write protection
	MCPWM_OutputMode(MCPWM1,MCPWM_OUT_CHN_012,ENABLE);

	ADC2_CHNT	= 4;			//采样4个通道
    ADC2_CFG	= 0;
    ADC2_TRIG	= 0;


    //单电阻Offset
	#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		M1_1ShuntNormalModeCFG();
	#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
		ADC_SetPChanne(ADC2, ADC_DAT_0, M1_ADC2_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC2, ADC_DAT_1, M1_ADC2_CURRETN_A_CH);		// 通道 1
		ADC_SetPChanne(ADC2, ADC_DAT_2, M1_ADC2_CURRETN_B_CH);		// 通道 2
		ADC_SetPChanne(ADC2, ADC_DAT_3, M1_ADC2_CURRETN_B_CH);		// 通道 3
	#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)    //未验证
		ADC_SetPChanne(ADC2, ADC_DAT_0, M1_ADC2_CURRETN_A_CH);		// 通道 0
		ADC_SetPChanne(ADC2, ADC_DAT_1, M1_ADC2_CURRETN_A_CH);		// 通道 1
		ADC_SetPChanne(ADC2, ADC_DAT_2, M1_ADC2_CURRETN_B_CH);		// 通道 2
		ADC_SetPChanne(ADC2, ADC_DAT_3, M1_ADC2_CURRETN_C_CH);		// 通道 3
	#endif

    ADC2_CFG |= BIT11;

    for (t_dlay = 0; t_dlay < 0x2ffff; t_dlay++)
        ;

    t_offset1 = 0;
    t_offset2 = 0;
    t_offset3 = 0;
    t_offset4 = 0;
    t_offset5 = 0;
    t_offset6 = 0;
    t_offset7 = 0;
    t_error = 0;
    t_error1 = 0;
    t_error2 = 0;

    last_ADC0_DAT0 = 0;
    last_ADC0_DAT1 = 0;
    last_ADC1_DAT1 = 0;


    ADC2_IF = 0x1f;
    ADC2_SWT = 0x00005AA5;

    /* get PGA offset */
    for (t_cnt = 0; t_cnt < t_nuCalPeriod; t_cnt++)   //ADC_GET_OFFSET_AVG_TIMES
    {
    	#if 0
        t_dlay = 0;
        for (t_dlay = 0; t_dlay < 1000; t_dlay++);
			ADC2_IF |= BIT1 | BIT0;
		#else
		while(!(ADC2_IF & BIT0));

		ADC2_IF		|= BIT1 | BIT0;
		ADC2_CFG	|= BIT11;
		#endif

        t_offset1 += (s16)((ADC2_DAT0));
        t_offset2 += (s16)((ADC2_DAT1));
        t_offset3 += (s16)((ADC2_DAT2));
        t_offset4 += (s16)((ADC2_DAT3));

        ADC2_SWT = 0x00005AA5;

    }

    M1_ADC_init();
	MCPWM_OutputMode(MCPWM1,MCPWM_OUT_CHN_012,DISABLE);


	#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		tS_pHdToMd->nBusShuntOffset = (s16)(t_offset1/t_nuCalPeriod);//bus offset.	
	#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
		tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
		tS_pHdToMd->nPhaseVOffset=(s16)(t_offset3/t_nuCalPeriod);
	#elif(EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
		tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
		tS_pHdToMd->nPhaseVOffset=(s16)(t_offset3/t_nuCalPeriod);
		tS_pHdToMd->nPhaseWOffset=(s16)(t_offset4/t_nuCalPeriod);
	#endif
}
#endif

/*******************************************************************************
 函数名称：    static void CurrentOffsetCalibrationPWM_ID(u8 t_bPwmId,STR_PubDatHDMD* tS_pHdToMd)
 功能描述：    根据PWM的ID号读电流Offset值
 输入参数：    t_bPwmId  PWM的ID号
 			   STR_PubDatHDMD* tS_pHdToMd  回传指针
 输出参数：    操作结果指针回传
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/1      V1.0           Tonghua Li          据历史版本更新
 *******************************************************************************/
#if (PLANTFORM_DRV_MODULE_NUM == 2)
static void CurrentOffsetCalibrationPWM_ID(u8 t_bPwmId,STR_PubDatHDMD* tS_pHdToMd,u16 t_nuCalPeriod)
{
	if(t_bPwmId == 0)
	{
    	CurrentOffsetReadPWM0(tS_pHdToMd,t_nuCalPeriod);
	}
	else
	{
    	CurrentOffsetReadPWM1(tS_pHdToMd,t_nuCalPeriod);
	}
}

static void CurrentOffsetCalibrationPWM(void)
{
	u8 t_nuObjID;
	u16 t_nuCalPeriod;
	PSTR_ControlObject	t_pObj;
	for(t_nuObjID = 0;t_nuObjID < PLANTFORM_DRV_MODULE_NUM; t_nuObjID++)
	{
	t_pObj		= getCtrlObjectPtr(t_nuObjID);
	t_nuCalPeriod	= t_pObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuADCCaliTimes;

	if(t_pObj->m_bPWM_Id >= PLANTFORM_DRV_MODULE_NUM)
	{
		return;
	}	
	CurrentOffsetCalibrationPWM_ID(t_pObj->m_bPWM_Id,&t_pObj->mGlobalDatPackage.mHdToMd,t_nuCalPeriod);
	}
}
#else

static void CurrentOffsetCalibrationPWM_ID(u8 t_bPwmId,STR_PubDatHDMD* tS_pHdToMd,u16 t_nuCalPeriod)
{
	#if (DRV0_PWM_ID == PLANTFORM_EPWM0)
    CurrentOffsetReadPWM0(tS_pHdToMd,t_nuCalPeriod);
	#elif (DRV0_PWM_ID == PLANTFORM_EPWM1)
	CurrentOffsetReadPWM1(tS_pHdToMd,t_nuCalPeriod);
	#endif
}

static void CurrentOffsetCalibrationPWM(void)
{
	PSTR_ControlObject	t_pObj;
	u16 t_nuCalPeriod;
	t_pObj		= getCtrlObjectPtr(0);
	t_nuCalPeriod	= t_pObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuADCCaliTimes;
	CurrentOffsetCalibrationPWM_ID(t_pObj->m_bPWM_Id,&t_pObj->mGlobalDatPackage.mHdToMd,t_nuCalPeriod);
}
#endif

/*******************************************************************************
 函数名称：    void CurrentOffsetCalibration(void)
 功能描述：    进行电流AD采样校正
 输入参数：    无
 输出参数：    操作结果指针回传到对应的数据结构中
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/1      V1.0           Tonghua Li          据历史版本更新
 *******************************************************************************/

void CurrentOffsetCalibration(void)
{
    volatile u32 t_dlay;

    //延时时间
    for(t_dlay = 0; t_dlay < 0x6ffff; t_dlay++);

	CurrentOffsetCalibrationPWM();
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
