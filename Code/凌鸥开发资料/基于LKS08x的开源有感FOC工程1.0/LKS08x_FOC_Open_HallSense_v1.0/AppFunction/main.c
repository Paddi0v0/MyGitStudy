#include "Global_Variable.h"
#include "function_config.h" 

/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

int main(void)
{
    Hardware_init(); 										/* 硬件初始化程序 */
	
	struFOC_CtrProc.nSys_TimerPWM = 0;  

    while(struFOC_CtrProc.nSys_TimerPWM < 1500) {;}

    sys_init(); 											/* 系统初始化程序 */

    if(strucontrol_handle.hand_speed_adc > HBSPD_BASE) 		/* 防飞车保护 速度采样大于基准值报转把故障 */
    {
		stru_motoronekeyrun.break_hand_err_flg |= BIT0;
        stru_motoronekeyrun.power_up_hand_err_flg |= BIT0;
    }

    for (;;)
    {
        Task_Scheduler(); 									/* 主循环函数 */
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
