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
#include "global_variable.h"
#include "MC_Parameter.h"
// #include "lks32mc07x_tim.h"
#include "lks32mc07x_lib.h"
#define CNT0_PRE_DRIVER_POLARITY P_HIGH__N_HIGH
#define CNT1_PRE_DRIVER_POLARITY P_HIGH__N_LOW

void SoftDelay(u32 cnt);
void SPI_init(void);
void DMA_init(void);
void GPIO0_Pin14Init(void);
void DMA_init(void);
extern uint16_t Tx_data_tbl[];
extern uint16_t Rx_data_tbl[];
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

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}
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
    __disable_irq(); /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;
    FLASH_CFG |= 0x00080000; /* enable prefetch */
//    SYS_SFT_RST = 0xffffffff;
    SYS_SFT_RST = 0;
    IWDG_DISABLE();          /* 关闭看门狗*/
    SYS_ModuleClockCmd(SYS_Module_GPIO, ENABLE);
    
    
    DMA_init();
    SPI_init();
    GPIO_init();
    
    
    SoftDelay(100); /* 延时等待硬件初始化稳定 */
    
    NVIC_EnableIRQ(DMA0_IRQn);
    NVIC_SetPriority(DMA0_IRQn, 0);
    NVIC_EnableIRQ(SPI0_IRQn);
    NVIC_SetPriority(SPI0_IRQn, 0);

    __enable_irq(); /* 开启总中断 */
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
void DMA_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.IRQ_EN = ENABLE;
    DMA_InitStruct.CIRC = DISABLE; // 关闭循环模式
    DMA_InitStruct.SINC = ENABLE;  // 源地址递增使能
    DMA_InitStruct.DINC = DISABLE; // 目的地址递增失能
    DMA_InitStruct.SBTW = DMA_BYTE_TRANS;
    DMA_InitStruct.DBTW = DMA_BYTE_TRANS;
    DMA_InitStruct.REN.B.SPI_TX_EN = ENABLE;
    DMA_InitStruct.TMS = 8;
    DMA_InitStruct.RMODE = ENABLE;
    DMA_InitStruct.SADR = (u32)Tx_data_tbl;
    DMA_InitStruct.DADR = (u32)&SPI0_TX_DATA;
    DMA_InitStruct.EN = ENABLE;
    DMA_Init(DMA_CHN1, &DMA_InitStruct);
}

/*******************************************************************************
 函数名称：    void SPI_Init(void)
 功能描述：    SPI硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           HMG               创建
 *******************************************************************************/
void SPI_init(void)
{
    SPI_InitTypeDef SPI_InitStruct;

    SPI_StructInit(&SPI_InitStruct);            // SPI结构体初始化
    SPI_InitStruct.Duplex = SPI_Half_Tx;        // 双工模式设置
    SPI_InitStruct.Mode = SPI_Master;           // master主机模式
    SPI_InitStruct.EN = ENABLE;                 // 使能SPI模块
    SPI_InitStruct.TRANS_MODE = SPI_DMA_ENABLE; // 选择SPI搬移方式，由MCU搬运数据到SPI
    SPI_InitStruct.Trig = 0;                    // 内部自动触发传输
    SPI_InitStruct.ENDIAN = SPI_FIRSTSEND_LSB;  // 该字节先发送 LSB
    SPI_InitStruct.CPHA = 0;                    // 第一个沿为发送数据时刻
    SPI_InitStruct.CPOL = 0;                    // CLK默认高电平
    SPI_InitStruct.BaudRate = 10;               // 传输速度96MHZ/(2*(31+1))= 1.50MHZ
    SPI_InitStruct.ByteLength = 8;              // 发送零个字节
    SPI_InitStruct.IRQEna = 0xf0;               // 关闭SPI各中断
    SPI_Init(SPI0, &SPI_InitStruct);            // SPI初始化程序
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

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/4/17      V1.1           Howlet Li          增加延时函数，等待PLL稳定
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;  /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 = BIT15;     /* BIT15:PLLPDN 开PLL */
    SoftDelay(100);           /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG = 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
    SYS_WR_PROTECT = 0;       /* 关闭系统寄存器写操作*/
}

/*******************************************************************************
 函数名称：    void Reg_Clr(void)
 功能描述：    寄存器清零
 输入参数：    addr ：需要清零寄存器的起始地址
               nSize：需要清零的寄存器个数
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/3/14      V1.0           Howlet Li          创建
 *******************************************************************************/
void Reg_Clr(u32 addr, u8 nSize)
{
    while (nSize--)
    {
        REG32(addr) = 0;
        addr += 4;
    }
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
    // SPI_DO P2.10
    // SPI_CLK P0.14
    // SPI_DO P2.3
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // 设置为输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_3;
    GPIO_SetBits(GPIO2,GPIO_Pin_3);
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_10, AF5_SPI); // GPIO2.10复用SPI_DO功能


    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // 设置为输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF5_SPI); // GPIO1.0复用SPI_CLK功能

}
