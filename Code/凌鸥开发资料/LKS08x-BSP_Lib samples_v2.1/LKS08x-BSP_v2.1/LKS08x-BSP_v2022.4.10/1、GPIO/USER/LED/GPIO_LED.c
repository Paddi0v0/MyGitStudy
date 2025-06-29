/*******************************************************************************
 * 版权所有 (
 *
 * 文件名称： GPIO_LED.c
 * 文件标识：
 * 内容摘要： LED显示配置程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： 
 * 完成日期： 2021年2月23日
 *
 * 修改记录1：
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/

#include "gpio_led.h"
#include "delay.h"

//LED状态显示函数
//mode:1,全亮
//     2,全灭
//     3,闪烁
//		 4,流水灯
void GPIO_LED(u8 mode)
{
	 int i = 0;
   switch(mode)
	 {
	   case ALL_ON:
			    LED1_ON;
		      LED2_ON;
		      LED3_ON;
		 break;
			 
		 case ALL_OFF:
					LED1_OFF;
					LED2_OFF;
					LED3_OFF;
		 break;
			 
		 case Blink:
			  
			   for(i = 0 ; i<250 ; i++)
		      {
						LED1_ON;
						LED2_ON;
						LED3_ON;
						delay(0xffff);
		      }
				 for(i = 0 ; i<250 ; i++)
		      {	
						LED1_OFF;
						LED2_OFF;
						LED3_OFF;
						delay(0xffff);
					}
		 break;
			 
		 case waterfall_light:
			    LED1_ON;
		      LED2_OFF;
					LED3_OFF; 
		      for(i = 0 ; i<100 ; i++)
		      {
		       delay(0xffff);
					}
		      LED2_ON;
		      LED1_OFF;
					LED3_OFF; 
		      for(i = 0 ; i<100 ; i++)
		      {
		       delay(0xffff);
					}
		      LED3_ON;		    
					LED1_OFF;
					LED2_OFF;
		      for(i = 0 ; i<100 ; i++)
		      {
		       delay(0xffff);
					}
		 break;	 
	 }		 
}







