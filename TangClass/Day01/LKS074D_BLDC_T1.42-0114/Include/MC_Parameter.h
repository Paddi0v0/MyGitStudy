/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： parameter.h
 * 文件标识：
 * 内容摘要： parameter config
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Andrew kong, Howlet Li
 * 完成日期： 2020年8月18日
 *
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "basic.h"
#include "hardware_config.h"
/* ---------------------------------功能相关定义------------------------------ */
#define ENABLE_FUNCTION                1           /* 开启功能 */
#define DISABLE_FUNCTION               0           /* 关闭功能 */

/* -------------------------- LKSSCOPE上位机启动/调速设置 ------------------------ */
#define LKSSCOPE_START_FUNCTION      DISABLE_FUNCTION       /* Lksscope控制电机启停功能 */
#define MANUAL_SPEED                 120                    /* 给定调速信号，输入范围：START_THRESHOLD_ADC-1400  */
                                                            /* 小于 START_THRESHOLD_ADC 电机关闭，
                                                            大于START_THRESHOLD_ADC小于SPEED_UP_ADC最低速运行，
                                                            高于SPEED_UP_ADC开始加速，大于1600满速运行 */
/* -------------------------- 电机自动启停测试 ------------------------ */
#define START_UP_TEST_FUNCTION      DISABLE_FUNCTION      /* 电机自动启停功能 */
#define START_TEST_TIME             2000                  /* 电机启停测试次数 */
#define START_DELAY_TIME            2000                  /* 单位：ms,开机延时时间 */
#define START_WORK_TIME             2500                  /* 单位：ms,开机后电机工作时间 */
 
/* --------------------------------- 顺风启动功能 ------------------------------ */
#define ON_FLY_START_FUNCTION         DISABLE_FUNCTION       /* 顺风起功能 */

#define ON_FLY_RUN_TIME               (u16)5  //顺风时间设置，单位：ms

#define ON_FLY_MAX_DUTY               (u16)(0.8 * PWM_PERIOD)
#define ON_FLY_MIN_DUTY               (u16)(0.1 * PWM_PERIOD)

#define MOTOR_MIN_SPEED               (u32)200//4915  //最低电压下最小运行转速
#define PER_ONE_DUTY_ADD_SPEED        (u32)200//500   //每升高1%占空比电机提升的转速

#define ON_FLY_MAX_POWER              (u16)(ON_FLY_MAX_DUTY * 32767/PWM_PERIOD)
#define ON_FLY_MIN_POWER              (u16)(ON_FLY_MIN_DUTY * 32767/PWM_PERIOD)

#define ON_FLY_VOL                    (u16)1    //(顺风起判断门槛，单位：V)
#define ON_FLY_ADC_THD                (u16)(ON_FLY_VOL * BEMF_SHUNT_RATIO*32767/ADC_SUPPLY_VOLTAGE) 
/* --------------------------------- EABS功能相关设置 ------------------------------ */
#define EABS_FUNCTION                 DISABLE_FUNCTION        /* Eabs刹车功能 */

#define EABS_HARD                     ENABLE_FUNCTION         /* 使能后刹车短三相下管，否则为软刹车，三相下管以一定占空比输出短接 */
                                                              /* PS:在用稳压电源调试软刹车时，电源可能会产生负电流保护，用电池包会好一些 */
																															/* PS:建议使用硬刹 */
#define EABS_SLIP_TIME               (u16)100                  /* 刹车前滑行时间设置 */
#define EABS_RUN_TIME                (u16)100                 /* 刹车时间设置 */
#define EABS_TOTAL_TIME              (u16)(EABS_SLIP_TIME + EABS_RUN_TIME)
#define SOFT_EABS_STEP               (u16)50                  /* 软刹车加速步长，占空比一直加大直到开满 */
#define SOFT_EABS_MIN_DUTY           (u16)1000                /* 软刹车基础占空比 */

