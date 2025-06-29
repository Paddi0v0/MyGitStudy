#include "hardinit.h"




void SYS_VolSelModule(uint32_t Vol);
void SoftDelay(u32 cnt);

void Clock_Init(void)
{
	SYS_WR_PROTECT = 0x7a83;
	SYS_AFE_REG5 |= 0x8000;
	#if POWER_MODE
	SYS_VolSelModule(MCU_POWER_5v0);       /* MCU供电电压：1：5V，0;3.3V*/
	#else
	SYS_VolSelModule(MCU_POWER_3v3);       /* MCU供电电压：1：5V，0;3.3V*/
	#endif
	SoftDelay(100);                /* 等待PLL稳定*/
	SYS_WR_PROTECT = 0x7a83;       /* 解除系统寄存器写保护 */
	
	SYS_CLK_CFG |= 0x000001ff;		 /* select fast clock */
	SYS_CLK_DIV2  = 0x0000;
	SYS_CLK_FEN = 0xff;
}

void SystemInit(void)
{
    Clock_Init();
}

void InitCom(void)
{
	GPIO0_PIE = BIT15;				// RX-P0.15
	GPIO1_POE = BIT0;				  // TX-P1.0 
	
	GPIO0_FFEDC = 0x4000;
	GPIO1_F3210 = 0x0004;
	
	UART0_DIVH = 0x27;
	UART0_DIVL = 0x0F;
	UART0_IE = 0x02;

	UTIMER_UNT0_CFG = 0x0400;
	UTIMER_UNT0_TH = 0xFB80;		//48000
	UTIMER_CFG = 0x10;
	UTIMER_IE = 0x01;
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


/**
 *@brief @b 函数名称:   void SYS_VolSelModule(uint32_t Vol)
 *@brief @b 功能描述:   MCU供电电压稳定判断函数
 *@see被调用函数：      无
 *@param输入参数：      Vol：0 3.3 Voltage；1 5.0 Voltage
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无     
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_VolSelModule(MCU_POWER_5v0);//MCU供电系统为5V系统
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年10月19日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_VolSelModule(uint32_t Vol)
{
	if(Vol == MCU_POWER_5v0)  // 5.0 Voltage
	 {
		 SYS_WR_PROTECT = 0x7a83;       /* 解除系统寄存器写保护 */
		 SYS_AFE_REG6 &=~(BIT8|BIT9);  //main init set to 3.6v, this clause reset to 4.5v 
		 SoftDelay(100);              /* 延时100us*/
		 SYS_AFE_REG6 |= POWER_4V2 << 8;//配置为4.2V监控，可根据实际配置其它档位：3.6V/3.9V/4.2V/4.5V
		 SoftDelay(100);              /* 延时100us, 等待电源检测配置完毕*/
		 while(SYS_AFE_CMP & BIT13){};  //等待外部5VOK
		 SYS_AFE_REG6 &=~(BIT8|BIT9);  //reset to 4.5V
		 SoftDelay(100);             /* 延时100us*/
		 SYS_AFE_REG6 |= POWER_3V6<< 8; //配置为3.6V，防止电源和欠压比较的抖动
		 SoftDelay(100);             /* 延时100us*/
		 NVIC_ClearPendingIRQ(PWRDN_IRQn);
		 SYS_WR_PROTECT = 0x0;          /*关闭系统寄存器写操作*/
		}
}

/**
 *@brief @b 函数名称:   void SYS_VolSelModuleIRQ(void)
 *@brief @b 功能描述:   MCU供电电压稳定判断中断函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无     
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_VolSelModuleIRQ();
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年10月19日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_VolSelModuleIRQ(void)
{
		NVIC_DisableIRQ(PWRDN_IRQn);       /* 关闭电源检测中断 */ 
		NVIC_ClearPendingIRQ(PWRDN_IRQn);
		//turn off pwm
		MCPWM_PRT   = 0xDEAD;
		MCPWM_FAIL &= ~BIT6 ;
		MCPWM_TCLK &=~0x0000000C;
		MCPWM_PRT   = 0x0000;
		SYS_WR_PROTECT = 0x7A83;   /* 解除系统寄存器写保护 */
		SYS_SFT_RST = 0xff;        //所有外设复位 
		SYS_CLK_CFG &= ~BIT8;      //系统时钟选择RCH
		SYS_AFE_REG5 &= ~BIT15;    //关闭PLL
		SYS_SFT_RST = 0x0;         // 释放外设复位
		SYS_WR_PROTECT = 0x0;      /*关闭系统寄存器写操作*/
		NVIC_SystemReset();//软复位 

}

/**
 *@brief @b 函数名称:   void SYS_VolSelModuleEnableIRQ(uint32_t Vol)
 *@brief @b 功能描述:   MCU供电电压稳定判断中断使能函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无     
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_VolSelModuleIRQ(MCU_POWER_5v0);
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年10月19日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_VolSelModuleEnableIRQ(uint32_t Vol)
{
     if(Vol == MCU_POWER_5v0)
     {
       NVIC_SetPriority(PWRDN_IRQn, 0);  /*PWRDN_IRQn中断优先级设置为0*/
       NVIC_EnableIRQ(PWRDN_IRQn);       /* 打开电源检测中断 */
     }else{ 

       NVIC_DisableIRQ(PWRDN_IRQn);       /* 关闭电源检测中断 */ 
     }
}



