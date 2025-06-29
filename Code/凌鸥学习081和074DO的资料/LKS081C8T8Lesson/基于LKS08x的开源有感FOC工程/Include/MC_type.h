

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_TYPE_H
#define __MC_TYPE_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x_lib.h"

/* Exported types ------------------------------------------------------------*/
/*! Macro converting a signed fractional [-1,1) number into a fixed point 16-bit
 * number in the format Q1.15. */
#define FRAC16(x)           ((s16) ((x) < (S16_MAX) ? ((x) >= S16_MIN ? (x)*0x8000 : 0x8000) : 0x7fff))

/*! Macro converting a signed fractional [-1,1) number into a fixed point 32-bit
 * number in the format Q1.31. */
#define FRAC32(x)           ((s32) ((x) < (S32_MAX) ? ((x) >= S32_MIN ? (x)*0x80000000 : 0x80000000) : 0x7fffffff))

#define ABS(X)              ( ( (X) >= 0 ) ? (X) : -(X) )

#define sat(x,ll,ul) ( (x) > (ul) ) ? (ul) : ( ( (x) < (ll) ) ? (ll) : (x) )

#define HALL_SPEED_FIFO_SIZE 	 	((u8)6)		/* Hall信号处理Buffer大小，6次求平均 */

typedef struct
{
    s16 qI_Value1;
    s16 qI_Value2;
} stru_CurrVoctor;

typedef struct
{
    s16 qV_Value1;
    s16 qV_Value2;
} stru_VoltVoctor;

typedef struct
{
    s16 u;
    s16 v;
    s16 w;
} stru_VoltPhaseUVW; 

typedef struct
{
    s16 hCos;
    s16 hSin;
} stru_TrigComponents;

typedef struct 
{
    s32 Kp;
    s32 Ki;
    s32 Kd;
	
} sPID;

typedef union
{
    u16 R;
    struct
    {
        u16 SoftCurretError : 1; 				/* 软件过流错误标志位 */
        u16 HardCurretError : 1; 				/* 硬件过流错误标志位 */
        u16 VoltOverError   : 1; 				/* 过压错误标志位 */
        u16 OffsetError     : 1; 				/* 偏置错误标志位 */
        u16                 : 12;				/* 保留，可根据其他需求来添加错误标志位，注意不要超过16位，否则需要修改u16 R --> u32 R */
    } B;
} stru_FaultStatus_t;

typedef struct
{
    s16 hKp_Gain;
    u16 hKp_Divisor;
    s16 hKi_Gain;
    u16 hKi_Divisor;
    s16 hLower_Limit_Output;     					//Lower Limit for Output limitation
    s16 hUpper_Limit_Output;     					//Lower Limit for Output limitation
    s32 wLower_Limit_Integral;   					//Lower Limit for Integral term limitation
    s32 wUpper_Limit_Integral;   					//Lower Limit for Integral term limitation
    s32 wIntegral;
} stru_PIparams;

//typedef struct
//{
//    u16 nCofA;      								/* 温度系数A */
//    u16 nOffsetB;   								/* 温度系数偏置 */
//	volatile s16 Temperture_adc;					/* 芯片温度ADC值 */
//	volatile s16 Temperture;						/* 芯片当前温度 */
//} Stru_TempertureCof_Def;

typedef struct
{
    s32 yk_1;
    u16 coef;
} stru_RC_Def;


typedef struct
{
    volatile u8 nTimeBaseFlg;        				/* Timer 中断标记，取值 0或1 */
    volatile u8  bPWM_UpdateFlg;      				/* PWM周期更新标志，一次间隔为一个PWM周期 */
    u8  bTimeCnt1ms;         						/* 1mS计数器 */
	u8  bTimeCnt2ms;         						/* 2mS计数器 */
    u16 nTimeCnt10ms;        						/* 10mS计数器 */
    u16 nTimeCnt500ms;       						/* 500mS计数器 */
	
} stru_TaskSchedulerDef;

/* ****************************** 转吧 ****************************************** */

typedef struct
{
	u8  bgear_shift; 								/* 档位切换 */
	u16 inching_shift_time;							/* 点动切换去抖 */
	volatile s16 hand_speed_adc; 					/* 转把电压 */
	s16 hand_speed_adc_fir; 						/* 转把电压滤波后 */
	s16 hand_out_powre; 							/* 转把输出的油门值 */
	volatile s16 actual_out_powre; 					/* 实际输出的油门值 */
	volatile s16 given_hdcur_ref; 					/* 给定弱磁深度 */
	s16 Proportional_drop_Slope;					/* 速降给定弱磁深度 */
	
} stru_speed_control_handle;

/* ****************************** 加减速处理 ****************************************** */

typedef struct
{
	u8  speed_add_slope; 							/* 加速斜率 */
	u8  speed_dec_slope; 							/* 减速斜率 */
	u8  second_cut_in; 								/* 二次切入 */
	volatile u16 nclosemosfetcnt; 					/* 松转把关驱动计数 */
	volatile u16 nsoft_voltage_cnt; 				/* 软欠压关电计数 */
	volatile u16 ndqnegcnt; 						/* 二次转把负电流计数 */
	
} stru_motor_adjust_speed;

/* ****************************** 刹车 ****************************************** */

typedef struct
{
	u8  break_flg; 									/* 刹车标志 */
	
} stru_break_eabs;

/* ****************************** 一键修复 ****************************************** */

typedef struct
{
	u8  break_hand_err_flg; 						/* 刹车转把故障标志位 */
	u8  power_up_hand_err_flg; 						/* 上电防飞车标志位 */
	u8  onekeyrunflg; 								/* 一键修复标志 */
	u16 in_yjxf_time; 								/* 进入一键修复延时时间 */
	u16 hand_err_clear_cnt; 						/* 转把故障恢复滤波 */
	
} stru_motor_onekeyrun;

/* ****************************** 存储，堵转功能结构体 *************************** */

typedef struct
{
	u8  setup_parameters_flg;						/* 允许存储标志 */ 
	u8  motorblockflg;								/* 电机堵转标志 */ 
	u16 smotorblockcnt;								/* 进入电机堵转时间计数 */ 
	u16 nInputPort_State;							/* 端口输入状态 */ 
	s8  bInputCnt[12];								/* 端口输入去抖 */ 
	
} stru_motor_comprehensive;

/* ****************************** 上电处理  ****************************************** */

typedef struct
{
	u16 power_up_time; 								/* 上电时间计数 */ 
	
} stru_power_up;

typedef enum
{
    IDLE       = 0,   								/* 空闲状态 */
    INIT       = 1,   								/* 初始化状态 */
    RUN        = 2,   								/* 正常运行状态 */
    STOP       = 3,   								/* 停止状态 */
    WAIT       = 4,  								/* 等待状态 */
} enum_SystStatus;

typedef struct
{
	u8  bFstHallSigFlg;                      		/* 第一次Hall变化标志，用来Hall信号去抖 */
    u32 wOldSensorPeriod;                    		/* 上次Hall信号滤波后周期值 */
    u32 wMotorSpeedAvgCnt;                   		/* Hall信号滤波后周期值, 以HAll模块时钟周期计数 */
    u32 wSensorPeriod[HALL_SPEED_FIFO_SIZE]; 		/* Hall信号周期变化数组，用来求信号平均值 */
    u8  bSpeedFIFO_Index;                    		/* Hall信号周期变化数组指针 */
    volatile u32 wHallPWMTimerCnt;           		/* Hall变化周期以PWM周期冗余计数，计数器值 */
    volatile u16 nElectrical_Angle;             	/* 当前转子位置角度值，0~65535对应0~360度 */
    volatile u16 nOldElectrical_Angle;          	/* 上一次转子位置角度值，0~65535对应0~360度 */  
    volatile s16 nEndElectricalAngle;           	/* 最大角度增量限制值，在Hall处理错误时，用来快速找回正确角度 */
    volatile u16 nTabElectrical_Angle;          	/* 直接查表等到的当前转子电角度值 */
    u16 nRotorFreqDpp;                       		/* 当前角速度值, 一个PWM周期下的角度增量值。0~65536对应0~360度 */
    u16 nReduceToqueDpp;                     		/* 极低速模式下当前角速度值, 一个PWM周期下的角度增量值。0~65536对应0~360度 */
    u16 nReduceToqueAngle;                   		/* 低速模式下, 角度增量 */
    volatile u32 wHallCapCnt;                   	/* Hall模块捕捉累计值 */
    s16 nMaxReduceIncAngle;                  		/* 在Reduce Toque模式下，角度最大增量 0~65536对应0~360度 */
  
    volatile u8 bHallState;                     	/* 当前滤波后的Hall状态 */

    u8 bMotorDirtionCtrl;                    		/* 期望控制的电机运行方向 */

    u8 bHallRunFlg;                          		/* Hall运行状态标志，故障、方向、超时等状态 HALL_COM_TIMEOUT，
														HALL_COM_FLG，HALL_COM_ERR，HALL_DIR_FLG*/
    s16 ErrCnt;                 	 				/* HALL错误计数 */

    u8 bReduceToqueFlg;                      		/* Reduce Toque模式工作标志，电机速度过低，工作在此模式 */ 
    u8 bFastAddElecAngleFlg;                 		/* 在Hall处理错误时，用来快速累加到正确的角度 */
    u8 bCloseLoopAngleFlg;                   		/* Hall角度拟合，PLL闭环工作标志  */
  
    u16 nPhaseShift;                         		/* 当前Hall角度计算角度偏移值 */
    u16 nPhaseShiftOffset;                   		/* 当前Hall角度偏移值设置 */
    
    u32 wCloseLoopPeriodThd;                 		/* HALL PLL闭环工作门限值 */
    u32 wOpenLoopPeriodThd;                  		/* HALL PLL开环工作门限值 */
    
    u16 nMaxIncAngle;                        		/* 最大角度增量 */

    u16 nHallOffsetArry[6];                  		/* Hall偏移角修正，锁相环输出，修正Hall安装引起的机械安装偏移角 */
    
    u8  bHallPossableTab[8];                 		/* Hall换相表，存储下一相Hall值 */
    u8  bHallPossableTab2[8];               		/* Hall换相表，存储上一相Hall值 */
    u8  bHallCommTab[8];                     		/* Hall换相表 */
    
    u8 bHallState_org;       						/* Hall原始信号 */
	
} stru_HallProcessDef;

