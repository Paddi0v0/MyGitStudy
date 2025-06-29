/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Time_Process.h
 * 文件标识：
 * 内容摘要： 定时相关函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/
/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __TIME_PROCESS_H
#define __TIME_PROCESS_H

#define PWM_TIME_500uS                    (u16)(PWM_FREQ/1000/2)
#define PWM_TIME_1MS                      (u16)(PWM_FREQ/1000)
#define PWM_TIME_2MS                      (u16)(2*PWM_FREQ/1000)
#define PWM_TIME_4MS                      (u16)(4*PWM_FREQ/1000)
#define COMM_PER_TIME_5MS              	  ((u16)10)   
#define PWM_TIME_10MS                     (u16)(20*PWM_FREQ/1000)
#define PWM_TIME_20MS      				  (u16)(40*PWM_FREQ/1000)

#define TASK_SCHEDU_1MS                   (2)                                      /* 任务调度1ms计数时长 */
#define TASK_SCHEDU_2MS                   (4)                                      /* 任务调度2ms计数时长 */
#define TASK_SCHEDU_10MS                  (20)                                     /* 任务调度10ms计数时长 */
#define TASK_SCHEDU_240MS                 (480)                                    /* 任务调度240ms计数时长 */
#define TASK_SCHEDU_500MS                 (1000)                                   /* 任务调度500ms计数时长 */

#endif
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
