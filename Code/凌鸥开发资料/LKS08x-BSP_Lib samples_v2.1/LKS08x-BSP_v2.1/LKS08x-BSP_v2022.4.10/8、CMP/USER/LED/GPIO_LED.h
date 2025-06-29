#ifndef __GPIO_LED_H__
#define __GPIO_LED__H__
#include "lks32mc08x_sys.h"

#define ALL_ON          1 //ȫ��
#define ALL_OFF         2 //ȫ��
#define Blink           3 //��˸
#define waterfall_light 4 //��ˮ��


//LED1 2 3�����
#define LED1_OFF  GPIO_ResetBits(GPIO0 , GPIO_Pin_6)
#define LED2_OFF  GPIO_ResetBits(GPIO0 , GPIO_Pin_7)
#define LED3_OFF  GPIO_SetBits(GPIO0 , GPIO_Pin_3)

//LED1 2 3�����
#define LED1_ON  GPIO_SetBits(GPIO0 , GPIO_Pin_6)
#define LED2_ON  GPIO_SetBits(GPIO0 , GPIO_Pin_7)
#define LED3_ON  GPIO_ResetBits(GPIO0 , GPIO_Pin_3)

void GPIO_LED(u8 mode);
void Invers_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);//GPIO��ƽ��ת����
#endif

