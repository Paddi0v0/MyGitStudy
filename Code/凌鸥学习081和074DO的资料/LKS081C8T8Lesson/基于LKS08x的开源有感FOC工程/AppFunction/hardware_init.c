#include "global_variable.h"
#include "hardware_config.h"
#include "function_config.h" 

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
    __disable_irq();/* 关闭中断 中断总开关 */
	SYS_WR_PROTECT = 0x7a83;

    FLASH_CFG |= 0x00080000; /* enable prefetch */

	DSP_Init();                       	/* DSP模块初始化*/
	ADC_init();    						/* ADC初始化 */
	MCPWM_init();   					/* PWM初始化 */
    UTimer_init(); 						/* 通用计数器初始化 */
    GPIO_init();    					/* GPIO初始化 */
    DAC_init();                       	/* DAC 初始化 */
    PGA_init();                       	/* PGA 初始化 */
    CMP_init();                       	/* 比较器初始化 */
    HALL_Perip_Init();                	/* HALL模块初始化 */
	
	SoftDelay(100);                   	/* 延时等待硬件初始化稳定 */

    DSP_SC = BIT1; /* DSP Paused */

    NVIC_SetPriority(ADC0_IRQn, 1);
    NVIC_SetPriority(HALL_IRQn, 2);
    NVIC_SetPriority(CMP_IRQn, 0);
    NVIC_SetPriority(TIMER0_IRQn, 2);

    NVIC_EnableIRQ(ADC0_IRQn);   /* enable the ADC0 interrupt */
    NVIC_EnableIRQ (TIMER0_IRQn);
    NVIC_EnableIRQ (CMP_IRQn);
	
    __enable_irq();/* 开启中断 */
}

/*******************************************************************************
 函数名称：    void DSP_Init(void)
 功能描述：    DSP时钟使能
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/6/28      V1.0           cfwu          创建
 *******************************************************************************/

void DSP_init(void)
{
	SYS_CLK_FEN |= SYS_Module_DSP;
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

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/4/17      V1.1           Howlet Li          增加延时函数，等待PLL稳定
 *******************************************************************************/

void Clock_init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;     /* BIT15:PLLPDN 开PLL */
    SoftDelay(100);            /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG |= 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
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
 2021/3/14      V1.0           Howlet Li          创建
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
 2016/3/14      V1.0           Howlet Li          创建
 *******************************************************************************/

void SystemInit(void)
{
    Clock_init();  	/* 时钟初始化 */
}

/*******************************************************************************
 函数名称：    void TempSensor_Init(void)
 功能描述：    温度传感器初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void TempSensor_Init(void)
{

    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT13;     /* 打开温度传感器开关 */
  
    m_TempertureCof.nCofA    = Read_Trim(0x00000398);
    m_TempertureCof.nOffsetB = Read_Trim(0x0000039C);

}

/*******************************************************************************
 函数名称：    void PGA_Init(void)
 功能描述：    PGA初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/15      V1.0           Howlet Li          创建
 *******************************************************************************/

void PGA_init(void)
{
	SYS_AFE_REG5 |= 0x20ff;
    
    SYS_AFE_REG0 = OPA0_GIAN | OPA1_GIAN | OPA2_GIAN | OPA3_GIAN; /* 4个OPA增益设置 */ 
}

/*******************************************************************************
 函数名称：    void CMP_Init(void)
 功能描述：    比较器初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/15      V1.0           Howlet Li          创建
 *******************************************************************************/

void CMP_init(void)
{
//    CMP_InitTypeDef CMP_InitStruct;

//    CMP_StructInit(&CMP_InitStruct);

//    CMP_InitStruct.CMP0_EN = ENABLE;
//    CMP_InitStruct.CMP0_SELN = SELN_DAC;		/* 负端连接芯片内部DAC */
//    CMP_InitStruct.CMP0_SELP = SELP_CMP_IP0;	/* 正端连接IP0输入 */

//    CMP_InitStruct.CMP0_IE = ENABLE;			/* 比较器0信号中断使能 */
//    CMP_InitStruct.CMP0_InEnable = ENABLE; 		/* 比较器信号输入使能 */

//    CMP_InitStruct.CMP_FltCnt = 15; 			/* 即滤波宽度=tclk 周期*16*CMP_FltCnt */
//    CMP_InitStruct.CMP_CLK_EN = ENABLE; 		/* 时钟使能 */

//    Comparator_init(&CMP_InitStruct);
}

/*******************************************************************************
 函数名称：    void DAC_Init(void)
 功能描述：    DAC初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/23      V1.0           Howlet Li          创建
 *******************************************************************************/

