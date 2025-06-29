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

#include "lks32mc08x_lib.h"

typedef struct
{
	u32 Data_Length_TX;		 // I2C发送数据长度
	u32 Data_Temp_Length_TX; // 发送当前字节个数
	u32 Data_Length_RX;		 // I2C接收数据长度
	u32 Data_Temp_Length_RX; // 接收当前字节个数
	u8 *I2C_DATA_TX;		 // I2C发送数据缓冲区
	u8 *I2C_DATA_RX;		 // I2C接收数据缓冲区
	u8 Idle_TX_Flag;		 // I2C发送时检查空闲标志位
	u8 Idle_RX_Flag;		 // I2C接收时检查空闲标志位
	u8 I2C_Tran_Flag;		 // I2C传输完成标志位
	u8 I2C_Mode;			 // I2C模式，0：发送模式，1：接收模式
	u8 Tran_Mode;			 // 传输模式，1:主模式只接收或者只发送，2:主模式发送数据后立刻转为接收，或者接收数据后立刻转为发送
	u8 IIC_ADDR;
	u8 IIC_div_t;
} I2C_Parameter;

extern I2C_Parameter I2C_Par;

#define I2C_TX_OR_RX 1	//主模式只接收
#define I2C_TX_AND_RX 2 //主模式发送数据后立刻转为接收，或者接收数据后立刻转为发送

u8 I2C_TX_Function(u8 addr, u8 *i2c_data, u32 len, u8 mode);
u8 I2C_RX_Function(u8 addr, u8 *i2c_data, u32 len, u8 mode);


#define start_PRES 1 //start
#define stop_PRES 2  //stop

#define key_start GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_11)
#define key_stop GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_12)

void GPIO_init(void);
void Clock_Init(void);
void Hardware_init(void);
void SoftDelay(u32 cnt);
void I2C_init(u32 div0);
void SPI_init(void);
int GPIO_KEY_Scan(u8 mode);
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

