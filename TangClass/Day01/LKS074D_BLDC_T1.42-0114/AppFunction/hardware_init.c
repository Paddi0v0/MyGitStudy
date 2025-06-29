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
#include "hardware_init.h"
#include "basic.h"
#include "SEGGER_RTT.h"
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
    Clock_Init();  /* 时钟初始化 */
}
/*******************************************************************************
 函数名称：    void Clock_Init(void)
 功能描述：    时钟配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 2021/4/17      V1.1           Howlet Li          增加延时函数，等待PLL稳定
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;    /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;      /* BIT15:PLLPDN 开PLL */
	SYS_SFT_RST = 0xffff;       /* 外设模块软复位hold */
    Soft_Delay(400);            /* 延时100us, 等待PLL稳定 21.4.17*/
	SYS_SFT_RST = 0;            /* 外设模块软复位释放 */
    SYS_CLK_CFG = 0x000001ff;   /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
	SYS_WR_PROTECT = 0;         /* 关闭系统寄存器写操作*/
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
    __disable_irq();                  /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;
    IWDG_DISABLE();                   /* 关闭看门狗*/
    FLASH_CFG |= 0x00080000;          /* enable prefetch */

	  Timer0_init();                    /* Time0初始化 */
    PGA_init();		
    DAC_init();	
	  CMP_init();	
	  HALL_init();
    GPIO_init();                      /* GPIO初始化 */
    MCPWM_init();                     /* PWM初始化 */
	  ADC_init();                      /* ADC1初始化 */

    Soft_Delay(100);                  /* 延时等待硬件初始化稳定 */

	NVIC_SetPriority(ADC0_IRQn, 3);
    NVIC_EnableIRQ(ADC0_IRQn);
	
	NVIC_SetPriority(ADC1_IRQn, 2);
    NVIC_EnableIRQ(ADC1_IRQn);	
	
	NVIC_SetPriority(MCPWM0_IRQn, 0);
	NVIC_EnableIRQ(MCPWM0_IRQn);
	
	NVIC_SetPriority(TIMER0_IRQn, 4);
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	NVIC_SetPriority(CMP_IRQn, 1);
	NVIC_EnableIRQ(CMP_IRQn);	
	
    SEGGER_RTT_ConfigUpBuffer(1, "JScope_i2u2", bRttBuf, 2048, SEGGER_RTT_MODE_NO_BLOCK_SKIP);	

    __enable_irq();                   /* 开启总中断 */
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
	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);
	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    /* P2.6 电源控制 */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
	
    /* P2.10 电机正反转控制 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;  //输入模式
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;  //默认上拉
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
//		GPIO_SetBits(GPIO2,GPIO_Pin_10); 

    /* P0.15 LED故障显示灯 */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
	GPIO_SetBits(GPIO0,GPIO_Pin_15);  //P0.15输出高电平，LED常亮
//		GPIO_ResetBits(GPIO0,GPIO_Pin_15);  //P0.15输出低电平
    LED_ON();

    /* P2.4 OC设为高阻，暂时没用到 */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;   //高阻
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIO2, &GPIO_InitStruct);


//////		/* P1.0 LED状态显示灯  此IO口初始化会导致MCU锁死 */	
//////		/* MCU锁死后可通过 JLINK 的复位脚解锁 */
//////		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//////    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//////    GPIO_Init(GPIO0, &GPIO_InitStruct);
//////	  GPIO_SetBits(GPIO1,GPIO_Pin_0);   //P1.0输出高电平，LED常亮

//    /* P3.5 ，FG输出 */	
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
//    GPIO_Init(GPIO0, &GPIO_InitStruct);
//	GPIO_SetBits(GPIO3,GPIO_Pin_5); 
//		
//		/* P3.7 ， STATE异常状态输出 */
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
//    GPIO_Init(GPIO0, &GPIO_InitStruct);
//	GPIO_SetBits(GPIO3,GPIO_Pin_7); 

   /* P0.14，PWM_IN PWM信号输入/(暂时复用为FG输出)*/	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
//	GPIO_SetBits(GPIO0,GPIO_Pin_14);
	GPIO_ResetBits(GPIO0,GPIO_Pin_14); 
//    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF8_TIMER23);	

    /* P0.6 ， UART_RX */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF4_UART);
		
    /* P0.7 ， UART_TX */	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF4_UART);		

		
		
    LOCK_POWER_ON();  //打开电源
