#include "global_variable.h"
#include "hardware_config.h"
void Hardware_init(void);
void SystemInit(void);
void PGA_init(void);
void DAC_init(void);
void ADC_init(void);
void ADC_NormalModeCFG(void);
void GPIO_init(void);
void MCPWM_init(void);
void MCPWM0_RegUpdate(stru_VoltPhaseUVW VoltPhaseUVW);
void SoftDelay(u32 cnt);

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    初始化外设
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void Hardware_init(void)
{
	DSP_Init();                       	/* DSP模块初始化*/
	ADC_init();    						/* ADC初始化 */
	MCPWM_init();   					/* PWM初始化 */
    GPIO_init();    					/* GPIO初始化 */
    PGA_init();                       	/* PGA 初始化 */
    
	SoftDelay(100);                   	/* 延时等待硬件初始化稳定 */
    
    NVIC_SetPriority(ADC0_IRQn, 1);
    NVIC_EnableIRQ(ADC0_IRQn);
    NVIC_SetPriority(PendSV_IRQn,3);
    NVIC_EnableIRQ(PendSV_IRQn);
}

/*******************************************************************************
 函数名称：    void SystemInit(void)
 功能描述：    初始化时钟，上电后在MAIN函数之前运行
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void SystemInit(void)
{
    SYS_WR_PROTECT = 0x7a83;    // 解除系统寄存器写保护
    SYS_AFE_REG5 = BIT15;       // BIT15:PLLPDN 开PLL
    SoftDelay(100);             // 延时100us, 等待PLL稳定 21.4.17
    SYS_CLK_CFG = 0x000001ff;   // 芯片时钟96Mhz
    FLASH_CFG = BIT19;          // 开启预取加速
}
/*******************************************************************************
 函数名称：    void PGA_init(void)
 功能描述：    初始化运放
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void PGA_init(void)
{
	SYS_AFE_REG5 |= 0x20ff;
    SYS_AFE_REG0 = PGA_GAIN_20 | PGA_GAIN_20<<2;
}

/*******************************************************************************
 函数名称：    void ADC_init(void)
 功能描述：    初始化ADC
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void ADC_init(void) 
{
    ADC_InitTypeDef ADC_InitStructure;

    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;
    ADC_InitStructure.Align = ADC_LEFT_ALIGN;
    ADC_InitStructure.FirSeg_Ch = 4;
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
 功能描述：    初始化ADC采样通道
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void ADC_NormalModeCFG(void)
{
    ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | ADC0_CURRETN_B_CHANNEL<<8;
    ADC0_CHN1 = ADC0_BUS_VOL_MSK       | ADC0_TEMP_MSK<<8;
}

/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    初始化GPIO
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

    /* MCPWM P1.4~P1.9 */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);
    /* start  */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
}

/*******************************************************************************
 函数名称：    void MCPWM_init(void)
 功能描述：    初始化MCPWM
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = 0;
    MCPWM_InitStructure.MCLK_EN = ENABLE;
    MCPWM_InitStructure.MCPWM_Cnt_EN = ENABLE; 					
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE; 	

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12;
    MCPWM_InitStructure.CMP_BKIN_Filter = 12; 					

    MCPWM_InitStructure.MCPWM_PERIOD = PWM_PERIOD;
    MCPWM_InitStructure.TriggerPoint0 = (u16)(100 - PWM_PERIOD);
    MCPWM_InitStructure.TriggerPoint1 = (u16)(PWM_PERIOD - 1);
    MCPWM_InitStructure.DeadTimeCH0N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH0P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH1P = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2N = DEADTIME;
    MCPWM_InitStructure.DeadTimeCH2P = DEADTIME; 		

    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE; 	

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; 	
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; 	
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; 	

    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1N_default_output = HIGH_LEVEL; 
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = HIGH_LEVEL;

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE;

    MCPWM_InitStructure.MCPWM_T0_UpdateEN = ENABLE;
    MCPWM_InitStructure.MCPWM_T1_UpdateEN = DISABLE;

    MCPWM_InitStructure.T0_Update_INT_EN = DISABLE;

    MCPWM_Init(&MCPWM_InitStructure);
}

/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(stru_VoltPhaseUVW VoltPhaseUVW)
 功能描述：    更新PWM占空比
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void MCPWM0_RegUpdate(stru_VoltPhaseUVW VoltPhaseUVW)
{
	MCPWM_TH00 = -VoltPhaseUVW.nPhaseU;
	MCPWM_TH01 = VoltPhaseUVW.nPhaseU;

	MCPWM_TH10 = -VoltPhaseUVW.nPhaseV;
	MCPWM_TH11 = VoltPhaseUVW.nPhaseV;

	MCPWM_TH20 = -VoltPhaseUVW.nPhaseW;
	MCPWM_TH21 = VoltPhaseUVW.nPhaseW;
}

/*******************************************************************************
 函数名称：    void SoftDelay(u32 cnt)
 功能描述：    软件延时
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}
