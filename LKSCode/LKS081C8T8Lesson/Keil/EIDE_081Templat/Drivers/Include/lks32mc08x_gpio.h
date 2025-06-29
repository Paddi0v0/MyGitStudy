/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_gpio.h\n
 * 文件标识： 无 \n
 * 内容摘要： GPIO外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年6月19日     <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
#ifndef __LKS32MC08x_GPIO_H
#define __LKS32MC08x_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
#include "lks32mc08x.h"

/**
 *@brief GPIO寄存器结构体句柄
 */
typedef struct
{
    __IO uint32_t PIE;   /*!< 输入使能 */
    __IO uint32_t POE;   /*!< 输出使能 */
    __IO uint32_t PDI;   /*!< 输入数据 */
    __IO uint32_t PDO;   /*!< 输出数据 */
    __IO uint32_t PUE;   /*!< 上拉使能 */
    __IO uint32_t PDE;   /*!< 空闲     */
    __IO uint32_t PODE;  /*!< 开漏使能 */
    __IO uint32_t LCKR;  /*!< 配置锁存 */
    __IO uint32_t F3210; /*!< 功能选择 GPIO_Pin_0-3 */
    __IO uint32_t F7654; /*!< 功能选择 GPIO_Pin_4-7 */
    __IO uint32_t FBA98; /*!< 功能选择 GPIO_Pin_8-11 */
    __IO uint32_t FFEDC; /*!< 功能选择 GPIO_Pin_12-15 */
} GPIO_TypeDef;

/**
 * GPIO0结构体基地址定义
 */
#ifndef GPIO0
#define GPIO0 ((GPIO_TypeDef *)GPIO0_BASE)
#endif
/**
 * GPIO1结构体基地址定义
 */
#ifndef GPIO1
#define GPIO1 ((GPIO_TypeDef *)GPIO1_BASE)
#endif
/**
 * GPIO2结构体基地址定义
 */
#ifndef GPIO2
#define GPIO2 ((GPIO_TypeDef *)GPIO2_BASE)
#endif
/**
 * GPIO3结构体基地址定义
 */
#ifndef GPIO3
#define GPIO3 ((GPIO_TypeDef *)GPIO3_BASE)
#endif

/**
 *@brief GPIO模式选择枚举
 */
typedef enum
{
    GPIO_Mode_IN = 0x00,  /*!< GPIO Input Mode */
    GPIO_Mode_OUT = 0x01, /*!< GPIO Output Mode */
    GPIO_Mode_ANA = 0x02, /*!< GPIO Analog In/Out Mode,用作ANA时需禁止输入输出 */
    GPIO_Mode_IO = 0x03
} GPIOMode_TypeDef;

/**
 *@brief GPIO输出模式选择枚举
 */
typedef enum
{
    GPIO_PuPd_NOPULL = 0x00, /*!< 高阻态 */
    GPIO_PuPd_UP = 0x01,     /*!< 上拉 */
} GPIOPuPd_TypeDef;

/**
 *@brief GPIO寄存器写入量枚举
 */
typedef enum
{
    Bit_RESET = 0, // 写0
    Bit_SET        // 写1
} BitAction;

/**
 *@brief  GPIO功能配置结构体句柄
 */
typedef struct
{
    uint32_t GPIO_Pin;          /*!< 要配置的Pad */
    GPIOMode_TypeDef GPIO_Mode; /*!< GPIO模式:输入、输出、模拟 */
    GPIOPuPd_TypeDef GPIO_PuPd; /*!< 默认/上拉 */
    uint32_t GPIO_PODEna;       /*!< 开漏 */
} GPIO_InitTypeDef;

#define AF0_GPIO 0 /*!< GPIO复用功能0，模拟功能 */
#define AF1_SYSAF                                                                                                                                                                                      \
    1                 /*!< GPIO复用功能1，SYS_AF、CMP、CLOCK等数字信号输出功能 \
                     */
#define AF2_HALL 2    /*!< GPIO复用功能2，HALL功能 */
#define AF3_MCPWM 3   /*!< GPIO复用功能3，MCPWM功能 */
#define AF4_UART 4    /*!< GPIO复用功能4，UART功能 */
#define AF5_SPI 5     /*!< GPIO复用功能5，SPI功能 */
#define AF6_I2C 6     /*!< GPIO复用功能6，I2C功能 */
#define AF7_TIMER01 7 /*!< GPIO复用功能7，Timer0、Timer1功能 */
#define AF8_TIMER23 8 /*!< GPIO复用功能8，Timer2、Timer3、QEP0、QEP1功能 */
#define AF9_DEBUG 9   /*!< GPIO复用功能9，ADC trigger debug功能 */
#define AF10_CAN 10   /*!< GPIO复用功能10，CAN功能 */
#define AF11_SIF 11   /*!< GPIO复用功能11，SIF功能 */

