/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： state_machine.h
 * 内容摘要： state machine
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2019年11月19日
 *
 *******************************************************************************/
#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include "basic.h"
#include "mc_type.h"


typedef struct
{
    s16 nChargeTime;       //充电时间，以1ms为单位
    s16 nAlignTime;        //定位时间，以1ms为单位
    s16 nDirCheckTime;     //顺逆风时间，以1ms为单位
    s16 nLoopDelyTime;     //速度环延迟时间，以1ms为单位
    s16 nStopDelayTime;    //电机停止延迟时间，以1ms为单位
    s16 nStopDelayCntr;    //电机停止滤波时间，即连续判断电机停止的时间，以1ms为单位
    s16 nOpenRunCntr;      //开环切闭环时间，以1ms为单位
}stru_Time_t;

extern stru_Time_t                 struTime;

extern void StateInit(void);
extern void StateCalib(void);
extern void StateCharge(void);
extern void StateDirCheck(void);
extern void StatePosSeek(void);
extern void StateAlign(void);
extern void StateOpen(void);
extern void StateRun(void);
extern void StateFault(void);
extern void StateIdle(void);
extern void StateStop(void);

extern void FluxObserveInit(void);
#endif

