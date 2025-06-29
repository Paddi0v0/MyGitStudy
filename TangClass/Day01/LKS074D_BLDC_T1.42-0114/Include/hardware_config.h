/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_config.h
 * 文件标识：
 * 内容摘要： 硬件相关文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月20日
 *
 * 修改记录1：
 * 修改日期： 2020年8月20日
 * 版 本 号： V 2.0
 * 修 改 人： Howlet
 * 修改内容： 创建
 *
 *******************************************************************************/

/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "lks32mc07x.h"
#include "lks32mc07x_MCPWM.h"
#include "lks32mc07x_sys.h"
#include "lks32mc07x_adc.h"
#include "lks32mc07x_MCPWM.h"
#include "lks32mc07x_flash.h"
#include "lks32mc07x_gpio.h"
#include "lks32mc07x_DMA.h"
#include "lks32mc07x_cmp.h"
#include "lks32mc07x_uart.h"
#include "lks32mc07x_hall.h"
#include "lks32mc07x_tim.h"
#include "lks32mc07x_NVR.h"
//#include "lks32mc07x_iwdg.h"
#include "basic.h"
#include "PID.h"	

#include "hardware_init.h"
#include "Global_Variable.h"
#include "MC_Parameter.h"

#define LKS32MC070          1
#define LKS32MC071          2
#define LKS32MC072          3
#define LKS32MC073          4
#define LKS32MC074D         5
#define LKS32MC074DO        6
#define LKS32MC076D         7
#define LKS32MC077          8
#define LKS32MC077D         9
#define LKS32MC078          10
#define LKS32MC079          11
/* ----------------------PWM 频率及死区定义----------------------------------- */
#define MCU_MCLK                       (96000000LL)       /* PWM模块运行主频 */ 

#define PWM_MCLK                       ((u32)MCU_MCLK)    /* PWM模块运行主频 */
#define PWM_PRSC                       ((u8)0)            /* PWM模块运行预分频器 */
#define PWM_FREQ                       ((u16)15000)        /* PWM斩波频率 */

/* 电机控制PWM 周期计数器值 */
#define PWM_PERIOD                     ((u16) (PWM_MCLK / (u32)(2 * PWM_FREQ *(PWM_PRSC+1))))

#define MCU_SYS_TIME                   (10.42)

#define DEADTIME_NS                    ((u16)1800)      //1500                        /* 死区时间 */
#define DEADTIME                       (u16)(((unsigned long long)PWM_MCLK * (unsigned long long)DEADTIME_NS)/1000000000uL)

/* -------------------------------- 系统故障码定义 ------------------------------ */
#define SHORT_ERROR                    BIT0  /* 短路故障 1*/
#define LOW_VOL_ERROR                  BIT1  /* 低压故障 2*/
#define HIG_VOL_ERROR                  BIT2  /* 过压故障 4*/
#define BLOCK_ERROR                    BIT3  /* 堵转故障 8*/
#define DC_OFFSET_ERROR                BIT4  /* 直流偏置故障 16*/
#define MOS_OVER_ERROR                 BIT5  /* MOS过温故障 32*/
#define MOS_LOW_ERROR                  BIT6  /* MOS低温故障 64*/
#define BAT_OVER_ERROR                 BIT7  /* 电池过温故障 128*/
#define BAT_LOW_ERROR                  BIT8  /* 电池低温故障 256*/
#define OVER_LOAD_ERROR                BIT9  /* 过流故障 512*/
#define PHASE_DROP_ERROR               BIT10 /* 缺相故障 1024*/

/* ----------------------芯片型号及预驱极性设置----------------------------------- */
#define  CHIP_PART_NUMBER              LKS32MC074D         /* 芯片型号选择，选择不正确将影响芯片模块的初始化 */
#define  P_HIGH__N_HIGH                0
#define  P_HIGH__N_LOW                 1

#if ((CHIP_PART_NUMBER == LKS32MC074D) || (CHIP_PART_NUMBER == LKS32MC074DO) ||(CHIP_PART_NUMBER == LKS32MC076D))
    #define  MCPWM_SWAP_SETTING        1                  /* 芯片内置预驱需调用，芯片无内置预驱将此句屏蔽即可*/
    #define  PRE_DRIVER_POLARITY       P_HIGH__N_HIGH     /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
	  #define  DRIVER_POLARITY           0x0000             // 取MCPWM_IO1、MCPWIO23配置里面CHxN、CHxP的极性的配置
#else
    #define  MCPWM_SWAP_SETTING        0                  /* 芯片内置预驱需调用，芯片无内置预驱将此句屏蔽即可*/
    #define  PRE_DRIVER_POLARITY       P_HIGH__N_LOW      /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */
	  #define  DRIVER_POLARITY           0x0101             // 取MCPWM_IO1、MCPWIO23配置里面CHxN、CHxP的极性的配置		
