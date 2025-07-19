/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "MC_Parameter_M0.h"

void UART_init(void);
void HALL_Perip_Init(void);
void SoftDelay(u32 cnt);
void TempSensor_Init(void);

void DAC_init(void);
void CMP_init(void);
void UTimer_init(void);
void GPIO_init(void);
void UART1_init(void);
void ADC0_init(void);
void get_ic_temp_init(void);
void Clock_Init(void);
void Hardware_init(void);

extern void registerEPWM0_DrvLevel(void);
extern void ADC_1Shunt_NormalModeCFG(void);
extern void ADC_2Shunt_NormalModeCFG(void);

void PGA_init(void);
void MCPWM_init(void);

extern	PSTR_DrvCfgPara getCfgParaPtr(u8 objID);
extern	u16 getPWMPrd(PSTR_DrvCfgPara pDrvCfgPara);
extern	u16 getDeadTime(PSTR_DrvCfgPara pDrvCfgPara);

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
	SYS_WR_PROTECT = 0x7a83;
	SYS_DBG_CFG |= BIT14;				/* 软件复位通用寄存器*/
    IWDG_DISABLE();						/* 关闭独立看门狗使能*/	
	FLASH_CFG |= 0x00080000;			/* enable prefetch */

	DSP_Init();							/* DSP模块初始化*/
	UART_init();						/* 串口初始化UART0*/
	ADC0_init();						/* ADC初始化 */
	MCPWM_init();						/* PWM初始化 */
	UTimer_init();						/* 通用计数器初始化 */
	GPIO_init();						/* GPIO初始化 */
	DAC_init();							/* DAC 初始化 */
	PGA_init();							/* PGA 初始化 */
	CMP_init();							/* 比较器初始化 */
	HALL_Perip_Init();					/* HALL模块初始化 */
	TempSensor_Init();					/* 温度传感器初始化 */

	SoftDelay(100);						/* 延时等待硬件初始化稳定 */

//	DSP_SC = BIT1;						/* DSP Paused */

	NVIC_SetPriority(UART_IRQn, 0);		/* 设置UART0中断优先级为2 | 共0，1，2，3四级中断优先级，0为最高*/
	NVIC_SetPriority(ADC_IRQn, 1);
	NVIC_SetPriority(HALL_IRQn, 2);
	NVIC_SetPriority(MCPWM0_IRQn, 2);
//	NVIC_SetPriority(CMP_IRQn, 0);		/* 设置CMP_IRQn中断优先级为0 | 共0，1，2，3四级中断优先级，0为最高*/
	NVIC_SetPriority(TIMER0_IRQn, 2);
//	NVIC_SetPriority(TIMER3_IRQn, 0);

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	NVIC_SetPriority(MCPWM0_IRQn, 1);   
	NVIC_EnableIRQ (MCPWM0_IRQn);
#else
	NVIC_EnableIRQ(ADC_IRQn);			/* enable the ADC0 interrupt */
#endif

	NVIC_EnableIRQ (TIMER0_IRQn);
//	NVIC_EnableIRQ (CMP_IRQn);			/* 打开比较器中断 */ 
//	NVIC_EnableIRQ(TIMER2_IRQn);
//	NVIC_EnableIRQ(TIMER3_IRQn);
//	NVIC_EnableIRQ (UART0_IRQn);

//	__enable_irq(); 				  /* 开启总中断 */
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
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_VolSelModule(1);       /* 0: 3.3V ; 1: 5.0V*/
    SYS_AFE_REG0 |= BIT15;     /* BIT15:PLLPDN */
    SoftDelay(100);            /* 等待PLL稳定*/
	SYS_CLK_CFG = 0x000001ff; /* BIT[9:8]:0: CLK_HS,1:PLL,2:LRC,3:LRC
                                 | BIT[7:0]CLK_DIV  | 0x1ff对应48M时钟 */
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
 函数名称：    void Reg_Reset(void)
 功能描述：    寄存器复位
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/3/14      V1.0           Howlet Li          创建
 *******************************************************************************/
