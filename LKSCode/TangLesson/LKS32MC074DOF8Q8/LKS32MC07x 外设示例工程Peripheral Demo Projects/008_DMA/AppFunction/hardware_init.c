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
#include "hardware_init.h"

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
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/
		IWDG_DISABLE();						/*关闭看门狗*/
		DMA_init(); 							/*DMA配置初始化*/
		GPIO_init();
		UART1_init();
		SoftDelay(100);                  /* 等待硬件初始化完毕*/
		NVIC_EnableIRQ(DMA0_IRQn);
		NVIC_SetPriority(DMA0_IRQn, 1);
	  SYS_WR_PROTECT = 0x0;    /*关闭系统寄存器写操作*/
	  __enable_irq();          /* 开启总中断 */
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
	   //配置UART0_RXD  P2.8
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
	
    //配置UART0_TXD  P3.9
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO3, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF4_UART);
    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_9, AF4_UART);
}


/*******************************************************************************
 函数名称：    void UART0_init(void)
 功能描述：    UART0寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART0_init(void)
{
    UART_InitTypeDef UART_InitStruct;
    
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 38400;                 /* 设置波特率38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* 发送数据长度8位 */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* 先发送LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;      /* 无奇偶校验 */
    UART_InitStruct.IRQEna = 0;
    UART_Init(UART0, &UART_InitStruct);

}

/*******************************************************************************
 函数名称：    void UART1_init(void)
 功能描述：    UART0寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/02/11      V1.0           ywx          创建
 *******************************************************************************/
void UART1_init(void)
{
    UART_InitTypeDef UART_InitStruct;
    
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 38400;                 /* 设置波特率38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* 发送数据长度8位 */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* 先发送LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;      /* 无奇偶校验 */
		UART_InitStruct.DMARE = TX_DMA_RE;
    UART_Init(UART1, &UART_InitStruct);

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
    SYS_AFE_REG5 |= BIT15 ;       /* BIT15:PLLPDN*/
    SoftDelay(100);               /* 等待硬件初始化完毕*/	
	  SYS_CLK_CFG = 0x000001ff;     /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 ; 开启所有时钟*/
    SYS_WR_PROTECT = 0x0;         /*关闭系统寄存器写操作*/
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
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

/*******************************************************************************
 函数名称：    void DMA_init(void)
 功能描述：    DMA初始化配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    问：如何判断DMA_UART的传输方向
               答：DMA_DIR配置DMA_UART的传输方向
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/02/22      V1.0             ywx                创建
 *******************************************************************************/
u8 DMA_TX[13] = {'L', 'K', 'S', '_','D','M','A', '_', 'T', 'e','s','t','\n'};/*搬运数据定义*/
void DMA_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.IRQ_EN = ENABLE;
    DMA_InitStruct.CIRC = DISABLE;
    DMA_InitStruct.SINC = ENABLE;
    DMA_InitStruct.DINC = DISABLE;
    DMA_InitStruct.SBTW = DMA_BYTE_TRANS;
    DMA_InitStruct.DBTW = DMA_BYTE_TRANS;
    DMA_InitStruct.REN.B.UART1_TX_EN = ENABLE;
    DMA_InitStruct.TMS = 13;
    DMA_InitStruct.RMODE = ENABLE;
    DMA_InitStruct.SADR = (u32)DMA_TX;
    DMA_InitStruct.DADR = (u32)&UART1_BUFF;
    DMA_InitStruct.EN = ENABLE;
    DMA_Init(DMA_CHN3, &DMA_InitStruct);
}


