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

RC_t PWM_DutyRC;

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
	  NVIC_SetPriority(TIMER3_IRQn, 1); /*TIMER3中断优先级配置*/
    NVIC_EnableIRQ(TIMER3_IRQn);      /*使能UTimer定时器中断*/
  	SoftDelay(100);                   /* 等待硬件初始化完毕*/
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
 2023/3/2      V1.0          HuangMG             创建
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
 2023/3/2      V1.0          HuangMG             创建
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
 2023/3/2      V1.0          HuangMG             创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

	  //配置P1.3 UTIMER3_CH1
	  GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;  //GPIO输入模式
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
 2023/3/2      V1.0          HuangMG             创建
 *******************************************************************************/
void UTimer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerStrutInit(&TIM_InitStruct);                  /* Timer结构体初始化*/
	  TIM_InitStruct.Timer_SRC0 = CAP_SRC_TCH1;             /* 定时器0通道0捕获定时器0通道1的输入信号*/
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP; /* 设置Timer CH0为捕获模式 */
    TIM_InitStruct.Timer_CAP0_CLR_EN =ENABLE;             /* 当发生CAP0捕获事件时，清零Timer计数器*/
	  TIM_InitStruct.Timer_CH0_RE_CAP_EN = ENABLE;          /* 使能Timer通道0上升沿捕获*/
	  TIM_InitStruct.Timer_CH0_FE_CAP_EN = DISABLE;         /* 关闭Timer通道0下降沿捕获*/
	
	  TIM_InitStruct.Timer_SRC1 = CAP_SRC_TCH1;             /* 定时器0通道1捕获定时器0通道1的输入信号*/
  	TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CAP; /* 设置Timer CH1为捕获模式 */
    TIM_InitStruct.Timer_CAP1_CLR_EN = DISABLE;           /* 当发生CAP1捕获事件时，清零Timer计数器*/
	  TIM_InitStruct.Timer_CH1_RE_CAP_EN = DISABLE;         /* 使能Timer通道1上升沿捕获*/
	  TIM_InitStruct.Timer_CH1_FE_CAP_EN = ENABLE;          /* 关闭Timer通道1下降沿捕获*/
	
	  TIM_InitStruct.Timer_TH = 96000000;    							  /* 定时器计数门限初始值96000000*/	  
    TIM_InitStruct.Timer_FLT = 0;  										    /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;       /* 设置Timer模块时钟2分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_ZC;        /* 开启Timer模块过零中断*/
    TIM_TimerInit(UTIMER3, &TIM_InitStruct); 
    TIM_TimerCmd(UTIMER3, ENABLE);                        /* Timer3 模块使能 */
}





/*******************************************************************************
 函数名称：    s16 lowPass_filter(RC_t *rc,s16 signal)
 功能描述：    低通滤波函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG             创建
 *******************************************************************************/
s16 lowPass_filter(RC_t *rc,s16 signal)
{
    s32 t_inter;
    t_inter = (signal - (s16)(rc->yk_1>>16)) * (rc->coef);
    rc->yk_1 += t_inter;
    return(rc->yk_1>>16);
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
 2023/3/2      V1.0          HuangMG             创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}