void Reg_Reset(void)
{
	SYS_WR_PROTECT = 0x7a83;				/* 解除系统寄存器写保护 */
	SYS_SFT_RST = 0xfff;

	Reg_Clr((u32)(&SYS_AFE_REG0),8);		/* 清SYS_AFE_REG0~SYS_AFE_REG7 */
	Reg_Clr((u32)(&ADC_CHN0),12);
	//Reg_Clr((u32)(&ADC_GAIN0),2);
	Reg_Clr((u32)(&ADC_IE),6);

	Reg_Clr((u32)(&DMA_CCR0),18);
	Reg_Clr(GPIO0_BASE,12);				/* 清GPIO0 相关的12个寄存器 */
	Reg_Clr(GPIO1_BASE,12);
	//Reg_Clr(GPIO2_BASE,12);
	//Reg_Clr(GPIO3_BASE,12);   
	Reg_Clr(EXTI_BASE,6);
	Reg_Clr(CMP_BASE,5);
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
void SystemInit (void)
{
	Reg_Reset();   /* 初始化所有外设寄存器 */
    Clock_Init();  /* 时钟初始化 */
}

#if 0
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

    //m_TempertureCof.nCofA    = Read_Trim(0x00000398);
    //m_TempertureCof.nOffsetB = Read_Trim(0x0000039C);
}
#endif

/*******************************************************************************
 函数名称：    void PGA_init(void)
 功能描述：    根据配置进行PGA初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/1/15      V1.0           Li Tonghua          创建
 *******************************************************************************/
void PGA_init(void)
{
	u16 OPA_mode;
	PSTR_DrvCfgPara	pParaPtr;

	pParaPtr	= getCfgParaPtr(0);
	OPA_mode	= pParaPtr->mS_GlobalCfg.m_bOPAValue;
	
    OPA_InitTypeDef OPA_InitStruct;
    OPA_StructInit(&OPA_InitStruct);
    OPA_InitStruct.OPA_CLEna = ENABLE;			/*使能OPA*/
    OPA_InitStruct.OPA_Gain = OPA_mode;			/*OPA内部增益电阻选择200：10*/
    OPA_InitStruct.OPA_B_EN = OPA0_IN_IP;		/*OPA0使用 OPA0_IN/OPA0_IP 作为差分输入;单,双电阻 需要根据不同芯片相匹配选择*/
    OPA_Init(OPA, &OPA_InitStruct);

    /*ADC采集电压OPA_IN * 170/(40 + 1) = OPA_IN * 4.14634*/
    OPA_OUT(OPA, DISABLE); /* 关闭OPA输出通过外部引脚P2.7输出功能*/    
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
    CMP_InitTypeDef CMP_InitStruct;
    CMP_StructInit(&CMP_InitStruct);

    // 比较器0
    CMP_InitStruct.CMP0_EN = ENABLE;			// 比较器 0 开关
    CMP_InitStruct.CMP0_SELN = CMP_SELN_DAC;	// CMP1_N SELN_DAC;
    CMP_InitStruct.CMP0_SELP = CMP_SELP_OPA0_IP;// CMP0_P CMP0_IP3母线
    CMP_InitStruct.CMP0_IN_EN = ENABLE;			// 比较器 0 信号输入使能
    CMP_InitStruct.CMP0_IE = ENABLE;			// 比较器 0 中断使能
    CMP_InitStruct.CMP0_POL = 0;				// 比较器 0 极性选择：0高电平，1低电平
    // 比较器1
    CMP_InitStruct.CMP1_EN = DISABLE;			// 比较器 1 开关
    CMP_InitStruct.CMP1_SELN = CMP_SELN_DAC;	// CMP1_N SELN_DAC;
    CMP_InitStruct.CMP1_SELP = CMP_SELP_OPA0_IP; // CMP1_P CMP1_IP0母线
    CMP_InitStruct.CMP1_IE = DISABLE;			// 比较器 1 中断使能
    CMP_InitStruct.CMP1_IN_EN = DISABLE;		// 比较器 1 信号输入使能
    CMP_InitStruct.CMP1_POL = 0;				// 比较器 1 极性选择：0高电平，1低电平

    CMP_InitStruct.CMP_HYS = CMP_HYS_20mV;		// 比较器回差为20mV
    CMP_InitStruct.CLK10_EN = ENABLE;			// 比较器 1/0 滤波时钟使能
    CMP_InitStruct.FIL_CLK10_DIV2 = 2;			// 比较器 1/0 滤波时钟分频
    CMP_InitStruct.FIL_CLK10_DIV16 = 15;		// 比较器 1/0 滤波系数
    CMP_Init(&CMP_InitStruct);
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
	s16 nDACRef;
	s32 wDACCmp;
	PSTR_DrvCfgPara	pParaPtr;	
	
	pParaPtr	= getCfgParaPtr(0);
	wDACCmp	= (s32)pParaPtr->mS_FBCurSense.nHardOvCurVolt;	
	
	DAC_InitTypeDef DAC_InitStruct;
    DAC_StructInit(&DAC_InitStruct);
    DAC_InitStruct.DACOUT_EN = DISABLE;			/*关闭DAC通过IO（P0.0）输出*/

    DAC_Init(&DAC_InitStruct);

	nDACRef		= 3000;							// 固定3000mV ----- 256
	wDACCmp		= (wDACCmp * 256)/nDACRef;
	
    DAC_OutputValue(wDACCmp);                 /* 3*40/256/0.050 = 10A, 其中0.005为母线采样电阻*/
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
    UART_InitStruct.BaudRate = 38400;                 /* 设置波特率38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* 发送数据长度8位 */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* 先发送LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;      /* 无奇偶校验 */
    UART_InitStruct.IRQEna = 0;
    UART_Init(UART0, &UART_InitStruct);
}

