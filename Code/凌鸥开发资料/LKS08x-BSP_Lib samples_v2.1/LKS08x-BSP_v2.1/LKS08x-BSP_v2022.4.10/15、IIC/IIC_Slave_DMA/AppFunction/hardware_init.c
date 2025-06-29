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
#include "hardware_config.h"
#include "lks32mc08x_i2c.h"
#include "lks32mc08x_DMA.h"

void IIC_init(u16 div0);
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

    GPIO_init();     /* GPIO初始化 */
    IIC_init(0x13f); /* GPIO初始化 */
    DMA_init();      /* GPIO初始化 */
    SoftDelay(100);  /* 延时等待硬件初始化稳定 */

    NVIC_SetPriority(I2C0_IRQn, 0);
    NVIC_EnableIRQ(I2C0_IRQn);
    NVIC_SetPriority(DMA_IRQn, 1);
    NVIC_EnableIRQ(DMA_IRQn);
    __enable_irq(); /* 开启总中断 */
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
	
    //P0.3 SCL P0.4 SDA
    GPIO0_PIE = 0x0018; // P0.3和P0.4输入使能
    GPIO0_POE = 0x0018; // P0.3和P0.4输出使能
	  GPIO_PinAFConfig(GPIO0,GPIO_PinSource_3,AF6_I2C); //P0.3  复用功能SCL
		GPIO_PinAFConfig(GPIO0,GPIO_PinSource_4,AF6_I2C); //P0.4  复用功能SDA
}

/*******************************************************************************
 函数名称：    void SPI_Init(void)
 功能描述：    SPI硬件部分初始化
 输入参数：    div0 IIC时钟分频系数
 输出参数：    无
 返 回 值：    无
 其它说明：    I2C 工作时钟=MCLK/(CLK_DIV0+1)。其中 MCLK 由 SYS_CLK_CFG 分频系数决定
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           HMG               创建
 *******************************************************************************/
void IIC_init(u16 div0)
{
    I2C_InitTypeDef I2C_InitStruct;
    I2C_StructInit(&I2C_InitStruct);

    I2C_InitStruct.ADRCMP = ENABLE;    //I2C地址按硬件比较，1:启用，0:禁用
    I2C_InitStruct.ADDR = 0x00;        //I2C地址，7位
    I2C_InitStruct.MASTER = DISABLE;   //I2C主模式，1:启用，0:禁用
    I2C_InitStruct.SLAVE = ENABLE;     //I2C从模式，1:启用，0:禁用
    I2C_InitStruct.DMA = ENABLE;       //I2C DMA传输方式，1:启用，0:禁用
    I2C_InitStruct.PREFETCH = DISABLE; //I2C从机预取启用，1:启用，0:禁用

    /*I2C一共有5个中断*/
    I2C_InitStruct.INTEN = ENABLE;      //I2C中断使能，1:启用，0:禁用
    I2C_InitStruct.NACKINT = ENABLE;    //I2C NACK中断启用，1:启用，0:禁用
    I2C_InitStruct.ADRCMPINT = DISABLE; //I2C地址比较硬件中断启用，1:启用，0:禁用
    I2C_InitStruct.DONEINT = ENABLE;    //I2C传输完成中断启用，1:启用，0:禁用
    I2C_InitStruct.BUSERRINT = DISABLE; //I2C总线错误中断启用，1:启用，0:禁用
    I2C_InitStruct.STOPINT = DISABLE;   //I2C停止事件中断启用，1:启用，0:禁用

    SYS_SoftResetModule(SYS_Module_I2C);
    I2C_Init(I2C, &I2C_InitStruct);

    SYS_WR_PROTECT = 0x7a83;  /*开启写操作*/
    SYS_CLK_DIV0 = div0;
		SYS_WR_PROTECT = 0x0000;  /*关闭写操作*/
}

/****************************************************************************************************
 函数名称：    void Spi_master_DMA(UINT8 *spi_txdma_data ，UINT8 *spi_rxdma_data, u32 spi_txdma_len)
 功能描述：    SPI数据发送与接收函数
 输入参数：    spi_txdma_data：发送数据内存地址
              spi_rxdma_data：接收数据内存地址
              spi_txdma_len : 发送字节数
 输出参数：    无
 返 回 值：    无
 其它说明：    本实验SPI配置为全双工，所以SPI一次发送len数据，同时接收数据也是len个，
              所以需要确保接收与发送缓冲区大小一致
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           HMG               创建
 ****************************************************************************************************/
