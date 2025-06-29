#include "lks32mc08x.h"
#include "basic.h"
#include "delay.h"
#include <stdbool.h>

#define KEY_START	(GPIO2_PDI & BIT11)

void Clock_Init(void);
bool key_scan(void);

int main(void)
{
	__disable_irq();

	Clock_Init();
	delay_init(96);

	REG32(0xE000ED08) = 0x00000A00;//重映射中断向量入口地址
  
	delay_ms(100);
	
	GPIO0_POE |= BIT7;
	GPIO0_PDO |= BIT7;
	
	__enable_irq();
	
	while(1)
	{
		GPIO0_PDO ^= BIT7;
		delay_ms(50);
	}
}

void Clock_Init(void)
{
	SYS_WR_PROTECT  = PSW_SYS_PROTECT;
	SYS_CLK_CFG 	= 0x01FF;//96M
	SYS_SFT_RST = 0x00FF;
	SYS_SFT_RST = 0x0000;
	SYS_CLK_FEN = 0XFFFF;
	SYS_AFE_REGC = 0x01;// add it for the moment
}

bool key_scan()
{
	u16 val = KEY_START;
	if (val == 0)
	{
		delay_ms(10);
		
		val = KEY_START;
		if (val == 0)
		{
			return true;
		}
	}
	
	return false;
}
