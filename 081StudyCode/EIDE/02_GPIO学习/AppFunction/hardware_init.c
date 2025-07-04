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
#include "hardware_init.h"

/*******************************************************************************
 �������ƣ�    void Hardware_init(void)
 ����������    Ӳ�����ֳ�ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
    �ؼ���ʼ�����裨�����ŸLKS32MC08xоƬ�Ĺ̶�д������
      1. �ر����жϣ���ֹ��ʼ�����̱��жϴ��
      2. ����Ĵ���д������ʹ�ó��̶̹�����0x7a83����ϵͳ�Ĵ���
      3. ʹ��FLASHԤȡ�����ٴ���ִ�У�����Ƶ�±��뿪��
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();
    SYS_WR_PROTECT = 0x7a83;
    FLASH_CFG |= 0x00080000;

    // ֻ����P0.3���ų�ʼ��
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

    // ����P0.3Ϊ����͵�ƽ
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_ResetBits(GPIO0, GPIO_Pin_3); // ����͵�ƽ

    /* ע�͵���������Ҫ�������ʼ��
    SoftDelay(100);
    SYS_WR_PROTECT = 0x0;
    #if POWER_MODE
        SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);
    #else
        SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);
    #endif
    */
    __enable_irq();
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
    SoftDelay(100);           /* �ȴ�PLL�ȶ�*/
    SYS_WR_PROTECT = 0x7a83;  /* ���ϵͳ�Ĵ���д���� */
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
}

/*******************************************************************************
 �������ƣ�    int GPIO_KEY_Scan(u8 mode)
 ����������    ����������
 ���������    mode:0,��֧��������;1,֧��������;
 ���������    ��
 �� �� ֵ��    0��û���κΰ������£�1����ʼ�������£�2��ֹͣ��������
 ����˵����
    ʵ���߼���
      1. ���徲̬����key_up��¼�����ɿ�״̬��1Ϊ�ɿ���0Ϊ���£�
      2. ���mode=1��֧������������ÿ�ε��ö���key_up��1����֧��������⣩
      3. �����ǰ���������ɿ�״̬��key_up=1���Ҽ�⵽�а������£�key_start��key_stopΪ0��
          - ��ʱ������10����ѭ����
          - ����key_up=0����ʾ�����Ѱ��£�
          - �жϾ������ĸ��������£����ض�Ӧ�İ���ֵ��start_PRES��stop_PRES��
      4. �����⵽�����������ͷţ�key_start��key_stop��Ϊ1����������key_up=1����ǰ������ɿ���
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/6/8      V1.0           HuangMG            ����
 *******************************************************************************/
int GPIO_KEY_Scan(u8 mode)
{
    static u8 key_up = 1; // �����ɿ���־����̬����������״̬��
    if (mode) key_up = 1; // ���֧����������ÿ�ε��ö�����key_upΪ1��������������⣩

    if (key_up && (key_start == 0 || key_stop == 0)) // ������������ɿ�״̬���а���������
    {
        SoftDelay(10);          // ��ʱ10����ѭ����������
        key_up = 0;             // ��ǰ����Ѱ��£���ֹ�ظ�������
        if (key_start == 0)     // �ٴμ�⿪ʼ�����Ƿ��£�������ȷ�ϣ�
            return start_PRES;  // ���ؿ�ʼ�������µ�״ֵ̬
        else if (key_stop == 0) // ���ֹͣ�����Ƿ���
            return stop_PRES;   // ����ֹͣ�������µ�״ֵ̬
    }
    else if (key_start == 1 && key_stop == 1) // ������������������ͷ�״̬
        key_up = 1;                           // ��ǰ������ɿ��������´μ�⣩

    return 0; // �ް�������
}

/*******************************************************************************
 �������ƣ�    void SoftDelay(u32 cnt)
 ����������    �����ʱ����
 ���������    cnt - ��ʱѭ��������ֵԽ����ʱԽ����
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
    ʵ��ԭ��
      1. ʹ��volatile���μ�������������ֹ�������Ż���
      2. ͨ����ѭ������CPUʱ��ʵ����ʱ
      3. ÿ��ѭ��ִ��__NOP()ָ��޲���ָ�
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt; // volatile��ֹ�������Ż����������

    for (t_cnt = 0; t_cnt < cnt; t_cnt++) // ѭ��cnt��
    {
        __NOP(); // ִ���޲���ָ�����һ��ʱ�����ڣ�
    }
}

/*******************************************************************************
 �������ƣ�    uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 ����������    GPIO��ƽ��ת����
 ���������    
     - GPIOx: GPIO�˿ڣ���GPIO0��
     - GPIO_Pin: ���źţ���GPIO_Pin_6��
 ���������    ��
 �� �� ֵ��    ��ת������ŵ�ƽ״̬��0-�͵�ƽ��1-�ߵ�ƽ��
 ����˵����
    ʵ���߼���
      1. ��ȡ��ǰ���ŵ�ƽ״̬
      2. �����ǰΪ�ߵ�ƽ��������Ϊ�͵�ƽ
      3. �����ǰΪ�͵�ƽ��������Ϊ�ߵ�ƽ
      4. ���ط�ת��ĵ�ƽ״̬
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             ����
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg;
    reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); // ��ȡ��ǰ���ŵ�ƽ״̬
    if (reg)                                       // �����ǰ�Ǹߵ�ƽ
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin); // ����Ϊ�͵�ƽ
        return 0;                        // ���ص͵�ƽ״̬
    }
    else // �����ǰ�ǵ͵�ƽ
    {
        GPIO_SetBits(GPIOx, GPIO_Pin); // ����Ϊ�ߵ�ƽ
        return 1;                      // ���ظߵ�ƽ״̬
    }
}