//	  LOCK_POWER_OFF(); 
//	GPIO0_PDO &= ~BIT6;
		
	  
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
    ADC_InitStructure.IE         = ADC_SF1_IE;          // 中断使能
    ADC_InitStructure.RE         = 0;                   // DMA请求使能
    ADC_InitStructure.NSMP        = DISABLE;             // 两段采样使能
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT右对齐使能
    ADC_InitStructure.CSMP       = DISABLE;             // 连续采样使能
    ADC_InitStructure.TCNT       = 0;                   // 触发一次采样所需的事件数
    ADC_InitStructure.TROVS      = DISABLE;             // 手动触发过采样使能，开启后一次采样需要多次触发
    ADC_InitStructure.OVSR       = 0;                   // 过采样率
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T1;  // 触发信号
    ADC_InitStructure.S1         = 3;                   // 第一段常规采样次数
    ADC_InitStructure.S2         = 1;                   // 第二段常规采样次数
    ADC_InitStructure.IS1        = 1;                   // 空闲采样次数
    ADC_InitStructure.LTH        = 0;                   // ADC 模拟看门狗 0 下阈值
    ADC_InitStructure.HTH        = 0;                   // ADC 模拟看门狗 0 上阈值
    ADC_InitStructure.GEN        = 0;                   // ADC 模拟看门狗 0 对应使能位
    ADC_Init(ADC0, &ADC_InitStructure);		
    ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);

	ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.IE         = ADC_SF1_IE;          // 中断使能
    ADC_InitStructure.RE         = 0;                   // DMA请求使能
    ADC_InitStructure.NSMP        = DISABLE;             // 两段采样使能
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT右对齐使能
    ADC_InitStructure.CSMP       = DISABLE;             // 连续采样使能
    ADC_InitStructure.TCNT       = 0;                   // 触发一次采样所需的事件数
    ADC_InitStructure.TROVS      = DISABLE;             // 手动触发过采样使能，开启后一次采样需要多次触发
    ADC_InitStructure.OVSR       = 0;                   // 过采样率
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // 触发信号
    ADC_InitStructure.S1         = 4;                   // 第一段常规采样次数
    ADC_InitStructure.S2         = 2;                   // 第二段常规采样次数
    ADC_InitStructure.IS1        = 1;                   // 空闲采样次数
    ADC_InitStructure.LTH        = 0;                   // ADC 模拟看门狗 0 下阈值
    ADC_InitStructure.HTH        = 0;                   // ADC 模拟看门狗 0 上阈值
    ADC_InitStructure.GEN        = 0;                   // ADC 模拟看门狗 0 对应使能位
    ADC_Init(ADC1, &ADC_InitStructure);		
    ADC_ClearIRQFlag(ADC1, ADC_ALL_IF);	
	
    ADC_CHN_GAIN_CFG(ADC0,CHN0,ADC_BUS_VOL_CHANNEL,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0,CHN1,ADC_OPA_OUT_CHANNEL,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0,CHN2,ADC_SPEED_CHANNEL,ADC_GAIN3V6);		
		
    ADC_CHN_GAIN_CFG(ADC1,CHN0,BEMF_CH_A,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1,CHN1,BEMF_CH_B,ADC_GAIN3V6);
	ADC_CHN_GAIN_CFG(ADC1,CHN2,BEMF_CH_C,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1,CHN3,ADC_PEAK_CUR_CHANNEL,ADC_GAIN3V6);
	
}


void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;
    MCPWM_StructInit(&MCPWM_InitStructure);
    
	MCPWM_InitStructure.MCLK_EN = ENABLE;              /* 模块时钟开启 */
    MCPWM_InitStructure.CLK_DIV = 0;                   /* MCPWM时钟分频设置 */
	
    MCPWM_InitStructure.IO_CMP_FLT_CLKDIV  = 6;  /* 急停事件(来自IO口信号)数字滤波器时间设置 */ 	
