/*********************************************************************************************
模板制作：  杜洋工作室/洋桃电子
程序名：	使用定时器PWM输出1kHz的方波信号
编写人：		
编写时间：	
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

说明：
 # 本模板加载了STM32F103内部的RCC时钟设置，并加入了利用滴答定时器的延时函数。
 # 可根据自己的需要增加或删减。

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{                        //主程序
    RCC_Configuration(); //时钟设置
    LED_Init();
    while (1)
    {

    }
}
