#ifndef __HARDWARE_INIT_H
#define __HARDWARE_INIT_H
#include "stm32f103c8t6_lib.h"

void hardware_init(void);
void led_on();
void led_off();
void inversion_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif