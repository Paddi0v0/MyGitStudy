/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： LKS32MC081_DMA.c
 * 文件标识：
 * 内容摘要： DMA外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年08月1日
 *
 * 修改记录1：
 * 修改日期：2020年08月1日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet
 * 修改内容：创建
 *
 * 修改记录2：
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/
#include "lks32mc08x_DMA.h"
#include "string.h"

/*******************************************************************************
 函数名称：    void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
 功能描述：    DMA结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.08.1      V1.0           howlet              创建
 *******************************************************************************/
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
{
    memset(DMAInitStruct, 0, sizeof(DMA_InitTypeDef));
}

/*******************************************************************************
 函数名称：    void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
 功能描述：    DMA初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.08.1      V1.0           howlet              创建
 *******************************************************************************/
void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
{
    DMA_CTRL  = 0x0000;
    /* 通道配置寄存器 斌值 */
    DMAx->DMA_CCR = 0;
    DMAx->DMA_CTMS = DMAInitStruct->DMA_TIMES | (DMAInitStruct->DMA_ROUND<<16); /* 传输次数寄存器 */
    DMAx->DMA_CPAR = DMAInitStruct->DMA_CPAR;   /* 外设地址寄存器 */
    DMAx->DMA_CMAR = DMAInitStruct->DMA_CMAR;   /* 内存地址寄存器 */
    DMAx->DMA_CCR = DMAInitStruct->DMA_Channel_EN | (DMAInitStruct->DMA_IRQ_EN<<1) | (DMAInitStruct->DMA_DIR<<4) |\
                    (DMAInitStruct->DMA_CIRC<<5) | (DMAInitStruct->DMA_PINC<<6) | (DMAInitStruct->DMA_MINC<<7) |\
                    (DMAInitStruct->DMA_PBTW<<8) | (DMAInitStruct->DMA_MBTW<<10) | (DMAInitStruct->DMA_REQ_EN<<12);

    DMA_CTRL  = 0x0001;  /*enable dma, mcu has higher priorit */
}  


