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
#include "project_mcu.h"
#include "hardware_config.h"


void M0_ADC_init(void);
void M1_ADC_init(void);
void UTimer_init(void);
void GPIO_init(void);
void UART_init(void);
void HALL_Perip_Init(void);

extern void registerEPWM0_DrvLevel(void);
extern void registerEPWM1_DrvLevel(void);

void EPWM0_MCPWM_init(void);
void EPWM1_MCPWM_init(void);

void PGA_Init(void);
void EPWM0_DAC_init(void);
void EPWM1_DAC_init(void);

extern	PSTR_DrvCfgPara getCfgParaPtr(u8 objID);
extern	u16 getPWMPrd(PSTR_DrvCfgPara pDrvCfgPara);
extern	u16 getDeadTime(PSTR_DrvCfgPara pDrvCfgPara);
extern	u8 getCtrlObjectID(u8 PWM_ID);

extern	void M0_1ShuntNormalModeCFG(void);
extern	void M0_2ShuntNormalModeCFG(void);
extern	void M0_3ShuntNormalModeCFG(void);

extern	void M1_1ShuntNormalModeCFG(void);
extern	void M1_2ShuntNormalModeCFG(void);
extern	void M1_3ShuntNormalModeCFG(void);

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
    __disable_irq();					/* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;			/*解除寄存器保护*/

    //[6]、[7]、[14]
    SYS_AFE_REG9 = 0xbf3f;				/* 使能外设模块,[14]、[6] [7]必须为0; 打开所有运放，打开所有比较器，打开所有ADC  */
    SYS_AFE_REGA = 0;					//ADD 添加不提

	SYS_PROTECT = 0x0;					/*关闭写保护*/

    FPU_ENABLE();						/* FPU Enable */

    IWDG_CFG = 0x3C00;					/*独立看门狗默认使能，此处禁用*/
    WWDG_CR  = 0x3C7F;					/*禁用窗口看门狗功能，上电默认禁用*/

    //UART_init();						/* 串口初始化UART*/

    M0_ADC_init();						/* ADC初始化 */
	M1_ADC_init(); 

	#if (EPWM0_USED == FUNCTION_ON)
		EPWM0_MCPWM_init();				/* PWM初始化 */
	#endif
	#if (EPWM1_USED == FUNCTION_ON)
		EPWM1_MCPWM_init();
	#endif

    UTimer_init();						/* 通用计数器初始化 */

    GPIO_init();						/* GPIO初始化 */

    HALL_Perip_Init();					/* Hall模块初始化 */

    EPWM0_DAC_init();					/* DAC 初始化 无*/
	EPWM1_DAC_init();					/* DAC 初始化 无*/

	PGA_Init();	
	
    //CMP_init();						/* 比较器初始化无*/

    //初始化系统Systick定时器
    //SysTick_Config(96000);				// 96000/192Mhz=0.5ms

    NVIC_SetPriority(UART0_IRQn, 2);		/* 设置UART0中断优先级为2 | 共0，1，2，3四级中断优先级，0为最高*/
    NVIC_SetPriority(ADC0_IRQn, 1);
    NVIC_SetPriority(ADC1_IRQn, 1);
    NVIC_SetPriority(ADC2_IRQn, 1);
    NVIC_SetPriority(HALL0_IRQn, 1);
    NVIC_SetPriority(HALL1_IRQn, 1);
    NVIC_SetPriority(MCPWM10_IRQn, 2);		//PWM1 时基0
    NVIC_SetPriority(MCPWM00_IRQn, 2);		//PWM0 时基0
    NVIC_SetPriority(CMP0_IRQn, 1);			/* 设置CMP_IRQn中断优先级为0 | 共0，1，2，3四级中断优先级，0为最高*/
    NVIC_SetPriority(TIMER0_IRQn, 2);

	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)    
	    NVIC_SetPriority(MCPWM00_IRQn, 1);
	    NVIC_EnableIRQ (MCPWM00_IRQn);      //PWM0_时基0	
	#else
 		NVIC_EnableIRQ(ADC0_IRQn);			/* enable the ADC0 interrupt */
	#endif

	#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		NVIC_SetPriority(MCPWM10_IRQn, 1);
		NVIC_EnableIRQ (MCPWM10_IRQn);		//PWM1_时基0
	#else
		NVIC_EnableIRQ(ADC2_IRQn);			/* enable the ADC0 interrupt */	
	#endif


    NVIC_EnableIRQ(TIMER0_IRQn);
    //NVIC_EnableIRQ(CMP_IRQn);				/* 打开比较器中断 */

	#if ((ROTOR_SENSOR_TYPE_M0 == ROTOR_HALL_SENSOR) || (ROTOR_SENSOR_TYPE_M0 == ROTOR_HALL2SENSORLESS))
    	NVIC_EnableIRQ(HALL0_IRQn);			/* enable the HALL interrupt */
    	NVIC_EnableIRQ(HALL1_IRQn);			/* enable the HALL interrupt */
	#endif

    SCB->SHCSR |= 0x70000;					/* 打开 MemManageFault BusFault UsageFault中断*/
}

void _fp_init(void)
{

}

/*******************************************************************************
 函数名称：    void SystemInit(void)
 功能描述：    硬件系统初始化，调用时钟初始化函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    MUN initial
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/14      V1.0           Howlet Li          创建
 *******************************************************************************/