//	MCPWM_InitStructure.AUEN = MCPWM0_ALL_AUPDAT;     /*自动加载使能*/
	  
	/* MCPWM0_CNT0 */	  
    MCPWM_InitStructure.BASE_CNT0_EN = ENABLE;                /* 主计数器开始计数使能开关 */
	MCPWM_InitStructure.TH0 = PWM_PERIOD;                    /* 计数周期设置即MCPWM输出周期*/
		
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
	
    MCPWM_InitStructure.DeadTimeCH012N = DEADTIME;/* 死区时间设置 */
    MCPWM_InitStructure.DeadTimeCH012P = DEADTIME;
	
    MCPWM_InitStructure.CMP_CTRL_CNT0  = DISABLE ;/* CMP控制CNT0使能 */
	MCPWM_InitStructure.EVT_CNT0_EN    = DISABLE ;/* MCPWM_CNT1外部触发使能 */
	MCPWM_InitStructure.EVT0           = DISABLE ;
	
	MCPWM_InitStructure.TR0_UP_INTV     = DISABLE;
	MCPWM_InitStructure.TR0_T0_UpdateEN = ENABLE ;
	MCPWM_InitStructure.TR0_T1_UpdateEN = DISABLE ;
    MCPWM_InitStructure.TR0_AEC         = DISABLE;
		
    MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0更新事件 中断关闭 */
	MCPWM_InitStructure.T1_Update0_INT_EN = DISABLE ; /* T1更新事件 中断使能 */
	MCPWM_InitStructure.Update1_INT_EN = DISABLE;       /* CNT0 更新事件 中断使能  */
		
#if (CNT0_PRE_DRIVER_POLARITY == P_HIGH__N_LOW)                    /* CHxP 高有效， CHxN低电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM0_IO01和MCPWM0_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_HIGH_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_HIGH_LEVEL;
#endif
#if (CNT0_PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP 高有效， CHxN高电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM0_IO01和MCPWM0_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_LOW_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_LOW_LEVEL;
#endif


#if(MCPWM_SWAP_SETTING == 1)   
  PWM_SWAP = 0x67;
#endif

    MCPWM_InitStructure.CH0N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH0P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2P_FAIL_EN = ENABLE ;
		
    MCPWM_InitStructure.FAIL0_INPUT_EN   = DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_INT_EN     = DISABLE;
	MCPWM_InitStructure.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_Polarity   = MCPWM0_HIGH_LEVEL_ACTIVE ;

		
	MCPWM_InitStructure.FAIL1_INPUT_EN   = ENABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL1_INT_EN     = ENABLE;
	MCPWM_InitStructure.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL1_Polarity   = MCPWM0_HIGH_LEVEL_ACTIVE ;
		
	MCPWM_InitStructure.HALT_PRT0        = DISABLE ;
	MCPWM_InitStructure.FAIL_0CAP        = DISABLE ;
				
    MCPWM_InitStructure.TMR0 = 0;   /* MCPWM0_TMR0  设置 */
    MCPWM_InitStructure.TMR1 = 0;   /* MCPWM0_TMR1  设置 */
	MCPWM_InitStructure.TMR2 = 0;   /* MCPWM0_TMR2  设置 */
    MCPWM_InitStructure.TMR3 = 0;   /* MCPWM0_TMR3  设置 */ 
	
	MCPWM_InitStructure.TMR2_TB        = 0;/* MCPWM TMR2时基（计数器）选择 0：时基0；1：时基1 */
	MCPWM_InitStructure.TMR3_TB        = 1;/* MCPWM TMR3时基（计数器）选择 0：时基0；1：时基1 */

    MCPWM_Init(&MCPWM_InitStructure);
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
void Timer0_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;
	
	TIM_InitStruct.Timer_CH0_WorkMode = 0; /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0Output = 0;    /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = 0; /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1Output = 0;    /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 48000;       /* 定时器计数门限初始值48000*/
    TIM_InitStruct.Timer_CMP0 = 250;  	   /* 设置比较模式的CH0比较初始值24000 */
    TIM_InitStruct.Timer_CMP1 = 250;  		/* 设置比较模式的CH1比较初始值24000 */
    TIM_InitStruct.Timer_FLT = 0;  			/* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;  /* 设置Timer模块时钟2分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_ZC;   /* 开启Timer模块比较中断和过零中断*/
    TIM_TimerInit(UTIMER0, &TIM_InitStruct); 


	TIM_InitStruct.Timer_CH0_WorkMode = 0; /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0Output = 0;     /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = 0; /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1Output = 0;     /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 96000000;    	/* 定时器计数门限初始值48000*/
    TIM_InitStruct.Timer_CMP0 = 250;  		/* 设置比较模式的CH0比较初始值24000 */
    TIM_InitStruct.Timer_CMP1 = 250;  		/* 设置比较模式的CH1比较初始值24000 */
    TIM_InitStruct.Timer_FLT = 0;  			/* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;     /* 设置Timer模块时钟2分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_None;    /* 开启Timer模块比较中断和过零中断*/
    TIM_TimerInit(UTIMER2, &TIM_InitStruct); 	
	
    TIM_TimerCmd(UTIMER0, ENABLE);      /* Timer0 模块使能 */	
    TIM_TimerCmd(UTIMER2, ENABLE);      /* Timer2 模块使能 */
	
}

