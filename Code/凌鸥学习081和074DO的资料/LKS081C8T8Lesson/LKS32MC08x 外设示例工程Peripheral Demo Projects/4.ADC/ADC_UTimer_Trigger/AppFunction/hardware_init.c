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
 2021/8/27      V1.0           HuangMG           创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/
    GPIO_init();             /* GPIO初始化 */
    UTimer_init();           /* UTimer初始化 */
    ADC0_init();             /* ADC初始化 */
	  SoftDelay(100);          /* 等待硬件初始化完毕*/
	  NVIC_SetPriority(ADC0_IRQn, 0); //ADC0中断优先级配置
    NVIC_EnableIRQ(ADC0_IRQn);      //使能ADC0中断
	  SYS_WR_PROTECT = 0x0;    /*关闭系统寄存器写操作*/
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    //配置LED1：P0.6  LED2：P0.7  LED3: P0.3
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    /* 配置UTimer0  TIM0_CH1: P0.14   TIM0_CH0: P0.15 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0,GPIO_PinSource_14,AF7_TIMER01); //P0.15复用为timer0的输出模式
    GPIO_PinAFConfig(GPIO0,GPIO_PinSource_15,AF7_TIMER01); //P0.15复用为timer0的输出模式
}

/*******************************************************************************
 函数名称：    void ADC0_init(void)
 功能描述：    ADC0硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#define ADC_MODE1 1 //一，二，四段模式触发选择
#define ADC_MODE2 0 //一，二，四段模式触发选择
#define ADC_MODE4 0 //一，二，四段模式触发选择

#if ADC_MODE1
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure); //初始化结构体

    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN | ADC_DAT0_OV_IRQ_EN; //第一段扫描结束中断使能和ADC_DAT0超阈值中断
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;                    //ADC数据输出左对齐
    ADC_InitStructure.UTIMER_Trigger_En = ADC_UTIMER_T0_TRG;     //UTIMER_T0硬件触发ADC采样
    ADC_InitStructure.MCPWM_Trigger_En = DISABLE;                //关闭MCPWM的硬件中断
    ADC_InitStructure.FirSeg_Ch = ADC_2_TIMES_SAMPLE;            //第一段采样的总通道数: 1~20
    ADC_InitStructure.Trigger_Cnt = 0;                           /*单段触发模式下触发一次采样所需要的事件数:0~15 0表示需要一次触发，15表示需要16次*/
    ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;               /*ADC采样1段模式*/
    ADC_InitStructure.DAT0_TH_Type = 1;                          //设置ADC比较上阈值中断
    ADC0_DAT0_TH = 5000;                                         //设置ADC0_DARA0大于ADC0_DAT0_TH值时，触发ADC数值比较中断
    ADC_Init(ADC0, &ADC_InitStructure);

    ADC0_IF = 0xff;                                   //清中断标志位
    ADC0_GAIN0 = 0x0;                                 //开启2/3增益
    ADC0_CHN0 = ADC_CHANNEL_9 | (ADC_CHANNEL_9 << 8); //采样电位器分压值                                                 

}
#endif
#if ADC_MODE2
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure); //初始化结构体

    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN | ADC_EOS1_IRQ_EN;                    //第一段扫描结束中断使能
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;                                    //ADC数据输出左对齐
    ADC_InitStructure.UTIMER_Trigger_En = ADC_UTIMER_T0_TRG | ADC_UTIMER_T1_TRG; //UTIMER_T0硬件触发ADC采样
    ADC_InitStructure.MCPWM_Trigger_En = DISABLE;                                //关闭MCPWM的硬件中断
    ADC_InitStructure.FirSeg_Ch = ADC_2_TIMES_SAMPLE;                            //第一段采样的总通道数: 1~20
    ADC_InitStructure.SecSeg_Ch = ADC_2_TIMES_SAMPLE;                            //第二段采样的总通道数: 1~20
                                                                                 //  ADC_InitStructure.Trigger_Cnt = 0; /*单段触发模式下触发一次采样所需要的事件数:0~15 0表示需要一次触发，15表示需要16次*/
    ADC_InitStructure.Trigger_Mode = ADC_2SEG_TRG;                               /*ADC采样2段模式*/

    ADC_Init(ADC0, &ADC_InitStructure);

    //	  ADC0_CHN0 = ADC_CHANNEL_8|(ADC_CHANNEL_8<<8);          //采样通道通道1
    ADC0_IF = 0xff;   //清中断标志位
    ADC0_GAIN0 = 0x0; //开启2/3增益
    ADC0_CHN0 = ADC_CHANNEL_9 | (ADC_CHANNEL_9 << 8);
    ADC0_CHN1 = ADC_CHANNEL_9 | (ADC_CHANNEL_9 << 8);
    //	  ADC0_TRIG=0x4010;

}
#endif
#if ADC_MODE4
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure); //初始化结构体

    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN | ADC_EOS1_IRQ_EN | ADC_EOS2_IRQ_EN | ADC_EOS3_IRQ_EN;                        //第一二四段扫描结束中断使能
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;                                                                            //ADC数据输出左对齐
    ADC_InitStructure.UTIMER_Trigger_En = ADC_UTIMER_T0_TRG | ADC_UTIMER_T1_TRG | ADC_UTIMER_T2_TRG | ADC_UTIMER_T3_TRG; //UTIMER_T0硬件触发ADC采样
    ADC_InitStructure.MCPWM_Trigger_En = DISABLE;                                                                        //关闭MCPWM的硬件中断
    ADC_InitStructure.FirSeg_Ch = ADC_1_TIMES_SAMPLE;                                                                    //第一段采样的总通道数: 1~20
    ADC_InitStructure.SecSeg_Ch = ADC_1_TIMES_SAMPLE;                                                                    //第二段采样的总通道数: 1~20
    ADC_InitStructure.ThrSeg_Ch = ADC_1_TIMES_SAMPLE;                                                                    //第三段采样的总通道数: 1~20
    ADC_InitStructure.FouSeg_Ch = ADC_1_TIMES_SAMPLE;                                                                    //第四段采样的总通道数: 1~20
                                                                                                                         //  ADC_InitStructure.Trigger_Cnt = 0; /*单段触发模式下触发一次采样所需要的事件数:0~15 0表示需要一次触发，15表示需要16次*/
    ADC_InitStructure.Trigger_Mode = ADC_4SEG_TRG;                                                                       /*ADC采样2段模式*/

    ADC_Init(ADC0, &ADC_InitStructure);

    //	  ADC0_CHN0 = ADC_CHANNEL_8|(ADC_CHANNEL_8<<8);          //采样通道通道1
    ADC0_IF = 0xff;   //清中断标志位
    ADC0_GAIN0 = 0x0; //开启2/3增益
    ADC0_CHN0 = ADC_CHANNEL_9 | (ADC_CHANNEL_9 << 8);
    ADC0_CHN1 = ADC_CHANNEL_9 | (ADC_CHANNEL_9 << 8);
    //	  ADC0_TRIG=0x4010;
}
#endif


