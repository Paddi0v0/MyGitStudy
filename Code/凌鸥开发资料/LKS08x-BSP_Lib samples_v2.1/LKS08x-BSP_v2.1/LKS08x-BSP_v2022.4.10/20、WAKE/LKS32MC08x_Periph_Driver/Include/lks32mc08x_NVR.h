/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc08x_NVR.c
 * 文件标识：
 * 内容摘要： NVR读取程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： DengT
 * 完成日期：
 *
 * 修改记录1：
 * 修改日期：
 * 版 本 号：V 1.0
 * 修 改 人：
 * 修改内容：创建
 *
 *
 *******************************************************************************/
#include "hardware_config.h"

typedef struct
{
   u16 nCofA;      /* 温度系数A */
   u16 nOffsetB;   /* 温度系数偏置 */
} Stru_TempertureCof_Def;

uint32_t Read_NVR(uint32_t adr);
uint32_t Read_Trim(uint32_t adr);

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
