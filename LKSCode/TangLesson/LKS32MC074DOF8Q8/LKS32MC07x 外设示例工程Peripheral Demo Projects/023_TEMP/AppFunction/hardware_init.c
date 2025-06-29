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
#include "hardware_init.h"
#include "lks32mc07x_lib.h"

#define  CNT0_PRE_DRIVER_POLARITY           P_HIGH__N_HIGH
#define  CNT1_PRE_DRIVER_POLARITY           P_HIGH__N_LOW

void UART_init(void);
void HALL_Perip_Init(void);
void SoftDelay(u32 cnt);

void DMA_init(void);
void GPIO0_Pin14Init(void);
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
    __disable_irq();                  /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;
	  IWDG_DISABLE();                   /* 关闭看门狗*/
    FLASH_CFG |= 0x00080000;          /* enable prefetch */

	  TempSensor_Init();
    ADC0_init();                      /* ADC初始化 */
	  GPIO0_Pin14Init();
    MCPWM_init();                     /* PWM初始化 */
    GPIO_init();                      /* GPIO初始化 */
    SoftDelay(100);                   /* 延时等待硬件初始化稳定 */

    NVIC_SetPriority(ADC0_IRQn, 1);
		NVIC_SetPriority(ADC1_IRQn, 2);
		NVIC_SetPriority(MCPWM0_IRQn, 1);

    NVIC_EnableIRQ(ADC0_IRQn);        /* enable the ADC0 interrupt */
    NVIC_EnableIRQ(ADC1_IRQn);
		NVIC_EnableIRQ(MCPWM0_IRQn);

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

    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 = BIT15;     /* BIT15:PLLPDN 开PLL */
    SoftDelay(100);            /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG = 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
    
    SYS_SFT_RST = 0xFFFFFF;
    SYS_SFT_RST = 0x0000;
    SYS_AFE_REG1 = BIT15;


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
    Clock_Init();  /* 时钟初始化 */
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
    ADC_InitStructure.IE         = ADC_SF1_IE | ADC_SF2_IE;          // 中断使能
    ADC_InitStructure.RE         = 0;                   // DMA请求使能
    ADC_InitStructure.NSMP       = ENABLE;              // 两段采样使能
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT右对齐使能
    ADC_InitStructure.CSMP       = DISABLE;             // 连续采样使能
    ADC_InitStructure.TCNT       = 1;                   // 触发一次采样所需的事件数
    ADC_InitStructure.TROVS      = DISABLE;             // 手动触发过采样使能，开启后一次采样需要多次触发
    ADC_InitStructure.OVSR       = 0;                   // 过采样率
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0 | ADC_TRIG_MCPWM0_T1;  // 触发信号
    ADC_InitStructure.S1         = 2;                   // 第一段常规采样次数
    ADC_InitStructure.S2         = 2;                   // 第二段常规采样次数
    ADC_InitStructure.IS1        = 1;                   // 空闲采样次数
    ADC_InitStructure.LTH        = 0;                   // ADC 模拟看门狗 0 下阈值
    ADC_InitStructure.HTH        = 0;                   // ADC 模拟看门狗 0 上阈值
    ADC_InitStructure.GEN        = 0;                   // ADC 模拟看门狗 0 对应使能位
    ADC_Init(ADC0, &ADC_InitStructure);
		
		ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.IE         = ADC_SF1_IE | ADC_SF2_IE;;          // 中断使能
    ADC_InitStructure.RE         = 0;                   // DMA请求使能
    ADC_InitStructure.NSMP       = ENABLE;             // 两段采样使能
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT右对齐使能
    ADC_InitStructure.CSMP       = DISABLE;             // 连续采样使能
    ADC_InitStructure.TCNT       = 2;                   // 触发一次采样所需的事件数
    ADC_InitStructure.TROVS      = DISABLE;             // 手动触发过采样使能，开启后一次采样需要多次触发
    ADC_InitStructure.OVSR       = 0;                   // 过采样率
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0 | ADC_TRIG_MCPWM0_T1;  // 触发信号
    ADC_InitStructure.S1         = 2;                   // 第一段常规采样次数
    ADC_InitStructure.S2         = 2;                   // 第二段常规采样次数
    ADC_InitStructure.IS1        = 1;                   // 空闲采样次数
    ADC_InitStructure.LTH        = 0;                   // ADC 模拟看门狗 0 下阈值
    ADC_InitStructure.HTH        = 0;                   // ADC 模拟看门狗 0 上阈值
    ADC_InitStructure.GEN        = 0;                   // ADC 模拟看门狗 0 对应使能位
    ADC_Init(ADC1, &ADC_InitStructure);
		
    ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);//清除所有中断标志位
    ADC_ClearIRQFlag(ADC1, ADC_ALL_IF);
		
    ADC_CHN_GAIN_CFG(ADC0,CHN0,ADC_CHANNEL_9,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0,CHN1,ADC_CHANNEL_9,ADC_GAIN7V2);
		ADC_CHN_GAIN_CFG(ADC0,CHN2,ADC_CHANNEL_9,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0,CHN3,ADC_CHANNEL_9,ADC_GAIN7V2);
		
    ADC_CHN_GAIN_CFG(ADC1,CHN0,ADC_CHANNEL_14,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1,CHN1,ADC_CHANNEL_14,ADC_GAIN3V6);
		ADC_CHN_GAIN_CFG(ADC1,CHN2,ADC_CHANNEL_14,ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1,CHN3,ADC_CHANNEL_14,ADC_GAIN3V6);
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
	  
	  /* MCPWM P1.10,P1.11;P3.10,P3.11;P2.9,P2.10 */
	  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_10, AF3_MCPWM);//CH3N
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_11, AF3_MCPWM);//CH3N
    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_10, AF3_MCPWM);//CH4P
    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_11, AF3_MCPWM);//CH4N
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_9,  AF3_MCPWM);//CH5P
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_10, AF3_MCPWM);//CH5N
		
		GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
    GPIO_Init(GPIO1, &GPIO_InitStruct);
		
		GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
    GPIO_Init(GPIO3, &GPIO_InitStruct);
		
		GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; 
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    
	  GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;  //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

}
void GPIO0_Pin14Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
		GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF3_MCPWM);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_14 ;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
}
#define MCPWM_PERIOD0 3000
#define MCPWM_PERIOD1 3000
#define DEADTIME 100
void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;
    MCPWM_StructInit(&MCPWM_InitStructure);
    
	  MCPWM_InitStructure.MCLK_EN = ENABLE;              /* 模块时钟开启 */
    MCPWM_InitStructure.CLK_DIV = 0;                   /* MCPWM时钟分频设置 */
	
    MCPWM_InitStructure.IO_CMP_FLT_CLKDIV  = 12;  /* 急停事件(来自IO口信号)数字滤波器时间设置 */
	
	  MCPWM_InitStructure.AUEN = MCPWM0_ALL_AUPDAT; /*自动加载使能*/
	  
	  /* MCPWM0_CNT0 */
	  
    MCPWM_InitStructure.BASE_CNT0_EN = ENABLE;                /* 主计数器开始计数使能开关 */
	  MCPWM_InitStructure.TH0 = MCPWM_PERIOD0;                    /* 计数周期设置即MCPWM输出周期*/
	
	  MCPWM_InitStructure.TH00 = (u16)(-(MCPWM_PERIOD0 >> 2));
	  MCPWM_InitStructure.TH01 = (MCPWM_PERIOD0 >> 2);
	  MCPWM_InitStructure.TH10 = (u16)(-(MCPWM_PERIOD0 >> 2));
	  MCPWM_InitStructure.TH11 = (MCPWM_PERIOD0 >> 2);
	  MCPWM_InitStructure.TH20 = (u16)(-(MCPWM_PERIOD0 >> 2));
	  MCPWM_InitStructure.TH21 = (MCPWM_PERIOD0 >> 2);
		
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
    MCPWM_InitStructure.DeadTimeCH012N = DEADTIME;/* 死区时间设置 */
    MCPWM_InitStructure.DeadTimeCH012P = DEADTIME;
	  MCPWM_InitStructure.CMP_CTRL_CNT0  = DISABLE ;/* CMP控制CNT0失能 */
	  MCPWM_InitStructure.EVT_CNT0_EN    = DISABLE ;/* MCPWM_CNT1外部触发失能 */
	  MCPWM_InitStructure.EVT0           = DISABLE ;
	
	  MCPWM_InitStructure.TR0_UP_INTV     = DISABLE;
	  MCPWM_InitStructure.TR0_T0_UpdateEN = ENABLE ;
	  MCPWM_InitStructure.TR0_T1_UpdateEN = DISABLE ;
		MCPWM_InitStructure.TR0_AEC         = DISABLE;
		
		MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE; /* T0更新事件 中断关闭 */
		MCPWM_InitStructure.T1_Update0_INT_EN = ENABLE ; /* T1更新事件 中断使能 */
		MCPWM_InitStructure.Update1_INT_EN = ENABLE;     /* CNT0 更新事件 中断使能  */
		
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

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = HIGH_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = HIGH_LEVEL;
#else
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

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_LOW_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_LOW_LEVEL;
#endif
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
		
		MCPWM_InitStructure.FAIL1_INPUT_EN   = DISABLE ;//FAIL_0CAP
		MCPWM_InitStructure.FAIL1_INT_EN     = DISABLE;
		MCPWM_InitStructure.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_IO ;//FAIL_0CAP
		MCPWM_InitStructure.FAIL1_Polarity   = MCPWM0_HIGH_LEVEL_ACTIVE ;
		
		MCPWM_InitStructure.HALT_PRT0        = DISABLE ;
		MCPWM_InitStructure.FAIL_0CAP        = DISABLE ;
		
		
	  /* MCPWM0_CNT1 */
		MCPWM_InitStructure.BASE_CNT1_EN = ENABLE;                /* 主计数器开始计数使能开关 */
	  MCPWM_InitStructure.TH1 = MCPWM_PERIOD1;              /* 计数周期设置即MCPWM输出周期*/
		MCPWM_InitStructure.TH30 = (u16)(-(MCPWM_PERIOD1 >> 2));
		MCPWM_InitStructure.TH31 = (MCPWM_PERIOD1 >> 2);
		MCPWM_InitStructure.TH40 = (u16)(-(MCPWM_PERIOD1 >> 2));
		MCPWM_InitStructure.TH41 = (MCPWM_PERIOD1 >> 2);
		MCPWM_InitStructure.TH50 = (u16)(-(MCPWM_PERIOD1 >> 2));
		MCPWM_InitStructure.TH51 = (MCPWM_PERIOD1 >> 2);
    
    MCPWM_InitStructure.MCPWM_WorkModeCH3 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
    MCPWM_InitStructure.MCPWM_WorkModeCH4 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH5 = MCPWM0_CENTRAL_PWM_MODE;

    MCPWM_InitStructure.DeadTimeCH345N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH345P = DEADTIME;
    MCPWM_InitStructure.CMP_CTRL_CNT1  = DISABLE ;/* CMP控制CNT1失能 */
	  MCPWM_InitStructure.EVT_CNT1_EN    = DISABLE ;/* MCPWM_CNT1外部触发失能 */
    MCPWM_InitStructure.EVT1           = DISABLE ;
    
		MCPWM_InitStructure.TR1_UP_INTV     = DISABLE;
	  MCPWM_InitStructure.TR1_T0_UpdateEN = ENABLE ;
	  MCPWM_InitStructure.TR1_T1_UpdateEN = DISABLE ;
		MCPWM_InitStructure.TR1_AEC         = DISABLE;
	
    MCPWM_InitStructure.T0_Update1_INT_EN = DISABLE;  /* CNT1 T0更新事件 中断使能 */
		MCPWM_InitStructure.T1_Update1_INT_EN = ENABLE ;  /* CNT1 T1更新事件 中断关闭  */
		MCPWM_InitStructure.Update1_INT_EN = ENABLE;      /* CNT1 更新事件 中断使能  */
		
    MCPWM_InitStructure.TMR0 = (u16)(10 - MCPWM_PERIOD1); /* MCPWM_TMR0  设置 */
    MCPWM_InitStructure.TMR1 = (u16)(MCPWM_PERIOD1 - 1);  /* MCPWM_TMR1  设置 */
		MCPWM_InitStructure.TMR2 = (u16)(10 - MCPWM_PERIOD1); /* MCPWM_TMR2  设置 */
    MCPWM_InitStructure.TMR3 = (u16)(MCPWM_PERIOD1 - 1);  /* MCPWM_TMR3  设置 */ 

#if (CNT1_PRE_DRIVER_POLARITY == P_HIGH__N_LOW)                    /* CHxP 高有效， CHxN低电平有效 */
    MCPWM_InitStructure.CH3N_Polarity_INV = ENABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH4N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH4P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH5N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH5P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH3N_CH3P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH4N_CH4P =  DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH5N_CH5P =  DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH3P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH3N_default_output = MCPWM0_HIGH_LEVEL;
    MCPWM_InitStructure.CH4P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH4N_default_output = MCPWM0_HIGH_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH5P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH5N_default_output = MCPWM0_HIGH_LEVEL;
#else
#if (CNT1_PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP 高有效， CHxN高电平有效 */
    MCPWM_InitStructure.CH3N_Polarity_INV = DISABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH4N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH4P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH5N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH5P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH3N_CH3P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH4N_CH4P =  DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH5N_CH5P =  DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH3P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH3N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH4P_default_output = LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH4N_default_output = LOW_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH5P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH5N_default_output = LOW_LEVEL;
#endif
#endif

    MCPWM_InitStructure.CH3N_FAIL_EN = ENABLE ;
		MCPWM_InitStructure.CH3P_FAIL_EN = ENABLE ;
		MCPWM_InitStructure.CH4N_FAIL_EN = ENABLE ;
		MCPWM_InitStructure.CH4P_FAIL_EN = ENABLE ;
		MCPWM_InitStructure.CH5N_FAIL_EN = ENABLE ;
		MCPWM_InitStructure.CH5P_FAIL_EN = ENABLE ;
		
    MCPWM_InitStructure.FAIL2_INPUT_EN   = DISABLE ;//FAIL_0CAP
		MCPWM_InitStructure.FAIL2_INT_EN     = DISABLE;
		MCPWM_InitStructure.FAIL2_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
		MCPWM_InitStructure.FAIL2_Polarity   = MCPWM0_HIGH_LEVEL_ACTIVE ;
		
		MCPWM_InitStructure.FAIL3_INPUT_EN   = DISABLE ;//FAIL_0CAP
		MCPWM_InitStructure.FAIL3_INT_EN     = DISABLE;
		MCPWM_InitStructure.FAIL3_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
		MCPWM_InitStructure.FAIL3_Polarity   = MCPWM0_HIGH_LEVEL_ACTIVE ;
		
		MCPWM_InitStructure.HALT_PRT1        = DISABLE ;
		MCPWM_InitStructure.FAIL_1CAP        = DISABLE ;
		
		MCPWM_InitStructure.TMR2_TB        = 0;/* MCPWM TMR2时基（计数器）选择 0：时基0；1：时基1 */
	  MCPWM_InitStructure.TMR3_TB        = 1;/* MCPWM TMR3时基（计数器）选择 0：时基0；1：时基1 */

    MCPWM_Init(&MCPWM_InitStructure);
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
    MCPWM0_TH00 = (u16)(-(MCPWM_PERIOD0 >> 2));
    MCPWM0_TH01 = (MCPWM_PERIOD0 >> 2);
    MCPWM0_TH10 = (u16)(-(MCPWM_PERIOD0 >> 2));
    MCPWM0_TH11 = (MCPWM_PERIOD0 >> 2);
    MCPWM0_TH20 = (u16)(-(MCPWM_PERIOD0 >> 2));
    MCPWM0_TH21 = (MCPWM_PERIOD0 >> 2);
    
    MCPWM0_TH30 = (u16)(-(MCPWM_PERIOD1 >> 2));
    MCPWM0_TH31 = (MCPWM_PERIOD1 >> 2);
    MCPWM0_TH40 = (u16)(-(MCPWM_PERIOD1 >> 2));
    MCPWM0_TH41 = (MCPWM_PERIOD1 >> 2);
    MCPWM0_TH50 = (u16)(-(MCPWM_PERIOD1 >> 2));
    MCPWM0_TH51 = (MCPWM_PERIOD1 >> 2);

    PWMOutputs(ENABLE);
    while(1)
    {
    }
}