/* --------------------------------- 速度环功能设置 -------------------------------------- */
#define SPEED_LOOP_FUNCTION            DISABLE_FUNCTION          /* 速度环功能 (支持零速闭环)*/
#define EXPECTED_MACHINE_SPEED         (u32)250                  /* 单位：RPM，机械转速目标值 */  
#define SPEED_LOOP_MIN_SPEED           (u32)200                  /* 单位：RPM，速度环模式下最小机械速度 */
#define EXPECTED_ELECT_SPEED           (u32)(MOTOR_POLE_NUMBER*EXPECTED_MACHINE_SPEED)   /* 单位：HZ，电转速目标值，是实际电转速的60倍 */

///* --------------------------------- 功率环功能设置 -------------------------------------- */
//#define POWER_LOOP_FUNCTION            DISABLE_FUNCTION          /* 功率环功能 */
//#define EXPECTED_POWER                 (u32)50                  /* 单位：W，目标功率值 */  
//#define EXPECTED_POWER_MIN             (u32)10                  /* 单位：W，功率环模式下最小功率 */


/*------------------------------------扳机调速设置-----------------------------------------*/
#define START_THRESHOLD_ADC     100        //扳机启动信号ADC值 
#define START_POWER             1200       //启动后的最小占空比：START_POWER/32767
#define TRIGGER_DUTY_CONTROL              0     //扳机占空比调速模式
#define TRIGGER_SPEED_CONTROL             1     //扳机速度环调速模式
#define TRIGGER_CONTROL_MODE             TRIGGER_DUTY_CONTROL        //扳机调速模式选择

#define SPEED_UP_ADC            400        //扳机加速信号ADC值  输入范围： 大于START_THRESHOLD_ADC，小于1600
#define SPEED_UP_RATIO          19         //调速倍率，可根据扳机ADC采集范围灵活调整
#define SPEED_UP_UNIT      (u32)((100000*(MOTOR_MACHINE_SPEED_MAX - SPEED_LOOP_MIN_SPEED))/(U12_MAX - SPEED_UP_ADC))  //扳机加速倍率  1.602 

/*******************************************************************************
 调速模式： 扳机占空比调速模式
 功能描述： 1，模式下扳机调速仅控制输出的占空比，最小值为START_POWER，最大值为32767。
            2，扳机ADC采样值（Speed_value）大于 START_THRESHOLD_ADC 电机启动，大于SPEED_UP_ADC 电机加速。
		    3，该模式下的电机运行速度取决电机在当前占空比下的运行情况。
 *******************************************************************************/

/*******************************************************************************
 调速模式： 扳机速度环调速模式(支持零速闭环)
 功能描述： 1，模式下扳机调速直接控制电机的机械转速，最小值为START_POWER下对应的机械转速，最大值为MOTOR_MACHINE_SPEED_MAX。
            2，扳机ADC采样值（Speed_value）大于 START_THRESHOLD_ADC 电机启动，大于SPEED_UP_ADC 电机加速。
		    3，一般为了电机运行稳定，电机最好运行在最低转速下后进入速度环调速模式
 *******************************************************************************/



 //卷帘门电机 正反转
/* --------------------------------- 电机参数 -------------------------------------------- */
#define MOTOR_POLE_NUMBER               5                         /* 电机极对数 */
#define MOTOR_MACHINE_SPEED_MAX        (u32)4000                  /* 单位：RPM，电机最大机械转速 */
#define MOTOR_ELECT_SPEED              (u32)(MOTOR_POLE_NUMBER*MOTOR_MACHINE_SPEED/60)    /* 单位：HZ，电机最大转速电频率 */

