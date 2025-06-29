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


I2C_Parameter I2C_Par = {
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	NULL,
	NULL,
	0x01,
	0x01,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00};


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
    GPIO_init();      /* GPIO初始化 */
    I2C_init(10000);  /* IIC初始化 */
    SoftDelay(100);   /* 延时等待硬件初始化稳定 */
    NVIC_SetPriority(I2C0_IRQn, 0);
    NVIC_EnableIRQ(I2C0_IRQn);
	  SYS_WR_PROTECT = 0x0; /*关闭系统寄存器写操作*/
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
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
 函数名称：    void I2C_init(u32 div0)
 功能描述：    I2C硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/31      V1.0           YangZJ             创建
 *******************************************************************************/
void I2C_init(u32 div0)
{
    I2C_InitTypeDef I2C_InitStruct;
    I2C_StructInit(&I2C_InitStruct);
    
    I2C_InitStruct.ADRCMP           =   DISABLE ;   //  I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效。
    I2C_InitStruct.MST_MODE         =   ENABLE  ;   //  I2C 主模式使能
    I2C_InitStruct.SLV_MODE         =   DISABLE ;   //  I2C 从模式使能
    I2C_InitStruct.DMA              =   DISABLE  ;  //  I2C DMA传输使能
    I2C_InitStruct.BaudRate         =   div0 ;      //  I2C 波特率
    I2C_InitStruct.IE               =   ENABLE  ;   //  I2C 中断使能
    I2C_InitStruct.TC_IE            =   ENABLE  ;   //  I2C 数据传输完成中断使能
    I2C_InitStruct.BUS_ERR_IE       =   DISABLE ;   //  I2C 总线错误事件中断使能
    I2C_InitStruct.STOP_IE          =   ENABLE ;    //  I2C STOP 事件中断使能
    I2C_InitStruct.BURST_NACK       =   ENABLE  ;   //  I2C 传输，NACK 事件中断使能
    I2C_InitStruct.BURST_ADDR_CMP   =   DISABLE ;   //  I2C 传输，硬件地址匹配中断使能
    I2C_Init(I2C, &I2C_InitStruct);
    
	  I2C_Par.IIC_div_t = div0;/* 保存IIC波特率设置，在传输错误中断会重新继续硬件初始化*/
	  I2C_Par.Idle_RX_Flag = 1;/* I2C接收时检查空闲标志位初始化*/
	  I2C_Par.Idle_TX_Flag = 1;/* I2C发送时检查空闲标志位初始化*/
}
/*******************************************************************************
 函数名称：    u8 i2c_delay_txok(void)
 功能描述：    等待I2C发送完成
 输入参数：    无
 输出参数：    无
 返 回 值：    0：总线忙，!0：总线空闲
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/1/14      V1.0           HMG               创建
 *******************************************************************************/
u8 i2c_delay_txok(void)
{
	u16 t = 0;
	if (I2C_Par.Tran_Mode == I2C_TX_OR_RX)
	{
		while ((!I2C_Par.Idle_RX_Flag) || (!I2C_Par.Idle_TX_Flag)) // 等待I2C空闲;判断I2C_Par.FF置1
		{
			t++;
			if (t == 0xffff)
			{				 //避免程序卡死
				return 0xff; /*总线忙*/
			}
		}
	}
	else
	{
		while (!I2C_Par.Idle_TX_Flag) // 等待I2C空闲;判断I2C_Par.FF置1
		{
			t++;
			if (t == 0xffff)
			{				 //避免程序卡死
				return 0xff; /*总线空闲*/
			}
		}
	}
	I2C_Par.Idle_TX_Flag = 0;
	I2C_Par.Idle_RX_Flag = 0;
	return 0x0; /*发送成功*/
}
/*******************************************************************************
 函数名称：    u8 i2c_delay_rxok(void)
 功能描述：    等待I2C接收完成
 输入参数：    无
 输出参数：    无
 返 回 值：    0：总线忙，!0：总线空闲
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/1/14      V1.0           HMG               创建
 *******************************************************************************/
