/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� Main.c
 * �ļ���ʶ��
 * ����ժҪ�� ����������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet Li
 * ������ڣ� 2020��8��5��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�2020��8��16��
 * �� �� �ţ�V 1.0
 * �� �� �ˣ�Howlet Li
 * �޸����ݣ�����
 *
 *******************************************************************************/
#include "hardware_config.h"
#include "main.h"
stru_TaskSchedulerDef struTaskScheduler;    /* ������Ƚṹ�� */
stru_BLDC_CtrProcDef mBLDC_CtrProc;         /* BLDC���̿��ƽṹ�� */
/*******************************************************************************
 �������ƣ�    int main(void)
 ����������    ���������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/3/9      V1.0           Zhujie             ����
 *******************************************************************************/
int main(void)
{
    Hardware_init();      /* Ӳ����ʼ�� */

    sys_init();

    for(;;)
    {
      Task_Scheduler();
    }
}
/*******************************************************************************
 �������ƣ�    void Task_Scheduler(void)
 ����������    ��ʱ��Ƭ������Ⱥ���
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/6/8      V1.0        LSL          ����
 *******************************************************************************/
void Task_Scheduler(void)
{
    if (struTaskScheduler.bTimeCnt1ms >= TASK_SCHEDU_1MS)
    {   /* 1�����¼���������� */
        struTaskScheduler.bTimeCnt1ms = 0;
					
     Speed_Getting();       /* ת�ٻ�ȡ */
					
	 Speed_control();        /*����ź����봦��*/
			
	 Vol_protect();            /* ��ѹ���� */
			 	
//		OVER_current_protect();   /* �ּ��������� */
			
		Motor_Block_Protect();    /* ��ת���� */
			
//		TEMP_protect();         /* �¶ȱ��� */
			
//    Clear_error();           /* ���ϱ�־���� */
		
//		Block_error_Rev();    /* ��ת���� */

//		key_in_proc();           /* �ⲿ�������� */
			
//	   Directions_Control();    /* ����ת�л� */

//		Dely_Turn_Off();       /* ��ʱ�ϵ� */
			
		 LED_display();          /* LED��ʾ */
			  
	   speed_ref_ramp();       /* ռ�ձȴ��� */	

     Sys_State_Machine();    /* ���0״̬������ */
    }   

    if (struTaskScheduler.nTimeCnt10ms >= TASK_SCHEDU_10MS)
    {   /* 10�����¼���������� */
        struTaskScheduler.nTimeCnt10ms = 0;
    }
    
    if (struTaskScheduler.nTimeCnt100ms >= TASK_SCHEDU_100MS)
    {   /* 100�����¼���������� */
        struTaskScheduler.nTimeCnt100ms = 0;
					      
    }

    if (struTaskScheduler.nTimeCnt500ms >= TASK_SCHEDU_500MS)
    {   /* 500�����¼���������� */
        struTaskScheduler.nTimeCnt500ms = 0;
			  
    }

}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

