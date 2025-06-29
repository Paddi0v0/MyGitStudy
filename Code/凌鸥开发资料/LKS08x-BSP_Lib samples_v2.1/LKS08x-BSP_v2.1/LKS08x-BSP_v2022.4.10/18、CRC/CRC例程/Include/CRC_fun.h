/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： CRC_fun.h
 * 文件标识：
 * 内容摘要： 硬件CRC计算
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： yangzj
 * 完成日期： 2021年7月05日
 *
 * 修改记录1：
 * 修改日期： 2021年7月05日
 * 版 本 号： V 1.0
 * 修 改 人： yangzj
 * 修改内容： 创建
 *
 *******************************************************************************/

/*------------------------------prevent recursive inclusion -------------------*/
#include "hardware_config.h"
#ifndef __CRC_FUN_H_
#define __CRC_FUN_H_
u8 crc8(u8 *pData,u32 uLen);
u8 crc8_ITU(u8 *pData,u32 uLen);
u8 crc8_ROHC(u8 *pData,u32 uLen);
u8 crc8_MAXIM(u8 *pData,u32 uLen);

u16 crc16_IBM(u8 *pData,u32 uLen);
u16 crc16_MAXIM(u8 *pData,u32 uLen);
u16 crc16_USB(u8 *pData,u32 uLen);
u16 crc16_MODBUS(u8 *pData,u32 uLen);
u16 crc16_CCITT(u8 *pData,u32 uLen);
u16 crc16_CCITT_FALSE(u8 *pData,u32 uLen);
u16 crc16_X25(u8 *pData,u32 uLen);
u16 crc16_XMODEM(u8 *pData,u32 uLen);
u16 crc16_DNP(u8 *pData,u32 uLen);

u32 crc32(u8 *pData,u32 uLen);
u32 crc32_MPEG_2(u8 *pData,u32 uLen);
#endif