void DAC_init(void)
{
	SYS_AFE_REG5 |= 0x1000;
	
    SYS_WR_PROTECT = 0x7a83;

    SYS_AFE_DAC = 512;                  /* 3.0*512/4096/(0.005/2) = 150A, 其中0.005为母线采样电阻,2为采样电阻个数*/ 
}

/*******************************************************************************
 函数名称：    void UART_init(void)
 功能描述：    UART0寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void UART_init(void)
{
    UART_InitTypeDef UART_InitStruct;

    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 9600;
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;
    UART_InitStruct.ParityMode = UART_Parity_NO;
    UART_InitStruct.IRQEna = UART_IRQEna_SendOver | UART_IRQEna_RcvOver;
    UART_Init(UART1, &UART_InitStruct);
}

/*******************************************************************************
 函数名称：    void UART0_SENDDATA(void)
 功能描述：    UART0发送程序
 输入参数：    n：需要发送的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void UART0_SENDDATA(UINT8 n)
{
    UART0_BUFF = n;
}

/*******************************************************************************
 函数名称：    void UART1_SENDDATA(void)
 功能描述：    UART1发送程序
 输入参数：    n：需要发送的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
 
void UART1_SENDDATA(UINT8 n)
{
    UART1_BUFF = n;
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

void ADC_init(void) 
{
    ADC_InitTypeDef ADC_InitStructure;

    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;
    ADC_InitStructure.FirSeg_Ch = 8;
    ADC_InitStructure.SecSeg_Ch = 0;
    ADC_InitStructure.Trigger_Cnt = 0;
    ADC_InitStructure.MCPWM_Trigger_En = ADC_MCPWM_T0_TRG;
    ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;
    ADC_Init(ADC0, &ADC_InitStructure);

    ADC0_IF = 0xff;

    ADC_NormalModeCFG();
}

/*******************************************************************************
 函数名称：    void ADC_NormalModeCFG(void)
 功能描述：    ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void ADC_NormalModeCFG(void)
{
    ADC0_CHN0 = ADC0_CUR_A_1ST_MSK | ADC1_CUR_B_1ST_MSK;
    ADC0_CHN1 = ADC0_CUR_A_1ST_MSK | ADC1_CUR_B_1ST_MSK;
    ADC0_CHN2 = ADC0_3th_MSK | ADC1_3th_MSK;
    ADC0_CHN3 = ADC0_4th_MSK | ADC1_4th_MSK;
}

/*******************************************************************************
 函数名称：    void HALL_Init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2018/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void HALL_Perip_Init(void)
{
    HALL_InitTypeDef HALL_InitStruct;
    HALL_StructInit(&HALL_InitStruct);

    HALL_InitStruct.FilterLen = 4096;
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1;
    HALL_InitStruct.Filter75_Ena = DISABLE;
    HALL_InitStruct.HALL_Ena = ENABLE;
    HALL_InitStruct.Capture_IRQ_Ena = ENABLE;
    HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;
    HALL_InitStruct.CountTH = 96000000;
    HALL_InitStruct.softIE = DISABLE;

    HALL_Init(&HALL_InitStruct);
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
    GPIO_StructInit(&GPIO_InitStruct);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIO0, GPIO_PinSource_11, AF2_HALL);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_12, AF2_HALL);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_13, AF2_HALL);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
	
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);
	
	GPIO0_PUE = GPIO_Pin_3;
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
    TIM_TimerCmd(TIMER0, ENABLE);
    TIM_TimerStrutInit(&TIM_InitStruct);
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP;
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH0Output = 0;
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP;
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH1Output = 0;
    TIM_InitStruct.Timer_TH = 48000;
    TIM_InitStruct.Timer_CMP0 = 240000;
    TIM_InitStruct.Timer_CMP1 = 500;
    TIM_InitStruct.Timer_Filter0 = 0;
    TIM_InitStruct.Timer_Filter1 = 0;
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1;
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_Zero;
    TIM_TimerInit(TIMER0, &TIM_InitStruct);
}

/*******************************************************************************
 函数名称：    void MCPWM_init(void)
 功能描述：    MCPWM硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = 0;
    MCPWM_InitStructure.MCLK_EN = ENABLE;
    MCPWM_InitStructure.MCPWM_Cnt_EN = ENABLE; 					/* 时钟设置 */
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE; 	/* 工作模式设置 */

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12;
    MCPWM_InitStructure.CMP_BKIN_Filter = 12; 					/* 滤波器时间设置 */

    MCPWM_InitStructure.MCPWM_PERIOD = PWM_PERIOD;
    MCPWM_InitStructure.TriggerPoint0 = (u16)(100 - PWM_PERIOD);
    MCPWM_InitStructure.TriggerPoint1 = (u16)(PWM_PERIOD - 1);
    MCPWM_InitStructure.DeadTimeCH0N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH0P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2P = DEADTIME; 				/* 周期，死区时间设置 */

    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE; 			/* 极性选择设置 */

    MCPWM_InitStructure.Switch_CH0N_CH0P = ENABLE; 				/* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = ENABLE; 				/* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = ENABLE; 				/* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
    	                                                通道交换和极性控制的影响，直接控制通道输出。*/
    MCPWM_InitStructure.CH0P_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH1N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2P_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = LOW_LEVEL;

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE;

    MCPWM_InitStructure.MCPWM_T0_UpdateEN = ENABLE;
    MCPWM_InitStructure.MCPWM_T1_UpdateEN = DISABLE; 				/* 更新事件设置 */

    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE;  				/* T0更新 中断使能 */

