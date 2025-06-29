/*******************************************************************************
 * 版权所�? (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称�? hardware_init.h
 * 文件标识�?
 * 内容摘要�? 硬件初始化头文件定义
 * 其它说明�? �?
 * 当前版本�? V 1.0
 * �?    者： Howlet Li
 * 完成日期�? 2020�?8�?16�?
 *
 * 修改记录1�?
 * 修改日期�?2020�?8�?16�?
 * �? �? 号：V 1.0
 * �? �? 人：Howlet Li
 * 修改内容：创�?
 *
 *******************************************************************************/
#ifndef __HARDWARE_INIT_H
#define __HARDWARE_INIT_H

#include "lks32mc07x_lib.h"

void GPIO_init(void);
void Clock_Init(void);
void Hardware_init(void);
void SoftDelay(u32 cnt);
void DMA_init(void);
void UART1_init(void);
#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

