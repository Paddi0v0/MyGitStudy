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
    __disable_irq();               /* �ر��ж� �ж��ܿ��� */
    SYS_WR_PROTECT = 0x7a83;       /* ʹ��ϵͳ�Ĵ���д����*/
    FLASH_CFG |= 0x00080000;       /* FLASHԤȡ����ʹ��*/
    GPIO_init();                   /* GPIO��ʼ�� */
    CMP_Init();                    /* CMP_Init��ʼ�� */
    NVIC_SetPriority(CMP_IRQn, 3); // CMP�ж����ȼ�����
    NVIC_EnableIRQ(CMP_IRQn);      // ʹ��CMP��ʱ���ж�
    __enable_irq();                /* �����ж� */
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

    //CMP1_OUT  GPIO_P2.3����Ϊģ��ͨ��
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_3, AF1_SYSAF);
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
 �������ƣ�    void CMP_Init(void)
 ����������    �Ƚ�����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2016/3/15      V1.0           Howlet Li          ����
 *******************************************************************************/
void CMP_Init(void)
{
    CMP_InitTypeDef CMP_InitStruct;

    CMP_StructInit(&CMP_InitStruct);

    CMP_InitStruct.CMP0_EN = ENABLE;            /* �Ƚ���0���� ����SYS_AFE_REG5 */
    CMP_InitStruct.CMP0_SELN = SELN_REF;        /* �Ƚ���0�������ź�ѡ�� */
    CMP_InitStruct.CMP0_SELP = SELP_CMP_OPA0IP; /* CMP0_P CMP0_OPA0_IP */
    CMP_InitStruct.CMP0_InEnable = ENABLE;      /* �Ƚ����ź�����ʹ�� */
    CMP_InitStruct.CMP0_IE = ENABLE;            /* �Ƚ���0�ź��ж�ʹ�� */

    CMP_InitStruct.CMP1_EN = ENABLE;         /* �Ƚ���1���� */
    CMP_InitStruct.CMP1_SELN = SELN_REF;     /* CMP1_N �ڲ��ο� */
    CMP_InitStruct.CMP1_SELP = SELP_CMP_IP0; /* CMP1_P CMP1_IP0 */
    CMP_InitStruct.CMP1_InEnable = ENABLE;   /* �Ƚ����ź�����ʹ�� */
    CMP_InitStruct.CMP1_IE = ENABLE;         /* �Ƚ���1�ź��ж�ʹ�� */

    CMP_InitStruct.CMP_FltCnt = 15;     /* ���˲����=tclk ����*16*CMP_FltCnt (CMP_FltCnt��Ƶϵ��,0~15)*/
    CMP_InitStruct.CMP_CLK_EN = ENABLE; /* �Ƚ����ж�����ʱ�Ӵ� */

    Comparator_init(&CMP_InitStruct);
}



