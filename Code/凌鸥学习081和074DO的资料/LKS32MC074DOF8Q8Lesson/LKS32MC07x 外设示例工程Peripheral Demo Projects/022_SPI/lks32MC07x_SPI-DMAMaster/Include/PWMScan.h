/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： KeyScan.h
 * 文件标识：
 * 内容摘要： KeyScan
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2019年12月27日
 *
 *******************************************************************************/
#ifndef __PWMSCAN_H
#define __PWMSCAN_H
 
#include "basic.h"
#include "FOC_Drive.h"

#define PWM_TIME_PERIOD      9600//输入频率对应Timer计数值。针对不接PWM的时候调用
#define DUTY_ZERO            0  //0占空比
#define DUTY_FULL            1000//100%占空比，数值扩大了10倍

#define PWM_HIGH             (GPIO2_PDI & BIT5) //PWM输入IO电平为高，一般来说恒高占空比为100%，恒低为0%

#define DIR_FLITER           10//单位：ms 方向按键滤波时间，用于按键去抖，时间长短决定灵敏度
#define DIR_CW               (GPIO0_PDI & BIT11)//方向输入IO口电平为高

#define DIR_DELAY            (500)//单位:ms

#define FG_HIGH              (GPIO0_PDO |= 0x8000) //FG输出IO口电平为高
#define FG_LOW               (GPIO0_PDO &= 0x7FFF) //FG输出IO口电平为低

#define RESET_TIME            (5000) //单位：ms 软复位时间

/*********************PWM检测设定******************************/ 
#define PWM_MIN               (200)//最小占空比：20%
#define PWM_MAX               (900)//最大占空比：90%

#define SPEED_MIN             (s32)(1000) //单位：0.01Hz 最小转速
#define SPEED_MAX             (s32)(10000)//单位：0.01Hz 最大转速

#define SPEED_SCALE           (float)(SPEED_MAX - SPEED_MIN)/(PWM_MAX - PWM_MIN)  //PWM 调速斜率

/***********************VSP检测设定****************************/ 
#define VSP_MIN               (4550)//电位器电压最小值   计算公式： 0.5/3.6*32767 ，0.5为最小电压
#define VSP_MAX               (27305)//电位器电压最大值  计算公式： 3.0/3.6*32767 ，3.0为最大电压

#define POWER_MIN             (142)  //功率最小值 按照功率拟合曲线标定
#define POWER_MAX             (12850)//功率最大值 按照功率拟合曲线标定

#define POWER_SCALE           (float)(POWER_MAX - POWER_MIN)/(VSP_MAX - VSP_MIN) //功率设定斜率

typedef struct
{
  s16 nHighLevelTime;    //高电平计数值
  s16 nLowLevelTime;     //低电平计数值
  s16 nPeriod;           //周期计数值
  u16 nDuty;             //占空比
  u16 nFlagPeriod;       //周期加测标志位
  s16 nPreTime;          //上次计数值
  u16 nFlagReset;        //软复位标志位
  u16 nResetCntr;        //软复位计数
  
  s16  nVSPValue;        //电位器电压
  s32  wPowerValue;      //功率设定值
}stru_PWMTime_t;



extern volatile u8 g_bMC_RunFlg;

extern stru_PWMTime_t  PWMTime;
extern void delay(u32 cnt);

extern void PWMScan(void);
extern void PWMScanInit(void);
extern void PWMDutyScan(void);
extern void SpeedScan(void);
extern void MotorDirScan(void);
extern void FGScan(UINT16 Theta);
extern void FGScanInit(void);
extern void PowerScan(void);

extern void PWMOutputs(FuncState t_state);

#endif

