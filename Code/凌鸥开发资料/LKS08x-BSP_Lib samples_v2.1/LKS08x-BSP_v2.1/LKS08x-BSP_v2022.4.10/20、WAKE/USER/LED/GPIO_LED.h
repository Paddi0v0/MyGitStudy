#ifndef __GPIO_LED_H__
#define __GPIO_LED__H__
#include "lks32mc08x_sys.h"

#define ALL_ON 1          //ȫ��
#define ALL_OFF 2         //ȫ��
#define Blink 3           //��˸
#define waterfall_light 4 //��ˮ��

/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
//LED1  P0.6
#define LED1_GPIO_PORT GPIO0            /* GPIO�˿� */
#define LED1_GPIO_Mode GPIO_Mode_OUT;   /*GPIO���ģʽ*/
#define LED1_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO������ģʽѡ��*/
#define LED1_GPIO_PIN GPIO_Pin_15       /*���GPIO�˿ں�*/

//LED2  P0.7
#define LED2_GPIO_PORT GPIO0            /* GPIO�˿� */
#define LED2_GPIO_Mode GPIO_Mode_OUT;   /*GPIO���ģʽ*/
#define LED2_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO������ģʽѡ��*/
#define LED2_GPIO_PIN  GPIO_Pin_7        /*���GPIO�˿ں�*/

//LED3  P0.3
#define LED3_GPIO_PORT GPIO0            /* GPIO�˿� */
#define LED3_GPIO_Mode GPIO_Mode_OUT;   /*GPIO���ģʽ*/
#define LED3_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO�Ȳ�����Ҳ������*/
#define LED3_GPIO_PIN GPIO_Pin_3        /*���GPIO�˿ں�*/

//LED1 2 3�����
#define LED1_OFF GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED2_OFF GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED3_OFF GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN)

//LED1 2 3�����
#define LED1_ON GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED2_ON GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED3_ON GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN)

void GPIO_LED(u8 mode);

#endif