void SystemInit (void)
{
    SYS_PROTECT = PSW_SYS_PROTECT;		/*解除保护*/
	
	SYS_SFT_RST = 0xffffffff;			/* 软复位 */
	__asm("NOP");
	__asm("NOP");
	__asm("NOP");
	__asm("NOP");
	SYS_SFT_RST = 0;					// 软复位释放
	

    SYS_CLK_CFG = 0x1FF;				/* switch to full speed PLL clock 192Mhz*/
    __asm("NOP");  /*延时等待稳定*/
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");	
	
	SoftDelay(200);
	
    SYS_CACHE_CFG = 0x1;				/* enable cache */
    WWDG_CR = 0x3C7F;					/* disable wwdg */
    SYS_MEM_CFG = 0x2 << 8;				/* use sram3 as cram */

	SYS_PROTECT = 0x0;					/*关闭写保护*/
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
    u32 reg;

	u16 OPA_modeM0	= 0;
	u16 OPA_modeM1	= 0;
	u8	ObjId		= 0;
	
	PSTR_DrvCfgPara	pParaPtr;

	#if (PLANTFORM_DRV_MODULE_NUM == 1)
	ObjId = getCtrlObjectID(DRV0_PWM_ID);
	pParaPtr	= getCfgParaPtr(ObjId);
	
		#if (DRV0_PWM_ID == PLANTFORM_EPWM0)
		OPA_modeM0  = pParaPtr->mS_GlobalCfg.m_bOPAValue;
		#else
		OPA_modeM1  = pParaPtr->mS_GlobalCfg.m_bOPAValue;
		#endif
		
	#elif (PLANTFORM_DRV_MODULE_NUM == 2)
	
	ObjId 		= getCtrlObjectID(DRV0_PWM_ID);
	pParaPtr	= getCfgParaPtr(ObjId);
	OPA_modeM0  = pParaPtr->mS_GlobalCfg.m_bOPAValue;

		#if (DRV0_PWM_ID == PLANTFORM_EPWM0)
		OPA_modeM0  = pParaPtr->mS_GlobalCfg.m_bOPAValue;
		#else
		OPA_modeM1  = pParaPtr->mS_GlobalCfg.m_bOPAValue;
		#endif

	ObjId 		= getCtrlObjectID(DRV1_PWM_ID);
	pParaPtr	= getCfgParaPtr(ObjId);
	OPA_modeM1	= pParaPtr->mS_GlobalCfg.m_bOPAValue;

		#if (DRV1_PWM_ID == PLANTFORM_EPWM1)
		OPA_modeM1  = pParaPtr->mS_GlobalCfg.m_bOPAValue;
		#else
		OPA_modeM0  = pParaPtr->mS_GlobalCfg.m_bOPAValue;
		#endif
	#endif

	
    SYS_WR_PROTECT = 0x7A83;    //解除系统寄存器写保护

    //配置不输出 SYS_AFE_REG2
    reg = SYS_AFE_REG2;
    reg &= ~(0xff | BIT13);
    SYS_AFE_REG2 = reg | (0) | (0 << 4) | (0 << 13);
    reg = SYS_AFE_REG3;
    reg &= ~3;
    //SYS_AFE_REG3 = reg | (this->IT_OPA);
    SYS_AFE_REG3 = reg | (0);

    //配置增益
    SYS_AFE_REG0 = (OPA_modeM1) | (OPA_modeM1 << 4) | (OPA_modeM1 << 8) | (OPA_modeM0 << 12);  //运放比例配置 011：160K：10K
    SYS_AFE_REG1 = (OPA_modeM0) | (OPA_modeM0 << 4);   /*OPA4 OPA5的运放比例  011：160K：10K*/

    SYS_WR_PROTECT = 0;         //添加上系统寄存器写保护
}

/*******************************************************************************
 函数名称：    void CMP_init(void)
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
    CMP_InitTypeDef cmp_config;
    CMP_StructInit(&cmp_config);

    cmp_config.FT = DISABLE;                  // 比较器快速比较使能
    cmp_config.HYS = CMP_HYS_20mV;            // 比较器回差选择
    cmp_config.IT_CMP = ENABLE;               // 比较速度选择 0:比较速度 150ns    1:比较速度 600ns
    cmp_config.CLK01_DIV = 100;               // 比较器01滤波系数，1-2048
    cmp_config.cmp0.SELP = AFE_CMP0_SELP_IP0; // 比较器 0 信号正端选择
    cmp_config.cmp0.SELN = AFE_CMP0_SELN_DAC; // 比较器 0 信号负端选择
    cmp_config.cmp0.EN = ENABLE;              // 比较器 0 使能
    cmp_config.cmp0.IE = ENABLE;              // 比较器 0 中断使能
    cmp_config.cmp0.RE = DISABLE;             // 比较器 0 DMA 请求
    cmp_config.cmp0.IN_EN = ENABLE;           // 比较器 0 信号输入使能 // CMP0配置


    cmp_config.FT = DISABLE;                   // 比较器快速比较使能
    cmp_config.HYS = CMP_HYS_20mV;             // 比较器回差选择
    cmp_config.IT_CMP = ENABLE;				   // 比较速度选择 0:比较速度 150ns    1:比较速度 600ns
    cmp_config.CLK01_DIV = 100;                // 比较器12滤波系数，1-2048
    cmp_config.cmp1.SELP = AFE_CMP1_SELP_IP0;  // 比较器 1 信号正端选择
    cmp_config.cmp1.SELN = AFE_CMP1_SELN_DAC;  // 比较器 1 信号负端选择
    cmp_config.cmp1.EN = ENABLE;               // 比较器 1 使能
    cmp_config.cmp1.IE = ENABLE;               // 比较器 1 中断使能
    cmp_config.cmp1.RE = DISABLE;              // 比较器 1 DMA 请求
    cmp_config.cmp1.IN_EN = ENABLE;            // 比较器 1 信号输入使能 // CMP1配置

    CMP_Init(&cmp_config);
    CMP_Enable();
}


/*******************************************************************************
 函数名称：    void DAC_Init_cfg(void)
 功能描述：    DAC初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/23      V1.0           Howlet Li          创建
 *******************************************************************************/
