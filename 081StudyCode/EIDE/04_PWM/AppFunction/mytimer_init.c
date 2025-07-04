/*
 * mytimer_init.c
 *---------------------------------------------------------------------------
 * 功能：
 *   ? 对 UTIMER1 进行比较模式初始化，为双路呼吸灯准备固定频率 (≈400 Hz) 的 PWM 载波；
 *   ? 外部可通过 set_cmp() 动态调整 CMPT 寄存器，实现占空比变化。
 *---------------------------------------------------------------------------
 * 参数推导：
 *   f_src  = 96 MHz   ，ClockDiv = 8 → f_cnt = 12 MHz
 *   TH     = 29 999   → f_PWM = 12 MHz / 30 000 ≈ 400 Hz
 *   MIN_D  =  2 400   (8 % 最低亮度)
 *---------------------------------------------------------------------------
 */
#include "lks32mc08x_lib.h" // 引入凌鸥官方底层库，包含寄存器与驱动声明

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
#define UNT1_CMP0 (*(volatile uint32_t *)0x4001182C) // TIMER1_CH0 比较寄存器 (低 16 位有效)
#define UNT1_CMP1 (*(volatile uint32_t *)0x40011830) // TIMER1_CH1 比较寄存器 (低 16 位有效)
#define TH_VALUE 29999                               // PWM 周期门限 (≈400 Hz)

void set_cmp(uint16_t value) // 动态修改两路比较寄存器
{
    UNT1_CMP0 = value; // 写入 CH0 → LED1 占空比
    UNT1_CMP1 = value; // 写入 CH1 → LED2 占空比
}
int getTh_Value()
{
    return TH_VALUE; // 返回当前设置的 TH，用于外部计算占空比
}
void Timer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;                   // 声明并保存初始化参数
    TIM_TimerStrutInit(&TIM_InitStruct);                   // 结构体字段清零并设默认值
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP;  // CH0 设为比较模式
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None; // CH0 不做捕获
    TIM_InitStruct.Timer_CH0Output = 1;                    // CNT=0 时输出高电平→LED 高电平点亮
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP;  // CH1 同理
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None; // CH1 不做捕获
    TIM_InitStruct.Timer_CH1Output = 1;                    // CH1 初始输出高电平
    TIM_InitStruct.Timer_TH = TH_VALUE;                    // 设定周期计数门限
    TIM_InitStruct.Timer_CMP0 = 0;                         // 初始占空比 0 % → 最暗
    TIM_InitStruct.Timer_CMP1 = 0;                         // 同步 CH1
    TIM_InitStruct.Timer_Filter0 = 0;                      // 捕获滤波关闭
    TIM_InitStruct.Timer_Filter1 = 0;                      // 捕获滤波关闭
    TIM_InitStruct.Timer_ClockDiv = ECD_Clk_Div8;          // 96 MHz÷8 → 12 MHz 计数时钟
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_Zero;       // 仅使能过零中断
    TIM_TimerInit(TIMER1, &TIM_InitStruct);                // 把配置写进 TIMER1 寄存器
    TIM_TimerCmd(TIMER1, ENABLE);                          // 使能 TIMER1 开始计数
}
