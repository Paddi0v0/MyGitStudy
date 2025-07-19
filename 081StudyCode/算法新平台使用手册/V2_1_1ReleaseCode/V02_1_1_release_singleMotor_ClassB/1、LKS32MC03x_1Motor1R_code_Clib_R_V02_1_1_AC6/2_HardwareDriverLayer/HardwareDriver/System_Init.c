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

#include "math.h"
#include "hardware_init.h"
#include "PubData_DriverInstance.h"
#include "segger_rtt.h"

void CurrentOffsetCalibration(void);
#if (DEBUG_PWM_OUTPUT == TEST_ON)
void DebugPWM_OutputFunction(void); /* 调试的时候输出50%的PWM波形 */
#endif

extern PSTR_ControlObject getCtrlObjectPtr(u8 objID);
extern void ADC0_init(void);
extern u8 getLibMaxObjNumber(void);

typedef struct
{
    s32 IPhAFilt;
    s32 IPhBFilt;
    s32 IPhCFilt;
    s32 IBusFilt;
    s32 UBusFilt;
    s32 BemfAFlit;
    s32 BemfBFlit;
    s32 BemfCFlit;
} stru_OffsetDef; /* 偏置读取结构体 */


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
    //SEGGER_RTT_ConfigUpBuffer(1, "JScope_i2i2i2i2", bRttBuf, 512, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    SEGGER_RTT_ConfigUpBuffer(1, "JScope_i2i2", bRttBuf, 256, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
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
static void CurrentOffsetReadPWM0(STR_PubDatHDMD* tS_pHdToMd, u16 t_nuCalPeriod)
{
    u16 CalibCnt = 0;
    volatile u32 t_delay;
    stru_OffsetDef  struOffset;

    PWMOutputs(MCPWM0, DISABLE);

    ADC_SOFTWARE_TRIG_ONLY();

    ADC_CFG = 0;       /* 软件触发 */
    ADC_CHNT = 5;      /* 采样5次 */

    ADC_STATE_RESET();

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_CHN0 = ADC_1SHUNT_CURR_CH | (BEMF_CH_A << 4) | (BEMF_CH_B << 8) | (M0_ADC_BUS_CURR_CH << 12);
    ADC_CHN1 = BEMF_CH_C;
#elif(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    ADC_CHN0 = ADC0_CURRETN_A_CHANNEL | (BEMF_CH_A << 4) | (BEMF_CH_B << 8) | (ADC0_CURRETN_B_CHANNEL << 12);
    ADC_CHN1 = BEMF_CH_C;
#endif

    for(t_delay = 0; t_delay < 0x7ffff; t_delay++) {};

    struOffset.IPhAFilt    = 0;
    struOffset.IPhBFilt    = 0;
    struOffset.UBusFilt    = 0;
    struOffset.IBusFilt    = 0;
    struOffset.BemfAFlit = 0;
    struOffset.BemfBFlit = 0;
    struOffset.BemfCFlit = 0;

    for(CalibCnt = 0; CalibCnt < (t_nuCalPeriod); CalibCnt++)
    {
        /* Clear the ADC0 JEOC pending flag */
        ADC_SWT = 0x00005AA5;

        while(!(ADC_IF & BIT0));

        ADC_IF |= BIT1 | BIT0;
        ADC_STATE_RESET();

		#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
        struOffset.IPhAFilt +=  (s16)((ADC_DAT0)); //ADC_DAT0
        struOffset.IPhBFilt +=  (s16)((ADC_DAT3)); //B
        struOffset.BemfAFlit +=  (s16)((ADC_DAT1));
        struOffset.BemfBFlit += (s16)((ADC_DAT2));
        struOffset.BemfCFlit += (s16)((ADC_DAT4));

		#elif(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
        struOffset.IPhAFilt +=  (s16)((ADC_DAT0)); //ADC_DAT0
        struOffset.IBusFilt +=  (s16)((ADC_DAT3)); //Ibus
        struOffset.BemfAFlit +=  (s16)((ADC_DAT1));
        struOffset.BemfBFlit += (s16)((ADC_DAT2));
        struOffset.BemfCFlit += (s16)((ADC_DAT4));
		#endif
    }

    ADC0_init(); 


	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)

	tS_pHdToMd->nPhaseUOffset=(s16)(struOffset.IPhAFilt/t_nuCalPeriod);
	tS_pHdToMd->nPhaseVOffset=(s16)(struOffset.IPhBFilt/t_nuCalPeriod);
   
	#elif(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	tS_pHdToMd->nBusShuntOffset = (s16)(struOffset.IPhAFilt/t_nuCalPeriod); 

	#elif((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
	
	tS_pHdToMd->nPhaseUOffset=(s16)(struOffset.IPhAFilt/t_nuCalPeriod);
	tS_pHdToMd->nPhaseVOffset=(s16)(struOffset.IPhBFilt/t_nuCalPeriod);
	tS_pHdToMd->nPhaseWOffset=(s16)(struOffset.IPhAFilt/t_nuCalPeriod);
	#endif

    //stru_BEMF_Check.nBemf_ADCoffset.nPhaseU =  (s16)(struOffset.BemfAFlit >> ADC_GET_OFFSET_SAMPLES);
    //stru_BEMF_Check.nBemf_ADCoffset.nPhaseV =  (s16)(struOffset.BemfBFlit >> ADC_GET_OFFSET_SAMPLES);
    //stru_BEMF_Check.nBemf_ADCoffset.nPhaseW =  (s16)(struOffset.BemfCFlit >> ADC_GET_OFFSET_SAMPLES);
}

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
static void CurrentOffsetCalibrationPWM_ID(u8 t_bPwmId,STR_PubDatHDMD* tS_pHdToMd,u16 t_nuCalPeriod)
{
    CurrentOffsetReadPWM0(tS_pHdToMd,t_nuCalPeriod);	
}

static void CurrentOffsetCalibrationPWM(void)
{
	PSTR_ControlObject	t_pObj;
	u16 t_nuCalPeriod;
	t_pObj		= getCtrlObjectPtr(0);
	t_nuCalPeriod	= t_pObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuADCCaliTimes;
	CurrentOffsetCalibrationPWM_ID(t_pObj->m_bPWM_Id,&t_pObj->mGlobalDatPackage.mHdToMd,t_nuCalPeriod);
}

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
