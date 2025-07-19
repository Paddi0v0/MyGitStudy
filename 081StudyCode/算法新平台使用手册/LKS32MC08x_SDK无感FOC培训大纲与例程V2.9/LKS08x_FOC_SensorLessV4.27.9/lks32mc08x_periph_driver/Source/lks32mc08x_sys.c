/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_sys.c\n
 * 文件标识： 无 \n
 * 内容摘要： SYS外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年05月21日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */


#include "lks32mc08x_sys.h"

/**
 * @brief 低功耗初始化结构体定义
 * 
 */
WAKE_InitTypeDef WAKE_InitStruct;

/**
 *@brief @b 函数名称:   void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b 功能描述:   SYS模块初始化函数
 *@see被调用函数：      无
 *@param输入参数：      SYS_InitTypeDef* SYS_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       一般不使用该函数，因为涉及模块较多，比较杂乱，对应里面的配置在各模块
 *                     初始化单独配置。
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
           SYS_InitStruct.PLL_SrcSel = SYS_PLLSRSEL_RCH;    // 使用内部4MHz晶振作为时钟输入源
           SYS_Init(&SYS_InitStruct);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年07月02日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
void SYS_Init(SYS_InitTypeDef *SYS_InitStruct)
{
    uint32_t RCHPd, XTALPdn;
    uint32_t tmp1, tmp2;
    SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
    tmp1 = SYS_AFE_REG6;
    tmp1 &= 0x7FFF;
    tmp1 |= (SYS_InitStruct->PLL_SrcSel << 15);
    SYS_AFE_REG6 = tmp1;

    if (SYS_InitStruct->PLL_SrcSel == SYS_PLLSRSEL_CRYSTAL)
    {
        RCHPd = ENABLE;   /*RCH(4MHz)时钟关闭*/
        XTALPdn = ENABLE; /*晶体起振电路开启*/
    }
    else 
    {
        RCHPd = DISABLE;   /*RCH(4MHz)时钟不关闭*/
        XTALPdn = DISABLE; /*晶体起振电路不开启*/
    }

    tmp2 = SYS_AFE_REG5;
    tmp2 &= 0xBBFF;
    tmp2 |= (RCHPd << 10);
    tmp2 |= (XTALPdn << 14);
    SYS_AFE_REG5 = tmp2;

    SYS_CLK_CFG = SYS_InitStruct->PLL_DivSel + (SYS_InitStruct->PLL_ReDiv << 8);
    SYS_RST_CFG = SYS_InitStruct->WDT_Ena | (SYS_InitStruct->PORFilter_Ena << 1);

    SYS_CLK_DIV0 = SYS_InitStruct->Clk_DivSPI;
    SYS_CLK_DIV2 = SYS_InitStruct->Clk_DivUART;
    SYS_CLK_FEN = SYS_InitStruct->Clk_FEN;
    SYS_WR_PROTECT = 0x0;
}


