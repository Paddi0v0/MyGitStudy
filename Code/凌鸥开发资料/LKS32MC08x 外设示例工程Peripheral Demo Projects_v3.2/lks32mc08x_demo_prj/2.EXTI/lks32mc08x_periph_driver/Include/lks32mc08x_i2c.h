/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_i2c.h\n
 * 文件标识： 无 \n
 * 内容摘要： I2C驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0     <td>YangZJ     <td>创建
 * </table>
 */
 
#ifndef __LKS32MC08x_I2C_H
#define __LKS32MC08x_I2C_H

#include "lks32mc08x_lib.h"

/** 
 *@brief I2C寄存器结构体句柄
 */
typedef struct
{
   __IO uint32_t ADDR;
   __IO uint32_t CFG;
   __IO uint32_t SCR;
   __IO uint32_t DATA;
   __IO uint32_t MSCR;
   __IO uint32_t BCR;
}I2C_TypeDef;


/**
 * I2C结构体基地址定义
 */
#ifndef I2C
#define I2C         ((I2C_TypeDef *) I2C0_BASE)
#endif

/** 
 *@brief I2C初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    u8  ADRCMP          ;   /**<   I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效*/
    u8  MST_MODE        ;   /**<   I2C 主模式使能；ENABLE:使能，DISABLE:失能*/
    u8  SLV_MODE        ;   /**<   I2C 从模式使能；ENABLE:使能，DISABLE:失能*/
    u8  DMA             ;   /**<   I2C DMA传输使能；ENABLE:使能，DISABLE:失能*/
    u32 BaudRate        ;   /**<   I2C 波特率*/
    u8  IE              ;   /**<   I2C 中断使能；ENABLE:使能，DISABLE:失能*/
    u8  TC_IE           ;   /**<   I2C 数据传输完成中断使能；ENABLE:使能，DISABLE:失能*/
    u8  BUS_ERR_IE      ;   /**<   I2C 总线错误事件中断使能；ENABLE:使能，DISABLE:失能*/
    u8  STOP_IE         ;   /**<   I2C STOP 事件中断使能；ENABLE:使能，DISABLE:失能*/
    u8  BURST_NACK      ;   /**<   I2C 传输，NACK 事件中断使能；ENABLE:使能，DISABLE:失能*/
    u8  BURST_ADDR_CMP  ;   /**<   I2C 传输，硬件地址匹配中断使能；ENABLE:使能，DISABLE:失能*/
}I2C_InitTypeDef;

void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct);

void    I2C_SendData(I2C_TypeDef *I2Cx, uint8_t n);
uint8_t I2C_ReadData(I2C_TypeDef *I2Cx);

// i2c&dma发送&接收
void i2c_dma_rx(u8 addr, u8 *data, u8 len);
void i2c_dma_tx(u8 addr, u8 *data, u8 len);
void i2c_dma_init(void);
void i2c_dma_state_over(void);

#endif /*__lks32mc08x_I2C_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
