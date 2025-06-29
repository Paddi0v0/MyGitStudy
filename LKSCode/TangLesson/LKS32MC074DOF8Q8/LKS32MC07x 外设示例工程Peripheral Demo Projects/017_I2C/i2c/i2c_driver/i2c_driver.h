/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： i2c_driver.h
 * 文件标识：
 * 内容摘要： i2c驱动库
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： YangZJ
 * 完成日期： 220826
 *
 *******************************************************************************/
#ifndef __I2C_DRIVER_H
#define __I2C_DRIVER_H

#include "i2c_driver.h"
#include "lks32mc07x_i2c.h"
#include "lks32mc07x_dma.h"
#include "lks32mc07x_sys.h"

void i2c_DriverInit(I2C_TypeDef *I2Cx, DMA_RegTypeDef *DMA_CHx, u32 BaudRate, u8 ADDR); // I2C驱动库初始化
void i2c_DriverMasterRx(u8 addr, u8 *data, u8 len);                                     // 主模式接收
void i2c_DriverMasterTx(u8 addr, u8 *data, u8 len);                                     // 主模式发送
void i2c_DriverMasterSetRxCallback(void (*fun)(u8));                                    // 主模式接收完成回调设置
void i2c_DriverMasterSetTxCallback(void (*fun)(u8));                                    // 主模式发送完成回调设置
void i2c_DriverMasterWait(void);                                                        // 主模式等待发送完成
void i2c_DriverSlaveSetRxCallback(void (*fun)(void));                                   // 从模式接收完成回调设置
void i2c_DriverSlaveSetTxCallback(void (*fun)(void));                                   // 从模式发送完成回调设置
void i2c_DriverSlaveSetTxData(u8 *data, u8 len);                                        // 从模式设置待发送的数据
void i2c_DriverSlaveGetRxData(u8 *data, u8 len);                                        // 从模式读取刚接收的数据
#endif