/*******************************************************************************
 函数名称：    void UART_SENDDATA(void)
 功能描述：    UART0发送程序
 输入参数：    n：需要发送的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART_SENDDATA(UINT8 n)
{
    UART_BUFF = n;
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
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure);
	
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;               /* ADC数据左对齐模式 */
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_InitStructure.FirSeg_Ch = 2;                        /* 第一段共采样2个通道 */
    ADC_InitStructure.SecSeg_Ch = 6;                        /* 第二段共采样6个通道 */
    ADC_InitStructure.SEL_En = ADC_MCPWM_TRG ;              /* 打开MCPWM硬件触发事件 */
    ADC_InitStructure.Trigger_En = ADC_HARDWARE_T0_TRG | ADC_HARDWARE_T1_TRG;;  /* 打开MCPWM_T0 MCPWM_T1硬件触发事件 */
    ADC_InitStructure.Trigger_Mode = ADC_2SEG_TRG;          /* 设置ADC转换模式为双段式采样 */
    ADC_InitStructure.IE = 0;                     			//ADC_EOS1_IRQ_EN; /* ADC第二段采样结束中断使能,此处单电阻不需要ADC中断*/
    ADC_InitStructure.ADC_SAMP_CLK = 12;         			/* 12--20个时钟周期 */
#else
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    ADC_InitStructure.FirSeg_Ch = 8;                        /* 第一段共采样8个通道 */
    ADC_InitStructure.SecSeg_Ch = 0;                        /* 第二段共采样0个通道 */
    ADC_InitStructure.SEL_En = ADC_MCPWM_TRG ;              /* 打开 MCPWM 硬件触发事件 */
    ADC_InitStructure.Trigger_En = ADC_HARDWARE_T0_TRG;     /* 使能 T0 硬件触发ADC采样 */
    ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;          /* 设置ADC转换模式为单段式采样 */
    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;                 /* ADC第一段采样结束中断使能 */
	 ADC_InitStructure.ADC_SAMP_CLK = 12;					/* 12个时钟周期 */
