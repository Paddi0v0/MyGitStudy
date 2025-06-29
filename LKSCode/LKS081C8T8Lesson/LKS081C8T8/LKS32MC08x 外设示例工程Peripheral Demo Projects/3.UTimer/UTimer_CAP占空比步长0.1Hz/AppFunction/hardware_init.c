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

stru_PWMFreqCat  gS_PWMFreqCat;
/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/25      V1.0          HuangMG            创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();                  /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;          /* 使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000;          /* enable prefetch ，FLASH预取加速使能*/
    GPIO_init();                      /* GPIO初始化 */
    UTimer_init();                    /* UTimer初始化 */
	  SoftDelay(100);                   /* 等待硬件初始化完毕*/
    NVIC_SetPriority(TIMER3_IRQn, 0); /* TIMER0中断优先级配置必须最高*/
    NVIC_EnableIRQ(TIMER3_IRQn);      /* 使能UTimer定时器中断*/
	  SYS_WR_PROTECT = 0x0;             /*关闭系统寄存器写操作*/
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif
    __enable_irq();                   /* 开启中断 */
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
 2021/8/25      V1.0         HuangMG             创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体

    /* 配置LED1：P0.6  LED2：P0.7  LED3: P0.3*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    /* P2.8 PWM调速信号输入*/
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;//GPIO输入模式
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
		GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF8_TIMER23);//P2.8复用UTIMER3_CH0
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
 函数名称：    void UTimer_init(void)
 功能描述：    UTimer硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTimer_init(void)
{
	  TIM_TimerInitTypeDef TIM_InitStruct;
    TIM_TimerStrutInit(&TIM_InitStruct);
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP;      /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_RiseFall; /*双沿捕获*/
    TIM_InitStruct.Timer_TH = 9600000;                         /* 设置计数器计数模值 */
    TIM_InitStruct.Timer_CMP0 = 0;                             /* 设置比较模式的CH0比较值 */
    TIM_InitStruct.Timer_Filter0 = 15;                         /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1;              /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_Zero;/* 开启Timer模块CH0捕获中断 */
    TIM_TimerInit(TIMER3, &TIM_InitStruct);
		TIM_TimerCmd(TIMER3, ENABLE);                          /* Timer3 模块使能 */
}

/*******************************************************************************
 函数名称：    RAM_FUNC void Utimer3_CapFrwq(u8 * temp)
 功能描述：    utimer捕获输入PWM占空比函数
 输入参数：    temp：判断0%和100%极限占空比标志位
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/6/14      V1.0           HuangMG           创建
 *******************************************************************************/
RAM_FUNC void Utimer3_CapFrwq(u8* temp)
{
		static u32 InPut_1 = 0;
		static u32 InPut_2 = 0;
		static u8  Clear_Cntflag = 0;
		static u8  Start_flag = 0;        //捕获第一个上升沿标志
  		if(Clear_Cntflag == 0)
		{
			*temp = 1;
			gS_PWMFreqCat.LEVEL_HL = 0;
			Clear_Cntflag = 1;
			Start_flag = 0;
			UTIMER_UNT3_CNT = 0;		
		}else{
			 
			 switch(Start_flag)
			 {
				 case 0: 
					 if((SPsetup_Voltage != 0))//第一个是上升沿
						{
							InPut_1 = UTIMER_UNT3_CMP0;			
						}else{  //第一个是下升沿
							Start_flag = 2;
							InPut_1 = UTIMER_UNT3_CMP0;	
						}
				 break;
				 case 1: 
							InPut_2 = UTIMER_UNT3_CMP0;		
				 break;
				 case 2: 
							gS_PWMFreqCat.InPut_risitimevalue  = InPut_2 - InPut_1;//高电平计数值
							gS_PWMFreqCat.InPut_falltimevalue = UTIMER_UNT3_CMP0 - InPut_2;//低电平计数值
							Clear_Cntflag = 0;
				 break;
				 case 3: 
							InPut_2 = UTIMER_UNT3_CMP0;		
				 break;
				 case 4: 
							gS_PWMFreqCat.InPut_risitimevalue  = UTIMER_UNT3_CMP0 - InPut_2;//高电平计数值
							gS_PWMFreqCat.InPut_falltimevalue = InPut_2 - InPut_1;//低电平计数值
							Clear_Cntflag = 0;	 
				 break;			 
			 }
				Start_flag++;		 
			}

}


/*******************************************************************************
 函数名称：    void Voltage_Control(void)
 功能描述：    UTIMER捕获PWM占空比
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0          HuangMG          创建
 *******************************************************************************/
void Voltage_Control(void)
{

  float Duty_Ratio = 0;

	if(gS_PWMFreqCat.LEVEL_HL == 1)     /*超出最大占空比*/
	{
		 Duty_Ratio = 1000;
	}else if(gS_PWMFreqCat.LEVEL_HL == 2)/*超出最小占空比*/
	{
		 Duty_Ratio  = 0;
	
	}
	else{	
	  Duty_Ratio = (((float)gS_PWMFreqCat.InPut_risitimevalue)/(gS_PWMFreqCat.InPut_risitimevalue + gS_PWMFreqCat.InPut_falltimevalue)*1000)+1;      		 
  }
	  gS_PWMFreqCat.InPut_DutyCycle = (u16)Duty_Ratio;			
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
 函数名称：    void Invers_GPIO(void)
 功能描述：    LED电平翻转函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  u16 reg;
	reg = GPIO_ReadOutputDataBit(GPIOx,GPIO_Pin);//读GPIO电平
	if(reg)
	{
		GPIO_ResetBits(GPIOx,GPIO_Pin);
		return 0;
	}
	else
	{
		GPIO_SetBits(GPIOx,GPIO_Pin);
		return 1;
	}
}




