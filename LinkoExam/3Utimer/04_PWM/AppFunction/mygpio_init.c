#include "lks32mc08x_lib.h"

void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体

    /* 配置UTimer0  TIM0_CH0: P0.15 */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF7_TIMER01); //P0.15复用为timer0的输出模式
}
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); // 读取当前输出电平
    if (reg)
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin); // 如果为高，就拉低
        return 0;                        // 返回翻转后的电平
    }
    else
    {
        GPIO_SetBits(GPIOx, GPIO_Pin); // 如果为低，就拉高
        return 1;                      // 返回翻转后的电平
    }
}