void EPWM0_DAC_init(void)
{
	#if (EPWM0_USED == FUNCTION_ON)
		float fDACCmp = 0;	
		PSTR_DrvCfgPara	pParaPtr;

		#if (PLANTFORM_DRV_MODULE_NUM == 1)
			pParaPtr	= getCfgParaPtr(0);
			fDACCmp		= ((double)pParaPtr->mS_FBCurSense.nHardOvCurVolt)/1000.0;
			
		#elif (PLANTFORM_DRV_MODULE_NUM == 2)
			u8  ObjId;
				
			ObjId = getCtrlObjectID(PLANTFORM_EPWM0);
			if(ObjId < PLANTFORM_DRV_MODULE_NUM)
			{
				pParaPtr	= getCfgParaPtr(ObjId);
				fDACCmp		= ((double)pParaPtr->mS_FBCurSense.nHardOvCurVolt)/1000.0;
			}
		#endif
		
	    AFE_DacSetRange(AFE_MODULE_DAC0,AFE_DAC_RANGE_1_2V);    /* 设置DAC0满量程为1.2V；00:3V| 01:1.2V */
		
		SYS->PROTECT = 0x7a83;
		AFE_DacSetVoltage( AFE_MODULE_DAC0,  fDACCmp);			/* 设置DAC输出电压值 */ 
		SYS->PROTECT = 0x0;
		
	    AFE_ModuleClockCmd(AFE_MODULE_DAC0,ENABLE);             // 打开DAC0    
		AFE_Dac0OutGpio3Pin4(DISABLE);                          // 将DAC0输出到P3.4
		
	#else
		AFE_ModuleClockCmd(AFE_MODULE_DAC0,DISABLE);             // 关闭DAC0
	#endif
}

void EPWM1_DAC_init(void)
{
	#if (EPWM1_USED == FUNCTION_ON)
		float fDACCmp = 0;
		PSTR_DrvCfgPara	pParaPtr;
		
		#if (PLANTFORM_DRV_MODULE_NUM == 1)
			pParaPtr	= getCfgParaPtr(0);
			fDACCmp		= ((double)pParaPtr->mS_FBCurSense.nHardOvCurVolt)/1000.0;
				
		#elif (PLANTFORM_DRV_MODULE_NUM == 2)
			u8  ObjId;
			
			ObjId = getCtrlObjectID(PLANTFORM_EPWM1);
			if(ObjId < PLANTFORM_DRV_MODULE_NUM)
			{
				pParaPtr	= getCfgParaPtr(ObjId);
				fDACCmp		= ((double)pParaPtr->mS_FBCurSense.nHardOvCurVolt)/1000.0;
			}
		#endif	

		AFE_DacSetRange(AFE_MODULE_DAC1,AFE_DAC_RANGE_1_2V);	/* 设置DAC1满量程为1.2V；00:3V| 01:1.2V */

		SYS->PROTECT = 0x7a83;	
		AFE_DacSetVoltage( AFE_MODULE_DAC1,  fDACCmp);			/* 设置DAC输出电压值 */ 	
		SYS->PROTECT = 0x0;

		AFE_ModuleClockCmd(AFE_MODULE_DAC1,ENABLE);				// 打开DAC1
	    AFE_Dac1OutGpio4Pin7(DISABLE);                          // 将DAC0输出到P4.7
	#else
		AFE_ModuleClockCmd(AFE_MODULE_DAC1,DISABLE);			// 关闭DAC1
	#endif
}

/*******************************************************************************
 函数名称：    void UART_init(void)
 功能描述：    UART1寄存器配置
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
    UART_InitStruct.BAUDRATE	= 38400;					/* 设置波特率BAUDRATE=38400 */
    UART_InitStruct.BYTE_LEN	= UART_WORDLENGTH_8b;		/* 发送数据长度8位 */
    UART_InitStruct.STOP_LEN	= UART_STOPBITS_1b;
    UART_InitStruct.BIT_ORDER	= UART_FIRSTSEND_LSB;		/* 先发送LSB */
    UART_InitStruct.CK_TYPE		= UART_Parity_NO;			/* 无奇偶校验 */
    UART_InitStruct.CK_EN		= DISABLE;					/*数据校验使能位*/
    UART_InitStruct.IE			= 0;
    UART_Init(UART0, &UART_InitStruct);						/*UART*/
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
void UART0_SENDDATA(UINT8 n)
{
	UART_SendData(UART0, n);
}

