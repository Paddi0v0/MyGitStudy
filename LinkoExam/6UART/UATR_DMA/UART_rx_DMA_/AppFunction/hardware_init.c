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
 * 版 本 号：
 * 修 改 人：HMG
 * 修改内容：
 *
 *******************************************************************************/
#include "hardware_config.h"

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
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /*FLASH预取加速使能*/
    GPIO_init();             /* GPIO初始化 */
    UART_init();             /* UART初始化 */
    DMA_init();              /* DMA初始化 */
    SoftDelay(100);          /* 等待硬件初始化完毕*/
    NVIC_EnableIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, 0);
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
    __enable_irq();         /* 开启中断 */
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

    //配置UART0_RXD  P0.15
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    //配置UART0_TXD  P1.0
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF4_UART);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF4_UART);
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
    Clock_Init(); /* 时钟初始化 */
}

/*******************************************************************************
 函数名称：    void UART_init(void)
 功能描述：    UART0寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART_init(void)
{
    UART_InitTypeDef UART_InitStruct;

    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 9600;                 /* 设置波特率38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b; /* 发送数据长度8位 */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;     /* 停止位1位 */
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;  /* 先发送LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;     /* 无奇偶校验 */
    UART_InitStruct.IRQEna = UART_IRQEna_RX_DMA_RE;  /* 接收完成DMA请求使能*/
    UART_Init(UART0, &UART_InitStruct);
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
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
u8 DMA_RX[10];
void DMA_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);

    /*UART DMA接收使能，接收到10个数据后，产生DMA中断*/
    DMA_InitStruct.DMA_IRQ_EN = DMA_TCIE;             /* DMA 传输完成中断使能 */
    DMA_InitStruct.DMA_DIR = PERI2MEMORY;             /* 外设至内存 */
    DMA_InitStruct.DMA_CIRC = DISABLE;                /* DMA传输模式：循环模式，高有效 */
    DMA_InitStruct.DMA_PINC = DISABLE;                /* 外设地址每轮内是否递增,高有效 */
    DMA_InitStruct.DMA_MINC = ENABLE;                 /* 内存地址第二轮是否在第一轮地址的基础上递增,高有效 */
    DMA_InitStruct.DMA_PBTW = DMA_BYTE_TRANS;         /* 外设访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_MBTW = DMA_BYTE_TRANS;         /* 内存访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_CH2_UART0_REQ_EN; /* 通道 DMA_UART0_REQ_EN DMA 请求使能，高有效 */
    DMA_InitStruct.DMA_TIMES = 1;                     /* DMA 通道 x 每轮数据搬运次数 1~511 */
    DMA_InitStruct.DMA_ROUND = 10;                    /* DMA 通道 x 采样轮数 1~255 */
    DMA_InitStruct.DMA_CPAR = (u32)&UART0_BUFF;       /* DMA 通道 x 外设地址 */
    DMA_InitStruct.DMA_CMAR = (u32)DMA_RX;            /* DMA 通道 x 内存地址 */
    DMA_Init(DMA_CH2, &DMA_InitStruct);
	  DMA_CHx_EN(DMA_CH2,ENABLE);                       /*使能DMA_CH3通道*/
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

