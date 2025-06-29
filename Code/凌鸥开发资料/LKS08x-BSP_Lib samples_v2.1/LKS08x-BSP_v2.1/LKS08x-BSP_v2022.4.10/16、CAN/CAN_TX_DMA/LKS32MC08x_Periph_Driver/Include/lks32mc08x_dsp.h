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
#include "lks32mc081.h"
#include "basic.h"

/*DSP使能和关闭*/
void DSP_Cmd(FuncState state);

/*DSP除法运算*/
void DSP_CalcDivision(uint32_t nDID, uint32_t nDIS);
/*DSP开方运算*/
void DSP_CalcSquare(uint32_t nRAD);

/*DSP取得商*/
uint32_t DSP_GetQuo(void);
/*DSP取得余数*/
uint32_t DSP_GetRem(void);
/*DSP取得开方根*/
uint32_t DSP_GetSqrt(void);

/*除0错误标志*/
uint32_t DSP_DIS0Error(void);

#endif /*__lks32mc08x_DSP_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
