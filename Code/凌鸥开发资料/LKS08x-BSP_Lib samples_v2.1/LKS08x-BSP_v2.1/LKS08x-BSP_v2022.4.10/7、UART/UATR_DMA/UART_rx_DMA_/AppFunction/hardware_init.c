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
 * �޸����ڣ�2021��8��25��
 * �� �� �ţ�
 * �� �� �ˣ�HMG
 * �޸����ݣ�
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "lks32mc08x.h"
#include "lks32mc08x_DMA.h"

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
    FLASH_CFG |= 0x00080000; /*FLASHԤȡ����ʹ��*/
    GPIO_init();             /* GPIO��ʼ�� */
    UART_init();             /* UART��ʼ�� */
    DMA_init();              /* DMA��ʼ�� */

    NVIC_EnableIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, 0);
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

    //����UART0_RXD  P0.15
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    //����UART0_TXD  P1.0

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF4_UART);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF4_UART);
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
    UART_InitStruct.BaudRate = 9600;                 /* ���ò�����38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b; /* �������ݳ���8λ */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;     /* ֹͣλ1λ */
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;  /* �ȷ���LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;     /* ����żУ�� */
    UART_InitStruct.IRQEna = UART_IRQEna_RX_DMA_RE;  /* ʹ�ܽ�������ж�ʹ�� */
    UART_Init(UART0, &UART_InitStruct);
}
/*******************************************************************************
 �������ƣ�    void DMA_init(void)
 ����������    DMA��ʼ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    �ʣ�����ж�DMA_UART�Ĵ��䷽��
               ��DMA_DIR����DMA_UART�Ĵ��䷽��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
volatile u8 DMA_RX[10];
void DMA_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);

    /*UART DMA����ʹ�ܣ����յ�10�����ݺ󣬲���DMA�ж�*/
    DMA_InitStruct.DMA_Channel_EN = ENABLE;           /* DMA ͨ��ʹ��*/
    DMA_InitStruct.DMA_IRQ_EN = DMA_TCIE;             /* DMA ��������ж�ʹ�� */
    DMA_InitStruct.DMA_DIR = PERI2MEMORY;             /* �������ڴ� */
    DMA_InitStruct.DMA_CIRC = DISABLE;                /* DMA����ģʽ��ѭ��ģʽ������Ч */
    DMA_InitStruct.DMA_PINC = DISABLE;                /* �����ַÿ�����Ƿ����,����Ч */
    DMA_InitStruct.DMA_MINC = ENABLE;                 /* �ڴ��ַ�ڶ����Ƿ��ڵ�һ�ֵ�ַ�Ļ����ϵ���,����Ч */
    DMA_InitStruct.DMA_PBTW = DMA_BYTE_TRANS;         /* �������λ�� 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_MBTW = DMA_BYTE_TRANS;         /* �ڴ����λ�� 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_CH2_UART0_REQ_EN; /* ͨ�� DMA_UART0_REQ_EN DMA ����ʹ�ܣ�����Ч */
    DMA_InitStruct.DMA_TIMES = 1;                     /* DMA ͨ�� x ÿ�����ݰ��˴��� 1~511 */
    DMA_InitStruct.DMA_ROUND = 10;                    /* DMA ͨ�� x �������� 1~255 */
    DMA_InitStruct.DMA_CPAR = (u32)&UART0_BUFF;       /* DMA ͨ�� x �����ַ */
    DMA_InitStruct.DMA_CMAR = (u32)DMA_RX;            /* DMA ͨ�� x �ڴ��ַ */
    DMA_Init(DMA_CH2, &DMA_InitStruct);
}

/*******************************************************************************
 �������ƣ�    void Delay(void)
 ����������    ��ʱ����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/9/1      V1.0             HMG                ����
 *******************************************************************************/
void Delay(u32 cnt)
{
    u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}
