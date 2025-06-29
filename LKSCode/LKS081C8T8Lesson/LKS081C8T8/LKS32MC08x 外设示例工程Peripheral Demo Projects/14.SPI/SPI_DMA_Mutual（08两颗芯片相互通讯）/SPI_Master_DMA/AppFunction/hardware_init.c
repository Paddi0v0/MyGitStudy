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
    __disable_irq();                /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;        /* 使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000;        /* FLASH预取加速使能*/
    GPIO_init();                    /* GPIO初始化*/
    SPI_init();                     /* SPI初始化*/
	  SoftDelay(100);                 /* 等待硬件初始化完毕*/	
    NVIC_EnableIRQ(SPI0_IRQn);      /* 使能SPI中断*/
    NVIC_SetPriority(SPI0_IRQn, 1); /* SPI中断优先级配置*/
	  NVIC_EnableIRQ(DMA_IRQn);       /* 使能SPI中断*/
    NVIC_SetPriority(DMA_IRQn, 1);  /* SPI中断优先级配置*/
    SYS_WR_PROTECT = 0x0;           /* 关闭系统寄存器写操作*/
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
	  __enable_irq();                 /* 开启中断 */
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
    /*SPI初始化*/
    GPIO_StructInit(&GPIO_InitStruct);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //设置为输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_3;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_1, AF5_SPI);  //GPIO2.1复用SPI_clk功能
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_10, AF5_SPI); //GPIO2.10复用SPI_DO功能
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_3, AF5_SPI);  //GPIO2.3复用SPI_CS功能
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;            //设置为输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF5_SPI); //GPIO1.0复用SPI_DI功能
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

    SPI_StructInit(&SPI_InitStruct);              // SPI结构体初始化
    SPI_InitStruct.Duplex = SPI_Full;             //双工模式设置
    SPI_InitStruct.Mode = SPI_Master;             //master主机模式
    SPI_InitStruct.EN = ENABLE;                   //使能SPI模块
    SPI_InitStruct.DMA = SPI_DMA_ENABLE;          // 选择SPI搬移方式，由DMA搬运数据到SPI
    SPI_InitStruct.Trig = 0;                      //内部自动触发传输
    SPI_InitStruct.DataOrder = SPI_FIRSTSEND_LSB; //该字节先发送 MSB
    SPI_InitStruct.CPHA = 1;                      //第一个沿为发送数据时刻
    SPI_InitStruct.CPOL = 0;                      //CLK默认高电平
    SPI_InitStruct.BaudRate = 30;                 //传输速度96MHZ/(2*(30+1))= 1.548MHZ
    SPI_InitStruct.ByteLength = 1;                //发送零个字节
    SPI_InitStruct.IRQEna = DISABLE;              //关闭SPI各中断
    SPI_Init(SPI, &SPI_InitStruct);               //SPI初始化程序
	  					
    
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
void Spi_master_DMA(UINT8 *spi_txdma_data, UINT8 *spi_rxdma_data, u8 spi_len)
{
	  DMA_CTRL = 0x0000;                                         //关闭DMA使能	
	  spi_len = spi_len+1;
    SPI_SIZE = spi_len;                                      //SPI一轮发送spi_txdma_len字节
    DMA_CTMS2 = (((spi_len) << 16) & 0x00ff0000) | 0x00000001; //发送1轮，每轮1个字节
    DMA_CPAR2 = (u32)&SPI_TX_DATA;                             //SPI_TX_DATA
    DMA_CMAR2 = (u32)spi_txdma_data;                           //内存地址

    DMA_CCR2 = 0x2091; //BIT0:通道2使能,BIT4：传输方向外设至内存,BIT7：内存第二轮地址在第一轮上递增，
                       //BIT8~BIT9 = 0b00:外设访问位宽byte，BIT10~BIT11 = 0b00:内存访问位宽byte
                       //BIT12~BIT14 = 0b010:选择SPI_TX作为DMA_CH2触发信号

    DMA_CTMS1 = (((spi_len) << 16) & 0x00ff0000) | 0x00000001; //接收1轮，每轮一个字节
    DMA_CPAR1 = (u32)&SPI_RX_DATA;                             //SPI_RX_DATA
    DMA_CMAR1 = (u32)spi_rxdma_data;                           //内存地址

    DMA_CCR1 = 0x1081; //BIT0:通道2使能,BIT1:传输完成中断使能,BIT7：内存第二轮地址在第一轮上递增
                       //BIT8~BIT9 = 0b00:外设访问位宽byte，BIT10~BIT11 = 0b00:内存访问位宽byte
                       //BIT12~BIT14 = 0b001:选择SPI_RX作为DMA_CH1触发信号
	  DMA_CTRL = 0x0001; //DMA使能	

		SPI_TX_DATA = 0x00000000; //触发SPI传输完成标志位置位，使SPI_DMA搬移，
}


/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    按键处理函数
 输入参数：    mode:0,不支持连续按;1,支持连续按;
 输出参数：    无
 返 回 值：    0，没有任何按键按下
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/6/8      V1.0           HuangMG            创建
 *******************************************************************************/
int GPIO_KEY_Scan(u8 mode)
{
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(key_start ==0||key_stop==0))
	{
		SoftDelay(10);//去抖动 
		key_up=0;
		if(key_start==0)return start_PRES;
		else if(key_stop==0)return stop_PRES;
	}else if(key_start==1&&key_stop==1) key_up=1; 	    
 	return 0;// 无按键按下

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



