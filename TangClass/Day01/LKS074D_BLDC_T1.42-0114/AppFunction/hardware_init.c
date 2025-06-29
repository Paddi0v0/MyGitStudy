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
#include "hardware_config.h"
#include "hardware_init.h"
#include "basic.h"
#include "SEGGER_RTT.h"
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
    Clock_Init();  /* ʱ�ӳ�ʼ�� */
}
/*******************************************************************************
 �������ƣ�    void Clock_Init(void)
 ����������    ʱ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 2021/4/17      V1.1           Howlet Li          ������ʱ�������ȴ�PLL�ȶ�
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;    /* ���ϵͳ�Ĵ���д���� */
    SYS_AFE_REG5 |= BIT15;      /* BIT15:PLLPDN ��PLL */
	SYS_SFT_RST = 0xffff;       /* ����ģ����λhold */
    Soft_Delay(400);            /* ��ʱ100us, �ȴ�PLL�ȶ� 21.4.17*/
	SYS_SFT_RST = 0;            /* ����ģ����λ�ͷ� */
    SYS_CLK_CFG = 0x000001ff;   /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff��Ӧ96Mʱ�� */
	SYS_WR_PROTECT = 0;         /* �ر�ϵͳ�Ĵ���д����*/
}
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
    __disable_irq();                  /* �ر��ж� �ж��ܿ��� */
    SYS_WR_PROTECT = 0x7a83;
    IWDG_DISABLE();                   /* �رտ��Ź�*/
    FLASH_CFG |= 0x00080000;          /* enable prefetch */

	  Timer0_init();                    /* Time0��ʼ�� */
    PGA_init();		
    DAC_init();	
	  CMP_init();	
	  HALL_init();
    GPIO_init();                      /* GPIO��ʼ�� */
    MCPWM_init();                     /* PWM��ʼ�� */
	  ADC_init();                      /* ADC1��ʼ�� */

    Soft_Delay(100);                  /* ��ʱ�ȴ�Ӳ����ʼ���ȶ� */

	NVIC_SetPriority(ADC0_IRQn, 3);
    NVIC_EnableIRQ(ADC0_IRQn);
	
	NVIC_SetPriority(ADC1_IRQn, 2);
    NVIC_EnableIRQ(ADC1_IRQn);	
	
	NVIC_SetPriority(MCPWM0_IRQn, 0);
	NVIC_EnableIRQ(MCPWM0_IRQn);
	
	NVIC_SetPriority(TIMER0_IRQn, 4);
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	NVIC_SetPriority(CMP_IRQn, 1);
	NVIC_EnableIRQ(CMP_IRQn);	
	
    SEGGER_RTT_ConfigUpBuffer(1, "JScope_i2u2", bRttBuf, 2048, SEGGER_RTT_MODE_NO_BLOCK_SKIP);	

    __enable_irq();                   /* �������ж� */
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
    GPIO_StructInit(&GPIO_InitStruct);

    /* MCPWM P1.4~P1.9 */
	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);
	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    /* P2.6 ��Դ���� */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
	
    /* P2.10 �������ת���� */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;  //����ģʽ
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;  //Ĭ������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
//		GPIO_SetBits(GPIO2,GPIO_Pin_10); 

    /* P0.15 LED������ʾ�� */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
	GPIO_SetBits(GPIO0,GPIO_Pin_15);  //P0.15����ߵ�ƽ��LED����
//		GPIO_ResetBits(GPIO0,GPIO_Pin_15);  //P0.15����͵�ƽ
    LED_ON();

    /* P2.4 OC��Ϊ���裬��ʱû�õ� */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;   //����
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIO2, &GPIO_InitStruct);


//////		/* P1.0 LED״̬��ʾ��  ��IO�ڳ�ʼ���ᵼ��MCU���� */	
//////		/* MCU�������ͨ�� JLINK �ĸ�λ�Ž��� */
//////		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//////    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//////    GPIO_Init(GPIO0, &GPIO_InitStruct);
//////	  GPIO_SetBits(GPIO1,GPIO_Pin_0);   //P1.0����ߵ�ƽ��LED����

