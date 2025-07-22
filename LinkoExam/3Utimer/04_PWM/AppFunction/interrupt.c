#include "lks32mc08x_gpio.h"
#include "lks32mc08x_lib.h"

void UTIMER0_IRQHandler(void)
{
    if (TIM_GetIRQFlag(TIMER0, Timer_IRQEna_CH0))
    {
        TIM_ClearIRQFlag(TIMER0, Timer_IRQEna_CH0);
    }
    if (TIM_GetIRQFlag(TIMER0, TIMER_IF_ZERO))
    {
        TIM_ClearIRQFlag(TIMER0, TIMER_IF_ZERO);
    }
}
