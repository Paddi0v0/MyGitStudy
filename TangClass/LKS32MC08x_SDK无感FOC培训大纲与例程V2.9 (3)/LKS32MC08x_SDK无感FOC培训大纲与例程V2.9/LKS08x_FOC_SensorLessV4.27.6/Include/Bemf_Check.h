/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * 文件名称： Bemf_Check.h
 * 文件标识：
 * 内容摘要： 硬件相关文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月20日
 *
 * 修改记录1：
 * 修改日期： 2022年8月18日
 * 版 本 号： V 2.0
 * 修 改 人： Lizyt
 * 修改内容： 添加两种速度结果
 *******************************************************************************/

#ifndef __BEMF_CHECK_H_
#define __BEMF_CHECK_H_

#include "basic.h"
#include "MC_Type.h"
#include "MC_parameter.h"
#include "hardware_config.h"

typedef struct
{
    s16 nPhaseU;
    s16 nPhaseV;
    s16 nPhaseW;
} stru_BemfPhaseUVW_Def;

typedef struct
{
    s16 nAlpha;
    s16 nBeta;
} stru_BemfPhaseAlpahBeta_Def;

typedef struct
{
    s16 nBemf_Checkttime;                          //反电动势检测的时间
    stru_BemfPhaseUVW_Def         nBemf_ADC;       //adc采样值
    stru_BemfPhaseUVW_Def         nBemf_ADCoffset;       //adc采样值
    stru_BemfPhaseUVW_Def         nBemf_Value;     //采样后反电动势Core数据
    stru_BemfPhaseAlpahBeta_Def   nBemf_AlphaBeta; //alpha beta轴反电动势电压
    s32 wBemfUVWSum;                                //三相反电动势之和
    s16 nBemfUVWAver;                               //三相反电动势之和的平均
    s16 nBemfUVWAmp;                                //Alpha beta的均方根，反电动势幅值
    u16 nBemfUVWAmpValue;                           //Alpha beta的均方根，反电动势幅值物理值单位 0.01V
    s16 nVbus;                                      //预留母线电压用于合成FOC的三相电压
    u16 unBemf_Angle;                               //但当前反电动势检测的转子角度
    u16 unBemf_AngleSec;                            //反电动势检测的转子角度另外计算
    s16 unBemf_AngleLast;                           //上一时刻反电动势检测的转子角度
    s16 nBemf_DetaAngle;                            //反电动势检测的转子角度差，用于计算速度
    s32 wBemf_DetaAngleSum;                         //反电动势检测的转子角度差，用于计算速度
    s16 nBemf_DetaAngleAver;                        //反电动势检测的转子角度差，用于计算速度平均
    s16 nBemf_DetaAngleCnt;                         //反电动势检测的转子角度差，用于计算速度平均
    s16 nBemf_Freq;                                 //反电动势检测的频率
    s16 nBemf_FreqAve;                              //反电动势检测的滤波频率，符号判断 APP层数据
    s16 nBemf_KeFreq;                               //Ke计算反电动势检测的频率
    s16 nBemf_KeFreqAve;                            //Ke计算反电动势检测的频率     APP层数据
    stru_RC_Def  struRCBemf_Speed;                  //反电动势检测的速度低通滤波
    s16 nVbemf_Base;                                /**/
    s16 nVbemf_BaseValue;                           /*电压采样范围 0.01V单位*/
		s16 nBemf_AdvanceAngle;                         /*反电动势超前角*/   
} stru_BEMF_Def; /* 反电动势电路结构体 */

//定义反电动势变量
extern stru_BEMF_Def    stru_BEMF_Check;
extern void  Bemf_CheckInit(stru_BEMF_Def *pstru_BEMF , s16 angle_lead);
extern void Bemf_CheckProcess(stru_BEMF_Def *pstru_BEMF, s16 phaseA, s16 phaseB, s16 phaseC);
/****************反电动势检测切换到无感的角度赋值*****************/
extern void BemfSwitch(stru_BEMF_Def *pstru_BEMF);  

#endif