void DMA_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;

    DMA_InitStruct.DMA_Channel_EN = DISABLE;        /* DMA 通道使能*/
    DMA_InitStruct.DMA_IRQ_EN = ENABLE;             /* DMA 中断使能 */
    DMA_InitStruct.DMA_DIR = 1;                     /* DMA传输方向 0:外设至内存， 1:内存至外设 */
    DMA_InitStruct.DMA_CIRC = DISABLE;              /* DMA传输模式：循环模式，高有效 */
    DMA_InitStruct.DMA_PINC = DISABLE;              /* 外设地址每轮内是否递增,高有效 */
    DMA_InitStruct.DMA_MINC = ENABLE;               /* 内存地址第二轮是否在第一轮地址的基础上递增,高有效 */
    DMA_InitStruct.DMA_PBTW = 0;                    /* 外设访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_MBTW = 0;                    /* 内存访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_CH3_I2C_REQ_EN; /* 通道 x 三个硬件 DMA 请求使能，高有效 */
    DMA_InitStruct.DMA_TIMES = 1;                   /* DMA 通道 x 每轮数据搬运次数 1~511 */
    DMA_InitStruct.DMA_ROUND = 0;                   /* DMA 通道 x 采样轮数 1~255 */
    DMA_InitStruct.DMA_CPAR = (u32)&I2C0_DATA;      /* DMA 通道 x 外设地址 */
    DMA_InitStruct.DMA_CMAR = 0;                    /* DMA 通道 x 内存地址 */
    DMA_Init(DMA_CH3, &DMA_InitStruct);
    DMA_IF = 0xff;
    DMA_IF = 0x00;
}
/*******************************************************************************
 函数名称：    void i2c_delay_ok(void)
 功能描述：    等待I2C完成
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           HMG               创建
 *******************************************************************************/
void i2c_delay_ok(void)
{
    u16 t = 0;
    while ((I2C0_SCR & BIT5) == 0) // 等待I2C空闲;判断有STOP事件
    {
        t++;
        if (t == 0x1fff)
        { //避免程序卡死
            return;
        }
    }
    I2C0_SCR &= ~BIT5;
}

void i2c_tx(u8 addr, u8 *data, u8 len)
{
    len = (len) ? len : 1;
    len = (len > 16) ? 16 : len;                      //输入限制，1-16
    i2c_delay_ok();                                   //等待I2C完成
    DMA_CCR3 &= ~BIT0;                                //关闭DAM_CH3使能
    DMA_CMAR3 = (u32)data;                            // DMA发送数据地址
    DMA_CTMS3 = ((len) << 16) | 1;                    // DMA搬运的数据长度
    DMA_CCR3 |= BIT4 | BIT0;                          // 配置DMA传输方向并使能DMA
    I2C0_ADDR = 0x80 | (addr & 0x7f);                 // 使能地址比较，并设置从设备地址
    I2C0_BCR = (I2C0_BCR & 0xf0) | ((len - 1) & 0xf); // 设定数据长度
    I2C0_SCR |= BIT2;                                 // I2C传输方向(发送)
    I2C0_SCR |= BIT4;                                 // 收到数据后进行ACK回应
    I2C0_BCR |= BIT4;                                 // I2C多数据传输。从模式执行DMA方式发送，触发硬件预取第一个字节。
    I2C0_MSCR = 1;                                    // 触发I2C发送数据
}

void i2c_rx(u8 addr, u8 *data, u8 len)
{
    len = (len) ? len : 1;
    len = (len > 16) ? 16 : len;                      //输入限制，1-16
    i2c_delay_ok();                                   //等待I2C完成
    DMA_CCR3 &= ~BIT0;                                //关闭DAM_CH3使能
    DMA_CMAR3 = (u32)data;                            // DMA接收数据地址
    DMA_CTMS3 = ((len) << 16) | 1;                    // DMA搬运的数据长度
    DMA_CCR3 &= ~BIT4;                                // DMA传输方向（外设至内存）
    DMA_CCR3 |= BIT0;                                 // 使能DMA
    I2C0_ADDR = 0x80 | (addr & 0x7f);                 // 使能地址比较，并设置从设备地址
    I2C0_BCR = (I2C0_BCR & 0xf0) | ((len - 1) & 0xf); // 设定数据长度
    I2C0_SCR |= BIT4;                                 // 收到数据后进行ACK回应
    I2C0_SCR &= ~BIT2;                                // I2C传输方向（接收）
    I2C0_MSCR = 1;                                    // 触发I2C发送数据
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
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;     /* BIT15:PLLPDN  BIT0:ADC_Clock*/
    SoftDelay(100);            /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG |= 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 ; 开启所有时钟*/
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
 功能描述：    延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/31      V1.0            HMG               创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}
