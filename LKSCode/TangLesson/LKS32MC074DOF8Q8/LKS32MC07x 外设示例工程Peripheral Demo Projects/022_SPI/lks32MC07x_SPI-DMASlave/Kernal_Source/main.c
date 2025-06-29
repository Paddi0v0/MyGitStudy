/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Main.c
 * 文件标识：
 * 内容摘要： 工程主代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/
#include "hardware_config.h"
#include "global_variable.h"
#include "lks32mc07x_lib.h"

void Hardware_init(void);
void Spi_master_DMA(UINT8 *spi_txdma_data, UINT8 *spi_rxdma_data, u8 spi_len);
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    配置SPI为DMA从模式（程序B），接收和发送8个字节数组，用示波器观察输出 例程芯片对应071
 操作说明，    Debug模式下将“SPISendStartFlag”清零重置DMA（TX）搬运。
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/9      V1.0           Zhujie             创建
 *******************************************************************************/
u8 SPI_SendByte(u8 byte);
UINT8 Tx_data_tbl[32] = {0xf3, 0x3f, 0x11, 0x22, 0x23, 0x44, 0x56, 0x68,0xf3, 0x3f, 0x11, 0x22, 0x23, 0x44, 0x56, 0x68
,0xf3, 0x3f, 0x11, 0x22, 0x23, 0x44, 0x56, 0x68,0xf3, 0x3f, 0x11, 0x22, 0x23, 0x44, 0x56, 0x68}; //数据发送缓冲区
UINT8 Rx_data_tbl[32] = {0};//{0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};												 //接收数据缓冲区
u16 SPISendStartFlag = 0;
int main(void)
{
    Hardware_init();      /* 硬件初始化 */
	  SoftDelay(0xfff);

    for(;;)
    {
			 if(SPISendStartFlag  == 0)//SPI发送数据标志位
			 {
				   
				   DMA0_CTMS1 = 8;
				   DMA0_CTMS2 = 8;
				   SPI0_IE |= 0x03;
				   DMA_CHx_EN(DMA_CHN1,ENABLE);
				   DMA_CHx_EN(DMA_CHN2,ENABLE);
				   SPI0_TX_DATA = 0x01;//触发DMA搬运，本次写入不会数据不会混入SPI发送流程
				   SPISendStartFlag = 1;
			 }
		   SoftDelay(0xfff);
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

