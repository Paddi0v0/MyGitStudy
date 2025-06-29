#include "lks32mc08x.h"

void TIMER0_IRQHandler(void)
{
    if(UTIMER_IF & BIT0)
    {
        UTIMER_IF = BIT0;
    }
}
