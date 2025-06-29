

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_TYPE_H
#define __MC_TYPE_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x_lib.h"

#define SQRT_3      1.732051
#define SQRT_2      1.4142

#define ABS(X)              ( ( (X) >= 0 ) ? (X) : -(X) )
#define sat(x,ll,ul) ( (x) > (ul) ) ? (ul) : ( ( (x) < (ll) ) ? (ll) : (x) )

#define LOG2(x)     ((x) == 65535 ? 16 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 15 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 14 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 13 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 12 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 11 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 10 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 9 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 8 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 * 2 ? 7 : ((x) == 2 * 2 * 2 * 2 * 2 * 2 ? 6 : ((x) == 2 * 2 * 2 * 2 * 2 ? 5 : ((x) == 2 * 2 * 2 * 2 ? 4 : ((x) == 2 * 2 * 2 ? 3 : ((x) == 2 * 2 ? 2 : ((x) == 2 ? 1 : ((x) == 1 ? 0 : -1)))))))))))))))))
#define EFFECTIVE_NUM(x)    (((u16)x&BIT15)?16:\
                            ((u16)x&BIT14)?15:\
                            ((u16)x&BIT13)?14:\
                            ((u16)x&BIT12)?13:\
                            ((u16)x&BIT11)?12:\
                            ((u16)x&BIT10)?11:\
                            ((u16)x&BIT9)?10:\
                            ((u16)x&BIT8)?9:\
                            ((u16)x&BIT7)?8:\
                            ((u16)x&BIT6)?7:\
                            ((u16)x&BIT5)?6:\
                            ((u16)x&BIT4)?5:\
                            ((u16)x&BIT3)?4:\
                            ((u16)x&BIT2)?3:\
                            ((u16)x&BIT1)?2:\
                            ((u16)x&BIT0)?1:0)
#define MAX(a,b) ((a>b)?a:b)
#define COEF_DIV1           ((u32)(15 - (u32)EFFECTIVE_NUM((u16)MAX(MAX(C1,C3),C5))))

#define U8_MAX     								((u8)255)
#define S8_MAX     								((s8)127)
#define S8_MIN     								((s8)-128)
#define U16_MAX    								((u16)65535u)
#define S16_MAX    								((s16)32767)
#define S16_MIN    								((s16)-32768)
#define U32_MAX    								((u32)4294967295uL)
#define S32_MAX    								((s32)2147483647)
#define S32_MIN    								((s32)-2147483648)

typedef struct
{
    s16 Offset0;
    s16 Offset1;
} stru_ADCOffset;

typedef struct
{
    s16 nPhaseU;
    s16 nPhaseV;
    s16 nPhaseW;
} stru_CurrPhaseUVW;

typedef struct
{
    s16 nAlph;
    s16 nBeta;
} stru_CurrAlphBeta;

typedef struct
{
    s16 nAxisQ;
    s16 nAxisD;
} stru_CurrVoctorDQ;

typedef struct
{
    s16 nAxisQ;
    s16 nAxisD;
} stru_VoltVoctorDQ;

typedef struct
{
    s16 nAlph;
    s16 nBeta;
} stru_VoltAlphBeta;

typedef struct
{
    s16 nPhaseU;
    s16 nPhaseV;
    s16 nPhaseW;
} stru_VoltPhaseUVW;

typedef struct
{
    s16 hCos;
    s16 hSin;
} stru_TrigComponents;

typedef union
{
    u16 R;
    struct
    {
        u8 SoftCurretError : 1;     // 软件过流错误标志位
        u8 VoltOverError   : 1;     // 过压错误标志位
        u8 VoltLowError    : 1;     // 过压错误标志位
        u16 nul            : 13;    // 地址对齐
    } B;
} stru_FaultStatus_t;

typedef struct
{
    s16 hKp_Gain;
    u16 hKp_Divisor;
    s16 hKi_Gain;
    u16 hKi_Divisor;
    s16 hLower_Limit_Output;
    s16 hUpper_Limit_Output;
    s32 wLower_Limit_Integral;
    s32 wUpper_Limit_Integral;
    s32 wIntegral;
} stru_PIparams;

typedef enum
{
    IDLE       = 0,     /* 空闲状态 */
    INIT       = 1,     /* 初始化状态 */
    RUN        = 2,     /* 正常运行状态 */
    STOP       = 3,     /* 停止状态 */
} enum_SystStatus;

typedef struct
{
   s16 set;
   s16 ref;
   s16 coeff;
} Stru_Curr_RC;

typedef struct
{
    stru_VoltAlphBeta   VoltAlphBeta;       // 静止坐标系电压
    
    stru_ADCOffset      ADCOffset;          // ADC采样电流偏置
    stru_PIparams       struPI_Q_Torque;    // Q轴电流环PI参数
    stru_PIparams       struPI_D_Flux;      // D轴电流环PI参数
    Stru_Curr_RC        stru_QCur;
    Stru_Curr_RC        stru_DCur;
} stru_FOC_CurrLoopDef;

typedef struct
{
    s32 Gsmopos;        // 滑膜常数1
    s32 Fsmopos;        // 滑膜常数2
    s32 E0;             // 滑膜的电流误差的限幅值 0.5
    s32 Kslf;           // 滤波器系数
    s32 Kslide;         // 滤波器系数
    s32 wZeroSpeedTime; // 零速度定位时间
} stru_SMOCoef;
typedef struct
{
    s16 Valpha;         // 二相静止坐标系alpha-轴电压	
    s16 Ealpha;         // 二相静止坐标系alpha-轴反电动势
    s16 Zalpha;         // alfa轴滑膜观测器的z平面
    s16 EstIalpha;      // 滑膜估算alpha-轴电流
    
    s16 Vbeta;          // 二相静止坐标系beta-轴电压	 
    s16 Ebeta;          // 二相静止坐标系beta-轴反电动势
    s16 Zbeta;          // beta轴滑膜观测器的z平面	 
    s16 EstIbeta;       // 滑膜估算beta-轴电流 
    
    s16 angle;             // 电角度
    s16 speed;             // 电角度
    s32 wOpenAngle;
    s32 bAngleClosedLoop;
    s32 wZeroSpeedCnt; // 零速度定位计数器
    s32 wOpenSpeed;
    s16 angleopentoclose;
    s16 SpeedCalcOldAngle;
} stru_SMOVariable;
typedef struct
{
    stru_SMOCoef      coef;
    stru_SMOVariable  variable;
} stru_SMODef;
typedef struct
{
                u8                      bMC_RunFlg;         // 电机启动指令
                enum_SystStatus         eSysState;          // 当前电机运行状态机
                s16                     nBusVoltage;        // 直流母线电压
                stru_PIparams           struSpeed_loop;     // 速度环PI参数
                stru_FOC_CurrLoopDef    struFOC_CurrLoop;   // 电流内环结构体
                stru_SMODef             stru_SMO;           // 滑膜观测器
    volatile    stru_FaultStatus_t      stru_Faults;        // 系统错误调度结构体
	volatile    u16                     nSys_TimerPWM;      // PWM周期计数Cnt
} stru_FOC_CtrProcDef;


/* Exported constants --------------------------------------------------------*/


#endif /* __MC_TYPE_H */
/******************* (C) COPYRIGHT 2008 LINKO Semiconductor *****END OF FILE****/
