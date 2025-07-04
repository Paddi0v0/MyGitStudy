/*
 * hardware_init.c
 *---------------------------------------------------------------------------
 * 功能概述：
 *   完成本实验所需的全部芯片级初始化流程，包含：
 *     1. 全局中断屏蔽与系统寄存器写保护解锁；
 *     2. FLASH 预取加速打开；
 *     3. GPIO / UTimer 外设初始化调用；
 *     4. NVIC 中断优先级配置并使能 UTIMER1 中断；
 *     5. (可选) 电源电压检测中断打开；
 *     6. 对系统时钟进行 PLL 配置（见 Clock_Init）。
 *---------------------------------------------------------------------------
 * 设计思路：
 *   ? 先关中断 → 避免初始化过程中被意外中断打断。
 *   ? 对系统关键寄存器解锁后，依次初始化 GPIO → Timer，保证外设已有稳定时
 *     钟源和配置。
 *   ? 所有寄存器解锁/上锁流程都显式写出，方便后续维护。
 *---------------------------------------------------------------------------
 */
#include "lks32mc08x_lib.h"

void Hardware_init(void)
{
    // 默认写法
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /* 解除系统寄存器写保护 */
    FLASH_CFG |= 0x00080000; /* 打开 FLASH 预取加速 */

    GPIO_init();  /* 初始化 GPIO (LED 引脚复用) */
    Timer_init(); /* 初始化 UTimer1 (PWM 载波) */

    SoftDelay(100); /* 简易延时，等待外设稳定 */

    NVIC_SetPriority(TIMER1_IRQn, 0); /* 设置 UTimer1 中断优先级为最高 */
    NVIC_EnableIRQ(TIMER1_IRQn);      /* 使能 UTimer1 ZERO 中断 */

    SYS_WR_PROTECT = 0x0; /*关闭系统寄存器写操作*/
#if POWER_MODE
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0); /*MCU电源中断使能函数*/
#else
    SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3); /*MCU电源中断使能函数*/
#endif
    __enable_irq(); /* 打开全局中断 */
}

void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83; /* 解锁寄存器以配置 PLL */
    SYS_AFE_REG5 |= BIT15;   /* 解除 PLL 断电位，开始锁相 */
#if POWER_MODE
    SYS_VolSelModule(MCU_POWER_5v0);
#else
    SYS_VolSelModule(MCU_POWER_3v3);
#endif
    SoftDelay(100); /* 等待PLL稳定（此操作可能自动使能写保护） */

    /* 需要再次解锁写保护以配置时钟寄存器 */
    SYS_WR_PROTECT = 0x7a83;  /* 再次解锁，用于写 CLK_CFG */
    SYS_CLK_CFG = 0x000001ff; /* 选择 PLL，设置分频=0xFF→96MHz */
    SYS_WR_PROTECT = 0x0;     /* 锁定寄存器，防误写 */
}

void SystemInit(void)
{
    Clock_Init(); /* 调用上面函数完成系统时钟初始化 */
}

void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt; // volatile 防止编译器优化

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP(); // 占位空指令，消耗一个时钟周期
    }
}
