#ifndef __GLOBAL_VARIABLE__
#define __GLOBAL_VARIABLE__

#include "mc_type.h"
extern stru_FOC_CtrProcDef struFOC_CtrProc;          			/* FOC电流内环结构体 */

void Hardware_init(void); 										/* 硬件初始化程序 */
void sys_init(void); 										/* 系统初始化程序 */
void Task_Scheduler(void); 									/* 主循环函数 */
void DSP_Init(void);    /* DSP模块初始化*/
void ADC_init(void);    /* ADC初始化 */
void MCPWM_init(void);  /* PWM初始化 */
void UTimer_init(void); /* 通用计数器初始化 */
void GPIO_init(void);   /* GPIO初始化 */
void PGA_init(void);    /* PGA 初始化 */
void SoftDelay(u32);    /* 延时等待硬件初始化稳定 */
void ADC_NormalModeCFG(void);
void FOC_Model(stru_FOC_CtrProcDef *pCtrProc);
void StopMotorImmdly(stru_FOC_CtrProcDef *this);
void SetTime_TimeOut_Counter(u16 hTimeout);
void Sys_State_Run(stru_FOC_CtrProcDef *this);
stru_VoltVoctorDQ RevPark_Circle_Limitation(stru_VoltVoctorDQ VoltVoctorDQ);
void MCPWM0_RegUpdate(stru_VoltPhaseUVW VoltPhaseUVW);
void MCL_Init(stru_FOC_CtrProcDef *pCtrProc);
void Curr_rc_fir(Stru_Curr_RC * this);
void currentOffsetRead(void);
void FOC_InitstruParama(stru_FOC_CtrProcDef *this);
void Sys_State_Machine(stru_FOC_CtrProcDef *this);
void Key_in(stru_FOC_CtrProcDef *this);

stru_VoltPhaseUVW   SVPWM(stru_VoltAlphBeta,u16 hPWM_PERIOD);
stru_CurrAlphBeta   Clarke(stru_CurrPhaseUVW uvw);
stru_CurrVoctorDQ   Park(stru_CurrAlphBeta ab, stru_TrigComponents TrigComponents);
stru_VoltAlphBeta   Rev_Park(stru_VoltVoctorDQ dq, stru_TrigComponents TrigComponents);
stru_TrigComponents Trig_Functions(s16 hAngle);
#endif



/* ********************** (C) COPYRIGHT LINKO SEMICONDUCTOR ******************** */
/* ------------------------------END OF FILE------------------------------------ */
