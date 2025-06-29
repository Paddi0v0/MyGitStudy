/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Olive Wang
 * 完成日期： 2023年02月22日
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
2023/02/22     V1.0           Olive Wang          创建
*******************************************************************************/
void Hardware_init(void)
{
  __disable_irq();         /* 关闭中断 中断总开关 */
  SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
  FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/
  IWDG_DISABLE();                   /* 关闭看门狗*/	
	GPIO_init();					 /* GPIO初始化 */
  HALL_init();           /* HALL初始化 */
  SoftDelay(100);          /* 等待硬件初始化完毕*/
	NVIC_EnableIRQ(HALL0_IRQn); /*使能MCPWM中断*/
  NVIC_SetPriority(HALL0_IRQn, 3);
	SYS_WR_PROTECT = 0x0;      /*关闭系统寄存器写操作*/
  __enable_irq();          /* 开启中断 */
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
2023/02/22       V1.0           Olive Wang          创建
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 = BIT15;      /* BIT15:PLLPDN 开PLL */
    SoftDelay(100);            /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG = 0x000001ff;  /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
    SYS_WR_PROTECT = 0;        /* 关闭系统寄存器写操作*/
}
/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    GPIO配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22       V1.0           Olive Wang          创建
 *******************************************************************************/

void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
	
		//配置按键 start：P2.11  stop:P2.11
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIO2, &GPIO_InitStruct);
		//配置LED1：P0.6  LED2：P0.7  LED3: P0.3
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIO0, &GPIO_InitStruct);
	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
	
   //GPIO_P0.11/P0.12/P0.13设置为HALL_IN0/HALL_IN1/HALL_IN2模拟通道
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF2_HALL);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF2_HALL);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_6, AF2_HALL);
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
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
void SystemInit(void)
{
  Clock_Init(); /* 时钟初始化 */
}

/*******************************************************************************
 函数名称：    void HALL_init(void)
 功能描述：    HALL初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
void HALL_init(void)
{	
	  HALL_InitTypeDef HALL_InitStruct;
   
    HALL_StructInit(&HALL_InitStruct);
	
    HALL_InitStruct.FilterLen = 512;                /* Hall信号数字滤波长度 512个时钟周期 */
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV8;  /* 设置Hall模块时钟分频系数 */
    HALL_InitStruct.Filter75_Ena = DISABLE;         /* Hall信号滤波方式，7判5模式或者全1有效模式 */
    HALL_InitStruct.HALL_Ena = ENABLE;              /* 模块使能 */
    HALL_InitStruct.Capture_IRQ_Ena = ENABLE;       /* 捕捉中断使能 */
    HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;      /* 超时中断使能 */
    HALL_InitStruct.CountTH = 960000;              /* Hall模块计数模值，计数超过模值会产生超时中断 */
		HALL_InitStruct.softIE = ENABLE;								 /* 软件中断失能 */
	
    HALL_Init(&HALL_InitStruct);/* HALL初化 */
		HALL_Cmd(ENABLE);/* HALL使能 */
}

/*******************************************************************************
 函数名称：    int GPIO_KEY_Scan(u8 mode)
 功能描述：    按键处理函数
 输入参数：    mode:0,不支持连续按;1,支持连续按;
 输出参数：    无
 返 回 值：    0，没有任何按键按下
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang            创建
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
2023/02/22       V1.0           Olive Wang          创建
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
2023/02/22     V1.0          Olive Wang             创建
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

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
