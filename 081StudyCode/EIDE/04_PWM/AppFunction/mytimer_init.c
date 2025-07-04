/*
 * mytimer_init.c
 *---------------------------------------------------------------------------
 * ���ܣ�
 *   ? �� UTIMER1 ���бȽ�ģʽ��ʼ����Ϊ˫·������׼���̶�Ƶ�� (��400 Hz) �� PWM �ز���
 *   ? �ⲿ��ͨ�� set_cmp() ��̬���� CMPT �Ĵ�����ʵ��ռ�ձȱ仯��
 *---------------------------------------------------------------------------
 * �����Ƶ���
 *   f_src  = 96 MHz   ��ClockDiv = 8 �� f_cnt = 12 MHz
 *   TH     = 29 999   �� f_PWM = 12 MHz / 30 000 �� 400 Hz
 *   MIN_D  =  2 400   (8 % �������)
 *---------------------------------------------------------------------------
 */
#include "lks32mc08x_lib.h" // ������Ÿ�ٷ��ײ�⣬�����Ĵ�������������

/*
 * ������ֻ�ȽϼĴ��������߲���ռ 32 bit ��ַ��ȣ�
 * �����������ֲ���� 16 bit (bit0-15) ��Ч�����ڴ�űȽ�ֵ��
 * д�� 0-0xFFFF ֮���κ���ֵ�԰�ȫ������ 29999 (0x752F) �ᱻ����� 16 λ��
 * �� 16 λд��� 0 ��Ӳ���������޸����á�
 * ��������԰� 32-bit ָ�붨�壬��֤������ʹ�� word ָ��������衣
 */

/*
 * ���⣺��д��ֵ >0xFFFF��Ӳ��ֻ��ȡ�� 16 λ�������������� 32 bit��
 * �������ᱨ������󣬴����޷�ͨ�����룬��˲�����������"д���Ĵ�����Խ��"��
 */
#define UNT1_CMP0 (*(volatile uint32_t *)0x4001182C) // TIMER1_CH0 �ȽϼĴ��� (�� 16 λ��Ч)
#define UNT1_CMP1 (*(volatile uint32_t *)0x40011830) // TIMER1_CH1 �ȽϼĴ��� (�� 16 λ��Ч)
#define TH_VALUE 29999                               // PWM �������� (��400 Hz)

void set_cmp(uint16_t value) // ��̬�޸���·�ȽϼĴ���
{
    UNT1_CMP0 = value; // д�� CH0 �� LED1 ռ�ձ�
    UNT1_CMP1 = value; // д�� CH1 �� LED2 ռ�ձ�
}
int getTh_Value()
{
    return TH_VALUE; // ���ص�ǰ���õ� TH�������ⲿ����ռ�ձ�
}
void Timer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;                   // �����������ʼ������
    TIM_TimerStrutInit(&TIM_InitStruct);                   // �ṹ���ֶ����㲢��Ĭ��ֵ
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP;  // CH0 ��Ϊ�Ƚ�ģʽ
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None; // CH0 ��������
    TIM_InitStruct.Timer_CH0Output = 1;                    // CNT=0 ʱ����ߵ�ƽ��LED �ߵ�ƽ����
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP;  // CH1 ͬ��
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None; // CH1 ��������
    TIM_InitStruct.Timer_CH1Output = 1;                    // CH1 ��ʼ����ߵ�ƽ
    TIM_InitStruct.Timer_TH = TH_VALUE;                    // �趨���ڼ�������
    TIM_InitStruct.Timer_CMP0 = 0;                         // ��ʼռ�ձ� 0 % �� �
    TIM_InitStruct.Timer_CMP1 = 0;                         // ͬ�� CH1
    TIM_InitStruct.Timer_Filter0 = 0;                      // �����˲��ر�
    TIM_InitStruct.Timer_Filter1 = 0;                      // �����˲��ر�
    TIM_InitStruct.Timer_ClockDiv = ECD_Clk_Div8;          // 96 MHz��8 �� 12 MHz ����ʱ��
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_Zero;       // ��ʹ�ܹ����ж�
    TIM_TimerInit(TIMER1, &TIM_InitStruct);                // ������д�� TIMER1 �Ĵ���
    TIM_TimerCmd(TIMER1, ENABLE);                          // ʹ�� TIMER1 ��ʼ����
}
