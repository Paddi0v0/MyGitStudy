#include <stdint.h>
#include "delay.h"
#include "stm32f103c8t6_lib.h"

int main(void)
{
    // 1. 开启对应时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 2. 配置对应GPIO引脚
    GPIOB->CRL = 0;
    GPIOB->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0;

    // 3. 配置对应引脚输出
    // GPIOB->ODR |= GPIO_ODR_ODR0 | GPIO_ODR_ODR1;
    GPIOB->BSRR |= GPIO_BSRR_BR0 | GPIO_BSRR_BR1;

    while (1)
    {
        GPIOB->BSRR |= GPIO_BSRR_BS0;
        delay_ms(500);
        GPIOB->BSRR |= GPIO_BSRR_BR0;
        GPIOB->BSRR |= GPIO_BSRR_BS1;
        delay_ms(500);
        GPIOB->BSRR |= GPIO_BSRR_BR1;
    }
}
