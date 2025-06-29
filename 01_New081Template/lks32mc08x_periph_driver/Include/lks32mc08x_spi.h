 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_spi.h\n
 * 文件标识： 无 \n
 * 内容摘要： SPI驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年05月21日 <td>1.0     <td>cfwu       <td>创建
 * </table>
 */
#ifndef __LKS32MC08x_SPI_H
#define __LKS32MC08x_SPI_H


#include "lks32mc08x_lib.h"

 /** 
 *@brief SPI模式配置枚举
 */
typedef enum
{
   SPI_Master = 0x01, /**< SPI主模式 */
   SPI_Slave  = 0x00  /**< SPI从模式 */
}SPI_Mode;

 /** 
 *@brief SPI工作模式配置枚举
 */
typedef enum
{
   SPI_Full    = 0x0,  /**< SPI全双工 */
	SPI_Half_Tx = 0x2, /**< SPI半双工仅发送 */
   SPI_Half_Rx = 0x3   /**< SPI半双工仅接收 */
}SPI_Duplex;

/** 
 *@brief SPI寄存器结构体句柄
 */
typedef struct
{
   __IO uint32_t CFG;      /**< SPI控制寄存器 */
   __IO uint32_t IE;       /**< SPI中断寄存器 */
   __IO uint32_t DIV;      /**< SPI波特率控制寄存器 */
	__IO uint32_t TX_DATA;  /**< SPI发送数据寄存器 */
   __IO uint32_t RX_DATA;  /**< SPI接收数据寄存器 */
   __IO uint32_t SIZE;     /**< SPI传输数据长度寄存器 */
}SPI_TypeDef;

 /**
 * SPI结构体基地址定义
 */
#ifndef   SPI
#define   SPI      ((SPI_TypeDef *) SPI0_BASE)
#endif

 /** 
 *@brief SPI初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    /** 
     * @brief 全双工、半双工工作模式选择：0，全双工；2，半双工仅发送；3，半双工仅接收  \n
     * @see SPI_Duplex     
     */ 
	SPI_Duplex Duplex;   
   uint8_t    SS;        /**< 从设备下片选信号来源：0，恒为0；1，来源于主设备 */
    /** 
     * @brief 主从模式选择：0，从模式；1，主模式  \n
     * @see SPI_Mode     
     */    
   SPI_Mode   Mode;   
   uint8_t    CPHA;      /**<  相位选择：0对应0；1对应1 */
   uint8_t    CPOL;      /**<  极性选择：0对应0；1对应1 */
   uint8_t    DataOrder; /**<  传输顺序：0，高位先传；1，低位先传 */
   uint8_t    EN;        /**<  SPI模块使能：0，关闭；1，开启 */
    /** 
     * @brief SPI中断使能：DISABLE：关闭所以中断  \n
     * @see SPI_IRQEna_Enable     \n  
     * @see SPI_IRQEna_TranDone   \n  
     * @see SPI_IRQEna_SSErr      \n  
     * @see SPI_IRQEna_DataOver    
     */ 
   uint8_t    IRQEna; 
   uint8_t    Trig;      /**< 传输触发选择：0，内部自动执行（仅主模式有效）；1，外部触发 */

	 uint8_t   DMA;      /**< SPI数据搬运方式：0，DMA搬运；1，MCU搬运 */
   uint8_t    BaudRate;  /**< 波特率设置 */

   uint8_t    ByteLength;/**< SPI传输数据长度，CPU搬运只能写1 */
}SPI_InitTypeDef;

#define SPI_FIRSTSEND_LSB 1    /**< 低位先传 */
#define SPI_FIRSTSEND_MSB 0    /**< 高位先传 */

#define SPI_DMA_ENABLE     0   /**< 使能DMA搬运 */
#define SPI_DMA_DISABLE    1   /**< 禁止DMA搬运 */

#define SPI_IRQEna_Enable              BIT7            /**<中断使能定义，SPI中断使能 */
#define SPI_IRQEna_TranDone            BIT6            /**<中断使能定义，传输完成中断 */
#define SPI_IRQEna_SSErr               BIT5            /**<中断使能定义，传输异常事件中断 */
#define SPI_IRQEna_DataOver            BIT4            /**<中断使能定义，传输溢出事件中断 */

#define SPI_IF_TranDone                BIT2            /**<中断标志定义，传输完成中断标志位 */
#define SPI_IF_SSErr                   BIT1            /**<中断标志定义，传输异常中断标志位 */
#define SPI_IF_DataOver                BIT0            /**<中断标志定义，传输溢出中断标志位 */

void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);

uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag);
void SPI_ClearIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag);

void    SPI_SendData(SPI_TypeDef *SPIx, uint8_t n);
uint8_t SPI_ReadData(SPI_TypeDef *SPIx);
#endif /*__lks32mc08x_SPI_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
