#ifndef __GPIO_KEY_H__
#define __GPIO_KEY_H__
#include "lks32mc08x_sys.h"

#define start_PRES 1 //start����
#define stop_PRES 2  //stop����

/* ����KEY���ӵ�GPIO�˿� */
//START P2.11
#define START_GPIO_PORT GPIO2            /* GPIO�˿� */
#define START_GPIO_Mode GPIO_Mode_IN     /*GPIO���ģʽ*/
#define START_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO�Ȳ�����Ҳ������*/
#define START_GPIO_PIN GPIO_Pin_11       /*���GPIO�˿ں�*/

//STOP  P2.12
#define STOP_GPIO_PORT GPIO2            /* GPIO�˿� */
#define STOP_GPIO_Mode GPIO_Mode_IN     /*GPIO���ģʽ*/
#define STOP_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO�Ȳ�����Ҳ������*/
#define STOP_GPIO_PIN GPIO_Pin_12       /*���GPIO�˿ں�*/

#define key_start GPIO_ReadInputDataBit(START_GPIO_PORT, START_GPIO_PIN)
#define key_stop GPIO_ReadInputDataBit(STOP_GPIO_PORT, STOP_GPIO_PIN)

int GPIO_KEY_Scan(u8 mode);

#endif
