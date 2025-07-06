/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_tim.c\n
 * 文件标识： 无 \n
 * 内容摘要： 定时器外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年06月06日 <td>1.0     <td>cfwu        <td>创建
 * </table>
 */

#include "lks32mc08x_tim.h"


/**
 *@brief @b 函数名称:   void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_TimerInitStruct)
 *@brief @b 功能描述:   定时器初始化函数
 *@see被引用内容：      SYS_ModuleClockCmd()
 *@param输入参数：      TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 \n
                        TIM_TimerInitTypeDef  *TIM_TimerInitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			          TIM_TimerInitTypeDef TIM_InitStruct;
                TIM_TimerStrutInit(&TIM_InitStruct);                   // Timer结构体初始化
								TIM_InitStruct.EN = ENABLE;                            // 定时器模块使能
                TIM_InitStruct.Timer_ClockDiv = TIM_Clk_Div1;          // 设置Timer模块时钟1分频系数 
                TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP;  // 设置Timer CH0 为比较模式
                TIM_InitStruct.Timer_CH0Output = 0;                    // 计数器回零时，比较模式输出极性控制 
                TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP;  // 设置Timer CH1 为比较模式 
                TIM_InitStruct.Timer_CH1Output = 0;                    // 计数器回零时，比较模式输出极性控制 
                TIM_InitStruct.Timer_TH = 48000;                       // 定时器计数门限初始值500us
                TIM_InitStruct.Timer_CMP0 = 36000;                     // 设置比较模式的CH0比较初始值25%转空比 
                TIM_InitStruct.Timer_CMP1 = 24000;                     // 设置比较模式的CH1比较初始值24000
                TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0;        // 开启Timer模块比较中断
                TIM_TimerInit(TIMER0, &TIM_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年06月06日 <td>1.0       <td>cfwu          <td>创建
 * </table>
 *@par 修改日志: 去除定时器使能接口
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月13日 <td>1.0      <td>HuangMG       <td>修改
 * </table>
 */
void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_TimerInitStruct)
{
    uint32_t tempIE;
    uint32_t tempVal;
    uint32_t tempFilter;
    uint32_t filter0;
    uint32_t filter1;

    SYS_ModuleClockCmd(SYS_Module_TIMER,ENABLE);     //打开Timer时钟

   TIM_TimerCmd(TIMERx,TIM_TimerInitStruct->EN);

    TIMERx->CFG = TIM_TimerInitStruct->Timer_CH0_CapMode | (TIM_TimerInitStruct->Timer_CH0_WorkMode << 2)
                  | (TIM_TimerInitStruct->Timer_CH0Output << 3) | (TIM_TimerInitStruct->Timer_CH1_CapMode << 4)
                  | (TIM_TimerInitStruct->Timer_CH1_WorkMode << 6) | (TIM_TimerInitStruct->Timer_CH1Output << 7)
                  | (TIM_TimerInitStruct->Timer_ClockDiv << 8);
    TIMERx->TH = TIM_TimerInitStruct->Timer_TH;
    TIMERx->CMPT0 = TIM_TimerInitStruct->Timer_CMP0;
    TIMERx->CMPT1 = TIM_TimerInitStruct->Timer_CMP1;

    /*使能定时器中断*/
    /*滤波参数*/
    tempIE = UTIMER_IE;
    filter0 = TIM_TimerInitStruct->Timer_Filter0 & 0x000F;    /*滤波参数只使用低四位*/
    filter1 = TIM_TimerInitStruct->Timer_Filter1 & 0x000F;
    if (TIMERx == TIMER0)
    {
        tempVal = 0x0007;
        tempIE &= ~tempVal;
        tempIE |= (TIM_TimerInitStruct->Timer_IRQEna);

        tempFilter = UTIMER_FLT_TH01;
        tempFilter &= 0xFF00;
        tempFilter |= filter0;
        tempFilter |= (filter1 << 4);
        UTIMER_FLT_TH01 = tempFilter;
    }
    else if (TIMERx == TIMER1)
    {
        tempVal = 0x0038;
        tempIE &= ~tempVal;
        tempIE |= (TIM_TimerInitStruct->Timer_IRQEna << 3);

        tempFilter = UTIMER_FLT_TH01;
        tempFilter &= 0x00FF;
        tempFilter |= (filter0 << 8);
        tempFilter |= (filter1 << 12);
        UTIMER_FLT_TH01 = tempFilter;
    }
    else if (TIMERx == TIMER2)
    {
        tempVal = 0x01C0;
        tempIE &= ~tempVal;
        tempIE |= (TIM_TimerInitStruct->Timer_IRQEna << 6);

        tempFilter = UTIMER_FLT_TH23;
        tempFilter &= 0xFF00;
        tempFilter |= filter0;
        tempFilter |= (filter1 << 4);
        UTIMER_FLT_TH23 = tempFilter;
    }
    else if (TIMERx == TIMER3)
    {
        tempVal = 0x0E00;
        tempIE &= ~tempVal;
        tempIE |= (TIM_TimerInitStruct->Timer_IRQEna << 9);

        tempFilter = UTIMER_FLT_TH23;
        tempFilter &= 0x00FF;
        tempFilter |= (filter0 << 8);
        tempFilter |= (filter1 << 12);
        UTIMER_FLT_TH23 = tempFilter;
    }
    UTIMER_IE = tempIE;
}

