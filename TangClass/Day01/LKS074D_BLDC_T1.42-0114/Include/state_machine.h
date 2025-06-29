/*******************************************************************************
 * ��Ȩ���� (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� state_machine.h
 * ����ժҪ�� state machine
 * ����˵���� ��
 * ��ǰ�汾�� V1.0
 * ��    �ߣ� andrew kong
 * ������ڣ� 2019��11��19��
 *
 *******************************************************************************/
#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include "basic.h"
#include "mc_type.h"


typedef struct
{
    s16 nChargeTime;       //���ʱ�䣬��1msΪ��λ
    s16 nAlignTime;        //��λʱ�䣬��1msΪ��λ
    s16 nDirCheckTime;     //˳���ʱ�䣬��1msΪ��λ
    s16 nLoopDelyTime;     //�ٶȻ��ӳ�ʱ�䣬��1msΪ��λ
    s16 nStopDelayTime;    //���ֹͣ�ӳ�ʱ�䣬��1msΪ��λ
    s16 nStopDelayCntr;    //���ֹͣ�˲�ʱ�䣬�������жϵ��ֹͣ��ʱ�䣬��1msΪ��λ
    s16 nOpenRunCntr;      //�����бջ�ʱ�䣬��1msΪ��λ
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

