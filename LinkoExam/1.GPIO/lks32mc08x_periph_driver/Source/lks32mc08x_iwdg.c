/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_IWDG.c\n
 * 文件标识： 无 \n
 * 内容摘要： IWDG外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */

#include "lks32mc08x_iwdg.h"

/**
 *@brief @b 函数名称:   void IWDG_Init(IWDG_InitTypeDef *this)
 *@brief @b 功能描述:   看门狗初始化
 *@see被引用内容：       无
 *@param输入参数：       IWDG_InitTypeDef *this 看门狗配置结构体
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_InitTypeDef IWDG_InitStruct;
                IWDG_StrutInit(&IWDG_InitStruct);    //初始化结构体
                IWDG_InitStruct.WDG_EN  = ENABLE;    //使能看门狗
                IWDG_InitStruct.RTH     = WDT_RTH_2S;//设置看门狗2S后复位芯片
                IWDG_Init(&IWDG_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_Init(IWDG_InitTypeDef *this)
{
    SYS_WR_PROTECT = 0xCAFE;
    SYS_WDT_CLR = 0x7988 | (this->RTH << 1) | (1);
    SYS_WR_PROTECT = 0x7a83;
    if (this->WDG_EN)
    {
        SYS_RST_CFG |= BIT0;
    }
    else
    {
        SYS_RST_CFG &= ~BIT0;
    }
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b 函数名称:   void IWDG_StrutInit(IWDG_InitTypeDef *this)
 *@brief @b 功能描述:   看门狗配置结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       IWDG_InitTypeDef *this 看门狗配置结构体
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_InitTypeDef IWDG_InitStruct;
                IWDG_StrutInit(&IWDG_InitStruct);    //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_StrutInit(IWDG_InitTypeDef *this)
{
    this->WDG_EN = DISABLE; // 独立看门狗使能
    this->RTH = WDT_RTH_8S; // 看门狗超时复位时间（21位计数器，但低12恒位0）
                            // SECOND2IWDGCNT输入参数，秒
    //this->DWK_EN = DISABLE;             // 深度休眠定时唤醒使能
    //this->WTH = SECOND2IWDGCNT(1);      // 看门狗定时唤醒时间,大于复位时间后无效
}

/**
 *@brief @b 函数名称:   void IWDG_DISABLE(void)
 *@brief @b 功能描述:   关闭看门狗模块
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_DISABLE();    //关闭看门狗模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_DISABLE(void)
{
    SYS_RST_CFG &= ~BIT0;
}

/**
 *@brief @b 函数名称:   void IWDG_ENABLE(void)
 *@brief @b 功能描述:   打开看门狗模块
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_ENABLE();    //打开看门狗模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_ENABLE(void)
{
    SYS_RST_CFG |= BIT0;
}

/**
 *@brief @b 函数名称:   void IWDG_Feed(uint32_t timeOut)
 *@brief @b 功能描述:   看门狗喂狗
 *@see被引用内容：       无
 *@param输入参数：       
                        timeOut：看门狗复位时间 \n
                        WDT_RTH_2S    3s \n
                        WDT_RTH_4S    2s \n
                        WDT_RTH_8S    1s \n
                        WDT_RTH_64S   0s
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_Feed(WDT_RTH_2S);    //看门狗喂狗，且设置下一次复位时间为2S
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_Feed(uint32_t timeOut)
{
	
	SYS_WR_PROTECT = 0xCAFE; // 0xCAFE;

    if (timeOut == (uint32_t)WDT_RTH_64S)
    {
        SYS_WDT_CLR = 0x7989; // 1 00 1
    }
    else if (timeOut == (uint32_t)WDT_RTH_8S)
    {
        SYS_WDT_CLR = 0x798B; // 1 01 1
    }
    else if (timeOut == (uint32_t)WDT_RTH_4S)
    {
        SYS_WDT_CLR = 0x798D; // 1 10 1
    }
    else // WDT_RTH_2S
    {
        SYS_WDT_CLR = 0x798F; // 1 11 1
    }

    SYS_WR_PROTECT = 0;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