/*******************************************************************************
 函数名称：    void ADC_init(void)
 功能描述：    M0 ADC硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void M0_ADC_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure);

    ADC_InitStructure.Align = ADC_ALIGN_LEFT;				/* ADC转换结果采用左对齐格式 */

	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		ADC_InitStructure.S1	= 1;                        /* 第一段共采样4个通道 */
		ADC_InitStructure.S2	= 3;                        /* 第二段共采样2个通道 */
		ADC_InitStructure.TCNT	= 0;						/* 来一次触发事件执行一段转换动作 */  
		ADC_InitStructure.TRIG	= ADC_TRIG_MCPWM0_T0_EN | ADC_TRIG_MCPWM0_T1_EN;  ///* 设置MCPWM1_T0，MCPWM1_T1硬件触发事件  进入ADC0中断*/触发ADC采样
		ADC_InitStructure.NSMP	= ADC_NSMP_2; 				/* 设置ADC转换模式为二段式采样 */
		ADC_InitStructure.IE	= 0;						/* ADC第二段采样结束中断使能 */
		ADC_Init(ADC0, &ADC_InitStructure);      //ADC0采样使能

	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	    ADC_InitStructure.S1	= 4;                        /* 第一段共采样4个通道 */
	    ADC_InitStructure.S2	= 0;                        /* 第二段共采样0个通道 */
	    ADC_InitStructure.TCNT	= 0;						/* 来一次触发事件执行一段转换动作 */

	    /* 设置MCPWM0_T0，MCPWM1_T0硬件触发事件  进入ADC0中断*/
	    ADC_InitStructure.TRIG	= ADC_TRIG_MCPWM0_T0_EN;	// 触发ADC采样
	    ADC_InitStructure.NSMP	= ADC_NSMP_1;				/* 设置ADC转换模式为一段式采样 */
	    ADC_InitStructure.IE	= ADC_IE_SF1;				/* ADC第一段采样结束中断使能 */

		ADC_Init(ADC1, &ADC_InitStructure);					// ADC1采样使能 触发ADC1采样
	    ADC_Init(ADC0, &ADC_InitStructure);					// ADC0采样使能 触发ADC0采样
	    //ADC_Init(ADC1, &ADC_InitStructure);					// ADC1采样使能 触发ADC1采样
	    
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
	    ADC_InitStructure.S1	= 4;                        /* 第一段共采样4个通道 */
	    ADC_InitStructure.S2	= 0;                        /* 第二段共采样2个通道 */
	    ADC_InitStructure.TCNT	= 0;						/* 来一次触发事件执行一段转换动作 */

	    /* 设置MCPWM0_T0，MCPWM1_T0硬件触发事件  进入ADC0中断*/
	    ADC_InitStructure.TRIG	= ADC_TRIG_MCPWM0_T0_EN;	// 触发ADC采样
	    ADC_InitStructure.NSMP	= ADC_NSMP_1;				/* 设置ADC转换模式为一段式采样 */
	    ADC_InitStructure.IE	= ADC_IE_SF1;				/* ADC第一段采样结束中断使能 */
		
		ADC_Init(ADC0, &ADC_InitStructure);					// ADC0采样使能 触发ADC0采样
	    ADC_Init(ADC1, &ADC_InitStructure);					// ADC1采样使能 触发ADC1采样
	#endif

    //clear IF
	ADC_ClearIRQFlag(ADC0, 0x0f);
    ADC0_STATE_RESET();

	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		M0_1ShuntNormalModeCFG();
	
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
		ADC_ClearIRQFlag(ADC1, 0x0f);
		ADC1_STATE_RESET();	
		M0_2ShuntNormalModeCFG();

	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
		ADC_ClearIRQFlag(ADC1, 0x0f);
		ADC1_STATE_RESET();		
		M0_3Shunt_NormalModeCFG();
		#error "M0 dont't support 3 shunt in 453 Demo Board!"
		#error "Modify according to used Board!"
	#endif
}

/*******************************************************************************
 函数名称：    void soft_Trg_ADC_DRV0(void)
 功能描述：    M0 ADC硬件复位
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：		用于单电机关中断IPD功能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void soft_Trg_ADC_DRV0(void)
{
	ADC0_STATE_RESET();

	ADC0_SWT = 0x00005AA5;	 //软件触发 ADC0_SWT 

	while((ADC0_IF & BIT0) == 0)
	{
		;
	}
	ADC0_IF |= BIT1 | BIT0;

	
	#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT))
	
	ADC1_STATE_RESET();
	ADC1_SWT = 0x00005AA5;	 //软件触发 ADC0_SWT 

	while((ADC1_IF & BIT0) == 0)
	{
		;
	}
	ADC1_IF |= BIT1 | BIT0;
	#endif
}

/*******************************************************************************
 函数名称：    void M1_ADC_init(void)
 功能描述：    M1 ADC硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void M1_ADC_init(void)
{

    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.Align = ADC_ALIGN_LEFT;          			// ADC转换结果采用左对齐格式 

	#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		ADC_InitStructure.S1	= 1;								// 第一段共采样4个通道 
		ADC_InitStructure.S2	= 3;								// 第二段共采样2个通道 
		ADC_InitStructure.TCNT	= 0;								// 来一次触发事件执行一段转换动作 

		ADC_InitStructure.TRIG	= ADC_TRIG_MCPWM1_T0_EN | ADC_TRIG_MCPWM1_T1_EN;  ////设置MCPWM1_T0，MCPWM1_T1硬件触发事件  进入ADC0中断触发ADC采样
		ADC_InitStructure.NSMP	= ADC_NSMP_2;						// 设置ADC转换模式为二段式采样 
		ADC_InitStructure.IE	= 0;    							// ADC_SF2_IE;               ADC第二段采样结束中断使能 
		ADC_Init(ADC2, &ADC_InitStructure);							// ADC1采样使能
	#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	    ADC_InitStructure.S1	= 4;                        		/* 第一段共采样4个通道 */
	    ADC_InitStructure.S2	= 0;                        		/* 第二段共采样0个通道 */
	    ADC_InitStructure.TCNT	= 0;								/* 来一次触发事件执行一段转换动作 */

	    /* 设置MCPWM0_T0，MCPWM1_T0硬件触发事件  进入ADC2中断*/
	    ADC_InitStructure.TRIG	= ADC_TRIG_MCPWM1_T0_EN;			// 触发ADC采样
	    ADC_InitStructure.NSMP	= ADC_NSMP_1;           			/* 设置ADC转换模式为一段式采样 */
	    ADC_InitStructure.IE	= ADC_IE_SF1;                       /* ADC第一段采样结束中断使能 */
	    ADC_Init(ADC2, &ADC_InitStructure);      					// ADC2采样使能 触发ADC2采样
	#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
	    ADC_InitStructure.S1	= 4;                        		/* 第一段共采样4个通道 */
	    ADC_InitStructure.S2	= 0;                        		/* 第二段共采样2个通道 */
	    ADC_InitStructure.TCNT	= 0;								/* 来一次触发事件执行一段转换动作 */

	    /* 设置MCPWM0_T0，MCPWM1_T0硬件触发事件  进入ADC2中断*/
	    ADC_InitStructure.TRIG	= ADC_TRIG_MCPWM1_T0_EN;			// 触发ADC采样
	    ADC_InitStructure.NSMP	= ADC_NSMP_1;          				/* 设置ADC转换模式为一段式采样 */
	    ADC_InitStructure.IE	= ADC_IE_SF1;						/* ADC第一段采样结束中断使能 */
		ADC_Init(ADC2, &ADC_InitStructure);
	#endif

	ADC_ClearIRQFlag(ADC2, 0x0f);								//clear IF

    ADC2_STATE_RESET();

	#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
		M1_1ShuntNormalModeCFG();
	
	#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
		M1_2ShuntNormalModeCFG();

	#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
		M1_3ShuntNormalModeCFG();
		#error "M1 dont't support 3 shunt in 453 Demo Board!"	// 根据实际硬件修改电流采样通道
		#error "Modify according to used Board!"
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

    HALL_StructInit(&HALL_InitStruct);
    HALL_InitStruct.FilterLen			= 512;				/* Hall信号数字滤波长度 512个时钟周期 */
    HALL_InitStruct.ClockDivision		= HALL_CLK_DIV1;	/* 设置Hall模块时钟分频系数 */
    HALL_InitStruct.Filter75_Ena		= DISABLE;			/* Hall信号滤波方式，7判5模式或者全1有效模式 */
    HALL_InitStruct.HALL_Ena			= ENABLE;			/* 模块使能 */
    HALL_InitStruct.Capture_IRQ_Ena		= DISABLE;			/* 捕捉中断使能 */
    HALL_InitStruct.OverFlow_IRQ_Ena	= DISABLE;			/* 超时中断使能 */
    HALL_InitStruct.CountTH				= 0;				/* Hall模块计数模值，计数超过模值会产生超时中断 */

    HALL_Init(HALL0, &HALL_InitStruct);
    HALL_Init(HALL1, &HALL_InitStruct);
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