//    /* P3.5 ��FG��� */	
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
//    GPIO_Init(GPIO0, &GPIO_InitStruct);
//	GPIO_SetBits(GPIO3,GPIO_Pin_5); 
//		
//		/* P3.7 �� STATE�쳣״̬��� */
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
//    GPIO_Init(GPIO0, &GPIO_InitStruct);
//	GPIO_SetBits(GPIO3,GPIO_Pin_7); 

   /* P0.14��PWM_IN PWM�ź�����/(��ʱ����ΪFG���)*/	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
//	GPIO_SetBits(GPIO0,GPIO_Pin_14);
	GPIO_ResetBits(GPIO0,GPIO_Pin_14); 
//    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF8_TIMER23);	

    /* P0.6 �� UART_RX */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF4_UART);
		
    /* P0.7 �� UART_TX */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF4_UART);		

		
		
    LOCK_POWER_ON();  //�򿪵�Դ
//	  LOCK_POWER_OFF(); 
//	GPIO0_PDO &= ~BIT6;
		
	  
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
void ADC_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    		
	ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.IE         = ADC_SF1_IE;          // �ж�ʹ��
    ADC_InitStructure.RE         = 0;                   // DMA����ʹ��
    ADC_InitStructure.NSMP        = DISABLE;             // ���β���ʹ��
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT�Ҷ���ʹ��
    ADC_InitStructure.CSMP       = DISABLE;             // ��������ʹ��
    ADC_InitStructure.TCNT       = 0;                   // ����һ�β���������¼���
    ADC_InitStructure.TROVS      = DISABLE;             // �ֶ�����������ʹ�ܣ�������һ�β�����Ҫ��δ���
    ADC_InitStructure.OVSR       = 0;                   // ��������
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T1;  // �����ź�
    ADC_InitStructure.S1         = 3;                   // ��һ�γ����������
    ADC_InitStructure.S2         = 1;                   // �ڶ��γ����������
    ADC_InitStructure.IS1        = 1;                   // ���в�������
    ADC_InitStructure.LTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.HTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.GEN        = 0;                   // ADC ģ�⿴�Ź� 0 ��Ӧʹ��λ
    ADC_Init(ADC0, &ADC_InitStructure);		
    ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);

	ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.IE         = ADC_SF1_IE;          // �ж�ʹ��
    ADC_InitStructure.RE         = 0;                   // DMA����ʹ��
    ADC_InitStructure.NSMP        = DISABLE;             // ���β���ʹ��
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT�Ҷ���ʹ��
    ADC_InitStructure.CSMP       = DISABLE;             // ��������ʹ��
    ADC_InitStructure.TCNT       = 0;                   // ����һ�β���������¼���
    ADC_InitStructure.TROVS      = DISABLE;             // �ֶ�����������ʹ�ܣ�������һ�β�����Ҫ��δ���
    ADC_InitStructure.OVSR       = 0;                   // ��������
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // �����ź�
    ADC_InitStructure.S1         = 4;                   // ��һ�γ����������
    ADC_InitStructure.S2         = 2;                   // �ڶ��γ����������
    ADC_InitStructure.IS1        = 1;                   // ���в�������
    ADC_InitStructure.LTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.HTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.GEN        = 0;                   // ADC ģ�⿴�Ź� 0 ��Ӧʹ��λ
    ADC_Init(ADC1, &ADC_InitStructure);		
    ADC_ClearIRQFlag(ADC1, ADC_ALL_IF);	
	
    ADC_CHN_GAIN_CFG(ADC0,CHN0,ADC_BUS_VOL_CHANNEL,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0,CHN1,ADC_OPA_OUT_CHANNEL,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0,CHN2,ADC_SPEED_CHANNEL,ADC_GAIN3V6);		
		
    ADC_CHN_GAIN_CFG(ADC1,CHN0,BEMF_CH_A,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1,CHN1,BEMF_CH_B,ADC_GAIN3V6);
	ADC_CHN_GAIN_CFG(ADC1,CHN2,BEMF_CH_C,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1,CHN3,ADC_PEAK_CUR_CHANNEL,ADC_GAIN3V6);
	
}


