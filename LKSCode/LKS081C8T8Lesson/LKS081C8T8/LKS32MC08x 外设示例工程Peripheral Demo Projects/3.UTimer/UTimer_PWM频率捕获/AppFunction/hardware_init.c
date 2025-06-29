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

RC_t gS_UTIMER_RC;

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
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/
    GPIO_init();             /* GPIO初始化 */
    UTimer_init();           /* UTimer初始化 */
    SoftDelay(100);          /* 等待硬件初始化完毕*/
    NVIC_SetPriority(TIMER0_IRQn, 0); /*TIMER0中断优先级配置必须最高*/
    NVIC_EnableIRQ(TIMER0_IRQn);      /*使能UTimer定时器中断*/
	  SYS_WR_PROTECT = 0x0;    /*关闭系统寄存器写操作*/
 #if POWER_MODE	
    SYS_VolSelModuleEnableIRQ(MCU_POWER_5v0);/*MCU电源中断使能函数*/ 
	#else
		SYS_VolSelModuleEnableIRQ(MCU_POWER_3v3);/*MCU电源中断使能函数*/ 
 #endif	
	  __enable_irq();          /* 开启中断 */
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

    /* 配置UTimer0  TIM0_CH1: P0.14*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO0,GPIO_PinSource_14,AF7_TIMER01); //P0.14复用为timer0的输出模式
		
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
 其它说明：    定时器 96000/96000000 = 0.001s = 1kHz
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTimer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerStrutInit(&TIM_InitStruct);                   //Timer结构体初始化
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP;  /* 设置Timer0 CH0 为捕获模式 */
    TIM_InitStruct.Timer_CH0_CapMode = TIMER_CapMode_Fall; /*下降沿捕获*/
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CAP;  /* 设置Timer0 CH1 为捕获模式 */
    TIM_InitStruct.Timer_CH1_CapMode = TIMER_CapMode_Rise; /*上升沿捕获*/
    TIM_InitStruct.Timer_TH = 60000;                         /* 定时器0和1计数门限初始值最大65535*/

    TIM_InitStruct.Timer_Filter0 = 15; /*CH0滤波，滤波宽度为Timer_Filter0*8个时钟周期*/
    TIM_InitStruct.Timer_Filter1 = 15;

    TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1;                       /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH1 | Timer_IRQEna_Zero; /* 开启Timer模块比较中断*/
    TIM_TimerInit(TIMER0, &TIM_InitStruct);   
	
	  TIM_TimerCmd(TIMER0, ENABLE); /* Timer0 模块使能 */
}



/*******************************************************************************
 函数名称：    u16 InPutPulse_filter(u32 temp)
 功能描述：    UTIMER捕获PWM频率滤波函数
 输入参数：    temp：滤波系数 范围 0 ~ 1
 输出参数：    无
 返 回 值：    无
 其它说明：    低通滤波系数设置temp，系数越低滤波深度越高，频率波动越小，但频率调节延迟越大
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/6/14      V1.0           HuangMG           创建
 *******************************************************************************/
u16 InPutPulse_filter(u16 temp)
{
		static u32 s_temp0 = 0;
		static u32 s_temp1 = 0;
		static u32 s_temp2 = 0;
		static u32 s_temp3 = 0;
		static u32 s_temp4 = 0;
	  static u32 s_temp5 = 0;
	  static u32 s_tempout = 0;
	  s_temp4 = s_temp3;
    s_temp3 = s_temp2;
		s_temp2 = s_temp1;
		s_temp1 = s_temp0;
		s_temp0 = temp;
	
	  if(temp == s_temp0 )
		{
			if(temp == s_temp1)
			{
				if(temp == s_temp2)
				{
					if(temp == s_temp3)
					{
						if(temp == s_temp4)
						{
							s_tempout = temp;
						}else{
									s_tempout = s_temp5;
								 }
					}else{
								s_tempout = s_temp5;
							 }
				}else{
								s_tempout = s_temp5;
							}
			}else{
						 s_tempout = s_temp5;
					 }
		 }else{
			   s_tempout = s_temp5;
		 }
     s_temp5 = s_tempout;
		 
		 return (u16)lowPass_filter(&gS_UTIMER_RC,s_tempout);//低通滤波
}

/*******************************************************************************
 函数名称：    s16 lowPass_filter(RC_t *rc,s16 signal)
 功能描述：    低通滤波
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
s16 lowPass_filter(RC_t *rc,s16 signal)
{
    s32 t_inter;
    t_inter = (signal - (s16)(rc->yk_1>>16)) * (rc->coef);
    rc->yk_1 += t_inter;
    return(rc->yk_1>>16);
}
/*******************************************************************************
 函数名称：    void InPutPulse_init(float temp)
 功能描述：    UTIMER捕获PWM频率变量输出化
 输入参数：    temp：滤波系数 范围 0 ~ 1
 输出参数：    无
 返 回 值：    无
 其它说明：    低通滤波系数设置temp，系数越低滤波深度越高，频率波动越小，但频率调节延迟越大
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void InPutPulse_init(float temp)
{
  gS_UTIMER_RC.coef = (u16)(65535 * temp);
	gS_UTIMER_RC.yk_1 = 0;
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


