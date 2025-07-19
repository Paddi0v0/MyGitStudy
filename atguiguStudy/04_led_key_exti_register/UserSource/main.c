#include "stm32f103c8t6_lib.h"

int main(void)
{

    while (1) {
        GPIOB->BSRR |= GPIO_BSRR_BS0;
        delay_ms(500);
        GPIOB->BSRR |= GPIO_BSRR_BR0;
        GPIOB->BSRR |= GPIO_BSRR_BS1;
        delay_ms(500);
        GPIOB->BSRR |= GPIO_BSRR_BR1;
    }
}
