 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_dma.h\n
 * 文件标识： 无 \n
 * 内容摘要： DMA外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年08月1日 <td>1.0     <td>Howlet     <td>创建
 * </table>
 */
#ifndef __LKS32MC08x_DMA_H
#define __LKS32MC08x_DMA_H

#include "lks32mc08x_lib.h"

/** 
 *@brief DMA初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    /** 
     * @brief DMA 中断使能
     * @see DMA_TCIE    
     * @see DMA_TEIE      
     */  
    uint8_t DMA_IRQ_EN;               /**< DMA 中断使能 */
    /** 
     * @brief DMA传输方向
     * @see PERI2MEMORY  外设至内存搬运  
     * @see MEMORY2PERI  内存至外设搬运     
     */   
    uint8_t DMA_DIR;               
    uint8_t DMA_CIRC;                 /**< DMA传输模式：循环模式， ENABLE:使能 ， DISABLE:失能*/
    uint8_t DMA_PINC;                 /**< 外设地址每轮内是否递增,ENABLE:使能 ， DISABLE:失能*/
    uint8_t DMA_MINC;                 /**< 内存地址第二轮是否在第一轮地址的基础上递增, ENABLE:使能 ， DISABLE:失能*/
    /** 
     * @brief 外设访问位宽
     * @see DMA_BYTE_TRANS     
     * @see DMA_HALFWORD_TRANS      
     * @see DMA_WORD_TRANS
     */   
    uint8_t DMA_PBTW;                 /* 外设访问位宽， 0:byte, 1:half-word, 2:word */
    /** 
     * @brief 内存访问位宽
     * @see DMA_BYTE_TRANS     
     * @see DMA_HALFWORD_TRANS      
     * @see DMA_WORD_TRANS
     */   
    uint8_t DMA_MBTW;                 /* 内存访问位宽， 0:byte, 1:half-word, 2:word */
     /** 
     * @brief 通道 x 三个硬件 DMA 请求使能
     * @see DMA_CH0_ADC0_REQ_EN     （DMA通道0使用）  
     * @see DMA_CH0_TIMER0_REQ_EN   （DMA通道0使用）
     * @see DMA_CH0_TIMER1_REQ_EN   （DMA通道0使用） 
     * @see DMA_CH1_SPI_RX_REQ_EN   （DMA通道1使用）
     * @see DMA_CH1_MCPWM_REQ_EN    （DMA通道1使用）
     * @see DMA_CH1_TIMER2_REQ_EN   （DMA通道1使用）
     * @see DMA_CH2_UART0_REQ_EN    （DMA通道2使用）
     * @see DMA_CH2_SPI_TX_REQ_EN   （DMA通道2使用）
     * @see DMA_CH2_TIMER3_REQ_EN   （DMA通道2使用）  
     * @see DMA_CH3_UART1_REQ_EN    （DMA通道3使用） 
     * @see DMA_CH3_CAN_REQ_EN      （DMA通道3使用）
     * @see DMA_CH3_I2C_REQ_EN      （DMA通道3使用） 
     */    
    uint8_t DMA_REQ_EN;            
    uint16_t DMA_TIMES;               /**< DMA 通道 x 每轮数据搬运次数 1~511 */
    uint8_t DMA_ROUND;                /**< DMA 通道 x 采样轮数 1~255 */
    uint32_t DMA_CPAR;                /**< DMA 通道 x 外设地址 */
    uint32_t DMA_CMAR;                /**< DMA 通道 x 内存地址 */

} DMA_InitTypeDef;

/**
 * DAM通道0结构体基地址定义
 */
#ifndef DMA_CH0
#define DMA_CH0             ((DMA_RegTypeDef *) DMA_BASE)
#endif
/**
 * DAM通道1结构体基地址定义
 */
#ifndef DMA_CH1
#define DMA_CH1             ((DMA_RegTypeDef *) (DMA_BASE+0x10))
#endif
/**
 * DAM通道2结构体基地址定义
 */
#ifndef DMA_CH2
#define DMA_CH2             ((DMA_RegTypeDef *) (DMA_BASE+0x20))
#endif
/**
 * DAM通道3结构体基地址定义
 */
#ifndef DMA_CH3
#define DMA_CH3             ((DMA_RegTypeDef *) (DMA_BASE+0x30))
#endif

/** 
 *@brief DMA寄存器结构体句柄
 */
