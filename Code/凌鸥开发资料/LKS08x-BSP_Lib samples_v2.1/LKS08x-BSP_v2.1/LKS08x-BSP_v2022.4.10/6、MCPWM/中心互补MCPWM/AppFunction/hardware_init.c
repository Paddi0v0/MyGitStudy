/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2015年11月5日
 *
 * 修改记录1：
 * 修改日期：2021年8月25日
 * 版 本 号：V 1.0
 * 修 改 人：HMG
 * 修改内容：创建
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "gpio_led.h"
#include "gpio_key.h"
#include "utimer.h"
#include "WDT.h"
#include "lks32mc08x_MCPWM.h"

void UART_init(void);

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();            /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;    /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000;    /* enable prefetch ，FLASH预取加速使能*/
    GPIO_init();                /* GPIO初始化 */
    MCPWM_init();               /* MCPWM初始化 */
    NVIC_EnableIRQ(MCPWM_IRQn); //使能MCPWM中断
    NVIC_SetPriority(MCPWM_IRQn, 0);
    __enable_irq(); /* 开启中断 */
}

/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体

    //GPIO_P1.4到P1.11设置为输出模式，MCPWM复用
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM); //GPIO_PinSource_4表示P1的第四引脚
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_10, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_11, AF3_MCPWM);
}


/*******************************************************************************
 函数名称：    void Clock_Init(void)
 功能描述：    时钟配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Clock_Init(void)
{

    SYS_WR_PROTECT = 0x7a83;      /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15 | BIT0; /* BIT15:PLLPDN  BIT0:ADC_Clock*/
    SYS_CLK_CFG |= 0x000001ff;    /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 ; 开启所有时钟*/
}

/*******************************************************************************
 函数名称：    void SystemInit(void)
 功能描述：    硬件系统初始化，调用时钟初始化函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/14      V1.0           Howlet Li          创建
 *******************************************************************************/
void SystemInit(void)
{
    Clock_Init(); /* 时钟初始化 */
}



void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = PWM_PRSC;                   /* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;                     /* 模块时钟开启 */
    MCPWM_InitStructure.MCPWM_Cnt_EN = ENABLE;                /* 主计数器开始计数使能开关 */
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH3 = CENTRAL_PWM_MODE;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12; /* 急停事件(来自IO口信号)数字滤波器时间设置 */
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;  /* 急停事件(来自比较器信号)数字滤波器时间设置 */

    MCPWM_InitStructure.MCPWM_PERIOD = PWM_PERIOD;              /* 计数周期设置即MCPWM输出周期*/
    MCPWM_InitStructure.TriggerPoint0 = (u16)(10 - PWM_PERIOD); /* MCPWM_TMR0 ADC触发事件T0 设置 */
    MCPWM_InitStructure.TriggerPoint1 = (u16)(PWM_PERIOD - 1);  /* MCPWM_TMR1 ADC触发事件T1 设置 */
    MCPWM_InitStructure.DeadTimeCH0N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH0P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2P = DEADTIME; /* 死区时间设置 */
    MCPWM_InitStructure.DeadTimeCH3N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH3P = DEADTIME; /* 死区时间设置 */

#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)           /* CHxP 高有效， CHxN低电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE; /* CH0N通道输出极性设置 | 取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE; /* CH0P通道输出极性设置 | 正常输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH3N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;  /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = HIGH_LEVEL; /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH3P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH3N_default_output = HIGH_LEVEL;
#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH) /* CHxP 高有效， CHxN高电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE; /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE; /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH3N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH3N_CH3P = DISABLE; /* 通道交换选择设置 */
    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL; /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = LOW_LEVEL; /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH3P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH3N_default_output = LOW_LEVEL;

#endif
#endif

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE; /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                                 还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/

    MCPWM_InitStructure.MCPWM_T0_UpdateEN = ENABLE;  /* MCPWM T0事件更新使能 */
    MCPWM_InitStructure.MCPWM_T1_UpdateEN = DISABLE; /* MCPWM T1事件更新 禁止*/

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    MCPWM_InitStructure.T1_Update_INT_EN = ENABLE; /* T1更新事件 中断使能或关闭 */
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE; /* T0更新事件 中断使能或关闭 */
#else
#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE; /* T0更新事件 中断使能或关闭 */
#endif
#endif
#endif

    MCPWM_InitStructure.FAIL0_INT_EN = ENABLE;              /* FAIL0事件， 中断使能或关闭 */
    MCPWM_InitStructure.FAIL0_INPUT_EN = DISABLE;           /* FAIL0 输入功能使能*/
    MCPWM_InitStructure.FAIL0_Signal_Sel = FAIL_SEL_CMP;    /* FAIL0事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL0_Polarity = HIGH_LEVEL_ACTIVE; /* FAIL0事件极性选择，高有效 */

    MCPWM_InitStructure.FAIL1_INT_EN = ENABLE;              /* FAIL1事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL1_INPUT_EN = ENABLE;            /* FAIL1通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL1_Signal_Sel = FAIL_SEL_CMP;    /* FAIL1事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL1_Polarity = HIGH_LEVEL_ACTIVE; /* FAIL1事件极性选择，高有效或低有效 */
    MCPWM_InitStructure.T0_Update_INT_EN = ENABLE;          /* T0更新事件中斷使能 */
    MCPWM_Init(&MCPWM_InitStructure);

    MCPWM_TH00 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH01 = (PWM_PERIOD >> 2);
    MCPWM_TH10 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH11 = (PWM_PERIOD >> 2);
    MCPWM_TH20 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH21 = (PWM_PERIOD >> 2);
    MCPWM_TH30 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH31 = (PWM_PERIOD >> 2);

    PWMOutputs(ENABLE); //输出使能
}




