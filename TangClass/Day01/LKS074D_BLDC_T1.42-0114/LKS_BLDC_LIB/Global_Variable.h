/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� Global_Variable.h
 * �ļ���ʶ��
 * ����ժҪ�� ȫ�ֱ��������ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet
 * ������ڣ� 2020��8��5��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�2020��8��5��
 * �� �� �ţ�V 1.0
 * �� �� �ˣ�Howlet
 * �޸����ݣ�����
 *
 *******************************************************************************/

#ifndef __GLOBAL_VARIABLE__
#define __GLOBAL_VARIABLE__

#include "lks32mc07x.h"
#include "basic.h"
#include "MC_IPD.h"
#include "ON_fly_start.h"
#include "bldc_control.h"
#include "mc_type.h" 

extern stru_BLDC_sensorlessCtr BLDC_SensorlessCtr;   /* ������ƽṹ�� */
extern stru_IPD_CtrProcDef mIPD_CtrProc;             /* IPD ת��λ�ù��ƽṹ�� */

extern void StopMotorImmdly(void);
extern void BLDC_CommunicationOnly(void);
extern void getBemfValue(void);
extern void bldc_comm_process(u8 flg);
extern void PWM_Output_Control(u8 output_flg);

#endif

/* ********************** (C) COPYRIGHT LINKO SEMICONDUCTOR ******************** */
/* ------------------------------END OF FILE------------------------------------ */
