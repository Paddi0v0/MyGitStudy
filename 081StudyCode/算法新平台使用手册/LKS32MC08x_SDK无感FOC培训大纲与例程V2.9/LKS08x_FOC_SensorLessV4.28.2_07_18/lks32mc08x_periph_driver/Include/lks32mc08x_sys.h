/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_sys.h\n
 * 文件标识： 无 \n
 * 内容摘要： sys驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016年05月21日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */

#ifndef __LKS32MC08x_SYS_H
#define __LKS32MC08x_SYS_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc08x_lib.h"
#include <stdbool.h>

/** 低功耗IO唤醒电平枚举成员*/ 
typedef enum
{
	WAKETRIG_LOW, /**输入IO低电平唤醒*/ 
	WAKETRIG_HIGH,/**输入IO高电平唤醒*/ 
}enumWakeTrigLevel;

/** 
 *@brief 低功耗时钟配置中间变量
 */
typedef struct
{
    uint32_t AFE_REG5_RECORD;
    uint32_t AFE_REG6_RECORD;
	uint32_t CLK_CFG_RECORD;
}WAKE_InitTypeDef;

/** 
 *@brief 系统初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
	uint32_t PLL_SrcSel;                      /**<PLL信号输入源选择，RC时钟或外部晶体 @see SYS_PLLSRSEL_RCH @see SYS_PLLSRSEL_CRYSTAL*/

	uint32_t PLL_DivSel;                      /**<选择8个时钟周期中，哪个周期输出时钟*/
	uint32_t PLL_ReDiv;                       /**<PLL再分频，1分频或4分频*/

	uint32_t Clk_DivSPI;                      /**<I2C时钟分频*/
	uint32_t Clk_DivUART;                     /**<UART时钟分频*/
	uint32_t Clk_FEN;                         /**<模块时钟使能*/

	uint32_t WDT_Ena;                         /**<使能看门狗*/
	uint32_t PORFilter_Ena;                   /**<使能POR滤波*/
	
}SYS_InitTypeDef;


/*PLL信号输入源选择*/
#define SYS_PLLSRSEL_RCH        0x00  /**<使用4MHz RC时钟*/
#define SYS_PLLSRSEL_CRYSTAL    0x01  /**<使用晶体时钟*/

/*PLL再分频定义*/
#define SYS_PLLREDIV_4			0x00  /**<在PLL分频基础上再/4*/
#define SYS_PLLREDIV_1			0x01  /**<在PLL分频基础上不再分频*/

/*SPI时钟分频*/
#define SYS_Clk_SPIDiv1          0 /**< SPI时钟分频，占时未使用*/
#define SYS_Clk_SPIDiv2          1 /**< SPI时钟分频，占时未使用*/
#define SYS_Clk_SPIDiv4          2 /**< SPI时钟分频，占时未使用*/
#define SYS_Clk_SPIDiv8          3 /**< SPI时钟分频，占时未使用*/

/*UART时钟分频*/
#define SYS_Clk_UARTDiv1         0 /**< UART时钟分频，占时未使用*/
#define SYS_Clk_UARTDiv2         1 /**< UART时钟分频，占时未使用*/
#define SYS_Clk_UARTDiv4         2 /**< UART时钟分频，占时未使用*/
#define SYS_Clk_UARTDiv8         3 /**< UART时钟分频，占时未使用*/

/*数字模块位定义*/
#define SYS_Module_I2C           BIT0 /**< I2C模块*/
#define SYS_Module_HALL          BIT1 /**< HALL模块*/
#define SYS_Module_TIMER         BIT2 /**< TIMER模块*/
#define SYS_Module_MCPWM         BIT3 /**< MCPWM模块*/
#define SYS_Module_UART0         BIT4 /**< UART0模块*/
#define SYS_Module_UART1         BIT5 /**< UART1模块*/
#define SYS_Module_DSP           BIT6 /**< DSP模块*/
#define SYS_Module_CAN           BIT7 /**< CAN模块*/
#define SYS_Module_SPI           BIT8 /**< SPI模块*/

/*模拟模块定义*/
#define SYS_AnalogModule_ADC     BIT0  /**<ADC模块*/
#define SYS_AnalogModule_OPA0    BIT2  /**<OPA0模块*/
#define SYS_AnalogModule_OPA1    BIT3  /**<OPA1模块*/
#define SYS_AnalogModule_OPA2    BIT4  /**<OPA2模块*/
#define SYS_AnalogModule_OPA3    BIT5  /**<OPA3模块*/
#define SYS_AnalogModule_CMP0    BIT6  /**<CMP0模块*/
#define SYS_AnalogModule_CMP1    BIT7  /**<CMP1模块*/
#define SYS_AnalogModule_BGP     BIT8  /**<BGP模块*/
#define SYS_AnalogModule_RCH     BIT10 /**<RCH模块*/
#define SYS_AnalogModule_DAC     BIT12 /**<DAC模块*/
#define SYS_AnalogModule_TMP     BIT13 /**<温度传感器模块*/
#define SYS_AnalogModule_XTAL    BIT14 /**<晶振模块*/
#define SYS_AnalogModule_PLL     BIT15 /**<PLL模块*/

/*看门狗超时时间*/
#define SYS_WD_TimeOut2s  0         /**<看门狗超时时间2s复位*/
#define SYS_WD_TimeOut4s  1         /**<看门狗超时时间4s复位*/
#define SYS_WD_TimeOut8s  2         /**<看门狗超时时间8s复位*/
#define SYS_WD_TimeOut64s 3         /**<看门狗超时时间64s复位*/

/*复位信号源定义*/
#define SYS_RstSrc_LPOR        0x01     /**<复位信号源：内部1.5V电源管理复位*/
#define SYS_RstSrc_HPOR        0x02     /**<复位信号源：内部3.3V电源管理*/
#define SYS_RstSrc_KEYBOARD    0x04     /**<复位信号源：按键复位*/
#define SYS_RstSrc_WDT         0x08     /**<复位信号源：WDT复位*/

/*休眠唤醒间隔时间*/
#define SYS_WakeInterval_025s  0x00     /**<休眠唤醒间隔时间0.25s*/    
#define SYS_WakeInterval_05s   0x01     /**<休眠唤醒间隔时间0.5s*/
#define SYS_WakeInterval_1s    0x02     /**<休眠唤醒间隔时间1s*/
#define SYS_WakeInterval_2s    0x03     /**<休眠唤醒间隔时间2s*/
#define SYS_WakeInterval_4s    0x04     /**<休眠唤醒间隔时间4s*/
#define SYS_WakeInterval_8s    0x05     /**<休眠唤醒间隔时间8s*/
#define SYS_WakeInterval_16s   0x06     /**<休眠唤醒间隔时间16s*/
#define SYS_WakeInterval_32s   0x07     /**<休眠唤醒间隔时间32s*/

/*低功耗唤醒IO选择*/
#define WAKEIO_P0_0	 BIT0  /**<系统低功耗时使用P0.0作为唤醒IO*/
#define WAKEIO_P0_1	 BIT1  /**<系统低功耗时使用P0.1作为唤醒IO*/
#define WAKEIO_P1_0	 BIT2  /**<系统低功耗时使用P1.0作为唤醒IO*/
#define WAKEIO_P1_1	 BIT3  /**<系统低功耗时使用P1.1作为唤醒IO*/

#define MCU_POWER_3v3  0 //MCU 3.3V供电
#define MCU_POWER_5v0  1 //MCU 5V供电

#define POWER_MODE         MCU_POWER_5v0 

#ifndef POWER_4V5
#define POWER_4V5   0x00    /*电源掉电监测阈值为4.5V*/   
#endif
#ifndef POWER_4V2
#define POWER_4V2   0x01    /*电源掉电监测阈值为4.2V*/ 
#endif
#ifndef POWER_3V9
#define POWER_3V9   0x02    /*电源掉电监测阈值为3.9V*/
#endif
#ifndef POWER_3V6
#define POWER_3V6   0x03    /*电源掉电监测阈值为3.6V*/ 
#endif


/*系统设置*/
void SYS_Init(SYS_InitTypeDef* SYS_InitStruct);
void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct);

/*复位源*/
uint32_t SYS_GetRstSource(void);
void SYS_ClearRst(void);

/*看门狗*/
void SYS_WatchDogCmd(FuncState state);
void SYS_FeedDog(uint32_t timeOut);

/*POR滤波*/
//void SYS_PORFilterCmd(FuncState state);

/*休眠、唤醒、时钟切换*/
void SYS_FallSleep(void);
void SYS_SetWakeInterval(uint32_t nInterval);
void Switch2PLL(void);
void Switch2HRC(void);
void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint8_t ena);

/*控制8路时钟使能*/
void SYS_ModuleClockCmd(uint32_t nModule, FuncState state);

/*控制模拟模块时钟使能*/
void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state);
    
/*软复位各模块*/
void SYS_SoftResetModule(uint32_t nModule);

/*IAP_MODE*/
//允许进入IAP_MODE，在软复位以后

/*DSP模块初始化*/
void DSP_Init(void);

/* MCU供电电压稳定判断函数*/
void SYS_VolSelModule(uint32_t Vol);

/* MCU供电电压稳定判断中断函数*/
void SYS_VolSelModuleIRQ(void);

/* MCU供电电压稳定判断中断使能函数*/
void SYS_VolSelModuleEnableIRQ(uint32_t Vol);
#endif /*__lks32mc08x_SYS_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
