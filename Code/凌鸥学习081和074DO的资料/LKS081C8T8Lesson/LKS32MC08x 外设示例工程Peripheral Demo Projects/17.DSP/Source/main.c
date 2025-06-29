/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Main.c
 * 文件标识：
 * 内容摘要： 工程主代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： 李鹏
 * 完成日期： 2015年11月5日
 *
 * 修改记录1：
 * 修改日期：2015年11月5日
 * 版 本 号：V 1.0
 * 修 改 人：李鹏
 * 修改内容：创建
 *
 *******************************************************************************/
#include "hardware_config.h"
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    测试说明：		   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
float sin_Vlaue = 0;
float cos_Vlaue = 0;
s16 Angle = 5461; //角度范围(-32768 ~ 32767) 对应 (–π~π) 。

int16_t sin1,cos1,rms1,arctan1,c1,mod1,sqrt1;
int16_t sin2,cos2,rms2,arctan2,c2,mod2,sqrt2;
int main(void)
{
	u32 i = 0;
    
    
    DSP_Init();
    
    DSP_CALC_SIN(sin1, 0)    ;
    DSP_CALC_COS(cos1, 0)   ;
    DSP_CALC_RMS(rms1, 1000, 1000)  ;
    DSP_CALC_ARCTAN(arctan1, 1000, 1000);
    DSP_CALC_DIV(c1, 1000, 10)   ;
    DSP_CALC_MOD(mod1, 1000, 1000)        ;
    DSP_CALC_SQRT(sqrt1, 1000*1000) ;
    
    arctan2= DSP_arctan(1000,1000);
    c2= DSP_div(1000,10);
    sin2= DSP_sin(0);
    cos2= DSP_cos(0);
    rms2= DSP_rms(1000, 1000);
    mod2= DSP_mod(1000, 1000);
    sqrt2= DSP_sqrt(1000*1000);

    
    
	while (1)
	{
		Trig_Functions(Angle);
		sin_Vlaue = (float)(Local_Components.hSin) / 0x7FFF; //转换为-1.0到1.0范围内
		cos_Vlaue = (float)(Local_Components.hCos) / 0x7FFF;
		/*Local_Components.hSin值：其中最高位即BIT15为符号位（0为正数，1为负数），剩下15位是数值位，最大数值1对应0x7FFF，但是由于逼近计算所以接近0x7FFF*/
		i = 60000;
		while (i--)
			;
	}
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
