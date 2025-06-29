/**
 * LKS32MC081C8T8 GPIO 配置指南
 * ===========================================================
 *
 * 一、GPIO 工作模式 (GPIOMode_TypeDef)
 * -----------------------------------------------------------
 * 1. 输入模式 (GPIO_Mode_IN)   : 读取外部数字信号
 *    - 浮空输入: GPIO_PuPd_NOPULL
 *    - 上拉输入: GPIO_PuPd_UP
 *
 * 2. 输出模式 (GPIO_Mode_OUT)  : 驱动外部设备
 *    - 推挽输出: GPIO_PODEna = 0 (默认)
 *    - 开漏输出: GPIO_PODEna = 1 (需外接上拉电阻)
 *
 * 3. 模拟模式 (GPIO_Mode_ANA)  : ADC/DAC 模拟信号处理
 *    - 禁用数字功能
 *
 * 4. 通用IO模式 (GPIO_Mode_IO) : 双向数据传输
 *
 * 二、输出模式详解
 * -----------------------------------------------------------
 * 推挽输出 vs 开漏输出:
 *
 * | 特性         | 推挽输出                  | 开漏输出                  |
 * |--------------|--------------------------|--------------------------|
 * | 电路结构     | P-MOS + N-MOS            | 仅N-MOS                  |
 * | 高电平驱动   | 主动驱动到VDD            | 依赖外部上拉             |
 * | 低电平驱动   | 主动驱动到GND            | 主动驱动到GND            |
 * | 驱动能力     | 强（双向驱动）            | 弱（仅能拉低）            |
 * | 总线冲突保护 | 无                       | 天然防短路               |
 * | 电平转换     | 不支持                   | 支持（改变上拉电压）      |
 * | 典型应用     | LED/继电器驱动           | I2C总线/电平转换         |
 *
 * 三、关键配置结构体 (GPIO_InitTypeDef)
 * -----------------------------------------------------------
 * typedef struct {
 *   uint32_t GPIO_Pin;          // 引脚选择 (GPIO_Pin_0~15)
 *   GPIOMode_TypeDef GPIO_Mode; // 工作模式 (IN/OUT/ANA/IO)
 *   GPIOPuPd_TypeDef GPIO_PuPd; // 上拉配置 (NOPULL/UP)
 *   uint32_t GPIO_PODEna;       // 开漏使能 (0:推挽, 1:开漏)
 * } GPIO_InitTypeDef;
 *
 * 四、复用功能配置
 * -----------------------------------------------------------
 * 使用 GPIO_PinAFConfig() 配置引脚复用功能:
 *   - AF4_UART  : 串口通信
 *   - AF5_SPI   : SPI接口
 *   - AF6_I2C   : I2C总线
 *   - AF10_CAN  : CAN总线
 *
 * 五、配置锁定机制
 * -----------------------------------------------------------
 * 防止意外修改配置:
 *   GPIO_LockRegister()   : 锁定配置
 *   GPIO_UnlockRegister() : 解锁配置
 *
 * 六、最佳实践
 * -----------------------------------------------------------
 * 1. LED控制: 推挽输出 + 浮空输入
 * 2. 按钮检测: 上拉输入
 * 3. I2C总线: 开漏输出 + 4.7kΩ上拉电阻
 * 4. ADC采集: 模拟模式
 *
 * 注意: 使用前需启用GPIO时钟 (RCC相关配置)
 * ===========================================================
 */

#ifndef __MYGPIO_INIT_H_
#define __MYGPIO_INIT_H_

#include "lks32mc08x_lib.h"

void GPIO_init(void);

#endif

/*
// 示例：LED初始化函数
void LED_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 步骤1: 配置结构体参数
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;      // 选择GPIO1的Pin0
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;   // 输出模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;// 禁用上拉/下拉
    GPIO_InitStruct.GPIO_PODEna = 0;             // 推挽输出

    // 步骤2: 初始化GPIO
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    // 步骤3: 初始状态设为低电平(假设LED阴极接GPIO)
    GPIO_ResetBits(GPIO1, GPIO_Pin_0);
}

// 示例：按钮初始化函数
void Button_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;    // 输入模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;    // 启用内部上拉
    GPIO_InitStruct.GPIO_PODEna = 0;             // 无关参数

    GPIO_Init(GPIO0, &GPIO_InitStruct);
}

// 示例：I2C引脚初始化
void I2C_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // SDA线配置 (PB9)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;   // 输出模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;// 禁用内部上拉
    GPIO_InitStruct.GPIO_PODEna = 1;             // 开漏输出
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    // 复用功能配置
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF6_I2C);
}
*/
