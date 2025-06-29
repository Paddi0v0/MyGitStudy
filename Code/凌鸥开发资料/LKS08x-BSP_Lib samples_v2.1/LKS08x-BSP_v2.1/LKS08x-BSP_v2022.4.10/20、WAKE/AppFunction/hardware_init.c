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
 * �޸����ڣ� 2021��8��25��
 * �� �� �ţ�
 * �� �� �ˣ� HMG
 * �޸����ݣ�
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "global_variable.h"
#include "gpio_led.h"
#include "gpio_key.h"

void SoftDelay(u32 cnt);
void SYS_UtimerFallSleep(void);
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
	  delay_init(96);
	
    GPIO_init();             /* GPIO��ʼ�� */
	  NVIC_EnableIRQ(WAKE_IRQn); /* ��˯�߻����ж� */
    __enable_irq();          /* �������ж� */
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

    //���ð��� start��P2.11
    GPIO_StructInit(&GPIO_InitStruct);        //��ʼ���ṹ��
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO����ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    //���ð��� stop��P2.12
    GPIO_StructInit(&GPIO_InitStruct);        //��ʼ���ṹ��
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO����ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    //����LED1��P0.6
    GPIO_StructInit(&GPIO_InitStruct);         //��ʼ���ṹ��
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO���ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    //����LED2��P0.7
    GPIO_StructInit(&GPIO_InitStruct);         //��ʼ���ṹ��
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO���ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    //����LED3: P0.3
    GPIO_StructInit(&GPIO_InitStruct);         //��ʼ���ṹ��
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO���ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
		
		//�͹���IO���ѿ�
		GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //P0.0����ʹ��
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
		GPIO_Init(GPIO0, &GPIO_InitStruct);
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
	  SoftDelay(100);
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
 �������ƣ�    void SYS_SetWakeInter(uint32_t nInterval)
 ����������    �������߻�������
 �����ı�    ��
 ���������    000��0.125S 
							 001��0.25S
							 010��0.5S 
							 011��1S
							 100��2S 
							 101��4S   
							 110��8S 
							 111��16S
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2016/5/24      V1.0           HMG          ����
 *******************************************************************************/
void SYS_SetWakeInter(uint32_t nInterval)
{
	uint32_t tempReg = SYS_RST_CFG;
	SYS_WR_PROTECT = 0x7a83; /*�����Ĵ���дʹ��*/
	tempReg |= (nInterval << 2);
	SYS_RST_CFG = tempReg;
}

/*******************************************************************************
 �������ƣ�    void SYS_SetWakeIO(uint32_t nInterval)
 ����������    �������߻���IO
 �����ı�    ��
 ���������    1��nInterval = BIT3: GPIO 1[1] / P1[1] �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á�
							   nInterval = BIT2: GPIO 1[0] / P1[0] �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á�
							   nInterval = BIT1: GPIO 0[1] / P0[1] �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á�
							   nInterval = BIT0: GPIO 0[0] / P0[0] �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á�
					    2��ENABLE:IO�ߵ�ƽ����
						   	 DISABLE��IO�͵�ƽ����
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/4/14     V1.0           HuangMG            ����
 *******************************************************************************/
void SYS_SetWakeIO(uint32_t nInterval, u8 POL)
{
	SYS_WR_PROTECT = 0x7a83; /*�����Ĵ���дʹ��*/
	if (POL == ENABLE)
	{
		WAKE_PO = nInterval;
	}
	else
	{
		WAKE_PO &= ~nInterval;
	}
	 WAKE_EN = nInterval;
}


u32 AFE_REG5_RECORD = 0;
u32 AFE_REG6_RECORD = 0;
u32 CLK_CFG_RECORD = 0;
void Switch2PLL(void)
{
	  SYS_WR_PROTECT = 0x7a83; /*�����Ĵ���дʹ��*/
    SYS_AFE_REG5 = AFE_REG5_RECORD;
    SoftDelay(200);
	  SYS_AFE_REG6 = AFE_REG6_RECORD;
    SYS_CLK_CFG = CLK_CFG_RECORD;     // Switch main clock to PLL  clock
	  SYS_WR_PROTECT = 0x0;  /*�رռĴ���дʹ��*/
}

/*******************************************************************************
 �������ƣ�    void SYS_FallSleepMode(void)
 ����������    ����ϵͳ��������״̬
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2016/5/24      V1.0           cfwu          ����
 *******************************************************************************/
void SYS_FallSleepMode(void)
{
	SYS_WR_PROTECT = 0x7a83; /*�����Ĵ���дʹ��*/
	AFE_REG5_RECORD = SYS_AFE_REG5;
	AFE_REG6_RECORD = SYS_AFE_REG6;
	CLK_CFG_RECORD = SYS_CLK_CFG;
	SYS_AFE_REG5 = 0x0500;    // Prepare to shutdown PLL,HRC,BGP
  SYS_AFE_REG6|=1;          // Turn off power detection module in ANALOG
  SYS_CLK_CFG = 0;          // Switch to HRC clock
	SYS_CLK_SLP  = 0xDEAD;    // ��������ģʽ
	SYS_WR_PROTECT = 0x0; 
	__WFI();			   //PCָ��ֹͣ����
	SYS_UtimerFallSleep(); //��IO����ģʽ�У��ж���Utimer�����������������
	Switch2PLL();
}

extern void InversP_Test(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
extern u8 Utimer_flag;
/*******************************************************************************
 �������ƣ�    void SYS_UtimerFallSleep(void)
 ����������    ��������IO����ʱ���ж�ΪUtimer���ѣ���ִ�иú���������������
               �������Utimer���ѣ���IO����������������ִ��
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/9/6      V1.0             HMG               ����
 *******************************************************************************/
void SYS_UtimerFallSleep(void)
{
Sleep:
	if(Utimer_flag)				      /*�ж���Utimer�жϣ��������������*/
	{
		Utimer_flag = 0;	        /*Utimer���ѱ�־λ����*/
		SYS_WR_PROTECT = 0x7a83;  /*�����Ĵ���дʹ��*/
		SYS_CLK_SLP = 0xDEAD;     /*��������ģʽ*/
		__WFI();			            /*PCָ��ֹͣ����*/
		SYS_WR_PROTECT = 0x0; 
		goto Sleep;			          /*���ص�Sleep��*/
	}
	
}


/*******************************************************************************
 �������ƣ�    void Invers_GPIO(void)
 ����������    GPIO��ƽ��ת����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
                V1.0                                ����
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) //GPIO��ƽ��ת����
{
	u16 reg;
	reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); //��GPIO��ƽ
	if (reg)
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin);
		return 0;
	}
	else
	{
		GPIO_SetBits(GPIOx, GPIO_Pin);
		return 1;
	}
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
 2021/11/15      V1.0        mingganghuang          ����
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}