//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_15;
//    GPIO_Init(GPIO0, &GPIO_InitStruct);
    //GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF3_MCPWM); /* MCPWM1_CH3N */


//# SDA
//    //set_property PACKAGE_PIN K14 [get_ports {pad_p1[0]}]
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//    GPIO_Init(GPIO1, &GPIO_InitStruct);
//    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF3_MCPWM); /* MCPWM1_CH3P */


#if 1
    /* MCPWM P1.1~P1.6 */
	#if 1
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_1, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_2, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_3, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, GPIO_AF_MCPWM);
	#endif

		
    /* MCPWM P2.3~P2.8 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_3, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_6, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_7, GPIO_AF_MCPWM);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, GPIO_AF_MCPWM);		
#endif
		
#if 0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIO2, &GPIO_InitStruct);		

    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_13, GPIO_AF_HALL);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_14, GPIO_AF_HALL);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_15, GPIO_AF_HALL);


	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIO4, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO4, GPIO_PinSource_10, GPIO_AF_HALL);
    GPIO_PinAFConfig(GPIO4, GPIO_PinSource_11, GPIO_AF_HALL);
    GPIO_PinAFConfig(GPIO4, GPIO_PinSource_12, GPIO_AF_HALL);
#endif

    /**************************************************************************/
    //LED1  P4.5
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIO4, &GPIO_InitStruct);
    GPIO_SetBits(GPIO4, GPIO_Pin_5) ;
		
    //LED02 LED03  P2.11 T58,P2.12 T56
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIO2, &GPIO_InitStruct);


    //Test GPIO output T1 T3  P0.1 P0.2
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2 ;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    /*****************************************************************************************/
#if 0
    //Test Utimer0 ch1   TP46 P3.3   MOTOR0采样运行时候，需要关闭此处，否则会引起采样毛刺。
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIO3, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_3, GPIO_AF_TIMER0);      //timr0 ch1 输出电平
		
    //Test SYS CLK   TP2   P4.14  CLK_OUT
		
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_14  ;
	GPIO_Init(GPIO4, &GPIO_InitStruct);	
    GPIO_PinAFConfig(GPIO4, GPIO_PinSource_14, GPIO_AF_CLK);    //LKS453/P4.14 输出clk电平
    //CLK HSI OUTPUT  观察12.48Mhz
    CLKO_SEL |= 0x02;
#endif

#if 0
    /* P0.15-RX0, P1.0-TX0  UART0 */
    GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 ;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
		
    /* P0.15-RX0, P1.0-TX0  UART0 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_7;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
		
    /* P0.15-RX0, P1.0-TX0  UART0 */
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, GPIO_AF_UART);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, GPIO_AF_UART);
#endif
		
