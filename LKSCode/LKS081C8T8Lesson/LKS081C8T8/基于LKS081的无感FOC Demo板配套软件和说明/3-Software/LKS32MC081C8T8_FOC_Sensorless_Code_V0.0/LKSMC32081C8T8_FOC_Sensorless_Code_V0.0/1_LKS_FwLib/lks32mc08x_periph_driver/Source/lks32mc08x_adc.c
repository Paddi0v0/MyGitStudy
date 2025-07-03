/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_adc.c\n
 * 文件标识： 无 \n
 * 内容摘要： ADC外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月5日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 *@par 修改日志:调用NVR_Trim访问ADC加载值
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年12月15日 <td>1.1     <td>Howlet     <td>修改
 * </table>
 */

#include "lks32mc08x_adc.h"

/**
 *@brief @b 函数名称:   void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b 功能描述:   ADC初始化函数
 *@see被引用内容：      SYS_AnalogModuleClockCmd()
 *@param输入参数：      ADCx：ADC0 , ADC_InitTypeDef *ADC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			ADC_InitTypeDef ADC_InitStructure;
			ADC_StructInit(&ADC_InitStructure);                            // 初始化结构体
			ADC_InitStructure.ADC_CLK_DIV  = ADC_Clock_48M;                // ADC时钟选择48MHz
			ADC_InitStructure.Align = ADC_LEFT_ALIGN;                      // ADC数据输出左对齐
			ADC_InitStructure.Trigger_Mode = ADC_2SEG_TRG;                 // 设置ADC转换模式为双段式采样
			ADC_InitStructure.FirSeg_Ch = ADC_2_TIMES_SAMPLE;              // 第一段共采样2个通道
			ADC_InitStructure.SecSeg_Ch = ADC_2_TIMES_SAMPLE;              // 第二段共采样2个通道
			ADC_InitStructure.ThrSeg_Ch  = 0;                              // 第三段共采样0个通道
			ADC_InitStructure.FouSeg_Ch = 0;                               // 第四段共采样0个通道
			ADC_InitStructure.RefVol = RefVol_2V4;                         // ADC基准电压2.4V
			ADC_InitStructure.Gain0 = 0x0;                                 // ADC_DAT0-ADC_DAT9 (BIT0~BIT9)采样保持电路增益设置2/3
			ADC_InitStructure.Gain1 = 0x0;                                 // ADC_DAT10-ADC_DAT19(BIT10~BIT19)采样保持电路增益设置2/3
			ADC_InitStructure.Con_Sample = DISABLE;                        // 关闭连续采样
			// 打开 UTIMER T0 T1 硬件触发采样
			ADC_InitStructure.MCPWM_Trigger_En  = ADC_MCPWM_T0_TRG|ADC_MCPWM_T1_TRG;// 开启UTIMER硬件第一段和第二段触发采样
			ADC_InitStructure.UTIMER_Trigger_En = DISABLE;                 // 关闭UTIMER硬件触发采样
			ADC_InitStructure.Trigger_Cnt = 0;                             // 发生(Trigger_Cnt+1)次触发事件执行一段转换动作
			ADC_InitStructure.IE = ADC_EOS0_IRQ_EN | ADC_EOS1_IRQ_EN;      // ADC第一、二段采样结束中断使能
			ADC_Init(ADC0, &ADC_InitStructure);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2015年11月26日 <td>1.0     <td>Howlet Li       <td>创建
 * </table>
 */
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{
	uint16_t t_reg;

	SYS_AnalogModuleClockCmd(SYS_AnalogModule_ADC, ENABLE); // ADC模块使能

	SYS_WR_PROTECT = 0x7A83;						 //解除系统寄存器写保护
	SYS_AFE_REG1 |= ADC_InitStruct->RefVol << 3;		 // ADC基准电压选择
	SYS_AFE_REG7 = ADC_InitStruct->ADC_CLK_DIV << 4; // ADC时钟选择
	SYS_WR_PROTECT = 0x0;							 /*关闭系统寄存器写操作*/

	ADCx->IE = ADC_InitStruct->IE;

	t_reg = (ADC_InitStruct->Align) | (ADC_InitStruct->DAT0_TH_Type << 1);
	ADCx->CFG = t_reg;

	t_reg = (ADC_InitStruct->MCPWM_Trigger_En) | (ADC_InitStruct->UTIMER_Trigger_En << 4) |
			(ADC_InitStruct->Trigger_Cnt << 8) | (ADC_InitStruct->Trigger_Mode << 12) |
			(ADC_InitStruct->Con_Sample << 14);

	ADCx->TRG = t_reg; // TRIG

	ADCx->CHNT0 = ADC_InitStruct->FirSeg_Ch | (ADC_InitStruct->SecSeg_Ch << 8);
	ADCx->CHNT1 = ADC_InitStruct->ThrSeg_Ch | (ADC_InitStruct->FouSeg_Ch << 8);

	ADCx->DAT0_TH = ADC_InitStruct->DAT0_TH;

	ADCx->GAIN_0 = ADC_InitStruct->Gain0;

	ADCx->GAIN_1 = ADC_InitStruct->Gain1;

	if (ADC_InitStruct->Align == 0)
	{
		ADCx->DC_A0 = Read_Trim(0x00000310) << 4;
		ADCx->DC_A1 = Read_Trim(0x00000314) << 4;
		ADCx->AMC_A0 = Read_Trim(0x00000318);
		ADCx->AMC_A1 = Read_Trim(0x0000031C);

		ADCx->DC_B0 = Read_Trim(0x00000320) << 4;
		ADCx->DC_B1 = Read_Trim(0x00000324) << 4;
		ADCx->AMC_B0 = Read_Trim(0x00000328);
		ADCx->AMC_B1 = Read_Trim(0x0000032C);
	}
	else
	{
		ADCx->DC_A0 = Read_Trim(0x00000310);
		ADCx->DC_A1 = Read_Trim(0x00000314);
		ADCx->AMC_A0 = Read_Trim(0x00000318);
		ADCx->AMC_A1 = Read_Trim(0x0000031C);

		ADCx->DC_B0 = Read_Trim(0x00000320);
		ADCx->DC_B1 = Read_Trim(0x00000324);
		ADCx->AMC_B0 = Read_Trim(0x00000328);
		ADCx->AMC_B1 = Read_Trim(0x0000032C);
	}
}

