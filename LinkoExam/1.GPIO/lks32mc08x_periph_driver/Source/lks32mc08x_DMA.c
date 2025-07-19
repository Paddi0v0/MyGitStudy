/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC08x_dma.c\n
 * 文件标识： 无 \n
 * 内容摘要： DMA外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年8月1日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 *@par 修改日志:增加DMA通道使能函数,读取和清除DAM中断标志位函数
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月13日 <td>1.1     <td>HuangMG   <td>修改
 * </table>
 */

#include "lks32mc08x_dma.h"
#include "string.h"

/*******************************************************************************
 函数名称：    void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
 功能描述：    DMA结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.08.1      V1.0           howlet              创建
 *******************************************************************************/
/**
 *@brief @b 函数名称:   void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
 *@brief @b 功能描述:   DMA结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       DMA_InitTypeDef
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           DMA_InitTypeDef DMA_InitStructure;
		   DMA_StructInit(&DMA_InitStructure); //初始化结构体
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月26日 <td>1.0     <td>Howlet     <td>修改
 * </table>
 */
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
{
    memset(DMAInitStruct, 0, sizeof(DMA_InitTypeDef));
}

/**
 *@brief @b 函数名称:   void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
 *@brief @b 功能描述:   DMA初始化函数
 *@see被引用内容：       无
 *@param输入参数：       ADCx：ADC0 , ADC_InitTypeDef
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code    
			u8 memaddr[25] ={0x11,0x12,0x13};//发送数据缓冲区

			DMA_InitTypeDef DMA_InitStruct;
			DMA_StructInit(&DMA_InitStruct);
			DMA_InitStruct.DMA_IRQ_EN = DMA_TCIE;           // DMA 传输完成中断使能 
			DMA_InitStruct.DMA_DIR = MEMORY2PERI;           // 内存至外设 
			DMA_InitStruct.DMA_CIRC = DISABLE;              // 关闭循环传输模式 
			DMA_InitStruct.DMA_PINC = ENABLE;               // 外设地址每轮内是否递增,高有效 
			DMA_InitStruct.DMA_MINC = ENABLE;               // 内存地址第二轮是否在第一轮地址的基础上递增（轮内地址一定递增）,高有效 
			DMA_InitStruct.DMA_PBTW = DMA_BYTE_TRANS;       // 外设访问位宽， 0:byte, 1:half-word, 2:word 
			DMA_InitStruct.DMA_MBTW = DMA_BYTE_TRANS;       // 内存访问位宽， 0:byte, 1:half-word, 2:word 
			DMA_InitStruct.DMA_REQ_EN = DMA_CH3_CAN_REQ_EN; // CAN DMA请求使能，高有效 
			DMA_InitStruct.DMA_TIMES = 5;                   // DMA 通道 x 每轮数据搬运次数 1~511 
			DMA_InitStruct.DMA_ROUND = 5;                   // DMA 通道 x 采样轮数 1~255 
			DMA_InitStruct.DMA_CPAR = (u32)&CAN_TXRX0;      // DMA 通道 x 外设地址
			DMA_InitStruct.DMA_CMAR = (u32)memaddr;         // DMA 通道 x 内存地址 
			DMA_Init(DMA_CH3, &DMA_InitStruct);
			DMA_CHx_EN(DMA_CH3,ENABLE);                     //使能DMA_CH3通道
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2015年11月26日 <td>1.0     <td>Howlet Li       <td>创建
 * </table>
 *@par 修改日志:去除初始化使能DMA通道，改为DMA_CHx_EN（）函数使能DMA通道
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月13日 <td>1.1       <td>HuangMG        <td>修改
 * </table>
 */
void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
{
    /* 通道配置寄存器 斌值 */
    DMAx->DMA_CCR = 0;
    DMAx->DMA_CTMS = DMAInitStruct->DMA_TIMES | (DMAInitStruct->DMA_ROUND<<16); /* 传输次数寄存器 */
    DMAx->DMA_CPAR = DMAInitStruct->DMA_CPAR;   /* 外设地址寄存器 */
    DMAx->DMA_CMAR = DMAInitStruct->DMA_CMAR;   /* 内存地址寄存器 */
    DMAx->DMA_CCR  =  (DMAInitStruct->DMA_IRQ_EN<<1) | (DMAInitStruct->DMA_DIR<<4) |\
                     (DMAInitStruct->DMA_CIRC<<5) | (DMAInitStruct->DMA_PINC<<6) | (DMAInitStruct->DMA_MINC<<7) |\
                     (DMAInitStruct->DMA_PBTW<<8) | (DMAInitStruct->DMA_MBTW<<10) | (DMAInitStruct->DMA_REQ_EN<<12);

    DMA_CTRL  = 0x0001;  /*enable dma, mcu has higher priorit */
}  

