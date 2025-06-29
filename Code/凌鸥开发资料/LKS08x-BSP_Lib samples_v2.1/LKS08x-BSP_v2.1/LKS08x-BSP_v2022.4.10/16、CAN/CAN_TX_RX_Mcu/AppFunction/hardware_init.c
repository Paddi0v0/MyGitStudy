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
#include "can.h"
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
    __disable_irq(); /* �ر��ж� �ж��ܿ��� */
    SYS_WR_PROTECT = 0x7a83; /*ʹ��ϵͳ�Ĵ���д����*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ��FLASHԤȡ����ʹ��*/

    GPIO_init();   /* GPIO��ʼ�� */
    CAN_Init(0x1D,0x1C);  /*������100k*/
//	SFF_ID_Filter(0X5555 ,0x0000,0,0 ,0x08,0x0,0x55,0x0);/*��׼֡��ID�˲� ��׼֡���˲�ID�˲���ʾ*/
//	  EFF_ID_Filter(0X5555 ,0x0000,0,0);                   /*��չ֡��ID�˲� ��չ֡���˲�ID�˲���ʾ*/
//  ID1_Filter_Dual(0X11 ,0x0000,0,1 ,0x55,0xff,0);      /*CAN˫ID������ID1�˲� ��׼֡˫�˲�ID1�˲���ʾ*/
//	ID2_Filter_Dual(0Xaa ,0x0000,0,0,0);                 /*CAN˫ID������ID2�˲� ��׼֡˫�˲�ID2�˲���ʾ*/
	  ID1_Filter_Dual(0x0fA2000 ,0x00000000,0,0 ,0x0,0x0,1);      /*CAN˫ID������ID1�˲� ��չ֡˫�˲�ID1�˲���ʾ*/
    ID2_Filter_Dual(0x1fEE000 ,0x00000000,0,0,1);                 /*CAN˫ID������ID2�˲� ��չ֡˫�˲�ID2�˲���ʾ*/
	
	  NVIC_SetPriority(CAN_IRQn,1);
		NVIC_EnableIRQ(CAN_IRQn);
	
    __enable_irq();/* �����ж� */
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;//GPIO����ģʽ
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);	
	  //����LED1��P0.6  LED2��P0.7  LED3: P0.3
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//GPIO���ģʽ
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);	
		
		/* ����UTimer3  TIM3_CH0: P2.8   TIM3_CH1: P1.3*/
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIO2, &GPIO_InitStruct);
		
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIO1, &GPIO_InitStruct);
		
	  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_3, AF8_TIMER23);//����
		GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF8_TIMER23);//����
}

/*******************************************************************************
 �������ƣ�    void ADC0_init(void)
 ����������    ADC0Ӳ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure); //��ʼ���ṹ��
    ADC0_CHN0 = 0x09;                   //����ͨ��ͨ��9

    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;           //��һ��ɨ������ж�
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;         //ADC������������
    ADC_InitStructure.FirSeg_Ch = ADC_1_TIMES_SAMPLE; //����ͨ����
    ADC_InitStructure.UTIMER_Trigger_En = DISABLE;    //�ر�Ӳ������
    ADC_InitStructure.MCPWM_Trigger_En = DISABLE;     //�ر�Ӳ������
    ADC_InitStructure.Trigger_Cnt = 1;
    ADC_Init(ADC0, &ADC_InitStructure);

    ADC0_IF = 0xff; //���жϱ�־λ
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
    UART_InitStruct.BaudRate = 38400;                /* ���ò�����38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b; /* �������ݳ���8λ */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;     /* ֹͣλ1λ */
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;  /* �ȷ���LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;     /* ����żУ�� */
    UART_InitStruct.IRQEna = ENABLE;                 /* �����ж�ʹ�� */
    UART_Init(UART0, &UART_InitStruct);
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
 �������ƣ�    void TempSensor_Init(void)
 ����������    �¶ȴ�������ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void TempSensor_Init(void)
{
}

/*******************************************************************************
 �������ƣ�    void PGA_Init(void)
 ����������    PGA��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2016/3/15      V1.0           Howlet Li          ����
 *******************************************************************************/
void PGA_Init(void)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA0, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA1, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA2, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA3, ENABLE);
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

    CMP_InitStruct.CMP0_EN = ENABLE; /* �Ƚ���0���� */
    CMP_InitStruct.CMP0_SELN = SELN_DAC;
    CMP_InitStruct.CMP0_SELP = SELP_CMP_OPA0IP; /* CMP0_P CMP0_OPA0IP */
    CMP_InitStruct.CMP0_InEnable = ENABLE;      /* �Ƚ����ź�����ʹ�� */
    CMP_InitStruct.CMP0_IE = DISABLE;           /* �Ƚ���0�ź��ж�ʹ�� */

    CMP_InitStruct.CMP1_EN = ENABLE;         /* �Ƚ���1���� */
    CMP_InitStruct.CMP1_SELN = SELN_DAC;     /* CMP1_N �ڲ��ο� */
    CMP_InitStruct.CMP1_SELP = SELP_CMP_IP0; /* CMP1_P CMP1_OPA3 */
    CMP_InitStruct.CMP1_InEnable = ENABLE;   /* �Ƚ����ź�����ʹ�� */
    CMP_InitStruct.CMP1_IE = ENABLE;         /* �Ƚ���1�ź��ж�ʹ�� */

    CMP_InitStruct.CMP_FltCnt = 15;     /* ���˲����=tclk ����*16*CMP_FltCnt */
    CMP_InitStruct.CMP_CLK_EN = ENABLE; /* ʱ��ʹ�� */

    Comparator_init(&CMP_InitStruct);
	
}

/*******************************************************************************
 �������ƣ�    void DAC_Init(void)
 ����������    DAC��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2016/3/23      V1.0           Howlet Li          ����
 *******************************************************************************/
void DAC_Init(void)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC, ENABLE);
    SYS_WR_PROTECT = 0x7a83;
    SYS_AFE_DAC = 512; /* 1.2*512/4096/0.05 = 3A, ����0.05Ϊĸ�߲�������*/
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
    HALL_InitStruct.CountTH = 9600000;             /* Hallģ�����ģֵ����������ģֵ�������ʱ�ж� */

    HALL_Init(&HALL_InitStruct);
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
     TIM_TimerCmd(TIMER3, ENABLE); /* Timer0 ģ��ʹ�� */
     TIM_TimerStrutInit(&TIM_InitStruct);//Timer�ṹ���ʼ��


		 TIM_InitStruct.Timer_Filter0 = 1; /*CH0�˲����˲����ΪTimer_Filter0*8��ʱ������*/
		 TIM_InitStruct.Timer_Filter1 = 1;
		 TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1; //12M
     TIM_TimerInit(TIMER3, &TIM_InitStruct);
		
     UTIMER_ECD1_CNT = 0;   
		 UTIMER_ECD1_TH = 4096;
		 UTIMER_ECD1_CFG = (0<<8); 

     UTIMER_CFG |= (1<<9);    
}

void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = 0;           /* MCPWMʱ�ӷ�Ƶ���� */
    MCPWM_InitStructure.MCLK_EN = ENABLE;      /* ģ��ʱ�ӿ��� */
    MCPWM_InitStructure.MCPWM_Cnt_EN = ENABLE; /* ����������ʼ����ʹ�ܿ��� */
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE; /* ͨ������ģʽ���ã����Ķ������ض��� */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12; /* ��ͣ�¼�(����IO���ź�)�����˲���ʱ������ */
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;  /* ��ͣ�¼�(���ԱȽ����ź�)�����˲���ʱ������ */

    MCPWM_InitStructure.MCPWM_PERIOD = PWM_PERIOD;              /* ������������ */
    MCPWM_InitStructure.TriggerPoint0 = (u16)(10 - PWM_PERIOD); /* MCPWM_TMR0 ADC�����¼�T0 ���� */
    MCPWM_InitStructure.TriggerPoint1 = (u16)(PWM_PERIOD - 1);  /* MCPWM_TMR1 ADC�����¼�T1 ���� */
    MCPWM_InitStructure.DeadTimeCH0N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH0P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2P = DEADTIME; /* ����ʱ������ */