void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;
    MCPWM_StructInit(&MCPWM_InitStructure);
    
	MCPWM_InitStructure.MCLK_EN = ENABLE;              /* ģ��ʱ�ӿ��� */
    MCPWM_InitStructure.CLK_DIV = 0;                   /* MCPWMʱ�ӷ�Ƶ���� */
	
    MCPWM_InitStructure.IO_CMP_FLT_CLKDIV  = 6;  /* ��ͣ�¼�(����IO���ź�)�����˲���ʱ������ */ 	
//	MCPWM_InitStructure.AUEN = MCPWM0_ALL_AUPDAT;     /*�Զ�����ʹ��*/
	  
	/* MCPWM0_CNT0 */	  
    MCPWM_InitStructure.BASE_CNT0_EN = ENABLE;                /* ����������ʼ����ʹ�ܿ��� */
	MCPWM_InitStructure.TH0 = PWM_PERIOD;                    /* �����������ü�MCPWM�������*/
		
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0����ģʽ�����Ķ���PWMģʽ */
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* ͨ������ģʽ���ã����Ķ������ض��� */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
	
    MCPWM_InitStructure.DeadTimeCH012N = DEADTIME;/* ����ʱ������ */
    MCPWM_InitStructure.DeadTimeCH012P = DEADTIME;
	
    MCPWM_InitStructure.CMP_CTRL_CNT0  = DISABLE ;/* CMP����CNT0ʹ�� */
	MCPWM_InitStructure.EVT_CNT0_EN    = DISABLE ;/* MCPWM_CNT1�ⲿ����ʹ�� */
	MCPWM_InitStructure.EVT0           = DISABLE ;
	
	MCPWM_InitStructure.TR0_UP_INTV     = DISABLE;
	MCPWM_InitStructure.TR0_T0_UpdateEN = ENABLE ;
	MCPWM_InitStructure.TR0_T1_UpdateEN = DISABLE ;
    MCPWM_InitStructure.TR0_AEC         = DISABLE;
		
    MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0�����¼� �жϹر� */
	MCPWM_InitStructure.T1_Update0_INT_EN = DISABLE ; /* T1�����¼� �ж�ʹ�� */
	MCPWM_InitStructure.Update1_INT_EN = DISABLE;       /* CNT0 �����¼� �ж�ʹ��  */
		
#if (CNT0_PRE_DRIVER_POLARITY == P_HIGH__N_LOW)                    /* CHxP ����Ч�� CHxN�͵�ƽ��Ч */
    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;           /* CH0Nͨ������������� | ���������ȡ�����*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0Pͨ������������� | ���������ȡ����� */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* ͨ������ѡ������ */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* ͨ������ѡ������ */

    /* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM0_IO01��MCPWM0_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
                                                     ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_HIGH_LEVEL;     /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_HIGH_LEVEL;
#endif
#if (CNT0_PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP ����Ч�� CHxN�ߵ�ƽ��Ч */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;           /* CH0Nͨ������������� | ���������ȡ�����*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0Pͨ������������� | ���������ȡ����� */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* ͨ������ѡ������ */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* ͨ������ѡ������ */

    /* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM0_IO01��MCPWM0_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
                                                     ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_LOW_LEVEL;     /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_LOW_LEVEL;
#endif


#if(MCPWM_SWAP_SETTING == 1)   
  PWM_SWAP = 0x67;
#endif

    MCPWM_InitStructure.CH0N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH0P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2P_FAIL_EN = ENABLE ;
		
    MCPWM_InitStructure.FAIL0_INPUT_EN   = DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_INT_EN     = DISABLE;
	MCPWM_InitStructure.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_Polarity   = MCPWM0_HIGH_LEVEL_ACTIVE ;

		
	MCPWM_InitStructure.FAIL1_INPUT_EN   = ENABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL1_INT_EN     = ENABLE;
	MCPWM_InitStructure.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL1_Polarity   = MCPWM0_HIGH_LEVEL_ACTIVE ;
		
	MCPWM_InitStructure.HALT_PRT0        = DISABLE ;
	MCPWM_InitStructure.FAIL_0CAP        = DISABLE ;
				
    MCPWM_InitStructure.TMR0 = 0;   /* MCPWM0_TMR0  ���� */
    MCPWM_InitStructure.TMR1 = 0;   /* MCPWM0_TMR1  ���� */
	MCPWM_InitStructure.TMR2 = 0;   /* MCPWM0_TMR2  ���� */
    MCPWM_InitStructure.TMR3 = 0;   /* MCPWM0_TMR3  ���� */ 
	
	MCPWM_InitStructure.TMR2_TB        = 0;/* MCPWM TMR2ʱ������������ѡ�� 0��ʱ��0��1��ʱ��1 */
	MCPWM_InitStructure.TMR3_TB        = 1;/* MCPWM TMR3ʱ������������ѡ�� 0��ʱ��0��1��ʱ��1 */

    MCPWM_Init(&MCPWM_InitStructure);
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
 2023/3/2      V1.0          HuangMG            ����
 *******************************************************************************/
