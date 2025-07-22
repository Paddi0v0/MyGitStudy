 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_opa.h\n
 * 文件标识： 无 \n
 * 内容摘要： OPA驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年06月02日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
#ifndef __LKS32MC08x_OPA_H
#define __LKS32MC08x_OPA_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x_lib.h"

typedef enum
{
   OPA0 = 0, /**< OPA0模块*/
   OPA1 = 1, /**< OPA1模块*/
   OPA2 = 2, /**< OPA2模块*/
   OPA3 = 3  /**< OPA3模块*/
}enumOPA;

/** 
 *@brief OPA初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
       /** 
     * @brief 运放闭环增益 \n
     * @see PGA_GAIN_20   \n  
     * @see PGA_GAIN_9P5  \n
     * @see PGA_GAIN_6    \n
     * @see PGA_GAIN_4P25           
     */  
   uint32_t OPA_Gain;      
   uint32_t OPA_CLEna;      /**<运放闭环使能:Enable,Disable*/
}OPA_InitTypeDef;

/* ------------------------------PGA操作相关定义 ------------------------------ */
#define PGA_GAIN_20                    0x00                   /**< 反馈电阻200:10.2 */
#define PGA_GAIN_9P5                   0x01                   /**< 反馈电阻190:20.2 */
#define PGA_GAIN_6                     0x02                   /**< 反馈电阻180:30.4 */
#define PGA_GAIN_4P25                  0x03                   /**< 反馈电阻170:40.4 */                                                                                 

void OPA_Init(enumOPA opa, OPA_InitTypeDef* OPA_InitStruct);
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct);
void OPA_OUT(enumOPA opa, FuncState state);

#endif /*__lks32mc08x_OPA_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
