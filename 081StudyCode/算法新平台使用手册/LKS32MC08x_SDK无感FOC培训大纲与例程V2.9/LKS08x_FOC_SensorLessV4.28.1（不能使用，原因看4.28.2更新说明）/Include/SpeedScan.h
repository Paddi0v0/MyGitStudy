/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： SpeedScan.h
 * 文件标识：
 * 内容摘要： 电位器调速
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： HuangMG
 * 完成日期： 2021年5月30日
 *
 *******************************************************************************/
#ifndef __PWMSCAN_H
#define __PWMSCAN_H
#include "lks32mc08x.h"
#include "basic.h"
#include "FOC_Drive.h"

/***********************VSP检测设定****************************/ 
#define VSP_OFF               (1000.0) //电位器关机电压     计算公式：  0.2/3.6*32767 ，0.2为关机电压
#define VSP_MIN               (1500.0) //电位器电压最小值   计算公式：  0.3/3.6*32767 ，0.3为最小电压
#define VSP_MAX               (27380.0)//电位器电压最大值  计算公式：   2.2/3.6*32767 ，2.2为最大电压

#define VSP_SPEED_MIN         (30.0)    //单位：Hz
#define VSP_SPEED_MAX         (220.0)   //单位：Hz

#define VSP_SPEED_SCALE       (float)(VSP_SPEED_MAX - VSP_SPEED_MIN)/(VSP_MAX - VSP_MIN)  //PWM 调速斜率
    
void VspSpeedScan(void);
void KEY_Scan(void);

#endif


