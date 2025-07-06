#include "delay.h"
#include "stm32f103c8t6_lib.h" //头文件
#include "stm32f10x.h"

// 洋桃一号开发板,按下按键KEY1点亮LED1,松开按键KEY1熄灭LED1

int main(void)
{
    hardware_init();
    while (1)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) // 因为按键按下是低电平.所以判断按键是否按下
        {
            delay_us(100); // 消抖
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
                ;                             // 等待按键松开
            inversion_led(GPIOB, GPIO_Pin_0); // 按键按下,翻转LED1
        }
    }
}