/**
 *@brief @b 函数名称:   void TIM_TimerStrutInit(TIM_TimerInitTypeDef *TIM_TimerInitStruct)
 *@brief @b 功能描述:   定时器结构体初始化
 *@see被引用内容：      无
 *@param输入参数：      TIM_TimerInitTypeDef  *TIM_TimerInitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			    TIM_TimerInitTypeDef TIM_InitStruct;
                TIM_TimerStrutInit(&TIM_InitStruct);  // Timer结构体初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年06月06日 <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void TIM_TimerStrutInit(TIM_TimerInitTypeDef *TIM_TimerInitStruct)
{
    TIM_TimerInitStruct->Timer_CH0_CapMode = TIMER_CapMode_None;
    TIM_TimerInitStruct->Timer_CH0_WorkMode = TIMER_OPMode_CMP;
    TIM_TimerInitStruct->Timer_CH0Output = 0;

    TIM_TimerInitStruct->Timer_CH1_CapMode = TIMER_CapMode_None;
    TIM_TimerInitStruct->Timer_CH1_WorkMode = TIMER_OPMode_CMP;
    TIM_TimerInitStruct->Timer_CH1Output = 0;

    TIM_TimerInitStruct->Timer_TH = 1000;
    TIM_TimerInitStruct->Timer_CMP0 = 500;
    TIM_TimerInitStruct->Timer_CMP1 = 500;
    TIM_TimerInitStruct->Timer_Filter0 = 0;
    TIM_TimerInitStruct->Timer_Filter1 = 0;
    TIM_TimerInitStruct->Timer_ClockDiv = TIM_Clk_Div1;
    TIM_TimerInitStruct->Timer_IRQEna = Timer_IRQEna_None;
    TIM_TimerInitStruct->EN = DISABLE;
}

/**
 *@brief @b 函数名称:  void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
 *@brief @b 功能描述:   定时器TIMERx使能和停止
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 \n
                        FuncState state：使能与失能
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			    TIM_TimerCmd(TIMER0, ENABLE); // Timer0模块使能
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
{
    if (state != DISABLE)
    {
        if (TIMERx == TIMER0)
        {
            UTIMER_CFG |= BIT4;
        }
        else if (TIMERx == TIMER1)
        {
            UTIMER_CFG |= BIT5;
        }
        else if (TIMERx == TIMER2)
        {
            UTIMER_CFG |= BIT6;
        }
        else if (TIMERx == TIMER3)
        {
            UTIMER_CFG |= BIT7;
        }

    }
    else
    {
        if (TIMERx == TIMER0)
        {
            UTIMER_CFG &= ~BIT4;
        }
        else if (TIMERx == TIMER1)
        {
            UTIMER_CFG &= ~BIT5;
        }
        else if (TIMERx == TIMER2)
        {
            UTIMER_CFG &= ~BIT6;
        }
        else if (TIMERx == TIMER3)
        {
            UTIMER_CFG &= ~BIT7;
        }
    }
}


/**
 *@brief @b 函数名称:   uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if)
 *@brief @b 功能描述:   获取TIM中断标志
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 \n
                        timer_if：
 * <table>              <tr><th>TIMER_IF_CH1   <td>Timer CH1中断，比较或捕获中断
                        <tr><th>TIMER_IF_CH0   <td>Timer CH0中断，比较或捕获中断
                        <tr><th>TIMER_IF_ZERO  <td>Timer 过零中断
 * </table> 
 *@param输出参数：      无
 *@return返 回 值：     0或1，对应中断标志置位返回1，未置位返回0
 *@note其它说明：       无
 *@warning             只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
			    if(TIM_GetIRQFlag(TIMER0,TIMER_IF_CH0)) //判断UTimer0的CH0是否发生比较中断
                {
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if)
{
	if(TIMERx == TIMER0)
    {
			if((UTIMER_IF & timer_if & UTIMER_IE) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
		
		if(TIMERx == TIMER1)
    {
			if(((UTIMER_IF>>3) & timer_if & (UTIMER_IE>>3)) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
		
	  if(TIMERx == TIMER2)
    {
			if(((UTIMER_IF>>6) & timer_if & (UTIMER_IE>>6)) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
		
    if(TIMERx == TIMER3)
    {
			if(((UTIMER_IF>>9) & timer_if & (UTIMER_IE>>9)) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
		return 0;
}

/**
 *@brief @b 函数名称:   void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx ,uint32_t tempFlag)
 *@brief @b 功能描述:   清除TIM中断标志
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 \n
                        timer_if：
 * <table>              <tr><th>TIMER_IF_CH1   <td>Timer CH1中断，比较或捕获中断
                        <tr><th>TIMER_IF_CH0   <td>Timer CH0中断，比较或捕获中断
                        <tr><th>TIMER_IF_ZERO  <td>Timer 过零中断
 * </table> 
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
			    if(TIM_GetIRQFlag(TIMER0,TIMER_IF_CH0)) //判断UTimer0的CH0是否发生比较中断
                {
                    TIM_ClearIRQFlag(TIMER0,TIMER_IF_CH0); //清除UTimer0通道0比较中断标志位
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx ,uint32_t tempFlag)
{
	  if(TIMERx == TIMER0)
		{
			UTIMER_IF = tempFlag;
		}
		if(TIMERx == TIMER1)
		{
			UTIMER_IF = tempFlag<<3;
		}
	  if(TIMERx == TIMER2)
		{
			UTIMER_IF = tempFlag<<6;
		}
	  if(TIMERx == TIMER3)
		{
			UTIMER_IF = tempFlag<<9;
		}
}

/**
 *@brief @b 函数名称:   uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
 *@brief @b 功能描述:   获取Timer计数值
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_Value = 0;
                    TIMER0_Value = TIM_Timer_GetCount(TIMER0); //获取定时器0计数值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2016年06月06日 <td>1.0      <td>cfwu          <td>修改
 * </table>
 */
uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
{
    return TIMERx->CNT;
}

/**
 *@brief @b 函数名称:   uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx)
 *@brief @b 功能描述:   获取定时器通道0捕获值
 *@see被引用内容：       无
 *@param输入参数：      TIM_TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 
 *@param输出参数：      无
 *@return返 回 值：     定时器通道0捕获值
 *@note其它说明：       当定时器发生捕获事件时，将捕获时刻的cnt值存储到该寄存器中
 *@warning              无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT0(TIMER0); //获取定时器0捕获值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2016年06月06日 <td>1.0      <td>cfwu          <td>修改
 * </table>
 */
uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx)
{
    return TIM_TIMERx->CMPT0;
}

/**
 *@brief @b 函数名称:   uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx)
 *@brief @b 功能描述:   获取定时器通道1捕获值
 *@see被引用内容：      无
 *@param输入参数：      TIM_TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 
 *@param输出参数：      无
 *@return返 回 值：     定时器通道1捕获值
 *@note其它说明：       当定时器发生捕获事件时，将捕获时刻的cnt值存储到该寄存器中
 *@warning              无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT1(TIMER0); //获取定时器0捕获值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2016年06月06日 <td>1.0      <td>cfwu          <td>修改
 * </table>
 */
uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx)
{
    return TIM_TIMERx->CMPT1;
}

