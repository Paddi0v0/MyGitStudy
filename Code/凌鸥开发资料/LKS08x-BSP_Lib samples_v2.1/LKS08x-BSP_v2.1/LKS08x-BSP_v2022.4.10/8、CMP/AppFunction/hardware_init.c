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
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "gpio_led.h"
#include "gpio_key.h"
#include "utimer.h"
#include "WDT.h"

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
    __disable_irq();               /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;       /* 使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000;       /* FLASH预取加速使能*/
    GPIO_init();                   /* GPIO初始化 */
    CMP_Init();                    /* CMP_Init初始化 */
    NVIC_SetPriority(CMP_IRQn, 3); // CMP中断优先级配置
    NVIC_EnableIRQ(CMP_IRQn);      // 使能CMP定时器中断
    __enable_irq();                /* 开启中断 */
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

    //配置按键 start：P2.11  stop:P2.11
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    //配置LED1：P0.6  LED2：P0.7  LED3: P0.3
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    //CMP1_OUT  GPIO_P2.3设置为模拟通道
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_3, AF1_SYSAF);
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


/*******************************************************************************
 函数名称：    void CMP_Init(void)
 功能描述：    比较器初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/15      V1.0           Howlet Li          创建
 *******************************************************************************/
void CMP_Init(void)
{
    CMP_InitTypeDef CMP_InitStruct;

    CMP_StructInit(&CMP_InitStruct);

    CMP_InitStruct.CMP0_EN = ENABLE;            /* 比较器0开关 操作SYS_AFE_REG5 */
    CMP_InitStruct.CMP0_SELN = SELN_REF;        /* 比较器0，负端信号选择 */
    CMP_InitStruct.CMP0_SELP = SELP_CMP_OPA0IP; /* CMP0_P CMP0_OPA0_IP */
    CMP_InitStruct.CMP0_InEnable = ENABLE;      /* 比较器信号输入使能 */
    CMP_InitStruct.CMP0_IE = ENABLE;            /* 比较器0信号中断使能 */

    CMP_InitStruct.CMP1_EN = ENABLE;         /* 比较器1开关 */
    CMP_InitStruct.CMP1_SELN = SELN_REF;     /* CMP1_N 内部参考 */
    CMP_InitStruct.CMP1_SELP = SELP_CMP_IP0; /* CMP1_P CMP1_IP0 */
    CMP_InitStruct.CMP1_InEnable = ENABLE;   /* 比较器信号输入使能 */
    CMP_InitStruct.CMP1_IE = ENABLE;         /* 比较器1信号中断使能 */

    CMP_InitStruct.CMP_FltCnt = 15;     /* 即滤波宽度=tclk 周期*16*CMP_FltCnt (CMP_FltCnt分频系数,0~15)*/
    CMP_InitStruct.CMP_CLK_EN = ENABLE; /* 比较器中断配置时钟打开 */

    Comparator_init(&CMP_InitStruct);
}



