/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： HuangMG
 * 完成日期： 2023年3月2日
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
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();                  /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;
    
    FLASH_CFG |= 0x00080000;          /* enable prefetch */
    IWDG_DISABLE();                   /* 关闭看门狗*/
	  GPIO_init();                      /* UTimer初始化 */
	  UTimer_init();                    /* UTimer初始化 */
  	SoftDelay(100);                   /* 等待硬件初始化完毕*/
	  NVIC_SetPriority(TIMER0_IRQn, 0); /*TIMER0中断优先级配置*/
    NVIC_EnableIRQ(TIMER0_IRQn);      /*使能UTimer定时器中断*/
	  NVIC_SetPriority(TIMER3_IRQn, 1); /*TIMER3中断优先级配置*/
    NVIC_EnableIRQ(TIMER3_IRQn);      /*使能UTimer定时器中断*/
    SYS_WR_PROTECT = 0;               /* 关闭系统寄存器写操作*/
    __enable_irq();                   /* 开启总中断 */
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
 2023/3/2      V1.0          HuangMG            创建
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
 函数名称：    void Reg_Clr(void)
 功能描述：    寄存器清零
 输入参数：    addr ：需要清零寄存器的起始地址 
               nSize：需要清零的寄存器个数
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void Reg_Clr(u32 addr, u8 nSize)
{
   while(nSize --)
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
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void SystemInit(void)
{
    Clock_Init();  /* 时钟初始化 */
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
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体

    //配置P2.7 UTIMER0_CH0  
	  GPIO_StructInit(&GPIO_InitStruct); //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
	  GPIO_PinAFConfig(GPIO2,GPIO_PinSource_7,AF7_TIMER01); //P2.7复用为timer0的输出模式
		
	  //配置P2.11 UTIMER2_CH0 作为UTIMER3的外部时钟输入口
	  GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;  //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
		GPIO_PinAFConfig(GPIO2,GPIO_PinSource_11,AF8_TIMER23); //P2.11复用为timer2_CH0的输入模式
		
	  //配置P1.3 UTIMER3_CH1
	  GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1,GPIO_PinSource_3,AF8_TIMER23); //P3.1复用为timer3的输出模式
}

/*******************************************************************************
 函数名称：    void UTimer_init(void)
 功能描述：    UTimer硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void UTimer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerStrutInit(&TIM_InitStruct);                  /* Timer结构体初始化*/
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 48000;    									/* 定时器计数门限初始值48000*/
    TIM_InitStruct.Timer_CMP0 = 24000;  									/* 设置比较模式的CH0比较初始值24000 */
    TIM_InitStruct.Timer_CMP1 = 24000;  									/* 设置比较模式的CH1比较初始值24000 */
    TIM_InitStruct.Timer_FLT = 0;  										    /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;       /* 设置Timer模块时钟2分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | Timer_IRQEna_ZC; /* 开启Timer模块比较中断和过零中断*/
    TIM_TimerInit(UTIMER0, &TIM_InitStruct); 
    TIM_TimerCmd(UTIMER0, ENABLE);                        /* Timer0 模块使能 */	
	  
	  TIM_TimerStrutInit(&TIM_InitStruct);                   /* Timer结构体初始化*/
/********************使用定时器2的通道0，作为定时器3的外部时钟配置程序*********************/	
    TIM_InitStruct.Timer_XCLK_EN = ENABLE;                /*设置定时器3时钟使用外部时钟*/
	  TIM_InitStruct.Timer_EVT = TIMER2_EVT_CH0;            /*设置定时器3的外部时钟来源于定时器2的通道0口输入的信号*/
    SYS_ModuleClockCmd(SYS_Module_TIMER2, ENABLE);        /*使能定时器2的时钟门控，用于对定时器2输入信号滤波*/
		UTIMER2_FLT = 0;                                      /*设置定时器通道的数字滤波值*/
		UTIMER2_CFG |= 0x00<<4;                               /*设置定时器2的信号捕获模式通道0信号来源于该定时器的通道0*/
/********************定时器3通道1输出PWM波形配置程序*********************/			
	  TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 500;    									  /* 定时器计数门限初始值48000*/
    TIM_InitStruct.Timer_CMP0 = 250;  									  /* 设置比较模式的CH0比较初始值24000 */
    TIM_InitStruct.Timer_CMP1 = 250;  									  /* 设置比较模式的CH1比较初始值24000 */
    TIM_InitStruct.Timer_FLT = 0;  										    /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV2;       /* 设置Timer模块时钟2分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | Timer_IRQEna_ZC; /* 开启Timer模块比较中断和过零中断*/
    TIM_TimerInit(UTIMER3, &TIM_InitStruct); 
    TIM_TimerCmd(UTIMER3, ENABLE);                        /* Timer3 模块使能 */
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
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}




