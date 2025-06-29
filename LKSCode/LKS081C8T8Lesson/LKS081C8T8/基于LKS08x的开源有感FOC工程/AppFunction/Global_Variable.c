#include "absacc.h"
#include "MC_hall.h"
#include "MC_type.h"
#include "time_process.h"
#include "hardware_config.h"
#include "function_config.h" 

stru_TaskSchedulerDef struTaskScheduler;    			/* 任务调度结构体 */

volatile stru_FaultStatus_t stru_Faults;    			/* 系统错误调度结构体 */

stru_FOC_CtrProcDef struFOC_CtrProc;        			/* FOC电机控制流程结构体 */

stru_HallProcessDef  struHallProcess;    				/* Hall信号处理结构体 */

VoltageProtect_Struct stru_VoltageProtect;    			/* 工作电压结构体 */

stru_speed_control_handle strucontrol_handle;			/* 转把调速结构体 */

stru_motor_adjust_speed stru_motoradjust_speed;			/* 电机运行过程结构体 */

stru_break_eabs strubreak_eabs;							/* 刹车功能结构体 */

stru_motor_onekeyrun stru_motoronekeyrun;				/* 一键修复功能结构体 */

stru_motor_comprehensive stru_motorcomprehensive;		/* 存储，堵转功能结构体 */

stru_power_up strupower_up;								/* 上电初始化结构体 */

Stru_TempertureCof_Def m_TempertureCof;     			/* 温度传感器系数 */


volatile const FlashParamaStruct struFlashParama __at(HALL_LEARN_ADDR) =
{
    HALL0, HALL1, HALL2, HALL3, HALL4, HALL5, 0, 0,
    HALLTYPE, /* 120度Hall */
    MOTORTYPE0, /* 电机类型0 60度超前角 */
    0, 0, /* 字长对齐 */
    (CURRENT_LIM_VALUE), /* 母线电流限制 */
    VERSION0, VERSION1, VERSION2, VERSION3, /* 程序版本号0.3.0.1 */
    BEMFCOE, /* 反电动势系数 28  */
    HALL_OFFSET, /* hall超前角 */
    NUL1,	/* 限速标志 */
    NUL11,	/* 限速标志 */
    (CURRENT_LIM_VALUE), /* 母线电流限制 */
};









/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
