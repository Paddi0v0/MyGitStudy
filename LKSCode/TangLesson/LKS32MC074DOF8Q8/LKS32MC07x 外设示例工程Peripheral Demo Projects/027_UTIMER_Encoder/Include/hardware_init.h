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
#include "basic.h"

typedef struct
{
    s32 yk_1;
    u16 coef;
} RC_t;
extern RC_t PWM_DutyRC;

void Clock_Init(void);
void Hardware_init(void);
void SoftDelay(u32 cnt);
void GPIO_init(void);
void UTimer_init(void);
s16 lowPass_filter(RC_t *rc,s16 signal);
#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

