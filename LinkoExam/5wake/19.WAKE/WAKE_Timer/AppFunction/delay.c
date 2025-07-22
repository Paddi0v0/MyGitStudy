#include "delay.h"
#include "lks32mc08x_lib.h"

static u32 fac_us = 0;
static u32 fac_ms = 0;

void delay_init(u32 SYSCLK)
{
 	SysTick->CTRL = 1 << 2;					//SYSTICK使用内部时钟源
	fac_us=SYSCLK;						//不论是否使用OS,fac_us都需要使用,每产生1us，需要多少次数，因为是通过一个计数寄存器计时的。
	fac_ms=(u32)fac_us*1000;				//非OS下,代表每个ms需要的systick时钟数   
}

void delay_us(u32 nus)
{
	u32 temp;	    	 
	SysTick->LOAD=(u32)nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL |= 0x01 ;      				//开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL |= 0x00;      	 			//关闭计数器
	SysTick->VAL =0X00;       				//清空计数器 
}

void delay_xms(u32 nms)
{
	volatile u32 temp, val = 0;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL |=0x01 ;          			//开始倒数  
	do
	{
		temp=SysTick->CTRL;;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL |=0x00;       				//关闭计数器
	SysTick->VAL =0X00;     		  		//清空计数器	  	    
} 
//延时nms 
//nms:0~65535
void delay_ms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++)
    {
        delay_us(1000);
    }
}
