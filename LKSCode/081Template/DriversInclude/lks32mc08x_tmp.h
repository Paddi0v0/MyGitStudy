/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_tmp.h\n
 * 文件标识： 无 \n
 * 内容摘要： 芯片内置温度传感器驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月5日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */
#ifndef _LKS32MC08x_TMP_H_
#define _LKS32MC08x_TMP_H_

#include "lks32mc08x_lib.h"

/** 
 *@brief 芯片内置温度传感器初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
   u16 nCofA;      /**< 温度系数A，来源Read_Trim(0x00000398)输出值*/
   u16 nOffsetB;   /**< 温度系数偏置，来源Read_Trim(0x0000039C)输出值*/
} Stru_TempertureCof_Def;


void TempSensor_Init(void);
s16 GetCurrentTemperature(s16 ADC_value);

#endif /*_CONNIE_TMP_H_ */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
