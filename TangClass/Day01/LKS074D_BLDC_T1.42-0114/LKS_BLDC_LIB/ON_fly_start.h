#ifndef __ON_FLY_START__
#define __ON_FLY_START__

#include "basic.h"

void BEMF_GET_ON_fly(void);
void ON_FLY_Handle(void);
void get_max_BEMF(void);

typedef struct 
{ 

	  s16 A_flaot_ADC;           /* 电机滑行时A相但电动势电压 */
	  s16 B_flaot_ADC;           /* 电机滑行时B相但电动势电压 */
	  s16 C_flaot_ADC;           /* 电机滑行时C相但电动势电压 */
	  s16 Bus_Vol_ADC;           /* 母线电压 */
	  s16 max_flaot_ADC;         /* 反电动势最大相的ADC */
	  u8  MC_Fly_flg;            /* 顺风起标志 */
      u8  MAX_bemf_flg;          /* 最大反电动势对应相 */	
	  u8  BEMF_step;             /* 滑行时转子所在扇区 */
	  u8  old_BEMF_step;         /* 滑行时上一拍转子所在扇区 */
	  u8  fly_start_step;        /* 顺风起时转子所在扇区 */	
	  u32 sector_time[6];        /* 顺风起动前五拍每一拍的时间 */
	  u8  sector_time_cnt;       /* 记录扇区时间次数技数 */
	  u32 fly_step_time;         /* 顺风起启动时转子换向60度时间 */
	  u32 fly_Speed;             /* 顺风起启动时转子换向60度时间 */	
	  u16 ON_FLY_Start_THD;         /* 顺风起启动时转子换向60度时间 */	  
	
	  u32 duty;                  /* 顺风起占空比 */
	  u16 duty_fly;
	  u16 power;                 /* 顺风起初始占空比对应占空比 */
		
	  u16 ON_fly_cnt;

      u16 ON_Fly_Max_DUTY;
      u16 ON_Fly_Min_DUTY;	 
      u32 ON_Fly_delay_time;
	  
volatile u8  fly_cnt;               /* 顺风起动前转子判断次数 */		  
volatile u32 communicate_delay_time;	  
	  	  	
}ON_flyStruct;

extern ON_flyStruct ON_fly;

#endif
