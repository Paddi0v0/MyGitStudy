#include "Global_Variable.h"
#include "PID_regulators.h"

/*******************************************************************************
 函数名称：    s16 HL_PI_AntiDump(s16 DesiredValue, s16 MeasuredValue, stru_PIparams *pParams)
 功能描述：    PI处理
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
s16 HL_PI_AntiDump(s16 DesiredValue, s16 MeasuredValue, stru_PIparams *pParams)
{
    s32 ProportionalPortion, PIoutput, IntegralPortion, DumpPortion;
    s32 InputError;
    s64 dwAux;

    InputError = (s32)(DesiredValue - MeasuredValue);

    ProportionalPortion = (((pParams->hKp_Gain) * InputError) >> (pParams->hKp_Divisor));

    IntegralPortion = (pParams->hKi_Gain) * InputError; /* 计算本次的积分项 */

    dwAux = (s64) IntegralPortion + pParams->wIntegral; /* 计算整体的积分项 */

    if (dwAux > pParams->wUpper_Limit_Integral)
    {
        IntegralPortion = pParams->wUpper_Limit_Integral;
    }
    else if (dwAux < pParams->wLower_Limit_Integral)
    {
        IntegralPortion = pParams->wLower_Limit_Integral;
    }
    else
    {
        IntegralPortion = (s32)(dwAux);
    }

    PIoutput = (IntegralPortion >> pParams->hKi_Divisor) + ProportionalPortion; /* 计算比例+积分部分 */

    /* controller output limitation */
    if (PIoutput > pParams->hUpper_Limit_Output)
    {
        DumpPortion = PIoutput - (pParams->hUpper_Limit_Output);
        PIoutput = pParams->hUpper_Limit_Output;
		
        if (IntegralPortion > 0)
        {
            IntegralPortion = IntegralPortion - (DumpPortion << pParams->hKi_Divisor);
        }

    }
    else if (PIoutput < pParams->hLower_Limit_Output)
    {
        DumpPortion = PIoutput - (pParams->hLower_Limit_Output);
        PIoutput = pParams->hLower_Limit_Output;
		
        if (IntegralPortion < 0)
        {
            IntegralPortion = IntegralPortion - (DumpPortion  << pParams->hKi_Divisor);
        }
    }

    pParams->wIntegral = (IntegralPortion);

    return (s16) PIoutput; /* controller output with limitation */
}


/******************** (C) COPYRIGHT 2008 LINKO Semiconductor *******************/

