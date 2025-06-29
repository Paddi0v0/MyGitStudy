/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc08x_gpio.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� GPIO������������ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016��6��19��     <td>1.0     <td>cfwu      <td>����
 * </table>
 */
#ifndef __LKS32MC08x_GPIO_H // ͷ�ļ������꣬��ֹ�ظ�����
#define __LKS32MC08x_GPIO_H // ����ͷ�ļ����ʶ

/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x.h" // ����оƬ����Ĵ�������
#include "basic.h"      // ���������������Ͷ���

/**
 *@brief GPIO�Ĵ����ṹ����
 * ����GPIO�Ĵ���ӳ��Ľṹ��
 */
typedef struct
{
    __IO uint32_t PIE;   /*!< ����ʹ�ܼĴ��������������Ƿ���Ϊ���� */
    __IO uint32_t POE;   /*!< ���ʹ�ܼĴ��������������Ƿ���Ϊ��� */
    __IO uint32_t PDI;   /*!< �������ݼĴ�������ȡ���ŵ�ǰ����״̬ */
    __IO uint32_t PDO;   /*!< ������ݼĴ������������������ƽ */
    __IO uint32_t PUE;   /*!< ����ʹ�ܼĴ����������Ƿ������ڲ��������� */
    __IO uint32_t PDE;   /*!< ���мĴ���������δʹ�� */
    __IO uint32_t PODE;  /*!< ��©ʹ�ܼĴ����������Ƿ����ÿ�©���ģʽ */
    __IO uint32_t LCKR;  /*!< ��������Ĵ���������GPIO���ò��������޸� */
    __IO uint32_t F3210; /*!< ����ѡ��Ĵ���������Pin0-Pin3�ĸ��ù��� */
    __IO uint32_t F7654; /*!< ����ѡ��Ĵ���������Pin4-Pin7�ĸ��ù��� */
    __IO uint32_t FBA98; /*!< ����ѡ��Ĵ���������Pin8-Pin11�ĸ��ù��� */
    __IO uint32_t FFEDC; /*!< ����ѡ��Ĵ���������Pin12-Pin15�ĸ��ù��� */
} GPIO_TypeDef;          // GPIO�Ĵ�����ṹ�嶨��

/**
 * GPIO0�ṹ�����ַ���壺��GPIO0_BASE��ַӳ�䵽GPIO_TypeDef�ṹ��
 */
#ifndef GPIO0
#define GPIO0 ((GPIO_TypeDef *)GPIO0_BASE)
#endif

/**
 * GPIO1�ṹ�����ַ����
 */
#ifndef GPIO1
#define GPIO1 ((GPIO_TypeDef *)GPIO1_BASE)
#endif

/**
 * GPIO2�ṹ�����ַ����
 */
#ifndef GPIO2
#define GPIO2 ((GPIO_TypeDef *)GPIO2_BASE)
#endif

/**
 * GPIO3�ṹ�����ַ����
 */
#ifndef GPIO3
#define GPIO3 ((GPIO_TypeDef *)GPIO3_BASE)
#endif

/**
 *@brief GPIOģʽѡ��ö��
 * ����GPIO����ģʽ��4������
 */
typedef enum {
    GPIO_Mode_IN  = 0x00, /*!< ����ģʽ��������Ϊ�������� */
    GPIO_Mode_OUT = 0x01, /*!< ���ģʽ��������Ϊ������� */
    GPIO_Mode_ANA = 0x02, /*!< ģ��ģʽ����������ģ������/�������������ֹ��ܣ� */
    GPIO_Mode_IO  = 0x03  /*!< ����ģʽ */
} GPIOMode_TypeDef;

/**
 *@brief GPIO����/��������ö��
 * ����GPIO����ģʽʱ�ĵ�������
 */
typedef enum {
    GPIO_PuPd_NOPULL = 0x00, /*!< ������/����������̬���� */
    GPIO_PuPd_UP     = 0x01, /*!< �������裺Ĭ�ϸߵ�ƽ */
} GPIOPuPd_TypeDef;

/**
 *@brief GPIOλ����ö��
 * �������õ������ŵĵ�ƽ״̬
 */
typedef enum {
    Bit_RESET = 0, // ��������Ϊ�͵�ƽ
    Bit_SET        // ��������Ϊ�ߵ�ƽ
} BitAction;

/**
 *@brief GPIO���ýṹ��
 * ���ڳ�ʼ��GPIO���ŵĲ�������
 */
typedef struct
{
    uint32_t GPIO_Pin;          /*!< Ҫ���õ����ţ�ʹ��GPIO_Pin_x�꣩ */
    GPIOMode_TypeDef GPIO_Mode; /*!< ���Ź���ģʽ������/���/ģ�� */
    GPIOPuPd_TypeDef GPIO_PuPd; /*!< �������ã�������/���� */
    uint32_t GPIO_PODEna;       /*!< ��©���ʹ�ܣ�0=���������1=��©��� */
} GPIO_InitTypeDef;

