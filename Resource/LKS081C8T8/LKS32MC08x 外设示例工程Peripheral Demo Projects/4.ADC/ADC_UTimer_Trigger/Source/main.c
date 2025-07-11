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
 * 修改日期：2021年8月27日
 * 版 本 号：V 1.0
 * 修 改 人：HMG
 * 修改内容：创建
 *
 *******************************************************************************/
#include "hardware_init.h"

/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    本实验配置了UTIMER2和UTIMER3的CH0和CH1比较中断，为ADC的4段的触发信号，
               不过实际就使用UTIMER2_CH0的比较中断作为ADC的第一段触发，采集两个通道，
							 两个通道都是采集ADC_CH9输入的电位器电压。
			 
 运行效果为： 使用081demo板，例程烧录后，旋转电位器，进入Debug模式，查看Voltage_Value
             电位器电压，单位V
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/25      V1.0         HuangMG             创建
 *******************************************************************************/
int main(void)
{
	Hardware_init();   /* 硬件初始化 */
	while (1)
	{
		SoftDelay(0xFFFF);
	}
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