u8 i2c_delay_rxok(void)
{
	u16 t = 0;
	if (I2C_Par.Tran_Mode == I2C_TX_OR_RX)
	{
		while ((!I2C_Par.Idle_RX_Flag) || (!I2C_Par.Idle_TX_Flag)) // 等待I2C空闲;判断I2C_Par.FF置1
		{
			t++;
			if (t == 0xffff)
			{				 //避免程序卡死
				return 0xff; /*总线忙**/
			}
		}
	}
	else
	{
		while (!I2C_Par.Idle_RX_Flag) // 等待I2C空闲;判断I2C_Par.FF置1
		{
			t++;
			if (t == 0xffff)
			{				 //避免程序卡死
				return 0xff; /*总线空闲*/
			}
		}
	}
	I2C_Par.Idle_RX_Flag = 0;
	I2C_Par.Idle_TX_Flag = 0;
	return 0x0; /*发送成功*/
}
/*******************************************************************************
 函数名称：    u8 u8 I2C_TX_Function(u8 addr, u8* i2c_data , u32 len , u8 mode)
 功能描述：    I2C数据发送函数
输入参数：     addr:地址  i2c_data:发送数据缓冲区 len:发送字节个数
			  mode:IIC工作模式，1:主模式只接收或者只发送，2:主模式发送数据后立刻转为接收，
			  或者接收数据后立刻转为发送
 输出参数：    无
 返 回 值：    0：发送成功，!0：发送失败
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/1/14      V1.0           HMG               创建
 *******************************************************************************/
u8 I2C_TX_Function(u8 addr, u8 *i2c_data, u32 len, u8 mode)
{
	I2C_Par.Tran_Mode = mode;       //发送模式确认
	if (!i2c_delay_txok())          //等待I2C发送完成
	{
		I2C_Par.Data_Length_TX = len;
		I2C_Par.I2C_DATA_TX = i2c_data;
		I2C_Par.IIC_ADDR = addr << 1;
		I2C_Par.Data_Temp_Length_TX = 0;
		I2C0_DATA = I2C_Par.IIC_ADDR; // 地址信号
		I2C0_MSCR |= BIT0;			      // 触发I2C发送地址
		I2C_Par.I2C_Mode = 0;		      // 发送模式
		return 0x0;					          // 发送成功
	}
	else
	{
		return 0xff; /*发送失败*/
	}
}
/*******************************************************************************
 函数名称：    u8 u8 I2C_RX_Function(u8 addr, u8* i2c_data , u32 len , u8 mode)
 功能描述：    I2C数据接收函数
输入参数：     addr:地址  i2c_data:发送数据缓冲区 len:发送字节个数
			  mode:IIC工作模式，1:主模式只接收或者只发送，2:主模式发送数据后立刻转为接收，
			  或者接收数据后立刻转为发送
 输出参数：    无
 返 回 值：    0：发送成功，!0：发送失败
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/1/14      V1.0           HMG               创建
 *******************************************************************************/
u8 I2C_RX_Function(u8 addr, u8 *i2c_data, u32 len, u8 mode)
{
	I2C_Par.Tran_Mode = mode;
	if (!i2c_delay_rxok())
	{
		I2C_Par.IIC_ADDR = addr << 1;
		I2C_Par.Data_Length_RX = (len - 1);
		I2C_Par.I2C_DATA_RX = i2c_data;
		I2C_Par.Data_Temp_Length_RX = 0;
		I2C0_DATA = I2C_Par.IIC_ADDR | 0x01; // 地址信号
		I2C0_MSCR |= BIT0;					// 触发I2C发送地址
		I2C_Par.I2C_Mode = 1;				// 接收模式
		return 0x0;							// 发送成功
	}
	else
	{
		return 0xff; /*发送失败*/
	}
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



