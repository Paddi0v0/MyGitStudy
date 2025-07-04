 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_exti.h\n
 * 文件标识： 无 \n
 * 内容摘要： EXTI外部中断驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ        <td>创建
 * </table>
 */

#ifndef __LKS32MC08x_EXTI_H
#define __LKS32MC08x_EXTI_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x.h"
#include "lks32mc08x_gpio.h"
#include "basic.h"

/** 
 *@brief EXTI寄存器结构体句柄
 */
typedef struct  
{
   __IO uint32_t CR0;
   __IO uint32_t CR1;
   __IO uint32_t IF;   
   __IO uint32_t POL;
   __IO uint32_t EN;
}EXTI_TypeDef;

 /**
 * EXTI结构体基地址定义
 */
#ifndef EXTI
#define EXTI             ((EXTI_TypeDef *) EXTI_BASE)
#endif

 /**
 * EXTI触发信号定义
 */
typedef enum
{
   EXTI_Trigger_None    = 0x00, /**< 不触发*/
   EXTI_Trigger_Negedge = 0x01, /**< 下降沿触发*/
   EXTI_Trigger_Posedge = 0x02, /**< 上升沿触发*/
   EXTI_Trigger_Edge    = 0x03  /**< 上升沿、下降沿均触发*/
} EXTIMode_TypeDef;

void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger);
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);

#endif /*__lks32mc05x_EXTI_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
