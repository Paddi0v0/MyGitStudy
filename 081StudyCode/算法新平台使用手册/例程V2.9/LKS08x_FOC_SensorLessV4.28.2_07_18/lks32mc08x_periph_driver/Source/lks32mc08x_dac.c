/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC08x_dac.c\n
 * 文件标识： 无 \n
 * 内容摘要： DAC外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
#include "lks32mc08x_dac.h"
#include "string.h"

/**
 *@brief @b 函数名称:   void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
 *@brief @b 功能描述:   DAC结构体初始化
 *@see被调用函数：       无
 *@param输入参数：      ADC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无   
 *@par 示例代码：
 *@code    
           DAC_StructInit DAC_InitStructure;
		   DAC_StructInit(&DAC_InitStructure); //初始化结构体
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
    memset(DAC_InitStruct, 0, sizeof(DAC_InitTypeDef));
}
/**
 *@brief @b 函数名称:   void DAC_init(DAC_InitTypeDef* DAC_InitStruct)
 *@brief @b 功能描述:   DAC初始化函数
 *@see被调用函数：      SYS_AnalogModuleClockCmd()
 *@param输入参数：      DAC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			  DAC_InitTypeDef DAC_InitStructure;
			  DAC_StructInit(&DAC_InitStructure);
			  DAC_InitStructure.DAC_GAIN = DAC_RANGE_1V2;//DAC量程为1.2V
			  DAC_InitStructure.DACOUT_EN = DISABLE ;    //DAC通过IO P0[0]输出
			  DAC_Init(&DAC_InitStructure);              // DAC初始化
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC, ENABLE);  /* DAC 时钟使能 */
	
	  SYS_WR_PROTECT = 0x7a83;  /* 解锁寄存器写保护 */
	
	  SYS_AFE_REG1 &= ~((u32)0x03 << 6);              /* DAC增益寄存器清零 */
      SYS_AFE_REG1 |= DAC_InitStruct->DAC_GAIN << 6;  /* 设置DAC满量程为1.2V */
	  
	  if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_1V2)
		{ /* 加载DAC 1.2V量程校正值 */
			SYS_AFE_DAC_DC = Read_Trim(0x00000344);
			SYS_AFE_DAC_AMC = Read_Trim(0x00000334);
		}
		else if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_3V0)
		{ /* 加载DAC 3.0V量程校正值 */
			SYS_AFE_DAC_DC = Read_Trim(0x00000340);
			SYS_AFE_DAC_AMC = Read_Trim(0x00000330);
		}
		else if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_4V85)
		{ /* 加载DAC 4.85V量程校正值 */
			SYS_AFE_DAC_DC = Read_Trim(0x00000348);
			SYS_AFE_DAC_AMC = Read_Trim(0x00000338);
		}
		
	  SYS_AFE_REG3 |= DAC_InitStruct->DACOUT_EN << 11;/* DAC输出配置 */
	  
	  SYS_WR_PROTECT = 0xffff;  /* 锁定寄存器写保护 */
}


/**
 *@brief @b 函数名称:   void DAC_OutputValue(uint32_t DACValue)
 *@brief @b 功能描述:   DAC输出数字量数值设置
 *@see被调用函数：       无
 *@param输入参数：       DACValue:DAC输出电压对应数字量
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           DAC_OutputValue(2048);//DAC输出2048*1.2/4096 = 0.6V
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void DAC_OutputValue(uint32_t DACValue)
{	
	  if(DACValue >=4095)
		{
		    DACValue = 4095;
		} 
	  SYS_AFE_DAC = DACValue ;	
}

/**
 *@brief @b 函数名称:   void DAC_OutputVoltage(uint32_t DACVoltage)
 *@brief @b 功能描述:   DAC输出模拟量数值设置
 *@see被调用函数：       无
 *@param输入参数：       DACVoltage:DAC输出电压对应数字量
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        输入变量DACVoltage为Q12格式，即输出1V对应DACVoltage = 1<<12 = 4096
 *@warning              无   
 *@par 示例代码：
 *@code    
           DAC_OutputVoltage(BIT12 * 0.6);//DAC输出0.6V
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void DAC_OutputVoltage(uint16_t DACVoltage)
{
	  u32 temp = 0;
	  u32 range = 0;
	
	  if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_1V2)
		{ /* 加载DAC 1.2V量程校正值 */
			range = (uint16_t)((1.0/1.2)*BIT12);
		}
		else if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_3V0)
		{ /* 加载DAC 3.0V量程校正值 */
			range = (uint16_t)((1.0/3.0)*BIT12);
		}
		else if (((SYS_AFE_REG1 >> 6) & 0x03) == DAC_RANGE_4V85)
		{ /* 加载DAC 4.85V量程校正值 */
			range = (uint16_t)((1.0/4.85)*BIT12);
		} 
	  temp = (DACVoltage * range + BIT11) >> 12; 
	
		if(temp >=4095)
		{
		    temp = 4095;
		}
	  SYS_AFE_DAC = temp ;
	
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
