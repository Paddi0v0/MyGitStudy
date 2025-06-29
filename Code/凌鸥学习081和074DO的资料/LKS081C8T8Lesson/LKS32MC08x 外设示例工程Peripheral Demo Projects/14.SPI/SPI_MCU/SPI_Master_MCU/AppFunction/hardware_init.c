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
	  SYS_WR_PROTECT = 0x0;           /* 关闭系统寄存器写操作*/
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
    __enable_irq();                 /* 开启中断 */
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
    SPI_InitStruct.DMA = SPI_DMA_DISABLE;         // 选择SPI搬移方式，由MCU搬运数据到SPI
    SPI_InitStruct.Trig = 0;                      //内部自动触发传输
    SPI_InitStruct.DataOrder = SPI_FIRSTSEND_MSB; //该字节先发送 MSB
    SPI_InitStruct.CPHA = 0;                      //第一个沿为发送数据时刻
    SPI_InitStruct.CPOL = 0;                      //CLK默认高电平
    SPI_InitStruct.BaudRate = 30;                 //传输速度96MHZ/(2*(30+1))= 1.548MHZ
    SPI_InitStruct.ByteLength = 0;                //发送零个字节
    SPI_InitStruct.IRQEna = DISABLE;              //关闭SPI各中断
    SPI_Init(SPI, &SPI_InitStruct);               //SPI初始化程序
}

/****************************************************************************************************
 函数名称：    void SPI_SendByte(u8 byte)
 功能描述：    SPI数据发送与接收函数
 输入参数：    byte:要发送的数据
             
 输出参数：    无
 返 回 值：    1字节接收数据
 其它说明：    每次发送完成SPI_SIZE硬件自动清零，每次发送时都要将SPI_SIZE置1.
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           HMG               创建
 ****************************************************************************************************/
u8 SPI_SendByte(u8 byte)
{
    u8 rdata = 0;

    SPI_SIZE = 1;       //SPI发送字节，MCU方式，只能写入1。
    SPI_TX_DATA = byte; //发送数据
    while (!(SPI_IE & BIT2))
    {
    };                   /*等待传输完成*/
    rdata = SPI_RX_DATA; //接收数据
    SPI_IE |= BIT2;      //清除SPI传输完成标志位
    return rdata;        //返回接收数据
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



