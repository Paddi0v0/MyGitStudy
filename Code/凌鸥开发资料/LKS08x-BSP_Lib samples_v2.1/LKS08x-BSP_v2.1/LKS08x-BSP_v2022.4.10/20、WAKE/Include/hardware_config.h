/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� hardware_config.h
 * �ļ���ʶ��
 * ����ժҪ�� Ӳ������ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet
 * ������ڣ� 2020��8��20��
 *
 * �޸ļ�¼1��
 * �޸����ڣ� 2020��8��20��
 * �� �� �ţ� V 2.0
 * �� �� �ˣ� Howlet
 * �޸����ݣ� ����
 *
 *******************************************************************************/

/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "lks32mc08x.h"
#include "lks32mc08x_MCPWM.h"
#include "lks32mc08x_sys.h"
#include "lks32mc08x_adc.h"
#include "lks32mc08x_MCPWM.h"
#include "lks32mc08x_flash.h"
#include "lks32mc08x_Gpio.h"
#include "lks32mc08x_cmp.h"
#include "lks32mc08x_uart.h"
#include "lks32mc08x_hall.h"
#include "lks32mc08x_tim.h"
#include "hardware_init.h"
#include "lks32mc08x_NVR.h"
#include "delay.h"

#define  WAKE_EN  REG32(0x40012114)
#define  WAKE_PO  REG32(0x40012110)
#define GPIO0_0_POL BIT0 //P0.0��Ϊ����IO
#define GPIO0_1_POL BIT1 //P0.1��Ϊ����IO
#define GPIO1_0_POL BIT2 //P1.0��Ϊ����IO
#define GPIO1_1_POL BIT3 //P1.1��Ϊ����IO

#define High_Level  1    //IO���Ѹߵ�ƽ
#define Low_Level   0    //IO���ѵ͵�ƽ
/* ----------------------PWM Ƶ�ʼ���������----------------------------------- */
#define MCU_MCLK                       (96000000LL)       /* PWMģ��������Ƶ */
void SYS_UtimerFallSleep(void);
void InversP_Test(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SYS_SetWakeIO(uint32_t nInterval, u8 POL);
void SYS_FallSleepMode(void);
#include "delay.h"

#endif  /* __HARDWARE_CONFIG_H_ */

 
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
 
