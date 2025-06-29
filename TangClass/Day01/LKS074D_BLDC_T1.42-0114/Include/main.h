
#ifndef __MAIN_H_
#define __MAIN_H_

#include "hardware_config.h"

void Hardware_init(void);
void sys_init(void);
void Task_Scheduler(void);
void Sys_State_Machine(void);
void Speed_control(void);
void Flash_write(void);
void Clear_error(void);
void Vol_protect(void);
void key_in_proc(void);
void Motor_Block_Protect(void);
void Dely_Turn_Off(void);
void OVER_current_protect(void);
void LED_display(void);
void LED_flicker_setting(void);
void TEMP_protect(void);
void Speed_Getting(void);

void Directions_Control(void);
void Block_error_Rev(void);

#define TASK_SCHEDU_1MS                   (2)                                      /* 任务调度1ms计数时长 */
#define TASK_SCHEDU_10MS                  (20)                                     /* 任务调度10ms计数时长 */
#define TASK_SCHEDU_100MS                 (200)                                    /* 任务调度100ms计数时长 */
#define TASK_SCHEDU_500MS                 (1000)                                   /* 任务调度500ms计数时长 */

typedef struct
{
    u8  bTimeCnt1ms;         /* 1mS计数器 */
    u16 nTimeCnt10ms;        /* 10mS计数器 */
    u16 nTimeCnt100ms;       /* 100mS计数器 */  
    u16 nTimeCnt500ms;       /* 500mS计数器 */
    u16 nSetTimeLeftCnt;     /* 延时处理函数 */
	u16 nMultiplex_cnt100ms; /* 100ms延时SWD口复用*/
} stru_TaskSchedulerDef;

extern stru_TaskSchedulerDef struTaskScheduler;      /* 任务调度结构体 */
#endif  /* __MAIN_H_ */


