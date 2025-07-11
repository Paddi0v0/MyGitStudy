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
 * 修改日期：2021年8月25日
 * 版 本 号：V 1.0
 * 修 改 人：HMG
 * 修改内容：
 *
 *******************************************************************************/
#include "hardware_config.h"

/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    测试说明：本实验只使用P0.14（UTIMER0_CH1）进行外部PWM频率捕获，捕获频率
              在1KHZ以内准确，如果需要捕获几十KHz的波形需求，请联系凌鸥技术人员
			   运行效果为：将P0.14口输入PWM波，通过Debug查看InPut_Pulse频率值
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
extern u32 g_wuInPut_PulseFreq; //脉冲周期计数值
u16 g_wuInPutPulse = 0;    //滤波后，输入PWM频率 单位HZ
u16 g_wuOrigInPutPulse = 0;//滤波前，输入PWM频率 单位HZ
int main(void)
{ 
	Hardware_init(); /* 硬件初始化 */
	InPutPulse_init(0.01);//根据频率调节滤波系数
	while (1)
	{
		g_wuOrigInPutPulse = (MCU_MCLK/g_wuInPut_PulseFreq)+1; //注意实验UTIMER频率为MCU_MCLK，若UTIMER频率为48MHZ需要MCU_MCLK/2，脉冲频率值 单位HZ
		g_wuInPutPulse = InPutPulse_filter(g_wuOrigInPutPulse);
	}
}


	


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
