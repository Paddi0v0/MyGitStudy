/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： KeyScan.h
 * 文件标识：
 * 内容摘要： KeyScan  & Led
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2019年12月19日
 *
 *******************************************************************************/
#ifndef __KEYSCAN_H
#define __KEYSCAN_H

#include "basic.h"
#include "lks32mc07x.h"
#include "lks32mc07x_gpio.h"

#define KEY_START GPIO2, GPIO_Pin_11
#define KEY_STOP  GPIO2, GPIO_Pin_12

void KeyScan(void);
#endif