typedef struct
{
	u8  low_error_flg;  							/* 低压标志 */
	u16 slowvoltagecnt;  							/* 低压判断时间计数 */
	u16 shighvoltagecnt;  							/* 过压判断时间计数 */
    u16 hLowVoltageThd;  							/* 低压阀值 */
    u16 hLowVoltageRsmThd;  						/* 退出低压阀值 */
    u16 hOverVoltageThd;  							/* 过压阀值 */
    u16 hOverVoltageRsmThd;  						/* 退出过压阀值 */
	u16 nsoft_undervoltage_inter;  					/* 软欠压限制积分 */
} VoltageProtect_Struct;

typedef struct
{
    u16 ADC0_A_B_Cur_First; 						/* ADC0相采样时序 */
    u16 ADC0_A_C_Cur_First; 						/* ADC0相采样时序 */
    u16 ADC0_B_C_Cur_First; 						/* ADC0相采样时序 */
} Stru_ADC_sample;

typedef struct
{
	volatile Stru_ADC_sample Stru_ADC_sampParama;   /* 相线电流采样配置 */
	volatile stru_CurrVoctor StatCurr_a_b_test;     /* 本次电机定子A相B相电流 */
    volatile stru_CurrVoctor struStatCurr_a_b;      /* 电机定子A相B相电流 */
    volatile stru_CurrVoctor struLastStatCurr_a_b;  /* 上一次电机定子A相B相电流  */
    volatile stru_CurrVoctor struStatCurr_q_d;      /* 电机定子Q相D相电流  */
    volatile stru_CurrVoctor struStatCurr_alfa_beta;/* 电机定子alfa beta轴电流  */

    volatile stru_VoltVoctor struStatVolt_q_d;      /* 电机定子Q相D相电压  */
    volatile stru_VoltVoctor struStatVolt_alfa_beta;/* 电机定子alfa beta轴电压力 */

    volatile stru_TrigComponents struTrigSinCos;    /* 定子角度sin Cos值 */

    s16 nBusVoltage;                             	/* 直流母线电压 */
	s16 nBusVoltagefir;                          	/* 直流母线电压滤波值 */
	s16 nBusCurrentadc;                     		/* 直流母线电流采样值 */
	s16 nBusCurrentadcfir;                          /* 直流母线电流滤波值 */
                                                                          
    volatile stru_VoltPhaseUVW struVoltUVW_PWM;     /* UVW PWM输出电压 */

    volatile u8 bSector;                          	/* 当前扇区 */

	u8 bget_offset_flg;                          	/* 电流偏置状态 */
    s16 nPhaseAOffset;                           	/* A相ADC采样 Offset值 */
    s16 nPhaseBOffset;                           	/* B相ADC采样 Offset值 */
	s16 nPhaseBOffset1;                          	/* B相ADC采样 Offset值 */
    s16 nPhaseCOffset;                           	/* C相ADC采样 Offset值 */
	s16 nphaseAoffsetShift;                      	/* 电机类型1 A相offset 值 */
	s16 nphaseCoffsetShift;                      	/* 电机类型1 C相offset 值 */
	s16 nBusCurrentOffset;                       	/* 母线ADC采样 Offset值 */

    volatile s16 nDCur_Reference;                   /* D轴电流给定 */

    volatile s16 nRequestPower;                     /* Q轴电压给定 */

    volatile s8 bCntFirCurA;                        /* A相电流滤波计数器 */
    volatile s8 bCntFirCurB;                        /* B相电流滤波计数器 */
    stru_RC_Def struCurrA_RC;                    	/* A相相电流RC滤波结构体  */
    stru_RC_Def struCurrB_RC;                    	/* B相相电流RC滤波结构体  */

    u8 bFirstOpenMosFlgCnt;                      	/* 打开MOS的前几个周期，不采样，避开干扰 */

    stru_PIparams struPI_Torque;                 	/* Q轴电流环PI参数 */
    stru_PIparams struPI_Flux;                   	/* D轴电流环PI参数 */

} stru_FOC_CurrLoopDef;

