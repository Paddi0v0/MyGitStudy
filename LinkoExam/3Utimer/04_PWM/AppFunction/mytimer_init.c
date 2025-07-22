#include "lks32mc08x_lib.h"

#define TH_VALUE 1199 // PWM 周期门限 (=10KHz)
void Timer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerStrutInit(&TIM_InitStruct);                   /* Timer结构体初始化*/
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP;  /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None; /* 无捕获*/
    TIM_InitStruct.Timer_CH0Output = 0;                    /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP;  /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH1Output = 0;                                 /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = TH_VALUE;                                 /* 定时器计数门限初始值1200-1*/
    TIM_InitStruct.Timer_CMP0 = 600;                                  /* 设置比较模式的CH0比较初始值600 */
    TIM_InitStruct.Timer_CMP1 = 600;                                  /* 设置比较模式的CH1比较初始值600 */
    TIM_InitStruct.Timer_Filter0 = 0;                                   /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_Filter1 = 0;                                   /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div8;                       /* 设置Timer模块时钟8分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_Zero; /* 开启Timer模块比较中断和过零中断*/
    TIM_TimerInit(TIMER0, &TIM_InitStruct);
    TIM_TimerCmd(TIMER0, ENABLE); /* Timer0 模块使能 */
}

/*
 * 下列两只比较寄存器在总线层面占 32 bit 地址宽度，
 * 但根据数据手册仅低 16 bit (bit0-15) 有效，用于存放比较值。
 * 写入 0-0xFFFF 之间任何数值皆安全；例如 29999 (0x752F) 会被存入低 16 位，
 * 高 16 位写入的 0 被硬件丢弃，无副作用。
 * 因此这里仍按 32-bit 指针定义，保证编译器使用 word 指令访问外设。
 */

/*
 * 另外：若写入值 >0xFFFF，硬件只截取低 16 位；若常量本身超过 32 bit，
 * 编译器会报溢出错误，代码无法通过编译，因此不存在真正的"写进寄存器才越界"。
 */
// #define UNT1_CMP0 (*(volatile uint32_t *)0x4001182C) // TIMER1_CH0 比较寄存器 (低 16 位有效)
// #define UNT1_CMP1 (*(volatile uint32_t *)0x40011830) // TIMER1_CH1 比较寄存器 (低 16 位有效)

/*
void set_cmp(uint16_t value) // 动态修改两路比较寄存器
{
    UNT1_CMP0 = value; // 写入 CH0 → LED1 占空比
    UNT1_CMP1 = value; // 写入 CH1 → LED2 占空比
}
*/
/*
int getTh_Value()
{
    return TH_VALUE; // 返回当前设置的 TH，用于外部计算占空比
}
*/