// GPIO���ù��ܶ��壨AF = Alternate Function��
#define AF0_GPIO    0  /*!< ����GPIO���� */
#define AF1_SYSAF   1  /*!< ϵͳ�����ù��ܣ�CMP/CLOCK�� */
#define AF2_HALL    2  /*!< HALL�������ӿڹ��� */
#define AF3_MCPWM   3  /*!< �������PWM���� */
#define AF4_UART    4  /*!< UART���ڹ��� */
#define AF5_SPI     5  /*!< SPI�ӿڹ��� */
#define AF6_I2C     6  /*!< I2C�ӿڹ��� */
#define AF7_TIMER01 7  /*!< ��ʱ��0/1���� */
#define AF8_TIMER23 8  /*!< ��ʱ��2/3���������ӿڹ��� */
#define AF9_DEBUG   9  /*!< ���Դ������� */
#define AF10_CAN    10 /*!< CAN���߹��� */
#define AF11_SIF    11 /*!< SIF�ӿڹ��� */

/* GPIO���Ŷ��壨λ������ʽ��*/
#define GPIO_Pin_NONE 0      /*!< ������ѡ�� */
#define GPIO_Pin_0    BIT0   /*!< ѡ������0 */
#define GPIO_Pin_1    BIT1   /*!< ѡ������1 */
#define GPIO_Pin_2    BIT2   /*!< ѡ������2 */
#define GPIO_Pin_3    BIT3   /*!< ѡ������3 */
#define GPIO_Pin_4    BIT4   /*!< ѡ������4 */
#define GPIO_Pin_5    BIT5   /*!< ѡ������5 */
#define GPIO_Pin_6    BIT6   /*!< ѡ������6 */
#define GPIO_Pin_7    BIT7   /*!< ѡ������7 */
#define GPIO_Pin_8    BIT8   /*!< ѡ������8 */
#define GPIO_Pin_9    BIT9   /*!< ѡ������9 */
#define GPIO_Pin_10   BIT10  /*!< ѡ������10 */
#define GPIO_Pin_11   BIT11  /*!< ѡ������11 */
#define GPIO_Pin_12   BIT12  /*!< ѡ������12 */
#define GPIO_Pin_13   BIT13  /*!< ѡ������13 */
#define GPIO_Pin_14   BIT14  /*!< ѡ������14 */
#define GPIO_Pin_15   BIT15  /*!< ѡ������15 */
#define GPIO_Pin_ALL  0xFFFF /*!< ѡ���������� */

/* ����Դ���壨���ڸ��ù������ã�*/
#define GPIO_PinSource_0  0  /*!< ��������0�ĸ��ù��� */
#define GPIO_PinSource_1  1  /*!< ��������1�ĸ��ù��� */
#define GPIO_PinSource_2  2  /*!< ��������2�ĸ��ù��� */
#define GPIO_PinSource_3  3  /*!< ��������3�ĸ��ù��� */
#define GPIO_PinSource_4  4  /*!< ��������4�ĸ��ù��� */
#define GPIO_PinSource_5  5  /*!< ��������5�ĸ��ù��� */
#define GPIO_PinSource_6  6  /*!< ��������6�ĸ��ù��� */
#define GPIO_PinSource_7  7  /*!< ��������7�ĸ��ù��� */
#define GPIO_PinSource_8  8  /*!< ��������8�ĸ��ù��� */
#define GPIO_PinSource_9  9  /*!< ��������9�ĸ��ù��� */
#define GPIO_PinSource_10 10 /*!< ��������10�ĸ��ù��� */
#define GPIO_PinSource_11 11 /*!< ��������11�ĸ��ù��� */
#define GPIO_PinSource_12 12 /*!< ��������12�ĸ��ù��� */
#define GPIO_PinSource_13 13 /*!< ��������13�ĸ��ù��� */
#define GPIO_PinSource_14 14 /*!< ��������14�ĸ��ù��� */
#define GPIO_PinSource_15 15 /*!< ��������15�ĸ��ù��� */

/* ============== GPIO������������ ============== */

/* ��ʼ�������ú��� *********************************/
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct); // ��ʼ��GPIO����
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);                // ��ʼ�����ýṹ��ΪĬ��ֵ

void GPIO_LockRegister(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);   // ����GPIO����
void GPIO_UnlockRegister(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); // ����GPIO����

/* GPIO��д���� *************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);  // ��ȡ������������״̬
uint32_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);                       // ��ȡ�����˿�����״̬
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); // ��ȡ�����������״̬
uint32_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);                      // ��ȡ�����˿����״̬

void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);                    // ��������Ϊ�ߵ�ƽ
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);                  // ��������Ϊ�͵�ƽ
void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t Val);                           // д�������˿����ֵ
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal); // д�뵥������״̬

/* GPIO���ù������ú��� ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF); // �������Ÿ��ù���

#endif /*__lks32mc08x_GPIO_H */ // ����ͷ�ļ�����

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
