/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_mcpwm.c\n
 * 文件标识： 无 \n
 * 内容摘要： MCPWM外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2019年05月21日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */
#include "lks32mc08x_MCPWM.h"
#include "lks32mc08x.h"
#include "lks32mc08x_sys.h"
#include "string.h"

/**
 *@brief @b 函数名称:   void PWMOutputs(FuncState t_state)
 *@brief @b 功能描述:   MCPWM波形输出使能与失能函数
 *@see被引用内容：      无
 *@param输入参数：      FuncState t_state ENABLE：使能 ， DISABLE:使能
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   PWMOutputs(ENABLE) //使能MCPWM输出
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2019年05月21日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */
void PWMOutputs(FuncState t_state)
{
    MCPWM_PRT       = 0x0000DEAD;

    if(t_state == ENABLE)
    {
        MCPWM_FAIL |= MCPWM_MOE_ENABLE_MASK;
    }
    else
    {
        MCPWM_FAIL &= MCPWM_MOE_DISABLE_MASK;
    }
    MCPWM_PRT       = 0x0000CAFE;
}


/**
 *@brief @b 函数名称:   void MCPWM_StructInit(MCPWM_InitTypeDef* MCPWM_InitStruct)
 *@brief @b 功能描述:   MCPWM结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       MCPWM_InitTypeDef *MCPWM_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
            MCPWM_InitTypeDef MCPWM_InitStructure;
            MCPWM_StructInit(&MCPWM_InitStructure);//初始化MCPWM相关结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2019年05月21日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */
void MCPWM_StructInit(MCPWM_InitTypeDef* MCPWM_InitStruct)
{

    memset(MCPWM_InitStruct, 0, sizeof(MCPWM_InitTypeDef));
}


/**
 *@brief @b 函数名称:   void MCPWM_Init(MCPWM_InitTypeDef *MCPWM_InitStruct)
 *@brief @b 功能描述:   MCPWM初始化函数
 *@see被引用内容：      SYS_ModuleClockCmd()
 *@param输入参数：      MCPWM_InitTypeDef *MCPWM_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
            MCPWM_InitTypeDef MCPWM_InitStructure;
            MCPWM_StructInit(&MCPWM_InitStructure);//初始化MCPWM相关结构体
            MCPWM_InitStructure.CLK_DIV = PWM_PRSC;                   // MCPWM时钟分频设置 
            MCPWM_InitStructure.MCLK_EN = ENABLE;                     // 模块时钟开启 
            MCPWM_InitStructure.MCPWM_Cnt_EN = ENABLE;                // 主计数器开始计数使能开关 
            MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE; // MCPWM CH0工作模式：中心对齐PWM模式
            MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE; // 通道工作模式设置，中心对齐或边沿对齐
            MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;
            MCPWM_InitStructure.MCPWM_WorkModeCH3 = CENTRAL_PWM_MODE;
            MCPWM_Init(&MCPWM_InitStructure);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2019年05月21日 <td>1.0       <td>Howlet         <td>创建
 * </table>
 */
