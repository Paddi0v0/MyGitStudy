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
#ifndef __LKS32MC08x_GPIO_H // 头文件保护宏，防止重复包含
#define __LKS32MC08x_GPIO_H // 定义头文件宏标识

/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x.h" // 包含芯片外设寄存器定义
#include "basic.h"      // 包含基础数据类型定义

/**
 *@brief GPIO寄存器结构体句柄
 * 定义GPIO寄存器映射的结构体
 */
typedef struct
{
    __IO uint32_t PIE;   /*!< 输入使能寄存器：控制引脚是否作为输入 */
    __IO uint32_t POE;   /*!< 输出使能寄存器：控制引脚是否作为输出 */
    __IO uint32_t PDI;   /*!< 输入数据寄存器：读取引脚当前输入状态 */
    __IO uint32_t PDO;   /*!< 输出数据寄存器：设置引脚输出电平 */
    __IO uint32_t PUE;   /*!< 上拉使能寄存器：控制是否启用内部上拉电阻 */
    __IO uint32_t PDE;   /*!< 空闲寄存器：保留未使用 */
    __IO uint32_t PODE;  /*!< 开漏使能寄存器：控制是否启用开漏输出模式 */
    __IO uint32_t LCKR;  /*!< 配置锁存寄存器：保护GPIO配置不被意外修改 */
    __IO uint32_t F3210; /*!< 功能选择寄存器：控制Pin0-Pin3的复用功能 */
    __IO uint32_t F7654; /*!< 功能选择寄存器：控制Pin4-Pin7的复用功能 */
    __IO uint32_t FBA98; /*!< 功能选择寄存器：控制Pin8-Pin11的复用功能 */
    __IO uint32_t FFEDC; /*!< 功能选择寄存器：控制Pin12-Pin15的复用功能 */
} GPIO_TypeDef;          // GPIO寄存器组结构体定义

/**
 * GPIO0结构体基地址定义：将GPIO0_BASE地址映射到GPIO_TypeDef结构体
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
 * 定义GPIO工作模式的4种类型
 */
typedef enum {
    GPIO_Mode_IN  = 0x00, /*!< 输入模式：引脚作为数字输入 */
    GPIO_Mode_OUT = 0x01, /*!< 输出模式：引脚作为数字输出 */
    GPIO_Mode_ANA = 0x02, /*!< 模拟模式：引脚用作模拟输入/输出（需禁用数字功能） */
    GPIO_Mode_IO  = 0x03  /*!< 保留模式 */
} GPIOMode_TypeDef;

/**
 *@brief GPIO上拉/下拉配置枚举
 * 定义GPIO输入模式时的电阻配置
 */
typedef enum {
    GPIO_PuPd_NOPULL = 0x00, /*!< 无上拉/下拉：高阻态输入 */
    GPIO_PuPd_UP     = 0x01, /*!< 上拉电阻：默认高电平 */
} GPIOPuPd_TypeDef;

/**
 *@brief GPIO位操作枚举
 * 用于设置单个引脚的电平状态
 */
typedef enum {
    Bit_RESET = 0, // 设置引脚为低电平
    Bit_SET        // 设置引脚为高电平
} BitAction;

/**
 *@brief GPIO配置结构体
 * 用于初始化GPIO引脚的参数集合
 */
typedef struct
{
    uint32_t GPIO_Pin;          /*!< 要配置的引脚（使用GPIO_Pin_x宏） */
    GPIOMode_TypeDef GPIO_Mode; /*!< 引脚工作模式：输入/输出/模拟 */
    GPIOPuPd_TypeDef GPIO_PuPd; /*!< 上拉配置：无上拉/上拉 */
    uint32_t GPIO_PODEna;       /*!< 开漏输出使能：0=推挽输出，1=开漏输出 */
} GPIO_InitTypeDef;

// GPIO复用功能定义（AF = Alternate Function）
#define AF0_GPIO    0  /*!< 基本GPIO功能 */
#define AF1_SYSAF   1  /*!< 系统级复用功能：CMP/CLOCK等 */
#define AF2_HALL    2  /*!< HALL传感器接口功能 */
#define AF3_MCPWM   3  /*!< 电机控制PWM功能 */
#define AF4_UART    4  /*!< UART串口功能 */
#define AF5_SPI     5  /*!< SPI接口功能 */
#define AF6_I2C     6  /*!< I2C接口功能 */
#define AF7_TIMER01 7  /*!< 定时器0/1功能 */
#define AF8_TIMER23 8  /*!< 定时器2/3及编码器接口功能 */
#define AF9_DEBUG   9  /*!< 调试触发功能 */
#define AF10_CAN    10 /*!< CAN总线功能 */
#define AF11_SIF    11 /*!< SIF接口功能 */

