/**
 * @file
 * @defgroup cordic
 * @brief        三角计算模块库函数
 * @author       YangZJ
 * @date         2023-01-02
 * @{
 */
#include "lks32mc45x_cordic.h"
static volatile u8 dsp_flg;
/**
 * @brief    使用DSP计算正弦
 * @param u16  val     角度0-65535对应0-360度
 * @return s16 result  计算结果Q15格式
 * @par 更新记录  V1.0  2022.03.10  YangZJ  创建
 */
s16 CORDIC_CalcSin(s16 val)
{
    s16 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetMODULE(SYS_MODULE_CORDIC);
        DSP_SC = BIT2 | BIT1;
        DSP_CORDIC_THETA = (u32)val;
        result = (s16)DSP_CORDIC_SIN;
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/**
 * @brief    使用08x的DSP计算余弦
 * @param s16  val    角度0-65535对应0-360度
 * @return s16  result 计算结果Q15格式
 * @par 更新记录  V1.0  2022.03.10  YangZJ  创建
 */
s16 CORDIC_CalcCos(s16 val)
{
    s16 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetMODULE(SYS_MODULE_CORDIC);
        DSP_SC = BIT2 | BIT1;
        DSP_CORDIC_THETA = (u32)val;
        result = (s16)DSP_CORDIC_COS;
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/**
 * @brief    使用DSP计算均方根
 * @param s16 a,b
 * @par 更新记录  V1.0  2022.03.10  YangZJ  创建
 */
u16 CORDIC_CalcMod(s16 a, s16 b)
{
    u16 c;
    u16 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        // 先触发计算
        // 在计算的过程中判断数据是否可能溢出
        a = (a > 0) ? a : -a;
        b = (b > 0) ? b : -b;
        c = (u16)(a + b);
        SYS_SoftResetMODULE(SYS_MODULE_CORDIC);
        // 当数据可能溢出的时候降低1位精度并重新开始计算
        if (c > 32767) 
        {
            a >>= 1;
            b >>= 1;
            DSP_CORDIC_X = (u16)a;
            DSP_CORDIC_Y = (u16)b;
            result = (u16)DSP_CORDIC_MOD;
            result <<= 1;
        }
        else
        {
            DSP_CORDIC_X = (u16)a;
            DSP_CORDIC_Y = (u16)b;
            result = (u16)DSP_CORDIC_MOD;
        }
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/**
 * @brief    使用DSP计算反正切
 * @param s16  x,y
 * @return 计算结果 角度0-65535对应0-360度
 * @par 更新记录  V1.0  2022.03.10  YangZJ  创建
 */
s16 CORDIC_CalcArctan(s16 x, s16 y)
{
    u16 a;
    u8 i;
    s16 result = 0;
    u8 dsp_flg_old;
    a = (x > 0) ? (u16)x : (u16)(-x);
    a = (y > 0) ? (u16)(a + y) : (u16)(a - y);
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        for (i = 0; i < 16; i++)
        {
            if ((a & (0x8000 >> i)) != 0)
            {
                if (i == 0)
                {
                    SYS_SoftResetMODULE(SYS_MODULE_CORDIC);
                    x = x >> 1;
                    y = y >> 1;
                    DSP_CORDIC_X = (u16)x;
                    DSP_CORDIC_Y = (u16)y;
                }
                else
                {
                    SYS_SoftResetMODULE(SYS_MODULE_CORDIC);
                    x = (s16)(x << (i - 1));
                    y = (s16)(y << (i - 1));
                    DSP_CORDIC_X = (u16)x;
                    DSP_CORDIC_Y = (u16)y;
                }
                result = (s16)DSP_CORDIC_ARCTAN;
                break;
            }
        }
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/**
 * @brief 三角计算模块时钟使能
 */
void CORDIC_Enable(void)
{
    SYS_ModuleClockCmd(SYS_MODULE_CORDIC, ENABLE);
}
/**
 * @brief 三角计算模块时钟关闭
 */
void CORDIC_Disable(void)
{
    SYS_ModuleClockCmd(SYS_MODULE_CORDIC, DISABLE);
}

/*! @} */