/* -----------------------------------外设硬件设置----------------------------------- */
#define ADC_SUPPLY_VOLTAGE             (3.6)              //单位: V  ADC基准电压，3.6或者2.4,大部分应用选择3.6
#define AMPLIFICATION_GAIN             (21.33)            //运放放大倍数
#define RSHUNT                         (0.003)            //单位: Ω  采样电阻阻值
#define VOLTAGE_SHUNT_RATIO            (1.0/(22.0+1.0))   //母线电压分压比
#define BEMF_SHUNT_RATIO               (1.0/(22.0+1.0))   //反电势电压分压比  (1.0/(22.0+1.0)) 


/* ----------------------------------恒流输出设置----------------------------- */
#define MAX_BUS_CURRENT_SETTINT        (u16)5 /* 单位：A，恒流输出最大电流值 */
#define CURRENT_ADC_PER_A              (RSHUNT * AMPLIFICATION_GAIN * 32752/3.6) /* 每安电流ADC值 */ 
#define CURRENT_LIM_VALUE              (u16)(MAX_BUS_CURRENT_SETTINT * CURRENT_ADC_PER_A) /* 最大电流ADC值 */


/* ----------------------------------硬件过流保护设置---------------------------- */
#define SHORT_BUS_CURRENT              (u16)80 /* 母线电流阈值 */
#define SHORT_CURRENT_VOL              (SHORT_BUS_CURRENT * RSHUNT * AMPLIFICATION_GAIN *10000)   /* 单位: 0.1mv,短路电压 */
#define SHORT_CURRENT_DAC              (u16)((SHORT_BUS_CURRENT * RSHUNT * 4096)/4.85 )     /* 短路电压对应DAC值 */

//#define SHORT_PROTECT_DAC              (u16)(OPA_OUT_BASE_DAC + SHORT_CURRENT_DAC) /* 短路保护对应的DAC值 = 运放基础输出 + 设定的短路保护锁对应的DAC */
/* ----------------------------------分级限流保护设置----------------------------- */
#define BUS_CURRENT_FIRST              (u16)5    /* 一级限流 */
#define BUS_CURRENT_SECOND             (u16)10   /* 二级限流 */
#define BUS_CURRENT_THRED              (u16)15   /* 三级限流 */

#define CURRENT_ADC_PER_A              (RSHUNT * AMPLIFICATION_GAIN * 32752/3.6) /* 每安电流ADC值 */ 

#define OVER_CURRENT_FIRST_THD         (u16)(BUS_CURRENT_FIRST * CURRENT_ADC_PER_A)  /* 第一级限流电流ADC值 */
#define OVER_CURRENT_SECOND_THD        (u16)(BUS_CURRENT_SECOND * CURRENT_ADC_PER_A) /* 第二级限流电流ADC值 */
#define OVER_CURRENT_THRED_THD         (u16)(BUS_CURRENT_THRED * CURRENT_ADC_PER_A) /* 第二级限流电流ADC值 */

#define TIME_LIMIT_FIRST               2000  /* 一级限流时间 */
#define TIME_LIMIT_SECOND              500   /* 二级限流时间 */
#define TIME_LIMIT_THRED               100   /* 二级限流时间 */


/* ----------------------------------电压保护设置------------------------------- */
#define LOW_VOLATAGE_THD                  11   /* 欠压电压 */
#define RSM_LO_VOLATAGE_THD               10.5 /* 欠压恢复电压 */
#define OV_VOLTAGE_THD                    55   /* 过压门槛 */
#define RSM_OV_VOLTAGE_THD                30   /* 过压恢复门槛 */

#define LOW_VOLATAGE_THD_1                11.0   /* 第一段欠压电压:运行过程中欠压 */
#define LOW_VOLATAGE_THD_2                11.0   /* 第二段欠压电压:开机之前欠压 */

#define FIRST_LOW_TIME                    300    /* 第一段欠压时间 单位：ms */

#define LOW_VOLATAGE_FIRST                (u16)(LOW_VOLATAGE_THD_1 * VOLTAGE_SHUNT_RATIO/3.6*32768)  
#define LOW_VOLATAGE_SECOND               (u16)(LOW_VOLATAGE_THD_2 * VOLTAGE_SHUNT_RATIO/3.6*32768)  
 
