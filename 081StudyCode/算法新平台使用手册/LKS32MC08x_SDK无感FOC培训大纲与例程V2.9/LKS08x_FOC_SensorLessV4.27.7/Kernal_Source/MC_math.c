/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： MC_math.c
 * 文件标识：
 * 内容摘要： 电机控制相关数学计算函数
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
#include "mc_math.h"


/*******************************************************************************
 函数名称：    stru_TrigComponents Trig_Functions(s16 hAngle)
 功能描述：    求角度的正弦和余弦值
 输入参数：    s16 hAngle ：角度
 输出参数：    正弦和余弦值
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

stru_TrigComponents Trig_Functions(s16 hAngle)
{

    stru_TrigComponents Local_Components;

    DSP_SC |= BIT2;
    DSP_CORDIC_THETA = hAngle;

    Local_Components.hSin = DSP_CORDIC_SIN;
    Local_Components.hCos = DSP_CORDIC_COS;

    return (Local_Components);
}


/*******************************************************************************
 函数名称：    void CopyFromBuffer(u8* nDestAddr, u8* pSrcBuff, u16 nSize)
 功能描述：    以8Bit为一次复制数据到另外一个地址
 输入参数：    u8* nDestAddr, u8* pSrcBuff, u16 nSize
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void CopyFromBuffer(u8* nDestAddr, u8* pSrcBuff, u16 nSize)
{
    u8* ps = (u8*) pSrcBuff;
    u8* pd = (u8*) nDestAddr;

    while(nSize--)
        *pd++ = *ps++;


}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