#endif
#endif
    ADC_Init(ADC, &ADC_InitStructure);

    ADC_IF = 0xff;
	ADC_STATE_RESET();

	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_1Shunt_NormalModeCFG();
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	ADC_2Shunt_NormalModeCFG();
	#elif ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)) 
	ADC_3Shunt_NormalModeCFG();
	#endif  
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
    SYS_ModuleClockCmd(SYS_Module_HALL, ENABLE);

    HALL_StructInit(&HALL_InitStruct);
    HALL_InitStruct.FilterLen = 512;                /* Hall信号数字滤波长度 512个时钟周期 */
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1;  /* 设置Hall模块时钟分频系数 */
    HALL_InitStruct.Filter75_Ena = DISABLE;         /* Hall信号滤波方式，7判5模式或者全1有效模式 */
    HALL_InitStruct.HALL_Ena = ENABLE;              /* 模块使能;IPD时候需要使能*/
    HALL_InitStruct.Capture_IRQ_Ena = DISABLE;		/* 捕捉中断使能 */
    HALL_InitStruct.OverFlow_IRQ_Ena = DISABLE;		/* 超时中断使能 */
    HALL_InitStruct.CountTH = 9600000;              /* Hall模块计数模值，计数超过模值会产生超时中断 */

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

    /* MCPWM P1.4~P1.9 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_10, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_11, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_12, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_13, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF3_MCPWM);

#if ((ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) || (ROTOR_SENSOR_TYPE == ROTOR_HALL2SENSORLESS))  
    /* P0.15-RX0, P1.0-TX0  UART0 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_4, AF2_HALL);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_5, AF2_HALL);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF2_HALL);
#endif

//	GPIO输出 P1.6
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIO1, &GPIO_InitStruct);		
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
    TIM_TimerStrutInit(&TIM_InitStruct); /* Timer结构体变量初始化 */
 
    TIM_InitStruct.CLK_DIV = TIM_Clk_Div1;      /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.CH0_MODE = TIMER_OPMode_CMP; /* 设置Timer CH0为比较模式*/
    TIM_InitStruct.CH0_POL = 0;                 /* 计数器回零时，比较模式输出极性控制*/
    TIM_InitStruct.CH1_MODE = TIMER_OPMode_CMP; /* 设置Timer CH1为比较模式*/
    TIM_InitStruct.CH1_POL = 0;                 /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.TH = 24000;                  /* 设置计数器计数模值 1ms 1KHZ*/
    TIM_InitStruct.TIM_CMP0 = 0;                /* 设置比较模式的CH0比较值 */
    TIM_InitStruct.TIM_CMP1 = 0;                /* 设置比较模式的CH1比较值 */
    TIM_InitStruct.IE = TIM_IRQ_IE_ZC;          /* 开启Timer模块过零中断 */
    TIM_TimerInit(TIMER0, &TIM_InitStruct);
	TIM_TimerCmd(TIMER0,ENABLE);                /* 模块使能 */ 
}

/*******************************************************************************
 函数名称：    void MCPWM_init(void)
 功能描述：    MCPWM初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/11/5      V1.0           Li Tonghua          创建
 *******************************************************************************/