#if 0
    /* P5.1 MCPWM0_CH3P */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIO5, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO5, GPIO_PinSource_1, GPIO_AF_MCPWM);
		
		
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIO3, &GPIO_InitStruct);
		
    GPIO3_PDO |= BIT11;
    GPIO3_PDO &= ~(BIT13|BIT14|BIT15);
		
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;
    GPIO_Init(GPIO4, &GPIO_InitStruct);
    GPIO4_PDO &= ~BIT0;
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
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTimer_init(void)
{
    UTIMER_InitTypeDef TIM_InitStruct;

    UTIMER_StructInit(&TIM_InitStruct);

    TIM_InitStruct.EN				= ENABLE;    // Timer 模块整体使能，高有效
    TIM_InitStruct.CAP1_CLR_EN		= DISABLE;   // 当发生CAP1捕获事件时，清零Timer计数器，高有效
    TIM_InitStruct.CAP0_CLR_EN		= DISABLE;   // 当发生CAP0捕获事件时，清零Timer计数器，高有效
    TIM_InitStruct.ETON				= 0;                 // Timer 计数器计数使能配置 0:自动运行 1:等待外部事件触发计数
    TIM_InitStruct.CLK_DIV			= UTIMER_Clk_Div2;   // Timer 计数器分频设置
    TIM_InitStruct.CLK_SRC			= ENABLE;    // Timer 时钟源

    TIM_InitStruct.SRC1				= ENABLE;    // Timer 捕获模式通道 1 信号来源。默认为 3’h0
    TIM_InitStruct.CH1_POL			= ENABLE;    // Timer通道1在比较模式下的输出极性控制，当计数器计数值回零时的输出值
    TIM_InitStruct.CH1_MODE			= ENABLE;    // Timer通道1的工作模式选择，默认值为0
    TIM_InitStruct.CH1_FE_CAP_EN	= ENABLE;    // Timer通道1下降沿捕获事件使能
    TIM_InitStruct.CH1_RE_CAP_EN	= ENABLE;    // Timer通道1上升沿捕获事件使能

    TIM_InitStruct.SRC0				= ENABLE;    // Timer 捕获模式通道 1 信号来源。默认为 3’h0
    TIM_InitStruct.CH0_POL			= ENABLE;    // Timer通道1在比较模式下的输出极性控制，当计数器计数值回零时的输出值
    TIM_InitStruct.CH0_MODE			= ENABLE;    // Timer通道1的工作模式选择，默认值为0
    TIM_InitStruct.CH0_FE_CAP_EN	= ENABLE;    // Timer通道1下降沿捕获事件使能
    TIM_InitStruct.CH0_RE_CAP_EN	= ENABLE;    // Timer通道1上升沿捕获事件使能

    TIM_InitStruct.TH				= 48000;    // Timer 计数器计数门限。
    TIM_InitStruct.CMP0				= 24000;    // Timer 通道0工作在比较模式时，当计数器计数值等于CMP0时，发生比较事件。
    TIM_InitStruct.CMP1				= 24000;    // Timer 通道1工作在比较模式时，当计数器计数值等于CMP1时，发生比较事件。
    TIM_InitStruct.EVT_SRC			= ENABLE;    // Timer外部事件选择寄存器
    TIM_InitStruct.FLT				= ENABLE;    // 通道0/1信号滤波宽度选择。取值范围0~255
    TIM_InitStruct.IE				= UTIMER_IE_ZERO;    // 中断配置
    TIM_InitStruct.RE				= ENABLE;    // DMA请求
    UTIMER_Init(UTIMER0, &TIM_InitStruct);
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
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if (EPWM0_USED == FUNCTION_ON)
void EPWM0_MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

	u16 prd;
	u16 deadTime;
	u8  clockDiv;	
	PSTR_DrvCfgPara	pParaPtr;

	#if (PLANTFORM_DRV_MODULE_NUM == 1)
	pParaPtr	= getCfgParaPtr(0);
	prd 		= getPWMPrd(pParaPtr);
	deadTime	= getDeadTime(pParaPtr);
	clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;
		
	#elif (PLANTFORM_DRV_MODULE_NUM == 2)
	u8  ObjId;
		
	ObjId = getCtrlObjectID(PLANTFORM_EPWM0);
	if(ObjId < PLANTFORM_DRV_MODULE_NUM)
	{
		pParaPtr	= getCfgParaPtr(ObjId);
		prd 		= getPWMPrd(pParaPtr);
		deadTime	= getDeadTime(pParaPtr);
		clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;
	}
	#endif

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = clockDiv;							/* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;							/* 模块时钟开启 */
    MCPWM_InitStructure.MCPWM_Cnt0_EN = ENABLE;						/* 时基0主计数器开始计数使能开关 */
    MCPWM_InitStructure.MCPWM_Cnt1_EN = ENABLE;						/* 时基1主计数器开始计数使能开关 */

    MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM_CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM_CENTRAL_PWM_MODE;

    MCPWM_InitStructure.MCPWM_WorkModeCH3 = MCPWM_CENTRAL_PWM_MODE;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12;						/* 急停事件(来自IO口信号)数字滤波器时间设置 */
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;						/* 急停事件(来自比较器信号)数字滤波器时间设置 */

    MCPWM_InitStructure.TimeBase0_PERIOD = prd;						/* 时期0周期设置 */
    MCPWM_InitStructure.TimeBase1_PERIOD = prd;						/* 时期1周期设置 */

    MCPWM_InitStructure.TriggerPoint0 = (s16)(100 - prd);			/* MCPWM_TMR0 ADC触发事件T0 设置 */
    MCPWM_InitStructure.TriggerPoint1 = (s16)(800 - prd);			/* MCPWM_TMR1 ADC触发事件T1 设置 */
    MCPWM_InitStructure.TriggerPoint2 = (s16)(prd - 200);			/* MCPWM0 TMR2 = -PWM_PERIOD或者PWM_PERIOD 利用MCPWM1 TR2触发MCPWM0的时钟计数, 才能保证时基正交 */
    //0时候 相邻很近; PWM_PERIOD时候 前后差别半个周期

    MCPWM_InitStructure.DeadTimeCH0N = deadTime;
    MCPWM_InitStructure.DeadTimeCH0P = deadTime;
    MCPWM_InitStructure.DeadTimeCH1N = deadTime;
    MCPWM_InitStructure.DeadTimeCH1P = deadTime;
    MCPWM_InitStructure.DeadTimeCH2N = deadTime;
    MCPWM_InitStructure.DeadTimeCH2P = deadTime;					/* 死区时间设置 */

	#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)
	MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;					/* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;				/* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 */

	/* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
	MCPWM_InitStructure.CH0P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM_HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM_LOW_LEVEL;		/* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM_HIGH_LEVEL;		/* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM_HIGH_LEVEL;

	#elif (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)
	
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;				/* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;				/* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 */

	/* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
                                                     
    MCPWM_InitStructure.CH0P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM_LOW_LEVEL;    /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM_LOW_LEVEL;    /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM_LOW_LEVEL;
	#endif
   

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE;           /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                                 还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
    /* 自动更新使能寄存器 MCPWM_TH00 自动加载使能 MCPWM_TMR0 自动加载使能 MCPWM_0TH 自动加载使能 MCPWM_0CNT 自动加载使能*/
    MCPWM_InitStructure.AUEN = MCPWM_TH00_AUEN | MCPWM_TH01_AUEN | MCPWM_TH10_AUEN | MCPWM_TH11_AUEN |
                               MCPWM_TH20_AUEN | MCPWM_TH21_AUEN | MCPWM_TMR0_AUEN | MCPWM_TMR1_AUEN |
                               MCPWM_TMR2_AUEN | MCPWM_TMR3_AUEN | MCPWM_TH0_AUEN | MCPWM_TH30_AUEN | MCPWM_TH31_AUEN ;
    //通道0/1/2 固定使用时基 0，通道 3 固定使用时基 1。
    MCPWM_InitStructure.MCPWM_Base0T0_UpdateEN = ENABLE;				/* MCPWM 时基0 T0事件更新使能 */
    MCPWM_InitStructure.MCPWM_Base0T1_UpdateEN = DISABLE;				/* MCPWM 时基0 T1事件更新 禁止*/
		
	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    MCPWM_InitStructure.T1_Update_INT_EN_BASE0 = ENABLE;
    #else
	MCPWM_InitStructure.T0_Update_INT_EN_BASE0 = DISABLE;				/* T0更新事件 中断使能或关闭 */
    #endif

    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;							/* FAIL0事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL1_INT_EN = DISABLE;							/* FAIL1事件 中断使能或关闭 */
		
		
	MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;							/* FAIL0事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL0_INPUT_EN = DISABLE;						/* FAIL0通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL0_Signal_Sel = MCPWM_FAIL_SEL_CMP;			/* FAIL0事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL0_Polarity = MCPWM_HIGH_LEVEL_VALID;		/* FAIL0事件极性选择，高有效或低有效 */

   	MCPWM_InitStructure.FAIL2_INT_EN = DISABLE;							/* FAIL2事件 中断使能或关闭 */
	MCPWM_InitStructure.FAIL2_INPUT_EN = DISABLE;						/* FAIL2通道急停功能打开或关闭 */
	MCPWM_InitStructure.FAIL2_Signal_Sel = MCPWM_FAIL_SEL_CMP;			/* FAIL2事件信号选择，比较器或IO口 */
	MCPWM_InitStructure.FAIL2_Polarity = MCPWM_HIGH_LEVEL_VALID;		/* FAIL2事件极性选择，高有效或低有效 */

	MCPWM_Init(MCPWM0, &MCPWM_InitStructure);							/* MCPWM1模块初始化 */
	registerEPWM0_DrvLevel();
}
#endif