#define LOW_VOLATAGE_ADC                  (u16)(LOW_VOLATAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768)   
#define RSM_LO_VOLATAGE_ADC               (u16)(RSM_LO_VOLATAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768)   
#define OV_VOLTAGE_ADC                    (u16)(OV_VOLTAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768)   
#define RSM_OV_VOLTAGE_ADC                (u16)(RSM_OV_VOLTAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32768) 

/* ----------------------IPD 转子初始位置检测 脉冲注入时间设置---------------- */
#define SEEK_POSITION_STATUS           (TRUE)            //初始位置检测状态 TRUE为使能, FALSE为不使能
#define U_START_ANGLE_COMP             (0)               //单位:度 初始位置检测补偿角度

#define IPD_PLUS_TIME_SETTING          (50)      //80         /* 脉冲注入时间宽度设置 单位us */
#define IPD_WAIT_TIME_SETTING          (400)     //400       /* 脉冲空闲等待时间宽度设置 单位us */

#define IPD_PLUS_TIME_WIDTH            (u32)(IPD_PLUS_TIME_SETTING*(MCU_MCLK/1000000))   /* 脉冲注入时间宽度设置 单位clk */
#define IPD_PLUS_WAIT_TIME             (u32)(IPD_WAIT_TIME_SETTING*(MCU_MCLK/1000000))   /* 脉冲空闲等待时间宽度设置 单位clk */

/* -----------------------------------启动参数设置----------------------------------------- */
#define STARTUP_HAlL_COMM_TIME         20000     //20000       /* 启动时，最小换相时间 单位：HALL模块时钟周期数 */
#define STARTUP_HAlL_COMM_TIMEEX       1000000          /* 比较器工作模式下最大换相时间 单位：HALL模块时钟周期数 */
#define OVERFOLLW_HAlL_COMM_TIME       500000           /* 超时换相时间设置 单位：HALL模块时钟周期数 */

/* ----------------------------------工作模式切换----------------------------------------- */
#define WORK_MODE_THRESHLD             185000           /* ADC模式切换比较器模式速度阈值 */ 
#define QUIT_CMP_THRESHLD              200000           /* 比较器模式切换ADC模式速度阈值 */

/* ----------------------------------启动电流设置----------------------------------------- */
#define HEAVY_LOAD_START                 0               /* 重载启动参数 */
#define FIRST_START_MIN_DUTY             (float)0.24      /* 前三拍启动最小占空比 */
#define ADC_MODE_MIN_DUTY                (float)0.24      /* ADC模式下运行最小占空比 */

/* ----------------------------------PWM加速/减速步长-------------------------------------- */
#define BASIC_PWM_VALUE   200                        /* PWM基础输出值*/
#define POWER_UP_STEP     (u16)150                   /* PWM加速步长 */
#define POWER_DEC_STEP    (u16)30                    /* PWM减速步长 */

/* -----------------------------超低速运行功能设置----------------------------------- */
#define ULTRA_LOW_SPEED_FUNCTION       ENABLE_FUNCTION  /* 超低速运行功能：低速下插入180度反向脉冲*/
#define HFI_PWM_WIDTH                  50               /* 脉冲注入宽度 */
#define HFI_PWM_MIN                    ((s16)(-PWM_PERIOD + 2))
#define HFI_PWM_PLUS                   ((s16)(-PWM_PERIOD + HFI_PWM_WIDTH))
////速度环二选一，占空比函数优化整理，参数提取，ADC优化采样点，功率环

/* --------------------------------重叠换相时间设置---------------------------- */
#define RE_COMM_TIME                   1                 /* 重叠换相时间 单位：us */
#define RE_COMM_CNT                    (RE_COMM_TIME*MCU_MCLK/1000000) /* 标幺化的重叠换相时间 单位：Clk */

