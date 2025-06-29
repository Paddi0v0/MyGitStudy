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
#include "basic.h"
#include "hardware_config.h"
#include "gpio_led.h"
#include "gpio_key.h"
#include "utimer.h"
#include "can.h"
void UART_init(void);

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
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/

    GPIO_init();   /* GPIO初始化 */
    CAN_Init(0x1D,0x1C);  /*波特率100k*/
//	SFF_ID_Filter(0X5555 ,0x0000,0,0 ,0x08,0x0,0x55,0x0);/*标准帧单ID滤波 标准帧单滤波ID滤波演示*/
//	  EFF_ID_Filter(0X5555 ,0x0000,0,0);                   /*扩展帧单ID滤波 扩展帧单滤波ID滤波演示*/
//  ID1_Filter_Dual(0X11 ,0x0000,0,1 ,0x55,0xff,0);      /*CAN双ID过滤中ID1滤波 标准帧双滤波ID1滤波演示*/
//	ID2_Filter_Dual(0Xaa ,0x0000,0,0,0);                 /*CAN双ID过滤中ID2滤波 标准帧双滤波ID2滤波演示*/
	  ID1_Filter_Dual(0x0fA2000 ,0x00000000,0,0 ,0x0,0x0,1);      /*CAN双ID过滤中ID1滤波 扩展帧双滤波ID1滤波演示*/
    ID2_Filter_Dual(0x1fEE000 ,0x00000000,0,0,1);                 /*CAN双ID过滤中ID2滤波 扩展帧双滤波ID2滤波演示*/
	
	  NVIC_SetPriority(CAN_IRQn,1);
		NVIC_EnableIRQ(CAN_IRQn);
	
    __enable_irq();/* 开启中断 */
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
		
		/* 配置UTimer3  TIM3_CH0: P2.8   TIM3_CH1: P1.3*/
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIO2, &GPIO_InitStruct);
		
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIO1, &GPIO_InitStruct);
		
	  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_3, AF8_TIMER23);//复用
		GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF8_TIMER23);//复用
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
    ADC_StructInit(&ADC_InitStructure); //初始化结构体
    ADC0_CHN0 = 0x09;                   //采样通道通道9

    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;           //第一段扫描结束中断
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;         //ADC数据输出左对齐
    ADC_InitStructure.FirSeg_Ch = ADC_1_TIMES_SAMPLE; //采样通道数
    ADC_InitStructure.UTIMER_Trigger_En = DISABLE;    //关闭硬件触发
    ADC_InitStructure.MCPWM_Trigger_En = DISABLE;     //关闭硬件触发
    ADC_InitStructure.Trigger_Cnt = 1;
    ADC_Init(ADC0, &ADC_InitStructure);

    ADC0_IF = 0xff; //清中断标志位
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
    UART_InitStruct.BaudRate = 38400;                /* 设置波特率38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b; /* 发送数据长度8位 */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;     /* 停止位1位 */
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;  /* 先发送LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;     /* 无奇偶校验 */
    UART_InitStruct.IRQEna = ENABLE;                 /* 串口中断使能 */
    UART_Init(UART0, &UART_InitStruct);
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

    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;     /* BIT15:PLLPDN */
    SYS_CLK_CFG |= 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
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
void PGA_Init(void)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA0, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA1, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA2, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA3, ENABLE);
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
void CMP_Init(void)
{
    CMP_InitTypeDef CMP_InitStruct;

    CMP_StructInit(&CMP_InitStruct);

    CMP_InitStruct.CMP0_EN = ENABLE; /* 比较器0开关 */
    CMP_InitStruct.CMP0_SELN = SELN_DAC;
    CMP_InitStruct.CMP0_SELP = SELP_CMP_OPA0IP; /* CMP0_P CMP0_OPA0IP */
    CMP_InitStruct.CMP0_InEnable = ENABLE;      /* 比较器信号输入使能 */
    CMP_InitStruct.CMP0_IE = DISABLE;           /* 比较器0信号中断使能 */

    CMP_InitStruct.CMP1_EN = ENABLE;         /* 比较器1开关 */
    CMP_InitStruct.CMP1_SELN = SELN_DAC;     /* CMP1_N 内部参考 */
    CMP_InitStruct.CMP1_SELP = SELP_CMP_IP0; /* CMP1_P CMP1_OPA3 */
    CMP_InitStruct.CMP1_InEnable = ENABLE;   /* 比较器信号输入使能 */
    CMP_InitStruct.CMP1_IE = ENABLE;         /* 比较器1信号中断使能 */

    CMP_InitStruct.CMP_FltCnt = 15;     /* 即滤波宽度=tclk 周期*16*CMP_FltCnt */
    CMP_InitStruct.CMP_CLK_EN = ENABLE; /* 时钟使能 */

    Comparator_init(&CMP_InitStruct);
	
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
void DAC_Init(void)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC, ENABLE);
    SYS_WR_PROTECT = 0x7a83;
    SYS_AFE_DAC = 512; /* 1.2*512/4096/0.05 = 3A, 其中0.05为母线采样电阻*/
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
    HALL_InitStruct.FilterLen = 512;               /* Hall信号数字滤波长度 512个时钟周期 */
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1; /* 设置Hall模块时钟分频系数 */
    HALL_InitStruct.Filter75_Ena = DISABLE;        /* Hall信号滤波方式，7判5模式或者全1有效模式 */
    HALL_InitStruct.HALL_Ena = ENABLE;             /* 模块使能 */
    HALL_InitStruct.Capture_IRQ_Ena = ENABLE;      /* 捕捉中断使能 */
    HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;     /* 超时中断使能 */
    HALL_InitStruct.CountTH = 9600000;             /* Hall模块计数模值，计数超过模值会产生超时中断 */

    HALL_Init(&HALL_InitStruct);
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
     TIM_TimerCmd(TIMER3, ENABLE); /* Timer0 模块使能 */
     TIM_TimerStrutInit(&TIM_InitStruct);//Timer结构体初始化


		 TIM_InitStruct.Timer_Filter0 = 1; /*CH0滤波，滤波宽度为Timer_Filter0*8个时钟周期*/
		 TIM_InitStruct.Timer_Filter1 = 1;
		 TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1; //12M
     TIM_TimerInit(TIMER3, &TIM_InitStruct);
		
     UTIMER_ECD1_CNT = 0;   
		 UTIMER_ECD1_TH = 4096;
		 UTIMER_ECD1_CFG = (0<<8); 

     UTIMER_CFG |= (1<<9);    
}

