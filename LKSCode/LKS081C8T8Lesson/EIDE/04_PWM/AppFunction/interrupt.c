/******************************************************************************
 * �жϺ��������ܽ�����ļ�˳��
 *
 * | �жϺ���               | ��Ҫ����                     | �ؼ����� |
 * |------------------------|------------------------------|--------------------------|
 * | PWRDN_IRQHandler      | ��ԴǷѹ����                 | ���õ�Դ������ |
 * | ADC0_IRQHandler       | ADC0ת����ɴ���             | ���ADC�жϱ�־ | |
 *UART0_IRQHandler      | UART0ͨ�Ŵ����գ�          | �޲��� | |
 *MCPWM_IRQHandler      | �������PWM����              | ���MCPWM�жϱ�־ | |
 *HALL_IRQHandler       | ���������������գ�         | �޲��� | |
 *UTIMER0_IRQHandler    | ��ʱ��0�жϴ���              | �����ʱ���жϱ�־ | |
 *UTIMER1_IRQHandler    | ��ʱ��1�жϴ����գ�        | �޲��� | |
 *UTIMER2_IRQHandler    | ��ʱ��2�жϴ����գ�        | �޲��� | |
 *UTIMER3_IRQHandler    | ��ʱ��3�жϴ����գ�        | �޲��� | |
 *ENCODER0_IRQHandler   | ������0�����գ�            | �޲��� | |
 *ENCODER1_IRQHandler   | ������1�����գ�            | �޲��� | |
 *CMP_IRQHandler        | �Ƚ��������գ�             | �޲��� | |
 *UART1_IRQHandler      | UART1ͨ�Ŵ����գ�          | �޲��� | |
 *SysTick_Handler       | ϵͳ���Ķ�ʱ�������գ�     | �޲��� | |
 *SleepTimer_IRQHandler | ���߻��Ѵ���                 | ��ѭ�������޸ģ� | |
 *GPIO_IRQHandler       | GPIO�жϴ����գ�           | �޲��� | |
 *I2C0_IRQHandler       | I2C0ͨ�Ŵ����գ�           | �޲��� | |
 *SPI0_IRQHandler       | SPI0ͨ�Ŵ����գ�           | �޲��� |
 *
 * ˵����
 * 1. ��"���գ�"�ĺ�����Ҫ����ʵ�ʹ�����Ӵ���
 * 2. SleepTimer�е���ѭ����Ҫ�滻Ϊʵ�ʻ��Ѵ���
 * 3. ���Ӧ��ͨ��ֻ��SysTick��GPIO�ж�
 ******************************************************************************/
#include "lks32mc08x_lib.h"

/*
 * interrupt.c
 *---------------------------------------------------------------------------
 * ˵����
 *   ���ļ����з������������жϷ����� (ISR)��
 *   ���ڱ�ʵ�飬�� UTIMER1 ZERO �ж���������̬���� LED ռ�ձȣ�
 *   ���� ISR ��ǰΪ�գ�����������չ��
 *---------------------------------------------------------------------------
 * UTIMER1 �ж��߼��عˣ�
 *   ZERO �ж� �� ÿ�� PWM ���ڴ���һ�Ρ�
 *   1. ���ݷ��� dir(+1/-1) ������ݼ��Ƚ�ֵ cmp��
 *   2. ��Ԥ������(��92 %) ������(��8 %) ֮���۷��γ����ǲ���
 *   3. CH0 = cmp ��CH1 = TH - cmp + MIN �� ��· LED ����������
 *---------------------------------------------------------------------------
 */

// ��ԴǷѹ�жϴ���
void PWRDN_IRQHandler(void)
{
    /*
   * �����ԴǷѹ�¼�
   * SYS_VolSelModuleIRQ() �ǵ�Դ����ģ����жϴ�����
   * ���ܣ�
   * 1. ��⵱ǰ��Դ״̬��5V/3.3V��
   * 2. ִ����Ӧ�ĵ�Դ���ϴ���
   * 3. �����Դ�жϱ�־λ
   * 4. ���ܴ���ϵͳ��λ��͹���ģʽ
   */
    // SYS_VolSelModuleIRQ();
}

