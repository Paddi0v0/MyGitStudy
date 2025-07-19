#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"

void led_init(void);
void led_on(uint8_t led);
void led_off(uint8_t led);

#endif
