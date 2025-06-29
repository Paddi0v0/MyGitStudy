#include "global_variable.h"
s32 HL_PI_AntiDump(s32 InputError , stru_PIparams *pParams);

/*******************************************************************************
 函数名称：    s16 HL_PI_AntiDump(s32 InputError , stru_PIparams *pParams)
 功能描述：    PI处理
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
s32 HL_PI_AntiDump(s32 InputError , stru_PIparams *pParams)
{
    s64 ProportionalPortion, PIoutput, IntegralPortion, DumpPortion;
    
    s64 dwAux;

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

    return (s16) PIoutput;
}
