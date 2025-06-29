/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Main.c
 * 文件标识：
 * 内容摘要： 工程主代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/
#include "hardware_config.h"
#include "main.h"
stru_TaskSchedulerDef struTaskScheduler;    /* 任务调度结构体 */
stru_BLDC_CtrProcDef mBLDC_CtrProc;         /* BLDC过程控制结构体 */
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/9      V1.0           Zhujie             创建
 *******************************************************************************/
int main(void)
{
    Hardware_init();      /* 硬件初始化 */

    sys_init();

    for(;;)
    {
      Task_Scheduler();
    }
}
/*******************************************************************************
 函数名称：    void Task_Scheduler(void)
 功能描述：    按时间片任务调度函数
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          创建
 *******************************************************************************/
void Task_Scheduler(void)
{
    if (struTaskScheduler.bTimeCnt1ms >= TASK_SCHEDU_1MS)
    {   /* 1毫秒事件，任务调度 */
        struTaskScheduler.bTimeCnt1ms = 0;
					
     Speed_Getting();       /* 转速获取 */
					
	 Speed_control();        /*扳机信号输入处理*/
			
	 Vol_protect();            /* 电压保护 */
			 	
//		OVER_current_protect();   /* 分级限流保护 */
			
		Motor_Block_Protect();    /* 堵转保护 */
			
//		TEMP_protect();         /* 温度保护 */
			
//    Clear_error();           /* 故障标志清零 */
		
//		Block_error_Rev();    /* 堵转重启 */

//		key_in_proc();           /* 外部按键输入 */
			
//	   Directions_Control();    /* 正反转切换 */

//		Dely_Turn_Off();       /* 延时断电 */
			
		 LED_display();          /* LED显示 */
			  
	   speed_ref_ramp();       /* 占空比处理 */	

     Sys_State_Machine();    /* 电机0状态机调度 */
    }   

    if (struTaskScheduler.nTimeCnt10ms >= TASK_SCHEDU_10MS)
    {   /* 10毫秒事件，任务调度 */
        struTaskScheduler.nTimeCnt10ms = 0;
    }
    
    if (struTaskScheduler.nTimeCnt100ms >= TASK_SCHEDU_100MS)
    {   /* 100毫秒事件，任务调度 */
        struTaskScheduler.nTimeCnt100ms = 0;
					      
    }

    if (struTaskScheduler.nTimeCnt500ms >= TASK_SCHEDU_500MS)
    {   /* 500毫秒事件，任务调度 */
        struTaskScheduler.nTimeCnt500ms = 0;
			  
    }

}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

