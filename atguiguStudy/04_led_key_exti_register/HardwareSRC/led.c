#include "stm32f10x.h"

void led_init(void)
{
    // 1. 开启对应时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 2. 配置对应GPIO引脚
    GPIOB->CRL = 0;
    GPIOB->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0;
}
void led_on(uint8_t led)
{
}
void led_off(uint8_t led);