/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_cmp.h\n
 * 文件标识： 无 \n
 * 内容摘要： CMP外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author        <th>Description
 * <tr><td>2018年07月25日 <td>1.0  <td>William Zhang       <td>创建
 * </table>
 *@par 修改日志:增加开窗配置、增加比较器中断相关函数
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author        <th>Description
 * <tr><td>2022年04月26日 <td>2.0     <td>YangZJ          <td>创建
 * </table>
 */
#ifndef __LKS32MC08x_CMP_H
#define __LKS32MC08x_CMP_H
/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x_lib.h"
#include "string.h"
 
/**< 比较器回差选择*/
#define CMP_HYS_20mV            0        /**< 20mV*/
#define CMP_HYS_0mV             1        /**< 0mV*/

//比较器N端
#define CMP_SELN_IN             0        /**< 比较器N端，N端输入 */
#define CMP_SELN_REF            1        /**< 比较器N端，N端内部参考REF输入 */
#define CMP_SELN_DAC            2        /**< 比较器N端，N端内部DAC输入 */
#define CMP_SELN_HALL_MID       3        /**< 比较器N端，N端反电势过零中点输入 */
          
//比较器0 P端
#define CMP0_SELP_IP0            0        /**< P端IP0输入 */
#define CMP0_SELP_OPA0_IP        1        /**< P端OPA0 IP输入 */
#define CMP0_SELP_OPA0_OUT       2        /**< P端OPA0 OUT */
#define CMP0_SELP_OPA1_OUT       3        /**< P端OPA1 OUT */
#define CMP0_SELP_IP1            4        /**< P端IP1输入 */
#define CMP0_SELP_IP2            5        /**< P端IP2输入 */
#define CMP0_SELP_IP3            6        /**< P端IP3输入 */
#define CMP0_SELP_IP4            7        /**< P端IP4输入 */

//比较器1 P端
#define CMP1_SELP_IP0            0        /**< P端IP0输入 */
#define CMP1_SELP_OPA3_IP        1        /**< P端OPA3 IP输入 */
#define CMP1_SELP_OPA2_OUT       2        /**< P端OPA2 OUT */
#define CMP1_SELP_OPA3_OUT       3        /**< P端OPA3 OUT */
#define CMP1_SELP_IP1            4        /**< P端IP1输入 */
#define CMP1_SELP_IP2            5        /**< P端IP2输入 */
#define CMP1_SELP_IP3            6        /**< P端IP3输入 */
#define CMP1_SELP_AVSS           7        /**< 芯片地 */

//为保证库兼容性，保留修改的宏定义
#define SELN_CMP_IN             0        /**< N端输入（为保证库兼容性，保留修改的宏定义）*/
#define SELN_REF                1        /**< N端内部参考REF输入（为保证库兼容性，保留修改的宏定义） */
#define SELN_DAC                2        /**< N端内部DAC输入（为保证库兼容性，保留修改的宏定义） */
#define SELN_HALL_MID           3        /**< N端反电势过零中点输入（为保证库兼容性，保留修改的宏定义） */

#define SELP_CMP_OPA0IP         1        /**< P端OPA0_IP输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_OPA0OUT        2        /**< P端OPA0_OUT输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_OPA1OUT        3        /**< P端OPA1_OUT输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_OPA3IP         1        /**< P端OPA3_IP输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_OPA2OUT        2        /**< P端OPA2_OUT输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_OPA3OUT        3        /**< P端OPA3_OUT输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_IP0            0        /**< P端IP0输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_IP1            4        /**< P端IP1输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_IP2            5        /**< P端IP2输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_IP3            6        /**< P端IP3输入（为保证库兼容性，保留修改的宏定义） */
#define SELP_CMP_IP4            7        /**< P端IP4输入（为保证库兼容性，保留修改的宏定义） */

/** 
 *@brief CMP寄存器结构体句柄
 */
typedef struct
{
    __IO uint32_t IE;       /**< 比较器中断使能寄存器*/
    __IO uint32_t IF;       /**< 比较器中断标志寄存器*/
    __IO uint32_t TCLK;     /**< 比较器分频时钟控制寄存器*/
    __IO uint32_t CFG;      /**< 比较器控制寄存器*/
    __IO uint32_t BLCWIN;   /**< 比较器开窗控制寄存器*/
    __IO uint32_t DATA;     /**< 比较器输出数值寄存器*/
} CMP_TypeDef;
/**
 * CMP结构体基地址定义
 */
#ifndef CMP
#define CMP             ((CMP_TypeDef *) CMP_BASE)
#endif
/**
 * 比较器0
 */
#define CMP0            0
/**
 * 比较器1
 */
#define CMP1            1

