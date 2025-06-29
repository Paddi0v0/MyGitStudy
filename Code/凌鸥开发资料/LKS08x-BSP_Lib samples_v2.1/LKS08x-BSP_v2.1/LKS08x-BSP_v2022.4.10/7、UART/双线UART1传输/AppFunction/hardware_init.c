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
  GPIO_init();             /* GPIO��ʼ�� */
  UART_init();
  NVIC_EnableIRQ(UART1_IRQn);      //�򿪴���1�ж�
  NVIC_SetPriority(UART1_IRQn, 1); //�ж����ȼ�����

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


  //����UART1_RXD  P2.4
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO2, &GPIO_InitStruct);
  //����UART1_TXD  P2.5

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO2, &GPIO_InitStruct);

  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF4_UART);
  GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF4_UART);
}


/*******************************************************************************
 �������ƣ�    void UART_init(void)
 ����������    UART0�Ĵ�������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UART_init(void)
{
  UART_InitTypeDef UART_InitStruct;

  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.BaudRate = 2400;                                     /* ���ò�����38400 */
  UART_InitStruct.WordLength = UART_WORDLENGTH_8b;                     /* �������ݳ���8λ */
  UART_InitStruct.StopBits = UART_STOPBITS_1b;                         /* ֹͣλ1λ */
  UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;                      /* �ȷ���LSB */
  UART_InitStruct.ParityMode = UART_Parity_NO;                         /* ����żУ�� */
  UART_InitStruct.IRQEna = UART_IRQEna_SendOver | UART_IRQEna_RcvOver; /* �����ж�ʹ�� */
  UART_Init(UART1, &UART_InitStruct);
  UART1_IF = 0xff;
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
 �������ƣ�    void UART0_SENDDATA(void)
 ����������    UART0���ͳ���
 ���������    n����Ҫ���͵�ֵ
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UART0_SENDDATA(UINT8 n)
{
  UART0_BUFF = n;
}

/*******************************************************************************
 �������ƣ�    void UART1_SENDDATA(void)
 ����������    UART1���ͳ���
 ���������    n����Ҫ���͵�ֵ
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UART1_SENDDATA(UINT8 n)
{
  UART1_BUFF = n;
}



