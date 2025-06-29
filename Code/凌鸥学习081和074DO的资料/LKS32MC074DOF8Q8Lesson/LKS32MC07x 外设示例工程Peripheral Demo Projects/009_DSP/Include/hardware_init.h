/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.h
 * 文件标识：
 * 内容摘要： 硬件初始化头文件定义
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/
#ifndef __HARDWARE_INIT_H
#define __HARDWARE_INIT_H

#include "lks32mc07x_lib.h"

/*定义系统中断systick 时间 500us*/
/*系统 systick中断频率为2Khz*/
#define	SYS_TICK_FREQUENCY	2000	
#define	FACTOR_MS_DELAY			SYS_TICK_FREQUENCY/1000

typedef struct
{
    s16 hCos;
    s16 hSin;
} stru_TrigComponents;


extern stru_TrigComponents Local_Components;
extern stru_TrigComponents Trig_Functions(s16 hAngle);

void Clock_Init(void);
void Hardware_init(void);
void SoftDelay(u32 cnt);

int Systick_init(uint32_t ticks);
void delay_ms(__IO uint32_t nTime);

#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

