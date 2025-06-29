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
    SYS_WR_PROTECT = 0x7a83;          /* 解除系统寄存器写保护 */
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
 2023/3/2      V1.0          HuangMG             创建
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
 2023/3/2      V1.0          HuangMG            创建
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
 2023/3/2      V1.0          HuangMG            创建
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
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

	  //配置P0.13 QEP0_Z
	  GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;  //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
	  //配置P2.11 QEP0_T1  P2.12 QEP0_T2
		GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;  //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0,GPIO_PinSource_13,AF8_TIMER23); //复用为timer2的编码器Z信号
    GPIO_PinAFConfig(GPIO2,GPIO_PinSource_11,AF8_TIMER23); //复用为timer2的编码器T1信号
    GPIO_PinAFConfig(GPIO2,GPIO_PinSource_12,AF8_TIMER23); //复用为timer2的编码器T2信号

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
void UTimer_init(void)
{
    TIM_QEPInitTypeDef TIM_QEPInitStruct;

    TIM_QEPStructInit(&TIM_QEPInitStruct);                   /* Timer结构体初始化*/
	  TIM_QEPInitStruct.QEP_FE_CNT_EN = DISABLE;               /* 使能下降沿进行计数，ENABLE:使能 DISABLE:失能*/
	  TIM_QEPInitStruct.QEP_Mode = QEP_Mode_T1;                /* 编码器模式选择*/
	  TIM_QEPInitStruct.QEP_ClockDiv = QEP_CLK_DIV1;           /* 编码器时钟分频*/
	  TIM_QEPInitStruct.QEP_Filter = 0;                        /* 输入信号滤波系数*/
	  TIM_QEPInitStruct.QEP_TH = 65535;                        /* 编码器计数周期*/
	  TIM_QEPInitStruct.QEP_ZEC = ENABLE;                      /*Z 信号清零极性选择：低电平/下降沿清零使能*/
	  TIM_QEPInitStruct.QEP_ZLC = DISABLE;                     /*Z 信号清零极性选择：高电平/下降沿清零使能*/
	  TIM_QEPInitStruct.QEP_ZNC = DISABLE;                     /*Z 信号电平清零 QEP 计数器使能 */
	  TIM_QEPInitStruct.QEP_ZPC = ENABLE;                      /*Z 信号边沿清零 QEP 计数器使能 */
	  TIM_QEPInitStruct.QEP_IRQEna = DISABLE;                  /*中断使能*/
    TIM_QEPInit(QEP0, &TIM_QEPInitStruct); 
    TIM_QEPCmd(QEP0, ENABLE);                                /* QEP0模块使能 */
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
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}




