/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� hardware_init.c
 * �ļ���ʶ��
 * ����ժҪ�� Ӳ����ʼ������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Howlet Li
 * ������ڣ� 2015��11��5��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�
 * �� �� �ţ�
 * �� �� �ˣ�
 * �޸����ݣ�
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "gpio_led.h"
#include "gpio_key.h"
#include "utimer.h"
#include "WDT.h"
#include "lks32mc08x_MCPWM.h"

void UART_init(void);

/*******************************************************************************
 �������ƣ�    void Hardware_init(void)
 ����������    Ӳ�����ֳ�ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Hardware_init(void)
{
  __disable_irq();         /* �ر��ж� �ж��ܿ��� */
  SYS_WR_PROTECT = 0x7a83; /*ʹ��ϵͳ�Ĵ���д����*/
  FLASH_CFG |= 0x00080000; /* enable prefetch ��FLASHԤȡ����ʹ��*/

  GPIO_init(); /* GPIO��ʼ�� */
  HALL_Perip_Init();
  NVIC_EnableIRQ(HALL_IRQn); //ʹ��MCPWM�ж�
  NVIC_SetPriority(HALL_IRQn, 3);

  __enable_irq(); /* �����ж� */
}

/*******************************************************************************
 �������ƣ�    void GPIO_init(void)
 ����������    GPIOӲ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/

void GPIO_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_StructInit(&GPIO_InitStruct); //��ʼ���ṹ��

  //���ð��� start��P2.11  stop:P2.11
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO����ģʽ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO2, &GPIO_InitStruct);
  //����LED1��P0.6  LED2��P0.7  LED3: P0.3
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO���ģʽ
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO0, &GPIO_InitStruct);


  //GPIO_P2.4/P2.5/P2.6����ΪHALL_IN0/HALL_IN1/HALL_IN2ģ��ͨ��
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_Init(GPIO2, &GPIO_InitStruct);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF2_HALL);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF2_HALL);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_6, AF2_HALL);

}


/*******************************************************************************
 �������ƣ�    void Clock_Init(void)
 ����������    ʱ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Clock_Init(void)
{

  SYS_WR_PROTECT = 0x7a83;      /* ���ϵͳ�Ĵ���д���� */
  SYS_AFE_REG5 |= BIT15 | BIT0; /* BIT15:PLLPDN  BIT0:ADC_Clock*/
  SYS_CLK_CFG |= 0x000001ff;    /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff��Ӧ96Mʱ�� ; ��������ʱ��*/
}

/*******************************************************************************
 �������ƣ�    void SystemInit(void)
 ����������    Ӳ��ϵͳ��ʼ��������ʱ�ӳ�ʼ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2016/3/14      V1.0           Howlet Li          ����
 *******************************************************************************/
void SystemInit(void)
{
  Clock_Init(); /* ʱ�ӳ�ʼ�� */
}

/*******************************************************************************
 �������ƣ�    void HALL_Init(void)
 ����������    GPIOӲ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2018/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void HALL_Perip_Init(void)
{

  HALL_InitTypeDef HALL_InitStruct;

  HALL_StructInit(&HALL_InitStruct);
  HALL_InitStruct.FilterLen = 512;               /* Hall�ź������˲����� 512��ʱ������ */
  HALL_InitStruct.ClockDivision = HALL_CLK_DIV1; /* ����Hallģ��ʱ�ӷ�Ƶϵ�� */
  HALL_InitStruct.Filter75_Ena = DISABLE;        /* Hall�ź��˲���ʽ��7��5ģʽ����ȫ1��Чģʽ */
  HALL_InitStruct.HALL_Ena = ENABLE;             /* ģ��ʹ�� */
  HALL_InitStruct.Capture_IRQ_Ena = ENABLE;      /* ��׽�ж�ʹ�� */
  HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;     /* ��ʱ�ж�ʹ�� */
  HALL_InitStruct.softIE = ENABLE;               /* ����ж�ʹ�� */
  HALL_InitStruct.CountTH = 9600000;             /* Hallģ�����ģֵ����������ģֵ�������ʱ�ж� */

  HALL_Init(&HALL_InitStruct);
}