// ADC0�жϴ���
void ADC0_IRQHandler(void)
{
    /*
   * ���ADC0�жϱ�־λ
   * BIT1 | BIT0 ��ӦADC0���жϱ�־λ
   * ����˵����
   * 1. ADC0_IF ��ADC0�жϱ�־�Ĵ���
   * 2. BIT0 = 0x01 ��ʾת������жϱ�־
   * 3. BIT1 = 0x02 ��ʾת�������жϱ�־
   * 4. ͨ��д1�����־λ��д1���㣩
   */
    // ADC0_IF |= BIT1 | BIT0;
}

// UART0�жϴ����գ�
void UART0_IRQHandler(void)
{
    // Ԥ������ 0 �ж�
}

// MCPWM�жϴ���
void MCPWM_IRQHandler(void)
{
    /*
   * ���MCPWM�жϱ�־λ
   * BIT1 | BIT0 ��ӦMCPWM���жϱ�־λ
   * ����˵����
   * 1. MCPWM_IF �ǵ������PWM�жϱ�־�Ĵ���
   * 2. BIT0 = 0x01 ��ʾPWM���ڽ����ж�
   * 3. BIT1 = 0x02 ��ʾPWM���ϱ����ж�
   * 4. ֱ�Ӹ�ֵ�����־λ����ͬ��ADC��д1���㣩
   */
    // MCPWM_IF = BIT1 | BIT0;
}

// HALL�жϴ����գ�
void HALL_IRQHandler(void)
{
    // Ԥ�������������ж�
}

void UTIMER0_IRQHandler(void)
{
    // Ԥ��������ڶ�����ʱ������ֲ�˴�
}

// UTIMER1 ZERO �жϣ���ÿ�� PWM ���ڻ���ʱ���� CMPT0/1���������� LED �������
void UTIMER1_IRQHandler(void)
{
    if (TIM_GetIRQFlag(TIMER1, TIMER_IF_ZERO))
    {
        TIM_ClearIRQFlag(TIMER1, TIMER_IF_ZERO);

        static int32_t cmp = 0; // ��ǰ�Ƚ�ֵ (ռ�ձȡ�TH)
        static int8_t dir = +1; // +1: ����  -1: �䰵

        cmp += dir * 40; // ÿ�θı� 40/30000 �� 0.13 % ռ��
        if (cmp >= 30000)
        {
            cmp = 30000; // ���ޡ�92 %
            dir = -1;    // �۷���ʼ�䰵
        }
        else if (cmp <= 2400)
        { // ����  8 %
            cmp = 2400;
            dir = +1; // �۷���ʼ����
        }

        TIMER1->CMPT0 = (uint32_t)cmp;      // LED1
        TIMER1->CMPT1 = 30000 - cmp + 2400; // LED2 (����)
    }
}

// TIMER2�жϴ����գ�
void UTIMER2_IRQHandler(void)
{
    // Ԥ��
}

// TIMER3�жϴ����գ�
void UTIMER3_IRQHandler(void)
{
    // Ԥ��
}

// ENCODER0�жϴ����գ�
void ENCODER0_IRQHandler(void)
{
}

// ENCODER1�жϴ����գ�
void ENCODER1_IRQHandler(void)
{
}

// �Ƚ����жϴ����գ�
void CMP_IRQHandler(void)
{
}

// UART1�жϴ����գ�
void UART1_IRQHandler(void)
{
}

// ϵͳ�δ�ʱ�жϴ����գ�
void SysTick_Handler(void)
{
}

// ���߻����жϴ���
void SleepTimer_IRQHandler(void)
{
    /*
   * ���߻����жϴ���
   * ��ǰʵ��Ϊ��ѭ���������ʵ�������޸ģ�
   * ��ȷ������
   * 1. ������߶�ʱ���жϱ�־
   * 2. ִ��ϵͳ���ѳ�ʼ��
   * 3. �ָ�ϵͳʱ�Ӻ�����
   * 4. ����������ִ��
   *
   * ���棺��ǰ��ѭ���ᵼ��ϵͳ����
   * ��ʱ���������ڵ��Ի���������
   */
    /*
  while (1)
      ;
       */
}

// GPIO�жϴ����գ�
void GPIO_IRQHandler(void)
{
}

// I2C0�жϴ����գ�
void I2C0_IRQHandler(void)
{
}

// SPI0�жϴ����գ�
void SPI0_IRQHandler(void)
{
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR
 * **********************/
/* ------------------------------END OF FILE------------------------------------
 */