void Timer0_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;
	
	TIM_InitStruct.Timer_CH0_WorkMode = 0; /* ����Timer CH0 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH0Output = 0;    /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_CH1_WorkMode = 0; /* ����Timer CH1 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH1Output = 0;    /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_TH = 48000;       /* ��ʱ���������޳�ʼֵ48000*/
    TIM_InitStruct.Timer_CMP0 = 250;  	   /* ���ñȽ�ģʽ��CH0�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_CMP1 = 250;  		/* ���ñȽ�ģʽ��CH1�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_FLT = 0;  			/* ���ò�׽ģʽ�������ģʽ�¶�Ӧͨ���������˲�ֵ */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;  /* ����Timerģ��ʱ��2��Ƶϵ�� */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_ZC;   /* ����Timerģ��Ƚ��жϺ͹����ж�*/
    TIM_TimerInit(UTIMER0, &TIM_InitStruct); 


	TIM_InitStruct.Timer_CH0_WorkMode = 0; /* ����Timer CH0 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH0Output = 0;     /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_CH1_WorkMode = 0; /* ����Timer CH1 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH1Output = 0;     /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_TH = 96000000;    	/* ��ʱ���������޳�ʼֵ48000*/
    TIM_InitStruct.Timer_CMP0 = 250;  		/* ���ñȽ�ģʽ��CH0�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_CMP1 = 250;  		/* ���ñȽ�ģʽ��CH1�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_FLT = 0;  			/* ���ò�׽ģʽ�������ģʽ�¶�Ӧͨ���������˲�ֵ */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;     /* ����Timerģ��ʱ��2��Ƶϵ�� */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_None;    /* ����Timerģ��Ƚ��жϺ͹����ж�*/
    TIM_TimerInit(UTIMER2, &TIM_InitStruct); 	
	
    TIM_TimerCmd(UTIMER0, ENABLE);      /* Timer0 ģ��ʹ�� */	
    TIM_TimerCmd(UTIMER2, ENABLE);      /* Timer2 ģ��ʹ�� */
	
}

/*******************************************************************************
 �������ƣ�    void DAC_Init(void)
 ����������    DAC��ʼ��(ͨ������ͬʱ��� DAC0 �� DAC1����������źž�����)
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          ����
 *******************************************************************************/
volatile u16 DAC_Range_Vol,DAC_Short_Value;
void DAC_init(void)
{	
	DAC_InitTypeDef DAC_InitStre;
    DAC_StructInit(&DAC_InitStre);                /* DAC�ṹ���ʼ�� */

	DAC_InitStre.DAC_GAIN = DAC_RANGE_4V85;      /*DAC�������Ϊ4.85V*/
	DAC_InitStre.DACOUT_EN = DISABLE;				/*ʹ��DAC�����P0.0*/
	DAC_InitStre.TIG_CH_EN = DISABLE; 		    /*ʹ��UTIMER����*/
	DAC_InitStre.DAC_STEP = 0;				    /*����ֵΪ0*/
	DAC_Init(DAC_Channel_0,&DAC_InitStre);       /* DAC��ʼ�� */
	
	DAC_Cmd(DAC_Channel_0,ENABLE);				/*ʹ��DACʱ��*/
	
	if(DAC_InitStre.DAC_GAIN == DAC_RANGE_4V85)
	{
	  DAC_Range_Vol = 48500;
	}
	else
	{
	  DAC_Range_Vol = 12000;
	}
	
	DAC_Short_Value = (mBLDC_CtrProc.NVR_OPAx_Vol + SHORT_CURRENT_VOL/2)*4096/DAC_Range_Vol;   //SHORT_CURRENT_VOL = 28795 
	
	DAC_OutputValue(DAC_Channel_0,DAC_Short_Value);
}
/*******************************************************************************
 �������ƣ�    void CMP_init(void)
 ����������    CMP��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          ����
 *******************************************************************************/
