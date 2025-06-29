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
 * 修 改 人：李鹏
 * 修改内容：创建
 *
 *******************************************************************************/
#include "hardware_config.h"
#include "delay.h"
#include "gpio_led.h"
#include "gpio_key.h"


uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    测试说明：stop按键开启休眠模式，例程配置休眠P0.0—IO高电平唤醒。
              注意休眠中断NVIC一定放在休眠函数前面，因为__WFI();是等待中断执行，
							所以在执行__WFI();之前，先使能中断。
			        
 运行效果为：  程序烧录后，上电2S后，P0.6电平间隔500ms翻转一次，当按下STOP
				      按键芯片进入休眠模式，P0.6电平不再翻转。当P0.0输入高电平信号时，P0.6电平
				      继续翻转，且P0.7电平翻转一次（P0.7作用：检测到唤醒时能够进入唤醒中断）。
							
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
extern u8 Awaken_Flag;
int main(void)
{
	u8 key = 0 , delay_value = 0;;
	Hardware_init();   /* 硬件初始化 */
	delay_ms(2000);    /* 防止芯片上电即进入低功耗模式，导致我发烧录程序*/
/***************************************************************************/
	SYS_SetWakeInterval(SYS_WakeInterval_4s); //Utimer 4秒唤醒
	SYS_SetWakeIO(GPIO0_0_POL, Low_Level);	  //设置高电平唤醒
	GPIO0_POE |= BIT0;
	GPIO_LED(ALL_OFF); //初始化所有LED全灭
	while (1)
	{
		key = GPIO_KEY_Scan(0);
		switch (key)
		{
		case start_PRES:
         
			break;
		case stop_PRES:	   
		     SYS_FallSleepMode();   //开启睡眠模式（休眠函数不能放入休眠中断内）
			break;		
		}
		delay_value++;
		if(delay_value > 25)
		{
		  Invers_GPIO(GPIO0,GPIO_Pin_6);
			delay_value = 0;
		}
		if(Awaken_Flag)
		{
			Awaken_Flag = 0;
		  Invers_GPIO(GPIO0,GPIO_Pin_7);
		}
		delay_ms(20);  /* 延时20ms*/
	}
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
