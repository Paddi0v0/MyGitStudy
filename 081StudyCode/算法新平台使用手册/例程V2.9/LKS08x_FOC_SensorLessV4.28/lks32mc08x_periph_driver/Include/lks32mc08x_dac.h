/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_dac.h\n
 * 文件标识： 无 \n
 * 内容摘要： DAC外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月18日 <td>1.0     <td>Zhu Jie    <td>创建
 * </table>
 */
#ifndef __LKS32MC08x_DAC_H
#define __LKS32MC08x_DAC_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x_lib.h"
typedef struct
{
    /**
     * @brief DAC输出档位：0，3V；1，1.2V；2，4.85V
     * @see DAC_RANGE_3V0
     * @see DAC_RANGE_1V2
     * @see DAC_RANGE_4V85
     */
    uint8_t DAC_GAIN;               
	uint8_t DACOUT_EN;                /**< DAC输出使能：DISABLE，不使能；ENABLE，使能。 */
}DAC_InitTypeDef;

/* ------------------------------DAC操作相关定义 ------------------------------ */
#define DAC_RANGE_3V0                  0                   /**< DAC 3.0V量程 */
#define DAC_RANGE_1V2                  1                   /**< DAC 1.2V量程 */
#define DAC_RANGE_4V85                 2                   /**< DAC 4.85V量程 */

void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);/* DAC结构体初始化 */
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct);      /* DAC初始化 */
void DAC_OutputValue(uint32_t DACValue);             /* DAC输出数值设置--数字量 */
void DAC_OutputVoltage(uint16_t DACVoltage);         /* DAC输出模拟量数值设置--模拟量 */

#endif