/*******************************************************************************
 函数名称：    void DAC_Init(void)
 功能描述：    DAC初始化(通常不会同时输出 DAC0 和 DAC1，以免造成信号竞争。)
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
volatile u16 DAC_Range_Vol,DAC_Short_Value;
void DAC_init(void)
{	
	DAC_InitTypeDef DAC_InitStre;
    DAC_StructInit(&DAC_InitStre);                /* DAC结构体初始化 */

	DAC_InitStre.DAC_GAIN = DAC_RANGE_4V85;      /*DAC输出量程为4.85V*/
	DAC_InitStre.DACOUT_EN = DISABLE;				/*使能DAC输出到P0.0*/
	DAC_InitStre.TIG_CH_EN = DISABLE; 		    /*使能UTIMER触发*/
	DAC_InitStre.DAC_STEP = 0;				    /*步进值为0*/
	DAC_Init(DAC_Channel_0,&DAC_InitStre);       /* DAC初始化 */
	
	DAC_Cmd(DAC_Channel_0,ENABLE);				/*使能DAC时钟*/
	
	if(DAC_InitStre.DAC_GAIN == DAC_RANGE_4V85)
	{
	  DAC_Range_Vol = 48500;
	}
	else
	{
	  DAC_Range_Vol = 12000;
	}
	
	DAC_Short_Value = (mBLDC_CtrProc.NVR_OPAx_Vol + SHORT_CURRENT_VOL/2)*4096/DAC_Range_Vol;   //SHORT_CURRENT_VOL = 28795 
	
	DAC_OutputValue(DAC_Channel_0,DAC_Short_Value);
}
/*******************************************************************************
 函数名称：    void CMP_init(void)
 功能描述：    CMP初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
void CMP_init(void)
{	
	CMP_InitTypeDef CMP_InitStre;
	CMP_StructInit(&CMP_InitStre);
	
	CMP_InitStre.CLK_COM_DIV = 0;									/* 比较器共用滤波时钟分频*/
	CMP_InitStre.FT = DISABLE;										/* 比较器快速比较*/
	CMP_InitStre.HYS = CMP_HYS_0mV;							   /* 比较器滞回电压*/
	
	CMP_InitStre.CMP0.SELP = CMP0_SELP_IP1; 		       /* 比较器0正端信号选择 */
	CMP_InitStre.CMP0.SELN = CMP0_SELN_HALL0_MID; 				/* 比较器0负端信号选择 */
	CMP_InitStre.CMP0.RE = DISABLE;								/* 比较器0DMA失能*/
	CMP_InitStre.CMP0.POL= CMP_HIGH_LEVEL;				/* 比较器0高电平输出有效*/
	CMP_InitStre.CMP0.IRQ_TRIG = IRQ_LEVEL_TRIG_MODE; /* 比较器0电平触发中断模式*/
	CMP_InitStre.CMP0.IN_EN = ENABLE; 			 			/* 比较器0信号输入使能 */
	CMP_InitStre.CMP0.IE = DISABLE;  							/* 比较器0信号中断使能 */
	CMP_InitStre.CMP0.FIL_CLK_DIV16 = 2; 					/* 即滤波宽度=tclk 周期*16*CMP_FltCnt (CMP_FltCnt分频系数,0~15)*/
	CMP_InitStre.CMP0.FIL_CLK_DIV2 = 2;  					/* 比较器 2/1/0 滤波时钟使能 */
	CMP_InitStre.CMP0.CLK_EN = ENABLE;						/* 比较器时钟使能*/
	CMP_InitStre.CMP0.EN = ENABLE;       				  /* 比较器0开关 操作SYS_AFE_REG5 */
	
	CMP_InitStre.CMP1.SELP = CMP1_SELP_OPA3_OUT; 		       /* 比较器0正端信号选择 */
	CMP_InitStre.CMP1.SELN = CMP_SELN_DAC0; 				/* 比较器0负端信号选择 */
	CMP_InitStre.CMP1.RE = DISABLE;								/* 比较器0DMA失能*/
	CMP_InitStre.CMP1.POL= CMP_HIGH_LEVEL;				/* 比较器0高电平输出有效*/
	CMP_InitStre.CMP1.IRQ_TRIG = IRQ_LEVEL_TRIG_MODE; /* 比较器0电平触发中断模式*/
	CMP_InitStre.CMP1.IN_EN = ENABLE; 			 			/* 比较器0信号输入使能 */
	CMP_InitStre.CMP1.IE = DISABLE;  							/* 比较器0信号中断使能 */
	CMP_InitStre.CMP1.FIL_CLK_DIV16 = 4; 					/* 即滤波宽度=tclk 周期*16*CMP_FltCnt (CMP_FltCnt分频系数,0~15)*/
	CMP_InitStre.CMP1.FIL_CLK_DIV2 = 0;  					/* 比较器 2/1/0 滤波时钟使能 */
	CMP_InitStre.CMP1.CLK_EN = ENABLE;						/* 比较器时钟使能*/
	CMP_InitStre.CMP1.EN = ENABLE;       				  /* 比较器0开关 操作SYS_AFE_REG5 */	
	
	CMP_Init(&CMP_InitStre);										/* 比较器初始化 */
	
	
	SYS_ModuleClockCmd(SYS_Module_CMP,ENABLE);
	
	CMP_Cmd(CMP_CHN_0,ENABLE);/* 比较器0时钟使能*/
	CMP_Cmd(CMP_CHN_1,ENABLE);/* 比较器0时钟使能*/
}

