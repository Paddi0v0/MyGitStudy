#include <stdint.h>
#include "stm32f103c8t6_lib.h"

int main(void)
{
    // 1. 时钟配置
    // *(volatile uint32_t *)(0x40021000 + 0x18) = 8; // 开启GPIOB的时钟
    // RCC->APB2ENR &= ~0x00000008; // 关闭GPIOB的时钟 只操作GPIOB可以不写
    // RCC->APB2ENR = 0x8; // 开启GPIOB的时钟
    // RCC->APB2ENR |= 1 << 3;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    // 2. GPIO工作模式配置
    // *(volatile uint32_t *)(0x40010c00 + 0x00) = 0x11; // 设置GPIOB的第0和1引脚为:通用推挽输出模式 输出最大速度10MHz
    // GPIOB->CRL = 0x11;
    // GPIOB->CRL &= ~((0xf << 0) | (0xf << 4)); // 先清除 PB0、PB1 的 4 位配置
    // GPIOB->CRL |= (1 << 0) | (1 << 4);        // 配置 PB0、PB1 为通用推挽输出 10MHz (0x1)
    /*
    GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_MODE1); // 清除 PB0、PB1 的 4 位配置
    GPIOB->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0; // 配置 PB0、PB1 为通用推挽输出 10MHz (0x1)
    GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1);   // 清除 PB0、PB1 的 4 位配置
    下面有一个更好的写法
    */
    GPIOB->CRL = 0;
    GPIOB->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0;
    

    // PB1输出高电平
    // *(volatile uint32_t *)(0x40010c00 + 0x0c) = 0x3; // 设置GPIOB的第0和1引脚为:高电平
    // GPIOB->ODR = 0x3;
    // GPIOB->ODR |= (1 << 0) | (1 << 1);
     GPIOB->ODR |= GPIO_ODR_ODR0 | GPIO_ODR_ODR1;
    // GPIOB->ODR &= ~(GPIO_ODR_ODR0 | GPIO_ODR_ODR1);
    while (1)
    {
        ;
    }
}
