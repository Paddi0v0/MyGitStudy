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
#include "hardware_init.h"
#include "basic.h"
#include "hardware_config.h"
#include "lks32mc08x_gpio.h"
#include "lks32mc08x_lib.h"

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

    GPIO_init();
    DAC_init();     /* DAC��ʼ�� */
    PGA_init();     /* PGA��ʼ�� */
    SoftDelay(100); /* �ȴ�Ӳ����ʼ�����*/

    SYS_WR_PROTECT = 0x0; /*�ر�ϵͳ�Ĵ���д����*/
#if POWER_MODE
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0); /*MCU��Դ�ж�ʹ�ܺ���*/
#else
    SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3); /*MCU��Դ�ж�ʹ�ܺ���*/
#endif
    __enable_irq(); /* �����ж� */
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
 2023/10/23      V2.0         HuangMG        ����MCU��Դ��⹦��
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83; /* ���ϵͳ�Ĵ���д���� */
    SYS_AFE_REG5 |= BIT15;   /* BIT15:PLLPDN */
#if POWER_MODE
    SYS_VolSelModule(MCU_POWER_5v0); /* MCU�����ѹ��1��5V��0;3.3V*/
#else
    SYS_VolSelModule(MCU_POWER_3v3); /* MCU�����ѹ��1��5V��0;3.3V*/
#endif
    SoftDelay(100);          /* �ȴ�PLL�ȶ�*/
    SYS_WR_PROTECT = 0x7a83; /* ���ϵͳ�Ĵ���д���� */

    SYS_CLK_CFG = 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff��Ӧ96Mʱ�� */
    SYS_WR_PROTECT = 0x0;     /*�ر�ϵͳ�Ĵ���д����*/
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
void DAC_init(void)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC, ENABLE);
    SYS_WR_PROTECT = 0x7a83; /* ���ϵͳ�Ĵ���д���� */

    SYS_AFE_REG1 &= ~((u32)0x03 << 6);
    SYS_AFE_REG1 |= (DAC_RANGE_1V2 << 6); /* ����DAC������Ϊ1.2V��00:3V| 01:1.2V| 10:4.85V */

    if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_1V2)
    { /* ����DAC 1.2V����У��ֵ */
        SYS_AFE_DAC_DC = Read_Trim(0x00000344);
        SYS_AFE_DAC_AMC = Read_Trim(0x00000334);
    }
    else if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_3V0)
    { /* ����DAC 3.0V����У��ֵ */
        SYS_AFE_DAC_DC = Read_Trim(0x00000340);
        SYS_AFE_DAC_AMC = Read_Trim(0x00000330);
    }
    else if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_4V85)
    { /* ����DAC 4.85V����У��ֵ */
        SYS_AFE_DAC_DC = Read_Trim(0x00000348);
        SYS_AFE_DAC_AMC = Read_Trim(0x00000338);
    }
    SYS_AFE_REG3 |= BIT11; /*ʹ��DAC�����P0.0 IO��*/
    SYS_AFE_DAC = 2731;    /*DAC�����ѹΪ��2731*1.2V��/4096 = 0.8V*/
    SYS_WR_PROTECT = 0x0;  /*�ر�ϵͳ�Ĵ���д����*/
}

void GPIO_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_ANA;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStructure);
}

void PGA_init(void)
{
    OPA_InitTypeDef OPA_InitStruct;
    OPA_StructInit(&OPA_InitStruct);

    OPA_InitStruct.OPA_CLEna = ENABLE;
    OPA_InitStruct.OPA_Gain = PGA_GAIN_9P5;
    OPA_Init(OPA0, &OPA_InitStruct);

    OPA_OUT(OPA0, ENABLE); //OPA3�ź������P2.7��
}
/*******************************************************************************
 �������ƣ�    void SoftDelay(void)
 ����������    ����������
 ���������    mode:0,��֧��������;1,֧��������;
 ���������    ��
 �� �� ֵ��    0��û���κΰ�������
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/6/8      V1.0           HuangMG            ����
 *******************************************************************************/
int GPIO_KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //�������ɿ���־
    if (mode) key_up = 1; //֧������
    if (key_up && (key_start == 0 || key_stop == 0))
    {
        SoftDelay(10); //ȥ����
        key_up = 0;
        if (key_start == 0)
            return start_PRES;
        else if (key_stop == 0)
            return stop_PRES;
    }
    else if (key_start == 1 && key_stop == 1)
        key_up = 1;
    return 0; // �ް�������
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
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

/*******************************************************************************
 �������ƣ�    uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 ����������    GPIO��ƽ��ת����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             ����
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
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
