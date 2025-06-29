#ifndef __GPIO_LED_H__
#define __GPIO_LED__H__
#include "lks32mc08x_sys.h"

#define ALL_ON          1 //全亮
#define ALL_OFF         2 //全灭
#define Blink           3 //闪烁
#define waterfall_light 4 //流水灯


//LED1 2 3输出低
#define LED1_OFF  GPIO_ResetBits(GPIO0 , GPIO_Pin_6)
#define LED2_OFF  GPIO_ResetBits(GPIO0 , GPIO_Pin_7)
#define LED3_OFF  GPIO_SetBits(GPIO0 , GPIO_Pin_3)

//LED1 2 3输出高
#define LED1_ON  GPIO_SetBits(GPIO0 , GPIO_Pin_6)
#define LED2_ON  GPIO_SetBits(GPIO0 , GPIO_Pin_7)
#define LED3_ON  GPIO_ResetBits(GPIO0 , GPIO_Pin_3)

void GPIO_LED(u8 mode);
void Invers_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);//GPIO电平翻转函数
#endif

