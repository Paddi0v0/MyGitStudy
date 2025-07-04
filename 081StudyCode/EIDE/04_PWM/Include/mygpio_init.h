#ifndef __MYGPIO_INIT_H_
#define __MYGPIO_INIT_H_

#include "lks32mc08x_lib.h"

void GPIO_init(void);
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif
