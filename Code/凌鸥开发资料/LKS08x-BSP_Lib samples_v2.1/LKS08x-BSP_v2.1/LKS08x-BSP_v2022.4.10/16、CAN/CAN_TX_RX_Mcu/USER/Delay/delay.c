#include "delay.h"

void delay(u32 cnt)
{
	u32 t_cnt;

	for (t_cnt = 0; t_cnt < cnt; t_cnt++)
	{
		__nop();
	}
}

