#include "delay.h"
#include "stm32f103c8t6_lib.h" //ͷ�ļ�
#include "stm32f10x.h"

// ����һ�ſ�����,���°���KEY1����LED1,�ɿ�����KEY1Ϩ��LED1

int main(void)
{
    hardware_init();
    while (1)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) // ��Ϊ���������ǵ͵�ƽ.�����жϰ����Ƿ���
        {
            delay_us(100); // ����
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
                ;                             // �ȴ������ɿ�
            inversion_led(GPIOB, GPIO_Pin_0); // ��������,��תLED1
        }
    }
}