typedef struct
{
    __IO uint32_t DMA_CCR;  /**< DMA 通道配置寄存器*/
    __IO uint32_t DMA_CTMS; /**< DMA 控制寄存器*/
    __IO uint32_t DMA_CPAR; /**< DMA 外设地址寄存器*/
    __IO uint32_t DMA_CMAR; /**< DMA 内存地址寄存器*/
} DMA_RegTypeDef;

#define DMA_TCIE                 BIT0       /**< DMA中断使能定义，传输完成中断使能，高有效 */   
#define DMA_TEIE                 BIT1       /**< DMA中断使能定义，错误中断使能，高有效 */

#define PERI2MEMORY              0          /**< DMA搬运方向定义，外设至内存 */
#define MEMORY2PERI              1          /**< DMA搬运方向定义，内存至外设 */

#define DMA_BYTE_TRANS           0          /**< DMA搬运数据位宽定义，访问位宽， 0:byte */
#define DMA_HALFWORD_TRANS       1          /**< DMA搬运数据位宽定义，访问位宽， 1:half-word */
#define DMA_WORD_TRANS           2          /**< DMA搬运数据位宽定义，访问位宽， 2:word */ 

#define DMA_CH0_ADC0_REQ_EN      BIT0       /**< 触发DMA搬运源定义， Channel_0 ADC0 DMA请求使能 */
#define DMA_CH0_TIMER0_REQ_EN    BIT1       /**< 触发DMA搬运源定义， Channel_0 TIMER0 DMA请求使能 */
#define DMA_CH0_TIMER1_REQ_EN    BIT2       /**< 触发DMA搬运源定义， Channel_0 TIMER1 DMA请求使能 */ 
#define DMA_CH1_SPI_RX_REQ_EN    BIT0       /**< 触发DMA搬运源定义， Channel_1 SPI_RX DMA请求使能 */
#define DMA_CH1_MCPWM_REQ_EN     BIT1       /**< 触发DMA搬运源定义， Channel_1 MCPWM DMA请求使能 */
#define DMA_CH1_TIMER2_REQ_EN    BIT2       /**< 触发DMA搬运源定义， Channel_1 TIMER2 DMA请求使能 */
#define DMA_CH2_UART0_REQ_EN     BIT0       /**< 触发DMA搬运源定义， Channel_2 UART0 DMA请求使能 */
#define DMA_CH2_SPI_TX_REQ_EN    BIT1       /**< 触发DMA搬运源定义， Channel_2 SPI_TX DMA请求使能 */
#define DMA_CH2_TIMER3_REQ_EN    BIT2       /**< 触发DMA搬运源定义， Channel_2 TIMER3 DMA请求使能 */ 
#define DMA_CH3_UART1_REQ_EN     BIT0       /**< 触发DMA搬运源定义， Channel_3 UART1 DMA请求使能 */
#define DMA_CH3_CAN_REQ_EN       BIT1       /**< 触发DMA搬运源定义， Channel_3 SPI_CAN DMA请求使能 */
#define DMA_CH3_I2C_REQ_EN       BIT2       /**< 触发DMA搬运源定义， Channel_3 I2X DMA请求使能 */

#define DMA_CH0_FIF  BIT0    /**< DMA中断标志定义，通道 0 完成中断标志*/
#define DMA_CH1_FIF  BIT1    /**< DMA中断标志定义，通道 1 完成中断标志*/
#define DMA_CH2_FIF	 BIT2    /**< DMA中断标志定义，通道 2 完成中断标志*/
#define DMA_CH3_FIF  BIT3    /**< DMA中断标志定义，通道 3 完成中断标志*/
#define DMA_CH0_EIF  BIT4    /**< DMA中断标志定义，通道 0 错误中断标志*/
#define DMA_CH1_EIF  BIT5    /**< DMA中断标志定义，通道 1 错误中断标志*/
#define DMA_CH2_EIF  BIT6    /**< DMA中断标志定义，通道 2 错误中断标志*/
#define DMA_CH3_EIF  BIT7    /**< DMA中断标志定义，通道 3 错误中断标志*/

void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct);
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct);
uint32_t DMA_GetIRQFlag(DMA_RegTypeDef *DMAx  , u32 timer_if);
void DMA_ClearIRQFlag(DMA_RegTypeDef *DMAx , uint32_t tempFlag);
void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN);
#endif