/*******************************************************************************
 函数名称：    void PGA_init(void)
 功能描述：    PGA初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容

OPA0，共模电压（扩大10000 倍结果）    0x000014C0
OPA1，共模电压（扩大10000 倍结果）    0x000014C4
OPA2，共模电压（扩大10000 倍结果）    0x000014C8
OPA3，共模电压（扩大10000 倍结果）    0x000014CC
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
void PGA_init(void)
{	
	OPA_InitTypeDef OPA_InitStruct;
	OPA_StructInit(&OPA_InitStruct);

	OPA_InitStruct.OPA_IT = PGA_IT_DISABLE;  /*opa偏置电流调节禁止*/
	OPA_InitStruct.OPA_CLEna = ENABLE;       /*使能*/
	OPA_InitStruct.OPA_Gain = PGA_GAIN_32;   /*反馈电阻320k:10k*/
	OPA_Init(OPA3 ,&OPA_InitStruct);
		
    OPA_OUT(OPA3 , ENABLE);                 /*OPA3信号输出至P2.7脚*/
	
	mBLDC_CtrProc.NVR_OPAx_Vol = Read_Trim(0x000014CC); 
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
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1;  /* 设置Hall模块时钟分频系数 */
    HALL_InitStruct.Filter75_Ena = DISABLE;         /* Hall信号滤波方式，7判5模式或者全1有效模式 */
    HALL_InitStruct.HALL_Ena = ENABLE;              /* 模块使能 */
    HALL_InitStruct.Capture_IRQ_Ena = DISABLE;       /* 捕捉中断使能 */
    HALL_InitStruct.OverFlow_IRQ_Ena = DISABLE;      /* 超时中断使能 */
    HALL_InitStruct.CountTH = 0xFFFFFFFF;              /* Hall模块计数模值，计数超过模值会产生超时中断 */
	HALL_InitStruct.softIE = DISABLE;								 /* 软件中断失能 */
	
    HALL_Init(&HALL_InitStruct);/* HALL初化 */
	HALL_Cmd(ENABLE);/* HALL使能 */
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
void Soft_Delay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}





///*******************************************************************************
// 函数名称：    void Reg_Clr(void)
// 功能描述：    寄存器清零
// 输入参数：    addr ：需要清零寄存器的起始地址 
//               nSize：需要清零的寄存器个数
// 输出参数：    无
// 返 回 值：    无
// 其它说明：
// 修改日期      版本号          修改人            修改内容
// -----------------------------------------------------------------------------
// 2021/3/14      V1.0           Howlet Li          创建
// *******************************************************************************/
//void Reg_Clr(u32 addr, u8 nSize)
//{
//   while(nSize --)
//   {
//      REG32(addr) = 0;
//      addr += 4;
//   }
//}


