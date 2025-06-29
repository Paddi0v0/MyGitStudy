/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_IWDG.h\n
 * 文件标识： 无 \n
 * 内容摘要： 看门狗驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
#ifndef __LKS32MC08x_IWDG_H
#define __LKS32MC08x_IWDG_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x_lib.h"

/** 
 *@brief IWDG寄存器结构体句柄
 */
typedef struct
{
    u32 WDG_EN;             /**< 独立看门狗使能 */
    u32 RTH;                /**< 看门狗超时复位时间*/
}IWDG_InitTypeDef;

#define WDT_RTH_2S   3 /**< 看门狗超时复位时间1秒*/
#define WDT_RTH_4S   2 /**< 看门狗超时复位时间4秒*/
#define WDT_RTH_8S   1 /**< 看门狗超时复位时间8秒*/
#define WDT_RTH_64S  0 /**< 看门狗超时复位时间64秒*/

void IWDG_Init(IWDG_InitTypeDef *);                 // 看门狗初始化
void IWDG_StrutInit(IWDG_InitTypeDef *);            // 看门狗配置结构体初始化
void IWDG_DISABLE(void);                            // 关闭看门狗
void IWDG_ENABLE(void);                             // 使能看门狗
void IWDG_Feed(uint32_t timeOut);                   // 看门狗喂狗
#endif /*__lks32mc03x_IWDG_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