void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = 0;           /* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;      /* 模块时钟开启 */
    MCPWM_InitStructure.MCPWM_Cnt_EN = ENABLE; /* 主计数器开始计数使能开关 */
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12; /* 急停事件(来自IO口信号)数字滤波器时间设置 */
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;  /* 急停事件(来自比较器信号)数字滤波器时间设置 */

    MCPWM_InitStructure.MCPWM_PERIOD = PWM_PERIOD;              /* 计数周期设置 */
    MCPWM_InitStructure.TriggerPoint0 = (u16)(10 - PWM_PERIOD); /* MCPWM_TMR0 ADC触发事件T0 设置 */
    MCPWM_InitStructure.TriggerPoint1 = (u16)(PWM_PERIOD - 1);  /* MCPWM_TMR1 ADC触发事件T1 设置 */
    MCPWM_InitStructure.DeadTimeCH0N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH0P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2P = DEADTIME; /* 死区时间设置 */

#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)           /* CHxP 高有效， CHxN低电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;  /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE; /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;  /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = HIGH_LEVEL; /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = HIGH_LEVEL;
#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH) /* CHxP 高有效， CHxN高电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE; /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE; /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL; /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = LOW_LEVEL; /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = LOW_LEVEL;
#endif
#endif

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE; /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                                 还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/

    MCPWM_InitStructure.MCPWM_T0_UpdateEN = ENABLE;  /* MCPWM T0事件更新使能 */
    MCPWM_InitStructure.MCPWM_T1_UpdateEN = DISABLE; /* MCPWM T1事件更新 禁止*/

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    MCPWM_InitStructure.T1_Update_INT_EN = ENABLE; /* T0更新事件 中断使能或关闭 */
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE; /* T0更新事件 中断使能或关闭 */
#else
#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE; /* T0更新事件 中断使能或关闭 */
#endif
#endif
#endif

    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;             /* FAIL0事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL0_INPUT_EN = DISABLE;           /* FAIL0通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL0_Signal_Sel = FAIL_SEL_CMP;    /* FAIL0事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL0_Polarity = HIGH_LEVEL_ACTIVE; /* FAIL0事件极性选择，高有效 */

    MCPWM_InitStructure.FAIL1_INT_EN = ENABLE;              /* FAIL1事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL1_INPUT_EN = ENABLE;            /* FAIL1通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL1_Signal_Sel = FAIL_SEL_CMP;    /* FAIL1事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL1_Polarity = HIGH_LEVEL_ACTIVE; /* FAIL1事件极性选择，高有效或低有效 */

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
    ADC0_TRIG = BIT1;         /*硬件触发ADC MCPWM T1被使能 */
    ADC0_CFG |= BIT2;         /*状态机复位，idle状态，完成后自动请0 */
    MCPWM_TMR0 = PWM_PERIOD;  /*ADC采样时刻0设置为下桥关断中心点 */
    MCPWM_TMR1 = (u16)(-600); /*ADC采样时刻1设置为PWM中心点向后偏600个Clock*/
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
    MCPWM_TH00 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH01 = (PWM_PERIOD >> 2);
    MCPWM_TH10 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH11 = (PWM_PERIOD >> 2);
    MCPWM_TH20 = (u16)(-(PWM_PERIOD >> 2));
    MCPWM_TH21 = (PWM_PERIOD >> 2);

    PWMOutputs(ENABLE);
    while (1)
    {
    }
}

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_RegUpdate(void)
{
}

#else

#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_RegUpdate(void)
{
    MCPWM_TH00 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;
    MCPWM_TH01 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;

    MCPWM_TH10 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
    MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

    MCPWM_TH20 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
    MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
}

#endif

#ifdef TEST_FLASH
void Flash_Test(void)
{
    /**********************以下是调用Flash擦除，编程示例****************************/

    u8 testBuf[512] = {
        1,
        2,
        3,
        4,
        5,
    };
    volatile u8 flashRlt;

    erase_flag = 0x9A0D361F; //写擦除密码
    EraseSector(0x7800, 0);
    progm_flag = 0x9AFDA40C; //写编程密码
    flashRlt = ProgramPage(0x7800, 512, (u8 *)&testBuf[0], 0);
    /*******************************************************************************/
}
#endif

#endif