/**
 *@brief @b 函数名称:   void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b 功能描述:   SYS结构体初始化
 *@see被调用函数：      无
 *@param输入参数：      SYS_InitTypeDef* SYS_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无   
 *@par 示例代码：
 *@code    
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年07月02日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
void SYS_StructInit(SYS_InitTypeDef *SYS_InitStruct)
{
    SYS_InitStruct->PLL_SrcSel = SYS_PLLSRSEL_RCH;
    SYS_InitStruct->PLL_DivSel = 0xFF;
    SYS_InitStruct->PLL_ReDiv = SYS_PLLREDIV_1;

    SYS_InitStruct->Clk_DivSPI = SYS_Clk_SPIDiv1;
    SYS_InitStruct->Clk_DivUART = SYS_Clk_UARTDiv1;
    SYS_InitStruct->Clk_FEN = 0;

    SYS_InitStruct->WDT_Ena = DISABLE;
    SYS_InitStruct->PORFilter_Ena = DISABLE;
}

/**
 *@brief @b 函数名称:   void SYS_ClearRst(void)
 *@brief @b 功能描述:   SYS清除复位标志记录
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       请注意由于复位记录工作于低速时钟域，清除执行完成需要一定时间，不应清
                       除后立即读记录状态 
 *@warning             无
 *@par 示例代码：
 *@code    
           u32 RSET_VALUE = 0;
           SYS_ClearRst();//清除复位标志记录
           delay_ms(1);
           RSET_VALUE = SYS_GetRstSource();//读取复位源记录值
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年07月02日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
void SYS_ClearRst(void)
{
	  SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
      SYS_CLR_RST = 0xDEAD;
	  SYS_WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:   uint32_t SYS_GetRstSource(void)
 *@brief @b 功能描述:   获得SYS复位源信号
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     复位源记录值
 *@note其它说明：       返回值位介绍  
 *@warning             无     
 * <table>
 *                     <tr><th>BIT3 <td>看门狗复位发生标志<td> 高有效
 *                     <tr><th>BIT2 <td>按键复位发生标志  <td> 高有效
 *                     <tr><th>BIT1 <td>HPOR 复位发生标志 <td> 高有效
 *                     <tr><th>BIT0 <td>LPOR 复位发生标志 <td> 高有效
 * </table>
 *@par 示例代码：
 *@code    
           u32 RSET_VALUE = 0;
           RSET_VALUE = SYS_GetRstSource();//读取复位源记录值
           如 RSET_VALUE = 0x01;则LPOR发生复位
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年07月02日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
uint32_t SYS_GetRstSource(void)
{
    return SYS_RST_SRC;
}

/**
 *@brief @b 函数名称:   void SYS_FallSleep(void)
 *@brief @b 功能描述:   触发系统进入休眠状态
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无  
 *@warning             无     
 *@par 示例代码：
 *@code    
           SYS_FallSleep();//触发系统进入休眠状态
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年07月02日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
void SYS_FallSleep(void)
{
    SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
    SYS_CLK_SLP = 0xDEAD;
    SYS_WR_PROTECT = 0x0;
    __WFI(); /*PC指针停止运行，等待中断*/
}

/**
 *@brief @b 函数名称:    void SYS_SetWakeInterval(uint32_t nInterval)
 *@brief @b 功能描述:    设置系统休眠唤醒周期
 *@see被调用函数：       无
 *@param输入参数：       nInterval：唤醒时间
 * <table>
 *                      <tr><td> 宏定义         <td>原始值    <td>说明
 *                      <tr><th>SYS_WakeInterval_025s  <td>0x00     <td>0.25s  
 *                      <tr><th>SYS_WakeInterval_05s   <td>0x01     <td>0.5s
 *                      <tr><th>SYS_WakeInterval_1s    <td>0x02     <td>1s
 *                      <tr><th>SYS_WakeInterval_2s    <td>0x03     <td>2s
 *                      <tr><th>SYS_WakeInterval_4s    <td>0x04     <td>4s
 *                      <tr><th>SYS_WakeInterval_8s    <td>0x05     <td>8s
 *                      <tr><th>SYS_WakeInterval_16s   <td>0x06     <td>16s
 *                      <tr><th>SYS_WakeInterval_32s   <td>0x07     <td>32s
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无   
 *@warning             无    
 *@par 示例代码：
 *@code    
           SYS_SetWakeInterval(SYS_WakeInterval_1s);//系统休眠时,设置系统在1s后唤醒
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年07月02日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
void SYS_SetWakeInterval(uint32_t nInterval)
{
    uint32_t tempReg = SYS_RST_CFG;
	SYS_WR_PROTECT = 0x7a83;        /*开启寄存器写使能*/
    tempReg |= (nInterval << 2);
    SYS_RST_CFG = tempReg;
	SYS_WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:    void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint8_t ena)
 *@brief @b 功能描述:    设置休眠唤醒IO
 *@see唤醒电平选择枚举：  enumWakeTrigLevel 
 *@param输入参数：                           
 * <table>              <tr><td>wakeIO = WAKEIO_P1_1: P1.1 外部唤醒使能。1：使能；0：禁用 \n
 *                              wakeIO = WAKEIO_P1_0: P1.0 外部唤醒使能。1：使能；0：禁用 \n
 *                              wakeIO = WAKEIO_P0_1: P0.1 外部唤醒使能。1：使能；0：禁用 \n
 *                              wakeIO = WAKEIO_P0_0: P0.0 外部唤醒使能。1：使能；0：禁用 
 *                      <tr><td>enumWakeTrigLevel : \n
 *                              唤醒电平选择：\n 
 *                              0:低电平唤醒 \n
 *                              1:高电平唤醒 
 *                      <tr><td>ena: \n
 *                              ENABLE： 开启IO唤醒\n
 *                              DISABLE：关闭IO唤醒\n
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无    
 *@warning             无 
 *@par 示例代码：
 *@code    
           SetWakeIO(WAKEIO_P0_0,WAKETRIG_LOW,ENABLE);//系统休眠时,使能P0.0作为低功耗唤醒IO，
           低电平唤醒
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月14日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint8_t ena)
{
    if (ena == ENABLE)
    {
        GPIO_WAKE_EN |= wakeIO;
    }
    else
    {
        GPIO_WAKE_EN &= ~wakeIO;
    }

    if (trigLevel == WAKETRIG_HIGH)
    {
        GPIO_WAKE_POL |= wakeIO;
    }
    else
    {
        GPIO_WAKE_POL &= ~wakeIO;
    }
}
/**
 *@brief @b 函数名称:   static void SoftDelay(u32 cnt)
 *@brief @b 功能描述:   延时函数
 *@see被调用函数：      无
 *@param输入参数：      cnt：延时cnt的空指令_NOP()
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       改函数只在此文件使用，主要用在Switch2PLL函数内      
 *@warning             无
 *@par 示例代码：
 *@code    
           SoftDelay(0xff);//延时255个_NOP()时间1个_NOP大约按一个系统时钟周期计算
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月14日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
static void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;
    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

/**
 *@brief @b 函数名称:   void Switch2PLL(void)
 *@brief @b 功能描述:   休眠唤醒后，系统时钟切换到PLL时钟函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       系统低功耗唤醒使用  
 *@warning             无 
 *@par 示例代码：
 *@code    
           Switch2PLL();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月14日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void Switch2PLL(void)
{
    SYS_WR_PROTECT = 0x7a83;        /*开启寄存器写使能*/
    SYS_AFE_REG5 = WAKE_InitStruct.AFE_REG5_RECORD; /*开启 PLL,HRC,BGP*/
    SoftDelay(200);
    SYS_AFE_REG6 = WAKE_InitStruct.AFE_REG6_RECORD; /*开启掉电检测电路*/
    SYS_CLK_CFG = WAKE_InitStruct.CLK_CFG_RECORD;   /*将主时钟切换到PLL时钟*/
    SYS_WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:   void Switch2HRC(void)
 *@brief @b 功能描述:   休眠唤醒前一时刻，关闭高速时钟与BGP和掉电检测电路函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       系统低功耗休眠使用   
 *@warning             无
 *@par 示例代码：
 *@code    
           Switch2HRC();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月14日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void Switch2HRC(void)
{
    SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
    WAKE_InitStruct.AFE_REG5_RECORD = SYS_AFE_REG5;
    WAKE_InitStruct.AFE_REG6_RECORD = SYS_AFE_REG6;
    WAKE_InitStruct.CLK_CFG_RECORD = SYS_CLK_CFG;
    SYS_CLK_CFG = 0;       /* 切换到HRC时钟*/
    SYS_AFE_REG5 = 0x0500; /* 准备关闭 PLL,HRC,BGP*/
    SYS_AFE_REG6 |= 1;     /* 关闭掉电检测电路*/
    SYS_WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:   void SYS_WatchDogCmd(FuncState state)
 *@brief @b 功能描述:   看门狗模块使能函数
 *@see被调用函数：      无
 *@param输入参数：      state：ENABLE使能看门狗/DISABLE关闭开门狗
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无   
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_WatchDogCmd(ENABLE);//使能看门狗模块
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu         <td>创建
 * </table>
 */
void SYS_WatchDogCmd(FuncState state)
{
    SYS_WR_PROTECT = 0x7A83; //解除写保护

    if (state == ENABLE)
    {
        SYS_RST_CFG |= BIT0; //使能看门狗
    }
    else
    {
        SYS_RST_CFG &= (~BIT0); //关闭看门狗
    }
		SYS_WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:   void SYS_EnablePORFilter(void)
 *@brief @b 功能描述:   允许对POR进行滤波处理
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             @b 该函数目前不开放，请不要使用
 *@par 示例代码：
 *@code    
         SYS_EnablePORFilter();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu         <td>创建
 * </table>
 */
void SYS_EnablePORFilter(void)
{  
    uint32_t tempReg = SYS_RST_CFG;
	SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护
    tempReg |= BIT1;
    SYS_RST_CFG = tempReg;
    SYS_WR_PROTECT = 0x0;      /*关闭系统寄存器写操作*/
}

/**
 *@brief @b 函数名称:   void SYS_FeedDog(uint32_t timeOut)
 *@brief @b 功能描述:   喂狗
 *@see被调用函数：      无
 *@param输入参数：      timeOut：看门狗超时时间
 * <table> 
 *                     <tr><th>SYS_WD_TimeOut2s  <td>0    <td>2s复位
 *                     <tr><th>SYS_WD_TimeOut4s  <td>1    <td>4s复位
 *                     <tr><th>SYS_WD_TimeOut8s  <td>2    <td>8s复位
 *                     <tr><th>SYS_WD_TimeOut64s <td>3    <td>64s复位
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
        SYS_FeedDog(SYS_WD_TimeOut2s);//看门狗喂狗且设置下一次如果2s不喂狗则芯片复位
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu         <td>创建
 * </table>
 */
void SYS_FeedDog(uint32_t timeOut)
{
    SYS_WR_PROTECT = 0xCAFE; // 0xCAFE;

    if (timeOut == (uint32_t)SYS_WD_TimeOut64s)
    {
        SYS_WDT_CLR = 0x7989; // 1 00 1
    }
    else if (timeOut == (uint32_t)SYS_WD_TimeOut8s)
    {
        SYS_WDT_CLR = 0x798B; // 1 01 1
    }
    else if (timeOut == (uint32_t)SYS_WD_TimeOut4s)
    {
        SYS_WDT_CLR = 0x798D; // 1 10 1
    }
    else // SYS_WD_TimeOut2s
    {
        SYS_WDT_CLR = 0x798F; // 1 11 1
    }

    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b 函数名称:   void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b 功能描述:   数字模块时钟使能和停止
 *@see被调用枚举：      FuncState
 *@param输入参数：   
 *                     state： ENABLE使能 , DISABLE关闭     
 *                     nModule：参数可选： \n 
 * <table> 
 *                     <tr><td> 宏定义                   <td>原始值   <td>说明
 *                     <tr><th> SYS_Module_I2C          <td> BIT0    <td>I2C模块
 *                     <tr><th> SYS_Module_HALL         <td> BIT1    <td>HALL模块
 *                     <tr><th> SYS_Module_TIMER        <td> BIT2    <td>UTIMER模块
 *                     <tr><th> SYS_Module_MCPWM        <td> BIT3    <td>MCPWM模块
 *                     <tr><th> SYS_Module_UART0        <td> BIT4    <td>UART0模块
 *                     <tr><th> SYS_Module_UART1        <td> BIT5    <td>UART1模块
 *                     <tr><th> SYS_Module_DSP          <td> BIT6    <td>DSP模块
 *                     <tr><th> SYS_Module_CAN          <td> BIT7    <td>CAN模块
 *                     <tr><th> SYS_Module_SPI          <td> BIT8    <td>SPI模块                  
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
        SYS_ModuleClockCmd(SYS_Module_SPI,ENABLE);//使能SPI时钟
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu         <td>创建
 * </table>
 */
void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护

    if (state != DISABLE)
    {
        SYS_CLK_FEN |= nModule;
    }
    else
    {
        SYS_CLK_FEN &= ~nModule;
    }
		
	  SYS_WR_PROTECT = 0x0;      /*关闭系统寄存器写操作*/
}

/**
 *@brief @b 函数名称:   void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b 功能描述:   模拟模块使能和停止
 *@see被调用枚举：      FuncState
 *@param输入参数：      
 *                     state： ENABLE使能 , DISABLE关闭  
 *                     nModule：参数可选： \n 
 * <table> 
 *                     <tr><td> 宏定义                  <td>说明
 *                     <tr><th> SYS_AnalogModule_ADC    <td>  BIT0  <td> ADC模块  
 *                     <tr><th> SYS_AnalogModule_OPA0   <td>  BIT2  <td> OPA0模块 
 *                     <tr><th> SYS_AnalogModule_OPA1   <td> BIT3   <td> OPA1模块 
 *                     <tr><th> SYS_AnalogModule_OPA2   <td>  BIT4  <td> OPA2模块 
 *                     <tr><th> SYS_AnalogModule_OPA3   <td>  BIT5  <td> OPA3模块
 *                     <tr><th> SYS_AnalogModule_CMP0   <td>  BIT6  <td> CMP0模块 
 *                     <tr><th> SYS_AnalogModule_CMP1   <td>  BIT7  <td> CMP1模块 
 *                     <tr><th> SYS_AnalogModule_BGP    <td>  BIT8  <td> BGP模块  
 *                     <tr><th> SYS_AnalogModule_RCH    <td>  BIT10 <td> RCH模块  
 *                     <tr><th> SYS_AnalogModule_DAC    <td>  BIT12 <td> DAC模块  
 *                     <tr><th> SYS_AnalogModule_TMP    <td>  BIT13 <td> 温度传感器 
 *                     <tr><th> SYS_AnalogModule_XTAL   <td>  BIT14 <td> 晶振 
 *                     <tr><th> SYS_AnalogModule_PLL    <td>  BIT15 <td> PLL模块                 
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
        SYS_AnalogModuleClockCmd(SYS_AnalogModule_PLL,ENABLE);//使能PLL模块
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu         <td>创建
 * </table>
 */
void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护

    if (state != DISABLE)
    {
        SYS_AFE_REG5 |= nModule;
    }
    else
    {
        SYS_AFE_REG5 &= ~nModule;
    }
		SYS_WR_PROTECT = 0x0;      /*关闭系统寄存器写操作*/
}

/**
 *@brief @b 函数名称:   void SYS_SoftResetModule(uint32_t nModule)
 *@brief @b 功能描述:   数字模块软复位
 *@see被调用枚举：      无
 *@param输入参数：   
 *                     state： ENABLE使能 , DISABLE关闭     
 *                     nModule：参数可选： \n 
 * <table> 
 *                     <tr><td> 宏定义                   <td>原始值   <td>说明
 *                     <tr><th> SYS_Module_I2C          <td> BIT0    <td>I2C模块
 *                     <tr><th> SYS_Module_HALL         <td> BIT1    <td>HALL模块
 *                     <tr><th> SYS_Module_TIMER        <td> BIT2    <td>UTIMER模块
 *                     <tr><th> SYS_Module_MCPWM        <td> BIT3    <td>MCPWM模块
 *                     <tr><th> SYS_Module_UART0        <td> BIT4    <td>UART0模块
 *                     <tr><th> SYS_Module_UART1        <td> BIT5    <td>UART1模块
 *                     <tr><th> SYS_Module_DSP          <td> BIT6    <td>DSP模块
 *                     <tr><th> SYS_Module_CAN          <td> BIT7    <td>CAN模块
 *                     <tr><th> SYS_Module_SPI          <td> BIT8    <td>SPI模块              
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
        //软复位SPI模块，清除SPI寄存器配置，PC指针复位
        SYS_SoftResetModule(SYS_Module_SPI);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu         <td>创建
 * </table>
*@par 修改日志:增加延时函数，等待寄存器复位完毕与释放复位操作。
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月14日 <td>1.1     <td>HuangMG      <td>修改
 * </table>
 */
void SYS_SoftResetModule(uint32_t nModule)
{
    SYS_WR_PROTECT = 0x7A83;
    SYS_SFT_RST = nModule;     /*模块复位*/
    SYS_SFT_RST &= ~nModule;   /*释放复位操作*/
	SYS_WR_PROTECT = 0x0;      /*关闭系统寄存器写操作*/
}

/**
 *@brief @b 函数名称:   void DSP_Init(void)
 *@brief @b 功能描述:   DSP时钟使能
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
         DSP_Init();//DSP时钟使能
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu         <td>创建
 * </table>
 */
void DSP_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_DSP, ENABLE); /* DSP时钟使能*/
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
