/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * 文件名称： hardware_init.h
 * 内容摘要： 硬件初始化头文件定义
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 文件作用：
 *   本文件定义了硬件初始化相关的函数声明、宏定义和数据结构。
 *   主要功能包括：
 *     1. 定义按键状态值（start_PRES, stop_PRES）
 *     2. 定义按键引脚读取宏（key_start, key_stop）
 *     3. 声明硬件初始化函数（GPIO初始化、时钟初始化等）
 *   使用说明：
 *     1. 在需要使用这些函数或宏的源文件中包含本头文件
 *     2. 调用Hardware_init()函数进行硬件初始化（通常在main函数开始处调用）
 *     3. 使用GPIO_KEY_Scan()函数扫描按键状态
 *     4. 使用Invers_GPIO()函数翻转指定GPIO引脚的电平
 *******************************************************************************/
#ifndef __HARDWARE_INIT_H // 头文件保护宏：防止重复包含
#define __HARDWARE_INIT_H // 定义保护宏标识

#include "lks32mc08x_lib.h" // 包含芯片外设驱动库头文件（提供GPIO操作函数等）

/* 注释掉不需要的宏定义
#define start_PRES 1
#define stop_PRES  2
#define key_start GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_11)
#define key_stop  GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_12)
*/

// 只保留必要的函数声明
void Hardware_init(void);

/* 注释掉不需要的函数声明
void GPIO_init(void);
void Clock_Init(void);
void SoftDelay(u32 cnt);
int GPIO_KEY_Scan(u8 mode);
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
*/

#endif // 结束头文件保护宏

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */