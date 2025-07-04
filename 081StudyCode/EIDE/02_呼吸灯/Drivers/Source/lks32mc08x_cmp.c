/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_cmp.c\n
 * 文件标识： 无 \n
 * 内容摘要： cmp外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2019年3月5日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */
#include "lks32mc08x_cmp.h"

/**
 *@brief @b 函数名称:   CMP_Init(CMP_InitTypeDef* this)
 *@brief @b 功能描述:   CMP初始化
 *@see被调用函数：      SYS_AnalogModuleClockCmd()
 *@param输入参数：      CMP_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            CMP_InitTypeDef CMP_InitStruct;
            CMP_StructInit(&CMP_InitStruct);
            CMP_InitStruct.CLK10_EN             = ENABLE        ;   // 比较器 1/0 滤波时钟使能
            CMP_InitStruct.FIL_CLK10_DIV16      = 15            ;   // 比较器 1/0 滤波系数       0-0xF
            CMP_InitStruct.FIL_CLK10_DIV2       = 0             ;   // 比较器 1/0 滤波移位系数   0-0x3   最终分频系数为 (DIV16+1)<<DIV2
            CMP_InitStruct.CMP_FT               = DISABLE       ;   // 比较器快速比较使能
            CMP_InitStruct.CMP_HYS              = 0             ;   // 比较器回差选择            0：回差20mV 1：回差0mV
            
            CMP_InitStruct.CMP1_EN              = ENABLE        ;   // 比较器 1 使能
            CMP_InitStruct.CMP1_IN_EN           = ENABLE        ;   // 比较器 1 信号输入使能 影响比较器数字模块信号，模拟部分不受影响
            CMP_InitStruct.CMP1_SELP            = CMP1_SELP_IP2 ;   // 比较器 1 信号正端选择 见 CMP1_SELP_CMP1_IP0 比较器定义
            CMP_InitStruct.CMP1_SELN            = CMP_SELN_DAC  ;   // 比较器 1 信号负端选择
            CMP_InitStruct.CMP1_IE              = ENABLE        ;   // 比较器 1 中断使能
            CMP_InitStruct.CMP1_POL             = 0             ;   // 比较器 1 极性选择     0：高电平有效 1：低电平有效 只影响比较器中断
            CMP_InitStruct.CMP1_RE              = DISABLE       ;   // 比较器 1 DMA 请求使能
            CMP_InitStruct.CMP1_IRQ_TRIG        = DISABLE       ;   // 比较器 1 边沿触发使能
            CMP_InitStruct.CMP1_CHN3P_WIN_EN    = DISABLE       ;   // MCPWM 模块 CHN3_P 通道使能比较器 1 开窗
            CMP_InitStruct.CMP1_CHN2P_WIN_EN    = DISABLE       ;   // MCPWM 模块 CHN2_P 通道使能比较器 1 开窗
            CMP_InitStruct.CMP1_CHN1P_WIN_EN    = DISABLE       ;   // MCPWM 模块 CHN1_P 通道使能比较器 1 开窗
            CMP_InitStruct.CMP1_CHN0P_WIN_EN    = DISABLE       ;   // MCPWM 模块 CHN0_P 通道使能比较器 1 开窗
            CMP_InitStruct.CMP1_W_PWM_POL       = DISABLE       ;   // 比较器 1 开窗 PWM 信号极性选择  0:高电平有效；1:低电平有效
            CMP_Init(&CMP_InitStruct);
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2018年11月26日 <td>1.0     <td>Howlet Li       <td>创建
 * </table>
 */
void CMP_Init(CMP_InitTypeDef* this)
{
    // Comparator初始化
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP1,this->CMP1_EN);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP0,this->CMP0_EN);
    SYS_WR_PROTECT = 0x7A83;
    
    SYS_AFE_REG3 |= (this->CMP0_SELN << 2) | (this->CMP1_SELN << 4) | (this->CMP0_SELP << 8) |
                    (this->CMP1_SELP << 12) | (this->CMP_HYS << 7);

    /* CMP_HYS 比较器滞回功能，默认20mV, 写0关闭 */

    SYS_AFE_REG1 |= this->CMP_FT; /* 快速比较，Enable后 30nS */

    SYS_AFE_REG5 |= (this->CMP0_EN << 6) | (this->CMP1_EN << 7);
    
    SYS_WR_PROTECT = 0;
    
    CMP -> IE      = (this -> CMP1_IE           <<  1) | (this -> CMP0_IE);
    if(this->CLK10_EN == DISABLE)
    {
        if(this->CMP1_IN_EN || this->CMP0_IN_EN)
        {
            CMP->TCLK = BIT3;
        }
        else
        {
            CMP->TCLK = 0;
        }
    }
    else
    {
        CMP->TCLK  = (this -> FIL_CLK10_DIV16   <<  4) | (this -> CLK10_EN          <<  3) |
                     (this -> FIL_CLK10_DIV2);
    }
    CMP -> CFG     = (this -> CMP1_W_PWM_POL    <<  7) | (this -> CMP1_IRQ_TRIG     <<  6) |
                     (this -> CMP1_IN_EN        <<  5) | (this -> CMP1_POL          <<  4) |
                     (this -> CMP0_W_PWM_POL    <<  3) | (this -> CMP0_IRQ_TRIG     <<  2) |
                     (this -> CMP0_IN_EN        <<  1) | (this -> CMP0_POL);           
    CMP -> BLCWIN  = (this -> CMP1_CHN3P_WIN_EN <<  7) | (this -> CMP1_CHN2P_WIN_EN <<  6) |
                     (this -> CMP1_CHN1P_WIN_EN <<  5) | (this -> CMP1_CHN0P_WIN_EN <<  4) |
                     (this -> CMP0_CHN3P_WIN_EN <<  3) | (this -> CMP0_CHN2P_WIN_EN <<  2) |
                     (this -> CMP0_CHN1P_WIN_EN <<  1) | (this -> CMP0_CHN0P_WIN_EN);
    CMP -> IF = 3;
}
/**
 *@brief @b 函数名称:   void CMP_StructInit(CMP_InitTypeDef* CMP_InitStruct)
 *@brief @b 功能描述:   ADC结构体初始化
 *@see被调用函数：       无
 *@param输入参数：       CMP_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            CMP_StructInit CMP_InitStructure;
		    CMP_StructInit(&CMP_InitStructure); //初始化结构体
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2018年11月26日 <td>1.0     <td>Howlet Li       <td>创建
 * </table>
 */
void CMP_StructInit(CMP_InitTypeDef* CMP_InitStruct)
{
    memset(CMP_InitStruct, 0, sizeof(CMP_InitTypeDef));
}

/**
 *@brief @b 函数名称:   u8 CMP_GetIRQFlag(u8 CMPx)
 *@brief @b 功能描述:   读取比较器中断
 *@see被调用函数：       无
 *@param输入参数：       CMP0，CMP1即获取CMP0和CMP1中断标志位
 *@param输出参数：       无
 *@return返 回 值：      TIM中断标志0/1
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code    
             if(CMP_GetIRQFlag(CMP1))//获取CMP1中断标志位
              {
                CMP_ClearIRQFlag(CMP1);//清除CMP1中断标志位
              }
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月21日 <td>1.0        <td>Yangzj         <td>创建
 * </table>
 */
u8 CMP_GetIRQFlag(u8 CMPx)
{
	if(CMPx == CMP0)
    {
        if(CMP_IF&BIT0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(CMPx == CMP1)
    {
        if(CMP_IF&BIT1)
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
 *@brief @b 函数名称:   void CMP_ClearIRQFlag(u8 CMPx)
 *@brief @b 功能描述:   清除TIM中断标志
 *@see被调用函数：       无
 *@param输入参数：       CMP0，CMP1即获取CMP0和CMP1中断标志位
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code    
             if(CMP_GetIRQFlag(CMP1))//获取CMP1中断标志位
              {
                CMP_ClearIRQFlag(CMP1);//清除CMP1中断标志位
              }
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月11日 <td>1.0       <td>HuangMG         <td>创建
 * </table>
 */
void CMP_ClearIRQFlag(u8 CMPx)
{
	if(CMPx == CMP0)
    {
        CMP_IF=BIT0;
    }
    else if(CMPx == CMP1)
    {
        CMP_IF=BIT1;
    }
}
