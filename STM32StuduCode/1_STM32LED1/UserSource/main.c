#include "stm32f103c8t6_lib.h" //ͷ�ļ�

// ����һ�ſ�����,����LED1,��GPIOB��0�ڽ��в���

int main(void)
{
    gpio_init();
    while (1)
    {
        led_on();
    }
}