/**
 *@brief @b 函数名称:   void TIM_ECDInit(TIM_ECDTypeDef *ECDx, TIM_ECDInitTypeDef *TIM_ECDInitStruct)
 *@brief @b 功能描述:   编码器初始化函数
 *@see被引用内容：      SYS_ModuleClockCmd();
 *@param输入参数：      ECDx：ECD0/ECD1 \n
                       TIM_ECDInitTypeDef *TIM_ECDInitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
                    TIM_ECDInitTypeDef TIM_ECDInitStruct;
                    TIM_ECDStructInit(&TIM_ECDInitStruct);
                    TIM_ECDInitStruct.ECD_ClockDiv = ECD_Clk_Div1;      //96M
                    TIM_ECDInitStruct.ECD_Filter0 = 10;                 //CH0滤波，滤波宽度为Timer_Filter0*8
                                                                            个时钟周期 ECD_Filter00~15
                    TIM_ECDInitStruct.ECD_Filter1 = 10;                 //CH1滤波
                    TIM_ECDInitStruct.ECD_Mode = ECD_Mode_CCWSIGN;      //CCW+SIGN, 仅计数信号上升沿
                    TIM_ECDInitStruct.ECD_TH = 4096;                    //计数门限
                    TIM_ECDInitStruct.ECD_IRQEna = ECD_IRQEna_OverFlow; //使能上溢中断
                    TIM_ECDInit(ECD0, &TIM_ECDInitStruct);
                    TIM_ECDCmd(ECD0,ENABLE);                            //使能ECD0模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2016年06月06日 <td>1.0      <td>cfwu          <td>修改
 * </table>
 *@par 修改日志:增加定时器时钟使能函数
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0      <td>HuangMG       <td>修改
 * </table>
 */
void TIM_ECDInit(TIM_ECDTypeDef *ECDx, TIM_ECDInitTypeDef *TIM_ECDInitStruct)
{
    uint32_t tempIE;
    uint32_t tempFilter;
    uint32_t filter0;
    uint32_t filter1;
    uint32_t tempTimerCfg;

	  SYS_ModuleClockCmd(SYS_Module_TIMER,ENABLE);    /*打开Timer时钟*/
	
    ECDx->CFG = TIM_ECDInitStruct->ECD_Mode << 8;
    ECDx->TH = TIM_ECDInitStruct->ECD_TH;

    filter0 = TIM_ECDInitStruct->ECD_Filter0 & 0x000F;	/*滤波参数只使用低四位*/
    filter1 = TIM_ECDInitStruct->ECD_Filter1 & 0x000F;
    tempIE = UTIMER_IE;
    if (ECDx == ECD0)
    {
        tempFilter = UTIMER_FLT_TH23;
        tempFilter &= 0xFF00;
        tempFilter |= filter0;
        tempFilter |= (filter1 << 4);
        UTIMER_FLT_TH23 = tempFilter;

        tempIE |= (TIM_ECDInitStruct->ECD_IRQEna << 12);

        tempTimerCfg = TIMER2->CFG;
        tempTimerCfg &= ~(0x0300);
        tempTimerCfg |= (TIM_ECDInitStruct->ECD_ClockDiv << 8);
        TIMER2->CFG = tempTimerCfg;
        UTIMER_CFG |= BIT8;
    }
    else if (ECDx == ECD1)
    {
        tempFilter = UTIMER_FLT_TH23;
        tempFilter &= 0x00FF;
        tempFilter |= (filter0 << 8);
        tempFilter |= (filter1 << 12);
        UTIMER_FLT_TH23 = tempFilter;

        tempIE |= (TIM_ECDInitStruct->ECD_IRQEna << 14);

        tempTimerCfg = TIMER3->CFG;
        tempTimerCfg &= ~(0x0300);
        tempTimerCfg |= (TIM_ECDInitStruct->ECD_ClockDiv << 8);
        TIMER3->CFG = tempTimerCfg;
        UTIMER_CFG |= BIT9;
    }
    UTIMER_IE = tempIE;
}

/**
 *@brief @b 函数名称:   void TIM_ECDInit(TIM_ECDTypeDef *ECDx, TIM_ECDInitTypeDef *TIM_ECDInitStruct)
 *@brief @b 功能描述:   编码器结构体初始化  
 *@see被引用内容：      无
 *@param输入参数：      TIM_ECDInitTypeDef *TIM_ECDInitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
                    TIM_ECDInitTypeDef TIM_ECDInitStruct;
                    TIM_ECDStructInit(&TIM_ECDInitStruct);//编码器结构体初始化                               
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年06月06日 <td>1.0      <td>cfwu          <td>修改
 * </table>
 */
void TIM_ECDStructInit(TIM_ECDInitTypeDef *TIM_ECDInitStruct)
{
    TIM_ECDInitStruct->ECD_Mode = ECD_Mode_T1;
    TIM_ECDInitStruct->ECD_TH = 1000;
    TIM_ECDInitStruct->ECD_ClockDiv = TIM_Clk_Div1;
    TIM_ECDInitStruct->ECD_Filter0 = 0;
    TIM_ECDInitStruct->ECD_Filter1 = 0;
    TIM_ECDInitStruct->ECD_IRQEna = ECD_IRQEna_UnderFlow | ECD_IRQEna_OverFlow;
}

