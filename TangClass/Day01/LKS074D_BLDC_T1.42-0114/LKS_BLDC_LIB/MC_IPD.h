/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： MC_IPD.h
 * 文件标识：
 * 内容摘要： 电机初始位置定位函数声明
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_IPD_H
#define __MC_IPD_H

#include "basic.h"
                 
typedef struct
{
    u32 wIPD_PlusWidthSet;                        /* IPD位置检测，注入脉冲宽度设置，单位：clock周期数 */
    u32 wIPD_IdleWaitSet;                         /* IPD位置检测，续流结束等待宽度设置，单位：clock周期数 */
    u16 nPWM_PERIOD;                              /* PWM 占空比 */

    u8  bIPD_State;                               /* IPD状态标志 */
    u8  bIPD_StepFlg;                             /* IPD步骤标志 */

    u16 IPD_Angle;                                /* IPD得到的角度值 */

    s16 AdcSampCurr[7];                           /* ADC 电流采样值 */
    s16 VoltagePLUS_ADC[7];                       /* ADC 电压采样值 */
	
	u8  Max_Sector_Flg;                           
	u8  Seek_result;                              /* IPD定位结果 */	

} stru_IPD_CtrProcDef;


void IPD_RotorPosEst(void);

#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

