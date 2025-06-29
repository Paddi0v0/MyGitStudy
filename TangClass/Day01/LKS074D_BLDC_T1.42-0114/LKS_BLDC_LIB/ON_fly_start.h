#ifndef __ON_FLY_START__
#define __ON_FLY_START__

#include "basic.h"

void BEMF_GET_ON_fly(void);
void ON_FLY_Handle(void);
void get_max_BEMF(void);

typedef struct 
{ 

	  s16 A_flaot_ADC;           /* �������ʱA�൫�綯�Ƶ�ѹ */
	  s16 B_flaot_ADC;           /* �������ʱB�൫�綯�Ƶ�ѹ */
	  s16 C_flaot_ADC;           /* �������ʱC�൫�綯�Ƶ�ѹ */
	  s16 Bus_Vol_ADC;           /* ĸ�ߵ�ѹ */
	  s16 max_flaot_ADC;         /* ���綯��������ADC */
	  u8  MC_Fly_flg;            /* ˳�����־ */
      u8  MAX_bemf_flg;          /* ��󷴵綯�ƶ�Ӧ�� */	
	  u8  BEMF_step;             /* ����ʱת���������� */
	  u8  old_BEMF_step;         /* ����ʱ��һ��ת���������� */
	  u8  fly_start_step;        /* ˳����ʱת���������� */	
	  u32 sector_time[6];        /* ˳����ǰ����ÿһ�ĵ�ʱ�� */
	  u8  sector_time_cnt;       /* ��¼����ʱ��������� */
	  u32 fly_step_time;         /* ˳��������ʱת�ӻ���60��ʱ�� */
	  u32 fly_Speed;             /* ˳��������ʱת�ӻ���60��ʱ�� */	
	  u16 ON_FLY_Start_THD;         /* ˳��������ʱת�ӻ���60��ʱ�� */	  
	
	  u32 duty;                  /* ˳����ռ�ձ� */
	  u16 duty_fly;
	  u16 power;                 /* ˳�����ʼռ�ձȶ�Ӧռ�ձ� */
		
	  u16 ON_fly_cnt;

      u16 ON_Fly_Max_DUTY;
      u16 ON_Fly_Min_DUTY;	 
      u32 ON_Fly_delay_time;
	  
volatile u8  fly_cnt;               /* ˳����ǰת���жϴ��� */		  
volatile u32 communicate_delay_time;	  
	  	  	
}ON_flyStruct;

extern ON_flyStruct ON_fly;

#endif
