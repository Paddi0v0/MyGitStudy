/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： mingganghuang
 * 完成日期： 2021年11月15日
 *
 *******************************************************************************/
#include "lks32mc07x_lib.h"
#include "hardware_init.h"
#include "delay.h"

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();               /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;       /* 开启写使能*/
    IWDG_DISABLE();                /* 关闭独立看门狗使能*/
    FLASH_CFG |= 0x00080000;       /* FLASH 预取加速使能*/
    delay_init(48);                /* 延时函数初始化时钟48MHz*/
    GPIO_init();                   /* GPIO初始化*/
    I2C_init();                    /* I2C初始化 */
    delay_us(100);                 /* 延时等待硬件初始化稳定 */
    NVIC_EnableIRQ(I2C0_IRQn);      /* 使能I2C中断*/
    NVIC_SetPriority(I2C0_IRQn, 1); /* I2C中断优先级配置*/
    SYS_WR_PROTECT = 0x0;          /* 关闭系统寄存器写操作*/
    __enable_irq();                /* 开启总中断 */
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
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
//    SYS_VolSelModule(1);       /* 0: 3.3V ; 1: 5.0V*/
    SYS_AFE_REG0 |= BIT15;     /* BIT15:PLLPDN */
    SoftDelay(100);            /* 等待PLL稳定*/
    SYS_CLK_CFG = 0x000001ff; /* BIT[9:8]:0: CLK_HS,1:PLL,2:LRC,3:LRC
                               | BIT[7:0]CLK_DIV  | 0x1ff对应48M时钟 */
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
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void SystemInit(void)
{
    Clock_Init(); /* 时钟初始化 */
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
    GPIO_StructInit(&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_3, AF6_I2C);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_4, AF6_I2C);
    GPIO0->PUE |= BIT3|BIT4;
}
/*******************************************************************************
 函数名称：    void I2C_init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0         Howlet Li           创建
 *******************************************************************************/
void I2C_init(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    I2C_StructInit(&I2C_InitStruct);
    
    I2C_InitStruct.ADRCMP           =   DISABLE ;   //  I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效。
    I2C_InitStruct.MST_MODE         =   ENABLE  ;   //  I2C 主模式使能
    I2C_InitStruct.SLV_MODE         =   DISABLE ;   //  I2C 从模式使能
//    I2C_InitStruct.DMA              =   DISABLE  ;   //  I2C DMA传输使能
    I2C_InitStruct.BaudRate         =   100000 ;   //  I2C 波特率
    I2C_InitStruct.IE               =   ENABLE  ;   //  I2C 中断使能
    I2C_InitStruct.TC_IE            =   ENABLE  ;   //  I2C 数据传输完成中断使能
    I2C_InitStruct.BUS_ERR_IE       =   ENABLE ;   //  I2C 总线错误事件中断使能
    I2C_InitStruct.STOP_IE          =   ENABLE ;   //  I2C STOP 事件中断使能
    I2C_InitStruct.BURST_NACK       =   ENABLE  ;   //  I2C 传输，NACK 事件中断使能
    I2C_InitStruct.BURST_ADDR_CMP   =   DISABLE ;   //  I2C 传输，硬件地址匹配中断使能
    I2C_Init(I2C0,&I2C_InitStruct);
}


/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}

/*******************************************************************************
 函数名称：    uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 功能描述：    GPIO电平反转函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg;
    reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); //读GPIO电平
    if (reg)
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin);
        return 0;
    }
    else
    {
        GPIO_SetBits(GPIOx, GPIO_Pin);
        return 1;
    }
}
