/*******************************************************************************
 * 版权所有 (C)2015, LINKO Semiconductor
 *
 * 文件名称： mc_hall.c
 * 文件标识：
 * 内容摘要： Hall信号处理
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： 李鹏
 * 完成日期： 2016年2月16日
 *
 * 修改记录1：
 *    修改日期：2016年2月26日
 *    版 本 号：V 1.0
 *    修 改 人：李鹏
 *    修改内容：创建
 *
 * 修改记录2：
 *    修改日期：
 *    版 本 号：
 *    修 改 人：
 *    修改内容：
 *
 *******************************************************************************/


#ifndef __HALL_H
#define __HALL_H

#include "LKS32MC08x.h"
 
#define S16_360_PHASE_SHIFT 					(u16)(65535)
#define S16_330_PHASE_SHIFT 					(u16)(60075)
#define S16_318_PHASE_SHIFT 					(u16)(58000)
#define S16_315_PHASE_SHIFT 					(u16)(57344)
#define S16_300_PHASE_SHIFT 					(u16)(54613)
#define S16_270_PHASE_SHIFT 					(u16)(49152)
#define S16_240_PHASE_SHIFT 					(u16)(43691)
#define S16_210_PHASE_SHIFT 					(u16)(38220)
#define S16_180_PHASE_SHIFT 					(u16)(32768)
#define S16_150_PHASE_SHIFT 					(u16)(27300)
#define S16_120_PHASE_SHIFT 					(u16)(21845)
#define S16_90_PHASE_SHIFT  					(u16)(16384)
#define S16_75_PHASE_SHIFT  					(u16)(13653)
#define S16_70_PHASE_SHIFT  					(u16)(12743)
#define S16_63_PHASE_SHIFT  					(u16)(11468)
#define S16_60_PHASE_SHIFT  					(u16)(10923)
#define S16_45_PHASE_SHIFT  					(u16)(8192)
#define S16_30_PHASE_SHIFT  					(u16)(5461)
#define S16_20_PHASE_SHIFT  					(u16)(3641)
#define S16_15_PHASE_SHIFT  					(u16)(2731)
#define S16_10_PHASE_SHIFT  					(u16)(1820)
#define S16_5_PHASE_SHIFT   					(u16)(910)
#define S16_1_PHASE_SHIFT   					(u16)(182)								/* 1度角归一化处理 1/360*65536, 角度0~360度变化， 对应归一化数据0~65535 */

#define HALL_COM_TIMEOUT       		   			0x01           						 	/* 超时换相错误 */
#define HALL_COM_FLG           		   			0x02           						 	/* 换相标志，Hall发生变化时置1 */
#define HALL_COM_ERR           		  	 		0x04           						 	/* Hall变化和预期值不一致 */
#define HALL_DIR_FLG           		   			0x80           						 	/* 电机运行方向标志，0:正转 1:反转 */

#define REDUCE_TOQUE_PUSE      		   			0x01           						 	/* 电机速度较低时，正向降低换相引起的转矩波动标志 */
#define REDUCE_TOQUE_MINUS     		   			0x02           						 	/* 电机速度较低时，反向降低换相引起的转矩波动标志 */ 

#endif /* __HALL_H */
/******************* *****END OF FILE****/
