/*
 * hardware_init.c
 *---------------------------------------------------------------------------
 * ���ܸ�����
 *   ��ɱ�ʵ�������ȫ��оƬ����ʼ�����̣�������
 *     1. ȫ���ж�������ϵͳ�Ĵ���д����������
 *     2. FLASH Ԥȡ���ٴ򿪣�
 *     3. GPIO / UTimer �����ʼ�����ã�
 *     4. NVIC �ж����ȼ����ò�ʹ�� UTIMER1 �жϣ�
 *     5. (��ѡ) ��Դ��ѹ����жϴ򿪣�
 *     6. ��ϵͳʱ�ӽ��� PLL ���ã��� Clock_Init����
 *---------------------------------------------------------------------------
 * ���˼·��
 *   ? �ȹ��ж� �� �����ʼ�������б������жϴ�ϡ�
 *   ? ��ϵͳ�ؼ��Ĵ������������γ�ʼ�� GPIO �� Timer����֤���������ȶ�ʱ
 *     ��Դ�����á�
 *   ? ���мĴ�������/�������̶���ʽд�����������ά����
 *---------------------------------------------------------------------------
 */
#include "lks32mc08x_lib.h"

void Hardware_init(void)
{
    // Ĭ��д��
    __disable_irq();         /* �ر��ж� �ж��ܿ��� */
    SYS_WR_PROTECT = 0x7a83; /* ���ϵͳ�Ĵ���д���� */
    FLASH_CFG |= 0x00080000; /* �� FLASH Ԥȡ���� */

    GPIO_init();  /* ��ʼ�� GPIO (LED ���Ÿ���) */
    Timer_init(); /* ��ʼ�� UTimer1 (PWM �ز�) */

    SoftDelay(100); /* ������ʱ���ȴ������ȶ� */

    NVIC_SetPriority(TIMER1_IRQn, 0); /* ���� UTimer1 �ж����ȼ�Ϊ��� */
    NVIC_EnableIRQ(TIMER1_IRQn);      /* ʹ�� UTimer1 ZERO �ж� */

    SYS_WR_PROTECT = 0x0; /*�ر�ϵͳ�Ĵ���д����*/
#if POWER_MODE
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0); /*MCU��Դ�ж�ʹ�ܺ���*/
#else
    SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3); /*MCU��Դ�ж�ʹ�ܺ���*/
#endif
    __enable_irq(); /* ��ȫ���ж� */
}

void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83; /* �����Ĵ��������� PLL */
    SYS_AFE_REG5 |= BIT15;   /* ��� PLL �ϵ�λ����ʼ���� */
#if POWER_MODE
    SYS_VolSelModule(MCU_POWER_5v0);
#else
    SYS_VolSelModule(MCU_POWER_3v3);
#endif
    SoftDelay(100); /* �ȴ�PLL�ȶ����˲��������Զ�ʹ��д������ */

    /* ��Ҫ�ٴν���д����������ʱ�ӼĴ��� */
    SYS_WR_PROTECT = 0x7a83;  /* �ٴν���������д CLK_CFG */
    SYS_CLK_CFG = 0x000001ff; /* ѡ�� PLL�����÷�Ƶ=0xFF��96MHz */
    SYS_WR_PROTECT = 0x0;     /* �����Ĵ���������д */
}

void SystemInit(void)
{
    Clock_Init(); /* �������溯�����ϵͳʱ�ӳ�ʼ�� */
}

void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt; // volatile ��ֹ�������Ż�

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP(); // ռλ��ָ�����һ��ʱ������
    }
}