/*******************************************************************************
 函数名称：    void UTimer_init(void)
 功能描述：    UTimer硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/27      V1.0           HMG              创建
 *******************************************************************************/
void UTimer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerCmd(TIMER2, ENABLE);                         /* Timer2 模块使能 */
    TIM_TimerStrutInit(&TIM_InitStruct);                  //Timer结构体初始化
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH0Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH1Output = 0; /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 48000;    /* 定时器计数门限初始值1000*/
    TIM_InitStruct.Timer_CMP0 = 24000;  /* 设置比较模式的CH0比较初始值500 */
    TIM_InitStruct.Timer_CMP1 = 24000;  /* 设置比较模式的CH1比较初始值500 */
    TIM_InitStruct.Timer_Filter0 = 0;   /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_Filter1 = 0;
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div2;                                          /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | Timer_IRQEna_Zero; /* 开启Timer模块比较中断和过零中断*/
    TIM_TimerInit(TIMER2, &TIM_InitStruct);

    TIM_TimerCmd(TIMER3, ENABLE);                         /* Timer3 模块使能 */
    TIM_TimerStrutInit(&TIM_InitStruct);                  //Timer结构体初始化
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH0Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH1Output = 0; /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 48000;    /* 定时器计数门限初始值1000*/
    TIM_InitStruct.Timer_CMP0 = 24000;  /* 设置比较模式的CH0比较初始值500 */
    TIM_InitStruct.Timer_CMP1 = 24000;  /* 设置比较模式的CH1比较初始值500 */
    TIM_InitStruct.Timer_Filter0 = 0;   /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_Filter1 = 0;
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div2;                                          /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | Timer_IRQEna_Zero; /* 开启Timer模块比较中断和过零中断*/
    TIM_TimerInit(TIMER3, &TIM_InitStruct);
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






