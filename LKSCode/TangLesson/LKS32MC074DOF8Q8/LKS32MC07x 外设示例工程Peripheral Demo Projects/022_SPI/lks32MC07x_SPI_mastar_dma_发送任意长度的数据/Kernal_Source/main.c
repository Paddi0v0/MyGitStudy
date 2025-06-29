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

void spi_txdata(uint8_t *addr,uint32_t len);
void spidelaysend(void);
void Hardware_init(void);
void Spi_master_DMA(UINT8 *spi_txdma_data, UINT8 *spi_rxdma_data, u8 spi_len);
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    注意 SPICS使用软件实现
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u8 SPI_SendByte(u8 byte);
volatile uint8_t Tx_data_tbl[4096]; // 数据发送缓冲区
u16 SPISendStartFlag = 0;
int main(void)
{
    Hardware_init(); /* 硬件初始化 */
    int i,j=0;
    for (;;)
    {
        // 初始化数据为全0
        for (i = 0; i < 4096; i++)
        {
            Tx_data_tbl[i] = (uint8_t) 0;
        }
        if(j<4096)
        {
            j++;
        }
        else
        {
            j=0;
        }
        // 为了方便测试，在全0的数据中有一个是 0xff
        Tx_data_tbl[j] = 0xff;
        // 发送数据
        spi_txdata((uint8_t*)Tx_data_tbl,4096);
        // 等待数据发送完毕
        spidelaysend();
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