#if (EPWM1_USED == FUNCTION_ON)
void EPWM1_MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

	u16 prd;
	u16 deadTime;
	u8  clockDiv;
	
	PSTR_DrvCfgPara	pParaPtr;

	#if (PLANTFORM_DRV_MODULE_NUM == 1)
	pParaPtr	= getCfgParaPtr(0);
	prd 		= getPWMPrd(pParaPtr);
	deadTime	= getDeadTime(pParaPtr);
	clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;
		
	#elif (PLANTFORM_DRV_MODULE_NUM == 2)
	u8  ObjId;
		
	ObjId = getCtrlObjectID(PLANTFORM_EPWM1);
	if(ObjId < PLANTFORM_DRV_MODULE_NUM)
	{
		pParaPtr	= getCfgParaPtr(ObjId);
		prd 		= getPWMPrd(pParaPtr);
		deadTime	= getDeadTime(pParaPtr);
		clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;
	}
	#endif


    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = clockDiv;								/* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;								/* 模块时钟开启 */
    MCPWM_InitStructure.MCPWM_Cnt0_EN = ENABLE;							/* 时基0主计数器开始计数使能开关 */
    MCPWM_InitStructure.MCPWM_Cnt1_EN = ENABLE;							/* 时基1主计数器开始计数使能开关 */

    MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM_CENTRAL_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM_CENTRAL_PWM_MODE;		/* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM_CENTRAL_PWM_MODE;

    MCPWM_InitStructure.MCPWM_WorkModeCH3 = MCPWM_CENTRAL_PWM_MODE;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12;							/* 急停事件(来自IO口信号)数字滤波器时间设置 */
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;							/* 急停事件(来自比较器信号)数字滤波器时间设置 */

    MCPWM_InitStructure.TimeBase0_PERIOD = prd;							/* 时期0周期设置 */
    MCPWM_InitStructure.TimeBase1_PERIOD = prd;							/* 时期1周期设置 */

    MCPWM_InitStructure.TriggerPoint0 = (s16)(100 - prd);				/* MCPWM_TMR0 ADC触发事件T0 设置 */
    MCPWM_InitStructure.TriggerPoint1 = (s16)(800 - prd);				/* MCPWM_TMR1 ADC触发事件T1 设置 */
    MCPWM_InitStructure.TriggerPoint2 = (s16)(prd - 200);				/* MCPWM0 TMR2 = -PWM_PERIOD或者PWM_PERIOD 利用MCPWM1 TR2触发MCPWM0的时钟计数, 才能保证时基正交 */
    //0时候 相邻很近; PWM_PERIOD时候 前后差别半个周期

    MCPWM_InitStructure.DeadTimeCH0N = deadTime;
    MCPWM_InitStructure.DeadTimeCH0P = deadTime;
    MCPWM_InitStructure.DeadTimeCH1N = deadTime;
    MCPWM_InitStructure.DeadTimeCH1P = deadTime;
    MCPWM_InitStructure.DeadTimeCH2N = deadTime;
    MCPWM_InitStructure.DeadTimeCH2P = deadTime;					/* 死区时间设置 */

	#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)
	MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;					/* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;				/* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

																	//ENABLE ---- 不交换
    MCPWM_InitStructure.Switch_CH0N_CH0P = ENABLE;					/* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = ENABLE;					/* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = ENABLE;					/* 通道交换选择设置 */

	/* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
	MCPWM_InitStructure.CH0P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM_HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM_LOW_LEVEL;		/* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM_HIGH_LEVEL;		/* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM_HIGH_LEVEL;

	#elif (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)
	
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;				/* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;				/* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = MCPWM_SWITCH_DISABLE;	/* 通道交换选择设置 */

	/* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
                                                     
    MCPWM_InitStructure.CH0P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM_LOW_LEVEL;			/* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM_LOW_LEVEL;			/* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM_LOW_LEVEL;
	#endif   

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE;						/* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                             			//还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
    /* 自动更新使能寄存器 MCPWM_TH00 自动加载使能 MCPWM_TMR0 自动加载使能 MCPWM_0TH 自动加载使能 MCPWM_0CNT 自动加载使能*/
    MCPWM_InitStructure.AUEN = MCPWM_TH00_AUEN | MCPWM_TH01_AUEN | MCPWM_TH10_AUEN | MCPWM_TH11_AUEN |
                               MCPWM_TH20_AUEN | MCPWM_TH21_AUEN | MCPWM_TMR0_AUEN | MCPWM_TMR1_AUEN |
                               MCPWM_TMR2_AUEN | MCPWM_TMR3_AUEN | MCPWM_TH0_AUEN | MCPWM_TH30_AUEN | MCPWM_TH31_AUEN ;
    //通道0/1/2 固定使用时基 0，通道 3 固定使用时基 1。
    MCPWM_InitStructure.MCPWM_Base0T0_UpdateEN = ENABLE;				/* MCPWM 时基0 T0事件更新使能 */
    MCPWM_InitStructure.MCPWM_Base0T1_UpdateEN = DISABLE;				/* MCPWM 时基0 T1事件更新 禁止*/
		
	#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    MCPWM_InitStructure.T1_Update_INT_EN_BASE0 = ENABLE;
    #else
	MCPWM_InitStructure.T0_Update_INT_EN_BASE0 = DISABLE;	
    #endif

    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;							/* FAIL0事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL1_INT_EN = DISABLE;							/* FAIL1事件 中断使能或关闭 */

	MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;							/* FAIL0事件 中断使能或关闭 */
	MCPWM_InitStructure.FAIL0_INPUT_EN = DISABLE;						/* FAIL0通道急停功能打开或关闭 */
	MCPWM_InitStructure.FAIL0_Signal_Sel = MCPWM_FAIL_SEL_CMP;			/* FAIL0事件信号选择，比较器或IO口 */
	MCPWM_InitStructure.FAIL0_Polarity = MCPWM_HIGH_LEVEL_VALID;		/* FAIL0事件极性选择，高有效或低有效 */

	MCPWM_InitStructure.FAIL2_INT_EN = DISABLE;							/* FAIL2事件 中断使能或关闭 */
	MCPWM_InitStructure.FAIL2_INPUT_EN = DISABLE;						/* FAIL2通道急停功能打开或关闭 */
	MCPWM_InitStructure.FAIL2_Signal_Sel = MCPWM_FAIL_SEL_CMP;			/* FAIL2事件信号选择，比较器或IO口 */
	MCPWM_InitStructure.FAIL2_Polarity = MCPWM_HIGH_LEVEL_VALID;		/* FAIL2事件极性选择，高有效或低有效 */
	MCPWM_Init(MCPWM1, &MCPWM_InitStructure);							/* MCPWM1模块初始化 */
	registerEPWM1_DrvLevel();
}
#endif

