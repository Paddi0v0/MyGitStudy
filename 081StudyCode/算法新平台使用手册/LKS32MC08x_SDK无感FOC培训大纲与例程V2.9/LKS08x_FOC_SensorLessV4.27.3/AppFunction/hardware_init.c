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
#include "global_variable.h"
#include "MC_Parameter.h"
#include "SEGGER_RTT.h"

void UART_init(void);
void HALL_Perip_init(void);
void SoftDelay(u32 cnt);


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
    
    FLASH_CFG |= 0x00080000;          /* enable prefetch */

    DSP_Init();                       /* DSP模块初始化*/
    UART_init();                      /* 串口初始化UART0*/
    ADC0_init();                      /* ADC初始化 */
    MCPWM_init();                     /* PWM初始化 */
    UTimer_init();                    /* 通用计数器初始化 */
    GPIO_init();                      /* GPIO初始化 */
    DAC_init();                       /* DAC 初始化 */
    PGA_init();                       /* PGA 初始化 */
    CMP_init();                       /* 比较器初始化 */
    HALL_Perip_init();                /* HALL模块初始化 */
    TempSensor_Init();                /* 温度传感器初始化 */

    SoftDelay(100);                   /* 延时等待硬件初始化稳定 */

    DSP_SC = BIT1;                    /* DSP Paused */
     
    NVIC_SetPriority(PWRDN_IRQn, 0);  /*PWRDN_IRQn中断优先级设置为0*/
    NVIC_SetPriority(UART0_IRQn, 2);  /* 设置UART0中断优先级为2 | 共0，1，2，3四级中断优先级，0为最高*/
    NVIC_SetPriority(ADC0_IRQn, 1);
    NVIC_SetPriority(HALL_IRQn, 2);
    NVIC_SetPriority(MCPWM_IRQn, 2);
    NVIC_SetPriority(CMP_IRQn, 0);    /* 设置CMP_IRQn中断优先级为0 | 共0，1，2，3四级中断优先级，0为最高*/
    NVIC_SetPriority(TIMER0_IRQn, 2);

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    NVIC_SetPriority(MCPWM_IRQn, 1);   
    NVIC_EnableIRQ (MCPWM_IRQn);
#else
    NVIC_EnableIRQ(ADC0_IRQn);        /* enable the ADC0 interrupt */
#endif

#if ((ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) || (ROTOR_SENSOR_TYPE == ROTOR_HALL2SENSORLESS))
    NVIC_EnableIRQ (HALL_IRQn);       /* enable the HALL interrupt */
#endif
    NVIC_EnableIRQ (TIMER0_IRQn);
    NVIC_EnableIRQ (CMP_IRQn);        /* 打开比较器中断 */ 
    NVIC_EnableIRQ(PWRDN_IRQn);       /* 打开电源检测中断 */ 
		
#if (RTT_FUNCTION == FUNCTION_ON)
    /* JScope RTT模式初始化 */
    SEGGER_RTT_ConfigUpBuffer(1, "JScope_i2i2i2", bRttBuf, 2048, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif 

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
 2015/11/5      V1.0           Howlet Li          创建

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/4/17      V1.1           Howlet Li          增加延时函数，等待PLL稳定
 *******************************************************************************/
void Clock_Init(void)
{

    SYS_WR_PROTECT = 0x7a83;      /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;        /* BIT15:PLLPDN 开PLL */
	  SoftDelay(100);               /* 延时100us, 等待PLL稳定 21.4.17*/
	  SYS_AFE_REG6 |=POWER_4V5 << 8;//配置为4.5V监控，可根据实际配置其它档位：3.6V/3.9V/4.2V/4.5V
    SoftDelay(100);              /* 延时100us, 等待电源检测配置完毕*/
	  while(SYS_AFE_CMP & BIT13){};  //等待外部5VOK 
    SYS_CLK_CFG = 0x000001ff;   /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */

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
   SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
   SYS_SFT_RST = 0xfff;
  
   Reg_Clr((u32)(&SYS_AFE_REG0),8); /* 清SYS_AFE_REG0~SYS_AFE_REG7 */
   Reg_Clr((u32)(&ADC0_CHN0),12);
   Reg_Clr((u32)(&ADC0_GAIN0),2);
   Reg_Clr((u32)(&ADC0_IE),6);

   Reg_Clr((u32)(&DMA_CCR0),18);
   Reg_Clr(GPIO0_BASE,12);          /* 清GPIO0 相关的12个寄存器 */
   Reg_Clr(GPIO1_BASE,12);
   Reg_Clr(GPIO2_BASE,12);
   Reg_Clr(GPIO3_BASE,12);   
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
void SystemInit(void)
{
//    Reg_Reset();   /* 初始化所有外设寄存器 */
    Clock_Init();  /* 时钟初始化 */
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
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA0, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA1, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA2, ENABLE);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA3, ENABLE);
    
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
    CMP_InitTypeDef CMP_InitStruct;

    CMP_StructInit(&CMP_InitStruct);

    CMP_InitStruct.CMP0_EN = DISABLE;           /* 比较器0开关 */
    CMP_InitStruct.CMP0_SELN = CMP_SELN_DAC;    /* CMP0_N 内部参考 */
    CMP_InitStruct.CMP0_SELP = CMP0_SELP_OPA0_IP; /* CMP0_P CMP0_OPA0IP */
    CMP_InitStruct.CMP0_IN_EN = DISABLE;        /* 比较器信号输入使能 */
    CMP_InitStruct.CMP0_IE = DISABLE;           /* 比较器0信号中断使能 */

    CMP_InitStruct.CMP1_EN = ENABLE;            /* 比较器1开关 */
    CMP_InitStruct.CMP1_SELN = CMP_SELN_DAC;    /* CMP1_N 内部参考 */
    CMP_InitStruct.CMP1_SELP = CMP1_SELP_IP0;    /* CMP1_P CMP1_IP0 */
    CMP_InitStruct.CMP1_IN_EN = ENABLE;         /* 比较器信号输入使能 */  
    CMP_InitStruct.CMP1_IE = ENABLE;            /* 比较器1信号中断使能 */
    
    CMP_InitStruct.FIL_CLK10_DIV16 = 15;        /* 即滤波宽度=tclk 周期*16*CMP_FltCnt */
    CMP_InitStruct.CLK10_EN = ENABLE;           /* 时钟使能 */

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
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC, ENABLE);
    SYS_WR_PROTECT = 0x7a83;
  
    SYS_AFE_REG1 &= ~((u32)0x03 << 6);
    SYS_AFE_REG1 |= (DAC_RANGE_1V2 << 6);  /* 设置DAC满量程为1.2V；00:3V| 01:1.2V| 10:4.85V */
  
    if(((SYS_AFE_REG1 >> 6)&0x03) == DAC_RANGE_1V2)
    {/* 加载DAC 1.2V量程校正值 */
       SYS_AFE_DAC_DC = Read_Trim(0x00000344);
       SYS_AFE_DAC_AMC = Read_Trim(0x00000334);
    }
    else if(((SYS_AFE_REG1 >> 6)&0x03) == DAC_RANGE_3V0)
    { /* 加载DAC 3.0V量程校正值 */
       SYS_AFE_DAC_DC = Read_Trim(0x00000340);
       SYS_AFE_DAC_AMC = Read_Trim(0x00000330);
    }
    else if(((SYS_AFE_REG1 >> 6)&0x03) == DAC_RANGE_4V85)
    { /* 加载DAC 4.85V量程校正值 */
       SYS_AFE_DAC_DC = Read_Trim(0x00000348);
       SYS_AFE_DAC_AMC = Read_Trim(0x00000338);
    }

    SYS_AFE_DAC = 147;                     /* 1.2*147/4096/0.005 = 6A, 其中0.005为母线采样电阻*/ 
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

///*******************************************************************************
// 函数名称：    void UART0_init(void)
// 功能描述：    UART1寄存器配置
// 输入参数：    无
// 输出参数：    无
// 返 回 值：    无
// 其它说明：
// 修改日期      版本号          修改人            修改内容
// -----------------------------------------------------------------------------
// 2015/11/5      V1.0           Howlet Li          创建
// *******************************************************************************/
//void UART1_init(void)
//{

//    UART_InitTypeDef UART_InitStruct;
//    
//    UART_StructInit(&UART_InitStruct);
//    UART_InitStruct.BaudRate = 38400;                 /* 设置波特率38400 */
//    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* 发送数据长度8位 */
//    UART_InitStruct.StopBits = UART_STOPBITS_1b;
//    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* 先发送LSB */
//    UART_InitStruct.ParityMode = UART_Parity_NO;      /* 无奇偶校验 */
//    UART_InitStruct.IRQEna = 0;
//    UART_Init(UART1, &UART_InitStruct);

//}


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
void ADC0_init(void)
{

    ADC_InitTypeDef ADC_InitStructure;
    
    ADC_StructInit(&ADC_InitStructure);
    
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;               /* ADC转换结果采用左对齐格式 */
    ADC_InitStructure.Trigger_Cnt = 0;                      /* 发生一次触发事件执行一段转换动作 */  
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_InitStructure.FirSeg_Ch = 2;                        /* 第一段共采样6个通道 */
    ADC_InitStructure.SecSeg_Ch = 8;                        /* 第二段共采样0个通道 */
    ADC_InitStructure.MCPWM_Trigger_En = ADC_MCPWM_T0_TRG | ADC_MCPWM_T1_TRG;;  /* 打开MCPWM_T0 MCPWM_T1硬件触发事件 */
    ADC_InitStructure.Trigger_Mode = ADC_2SEG_TRG;          /* 设置ADC转换模式为双段式采样 */ 
    ADC_InitStructure.IE = ADC_EOS1_IRQ_EN;                 /* ADC第一段采样结束中断使能 */  
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    ADC_InitStructure.FirSeg_Ch = 6;                        /* 第一段共采样6个通道 */
    ADC_InitStructure.SecSeg_Ch = 0;                        /* 第二段共采样0个通道 */
    ADC_InitStructure.MCPWM_Trigger_En = ADC_MCPWM_T0_TRG ; /* 打开MCPWM_T0 MCPWM_T1硬件触发事件 */
    ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;          /* 设置ADC转换模式为单段式采样 */
    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;                 /* ADC第一段采样结束中断使能 */  
#else
#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)) 
    ADC_InitStructure.FirSeg_Ch = 6;                        /* 第一段共采样6个通道 */
    ADC_InitStructure.SecSeg_Ch = 0;                        /* 第二段共采样0个通道 */
    ADC_InitStructure.MCPWM_Trigger_En = ADC_MCPWM_T0_TRG ; /* 打开MCPWM_T0 MCPWM_T1硬件触发事件 */
    ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;          /* 设置ADC转换模式为单段式采样 */
    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;                 /* ADC第一段采样结束中断使能 */  
#endif  
#endif  
#endif

    ADC_Init(ADC0, &ADC_InitStructure);

    ADC0_IF |= 0xFF;
    
    ADC_NormalModeCFG();
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
void HALL_Perip_init(void)
{

    HALL_InitTypeDef HALL_InitStruct;
   
    HALL_StructInit(&HALL_InitStruct);
    HALL_InitStruct.FilterLen = 512;                /* Hall信号数字滤波长度 512个时钟周期 */
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1;  /* 设置Hall模块时钟分频系数 */
    HALL_InitStruct.Filter75_Ena = DISABLE;         /* Hall信号滤波方式，7判5模式或者全1有效模式 */
    HALL_InitStruct.HALL_Ena = ENABLE;              /* 模块使能 */
    HALL_InitStruct.Capture_IRQ_Ena = ENABLE;       /* 捕捉中断使能 */
    HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;      /* 超时中断使能 */
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
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);
    /* 内置栅极驱动器的型号，P1.12/ P1.15/ P3.13三个IO口必须设置为输出态 */
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
//    GPIO_Init(GPIO1, &GPIO_InitStruct);
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
//    GPIO_Init(GPIO3, &GPIO_InitStruct);
	
	  /*KEY_START P2.11 ,KEY_STOP P2.12*/
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIO2, &GPIO_InitStruct);


#if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) 
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF2_HALL);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF2_HALL);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_6, AF2_HALL);
#endif    
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
    
    TIM_TimerCmd(TIMER0, ENABLE);                          /* Timer0 模块使能 */

    TIM_TimerStrutInit(&TIM_InitStruct);
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP;  /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH0Output = 0;                    /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP;  /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_None;
    TIM_InitStruct.Timer_CH1Output = 0;                    /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 48000;                       /* 设置计数器计数模值 */
    TIM_InitStruct.Timer_CMP0 = 24000;                     /* 设置比较模式的CH0比较值 */
    TIM_InitStruct.Timer_CMP1 = 500;
    TIM_InitStruct.Timer_Filter0 = 0;                      /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_Filter1 = 0;
    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1;          /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_Zero;       /* 开启Timer模块过0中断 */
    TIM_TimerInit(TIMER0, &TIM_InitStruct);

}

