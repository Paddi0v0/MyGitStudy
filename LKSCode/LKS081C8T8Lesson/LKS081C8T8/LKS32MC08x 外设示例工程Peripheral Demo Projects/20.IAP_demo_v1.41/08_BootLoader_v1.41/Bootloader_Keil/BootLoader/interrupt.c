#include "comdata.h"
#include "hardinit.h"

/*******************************************************************************
 函数名称：    void PWRDN_IRQHandler(void)
 功能描述：    电源欠压中断函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/10/19      V1.0           HuangMG           创建
 *******************************************************************************/
void PWRDN_IRQHandler(void)
{
   SYS_VolSelModuleIRQ(); 
}

extern volatile u8 jumpFlg;
extern UINT32 tickCount;

void UTIMER0_IRQHandler(void)
{
    if(UTIMER_IF & BIT0)
    {
        UTIMER_IF = BIT0;
        tickCount++;

        if(tickCount == 100)				// 100*0.5 = 50ms
        {
            //超过等待时间，直接进入用户程序
			      jumpFlg = 1;
            tickCount = 0;
        }
    }
}

void TIMER1_IRQHandler(void)
{
    while(1);
}

void TIMER2_IRQHandler(void)
{
    while(1);
}

void TIMER3_IRQHandler(void)
{
    while(1);
}

void ENCODER0_IRQHandler(void)
{
    while(1);
}

void ENCODER1_IRQHandler(void)
{
    while(1);
}

void I2C0_IRQHandler(void)
{
    while(1);
}

void GPIO_IRQHandler(void)
{
    while(1);
}

static u8 revData0 = 0;
void UART0_IRQHandler(void)
{
    if(UART0_IF & BIT1)								//接收完成
    {
        UART0_IF = BIT1;
		revData0 = UART0_BUFF;
        AddRecvData(revData0);
    }
}

static u8 revData1 = 0;
void UART1_IRQHandler(void)
{
	if(UART1_IF & BIT1)								//接收完成
    {
		UART1_IF = BIT1;
		revData1 = UART1_BUFF;
		AddRecvData(revData1);
    }
}

void HALL_IRQHandler(void)
{
    while(1);
}

void ADC0_IRQHandler(void)
{
    while(1);
}

void ADC1_IRQHandler(void)
{
    while(1);
}

void MCPWM_IRQHandler(void)
{
    while(1);
}