/*******************************************************************************
 函数名称：    void DebugPWM_OutputFunction(void)
 功能描述：    PWM输出功能调试
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
	MCPWM_OutputMode(MCPWM0,MCPWM_OUT_CHN_012,DISABLE);
	MCPWM_OutputMode(MCPWM1,MCPWM_OUT_CHN_012,DISABLE);
	

    MCPWM0_TH00 = (-(PWM_PERIOD_M0  >> 2));
    MCPWM0_TH01 = (PWM_PERIOD_M0    >> 2);
    MCPWM0_TH10 = (-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH11 = (PWM_PERIOD_M0  >> 2);
    MCPWM0_TH20 = (-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH21 = (PWM_PERIOD_M0 >> 2);

    MCPWM1_TH00 = (-(PWM_PERIOD_M1  >> 1));
    MCPWM1_TH01 = (PWM_PERIOD_M1 >> 1);
    MCPWM1_TH10 = (-(PWM_PERIOD_M1  >> 1));
    MCPWM1_TH11 = (PWM_PERIOD_M1  >> 1);
    MCPWM1_TH20 = (-(PWM_PERIOD_M1 >> 1));
    MCPWM1_TH21 = (PWM_PERIOD_M1 >> 1);


	MCPWM_OutputMode(MCPWM0,MCPWM_OUT_CHN_012,ENABLE);
	MCPWM_OutputMode(MCPWM1,MCPWM_OUT_CHN_012,ENABLE);

    while(1)
    {
    }
}