/**
 *@brief @b 函数名称:   void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b 功能描述:   ADC结构体初始化
 *@see被引用内容：      无
 *@param输入参数：      ADC_InitTypeDef *ADC_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   ADC_InitTypeDef ADC_InitStructure;
		   ADC_StructInit(&ADC_InitStructure); //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月26日 <td>1.0     <td>Howlet     <td>修改
 * </table>
 */
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
	ADC_InitStruct->IE = 0;
	ADC_InitStruct->Align = 0;
	ADC_InitStruct->Con_Sample = 0;
	ADC_InitStruct->Trigger_Cnt = 0;
	ADC_InitStruct->FirSeg_Ch = 0;
	ADC_InitStruct->SecSeg_Ch = 0;
	ADC_InitStruct->ThrSeg_Ch = 0;
	ADC_InitStruct->FouSeg_Ch = 0;
	ADC_InitStruct->Trigger_Mode = 0;
	ADC_InitStruct->MCPWM_Trigger_En = 0;
	ADC_InitStruct->UTIMER_Trigger_En = 0;
	ADC_InitStruct->DAT0_TH_Type = 0;
	ADC_InitStruct->Gain0 = 0;   /* 0:2/3倍增益  3.6V 1:1倍增益 */
	ADC_InitStruct->Gain1 = 0;   /* 0:2/3倍增益  3.6V 1:1倍增益 */
	ADC_InitStruct->RefVol = 0;  /* 0:2.4V  1:1.2V */
                ADC_InitStruct->ADC_CLK_DIV = 0; /* 0:48MHz */
}