/** 
 *@brief CMP初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    /**
     * @brief CMP 滤波时钟频率Freq(CMP_Filter) = (Freq(MCLK)/2^FIL_CLK10_DIV2)/(FIL_CLK10_DIV16+1) ，
     * 其中MCLK 为系统的主时钟，通常为 96MHz 全速时钟。需要注意的是，产生 CMP 滤波时钟需要使能CLK10_EN。
     */
    u32         FIL_CLK10_DIV16;    /**< 比较器 1/0 滤波时钟分频\n 赋值范围0-0xF*/
    FuncState   CLK10_EN;           /**< 比较器 1/0 滤波时钟使能\n DISABLE:失能，ENABLE：使能 */
    /**
     * @brief CMP 滤波时钟频率Freq(CMP_Filter) = (Freq(MCLK)/2^FIL_CLK10_DIV2)/(FIL_CLK10_DIV16+1) ，
     * 其中MCLK 为系统的主时钟，通常为 96MHz 全速时钟。需要注意的是，产生 CMP 滤波时钟需要使能CLK10_EN。
     */
    u32         FIL_CLK10_DIV2;     /**< 比较器 1/0 滤波时钟分频\n 0x0:1分频，0x1:2分频,0x2:4分频,0x3:8分频*/
    FuncState   CMP_FT;             /**< 比较器快速比较使能\n  DISABLE:失能，ENABLE：使能*/
    u32         CMP_HYS;            /**< 比较器回差选择\n @see CMP_HYS_0mV \n  @see CMP_HYS_20mV  */
    																																				
    FuncState   CMP0_EN;            /**< 比较器 0 使能\n DISABLE:失能，ENABLE：使能*/
    /**
     * @brief 比较器 0 信号正端选择
     * @see CMP_SELP_IP0           
     * @see CMP_SELP_OPA_IP        
     * @see CMP_SELP_OPA_OUT       
     * @see CMP_SELP_IP1           
     * @see CMP_SELP_IP2           
     * @see CMP_SELP_IP3           
     * @see CMP_SELP_IP4  
     */
    u32         CMP0_SELP;  
        /**
     * @brief 比较器 0 信号负端选择
     * @see CMP_SELN_IN                   
     * @see CMP_SELN_REF                 
     * @see CMP_SELN_DAC                 
     * @see CMP_SELN_HALL_MID 
     */       
    u32         CMP0_SELN;       
    FuncState   CMP0_IE;            /**< 比较器 0 中断使能\n DISABLE:失能，ENABLE：使能 */
    u32         CMP0_W_PWM_POL;     /**< 比较器 0 开窗 PWM 信号极性选择\n  0:高电平有效；1:低电平有效*/
    FuncState   CMP0_IRQ_TRIG;      /**< 比较器 0 边沿触发使能\n DISABLE:失能，ENABLE：使能 */
    FuncState   CMP0_IN_EN;         /**< 比较器 0 信号输入使能\n DISABLE:失能，ENABLE：使能 */
    u32         CMP0_POL;           /**< 比较器 0 极性选择\n 0:高电平有效；1:低电平有效*/
    FuncState   CMP0_CHN3P_WIN_EN;  /**< MCPWM 模块 CHN3_P 通道使能比较器\n 0 开窗 DISABLE:失能，ENABLE：使能 */
    FuncState   CMP0_CHN2P_WIN_EN;  /**< MCPWM 模块 CHN2_P 通道使能比较器\n 0 开窗 DISABLE:失能，ENABLE：使能 */
    FuncState   CMP0_CHN1P_WIN_EN;  /**< MCPWM 模块 CHN1_P 通道使能比较器\n 0 开窗 DISABLE:失能，ENABLE：使能 */
    FuncState   CMP0_CHN0P_WIN_EN;  /**< MCPWM 模块 CHN0_P 通道使能比较器\n 0 开窗 DISABLE:失能，ENABLE：使能 */
																																					
    FuncState   CMP1_EN;            /**< 比较器 1 使能\n 使能 DISABLE:失能，ENABLE：使能*/
     /**
     * @brief 比较器 0 信号正端选择
     * @see CMP_SELP_IP0           
     * @see CMP_SELP_OPA_IP        
     * @see CMP_SELP_OPA_OUT       
     * @see CMP_SELP_IP1           
     * @see CMP_SELP_IP2           
     * @see CMP_SELP_IP3           
     * @see CMP_SELP_IP4  
     */   
    u32         CMP1_SELP;  
     /**
     * @brief 比较器 0 信号负端选择
     * @see CMP_SELN_IN                   
     * @see CMP_SELN_REF                 
     * @see CMP_SELN_DAC                 
     * @see CMP_SELN_HALL_MID 
     */          
    u32         CMP1_SELN;         
    FuncState   CMP1_IE;            /**< 比较器 1 中断使能\n DISABLE:失能，ENABLE：使能 */
    u32         CMP1_W_PWM_POL;     /**< 比较器 1 开窗 PWM 信号极性选择\n 0:高电平有效；1:低电平有效*/
    FuncState   CMP1_IRQ_TRIG;      /**< 比较器 1 边沿触发使能\n DISABLE:失能，ENABLE：使能 */
    FuncState   CMP1_IN_EN;         /**< 比较器 1 信号输入使能\n DISABLE:失能，ENABLE：使能 */
    u32         CMP1_POL;           /**< 比较器 1 极性选择 0:高电平有效；1:低电平有效*/
    FuncState   CMP1_CHN3P_WIN_EN;  /**< MCPWM 模块 CHN3_P 通道使能比较器 1 开窗\n 0:高电平有效；1:低电平有效 */
    FuncState   CMP1_CHN2P_WIN_EN;  /**< MCPWM 模块 CHN2_P 通道使能比较器 1 开窗\n 0:高电平有效；1:低电平有效 */
    FuncState   CMP1_CHN1P_WIN_EN;  /**< MCPWM 模块 CHN1_P 通道使能比较器 1 开窗\n 0:高电平有效；1:低电平有效 */
    FuncState   CMP1_CHN0P_WIN_EN;  /**< MCPWM 模块 CHN0_P 通道使能比较器 1 开窗\n 0:高电平有效；1:低电平有效 */
}CMP_InitTypeDef;

void CMP_Init(CMP_InitTypeDef *);           // 比较器初始化
void CMP_StructInit(CMP_InitTypeDef *);     // 比较器配置结构体初始化
void CMP_ClearIRQFlag(u8 CMPx);             // 清CMP中断
u8   CMP_GetIRQFlag(u8 CMPx);               // 读CMP中断

#endif /*__LKS32MC05x_CMP_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/