/*GPIO pin脚定义*/
#define GPIO_Pin_NONE 0               /*!<GPIO pin脚定义，无pin脚  */
#define GPIO_Pin_0 BIT0               /*!<<GPIO pin脚定义，pin_0脚 */
#define GPIO_Pin_1 BIT1               /*!<GPIO pin脚定义，pin_1脚  */
#define GPIO_Pin_2 BIT2               /*!<GPIO pin脚定义，pin_2脚  */
#define GPIO_Pin_3 BIT3               /*!<GPIO pin脚定义，pin_3脚  */
#define GPIO_Pin_4 BIT4               /*!<GPIO pin脚定义，pin_4脚  */
#define GPIO_Pin_5 BIT5               /*!<GPIO pin脚定义，pin_5脚  */
#define GPIO_Pin_6 BIT6               /*!<GPIO pin脚定义，pin_6脚  */
#define GPIO_Pin_7 BIT7               /*!<GPIO pin脚定义，pin_7脚  */
#define GPIO_Pin_8 BIT8               /*!<GPIO pin脚定义，pin_8脚  */
#define GPIO_Pin_9 BIT9               /*!<GPIO pin脚定义，pin_9脚  */
#define GPIO_Pin_10 BIT10             /*!<GPIO pin脚定义，pin_10脚 */
#define GPIO_Pin_11 BIT11             /*!<GPIO pin脚定义，pin_11脚 */
#define GPIO_Pin_12 BIT12             /*!<GPIO pin脚定义，pin_12脚 */
#define GPIO_Pin_13 BIT13             /*!<GPIO pin脚定义，pin_13脚 */
#define GPIO_Pin_14 BIT14             /*!<GPIO pin脚定义，pin_14脚 */
#define GPIO_Pin_15 BIT15             /*!<GPIO pin脚定义，pin_15脚 */
#define GPIO_Pin_ALL (uint32_t)0xFFFF /*!<GPIO pin脚定义，所有pin脚*/

/*GPIO复用功能pin脚定义*/
#define GPIO_PinSource_0 0   /*!<GPIO pin脚定义，pin_0脚 */
#define GPIO_PinSource_1 1   /*!<GPIO pin脚定义，pin_1脚 */
#define GPIO_PinSource_2 2   /*!<GPIO pin脚定义，pin_2脚 */
#define GPIO_PinSource_3 3   /*!<GPIO pin脚定义，pin_3脚 */
#define GPIO_PinSource_4 4   /*!<GPIO pin脚定义，pin_4脚 */
#define GPIO_PinSource_5 5   /*!<GPIO pin脚定义，pin_5脚 */
#define GPIO_PinSource_6 6   /*!<GPIO pin脚定义，pin_6脚 */
#define GPIO_PinSource_7 7   /*!<GPIO pin脚定义，pin_7脚 */
#define GPIO_PinSource_8 8   /*!<GPIO pin脚定义，pin_8脚 */
#define GPIO_PinSource_9 9   /*!<GPIO pin脚定义，pin_9脚 */
#define GPIO_PinSource_10 10 /*!<GPIO pin脚定义，pin_10脚 */
#define GPIO_PinSource_11 11 /*!<GPIO pin脚定义，pin_11脚 */
#define GPIO_PinSource_12 12 /*!<GPIO pin脚定义，pin_12脚 */
#define GPIO_PinSource_13 13 /*!<GPIO pin脚定义，pin_13脚 */
#define GPIO_PinSource_14 14 /*!<GPIO pin脚定义，pin_14脚 */
#define GPIO_PinSource_15 15 /*!<GPIO pin脚定义，pin_15脚 */

/* 初始化、配置函数 *********************************/
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);

void GPIO_LockRegister(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_UnlockRegister(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/* GPIO读写函数 *************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint32_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint32_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);

void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t Val);
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

/* GPIO功能选择函数 ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF);

#endif /*__lks32mc08x_GPIO_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF
 * FILE****/
