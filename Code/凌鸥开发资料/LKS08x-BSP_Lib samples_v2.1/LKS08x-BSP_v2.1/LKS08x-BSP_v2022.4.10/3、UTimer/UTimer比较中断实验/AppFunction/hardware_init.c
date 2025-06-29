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
 * �޸����ڣ� 2021��8��27��
 * �� �� �ţ�
 * �� �� �ˣ�
 * �޸����ݣ�
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "gpio_led.h"
#include "gpio_key.h"
void Delay(u32 cnt);
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
    UTimer_init();           /* UTimer��ʼ�� */
    __enable_irq();          /* �����ж� */
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

    /* ����UTimer0  TIM0_CH0: P0.15 */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO0,GPIO_PinSource_15,AF7_TIMER01); //P0.15����Ϊtimer0�����ģʽ
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

    SYS_WR_PROTECT = 0x7a83;   /* ���ϵͳ�Ĵ���д���� */
    SYS_AFE_REG5 |= BIT15;     /* BIT15:PLLPDN */
	  Delay(100);                /* �ȴ�PLL�ȶ�*/
    SYS_CLK_CFG |= 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff��Ӧ96Mʱ�� */
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
 �������ƣ�    void UTimer_init(void)
 ����������    UTimerӲ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UTimer_init(void)
{

    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerCmd(TIMER0, ENABLE); /* Timer0 ģ��ʹ�� */

    TIM_TimerStrutInit(&TIM_InitStruct);                  /* Timer�ṹ���ʼ��*/
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; /* ����Timer CH0 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None;/* �޲���*/
    TIM_InitStruct.Timer_CH0Output = 0;                   /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; /* ����Timer CH1 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH1Output = 0;                   /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_TH = 48000;    									/* ��ʱ���������޳�ʼֵ1000*/
    TIM_InitStruct.Timer_CMP0 = 24000;  									/* ���ñȽ�ģʽ��CH0�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_CMP1 = 24000;  									/* ���ñȽ�ģʽ��CH1�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_Filter0 = 0;  										/* ���ò�׽ģʽ�������ģʽ�¶�Ӧͨ���������˲�ֵ */
    TIM_InitStruct.Timer_Filter1 = 0;  									  /* ���ò�׽ģʽ�������ģʽ�¶�Ӧͨ���������˲�ֵ */
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div2;         /* ����Timerģ��ʱ��2��Ƶϵ�� */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | Timer_IRQEna_Zero; /* ����Timerģ��Ƚ��жϺ͹����ж�*/
    TIM_TimerInit(TIMER0, &TIM_InitStruct);

    NVIC_SetPriority(TIMER0_IRQn, 0); //TIMER0�ж����ȼ�����
    NVIC_EnableIRQ(TIMER0_IRQn);      //ʹ��UTimer��ʱ���ж�
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
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Delay(u32 cnt)
{
	u32 t_cnt;

	for (t_cnt = 0; t_cnt < cnt; t_cnt++)
	{
		__nop();
	}
}
/*******************************************************************************
 �������ƣ�    void GPIO_LED(void)
 ����������    LEDȫ��ȫ����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void GPIO_LED(u8 mode)
{
   switch(mode)
	 {
	   case ALL_ON:
			    LED1_ON;
		      LED2_ON;
		      LED3_ON;
		 break;
			 
		 case ALL_OFF:
					LED1_OFF;
					LED2_OFF;
					LED3_OFF;
		 break;
			 
	 }		 
}
/*******************************************************************************
 �������ƣ�    void Invers_GPIO(void)
 ����������    LED��ƽ��ת����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Invers_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)//GPIO��ƽ��ת����
{
  u16 reg;
	reg = GPIO_ReadOutputDataBit(GPIOx,GPIO_Pin);//��GPIO��ƽ
	if(reg)
	{
		GPIO_ResetBits(GPIOx,GPIO_Pin);
	}
	else
	{
		GPIO_SetBits(GPIOx,GPIO_Pin);
	}
}


