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
#include "Global_Variable.h"
#include "hardware_config.h"
#include "function_config.h"
#include "fault_detection.h"
#include "MC_parameter.h"
#include "math.h"


void CurrentOffsetCalibration(void);
void FluxObserveInit(void);

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
    FaultInit();                              /* 故障检测初始化 */
    FaultRecoverInit();                       /* 故障恢复初始化 */

    CurrentOffsetCalibration();               /* 读取电流采样通道偏置 */

    FluxObserveInit();                        /* 观测器参数初始化 */

		Bemf_CheckInit(&stru_BEMF_Check,BEMF_CHECK_ANGLE_COMP);/* 反电动势检测初始化 */

		
#if ((ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) || (HALL2SENSORLESS_ANGLE_VERIFY == TRUE))
	  struFOC_CtrProc.bMotorDirtionCtrlPhase = CW;   /* 有感软件改变相线的方式，改变电机转向，无感的移到此处，
	                                                     有感时void StateInit(void)内的注释掉啦 */
    HALL_InitHallMeasure(&struHallProcess);   /* HALL传感器初始化 */
#endif

    struTaskScheduler.sVersion = &sVersion[0];/* 初始化版本号 */

#if (DEBUG_PWM_OUTPUT == TEST_ON)
    DebugPWM_OutputFunction(); /* 调试的时候输出25%的PWM波形 */
#endif
}


/*******************************************************************************
 函数名称：    void CurrentOffsetCalibration(void)
 功能描述：    读电流Offset值
 输入参数：    stru_FOC_CtrProcDef *this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void CurrentOffsetCalibration(void)
{
    u16 CalibCnt = 0;
    stru_OffsetDef  struOffset;
    u32 t_delay;

    __disable_irq();

    ADC0_TRIG = 0;//关闭硬件触发

    ADC_SOFTWARE_TRIG_ONLY();//数据左对齐
    ADC0_CHNT0 = 4; //采样4个通道

    ADC_STATE_RESET()//ADC0 return to idle

    //延时后进行offset采样
    for(t_delay = 0; t_delay < 0x7ffff; t_delay++);

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC0_CHN0 = ADC_1SHUNT_CURR_CH | (ADC_1SHUNT_CURR_CH << 8);
    ADC0_CHN1 = ADC_BUS_VOL_CHANNEL | (M0_ADC_BUS_CURR_CH << 8);
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
    ADC0_CHN1 = ADC_BUS_VOL_CHANNEL | (M0_ADC_BUS_CURR_CH << 8);
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
    ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
    ADC0_CHN1 = ADC0_CURRETN_C_CHANNEL | (M0_ADC_BUS_CURR_CH << 8);
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)
    ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 8);
    ADC0_CHN1 = ADC0_CURRETN_C_CHANNEL | (M0_ADC_BUS_CURR_CH << 8);

    struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU = 0;
    struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV = 0;
    struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW = 0;
    MCPWM0_RegUpdate();
    PWMOutputs(ENABLE);


#endif
#endif
#endif
#endif
    struOffset.IPhAFilt    = 0;
    struOffset.IPhBFilt    = 0;
    struOffset.UBusFilt    = 0;
    struOffset.IBusFilt    = 0;

    for(CalibCnt = 0; CalibCnt < (1 << ADC_GET_OFFSET_SAMPLES); CalibCnt++)
    {
        /* Clear the ADC0 JEOC pending flag */
        ADC0_SWT = 0x00005AA5;

        while(!(ADC0_IF & BIT0));

        ADC0_IF |= BIT1 | BIT0;

        struOffset.IPhAFilt +=  (s16)((ADC0_DAT0));
        struOffset.IPhBFilt +=  (s16)((ADC0_DAT1));
        struOffset.IPhCFilt += (s16)((ADC0_DAT2));
        struOffset.IBusFilt += (s16)(ADC0_DAT3);
    }

    ADC0_init();

    ADC_NormalModeCFG();

    __enable_irq();

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    struFOC_CurrLoop.nBusShuntOffset =  (s16)(struOffset.IPhAFilt >> ADC_GET_OFFSET_SAMPLES);
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    struFOC_CurrLoop.nPhaseAOffset = (s16)(struOffset.IPhAFilt >> ADC_GET_OFFSET_SAMPLES);
    struFOC_CurrLoop.nPhaseBOffset = (s16)(struOffset.IPhBFilt >> ADC_GET_OFFSET_SAMPLES);
    if((ABS(struFOC_CurrLoop.nPhaseAOffset) > ADC_OFFSET_ERROR) ||
            (ABS(struFOC_CurrLoop.nPhaseBOffset) > ADC_OFFSET_ERROR))
    {
        stru_Faults.B.OffsetError = 1;
    }

#else
#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
    struFOC_CurrLoop.nPhaseAOffset = (s16)(struOffset.IPhAFilt >> ADC_GET_OFFSET_SAMPLES);
    struFOC_CurrLoop.nPhaseBOffset = (s16)(struOffset.IPhBFilt >> ADC_GET_OFFSET_SAMPLES);
    struFOC_CurrLoop.nPhaseCOffset = (s16)(struOffset.IPhCFilt >> ADC_GET_OFFSET_SAMPLES);

    if((ABS(struFOC_CurrLoop.nPhaseAOffset) > ADC_OFFSET_ERROR) ||
            (ABS(struFOC_CurrLoop.nPhaseBOffset) > ADC_OFFSET_ERROR) ||
            (ABS(struFOC_CurrLoop.nPhaseCOffset) > ADC_OFFSET_ERROR))
    {
        stru_Faults.B.OffsetError = 1;
    }
#endif
#endif
#endif



}

/*******************************************************************************
 函数名称：    void FluxObserveInit(void)
 功能描述：    观测器参数初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void FluxObserveInit(void)
{
    struFluxOB_Param.nSTO_KP = PLL_KP_GAIN;              /* 观测器PLL KP 参数 */
    struFluxOB_Param.nSTO_KI = PLL_KI_GAIN;              /* 观测器PLL KI 参数 */

    struFluxOB_Param.nCurrLoopIniKP = P_CURRENT_KP;      /* 电流环初始KP */
    struFluxOB_Param.nCurrLoopIniKI = P_CURRENT_KI;      /* 电流环初始KI */

    struFluxOB_Param.pStruMotorParame = &struMotorParam; /* 电机参数结构体 */
    struFluxOB_Param.pStruBoardParame = &struBoardParam; /* 功率板硬件电路特性参数 */

    FluxObserveParaCalc();                               /* 观测器参数计算 */

    FOC_InitstruParam();                                 /* FOC 相关控制变量及结构体初始化 */
}



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
