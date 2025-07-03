#include "hardware_init.h"
#include "lks32mc08x_lib.h"
#include "mygpio_init.h"
#include "mytimer_init.h"

void Hardware_init(void)
{
    // 默认写法
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/

    GPIO_init(); /* GPIO初始化 */

    SoftDelay(100);       /* 等待硬件初始化完毕*/
    SYS_WR_PROTECT = 0x0; /*关闭系统寄存器写操作*/
#if POWER_MODE
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0); /*MCU电源中断使能函数*/
#else
    SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3); /*MCU电源中断使能函数*/
#endif
    __enable_irq();
}

void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83; /* 解除写保护：用于配置PLL */
    SYS_AFE_REG5 |= BIT15;   /* BIT15:PLLPDN */
#if POWER_MODE
    SYS_VolSelModule(MCU_POWER_5v0);
#else
    SYS_VolSelModule(MCU_POWER_3v3);
#endif
    SoftDelay(100); /* 等待PLL稳定（此操作可能自动使能写保护） */

    /* 需要再次解除写保护以配置时钟寄存器 */
    SYS_WR_PROTECT = 0x7a83;  /* 解除写保护：用于配置时钟 */
    SYS_CLK_CFG = 0x000001ff; /* 选择PLL作为时钟源，分频系数0xFF=96MHz */
    SYS_WR_PROTECT = 0x0;     /* 重新使能写保护 */
}

void SystemInit(void)
{
    Clock_Init(); /* 时钟初始化 */
}

/*
*/