#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)           /* CHxP ����Ч�� CHxN�͵�ƽ��Ч */
    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;  /* CH0Nͨ������������� | ���������ȡ�����*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE; /* CH0Pͨ������������� | ���������ȡ����� */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; /* ͨ������ѡ������ */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* ͨ������ѡ������ */

    /* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM_IO01��MCPWM_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
                                                     ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;  /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
    MCPWM_InitStructure.CH1N_default_output = HIGH_LEVEL; /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = HIGH_LEVEL;
#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH) /* CHxP ����Ч�� CHxN�ߵ�ƽ��Ч */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE; /* CH0Nͨ������������� | ���������ȡ�����*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE; /* CH0Pͨ������������� | ���������ȡ����� */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; /* ͨ������ѡ������ */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* ͨ������ѡ������ */

    /* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM_IO01��MCPWM_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
                                                     ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL; /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
    MCPWM_InitStructure.CH1N_default_output = LOW_LEVEL; /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = LOW_LEVEL;
#endif
#endif

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE; /* �ڽ��Ϸ�����debug����ʱ����ͣMCU����ʱ��ѡ���PWMͨ��������������ź�
                                                                 �������Ĭ�ϵ�ƽ�������������� ENABLE:������� DISABLE:���Ĭ�ϵ�ƽ*/

    MCPWM_InitStructure.MCPWM_T0_UpdateEN = ENABLE;  /* MCPWM T0�¼�����ʹ�� */
    MCPWM_InitStructure.MCPWM_T1_UpdateEN = DISABLE; /* MCPWM T1�¼����� ��ֹ*/

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    MCPWM_InitStructure.T1_Update_INT_EN = ENABLE; /* T0�����¼� �ж�ʹ�ܻ�ر� */
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE; /* T0�����¼� �ж�ʹ�ܻ�ر� */
#else
#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE; /* T0�����¼� �ж�ʹ�ܻ�ر� */
#endif
#endif
#endif

    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;             /* FAIL0�¼� �ж�ʹ�ܻ�ر� */
    MCPWM_InitStructure.FAIL0_INPUT_EN = DISABLE;           /* FAIL0ͨ����ͣ���ܴ򿪻�ر� */
    MCPWM_InitStructure.FAIL0_Signal_Sel = FAIL_SEL_CMP;    /* FAIL0�¼��ź�ѡ�񣬱Ƚ�����IO�� */
    MCPWM_InitStructure.FAIL0_Polarity = HIGH_LEVEL_ACTIVE; /* FAIL0�¼�����ѡ�񣬸���Ч */

    MCPWM_InitStructure.FAIL1_INT_EN = ENABLE;              /* FAIL1�¼� �ж�ʹ�ܻ�ر� */
    MCPWM_InitStructure.FAIL1_INPUT_EN = ENABLE;            /* FAIL1ͨ����ͣ���ܴ򿪻�ر� */
    MCPWM_InitStructure.FAIL1_Signal_Sel = FAIL_SEL_CMP;    /* FAIL1�¼��ź�ѡ�񣬱Ƚ�����IO�� */
    MCPWM_InitStructure.FAIL1_Polarity = HIGH_LEVEL_ACTIVE; /* FAIL1�¼�����ѡ�񣬸���Ч�����Ч */

    MCPWM_Init(&MCPWM_InitStructure);
}

/*******************************************************************************
 �������ƣ�    void seekPosADCsetting(void)
 ����������    ����IPD����ǰ������ADC����ģʽ��Ϊ��ʼλ�ü����׼��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void seekPosADCsetting(void)
{
    ADC0_TRIG = BIT1;         /*Ӳ������ADC MCPWM T1��ʹ�� */
    ADC0_CFG |= BIT2;         /*״̬����λ��idle״̬����ɺ��Զ���0 */
    MCPWM_TMR0 = PWM_PERIOD;  /*ADC����ʱ��0����Ϊ���Źض����ĵ� */
    MCPWM_TMR1 = (u16)(-600); /*ADC����ʱ��1����ΪPWM���ĵ����ƫ600��Clock*/
}

/*******************************************************************************
 �������ƣ�    void DebugPWM_OutputFunction(void)
 ����������    PWM������ܵ���   ���25%ռ�ձ�
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void DebugPWM_OutputFunction(void)
{
    MCPWM_TH00 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH01 = (PWM_PERIOD >> 2);
    MCPWM_TH10 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH11 = (PWM_PERIOD >> 2);
    MCPWM_TH20 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH21 = (PWM_PERIOD >> 2);

    PWMOutputs(ENABLE);
    while (1)
    {
    }
}

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
/*******************************************************************************
 �������ƣ�    void MCPWM0_RegUpdate(void)
 ����������    ����MCPWMģ��ռ�ձ�ֵ������MCPWMģ��ADC������Ĵ���ֵ
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void MCPWM0_RegUpdate(void)
{
}

#else

#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
/*******************************************************************************
 �������ƣ�    void MCPWM0_RegUpdate(void)
 ����������    ����MCPWMģ��ռ�ձ�ֵ������MCPWMģ��ADC������Ĵ���ֵ
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void MCPWM0_RegUpdate(void)
{
    MCPWM_TH00 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;
    MCPWM_TH01 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;

    MCPWM_TH10 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
    MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

    MCPWM_TH20 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
    MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
}

#endif

#ifdef TEST_FLASH
void Flash_Test(void)
{
    /**********************�����ǵ���Flash���������ʾ��****************************/

    u8 testBuf[512] = {
        1,
        2,
        3,
        4,
        5,
    };
    volatile u8 flashRlt;

    erase_flag = 0x9A0D361F; //д��������
    EraseSector(0x7800, 0);
    progm_flag = 0x9AFDA40C; //д�������
    flashRlt = ProgramPage(0x7800, 512, (u8 *)&testBuf[0], 0);
    /*******************************************************************************/
}
#endif

#endif
