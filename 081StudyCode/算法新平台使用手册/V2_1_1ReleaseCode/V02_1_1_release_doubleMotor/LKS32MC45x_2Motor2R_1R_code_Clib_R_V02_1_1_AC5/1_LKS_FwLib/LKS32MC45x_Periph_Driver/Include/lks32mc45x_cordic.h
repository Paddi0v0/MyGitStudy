/**
 * @file
 * @brief        三角计算模块库函数头文件
 * @author       YangZJ
 * @date         2023-01-02
*  */
#ifndef __LKS32MC45x_CORDIC_H
#define __LKS32MC45x_CORDIC_H

///< Includes ------------------------------------------------------------------
#include "lks32mc45x.h"
#include "lks32mc45x_sys.h"
#include "basic.h"

typedef struct
{
    __IO u32 SC;     ///<  0x00 DSP状态控制寄存器
    __IO u32 THETA;  ///<  0x04 DSP sin/cos输入角度寄存器
    __IO u32 X;      ///<  0x08 DSP arctan/module计算输入坐标X寄存器
    __IO u32 Y;      ///<  0x0C DSP arctan/module计算输入坐标Y寄存器
    __IO u32 SIN;    ///<  0x10 DSP sin/cos计算结果sin寄存器
    __IO u32 COS;    ///<  0x14 DSP sin/cos计算结果cos寄存器
    __IO u32 MOD;    ///<  0x18 DSP arctan计算结果 sqrt(X2+Y2) 寄存器
    __IO u32 ARCTAN; ///<  0x1C DSP arctan计算结果arctan(Y/X) 角度寄存器
} CORDIC_TypeDef;
#ifndef CORDIC0
#define CORDIC0 ((CORDIC_TypeDef *)(CORDIC_BASE))
#endif
void CORDIC_Enable(void);
void CORDIC_Disable(void);
s16 CORDIC_CalcSin(s16 val);
s16 CORDIC_CalcCos(s16 val);
u16 CORDIC_CalcMod(s16 x, s16 y);
s16 CORDIC_CalcArctan(s16 x, s16 y);

#endif /*__lks32mc45x_cmp_H */