void MCPWM_Init(MCPWM_InitTypeDef* MCPWM_InitStruct)
{
    SYS_ModuleClockCmd(SYS_Module_MCPWM,ENABLE);//MCPWM时钟使能
    
    MCPWM_PRT = 0x0000DEAD; /*enter password to unlock write protection */
    MCPWM_TCLK =    MCPWM_InitStruct->CLK_DIV                | (MCPWM_InitStruct->MCLK_EN          << 2)\
               	 | (MCPWM_InitStruct->MCPWM_Cnt_EN    << 3)  | (MCPWM_InitStruct->GPIO_BKIN_Filter << 8)\
                 | (MCPWM_InitStruct->CMP_BKIN_Filter << 12);
	
    MCPWM_TH = MCPWM_InitStruct->MCPWM_PERIOD;

    MCPWM_TMR0 = MCPWM_InitStruct->TriggerPoint0;
    MCPWM_TMR1 = MCPWM_InitStruct->TriggerPoint1;
    MCPWM_TMR2 = MCPWM_InitStruct->TriggerPoint2;
    MCPWM_TMR3 = MCPWM_InitStruct->TriggerPoint3;

    MCPWM_IO01 =    MCPWM_InitStruct->CH0N_Polarity_INV        | (MCPWM_InitStruct->CH0P_Polarity_INV << 1)  \
	               | (MCPWM_InitStruct->CH0_NS            << 2)  | (MCPWM_InitStruct->CH0_PS            << 3)  \
                 | (MCPWM_InitStruct->CH0N_SCTRLN       << 4)  | (MCPWM_InitStruct->CH0P_SCTRLP       << 5)  \
                 | (MCPWM_InitStruct->Switch_CH0N_CH0P  << 6)  | (MCPWM_InitStruct->MCPWM_WorkModeCH0 << 7)  \
                 | (MCPWM_InitStruct->CH1N_Polarity_INV << 8)  | (MCPWM_InitStruct->CH1P_Polarity_INV << 9)  \
	               | (MCPWM_InitStruct->CH1_NS            << 10) | (MCPWM_InitStruct->CH1_PS            << 11) \
	               | (MCPWM_InitStruct->CH1N_SCTRLN       << 12) | (MCPWM_InitStruct->CH1P_SCTRLP       << 13) \
                 | (MCPWM_InitStruct->Switch_CH1N_CH1P  << 14) | (MCPWM_InitStruct->MCPWM_WorkModeCH1 << 15) ;
								 
		MCPWM_IO23 =    MCPWM_InitStruct->CH2N_Polarity_INV        | (MCPWM_InitStruct->CH2P_Polarity_INV << 1)  \
	               | (MCPWM_InitStruct->CH2_NS            << 2)  | (MCPWM_InitStruct->CH2_PS            << 3)  \
                 | (MCPWM_InitStruct->CH2N_SCTRLN       << 4)  | (MCPWM_InitStruct->CH2P_SCTRLP       << 5)  \
                 | (MCPWM_InitStruct->Switch_CH2N_CH2P  << 6)  | (MCPWM_InitStruct->MCPWM_WorkModeCH2 << 7)  \
                 | (MCPWM_InitStruct->CH3N_Polarity_INV << 8)  | (MCPWM_InitStruct->CH3P_Polarity_INV << 9)  \
	               | (MCPWM_InitStruct->CH3_NS            << 10) | (MCPWM_InitStruct->CH3_PS            << 11) \
	               | (MCPWM_InitStruct->CH3N_SCTRLN       << 12) | (MCPWM_InitStruct->CH3P_SCTRLP       << 13) \
                 | (MCPWM_InitStruct->Switch_CH3N_CH3P  << 14) | (MCPWM_InitStruct->MCPWM_WorkModeCH3 << 15) ;
		
		MCPWM_PP   =     MCPWM_InitStruct->IO0_PPE        | ( MCPWM_InitStruct->IO1_PPE << 1 ) \
		             | ( MCPWM_InitStruct->IO2_PPE << 2 ) | ( MCPWM_InitStruct->IO3_PPE << 3 ) ;

    MCPWM_FAIL =     MCPWM_InitStruct->FAIL0_Signal_Sel           |  (MCPWM_InitStruct->FAIL1_Signal_Sel   << 1) \
		              | (MCPWM_InitStruct->FAIL0_Polarity  << 2)      |  (MCPWM_InitStruct->FAIL1_Polarity     << 3) \
                  | (MCPWM_InitStruct->FAIL0_INPUT_EN  << 4)      |  (MCPWM_InitStruct->FAIL1_INPUT_EN     << 5) \
                  
                  |                                                 (MCPWM_InitStruct->DebugMode_PWM_out   << 7) \
                  | (MCPWM_InitStruct->CH0P_default_output << 8)  | (MCPWM_InitStruct->CH0N_default_output << 9) \
                  | (MCPWM_InitStruct->CH1P_default_output << 10) | (MCPWM_InitStruct->CH1N_default_output << 11)\
                  | (MCPWM_InitStruct->CH2P_default_output << 12) | (MCPWM_InitStruct->CH2N_default_output << 13)\
                  | (MCPWM_InitStruct->CH3P_default_output << 14) | (MCPWM_InitStruct->CH3N_default_output << 15);

    MCPWM_SDCFG =    MCPWM_InitStruct->MCPWM_UpdateInterval       | (MCPWM_InitStruct->MCPWM_T0_UpdateEN << 4) \
                  | (MCPWM_InitStruct->MCPWM_T1_UpdateEN   << 5)  | (MCPWM_InitStruct->MCPWM_Auto_ERR_EN << 6) ;

    MCPWM_DTH00 = MCPWM_InitStruct->DeadTimeCH0N;
    MCPWM_DTH01 = MCPWM_InitStruct->DeadTimeCH0P;
    MCPWM_DTH10 = MCPWM_InitStruct->DeadTimeCH1N;
    MCPWM_DTH11 = MCPWM_InitStruct->DeadTimeCH1P;
    MCPWM_DTH20 = MCPWM_InitStruct->DeadTimeCH2N;
    MCPWM_DTH21 = MCPWM_InitStruct->DeadTimeCH2P;
    MCPWM_DTH30 = MCPWM_InitStruct->DeadTimeCH3N;
    MCPWM_DTH31 = MCPWM_InitStruct->DeadTimeCH3P;

    MCPWM_EIF   = 0xffff;
    MCPWM_IE    = MCPWM_InitStruct->T0_Update_INT_EN         | (MCPWM_InitStruct->T1_Update_INT_EN  << 1)  \
		           | (MCPWM_InitStruct->TH00_Match_INT_EN << 2)  | (MCPWM_InitStruct->TH01_Match_INT_EN << 3)  \
							 | (MCPWM_InitStruct->TH10_Match_INT_EN << 4)  | (MCPWM_InitStruct->TH11_Match_INT_EN << 5)  \
							 | (MCPWM_InitStruct->TH20_Match_INT_EN << 6)  | (MCPWM_InitStruct->TH21_Match_INT_EN << 7)  \
							 | (MCPWM_InitStruct->TH30_Match_INT_EN << 8)  | (MCPWM_InitStruct->TH31_Match_INT_EN << 9)  \
							 | (MCPWM_InitStruct->TMR0_Match_INT_EN << 10) | (MCPWM_InitStruct->TMR1_Match_INT_EN << 11) \
							 | (MCPWM_InitStruct->TMR2_Match_INT_EN << 12) | (MCPWM_InitStruct->TMR3_Match_INT_EN << 13) \
							 | (MCPWM_InitStruct->MCPWM_REG_UPDATE_INT_EN << 14);

    MCPWM_EIE = (MCPWM_InitStruct->FAIL0_INT_EN << 4) | (MCPWM_InitStruct->FAIL1_INT_EN << 5);

    MCPWM_UPDATE = 0xffff;    /* write whatever value to trigger update */

    MCPWM_UPDATE = 0x00;

    MCPWM_PRT = 0x0000CAFE;  /* write any value other than 0xDEAD to enable write protection */
}