/**
 *@brief @b 函数名称:   void ADC_ClearIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b 功能描述:   ADC中断标志位清零
 *@see被引用内容：      无
 *@param输入参数：
 * <table>              <tr><td>ADCx：    <td> ADC0
 *                      <tr><td>INT_flag: <td> ADC中断标志
 * 						<tr><th>ADC_DAT0_OV_IRQ_IF       <td>ADC_DAT0超阈值中断标志位 \n
 * 						<tr><th>ADC_H_CONFLICT_IRQ_IF    <td>硬件触发冲突标志 \n
 * 						<tr><th>ADC_S_CONFLICT_IRQ_IF    <td>软件触发冲突标志 \n
 * 						<tr><th>ADC_EOS3_IRQ_IF          <td>第四段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS2_IRQ_IF          <td>第三段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS1_IRQ_IF          <td>第二段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS0_IRQ_IF          <td>第一段扫描结束中断标志 \n
 * 						<tr><th>ADC_ALL_IRQ_IF           <td>ADC全部中断标志位——可用于初始化 \n
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    无
 *@warning          无
 *@par 示例代码：
 *@code
		   if(ADC_GetIRQFlag(ADC0,ADC_EOS0_IRQ_IF))//获取第一段扫描结束中断标志
		   {
			  ADC_ClearIRQFlag(ADC0,ADC_EOS0_IRQ_IF)//第一段扫描结束中断标志
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_ClearIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
	ADCx->IF = INT_flag;
}

/**
 *@brief @b 函数名称:   uint16_t ADC_GetIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b 功能描述:   获取ADC中断标志
 *@see被引用内容：      无
 *@param输入参数：
 * <table>              <tr><td>ADCx：    <td> ADC0
 *                      <tr><td>INT_flag: <td> ADC中断标志
 * 						<tr><th>ADC_DAT0_OV_IRQ_IF       <td>ADC_DAT0超阈值中断标志位 \n
 * 						<tr><th>ADC_H_CONFLICT_IRQ_IF    <td>硬件触发冲突标志 \n
 * 						<tr><th>ADC_S_CONFLICT_IRQ_IF    <td>软件触发冲突标志 \n
 * 						<tr><th>ADC_EOS3_IRQ_IF          <td>第四段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS2_IRQ_IF          <td>第三段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS1_IRQ_IF          <td>第二段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS0_IRQ_IF          <td>第一段扫描结束中断标志 \n
 * 						<tr><th>ADC_ALL_IRQ_IF           <td>ADC全部中断标志位——可用于初始化 \n
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  读对应标志位是否为1，1位置位，0为未置位
 *@note其它说明：    无
 *@warning           只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
		   if(ADC_GetIRQFlag(ADC0,ADC_EOS0_IRQ_IF))//获取第一段扫描结束中断标志
		   {
			 ADC_ClearIRQFlag(ADC0,ADC_EOS0_IRQ_IF)//第一段扫描结束中断标志
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
u16 ADC_GetIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
	u8 ADCIRQFlag = 0;
	if (ADCx->IF & INT_flag & ADCx->IE)
	{
		ADCIRQFlag = 1;
	}
	else
	{
		ADCIRQFlag = 0;
	}
	return ADCIRQFlag;
}

/**
 *@brief @b 函数名称:   void ADC_ChannelConfig(ADC_TypeDef* ADCx,CHNx CHNum, uint16_t Channel_0 ,uint16_t Channel_1)
 *@brief @b 功能描述:   ADC采样通道设置
 *@see被引用内容：      CHNx
 *@param输入参数：
					   ADCx，08系列固定选择ADC0
 *                     CHNum为枚举类型，对应0-19；Channel_0为采样通道序号对应0-19
 *                     nChannel：ADC_CHANNEL_0 ~ ADC_CHANNEL_19
 *@param输出参数：     无
 *@return返 回 值：    无
 *@note其它说明：      无
 *@warning            无
 *@par 示例代码：
 *@code
		   ADC_ChannelConfig(ADC0,CHN0,ADC_CHANNEL_3);//配置ADC第0次采样ADC通道3的信号
		   ADC_ChannelConfig(ADC0,CHN1,ADC_CHANNEL_0);//配置ADC第1次采样ADC通道0的信号
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_ChannelConfig(ADC_TypeDef *ADCx, CHNx CHNum, uint16_t nChannel)
{
	u32 *p;
	u32 reg;
	p = (u32 *)&ADCx->CHN0;
	reg = p[CHNum >> 1];
	reg &= ~(0xff << (8 * (CHNum & 1)));
	reg |= nChannel << (8 * (CHNum & 1));
	p[CHNum >> 1] = reg;
}

/**
 *@brief @b 函数名称:   s16 ADC_GetConversionValue(DATNx DATNum)
 *@brief @b 功能描述:   读ADC采样值
 *@see被引用内容：      DATx
 *@param输入参数：      DATx：读取第几次采样结果值
 *@param输出参数：      无
 *@return返 回 值：     对应x次采样结果值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   s16 ADC_samp0 = 0；
		   ADC_samp0 = ADC_GetConversionValue(DAT0);//读取ADC第0次采样结果
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
s16 ADC_GetConversionValue(DATx DATNum)
{
	if (DATNum == DAT0)
	{
		return ADC0_DAT0;
	}
	else if (DATNum == DAT1)
	{
		return ADC0_DAT1;
	}
	else if (DATNum == DAT2)
	{
		return ADC0_DAT2;
	}
	else if (DATNum == DAT3)
	{
		return ADC0_DAT3;
	}
	else if (DATNum == DAT4)
	{
		return ADC0_DAT4;
	}
	else if (DATNum == DAT5)
	{
		return ADC0_DAT5;
	}
	else if (DATNum == DAT6)
	{
		return ADC0_DAT6;
	}
	else if (DATNum == DAT7)
	{
		return ADC0_DAT7;
	}
	else if (DATNum == DAT8)
	{
		return ADC0_DAT8;
	}
	else if (DATNum == DAT9)
	{
		return ADC0_DAT9;
	}
	else if (DATNum == DAT10)
	{
		return ADC0_DAT10;
	}
	else if (DATNum == DAT11)
	{
		return ADC0_DAT11;
	}
	else if (DATNum == DAT12)
	{
		return ADC0_DAT12;
	}
	else if (DATNum == DAT13)
	{
		return ADC0_DAT13;
	}
	else if (DATNum == DAT14)
	{
		return ADC0_DAT14;
	}
	else if (DATNum == DAT15)
	{
		return ADC0_DAT15;
	}
	else if (DATNum == DAT16)
	{
		return ADC0_DAT16;
	}
	else if (DATNum == DAT17)
	{
		return ADC0_DAT17;
	}
	else if (DATNum == DAT18)
	{
		return ADC0_DAT18;
	}
	else //(DATNum == DAT19)
	{
		return ADC0_DAT19;
	}
}

/**
 *@brief @b 函数名称:   void ADC_SoftTrgEN(ADC_TypeDef* ADCx, FuncState state)
 *@brief @b 功能描述:   ADC采样软件触发使能
 *@see被引用内容：      FuncState
 *@param输入参数：      ADCx，08系列固定选择ADC0
 *                     state：ENABLE触发，DISABLE不触发
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       ADC0_SWT写0x5AA5仅触发一次，完成后自动清零，等待下次软件触发
 *@warning             无
 *@par 示例代码：
 *@code
		  ADC_SoftTrgEN(ADC0，ENABLE);//软件触发一次ADC采样
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_SoftTrgEN(ADC_TypeDef *ADCx, FuncState state)
{
	if (state == ENABLE)
	{
		ADC0_SWT = 0x5AA5;
	}
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