/**
 *@brief @b 函数名称:   void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN)
 *@brief @b 功能描述:   使能DMA通道
 *@see被引用内容：       DMAx可选： DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param输入参数：       DMAx：DMA通道选择 \n 
                        Channel_EN：ENABLE：使能DMA通道，DISABLE：关闭DMA通道使能 \n         
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           DMA_CHx_EN(DMA_CH0,ENABLE);//使能DMA通道0
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月13日 <td>1.1       <td>HuangMG    <td>修改
 * </table>
 */
void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN)
{
   if(Channel_EN)
	 {
	   DMAx->DMA_CCR  |= BIT0;/*使能DMA搬运*/
	 }else{
	   DMAx->DMA_CCR  &= ~BIT0; /*关闭通道使能*/
	 }
}

/**
 *@brief @b 函数名称:   uint32_t DMA_GetIRQFlag(DMA_RegTypeDef *DMAx  , u32 timer_if)
 *@brief @b 功能描述:   获取DMA中断标志
 *@see被引用内容：       DMAx可选： DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param输入参数：       DMAx：DMA通道选择  \n
                        timer_if参数可选： 
 * <table>              <tr><td> 宏定义          <td>说明
                        <tr><th> DMA_CH0_FIF    <td>通道 0 完成中断标志
 *					    <tr><th> DMA_CH1_FIF    <td>通道 1 完成中断标志
 *						<tr><th> DMA_CH2_FIF	<td>通道 2 完成中断标志
 *						<tr><th> DMA_CH3_FIF    <td>通道 3 完成中断标志
 *						<tr><th> DMA_CH0_EIF    <td>通道 0 错误中断标志
 *						<tr><th> DMA_CH1_EIF    <td>通道 1 错误中断标志
 *						<tr><th> DMA_CH2_EIF    <td>通道 2 错误中断标志
 *						<tr><th> DMA_CH3_EIF    <td>通道 3 错误中断标志
 * </table>  
 *@see 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0   
 *@par 示例代码：
 *@code    
           if(DMA_GetIRQFlag(DMA_CH0,DMA_CH0_FIF))//获取DMA通道0完成中断标志
		   {	
		   }
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月13日 <td>1.1       <td>HuangMG    <td>修改
 * </table>
 */
uint32_t DMA_GetIRQFlag(DMA_RegTypeDef *DMAx  , u32 timer_if)
{
	 u8 reg = 0;	 
   if((DMAx->DMA_CCR) & BIT1)/*传输完成中断使能*/
	 {
		  reg = timer_if & 0x0f;
	    if(DMA_IF & reg)
			{
			  return 1;
			}
	 }
   if((DMAx->DMA_CCR) & BIT2)/*错误中断使能*/
	 {
		  reg = timer_if & 0xf0;
	    if(DMA_IF & reg)
			{
			  return 1;
			}
	 }
	 return 0;
}

/**
 *@brief @b 函数名称:   void DMA_ClearIRQFlag(DMA_RegTypeDef *DMAx , uint32_t tempFlag)
 *@brief @b 功能描述:   清除DMA中断标志
 *@see 被引用内容：      DMAx可选： DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param 输入参数：      DMAx：DMA通道选择  \n 
                        timer_if参数可选： 
 * <table>              <tr><td> 宏定义          <td>说明
                        <tr><th> DMA_CH0_FIF    <td>通道 0 完成中断标志
 *					    <tr><th> DMA_CH1_FIF    <td>通道 1 完成中断标志
 *						<tr><th> DMA_CH2_FIF	<td>通道 2 完成中断标志
 *						<tr><th> DMA_CH3_FIF    <td>通道 3 完成中断标志
 *						<tr><th> DMA_CH0_EIF    <td>通道 0 错误中断标志
 *						<tr><th> DMA_CH1_EIF    <td>通道 1 错误中断标志
 *						<tr><th> DMA_CH2_EIF    <td>通道 2 错误中断标志
 *						<tr><th> DMA_CH3_EIF    <td>通道 3 错误中断标志
 * </table>   
 * 
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
           if(DMA_GetIRQFlag(DMA_CH0,DMA_CH0_FIF))//获取DMA通道0完成中断标志
		   {	
			  DMA_ClearIRQFlag(DMA_CH0,DMA_CH0_FIF)//清除DMA通道0完成中断标志
		   }
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2022年4月13日   <td>1.1      <td>HuangMG      <td>修改
 * </table>
 */
void DMA_ClearIRQFlag(DMA_RegTypeDef *DMAx , uint32_t tempFlag)
{
    DMA_IF = tempFlag;
}
