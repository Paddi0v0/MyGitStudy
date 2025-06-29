#ifndef __GLOBAL_VARIABLE__
#define __GLOBAL_VARIABLE__

#include "MC_type.h"
                                                  
extern stru_TaskSchedulerDef struTaskScheduler;      			/* 任务调度结构体 */

extern volatile stru_FaultStatus_t stru_Faults;      			/* 系统错误调度结构体 */

extern stru_FOC_CtrProcDef struFOC_CtrProc;          			/* FOC电流内环结构体 */

extern stru_HallProcessDef  struHallProcess;    				/* Hall信号处理结构体 */

extern volatile const FlashParamaStruct struFlashParama;		/* HALL相序，相线偏置等相关常量定义 */

extern VoltageProtect_Struct stru_VoltageProtect;    			/* 工作电压结构体 */

extern stru_speed_control_handle strucontrol_handle;			/* 转把调速结构体 */

extern stru_motor_adjust_speed stru_motoradjust_speed;			/* 电机运行过程结构体 */

extern stru_break_eabs strubreak_eabs;							/* 刹车功能结构体 */

extern stru_motor_onekeyrun stru_motoronekeyrun;				/* 一键修复功能结构体 */

extern stru_motor_comprehensive stru_motorcomprehensive;		/* 存储，堵转功能结构体 */

extern stru_power_up strupower_up;								/* 上电初始化结构体 */

extern Stru_TempertureCof_Def m_TempertureCof;       			/* 温度传感器系数 */

#define GET_ELECTRICAL_ANGLE HALL_GetElectricalAngle(&struHallProcess)	/* 角度获取 */



void sys_init(void);
void ADC_init(void);
void PGA_init(void);
void DAC_init(void);
void CMP_init(void);
void GPIO_init(void);
void UART_init(void);
void GPIO_init(void);
void MCPWM_init(void);
void Clock_init(void);
void motor_break(void);
void UTimer_init(void);
void key_in_proc(void);
u8 ReadHallState(void);
void SoftDelay(u32 cnt);
void Power_Up_Init(void);
void Hardware_init(void);
void Power_Options (void);
void speed_ref_ramp(void);
void Task_Scheduler(void);
void power_zero_Pro(void);
u8 ReadHallStateMix(void);
void HALL_Perip_Init(void);
void TempSensor_Init(void);
void break_state_Pro(void);
void Flash_Write_Pro(void);
void StopMotorImmdly(void);
u8 SetTime_IsElapsed(void);
void speed_adjustment(void);
void gliding_movement(void);
void Sys_State_Machine(void);
void ADC_NormalModeCFG(void);
void FOC_InitstruParama(void);
void Motor_Block_Protect(void);
void PWMOutputs(FuncState t_state);
void CurrentOffsetCalibration(void);
void functional_variables_init(void);
void FOC_Model(stru_FOC_CtrProcDef *this);
void SetTime_TimeOut_Counter(u16 hTimeout);
void MCL_Init(stru_FOC_CtrProcDef *pCtrProc);
void SVPWM_2PH(stru_FOC_CtrProcDef *pCtrProc);
void speed_up_down(stru_FOC_CurrLoopDef *this);
stru_TrigComponents Trig_Functions(s16 hAngle);
s16 lowPass_filter(stru_RC_Def *rc, s16 signal);
void set_OPA_offset(stru_FOC_CurrLoopDef *this);
void HALL_IRQProcess(stru_HallProcessDef *this);
u32 GetAvrgHallPeriod(stru_HallProcessDef *this);
void key_capture(stru_motor_comprehensive *this);
void check_Vol_Temp(VoltageProtect_Struct *this);
void closeLoopAnglePLL(stru_HallProcessDef *this);
void Verify_Hall_State(stru_HallProcessDef *this);
void MCPWM0_RegUpdate(stru_FOC_CurrLoopDef *this);
void judgement_offset(stru_FOC_CurrLoopDef *this);
void hall_sensor_period(stru_HallProcessDef *this);
stru_CurrVoctor Clarke(stru_CurrVoctor Curr_Input);
void reduceToqueAnglePll(stru_HallProcessDef *this);
void LowPass_Filter_Init(stru_FOC_CtrProcDef *this);
void HALL_InitHallMeasure(stru_HallProcessDef *this);
void speed_adjustment_pi(stru_FOC_CurrLoopDef *this);
void closeLoopAnglePLLInit(stru_HallProcessDef *this);
void Speed_Power_Pro(stru_speed_control_handle *this);
s16 HALL_GetElectricalAngle(stru_HallProcessDef *this);
void hall_comm_VariableInit(stru_HallProcessDef *this);
void VoltageRampControl(stru_FOC_CtrProcDef *pCtrProc);
void FOC_CtrProcFilterInit(stru_FOC_CurrLoopDef *this);
u8 check_hall_state(u8 t_hall, stru_HallProcessDef *this);
void HALL_Init_Electrical_Angle(stru_HallProcessDef *this);
void CopyFromBuffer(u8* nDestAddr, u8* pSrcBuff, u16 nSize);
void Get_PhaseCurrent_AndFilter(stru_FOC_CurrLoopDef *this);
void RevPark_Circle_Limitation(stru_FOC_CtrProcDef *pCtrProc);
void calc_first_ElectAngle(u16 angle, stru_HallProcessDef *this);
void Hall_ElecAnglePWM_Process(stru_HallProcessDef *struHallProcess);
stru_CurrVoctor Park(stru_CurrVoctor,s16, stru_FOC_CurrLoopDef *this);
s16 HL_PI_AntiDump(s16 DesiredValue,s16 MeasuredValue,stru_PIparams *pParams);
stru_VoltVoctor Rev_Park(stru_VoltVoctor Volt_Input, stru_FOC_CurrLoopDef *this); 
stru_CurrVoctor SVPWM_2PH_3ShuntGetPhaseCurrentValues(stru_FOC_CurrLoopDef *this);


#endif



/* ********************** (C) COPYRIGHT LINKO SEMICONDUCTOR ******************** */
/* ------------------------------END OF FILE------------------------------------ */