#if (CMP_CHOICE == 0)
    MCPWM_InitStructure.FAIL0_INT_EN = ENABLE; 						/* FAIL0 中断使能 */
    MCPWM_InitStructure.FAIL0_INPUT_EN = ENABLE;
    MCPWM_InitStructure.FAIL0_Signal_Sel = HIGH_LEVEL;
    MCPWM_InitStructure.FAIL0_Polarity = LOW_LEVEL; 
#else
#if (CMP_CHOICE == 1) 
    MCPWM_InitStructure.FAIL1_INT_EN = ENABLE; 						/* FAIL0 中断使能 */
    MCPWM_InitStructure.FAIL1_INPUT_EN = ENABLE;
    MCPWM_InitStructure.FAIL1_Signal_Sel = HIGH_LEVEL;
    MCPWM_InitStructure.FAIL1_Polarity = LOW_LEVEL; 
#endif  
#endif

    MCPWM_Init(&MCPWM_InitStructure);
}

/*******************************************************************************
 函数名称：    void seekPosADCsetting(void)
 功能描述：    调用IPD功能前，设置ADC工作模式，为初始位置检测做准备
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void seekPosADCsetting(void)
{
    ADC0_TRIG = BIT1;          /*硬件触发ADC MCPWM T1被使能 */
    ADC0_CFG |= BIT2;          /*状态机复位，idle状态，完成后自动请0 */
    MCPWM_TMR0 = PWM_PERIOD;   /*ADC采样时刻0设置为下桥关断中心点 */
    MCPWM_TMR1 = (s16)(-600);  /*ADC采样时刻1设置为PWM中心点向后偏600个Clock*/
}

/*******************************************************************************
 函数名称：    void DebugPWM_OutputFunction(void)
 功能描述：    PWM输出功能调试   输出25%占空比
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void DebugPWM_OutputFunction(void)
{
    MCPWM_TH00 = (s16)(-(PWM_PERIOD >> 2));
    MCPWM_TH01 = (PWM_PERIOD >> 2);
    MCPWM_TH10 = (s16)(-(PWM_PERIOD >> 2));
    MCPWM_TH11 = (PWM_PERIOD >> 2);
    MCPWM_TH20 = (s16)(-(PWM_PERIOD >> 2));
    MCPWM_TH21 = (PWM_PERIOD >> 2);

    PWMOutputs(ENABLE);
    while(1)
    {
    }
}

/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(stru_FOC_CurrLoopDef *this)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void MCPWM0_RegUpdate(stru_FOC_CurrLoopDef *this)
{
	MCPWM_TH00 = -this->struVoltUVW_PWM.u;
	MCPWM_TH01 = this->struVoltUVW_PWM.u;

	MCPWM_TH10 = -this->struVoltUVW_PWM.v;
	MCPWM_TH11 = this->struVoltUVW_PWM.v;

	MCPWM_TH20 = -this->struVoltUVW_PWM.w;
	MCPWM_TH21 = this->struVoltUVW_PWM.w;
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
        __nop();
    }
}

/*******************************************************************************
 函数名称：    void CopyFromBuffer(u8* nDestAddr, u8* pSrcBuff, u16 nSize)
 功能描述：    拷贝数据
 输入参数：    nDestAddr需要拷贝的数据数组，pSrcBuff存放拷贝数据数组，nSize 拷贝长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void CopyFromBuffer(u8* nDestAddr, u8* pSrcBuff, u16 nSize)
{
    u8* ps = (u8*) pSrcBuff;
    u8* pd = (u8*) nDestAddr;

    while(nSize--)
        *pd++ = *ps++;
}