#endif

/* --------------------------------ADC通道号定义------------------------------ */
#define ADC0_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC0_CHANNEL_OPA1              ADC_CHANNEL_1
#define ADC0_CHANNEL_OPA2              ADC_CHANNEL_2
#define ADC0_CHANNEL_OPA3              ADC_CHANNEL_3

#define ADC1_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC1_CHANNEL_OPA1              ADC_CHANNEL_1
#define ADC1_CHANNEL_OPA2              ADC_CHANNEL_2
#define ADC1_CHANNEL_OPA3              ADC_CHANNEL_3
/* ADC相电流采样时序，硬件相关 ------------------------------------------------ */
/* Porting Application Notice 注意采样序列 ------------------------------------ */
#define BEMF_CH_A                      ADC_CHANNEL_13        /* A相反电动势采样通道 */
#define BEMF_CH_B                      ADC_CHANNEL_12        /* B相反电动势采样通道 */
#define BEMF_CH_C                      ADC_CHANNEL_11        /* C相反电动势采样通道 */

#define ADC_BUS_CUR_CHANNEL            ADC1_CHANNEL_OPA3     /* 母线平均电流采样通道 */
#define ADC_PEAK_CUR_CHANNEL           ADC1_CHANNEL_OPA3     /* 母线峰值电流采样通道 */

#define ADC_BUS_VOL_CHANNEL            ADC_CHANNEL_8        /* 母线电压 */
#define ADC_SPEED_CHANNEL              ADC_CHANNEL_7         /* 速度信号 */

#define ADC_MOS_TEMP_CHANNEL           ADC_CHANNEL_3         /* MOS温度 */
#define ADC_BAT_TEMP_CHANNEL           ADC_CHANNEL_10        /* 电池温度 */

#define ADC_OPA_OUT_CHANNEL            ADC_CHANNEL_11         /* 运放输出采样 */

#define ADC0_STATE_RESET()             {ADC0_CFG |= BIT11;}   /* ADC1 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC0_SOFTWARE_TRIG_ONLY()     {ADC0_TRIG = 0;}      /* ADC设置为仅软件触发 */

#define ADC1_STATE_RESET()             {ADC1_CFG |= BIT11;}   /* ADC1 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC1_SOFTWARE_TRIG_ONLY()      {ADC1_TRIG = 0;}      /* ADC设置为仅软件触发 */
/* ---------------------------CMP比较器设置相关定义 --------------------------- */
#define CMP0_SELN_SET                  CMP0_SELN_HALL0_MID       /* 比较器0负端选择HALL MID */
#define CMP0_SELP_SET                  CMP0_SELP_IP1       /* 比较器0正端选择IP0 */

#define CMP1_SELN_SET                  CMP_SELN_DAC0            /* 比较器1负端选择DAC */
#define CMP1_SELP_SET                  CMP1_SELP_OPA3_OUT       /* 比较器1正端选择运放1输出结果 */

#define CMP2_SELN_SET                  CMP_SELN_IN       /* 比较器0负端选择HALL MID */
#define CMP2_SELP_SET                  CMP2_SELP_IP0       /* 比较器0正端选择IP0 */

#define DAC0_OUT_SET                   DISABLE             /* DAC0输出使能 */
#define DAC1_OUT_SET                   DISABLE             /* DAC1输出使能 */

#define CMP_IP_A                       CMP0_SELP_IP3        /* A相反电势电压比较器通道 */
#define CMP_IP_B                       CMP0_SELP_IP2        /* B相反电势电压比较器通道 */
#define CMP_IP_C                       CMP0_SELP_IP1        /* C相反电势电压比较器通道 */

#define CMP0_IE_ENABLE()              {CMP_IE |= BIT0;}   /* 比较器0关闭使能 */
#define CMP0_IE_DISABLE()             {CMP_IE &= ~BIT0;}  /* 比较器0关闭使能 */
#define CMP0_IE_STATE()               (CMP_IE & BIT0)     /* 判断当前比较器0状态 */

#define CMP0_OUT_LEVEL()              (CMP_DATA & BIT0)   /* 比较器0输出电平原始信号状态 */

#define CMP0_POL_STATE()              (CMP_CFG & BIT0)    /* 当前比较器0输出极性选择 */ 

/* ------------------------------编译器选项------------------------------------ */
#define RUN_IN_RAM_FUNC  __attribute__ ((used, section ("ram3functions")))

/* ------------------------------硬件IO控制接口-------------------------------- */
#define LED_DELAY_TIME                 60000       /* 松扳机后延时关机时间 */ 

#define LOCK_POWER_ON()                {GPIO2_PDO |= BIT6;}         
#define LOCK_POWER_OFF()               {GPIO2_PDO &= ~BIT6;}

#define KEY_DIRECT_CTRL                GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_10)   //正反转切换按键,读取P2.10输入电平