/* GPIO引脚定义（位掩码形式）*/
#define GPIO_Pin_NONE 0      /*!< 无引脚选择 */
#define GPIO_Pin_0    BIT0   /*!< 选择引脚0 */
#define GPIO_Pin_1    BIT1   /*!< 选择引脚1 */
#define GPIO_Pin_2    BIT2   /*!< 选择引脚2 */
#define GPIO_Pin_3    BIT3   /*!< 选择引脚3 */
#define GPIO_Pin_4    BIT4   /*!< 选择引脚4 */
#define GPIO_Pin_5    BIT5   /*!< 选择引脚5 */
#define GPIO_Pin_6    BIT6   /*!< 选择引脚6 */
#define GPIO_Pin_7    BIT7   /*!< 选择引脚7 */
#define GPIO_Pin_8    BIT8   /*!< 选择引脚8 */
#define GPIO_Pin_9    BIT9   /*!< 选择引脚9 */
#define GPIO_Pin_10   BIT10  /*!< 选择引脚10 */
#define GPIO_Pin_11   BIT11  /*!< 选择引脚11 */
#define GPIO_Pin_12   BIT12  /*!< 选择引脚12 */
#define GPIO_Pin_13   BIT13  /*!< 选择引脚13 */
#define GPIO_Pin_14   BIT14  /*!< 选择引脚14 */
#define GPIO_Pin_15   BIT15  /*!< 选择引脚15 */
#define GPIO_Pin_ALL  0xFFFF /*!< 选择所有引脚 */

/* 引脚源定义（用于复用功能配置）*/
#define GPIO_PinSource_0  0  /*!< 配置引脚0的复用功能 */
#define GPIO_PinSource_1  1  /*!< 配置引脚1的复用功能 */
#define GPIO_PinSource_2  2  /*!< 配置引脚2的复用功能 */
#define GPIO_PinSource_3  3  /*!< 配置引脚3的复用功能 */
#define GPIO_PinSource_4  4  /*!< 配置引脚4的复用功能 */
#define GPIO_PinSource_5  5  /*!< 配置引脚5的复用功能 */
#define GPIO_PinSource_6  6  /*!< 配置引脚6的复用功能 */
#define GPIO_PinSource_7  7  /*!< 配置引脚7的复用功能 */
#define GPIO_PinSource_8  8  /*!< 配置引脚8的复用功能 */
#define GPIO_PinSource_9  9  /*!< 配置引脚9的复用功能 */
#define GPIO_PinSource_10 10 /*!< 配置引脚10的复用功能 */
#define GPIO_PinSource_11 11 /*!< 配置引脚11的复用功能 */
#define GPIO_PinSource_12 12 /*!< 配置引脚12的复用功能 */
#define GPIO_PinSource_13 13 /*!< 配置引脚13的复用功能 */
#define GPIO_PinSource_14 14 /*!< 配置引脚14的复用功能 */
#define GPIO_PinSource_15 15 /*!< 配置引脚15的复用功能 */

/* ============== GPIO操作函数声明 ============== */

/* 初始化、配置函数 *********************************/
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct); // 初始化GPIO引脚
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);                // 初始化配置结构体为默认值

void GPIO_LockRegister(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);   // 锁定GPIO配置
void GPIO_UnlockRegister(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); // 解锁GPIO配置

/* GPIO读写函数 *************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);  // 读取单个引脚输入状态
uint32_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);                       // 读取整个端口输入状态
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); // 读取单个引脚输出状态
uint32_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);                      // 读取整个端口输出状态

void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);                    // 设置引脚为高电平
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);                  // 设置引脚为低电平
void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t Val);                           // 写入整个端口输出值
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal); // 写入单个引脚状态

/* GPIO复用功能配置函数 ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF); // 配置引脚复用功能

#endif /*__lks32mc08x_GPIO_H */ // 结束头文件保护

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
