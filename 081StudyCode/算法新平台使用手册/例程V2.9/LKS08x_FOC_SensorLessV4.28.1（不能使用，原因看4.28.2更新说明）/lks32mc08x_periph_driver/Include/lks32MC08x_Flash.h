/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC08x_flash.h\n
 * 文件标识： 无 \n
 * 内容摘要： FLASH外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2018年07月25日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 *@par 修改日志:增加程序跑飞时，对Flash的保护
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年12月15日 <td>1.1     <td>DengT      <td>修改
 * </table>
 */

#ifndef __LKS32MC08x_FLASH__
#define __LKS32MC08x_FLASH__

#include "lks32mc08x_lib.h"

#define Flash_MAIN 0x000 /**< Flash的mian区域定义*/
#define Flash_NVR  0x800 /**< Flash的nvr区域定义*/

extern volatile u32 erase_flag; 
extern volatile u32 progm_flag;
int ProgramPage(u32 adr, u32 sz, u8 *buf, u16 nvr);
extern void EraseSector(u32 adr, u16 nvr);
void Read_More_Flash(u32 adr, u32 sz, u32 *buf, u16 nvr);

#endif

