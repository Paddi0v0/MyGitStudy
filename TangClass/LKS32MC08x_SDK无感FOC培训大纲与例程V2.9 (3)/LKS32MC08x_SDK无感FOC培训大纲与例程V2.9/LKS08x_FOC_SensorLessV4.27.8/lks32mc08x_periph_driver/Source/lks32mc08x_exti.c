/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_exti.c\n
 * 文件标识： 无 \n
 * 内容摘要： EXTI外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0    <td>YangZJ      <td>创建
 * </table>
 */
#include "lks32mc08x_exti.h"

/**
 *@brief @b 函数名称:   void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger)
 *@brief @b 功能描述:   GPIO外部触发极性选择
 *@see被引用内容：       GPIO_TypeDef
 *@param输入参数：       
                        GPIOx:GPIO对象可选(GPIO0) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15) \n
                        EXTI_Trigger:指定的触发极性 @see EXTI_Trigger参数来源：EXTIMode_TypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
		EXTI_Trigger_Config(GPIO0,GPIO_PinSource_0,EXTI_Trigger_Negedge);//P0.0信号下降沿触发外部中断事件
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ        <td>创建
 * </table>
 */
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger)
{
    if(GPIOx == GPIO0)
    {
        if(GPIO_PinSource>16)
        {
            return;
        }
        if(GPIO_PinSource<8)
        {
            EXTI->CR0 = (EXTI->CR0 & 0xfffc) | (EXTI_Trigger << (2 * GPIO_PinSource));
        }
        else
        {
            EXTI->CR1 = (EXTI->CR0 & 0xfffc) | (EXTI_Trigger << (2 * (GPIO_PinSource - 8)));
        }
    }
}

/**
 *@brief @b 函数名称:   u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
 *@brief @b 功能描述:   读取外部中断标志位
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象可选(GPIO0~GPIO3) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15)
 *@param输出参数：      无
 *@return返 回 值：     中断标志，高有效
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
		if(EXTI_GetIRQFlag(GPIO0,GPIO_PinSource_0))//获取P0.0外部中断标志位
        {
        }
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ        <td>创建
 * </table>
 */
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
{
    if(GPIO_PinSource>=16)
    {
        return 0;
    }
    if(GPIOx == GPIO0)
    {
        if(EXTI_IF & (1<<GPIO_PinSource))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

/**
 *@brief @b 函数名称:   void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
 *@brief @b 功能描述:   清除外部中断标志位
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象可选(GPIO0~GPIO3) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15)
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
		if(EXTI_GetIRQFlag(GPIO0,GPIO_PinSource_0))//获取P0.0外部中断标志位
        {
            EXTI_ClearIRQFlag(GPIO0,GPIO_PinSource_0);//清除P0.0外部中断标志位
        }
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ        <td>创建
 * </table>
 */
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
{
    if(GPIOx == GPIO0)
    {
        EXTI_IF = (1<<GPIO_PinSource);
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/


