/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Global_Variable.h
 * 文件标识：
 * 内容摘要： 全局变量声明文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：2020年8月5日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet
 * 修改内容：创建
 *
 *******************************************************************************/

#ifndef __GLOBAL_VARIABLE__
#define __GLOBAL_VARIABLE__

#include "lks32mc07x.h"
#include "basic.h"
#include "MC_IPD.h"
#include "ON_fly_start.h"
#include "bldc_control.h"
#include "mc_type.h" 

extern stru_BLDC_sensorlessCtr BLDC_SensorlessCtr;   /* 换相控制结构体 */
extern stru_IPD_CtrProcDef mIPD_CtrProc;             /* IPD 转子位置估计结构体 */

extern void StopMotorImmdly(void);
extern void BLDC_CommunicationOnly(void);
extern void getBemfValue(void);
extern void bldc_comm_process(u8 flg);
extern void PWM_Output_Control(u8 output_flg);

#endif

/* ********************** (C) COPYRIGHT LINKO SEMICONDUCTOR ******************** */
/* ------------------------------END OF FILE------------------------------------ */
