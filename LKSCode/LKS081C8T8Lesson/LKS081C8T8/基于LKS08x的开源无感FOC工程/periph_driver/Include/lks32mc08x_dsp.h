/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc08x_dsp.h
 * 文件标识：
 * 内容摘要： DSP驱动头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： 
 * 完成日期： 
 *
 * 修改记录1：
 * 修改日期：
 * 版 本 号：V 1.0
 * 修 改 人：
 * 修改内容：创建
 *
 * 修改记录2：
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/
 
#ifndef __lks32mc08x_DSP_H
#define __lks32mc08x_DSP_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x.h"
#include "lks32mc08x_sys.h"
#include "basic.h"

typedef struct
{
    s16 hCos;
    s16 hSin;
} stru_Dsp_sincos;
stru_Dsp_sincos lks08x_dsp_sin_cos(s16 val);
s16 lks08x_dsp_sin(s16 val);
s16 lks08x_dsp_cos(s16 val);
u16 lks08x_dsp_rms(s16 a, s16 b);
u16 lks08x_dsp_arctan(s16 x, s16 y);
s32 lks08x_dsp_div(s32 a, s16 b);
s32 lks08x_dsp_mod(s32 a, s16 b);
u16 lks08x_dsp_sqrt(u32 val);


#endif 



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
