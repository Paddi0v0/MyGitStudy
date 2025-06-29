/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_gpio.c\n
 * 文件标识： 无 \n
 * 内容摘要： GPIO外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年6月19日 <td>1.0     <td>cfwu       <td>创建
 * </table>
 */


#include "lks32mc08x_gpio.h"


/**
 *@brief @b 函数名称:   void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
 *@brief @b 功能描述:   GPIO初始化函数
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_InitStruct: GPIO初始化结构体
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			GPIO_InitTypeDef GPIO_InitStruct;
            //P2.11输入模式
            GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
            GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIO2, &GPIO_InitStruct);
            //P0.2输出模式    
            GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
            GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIO0, &GPIO_InitStruct);
            //P3.2开漏输出     
            GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
            GPIO_InitStruct.GPIO_PODEna = ENABLE;      //使能开漏模式
            GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//关闭上拉，配置为高阻态
            GPIO_Init(GPIO3, &GPIO_InitStruct);
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0        <td>cfwu         <td>创建
 * </table>
 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00, tempreg = 0x00;

    /*-------------------------- Configure the port pins -----------------------*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
        if (currentpin == pos)
        {
            if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
            {
                tempreg = GPIOx->PIE;    /*使能输入*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE;    /*禁止输出*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
            {
                tempreg = GPIOx->PIE;    /*禁止输入*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE;    /*使能输出*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_ANA)
            {
							  tempreg = GPIOx->PIE;    /*禁止输入*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PIE = tempreg;
							  
                tempreg = GPIOx->POE;    /*禁止输出*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }

            if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_UP)
            {
                tempreg = GPIOx->PUE;
                tempreg |= (BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_NOPULL)
            {
                tempreg = GPIOx->PUE;
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }

            tempreg = GPIOx->PODE;
            if(GPIO_InitStruct->GPIO_PODEna == (uint32_t)ENABLE)
            {
                tempreg |= (BIT0 << pinpos);
            }
            else
            {
                tempreg &= ~(BIT0 << pinpos);
            }
            GPIOx->PODE = tempreg;
        }
    }
}

/**
 *@brief @b 函数名称:   void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
 *@brief @b 功能描述:   GPIO结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIO_InitStruct: GPIO初始化结构体
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			GPIO_InitTypeDef GPIO_InitStruct;
            GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_NONE;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct->GPIO_PODEna = DISABLE;
}


/**
 *@brief @b 函数名称:   uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   读取GPIO的指定Pin的输入值
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     指定Pin输入数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_IN_VALUE = 0;
            GPIO_IN_VALUE = GPIO_ReadInputDataBit(GPIO0,GPIO_Pin_0);//读取P0.0输入电平 1为高电平，0为低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;
    if ((GPIOx->PDI & GPIO_Pin) != 0)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 *@brief @b 函数名称:   uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
 *@brief @b 功能描述:   读取GPIO的输入数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3）
 *@param输出参数：      无
 *@return返 回 值：     输入数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_IN_VALUE = 0;
            GPIO_IN_VALUE = GPIO_ReadInputData(GPIO0);//读取P0.0~P0.15输入电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    return GPIOx->PDI;
}


/**
 *@brief @b 函数名称:   uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   读取GPIO的指定Pin的输出值
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_Pin:指定的Pin（GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     指定IO输出数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_OUT_VALUE = 0;
            GPIO_OUT_VALUE = GPIO_ReadOutputDataBit(GPIO0,GPIO_Pin_0);//读取P0.0输出电平 1为高电平，0为低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;
    if ((GPIOx->PDO & GPIO_Pin) != 0)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 *@brief @b 函数名称:   uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
 *@brief @b 功能描述:   读取GPIO的输出数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3）
 *@param输出参数：      无
 *@return返 回 值：     输出数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_OUT_VALUE = 0;
            GPIO_OUT_VALUE = GPIO_ReadOutputData(GPIO0);//读取P0.0~P0.15输出电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    return GPIOx->PDO;
}


/**
 *@brief @b 函数名称:   void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   GPIO指定Pin置1
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_SetBits(GPIO0,GPIO_Pin_0);//P0.0输出高电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);
}

/**
 *@brief @b 函数名称:   void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   GPIO指定Pin置1
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_ResetBits(GPIO0,GPIO_Pin_0);//P0.0输出低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);
}

/**
 *@brief @b 函数名称:   void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
 *@brief @b 功能描述:   向GPIO指定的Pin写入数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15） \n
                        BitVal:写入的Bit值 （Bit_RESET 或 Bit_SET）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_WriteBit(GPIO0,GPIO_Pin_0,Bit_RESET);//P0.0输出低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    if (BitVal != Bit_RESET)
    {
        GPIOx->PDO |= GPIO_Pin;
    }
    else
    {
        GPIOx->PDO &= ~GPIO_Pin;
    }
}

/**
 *@brief @b 函数名称:   void GPIO_Write(GPIO_TypeDef* GPIOx, uint32_t Val)
 *@brief @b 功能描述:   向GPIO写入数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        BitVal:写入的Bit值 （0x00~0xffff）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_WriteBit(GPIO0,0x01);//P0.0置1,输出高电平，P0.1~P0.15值不变保持上一时刻状态
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint32_t Val)
{
    GPIOx->PDO |= Val;
}

/**
 *@brief @b 函数名称:   void GPIO_LockRegister(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
 *@brief @b 功能描述:   GPIO寄存器保护锁定
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       上锁后GPIO输入/输出/上下拉/开漏/功能选择不能被修改
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_LockRegister(GPIO0,GPIO_Pin_0);//P0.0上锁
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_LockRegister(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    LCKR_PRT = 0x5AC4;       /* 关闭写保护 */
	
    GPIOx->LCKR |= GPIO_Pin; /* 锁定GPIOx_Pin配置 */
	
	LCKR_PRT = 0xFFFF;       /* 开启写保护 */
}

