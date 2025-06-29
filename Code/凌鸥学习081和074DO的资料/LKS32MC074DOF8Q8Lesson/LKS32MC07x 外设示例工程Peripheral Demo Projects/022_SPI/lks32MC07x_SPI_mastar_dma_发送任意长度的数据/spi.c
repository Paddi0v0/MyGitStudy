#include "LKS32MC07x_spi.h"       
#include "LKS32MC07x_dma.h"

#define SPI_CS_0() GPIO2->BRR = BIT3;
#define SPI_CS_1() GPIO2->BSRR = BIT3;

void spidelaysend(void);
void spi_txdata(uint8_t *addr,uint32_t len);
uint32_t txaddr;
uint32_t txlen; // 剩余发送数据长度
volatile uint32_t spisendstate = 0; // 0 空闲 1正在发送数据
uint32_t sendflg = 0;// 继续发送标志
void spi_txdata(uint8_t *addr,uint32_t len)
{
    spidelaysend();
    SPI_CS_0();
    spisendstate = 1;
    txaddr = ((uint32_t)addr) ;
    txlen = len;
    
    SPI0_IE |= 0x03;
    DMA_CHx_EN(DMA_CHN1, DISABLE);
    DMA_CHN1->SADR = txaddr;
    if(txlen > 255)
    {
        txaddr += 255;
        txlen -= 255;
        DMA_CHN1->CTMS = 255;
    }
    else
    {
        DMA_CHN1->CTMS = txlen;
        txlen = 0;
    }
    DMA_CHx_EN(DMA_CHN1, ENABLE);
    SPI0_TX_DATA = 0x01; // 触发DMA搬运，本次写入不会数据不会混入SPI发送流程
}
void spidelaysend(void)
{
    while(spisendstate == 1);
}

/*******************************************************************************
 函数名称：    void DMA_IRQHandler(void)
 功能描述：    DMA中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void DMA0_IRQHandler(void)
{
    if (DMA0_IF & BIT1) // DMA通道1完成中断标志
	{
		DMA0_IF = BIT1;
        if(txlen == 0)
        {
            DMA_CHN1->SADR = 0; // 发送完毕
        }
        else
        {
            if(txlen > 255)
            {
                DMA_CHN1->CCR &= ~1;
                DMA_CHN1->SADR = txaddr;
                DMA_CHN1->CTMS = 255;
                DMA_CHN1->CCR |= 1;
                sendflg = 1;
                txlen -= 255;
                txaddr += 255;
            }
            else
            {
                DMA_CHN1->CCR &= ~1;
                DMA_CHN1->SADR = txaddr;
                DMA_CHN1->CTMS = txlen;
                DMA_CHN1->CCR |= 1;
                txlen = 0;
                sendflg = 1;
            }
        }
	}
    
}
void SPI0_IRQHandler(void)
{
    SPI0->IE |= 7;
    if(sendflg != 0)
    {
        SPI0->TX_DATA=0xff;// 触发DMA搬运，本次写入不会数据不会混入sPI发送流程
        sendflg = 0;
    }
    else
    {
        SPI_CS_1();
        spisendstate = 0;
    }
}
