#include "stm32f103c8t6_lib.h"

void hardware_init(void)
{
    gpio_init();
}

void led_on()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
void led_off()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}
void inversion_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin) == 0)
    {
        GPIO_SetBits(GPIOx, GPIO_Pin);
    }
    else
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin);
    }
}