/* ------------------------- BLDC SensorLess提前换相时间 ---------------------- */
#define EALY_COMM_TIME_RISE            (s16)(-200)       /* 反电势上升沿时提前换相时间 单位：HALL模块时钟周期数 */  //负值提前换相，正值延后换相
#define EALY_COMM_TIME_FALL            (s16)(-200)       /* 反电势下降沿时提前换相时间 单位：HALL模块时钟周期数 */  //范围：(-32767,32767)

/* -----------------------------------电机转向控制----------------------------- */
#define DIR_CHANGE_WAIT_TIME           (u32)(1000)          /* 电机正反转切换延时时间 单位：ms*/
#define CW                             (0)                /* 电机转向：顺时针 */ 
#define CCW                            (1)                /* 电机转向：逆时针*/

/* ------------------------------ADC校准相关参数设置---------------------------- */
#define CALIB_SAMPLES                  (512)              //ADC偏置校准次数，不可修改
#define OFFSET_THD                     (3500)             //ADC偏置误差阈值，不用修改

/* ----------------------------预驱自举电容预充电参数--------------------------- */
#define CHARGE_TIME                    (100)              //每相预充电时间，根据实际硬件参数修改


/****************************MOS温度保护*************************************/
#define MOS_TEMP_UP_VOL              5     //MOS温度检测上拉电压，单位：V  
#define MOS_TEMP_UP_RES              10    //MOS温度检测上拉电阻，单位：KΩ 

#define MOS_TEMP_OVER_TIME           500   //MOS过温时间

#define MOS_TEMP_OVER_RES            1.11  //MOS过温时NTC阻值，80℃对应1.67K  6512
#define RSM_MOS_TEMP_OVER_RES        1.2   //MOS过温恢复NTC阻值，75℃对应1.98K  7520
   
#define MOS_TEMP_OVER_THD            (u32)((MOS_TEMP_OVER_RES * MOS_TEMP_UP_VOL * 32767)/((MOS_TEMP_OVER_RES + MOS_TEMP_UP_RES) * 3.6))
#define RSM_MOS_TEMP_OVER_THD        (u32)((RSM_MOS_TEMP_OVER_RES * MOS_TEMP_UP_VOL * 32767)/((RSM_MOS_TEMP_OVER_RES + MOS_TEMP_UP_RES) * 3.6))

/****************************BAT温度保护*************************************/
#define BAT_TEMP_UP_VOL              5     //电池温度检测上拉电压，单位：V  
#define BAT_TEMP_UP_RES              10    //MOS温度检测上拉电阻，单位：KΩ 

#define BAT_TEMP_OVER_TIME           500  

#define BAT_TEMP_OVER_RES            1.11  //电池过温时NTC阻值，80℃对应1.67K  6512
#define RSM_BAT_TEMP_OVER_RES        1.2   //电池过温恢复NTC阻值，75℃对应1.98K  7520
   
#define BAT_TEMP_OVER_THD            (u32)((BAT_TEMP_OVER_RES * BAT_TEMP_UP_VOL * 32767)/((BAT_TEMP_OVER_RES + BAT_TEMP_UP_RES) * 3.6))
#define RSM_BAT_TEMP_OVER_THD        (u32)((RSM_BAT_TEMP_OVER_RES * BAT_TEMP_UP_VOL * 32767)/((RSM_BAT_TEMP_OVER_RES + BAT_TEMP_UP_RES) * 3.6))

/****************************堵转恢复参数*************************************/
#define STALL_NUMBER_STATUS            (FALSE)            /* 堵转恢复状态设置, TRUE = 无限恢复， 
                                                           FALSE = STALL_NUMBER 次恢复次数*/
#define STALL_NUMBER                   (200)             /* 堵转恢复次数*/
#define STALL_FAULT_RECOVER_TIME       (400)             /* 单位：ms  堵转恢复时间 */

#endif  /* __PARAMETER_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* -----------------------------------END OF FILE------------------------------- */

