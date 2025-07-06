#include "stm32f103c8t6_lib.h" //头文件

// 洋桃一号开发板,点亮LED1,对GPIOB的0口进行操作

int main(void)
{
    gpio_init();
    while (1)
    {
        led_on();
    }
}