/**
 *@brief @b 函数名称:   u16 MCPWM_GetIRQFlag(uint32_t INT_flag)
 *@brief @b 功能描述:   获取MCPWM中断标志
 *@see被引用内容：      无
 *@param输入参数：
 * <table>             <tr><th> MCPWM_T0_IRQ_IF       <td>BIT0  <td> 计数器计数值回到MCPWM_TH中断标志位 
 *                     <tr><th> MCPWM_T1_IRQ_IF       <td>BIT1  <td> 计数器计数值回到0中断标志位 
 *                     <tr><th> MCPWM_TH00_IRQ_IF     <td>BIT2  <td> 计数器计数值回到MCPWM_TH00中断标志位 
 *                     <tr><th> MCPWM_TH01_IRQ_IF     <td>BIT3  <td> 计数器计数值回到MCPWM_TH01中断标志位 
 *                     <tr><th> MCPWM_TH10_IRQ_IF     <td>BIT4  <td> 计数器计数值回到MCPWM_TH10中断标志位 
 *                     <tr><th> MCPWM_TH11_IRQ_IF     <td>BIT5  <td> 计数器计数值回到MCPWM_TH11中断标志位 
 *                     <tr><th> MCPWM_TH20_IRQ_IF     <td>BIT6  <td> 计数器计数值回到MCPWM_TH20中断标志位 
 *                     <tr><th> MCPWM_TH21_IRQ_IF     <td>BIT7  <td> 计数器计数值回到MCPWM_TH21中断标志位 
 *                     <tr><th> MCPWM_TH30_IRQ_IF     <td>BIT8  <td> 计数器计数值回到MCPWM_TH30中断标志位 
 *                     <tr><th> MCPWM_TH31_IRQ_IF     <td>BIT9  <td> 计数器计数值回到MCPWM_TH31中断标志位 
 *                     <tr><th> MCPWM_TMR0_IRQ_IF     <td>BIT10 <td> 计数器计数值回到MCPWM_TMR0中断标志位 
 *                     <tr><th> MCPWM_TMR1_IRQ_IF     <td>BIT11 <td> 计数器计数值回到MCPWM_TMR1中断标志位 
 *                     <tr><th> MCPWM_TMR2_IRQ_IF     <td>BIT12 <td> 计数器计数值回到MCPWM_TMR0中断标志位 
 *                     <tr><th> MCPWM_TMR3_IRQ_IF     <td>BIT13 <td> 计数器计数值回到MCPWM_TMR1中断标志位 
 *                     <tr><th> MCPWM_SHADE_IRQ_IF    <td>BIT14 <td> MCPWM_TH/MCPWM_TH00-MCPWM_TH31/MCPWM_TR0-MCPWM_TR3等寄存器更新到MCPWM实际运行系统中断标志位
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  读对应标志位是否为1，1位置位，0为未置位
 *@note其它说明：    无
 *@warning           只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
		   if(MCPWM_GetIRQFlag(MCPWM_T0_IRQ_EN))//获取MCPWM的计数器计数值回到MCPWM_TH中断标志
		   {
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
u16 MCPWM_GetIRQFlag(uint32_t INT_flag)
{
	  u8 MCPWMIRQFlag = 0;
	 if(INT_flag <= BIT14)
	 {
	     if(MCPWM_IF & INT_flag & MCPWM_IE)
				{
						MCPWMIRQFlag = 1;
				}
				else
				{
						MCPWMIRQFlag = 0;
				}
	 }
	 else
	 {
	     if(MCPWM_EIF & (INT_flag >> 15) & MCPWM_EIE)
				{
						MCPWMIRQFlag = 1;
				}
				else
				{
						MCPWMIRQFlag = 0;
				}
	 }
    return MCPWMIRQFlag;
}


/**
 *@brief @b 函数名称:   void MCPWM_ClearIRQFlag(uint32_t INT_flag)
 *@brief @b 功能描述:   清除MCPWM中断标志
 *@see被引用内容：      无
 *@param输入参数：
 * <table>             <tr><th> MCPWM_T0_IRQ_IF       <td>BIT0  <td> 计数器计数值回到MCPWM_TH中断标志位 
 *                     <tr><th> MCPWM_T1_IRQ_IF       <td>BIT1  <td> 计数器计数值回到0中断标志位 
 *                     <tr><th> MCPWM_TH00_IRQ_IF     <td>BIT2  <td> 计数器计数值回到MCPWM_TH00中断标志位 
 *                     <tr><th> MCPWM_TH01_IRQ_IF     <td>BIT3  <td> 计数器计数值回到MCPWM_TH01中断标志位 
 *                     <tr><th> MCPWM_TH10_IRQ_IF     <td>BIT4  <td> 计数器计数值回到MCPWM_TH10中断标志位 
 *                     <tr><th> MCPWM_TH11_IRQ_IF     <td>BIT5  <td> 计数器计数值回到MCPWM_TH11中断标志位 
 *                     <tr><th> MCPWM_TH20_IRQ_IF     <td>BIT6  <td> 计数器计数值回到MCPWM_TH20中断标志位 
 *                     <tr><th> MCPWM_TH21_IRQ_IF     <td>BIT7  <td> 计数器计数值回到MCPWM_TH21中断标志位 
 *                     <tr><th> MCPWM_TH30_IRQ_IF     <td>BIT8  <td> 计数器计数值回到MCPWM_TH30中断标志位 
 *                     <tr><th> MCPWM_TH31_IRQ_IF     <td>BIT9  <td> 计数器计数值回到MCPWM_TH31中断标志位 
 *                     <tr><th> MCPWM_TMR0_IRQ_IF     <td>BIT10 <td> 计数器计数值回到MCPWM_TMR0中断标志位 
 *                     <tr><th> MCPWM_TMR1_IRQ_IF     <td>BIT11 <td> 计数器计数值回到MCPWM_TMR1中断标志位 
 *                     <tr><th> MCPWM_TMR2_IRQ_IF     <td>BIT12 <td> 计数器计数值回到MCPWM_TMR0中断标志位 
 *                     <tr><th> MCPWM_TMR3_IRQ_IF     <td>BIT13 <td> 计数器计数值回到MCPWM_TMR1中断标志位 
 *                     <tr><th> MCPWM_SHADE_IRQ_IF    <td>BIT14 <td> MCPWM_TH/MCPWM_TH00-MCPWM_TH31/MCPWM_TR0-MCPWM_TR3等寄存器更新到MCPWM实际运行系统中断标志位
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    无
 *@warning          无
 *@par 示例代码：
 *@code
		   if(MCPWM_GetIRQFlag(MCPWM_T0_IRQ_EN))//获取MCPWM的计数器计数值回到MCPWM_TH中断标志
		   {
            MCPWM_ClearIRQFlag(MCPWM_T0_IRQ_EN);//清除MCPWM的计数器计数值回到MCPWM_TH中断标志
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void MCPWM_ClearIRQFlag(uint32_t INT_flag)
{
	 if(INT_flag <= BIT14)
	 {
	     MCPWM_IF = INT_flag;

	 }
	 else
	 {
	     MCPWM_EIF = (INT_flag >> 15);
	 }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