/**
 *@brief @b 函数名称:   void GPIO_UnlockRegister(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
 *@brief @b 功能描述:   GPIO寄存器保护解锁
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       解锁后GPIO输入/输出/上下拉/开漏/功能选择可以被修改
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_UnlockRegister(GPIO0,GPIO_Pin_0);//P0.0解锁
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_UnlockRegister(GPIO_TypeDef* GPIOx ,uint16_t GPIO_Pin)
{
	  LCKR_PRT = 0x5AC4;       /* 关闭写保护 */
	
      GPIOx->LCKR &= (~GPIO_Pin); /* 解锁GPIOx_Pin配置 */
	
	  LCKR_PRT = 0xFFFF;       /* 开启写保护 */
}

/**
 *@brief @b 函数名称:   void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF)
 *@brief @b 功能描述:   GPIO复用功能选择
 *@see被引用内容：       无
 *@param输入参数：       
 *                      GPIOx:GPIO对象,参数可选（GPIO0~GPIO3） \n
 *                      GPIO_PadSource:指定的PadSource （GPIO_PinSource_0~GPIO_PinSource_15） \n
 *                      GPIO_AF:指定复用功能 \n
 * 
 * <table>              <tr><td>复用功能名称    <td> 说明                  
 * 						<tr><th>AF0_GPIO                 <td>模拟功能
 * 						<tr><th>AF1_SYSAF                <td>SYS_AF、CMP、CLOCK等数字信号输出功能 
 * 						<tr><th>AF2_HALL                 <td>HALL功能 
 * 						<tr><th>AF3_MCPWM                <td>MCPWM功能
 * 						<tr><th>AF4_UART                 <td>UART功能 
 * 						<tr><th>AF5_SPI                  <td>SPI功能
 * 						<tr><th>AF6_I2C                  <td>I2C功能
 * 						<tr><th>AF7_TIMER01              <td>Timer0、Timer1功能 
 * 						<tr><th>AF8_TIMER23              <td>Timer2、Timer3、QEP0、QEP1功能 
 * 						<tr><th>AF9_DEBUG                <td>ADC trigger debug功能 
 * 						<tr><th>AF10_CAN                 <td>CAN功能 
 * 						<tr><th>AF11_SIF                 <td>SIF功能   
 * </table>                         
 *              
 *@param 输出参数：      无
 *@return 返 回 值：     无
 *@note 其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code    
            GPIO_PinAFConfig(GPIO1,GPIO_Pin_0，AF4_UART);//P1.0复用为串口功能
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年4月18日  <td>1.0       <td>cfwu          <td>创建
 * </table>
 */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF)
{
    uint32_t temp;
    switch(GPIO_PinSource)
    {
    /*F3210*/
    case 0:
    {
        temp = GPIOx->F3210 & 0xFFF0;  /*get F321*/
        GPIOx->F3210 = temp + GPIO_AF; /*F321 + F0*/
        break;
    }
    case 1:
    {
        temp = GPIOx->F3210 & 0xFF0F;
        GPIOx->F3210 = temp + (GPIO_AF << 4);
        break;
    }
    case 2:
    {/* 2020.8.13 Repair bug HL */
        temp = GPIOx->F3210 & 0xF0FF;
        GPIOx->F3210 = temp + (GPIO_AF << 8);
        break;
    }
    case 3:
    {
        temp = GPIOx->F3210 & 0x0FFF;
        GPIOx->F3210 = temp + (GPIO_AF << 12);
        break;
    }
    /*F7654*/
    case 4:
    {
        temp = GPIOx->F7654 & 0xFFF0;
        GPIOx->F7654 = temp + GPIO_AF;
        break;
    }
    case 5:
    {
        temp = GPIOx->F7654 & 0xFF0F;
        GPIOx->F7654 = temp + (GPIO_AF << 4);
        break;
    }
    case 6:
    {
        temp = GPIOx->F7654 & 0xF0FF;
        GPIOx->F7654 = temp + (GPIO_AF << 8);
        break;
    }
    case 7:
    {
        temp = GPIOx->F7654 & 0x0FFF;
        GPIOx->F7654 = temp + (GPIO_AF << 12);
        break;
    }
    /*FBA98*/
    case 8:
    {
        temp = GPIOx->FBA98 & 0xFFF0;
        GPIOx->FBA98 = temp + GPIO_AF;
        break;
    }
    case 9:
    {
        temp = GPIOx->FBA98 & 0xFF0F;
        GPIOx->FBA98 = temp + (GPIO_AF << 4);
        break;
    }
    case 10:
    {
        temp = GPIOx->FBA98 & 0xF0FF;
        GPIOx->FBA98 = temp + (GPIO_AF << 8);
        break;
    }
    case 11:
    {
        temp = GPIOx->FBA98 & 0x0FFF;
        GPIOx->FBA98 = temp + (GPIO_AF << 12);
        break;
    }
    /*FFEDC*/
    case 12:
    {
        temp = GPIOx->FFEDC & 0xFFF0;
        GPIOx->FFEDC = temp + GPIO_AF;
        break;
    }
    case 13:
    {
        temp = GPIOx->FFEDC & 0xFF0F;
        GPIOx->FFEDC = temp + (GPIO_AF << 4);
        break;
    }
    case 14:
    {
        temp = GPIOx->FFEDC & 0xF0FF;
        GPIOx->FFEDC = temp + (GPIO_AF << 8);
        break;
    }
    case 15:
    {
        temp = GPIOx->FFEDC & 0x0FFF;
        GPIOx->FFEDC = temp + (GPIO_AF << 12);
        break;
    }
    default:
        break;
    }
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