#define LED_OFF_TIME                   500         /*LED报警闪烁时间设置*/
#define LED_ON_TIME                    500
#define LED_PERIOD_DELAY               1000        /*LED报警闪烁周期延时时间设置*/

#define LED_ON()                       {GPIO0_PDO &= ~BIT15;}
#define LED_OFF()                      {GPIO0_PDO |= BIT15;}

#define KEYIN_FILTER_TIME              30 /* 按键输入滤波时间 */

#define SWITCH_INPUT_MASK              (GPIO2_PDI & BIT13)
#define DIRECT_INPUT_MASK              (GPIO2_PDI & BIT10)

#define SWITCH_INPUT                   (BIT0)  /* 开关 */
#define DIRECT_INPUT                   (BIT1)  /* 方向 */

typedef struct
{
    s32 yk_1;
    u16 coef;
} stru_RC_Def;


typedef enum
{
    IDLE       = 0,   /* 空闲状态 */
    INIT       = 1,   /* 初始化状态 */
    CHARGE     = 2,   /* 充电状态 */
    ALIGN      = 3,   /* 预定位 */
    OPEN_RUN   = 4,   /* 开环运行状态 */
    ONFLY_START  = 5,   /* 顺逆风检测 */
    POS_SEEK   = 6,   /* 初始位置检测 */
    RUN        = 7,   /* 正常运行状态 */
    STOP       = 8,   /* 停止状态 */
    BRAKE      = 9,   /* 刹车状态 */
    WAIT       = 10,  /* 等待状态 */
    FAULT      = 11,  /* 故障状态 */
    SEEK_POS   = 12,  /* 位置检测状态 */
} enum_SystStatus;


typedef struct
{
	u8 oldCommunicateStep;/* 上次换相电角度位置 */
	u8 communicate_cnt;	  
	u32 Provid_time;	    /* 速度计算周期时间  */	
	u32 Elect_Speed;      /* 电转速 */
	u32 Machine_Speed;    /* 机械转速 */	
} stru_Speedgetting_Ctr;

extern stru_Speedgetting_Ctr Speedgetting; /* 速度获取结构体 */


typedef struct
{
	u8 Last_key_status;     /* 上次按键状态 */
	u8 DirChange_Flag;	    /* 正反转切换标志 */
	u8 MotorRun_Dir;	      /* 电机期望运行方向 */	
	u32 DirChange_Cnt;      /* 正反转切换延时时间 */

} stru_DirChange_Ctr;	     

extern stru_DirChange_Ctr DirChange_Ctr; /* 正反转切换结构体 */

typedef struct
{
	u32 RecoverCnt;         /* 堵转恢复时间计数器 */
    u32 RecoverTime;	      /* 堵转恢复次数 */

} stru_Fault_Stall_Rev;	     

extern stru_Fault_Stall_Rev Fault_Stall_Rev; /* 堵转恢复结构体 */





typedef struct
{
    volatile u16 nSys_TimerPWM;                  /* PWM周期计数Cnt */ 
    u8 bMotorDirtionCtrl;                        /* 期望控制的电机运行方向 */
    u8 bMC_RunFlg;                               /* 电机启动指令 */
    enum_SystStatus eSysState;                   /* 当前电机运行状态机 */
    u16 nSetTimeLeftCnt;                         /* 状态机等待时间计数器 */

    stru_RC_Def struBusCurr_RC;                  /* 母线电流RC滤波结构体  */
  
    u16 nSpeed_ADC;                              /* 速度开关ADC值 */
    s16 nBUS_Vol_ADC;                            /* 母线电压ADC值 */
  
    s16 nPower;                                  /* 电压请求值(占空比目标值) */
  
    s16 nRequestPower;                           /* 实际电压请求值(实际占空比) */
  
    s16 nBLDC_PWM_value;                         /* PWM输出请求值 */
  
    s16 nBusCurrLimit_Value;                     /* 电流限制功能输出值 */
  
    u8 nWork_mode;                               /* 当前工作模式，ADC or 比较器 */
	  
    u16 nNTC_Vol_ADC;                            /* NTC温度ADC值 */
		
	u32 sys_error_flg;                           /* 系统错误状态标志 */
		
	u8 get_offset_flg;                           /* offset错误标志 */
		
	u16 MotorBlockCnt;                           /* 堵转时间计数 */

  	u8 Power_on_flg;                            /* 允许开机标志，1允许开机，0关机 */
		
    u16 BAT_NTC_adc;                            /* 电池温度采样ADC */
		
	u16 NVR_OPAx_Vol;                            /* 共模电压值 */		
		
} stru_BLDC_CtrProcDef;


extern stru_BLDC_CtrProcDef mBLDC_CtrProc;           /* BLDC过程控制结构体 */



#endif  /* __HARDWARE_CONFIG_H_ */

 
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
 
 