void CMP_init(void)
{	
	CMP_InitTypeDef CMP_InitStre;
	CMP_StructInit(&CMP_InitStre);
	
	CMP_InitStre.CLK_COM_DIV = 0;									/* �Ƚ��������˲�ʱ�ӷ�Ƶ*/
	CMP_InitStre.FT = DISABLE;										/* �Ƚ������ٱȽ�*/
	CMP_InitStre.HYS = CMP_HYS_0mV;							   /* �Ƚ����ͻص�ѹ*/
	
	CMP_InitStre.CMP0.SELP = CMP0_SELP_IP1; 		       /* �Ƚ���0�����ź�ѡ�� */
	CMP_InitStre.CMP0.SELN = CMP0_SELN_HALL0_MID; 				/* �Ƚ���0�����ź�ѡ�� */
	CMP_InitStre.CMP0.RE = DISABLE;								/* �Ƚ���0DMAʧ��*/
	CMP_InitStre.CMP0.POL= CMP_HIGH_LEVEL;				/* �Ƚ���0�ߵ�ƽ�����Ч*/
	CMP_InitStre.CMP0.IRQ_TRIG = IRQ_LEVEL_TRIG_MODE; /* �Ƚ���0��ƽ�����ж�ģʽ*/
	CMP_InitStre.CMP0.IN_EN = ENABLE; 			 			/* �Ƚ���0�ź�����ʹ�� */
	CMP_InitStre.CMP0.IE = DISABLE;  							/* �Ƚ���0�ź��ж�ʹ�� */
	CMP_InitStre.CMP0.FIL_CLK_DIV16 = 2; 					/* ���˲����=tclk ����*16*CMP_FltCnt (CMP_FltCnt��Ƶϵ��,0~15)*/
	CMP_InitStre.CMP0.FIL_CLK_DIV2 = 2;  					/* �Ƚ��� 2/1/0 �˲�ʱ��ʹ�� */
	CMP_InitStre.CMP0.CLK_EN = ENABLE;						/* �Ƚ���ʱ��ʹ��*/
	CMP_InitStre.CMP0.EN = ENABLE;       				  /* �Ƚ���0���� ����SYS_AFE_REG5 */
	
	CMP_InitStre.CMP1.SELP = CMP1_SELP_OPA3_OUT; 		       /* �Ƚ���0�����ź�ѡ�� */
	CMP_InitStre.CMP1.SELN = CMP_SELN_DAC0; 				/* �Ƚ���0�����ź�ѡ�� */
	CMP_InitStre.CMP1.RE = DISABLE;								/* �Ƚ���0DMAʧ��*/
	CMP_InitStre.CMP1.POL= CMP_HIGH_LEVEL;				/* �Ƚ���0�ߵ�ƽ�����Ч*/
	CMP_InitStre.CMP1.IRQ_TRIG = IRQ_LEVEL_TRIG_MODE; /* �Ƚ���0��ƽ�����ж�ģʽ*/
	CMP_InitStre.CMP1.IN_EN = ENABLE; 			 			/* �Ƚ���0�ź�����ʹ�� */
	CMP_InitStre.CMP1.IE = DISABLE;  							/* �Ƚ���0�ź��ж�ʹ�� */
	CMP_InitStre.CMP1.FIL_CLK_DIV16 = 4; 					/* ���˲����=tclk ����*16*CMP_FltCnt (CMP_FltCnt��Ƶϵ��,0~15)*/
	CMP_InitStre.CMP1.FIL_CLK_DIV2 = 0;  					/* �Ƚ��� 2/1/0 �˲�ʱ��ʹ�� */
	CMP_InitStre.CMP1.CLK_EN = ENABLE;						/* �Ƚ���ʱ��ʹ��*/
	CMP_InitStre.CMP1.EN = ENABLE;       				  /* �Ƚ���0���� ����SYS_AFE_REG5 */	
	
	CMP_Init(&CMP_InitStre);										/* �Ƚ�����ʼ�� */
	
	
	SYS_ModuleClockCmd(SYS_Module_CMP,ENABLE);
	
	CMP_Cmd(CMP_CHN_0,ENABLE);/* �Ƚ���0ʱ��ʹ��*/
	CMP_Cmd(CMP_CHN_1,ENABLE);/* �Ƚ���0ʱ��ʹ��*/
}

