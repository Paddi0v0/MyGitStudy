#include "stm32f103c8t6_lib.h"

void led_on()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
void led_off()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}