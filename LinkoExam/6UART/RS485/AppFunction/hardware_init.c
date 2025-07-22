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
 * 修改日期： 2022年4月14日
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/
#include "lks32mc08x_lib.h"
#include "hardware_init.h"
#include "basic.h"

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0           HuangMG            创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();                 /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;         /* 使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000;         /* enable prefetch ，FLASH预取加速使能*/
    GPIO_init();                     /* GPIO初始化 */
    UART_init();                     /* UART_init 初始化 */
    SoftDelay(100);                  /* 等待硬件初始化完毕*/
    NVIC_EnableIRQ(UART0_IRQn);      /* 使能UART_IRQn外部中断*/
    NVIC_SetPriority(UART0_IRQn, 0); /* UART_IRQn外部中断优先级设置为0*/
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
    __enable_irq();                  /* 开启中断 */
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
    /*UART0 P0.15-RX0*/
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; /*GPIO配置为输入模式*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;   /*PIN15*/
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    /*UART0 P1.0-TX0*/
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;/*GPIO配置为输出模式*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;    /*PIN0*/
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF4_UART); // P0.15复用成UART1_RX
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF4_UART);  // P1.0 复用成UART1_TX
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
 2023/10/23      V2.0         HuangMG        增加MCU电源检测功能
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;     /* BIT15:PLLPDN */
		#if POWER_MODE
		SYS_VolSelModule(MCU_POWER_5v0);       /* MCU供电电压：1：5V，0;3.3V*/
		#else
		SYS_VolSelModule(MCU_POWER_3v3);       /* MCU供电电压：1：5V，0;3.3V*/
		#endif
	  SoftDelay(100);            /* 等待PLL稳定*/
	  SYS_WR_PROTECT = 0x7a83;       /* 解除系统寄存器写保护 */
	
    SYS_CLK_CFG = 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
	  SYS_WR_PROTECT = 0x0;      /*关闭系统寄存器写操作*/
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
    Clock_Init(); /* 时钟初始化*/
}

/*******************************************************************************
 函数名称：    void UART_init(void)
 功能描述：    UART寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0           HuangMG            创建
 *******************************************************************************/
void UART_init(void)
{
    UART_InitTypeDef UART_InitStruct;

    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate     = 9600;                 /* 设置波特率9600 */
    UART_InitStruct.WordLength   = UART_WORDLENGTH_8b;   /* 发送数据长度8位 */
    UART_InitStruct.StopBits     = UART_STOPBITS_1b;     /* 停止位长度1位 */
    UART_InitStruct.FirstSend    = UART_FIRSTSEND_LSB;   /* 先发送LSB */
    UART_InitStruct.ParityMode   = UART_Parity_NO;       /* 无奇偶校验 */
    UART_InitStruct.RXD_INV      = DISABLE;              /* RXD电平正常输出*/
    UART_InitStruct.TXD_INV      = DISABLE;              /* TXD电平正常输出*/
    UART_InitStruct.MultiDropEna = ENABLE;               /* 使能 Multi-drop*/
    UART_InitStruct.Match485Addr = 0x32;                 /* 485通信时的匹配地址*/	
    /*使能接收和发送完成中断*/
    UART_InitStruct.IRQEna = UART_IRQEna_SendOver | UART_IRQEna_RcvOver;
    UART_Init(UART0, &UART_InitStruct);
}

/**********************使用printf函数需要添加的函数*****************************************/
//标准库需要的支持函数
struct __FILE
{
    int handle;
};

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}

//重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    UART_SendData(UART0, (uint8_t)ch);
    /* 发送缓存状态位 */
    while ((UART0->STT & BIT0) == FALSE)
        ; // UART0->STT发送缓存状态位。

    return (ch);
}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0           HuangMG            创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}

/*******************************************************************************
 函数名称：    void Invers_GPIO(void)
 功能描述：    LED电平翻转函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0           HuangMG            创建
 *******************************************************************************/
void Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) // GPIO电平翻转函数
{
    u16 reg;
    reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); //读GPIO电平
    if (reg)
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin);
    }
    else
    {
        GPIO_SetBits(GPIOx, GPIO_Pin);
    }
}