void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);
    
    MCPWM_InitStructure.CLK_DIV = 0;                          /* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;                     /* 模块时钟开启 */
    MCPWM_InitStructure.MCPWM_Cnt_EN = ENABLE;                /* 主计数器开始计数使能开关 */
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12;                /* 急停事件(来自IO口信号)数字滤波器时间设置 */
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;                 /* 急停事件(来自比较器信号)数字滤波器时间设置 */

    MCPWM_InitStructure.MCPWM_PERIOD = PWM_PERIOD;            /* 计数周期设置 */
    MCPWM_InitStructure.TriggerPoint0 = (u16)(10 - PWM_PERIOD); /* MCPWM_TMR0 ADC触发事件T0 设置 */
    MCPWM_InitStructure.TriggerPoint1 = (u16)(PWM_PERIOD - 1);/* MCPWM_TMR1 ADC触发事件T1 设置 */
    MCPWM_InitStructure.DeadTimeCH0N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH0P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2P = DEADTIME;              /* 死区时间设置 */

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

    MCPWM_InitStructure.MCPWM_T0_UpdateEN = ENABLE;           /* MCPWM T0事件更新使能 */
    MCPWM_InitStructure.MCPWM_T1_UpdateEN = DISABLE;          /* MCPWM T1事件更新 禁止*/

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    MCPWM_InitStructure.T1_Update_INT_EN = ENABLE;           /* T0更新事件 中断使能或关闭 */
#else
#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE;           /* T0更新事件 中断使能或关闭 */
#else
#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)) 
    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE;           /* T0更新事件 中断使能或关闭 */
#endif    
#endif
#endif

    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;               /* FAIL0事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL0_INPUT_EN = DISABLE;             /* FAIL0通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL0_Signal_Sel = FAIL_SEL_CMP;      /* FAIL0事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL0_Polarity = HIGH_LEVEL_ACTIVE;   /* FAIL0事件极性选择，高有效 */

    MCPWM_InitStructure.FAIL1_INT_EN = ENABLE;                /* FAIL1事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL1_INPUT_EN = ENABLE;              /* FAIL1通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL1_Signal_Sel = FAIL_SEL_CMP;      /* FAIL1事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL1_Polarity = HIGH_LEVEL_ACTIVE;   /* FAIL1事件极性选择，高有效或低有效 */ 
  
    MCPWM_Init(&MCPWM_InitStructure);
    
    mIPD_CtrProc.hDriverPolarity = MCPWM_IO01;                /* 读出驱动极性 */
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
    MCPWM_TMR1 = (-600);  /*ADC采样时刻1设置为PWM中心点向后偏600个Clock*/
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
    MCPWM_TH00 = (-(PWM_PERIOD >> 2));
    MCPWM_TH01 = (PWM_PERIOD >> 2);
    MCPWM_TH10 = (-(PWM_PERIOD >> 2));
    MCPWM_TH11 = (PWM_PERIOD >> 2);
    MCPWM_TH20 = (-(PWM_PERIOD >> 2));
    MCPWM_TH21 = (PWM_PERIOD >> 2);

    PWMOutputs(ENABLE);
    while(1)
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
	
    MCPWM_TH00 = struFOC_CurrLoop.mVoltUVW_NegPWM.nPhaseU;
    MCPWM_TH01 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;

    MCPWM_TH10 = struFOC_CurrLoop.mVoltUVW_NegPWM.nPhaseV;
    MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

    MCPWM_TH20 = struFOC_CurrLoop.mVoltUVW_NegPWM.nPhaseW;
    MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;

}





#else

#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)||(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)\
     || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
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
	  if(struFOC_CtrProc.bMotorDirtionCtrlPhase == CW)
		{
			MCPWM_TH10 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
			MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

			MCPWM_TH20 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
			MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
	}else{
	    MCPWM_TH10 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
      MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;

      MCPWM_TH20 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
      MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
   }

}


#endif

#ifdef TEST_FLASH
void Flash_Test(void)
{
/**********************以下是调用Flash擦除，编程示例****************************/
 
    u8 testBuf[512] = {1,2,3,4,5,};
    volatile u8 flashRlt;
    
    erase_flag = 0x9A0D361F;   //写擦除密码 
    EraseSector(0x7800,0);
    progm_flag = 0x9AFDA40C;   //写编程密码
    flashRlt = ProgramPage(0x7800, 512, (u8*)&testBuf[0], 0);
/*******************************************************************************/
}
#endif

#endif


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




