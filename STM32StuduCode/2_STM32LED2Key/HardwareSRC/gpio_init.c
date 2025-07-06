#include "stm32f103c8t6_lib.h"

void gpio_init(void)
{
    // ��ʼ��LED������GPIOB0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //��ʼ������KEY1������PA0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // ֻ�������Ч,�������ע�͵�
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}