/*
 * mygpio_init.c
 *---------------------------------------------------------------------------
 * ���ܣ�
 *   1. �� P0.6 / P0.7 ����Ϊ UTIMER1_CH0 / CH1 ����ڣ������������� LED��

 *---------------------------------------------------------------------------
 * �ؼ����
 *   ? GPIO_PinAFConfig() �˿ڸ���
 *   ? ��· LED �����Ϲ���ͬһ������������������λ��
 *---------------------------------------------------------------------------
 */
#include "lks32mc08x_lib.h"

void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;  // ���� GPIO ���ýṹ��
    GPIO_StructInit(&GPIO_InitStruct); // ���㲢дĬ��ֵ

    /* ��ѡ���� GPIO ���������ʽ���� LED�����ڴ˽⿪ע�� */
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // ��ͨ���
    // GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    // GPIO_Init(GPIO0, &GPIO_InitStruct);

    //    GPIO_StructInit(&GPIO_InitStruct);                  // �ٴ����㣬׼�� AF ��������
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;          // �����Ȱ�ģʽ��Ϊ OUT/AF
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // ֻ�� 0.6 / 0.7
    GPIO_Init(GPIO0, &GPIO_InitStruct);                 // д��Ĵ���

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF7_TIMER01); // P0.6 ���õ� TIM1_CH0
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF7_TIMER01); // P0.7 ���õ� TIM1_CH1
}
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); // ��ȡ��ǰ�����ƽ
    if (reg)
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin); // ���Ϊ�ߣ�������
        return 0;                        // ���ط�ת��ĵ�ƽ
    }
    else
    {
        GPIO_SetBits(GPIOx, GPIO_Pin); // ���Ϊ�ͣ�������
        return 1;                      // ���ط�ת��ĵ�ƽ
    }
}