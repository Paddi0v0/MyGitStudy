#include "global_variable.h"
stru_CurrAlphBeta Clarke(stru_CurrPhaseUVW uvw);
stru_CurrVoctorDQ Park(stru_CurrAlphBeta ab, stru_TrigComponents TrigComponents);
stru_VoltAlphBeta Rev_Park(stru_VoltVoctorDQ dq, stru_TrigComponents TrigComponents);
stru_VoltPhaseUVW SVPWM(stru_VoltAlphBeta ab,u16 hPWM_PERIOD);
stru_TrigComponents Trig_Functions(s16 hAngle);
stru_VoltVoctorDQ RevPark_Circle_Limitation(stru_VoltVoctorDQ VoltVoctorDQ);

/*******************************************************************************
 函数名称：    stru_CurrAlphBeta Clarke(stru_CurrPhaseUVW uvw)
 功能描述：    Clarke变换
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
stru_CurrAlphBeta Clarke(stru_CurrPhaseUVW uvw)
{
    stru_CurrAlphBeta ab;

    ab.nAlph = uvw.nPhaseU;
    ab.nBeta = (((u16)(32768 * 0.577350269))*(uvw.nPhaseV - uvw.nPhaseW))>>15;
    
   return ab;
}
/*******************************************************************************
 函数名称：    stru_CurrVoctorDQ Park(stru_CurrAlphBeta ab, stru_TrigComponents TrigComponents)
 功能描述：    Park变换
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
stru_CurrVoctorDQ Park(stru_CurrAlphBeta ab, stru_TrigComponents TrigComponents)
{
    stru_CurrVoctorDQ dq;
    s16 cos = TrigComponents.hCos;
    s16 sin = TrigComponents.hSin;
    
    dq.nAxisD =  (ab.nAlph * cos + ab.nBeta * sin)>>15;
    dq.nAxisQ = (-ab.nAlph * sin + ab.nBeta * cos)>>15;
    
    return (dq);
}

/*******************************************************************************
 函数名称：    stru_VoltAlphBeta Rev_Park(stru_VoltVoctorDQ dq, stru_TrigComponents TrigComponents)
 功能描述：    反Park变换
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
stru_VoltAlphBeta Rev_Park(stru_VoltVoctorDQ dq, stru_TrigComponents TrigComponents)
{
    stru_VoltAlphBeta ab;
    s16 cos = TrigComponents.hCos;
    s16 sin = TrigComponents.hSin;
    
    ab.nAlph = (dq.nAxisD * cos - dq.nAxisQ * sin)>>15;
    ab.nBeta = (dq.nAxisD * sin + dq.nAxisQ * cos)>>15;
    
    return ab;
}
/*******************************************************************************
 函数名称：    stru_VoltPhaseUVW SVPWM(stru_VoltAlphBeta ab,u16 hPWM_PERIOD)
 功能描述：    SVPWM合成
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
stru_VoltPhaseUVW SVPWM(stru_VoltAlphBeta ab,u16 hPWM_PERIOD)
{
    stru_VoltPhaseUVW VoltPhaseUVW;
    s16 nAlph = ab.nAlph;
    s16 nBeta = -ab.nBeta;
    s16 u,v,w;
    s32 uvw_average;
    s16 uvw_min;
    s16 uvw_max;
    
    u = nAlph;
    v = (s16)(-(((s32)nBeta * 28378 + (s32)nAlph * 16384))>>15);
    w = -u - v;
    
    uvw_min = u < v ? u < w ? u : w : v < w ? v : w;
    uvw_max = u > v ? u > w ? u : w : v > w ? v : w;
    uvw_average = (uvw_max + uvw_min)>>1;
    
    u -= uvw_average;
    v -= uvw_average;
    w -= uvw_average;
    
    u >>= 1;
    v >>= 1;
    w >>= 1;
    
    u += 16384;
    v += 16384;
    w += 16384;
    
    u = (u*hPWM_PERIOD)>>15;
    v = (v*hPWM_PERIOD)>>15;
    w = (w*hPWM_PERIOD)>>15;
    VoltPhaseUVW.nPhaseU = u;
    VoltPhaseUVW.nPhaseV = v;
    VoltPhaseUVW.nPhaseW = w;

    return VoltPhaseUVW;
}
/*******************************************************************************
 函数名称：    stru_TrigComponents Trig_Functions(s16 hAngle)
 功能描述：    三角运算
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
stru_TrigComponents Trig_Functions(s16 hAngle)
{
    stru_TrigComponents Local_Components;
    stru_Dsp_sincos dsp_val;
    dsp_val = lks08x_dsp_sin_cos(hAngle);
    Local_Components.hSin = dsp_val.hSin;
    Local_Components.hCos = dsp_val.hCos;
    return (Local_Components);
}
/*******************************************************************************
 函数名称：    stru_VoltVoctorDQ RevPark_Circle_Limitation(stru_VoltVoctorDQ VoltVoctorDQ)
 功能描述：    电压极限圆限制
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
stru_VoltVoctorDQ RevPark_Circle_Limitation(stru_VoltVoctorDQ VoltVoctorDQ)
{
    u32 t_value;
    t_value = (u32)((VoltVoctorDQ.nAxisD * VoltVoctorDQ.nAxisD) 
			 + VoltVoctorDQ.nAxisQ * VoltVoctorDQ.nAxisQ);
	
	if (t_value > (u32)(( 32767 * 32767) ) )
	{
        VoltVoctorDQ.nAxisQ = (s16)lks08x_dsp_sqrt((u32)(32767 * 32767 - VoltVoctorDQ.nAxisD * VoltVoctorDQ.nAxisD));
	}
    return VoltVoctorDQ;
}
