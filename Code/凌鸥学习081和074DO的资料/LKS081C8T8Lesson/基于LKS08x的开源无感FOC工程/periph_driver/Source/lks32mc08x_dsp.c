/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc08x_dsp.c
 * 文件标识：
 * 内容摘要： DSP协处理器模式驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： YangZJ
 * 完成日期： 2022年3月10日
 *
 * 修改记录1：
 * 修改日期：2022年3月10日
 * 版 本 号：V 1.0
 * 修 改 人：YangZJ
 * 修改内容：创建
 *
 *******************************************************************************/
#include "lks32mc08x.h"
#include "lks32mc08x_sys.h"
#include "lks32mc08x_dsp.h"
static volatile u8 dsp_flg; // 标志位，用于判断程序是否被打断
/*******************************************************************************
 函数名称：    s16 lks08x_dsp_sin(s16 val)
 功能描述：    使用08x的DSP计算正弦
 输入参数：    u16  val     角度0-65535对应0-360度
 返 回 值：    s16 result  计算结果Q15格式
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
stru_Dsp_sincos lks08x_dsp_sin_cos(s16 val)
{
    stru_Dsp_sincos result;
    
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_SC = BIT2 | BIT1;
        DSP_CORDIC_THETA = (u32)val;
        result.hSin = (s16)DSP_CORDIC_SIN;
        result.hCos = (s16)DSP_CORDIC_COS;
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/*******************************************************************************
 函数名称：    s16 lks08x_dsp_sin(s16 val)
 功能描述：    使用08x的DSP计算正弦
 输入参数：    u16  val     角度0-65535对应0-360度
 返 回 值：    s16 result  计算结果Q15格式
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
s16 lks08x_dsp_sin(s16 val)
{
    s16 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_SC = BIT2 | BIT1;
        DSP_CORDIC_THETA = (u32)val;
        result = (s16)DSP_CORDIC_SIN;
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/*******************************************************************************
 函数名称：    s16 lks08x_dsp_cos(s16 val)
 功能描述：    使用08x的DSP计算余弦
 输入参数：    u16  val    角度0-65535对应0-360度
 返 回 值：    s16  result 计算结果Q15格式
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
s16 lks08x_dsp_cos(s16 val)
{
    s16 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_SC = BIT2 | BIT1;
        DSP_CORDIC_THETA = (u32)val;
        result = (s16)DSP_CORDIC_COS;
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/*******************************************************************************
 函数名称：    u16 lks08x_dsp_rms(s16 a,s16 b)
 功能描述：    使用08x的DSP计算均方根
 输入参数：    s16 a,b
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
u16 lks08x_dsp_rms(s16 a, s16 b)
{
    u16 c;
    u16 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        //先触发计算
        //在计算的过程中判断数据是否可能溢出
        a = (a > 0) ? a : -a;
        b = (b > 0) ? b : -b;
        c = (u16)(a + b);
        SYS_SoftResetModule(SYS_Module_DSP);
        if (c > 32767) // 当数据可能溢出的时候降低1位精度并重新开始计算
        {
            DSP_CORDIC_X = (u32)(a >> 1);
            DSP_CORDIC_Y = (u32)(b >> 1);
            result = (u16)DSP_CORDIC_MOD;
            result <<= 1;
        }
        else // 正常计算
        {
            DSP_CORDIC_X = (u32)a;
            DSP_CORDIC_Y = (u32)b;
            result = (u16)DSP_CORDIC_MOD;
        }
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/*******************************************************************************
 函数名称：    u16 lks08x_dsp_arctan(s16 x,s16 y)
 功能描述：    使用08x的DSP计算反正切
 输入参数：    s16  x,y
 返 回 值：    计算结果 角度0-65535对应0-360度
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
u16 lks08x_dsp_arctan(s16 x, s16 y)
{
    u16 a;
    u8 i;
    u16 result = 0;
    u8 dsp_flg_old;
    a = (u16)((x > 0) ? x : -x);
    a = (u16)((y > 0) ? a + y : a - y);
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
                    // 08x的DSP在计算角度时必须保证(x*x+y*y)<32767
                    SYS_SoftResetModule(SYS_Module_DSP);
                    DSP_CORDIC_X = (u32)x >> 1;
                    DSP_CORDIC_Y = (u32)y >> 1;
                }
                else
                {
                    // 08x的DSP在计算atan时为提高精度，应尽可能的放到X和Y的幅值
                    SYS_SoftResetModule(SYS_Module_DSP);
                    DSP_CORDIC_X = (u32)x << (i - 1);
                    DSP_CORDIC_Y = (u32)y << (i - 1);
                }
                result = (u16)DSP_CORDIC_ARCTAN;
                break;
            }
        }
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/*******************************************************************************
 函数名称：    s32 lks08x_dsp_div(s32 a,s16 b)
 功能描述：    使用08x的DSP计算除法
 输入参数：    s32  a         被除数
               s16  b         除数
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
s32 lks08x_dsp_div(s32 a, s16 b)
{
    s32 c;
    s32 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_DID = (u32)a;
        DSP_DIS = (u32)b;
        if (b == (s16)0x8000)
        {
            c = -a - 1;
            result = (c >> 15) + 1;
        }
        else if (b == 0)
        {
            result = 0;
        }
        else
        {
            if (a != (s16)0x80000000)
            {
                result = (s32)DSP_QUO;
            }
            else
            {
                a >>= 1;
                DSP_DID = (u32)a;
                DSP_DIS = (u32)b;
                result = ((s32)DSP_QUO)<< 1;
            }
        }
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/*******************************************************************************
 函数名称：    s32 lks08x_dsp_mod(s32 a,s16 b)
 功能描述：    使用08x的DSP求模
 输入参数：    s32  a         被除数
               s16  b         除数
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
s32 lks08x_dsp_mod(s32 a, s16 b)
{
    s32 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_DID = (u32)a;
        DSP_DIS = (u32)b;
        if (b == 0)
        {
            result = a;
        }
        else
        {
            result = (s32)DSP_REM;
        }
    } while (dsp_flg_old != dsp_flg);
    return result;
}
/*******************************************************************************
 函数名称：    u16 lks08x_dsp_sqrt(u32 val)
 功能描述：    使用08x的DSP开平凡
 输入参数：    u32 val 被开方数
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022.03.10    V1.0           YangZJ            创建
 *******************************************************************************/
u16 lks08x_dsp_sqrt(u32 val)
{
    u16 result;
    u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_RAD = val;
        result = (u16)DSP_SQRT;
    } while (dsp_flg_old != dsp_flg);
    return result;
}