/*******************************************************************************
 �������ƣ�    void PGA_init(void)
 ����������    PGA��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����

OPA0����ģ��ѹ������10000 �������    0x000014C0
OPA1����ģ��ѹ������10000 �������    0x000014C4
OPA2����ģ��ѹ������10000 �������    0x000014C8
OPA3����ģ��ѹ������10000 �������    0x000014CC
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          ����
 *******************************************************************************/
void PGA_init(void)
{	
	OPA_InitTypeDef OPA_InitStruct;
	OPA_StructInit(&OPA_InitStruct);

	OPA_InitStruct.OPA_IT = PGA_IT_DISABLE;  /*opaƫ�õ������ڽ�ֹ*/
	OPA_InitStruct.OPA_CLEna = ENABLE;       /*ʹ��*/
	OPA_InitStruct.OPA_Gain = PGA_GAIN_32;   /*��������320k:10k*/
	OPA_Init(OPA3 ,&OPA_InitStruct);
		
    OPA_OUT(OPA3 , ENABLE);                 /*OPA3�ź������P2.7��*/
	
	mBLDC_CtrProc.NVR_OPAx_Vol = Read_Trim(0x000014CC); 
}

/*******************************************************************************
 �������ƣ�    void HALL_init(void)
 ����������    HALL��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          ����
 *******************************************************************************/
void HALL_init(void)
{	
	HALL_InitTypeDef HALL_InitStruct;
   
    HALL_StructInit(&HALL_InitStruct);
	
    HALL_InitStruct.FilterLen = 512;                /* Hall�ź������˲����� 512��ʱ������ */
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1;  /* ����Hallģ��ʱ�ӷ�Ƶϵ�� */
    HALL_InitStruct.Filter75_Ena = DISABLE;         /* Hall�ź��˲���ʽ��7��5ģʽ����ȫ1��Чģʽ */
    HALL_InitStruct.HALL_Ena = ENABLE;              /* ģ��ʹ�� */
    HALL_InitStruct.Capture_IRQ_Ena = DISABLE;       /* ��׽�ж�ʹ�� */
    HALL_InitStruct.OverFlow_IRQ_Ena = DISABLE;      /* ��ʱ�ж�ʹ�� */
    HALL_InitStruct.CountTH = 0xFFFFFFFF;              /* Hallģ�����ģֵ����������ģֵ�������ʱ�ж� */
	HALL_InitStruct.softIE = DISABLE;								 /* ����ж�ʧ�� */
	
    HALL_Init(&HALL_InitStruct);/* HALL���� */
	HALL_Cmd(ENABLE);/* HALLʹ�� */
}


/*******************************************************************************
 �������ƣ�    void SoftDelay(void)
 ����������    �����ʱ����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Soft_Delay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}





///*******************************************************************************
// �������ƣ�    void Reg_Clr(void)
// ����������    �Ĵ�������
// ���������    addr ����Ҫ����Ĵ�������ʼ��ַ 
//               nSize����Ҫ����ļĴ�������
// ���������    ��
// �� �� ֵ��    ��
// ����˵����
// �޸�����      �汾��          �޸���            �޸�����
// -----------------------------------------------------------------------------
// 2021/3/14      V1.0           Howlet Li          ����
// *******************************************************************************/
//void Reg_Clr(u32 addr, u8 nSize)
//{
//   while(nSize --)
//   {
//      REG32(addr) = 0;
//      addr += 4;
//   }
//}