typedef struct
{
	volatile u16 nSys_TimerPWM;                  	/* PWM周期计数Cnt */

    u8 bMC_RunFlg;                               	/* 电机启动指令 */
	
    enum_SystStatus eSysState;                   	/* 当前电机运行状态机 */
	
    u16 nSetTimeLeftCnt;                         	/* 状态机等待时间计数器 */
	
	s16 originalmax_bus_current;              	 	/* 原始最大母线电流限制值 */
    s16 max_bus_current;                      	 	/* 最大母线电流限制值 */
	
	s16 nQVoltageFir; 					 		 	/* 扭矩电压滤波后 */
	stru_RC_Def struCur_lowFir_Q;                	/* 扭矩电压滤波结构体 */

    stru_RC_Def struBusCurr_RC;                  	/* 母线电流RC滤波结构体  */ 
	
	stru_FOC_CurrLoopDef struFOC_CurrLoop;       	/* 电流内环结构体 */
	
} stru_FOC_CtrProcDef;

typedef struct
{
    u8 hall_Sequence[8]; 							/* hall相序 */
    u8 hallType; 									/* Hall 类型 60度或120度 */
    u8 motorType; 									/* 电机 类型 60度超前或-60度超前 */
    u8 null0[2]; 									/* 保证字长对齐 */
    u32 busCurrentLim; 								/* 母线电流限制 | addr 12 byte*/
    u8 version[4]; 									/* Program Version  | addr 16 byte */
    u32 BEMF_coefficient; 							/* 反电势系数   | addr 20 byte  */
    u32 hall_offsetAngle; 							/* Hall 超前角  | addr 24 byte */
    u32 null; 										/* addr 28 byte */
    u32 null1; 										/* addr 32 Byte */
    u32 null2; 										/* addr 36 Byte */
    u32 phaseAoffset; 								/* A 相offset 值 */
    u32 phaseBoffset; 								/* B 相offset 值 */
    u32 phaseCoffset; 								/* C 相offset 值 */
    u32 phaseBusOffset; 							/* bus 相offset 值 */
    u32 phaseB1offset; 								/* B1 相offset 值 */
    u32 phaseAoffset1; 								/* 电机类型1 A相offset 值 */
    u32 phaseCoffset1; 								/* 电机类型1 C相offset 值 */
} FlashParamaStruct_o;

typedef struct
{   
    u8 hall_Sequence[8]; 							/* hall相序 */
    u8 hallType; 									/* Hall 类型 60度或120度 */
    u8 motorType; 									/* 电机 类型 60度超前或-60度超前 */
    u8 null0[2]; 									/* 保证字长对齐 null0[0] 被占用软件限速标志*/
    u32 busCurrentLim; 								/* 母线电流限制 | addr 12 byte*/
    u8 version[4]; 									/* Program Version  | addr 16 byte */
    u32 BEMF_coefficient; 							/* 反电势系数   | addr 20 byte  */
    u32 hall_offsetAngle; 							/* Hall 超前角  | addr 24 byte */
    u32 hallBroken_flg; 							/* addr 28 byte zkw flg*/
    u32 null1; 										/* addr 32 Byte */
    u32 null2; 										/* addr 36 Byte */
    u32 phaseAoffset; 								/* A 相offset 值 */
    u32 phaseBoffset; 								/* B 相offset 值 */
    u32 phaseCoffset; 								/* C 相offset 值 */
    u32 phaseBusOffset; 							/* bus 相offset 值 */
    u32 phaseB1offset; 								/* B1 相offset 值 */
    u32 phaseAoffset1; 								/* 电机类型1 A相offset 值 */
    u32 phaseCoffset1; 								/* 电机类型1 C相offset 值 */

    u8 buffer[512 - sizeof(FlashParamaStruct_o)];
}FlashParamaStruct;

/* Exported constants --------------------------------------------------------*/

#define U8_MAX     								((u8)255)
#define S8_MAX     								((s8)127)
#define S8_MIN     								((s8)-128)
#define U16_MAX    								((u16)65535u)
#define S16_MAX    								((s16)32767)
#define S16_MIN    								((s16)-32768)
#define U32_MAX    								((u32)4294967295uL)
#define S32_MAX    								((s32)2147483647)
#define S32_MIN    								((s32)-2147483648)


#endif /* __MC_TYPE_H */
/******************* (C) COPYRIGHT 2008 LINKO Semiconductor *****END OF FILE****/
