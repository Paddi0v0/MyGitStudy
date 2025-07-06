
/*-----------------------------------------------------------------------------*/
/* Including Files											                   */
/*-----------------------------------------------------------------------------*/
#include "hardinit.h"
#include "comdata.h"


volatile u8 jumpFlg = 0;



int main()
{

    __disable_irq();
    SYS_WR_PROTECT = PSW_SYS_PROTECT;

	  Clock_Init();
    InitRecvData();
    InitHexData();
	  InitCom();

    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_EnableIRQ(TIMER0_IRQn);

 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
    __enable_irq();
   
    while(1)
	{
		CheckRecvData();
		
		if(jumpFlg)
		{
			jumpFlg = 0;
			StartUserProc();			  
		}
	}
}