void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

	u16 prd;
	u16 deadTime;
	u8  clockDiv;
	PSTR_DrvCfgPara	pParaPtr;
	
	pParaPtr	= getCfgParaPtr(0);
	prd			= getPWMPrd(pParaPtr);
	deadTime	= getDeadTime(pParaPtr);
	clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = clockDiv;                   /* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;                     /* 模块时钟开启 */
    MCPWM_InitStructure.MCPWM_Cnt0_EN = ENABLE;               /* 时基0主计数器开始计数使能开关 */
    MCPWM_InitStructure.MCPWM_Cnt1_EN = ENABLE;               /* 时基1主计数器开始计数使能开关 */
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;

    /* 自动更新使能寄存器 MCPWM_TH00 自动加载使能 MCPWM_TMR0 自动加载使能 MCPWM_0TH 自动加载使能 MCPWM_0CNT 自动加载使能*/
    MCPWM_InitStructure.AUEN = TH00_AUEN | TH01_AUEN | TH10_AUEN | TH11_AUEN |
                               TH20_AUEN | TH21_AUEN | TMR0_AUEN | TMR1_AUEN |
                               TMR2_AUEN | TMR3_AUEN | TH0_AUEN | TH30_AUEN | TH31_AUEN ;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12;                /* 急停事件(来自IO口信号)数字滤波器时间设置 */
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;                 /* 急停事件(来自比较器信号)数字滤波器时间设置 */

    MCPWM_InitStructure.TimeBase0_PERIOD = prd;        /* 时期0周期设置 */
    MCPWM_InitStructure.TimeBase1_PERIOD = prd;        /* 时期1周期设置 */
    MCPWM_InitStructure.TriggerPoint0 = (u16)(20 - prd); //100 /* MCPWM_TMR0 ADC触发事件T0 设置 */
    MCPWM_InitStructure.TriggerPoint1 = (u16)(800 - prd); /* MCPWM_TMR1 ADC触发事件T1 设置 */
    MCPWM_InitStructure.DeadTimeCH0123N = deadTime;           /* 通道0,1,2,3的N端死区时间设置 */
    MCPWM_InitStructure.DeadTimeCH0123P = deadTime;           /* 通道0,1,2,3的P端死区时间设置 */


#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)                    /* CHxP 高有效， CHxN低电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = HIGH_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = HIGH_LEVEL;
#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP 高有效， CHxN高电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = LOW_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = LOW_LEVEL;
#endif
#endif

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE;           /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                                 还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
    MCPWM_InitStructure.MCPWM_Base0T0_UpdateEN = ENABLE;      /* MCPWM 时基0 T0事件更新使能 */
    MCPWM_InitStructure.MCPWM_Base0T1_UpdateEN = DISABLE;     /* MCPWM 时基0 T1事件更新 禁止*/

    MCPWM_InitStructure.MCPWM_Base1T0_UpdateEN = ENABLE;      /* MCPWM 时基1 T0事件更新使能 */
    MCPWM_InitStructure.MCPWM_Base1T1_UpdateEN = DISABLE;     /* MCPWM 时基1 T1事件更新 禁止*/

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    MCPWM_InitStructure.CNT0_T1_Update_INT_EN = ENABLE;           /* T0更新事件 中断使能或关闭 */
#else
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    MCPWM_InitStructure.CNT0_T0_Update_INT_EN = DISABLE;           /* T0更新事件 中断使能或关闭 */
#else
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
    MCPWM_InitStructure.CNT0_T0_Update_INT_EN = DISABLE;           /* T0更新事件 中断使能或关闭 */
#endif
#endif
#endif

    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;               /* FAIL0事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL0_INPUT_EN = ENABLE;             /* FAIL0通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL0_Signal_Sel = FAIL_SEL_CMP;      /* FAIL0事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL0_Polarity = HIGH_LEVEL_VALID;    /* FAIL0事件极性选择，高有效 */

    MCPWM_InitStructure.FAIL1_INT_EN = DISABLE;                /* FAIL1事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL1_INPUT_EN = DISABLE;              /* FAIL1通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL1_Signal_Sel = FAIL_SEL_CMP;      /* FAIL1事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL1_Polarity = HIGH_LEVEL_VALID;    /* FAIL1事件极性选择，高有效或低有效 */

#ifdef MCPWM_SWAP_FUNCTION      /* 使用034D, 037E内置预驱芯片需要打开PWM交换功能 */
    MCPWM_PRT = 0x0000DEAD; /*enter password to unlock write protection */
    MCPWM_SWAP = 0x67;
#endif
    MCPWM_Init(MCPWM0, &MCPWM_InitStructure);                 /* MCPWM0 模块初始化 */
	
	registerEPWM0_DrvLevel();
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
    MCPWM_TH00 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM_TH01 = (PWM_PERIOD_M0 >> 2);
    MCPWM_TH10 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM_TH11 = (PWM_PERIOD_M0 >> 2);
    MCPWM_TH20 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM_TH21 = (PWM_PERIOD_M0 >> 2);

    PWMOutputs(MCPWM0,ENABLE);
    while(1)
    {
    }
}


