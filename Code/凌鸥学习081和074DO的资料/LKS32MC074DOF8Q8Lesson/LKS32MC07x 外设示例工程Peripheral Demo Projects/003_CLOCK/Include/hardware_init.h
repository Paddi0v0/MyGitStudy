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

#define start_PRES 1 //start
#define stop_PRES 2  //stop

#define key_start GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_11)
#define key_stop GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_12)

void GPIO_init(void);
void Clock_Init(void);
void Hardware_init(void);
void SoftDelay(u32 cnt);
int GPIO_KEY_Scan(u8 mode);
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void UART0_GPIO_init(void);
void UART1_GPIO_init(void);
void UART0_init(void);
void UART1_init(void);


void LED1_ON(void);
void LED2_ON(void);
void LED3_ON(void);

void LED1_OFF(void);
void LED2_OFF(void);
void LED3_OFF(void);

#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

