/*
 * mygpio_init.c
 *---------------------------------------------------------------------------
 * 功能：
 *   1. 将 P0.6 / P0.7 复用为 UTIMER1_CH0 / CH1 输出口，用于驱动两颗 LED；

 *---------------------------------------------------------------------------
 * 关键概念：
 *   ? GPIO_PinAFConfig() 端口复用
 *   ? 两路 LED 物理上共用同一个计数器，不存在相位误差。
 *---------------------------------------------------------------------------
 */
#include "lks32mc08x_lib.h"

void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;  // 定义 GPIO 配置结构体
    GPIO_StructInit(&GPIO_InitStruct); // 清零并写默认值

    /* 备选：纯 GPIO 推挽输出方式调试 LED，可在此解开注释 */
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // 普通输出
    // GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    // GPIO_Init(GPIO0, &GPIO_InitStruct);

    //    GPIO_StructInit(&GPIO_InitStruct);                  // 再次清零，准备 AF 复用配置
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;          // 必须先把模式设为 OUT/AF
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 只用 0.6 / 0.7
    GPIO_Init(GPIO0, &GPIO_InitStruct);                 // 写入寄存器

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF7_TIMER01); // P0.6 复用到 TIM1_CH0
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF7_TIMER01); // P0.7 复用到 TIM1_CH1
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