/**
 *@brief @b 函数名称:   void TIM_ECDCmd(TIM_ECDTypeDef *ECDx, FuncState state)
 *@brief @b 功能描述:   编码器ECDx使能和停止
 *@see被引用内容：      无
 *@param输入参数：      ECDx：ECD0/ECD1 \n
                       FuncState state：使能与失能
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			    TIM_ECDCmd(ECD0, ENABLE); // ECD0模块使能
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
void TIM_ECDCmd(TIM_ECDTypeDef *ECDx, FuncState state)
{
    uint32_t tempEna;
    tempEna = UTIMER_CFG;

    if (state != DISABLE)
    {
        if (ECDx == ECD0)
        {
            tempEna |= BIT8;
        }
        else if (ECDx == ECD1)
        {
            tempEna |= BIT9;
        }
    }
    else
    {
        if (ECDx == ECD0)
        {
            tempEna &= ~BIT8;
        }
        else if (ECDx == ECD1)
        {
            tempEna &= ~BIT9;
        }
    }
    UTIMER_CFG = tempEna;
}

/**
 *@brief @b 函数名称:   uint32_t TIM_ECD_GetCount(TIM_ECDTypeDef *TIM_ECDx)
 *@brief @b 功能描述:   编码器计数值
 *@see被引用内容：       无
 *@param输入参数：       ECDx：ECD0/ECD1 \n
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			    uint32_t ECD0_Value = 0;
                ECD0_Value = TIM_ECD_GetCount(ECD0); //获取编码器0计数值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年06月06日 <td>1.0        <td>cfwu          <td>修改
 * </table>
 */
uint32_t TIM_ECD_GetCount(TIM_ECDTypeDef *TIM_ECDx)
{
    return TIM_ECDx->CNT;
}


/**
 *@brief @b 函数名称:   uint32_t ECD_GetIRQFlag(TIM_ECDTypeDef *ECDx , u32 timer_if)
 *@brief @b 功能描述:   获取ECD中断标志
 *@see被引用内容：       无
 *@param输入参数：       ECDx：ECD0/ECD1 \n
                        timer_if：
 * <table>              <tr><th>ECD_IF_UNDERFLOW   <td>Encoder下溢中断
                        <tr><th>ECD_IF_OVERFLOW    <td>Encoder上溢中断                 
 * </table> 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
			    if(ECD_GetIRQFlag(ECD0,ECD_IF_OVERFLOW)) //获取上溢中断标志
                {
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
uint32_t ECD_GetIRQFlag(TIM_ECDTypeDef *ECDx , u32 timer_if)
{
	if(ECDx == ECD0)
    {
			if(((UTIMER_IF>>12) & timer_if & (UTIMER_IE>>12)) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
		
		if(ECDx == ECD1)
    {
			if(((UTIMER_IF>>14) & timer_if & (UTIMER_IE>>14)) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
		return 0;
}


/*******************************************************************************
 函数名称：    void ECD_ClearIRQFlag(TIM_ECDTypeDef *ECDx , uint32_t tempFlag)
 功能描述：    清除ECD中断标志
 操作的表：    无
 输入参数：    ECD中断标志
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/13      V1.0           HuangMG            创建
 *******************************************************************************/
/**
 *@brief @b 函数名称:   void ECD_ClearIRQFlag(TIM_ECDTypeDef *ECDx , uint32_t tempFlag)
 *@brief @b 功能描述:   清除ECD中断标志
 *@see被引用内容：       无
 *@param输入参数：       ECDx：ECD0/ECD1 \n
                        timer_if：
 * <table>              <tr><th>ECD_IF_UNDERFLOW   <td>Encoder下溢中断
                        <tr><th>ECD_IF_OVERFLOW    <td>Encoder上溢中断                 
 * </table> 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			    if(ECD_GetIRQFlag(ECD0,ECD_IF_OVERFLOW)) //获取编码器上溢中断标志
                {
                    ECD_ClearIRQFlag(ECD0,ECD_IF_OVERFLOW);//清除编码器上溢中断标志
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
void ECD_ClearIRQFlag(TIM_ECDTypeDef *ECDx , uint32_t tempFlag)
{
	  if(ECDx == ECD0)
		{
			UTIMER_IF = tempFlag<<12;
		}
		if(ECDx == ECD1)
		{
			UTIMER_IF = tempFlag<<14;
		}
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
