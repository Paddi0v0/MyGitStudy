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
 2023/02/12      V1.0           ywx          创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/
		IWDG_DISABLE();
		GPIO_init();
		SIF_init();    						/*SIF通讯初始化*/
		SoftDelay(100);           /*延时等待硬件初始化稳定 */
	  SYS_WR_PROTECT = 0x0;     /*关闭系统寄存器写操作*/
	  __enable_irq();           /* 开启总中断 */
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
    //配置SIF   单向通信引脚P0.14
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
	  GPIO_PinAFConfig(GPIO0,GPIO_PinSource_14,AF11_SIF);
}

/*******************************************************************************
 函数名称：    void SIF_init(void)
 功能描述：    SIF硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/02/12      V1.0           ywx          创建
 *******************************************************************************/
void SIF_init(void)
{
  SIF_InitTypeDef SIF_InitStruct;
  SIF_StructInit(&SIF_InitStruct); 
	
	SIF_InitStruct.SIF_DONE = DISABLE;			  // 传输完成后默认低电平 
	SIF_InitStruct.SIF_SYNC = DISABLE;			  // 同步信号默认低电平 
	SIF_InitStruct.SIF_SYNC_PULSE = ENABLE;		// 同步信号有电平反转 
	SIF_InitStruct.SIF_DONE_VLD = DISABLE;		// 无结束信号 
	SIF_InitStruct.SIF_SYNC_VLD = ENABLE;		  // 有同步信号
	SIF_InitStruct.SIF_RATIO = DISABLE;			  // 数据占空比 2：1 
	SIF_InitStruct.SIF_MSB = DISABLE;			    // 数据传送顺序 高字节在前 
	SIF_InitStruct.SIF_EN = ENABLE;				    // SIF模块使能 
	SIF_InitStruct.SIF_TOSC = 46;			    	  // 时基设置 47 * 333 = 15.67US 
	SIF_InitStruct.SIF_TSTH1 = 999;			  	  // 同步时长 1000 * SIF_TOSC * 32 
	SIF_InitStruct.SIF_TDTH1 = 0;				      // 结束信号时长 1MS 
	SIF_InitStruct.SIF_IRQ_IF = ENABLE;			  // 有SIF中断标志位 
	SIF_InitStruct.SIF_DMA_EN = ENABLE;			  // DMA传输使能 
	SIF_InitStruct.SIF_IRQ_EN = DISABLE;		  // SIF中断关闭 
	
	SIF_Init(SIF0, &SIF_InitStruct);
	
	/***设置时基单元****/
	SIF_Timebase_set(2);
	/*同步与结束时间信号周期设置*/
	SIF_TH_set(2,2);
}
/*******************************************************************************
 函数名称：    void  DMA_TxData(u8 *buff,u16 len)
 功能描述：    SIF硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/02/12      V1.0           ywx          创建
 *******************************************************************************/
extern  u8 SIF_BUFF[8];

void DMA_TxData(u8 *buff,u16 len)
{
	DMA_InitTypeDef DMA_InitStruct;
  DMA_StructInit(&DMA_InitStruct);
	
	DMA_InitStruct.EN = ENABLE;                                          // DMA通道使能
	DMA_InitStruct.IRQ_EN = ENABLE;                                      // DMA 传输完成中断使能 
	DMA_InitStruct.CIRC = DISABLE;                                       // DMA传输模式：循环模式，高有效 
	DMA_InitStruct.SINC = ENABLE;                                        // 源地址递增,  高有效,地址按照 SBTW 对应大小递增 1/2/4
	DMA_InitStruct.DINC = DISABLE;                                       // 目的地址递增,高有效,地址按照 DBTW 对应大小递增 1/2/4
	DMA_InitStruct.SBTW = DMA_BYTE_TRANS;                                // 源访问位宽， 0:byte, 1:half-word, 2:word 
	DMA_InitStruct.DBTW = DMA_BYTE_TRANS;                                // 目的访问位宽， 0:byte, 1:half-word, 2:word 
	DMA_InitStruct.REN.B.SIF_EN = ENABLE;                                // SIF DMA请求使能，高有效  
	DMA_InitStruct.TMS = len;                                            // DMA 通道 x 数据搬运次数 1~255 
	DMA_InitStruct.RMODE = 1;                                            // 0:单轮传输，一轮连续传输多次 / 1:多轮，每轮进行一次数据传输 
	DMA_InitStruct.SADR = (u32)buff;                                     // DMA 通道 x 源地址 &CAN0_TXBUF0
	DMA_InitStruct.DADR = (u32)&SIF0_WDATA;                              // DMA 通道 x 目的地址 CAN0_TXRX0 CAN0_RFIFO00
	DMA_Init(DMA_CHN0, &DMA_InitStruct);
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
 2023/02/12      V1.0           ywx          创建
 *******************************************************************************/
void UART1_init(void)
{
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
    SYS_CLK_CFG = 0x000001ff;    /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 ; 开
    启所有时钟*/
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




