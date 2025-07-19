/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_uart.h\n
 * 文件标识： 无 \n
 * 内容摘要： UART驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年05月21日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */


#ifndef __LKS32MC08x_UART_H
#define __LKS32MC08x_UART_H

#include "lks32mc08x_lib.h"

/** 串口奇偶校验配置枚举成员*/ 
typedef enum
{
   UART_Parity_NO = 0x00,  /**<无奇偶校验*/
   UART_Parity_EVEN = 0x01,/**<偶校验*/
   UART_Parity_ODD = 0x02  /**<奇校验*/
} UART_ParityMode;

/** 
 *@brief UART寄存器结构体句柄
 */
typedef struct
{
   __IO uint32_t CTRL; /**<UART控制寄存器*/
   __IO uint32_t DIVH; /**<UART波特率设置高字节寄存器*/
   __IO uint32_t DIVL; /**<UART波特率设置低字节寄存器*/
   __IO uint32_t BUFF; /**<UART收发缓冲寄存器*/
   __IO uint32_t ADR;  /**<485通信地址匹配寄存器*/
   __IO uint32_t STT;  /**<UART状态寄存器*/
   __IO uint32_t IE;   /**<UART中断使能寄存器*/
   __IO uint32_t IF;   /**<UART中断标志寄存器*/
   __IO uint32_t INV;  /**<UART IO翻转使能*/
} UART_TypeDef;

/** 
 *@brief UART初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
   uint32_t BaudRate;          /**<波特率*/
   uint8_t WordLength;         /**<数据长度   @see UART_WORDLENGTH_8b @see UART_WORDLENGTH_7b*/
   uint8_t StopBits;           /**<停止位长度 @see UART_STOPBITS_1b   @see UART_STOPBITS_2b*/
   uint8_t FirstSend;          /**<发送数据大小端设置 @see UART_FIRSTSEND_LSB @see UART_FIRSTSEND_MSB*/
   UART_ParityMode ParityMode; /**<奇偶校验,@see UART_ParityMode*/

   uint8_t MultiDropEna;       /**<使能Multi-drop,0:Disable 1:Enable*/
   uint8_t Bit9Value;          /**<Multi-drop Master模式时,第9个数据位值 改为一般不在初始化内使用*/

   uint16_t Match485Addr;      /**<用作485通信时的匹配地址*/
   /**@brief中断使能寄存器 
    * @see UART_IRQEna_SendOver
    * @see UART_IRQEna_RcvOver
    * @see UART_IRQEna_SendBuffEmpty
    * @see UART_IRQEna_StopError
    * @see UART_IRQEna_CheckError
    */
   uint8_t IRQEna;             
   uint8_t RXD_INV;            /**<接收电平取反 ENABLE取反，DISABLE正常*/
   uint8_t TXD_INV;            /**<发送电平取反 ENABLE取反，DISABLE正常*/
} UART_InitTypeDef;
/**
 * 串口0结构体基地址定义
 */
#ifndef UART0
#define UART0               ((UART_TypeDef *) UART0_BASE)
#endif
/**
 * 串口1结构体基地址定义
 */
#ifndef UART1
#define UART1               ((UART_TypeDef *) UART1_BASE)
#endif

/**
 * 系统时钟（UART使用系统时钟分频）
 */
#ifndef UART_MCU_MCLK
#define UART_MCU_MCLK (96000000LL) 
#endif

#define UART_WORDLENGTH_8b 0  /**<8bit数据位*/
#define UART_WORDLENGTH_7b 1  /**<7bit数据位*/

#define UART_STOPBITS_1b 0    /**<无停止位*/
#define UART_STOPBITS_2b 1    /**<1bit停止位*/

#define UART_FIRSTSEND_LSB 0  /**<低端先发送*/
#define UART_FIRSTSEND_MSB 1  /**<高端先发送*/

/*中断使能定义*/
#define UART_IRQEna_SendOver BIT0      /**<使能发送完成中断*/
#define UART_IRQEna_RcvOver BIT1       /**<使能接收完成中断*/
#define UART_IRQEna_SendBuffEmpty BIT2 /**<使能发送缓冲区空中断*/
#define UART_IRQEna_StopError BIT3     /**<使能停止位错误*/
#define UART_IRQEna_CheckError BIT4    /**<使能校验错误*/

/*DMA请求使能定义*/
#define UART_IRQEna_TX_DMA_RE BIT5     /**<发送完成DMA请求使能*/
#define UART_IRQEna_RX_DMA_RE BIT6     /**<接收完成DMA请求使能*/
#define UART_IRQEna_TX_BUF_DMA_RE BIT7 /**<发送缓冲区空DMA请求使能*/

/* 中断标志定义*/
#define UART_IF_SendOver BIT0     /**<发送完成中断*/
#define UART_IF_RcvOver BIT1      /**<接收完成中断*/
#define UART_IF_SendBufEmpty BIT2 /**<发送缓冲区空中断*/
#define UART_IF_StopError BIT3    /**<停止位错误*/
#define UART_IF_CheckError BIT4   /**<校验错误 */

void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);
void UART_StructInit(UART_InitTypeDef *UART_InitStruct);

void UART_SendData(UART_TypeDef *UARTx, uint32_t n);
uint32_t UART_ReadData(UART_TypeDef *UARTx);

uint8_t UART_SendAddr_485(UART_TypeDef *UARTx, uint8_t n);
uint8_t UART_SendData_485(UART_TypeDef *UARTx, uint8_t n);

uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag);
void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag);



#endif /*__lks32mc08x_UART_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
