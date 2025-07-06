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


can_parameter can_par =
{
        0x00,
        0x00,
        0x00,
        {0, 0},
        {0, 0},
        0x00,
};
		
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
    SYS_WR_PROTECT = 0x7a83;       /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000;       /* enable prefetch ，FLASH预取加速使能*/
    GPIO_init();                   /* GPIO初始化*/
    CAN_init();                    /* CAN初始化*/
	  SoftDelay(100);                /* 延时等待硬件初始化稳定 */
	  NVIC_EnableIRQ(DMA_IRQn);      /* 使能DMA中断 */
    NVIC_SetPriority(DMA_IRQn, 1); /* 配置DMA中断优先级*/	
	  SYS_WR_PROTECT = 0x0;          /*关闭系统寄存器写操作*/
	
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
    __enable_irq();                /* 开启中断 */
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
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体

	  //配置按键 start：P2.11  stop:P2.11
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;//GPIO输入模式
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);	
	  //配置LED1：P0.6  LED2：P0.7  LED3: P0.3
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//GPIO输出模式
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);	
		
	  /*P0.7 CAN TX*/
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    /*P0.6 CAN RX*/
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF10_CAN);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF10_CAN);
}
/*******************************************************************************
 函数名称: void CAN_init(void)
 功能描述: CAN初始化函数,采用2.0B协议
 操作的表:  Can波特率      BTR0    	BTR1
            1Mbps 		  0x05      0x14
            800Kbps 	  0x05      0x16
            666Kbps 	  0x85 	    0xB6
            500Kbps 	  0x05      0x1C
            400Kbps 	  0x05	    0xFA
            250Kbps 	  0x0B 	    0x1C
            200Kbps 	  0x05 	    0xFA
            125Kbps 	  0x17      0x1C
            100Kbps 	  0x1D      0x1C
            83.33Kbps 	0x17      0x6F
            80Kbps 		  0x97      0xFF
            66.66Kbps 	0x1D      0x6F
            50Kbps 		  0x3B      0x1C
            40Kbps 		  0xAF      0xFF
 输入参数: 无
 输出参数: 无
 返回值:   无
 其它说明:
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/5/3      V1.0           HuangMG            创建
*******************************************************************************/
void CAN_init(void)
{
    CAN_InitTypeDef CAN_InitStruct;
    CAN_StructInit(&CAN_InitStruct);
    /*Can波特率:500Kbps*/
    CAN_InitStruct.CAN_Btr0 = 0x05;
    CAN_InitStruct.CAN_Btr1 = 0x1C;
    CAN_InitStruct.CAN_DMAEn = ENABLE;               /*DMA搬运数据*/
    CAN_InitStruct.CAN_WorkMode = CAN_SELFTEST_MODE; /*CAN正常收发工作模式*/
	  CAN_InitStruct.CAN_ErrWarThre = 50;              /*错误与警告门限值为50*/
    CAN_InitStruct.IRQEna = CAN_IE_RFIFONOEMPTY | CAN_IE_TXDONE | CAN_IE_WERR;
    CAN_Init(CAN, &CAN_InitStruct);
    /*接收滤波： ID:0x5A ,标志帧，BYTE1:0x81,BYTE:0x23*/
    SFF_ID_Filter(0X5A, 0x00, 0x0, 0x0, 0x81, 0x00, 0x23, 0x00);
}

/*******************************************************************************
 函数名称：    void CAN_DMA_RX(u8 ide , u8 frame_number,u8 frame_size ,  u8* memaddr)
 功能描述：    CAN_DMA数据接收函数
 输入参数：    ide：0标准/1扩展帧
              frame_number：需要接收的帧个数
              frame_size：每帧接收数据长度（0-8 BYTE）数据，不含ID等。
              memaddr：接收数据缓冲区地址
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/5/4      V1.0           HuangMG            创建
 *******************************************************************************/
void CAN_DMA_RX(u8 ide , u8 frame_number,u8 frame_size ,  u8* memaddr)
{ 
	  u8 len = 0 , rgsr = 0;
	  DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
	  if(ide)/*扩展帧*/
		{
		  len = 5+frame_size;
		}else{ /*标准帧*/
			len = 3+frame_size;
		}
    DMA_InitStruct.DMA_IRQ_EN = DMA_TCIE;             /* DMA 传输完成中断使能 */
    DMA_InitStruct.DMA_DIR = PERI2MEMORY;             /* 外设至内存 */
    DMA_InitStruct.DMA_CIRC = DISABLE;                /* DMA传输模式：循环模式，高有效 */
    DMA_InitStruct.DMA_PINC = ENABLE;                 /* 外设地址每轮内是否递增,高有效 */
    DMA_InitStruct.DMA_MINC = ENABLE;                 /* 内存地址第二轮是否在第一轮地址的基础上递增（轮内地址一定递增）,高有效 */
    DMA_InitStruct.DMA_PBTW = DMA_BYTE_TRANS;         /* 外设访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_MBTW = DMA_BYTE_TRANS;         /* 内存访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_CH3_CAN_REQ_EN;   /* CAN DMA请求使能，高有效 */
    DMA_InitStruct.DMA_TIMES = len;                   /* DMA 通道 x 每轮数据搬运次数 1~511 */
    DMA_InitStruct.DMA_ROUND = frame_number;          /* DMA 通道 x 采样轮数 1~255 */
    DMA_InitStruct.DMA_CPAR = (u32)&CAN_TXRX0;        /* DMA 通道 x 外设地址 */
    DMA_InitStruct.DMA_CMAR = (u32)memaddr;           /* DMA 通道 x 内存地址 */
    DMA_Init(DMA_CH3, &DMA_InitStruct);
/*******************清除触发DMA数据搬运标志位，防止误接收数据触发DMA搬运*****************/
    rgsr =CAN_GetIRQFlag();                           /*读取中断状态寄存器*/
    rgsr = rgsr;                                      /*防止编译报警告*/
/************************************************************************************/		
    DMA_CHx_EN(DMA_CH3,ENABLE);                       /*使能DMA_CH3通道*/
};

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
