/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2015年11月5日
 *
 * 修改记录1：
 * 修改日期： 2021年8月25日
 * 版 本 号：
 * 修 改 人： HMG
 * 修改内容：
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "global_variable.h"
#include "gpio_led.h"
#include "gpio_key.h"

void SoftDelay(u32 cnt);
void SYS_UtimerFallSleep(void);
/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();         /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83; /*使能系统寄存器写操作*/
    FLASH_CFG |= 0x00080000; /* enable prefetch ，FLASH预取加速使能*/
	  delay_init(96);
	
    GPIO_init();             /* GPIO初始化 */
	  NVIC_EnableIRQ(WAKE_IRQn); /* 打开睡眠唤醒中断 */
    __enable_irq();          /* 开启总中断 */
}

/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct); //初始化结构体

    //配置按键 start：P2.11
    GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    //配置按键 stop：P2.12
    GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    //配置LED1：P0.6
    GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    //配置LED2：P0.7
    GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    //配置LED3: P0.3
    GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
		
		//低功耗IO唤醒口
		GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //P0.0输入使能
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
		GPIO_Init(GPIO0, &GPIO_InitStruct);
}
/*******************************************************************************
 函数名称：    void Clock_Init(void)
 功能描述：    时钟配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 |= BIT15;     /* BIT15:PLLPDN */
	  SoftDelay(100);
    SYS_CLK_CFG |= 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
}

/*******************************************************************************
 函数名称：    void SystemInit(void)
 功能描述：    硬件系统初始化，调用时钟初始化函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/14      V1.0           Howlet Li          创建
 *******************************************************************************/
void SystemInit(void)
{
    Clock_Init(); /* 时钟初始化 */
}


/*******************************************************************************
 函数名称：    void SYS_SetWakeInter(uint32_t nInterval)
 功能描述：    设置休眠唤醒周期
 操作的表：    无
 输入参数：    000：0.125S 
							 001：0.25S
							 010：0.5S 
							 011：1S
							 100：2S 
							 101：4S   
							 110：8S 
							 111：16S
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/5/24      V1.0           HMG          创建
 *******************************************************************************/
void SYS_SetWakeInter(uint32_t nInterval)
{
	uint32_t tempReg = SYS_RST_CFG;
	SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
	tempReg |= (nInterval << 2);
	SYS_RST_CFG = tempReg;
}

/*******************************************************************************
 函数名称：    void SYS_SetWakeIO(uint32_t nInterval)
 功能描述：    设置休眠唤醒IO
 操作的表：    无
 输入参数：    1、nInterval = BIT3: GPIO 1[1] / P1[1] 外部唤醒使能。1：使能；0：禁用。
							   nInterval = BIT2: GPIO 1[0] / P1[0] 外部唤醒使能。1：使能；0：禁用。
							   nInterval = BIT1: GPIO 0[1] / P0[1] 外部唤醒使能。1：使能；0：禁用。
							   nInterval = BIT0: GPIO 0[0] / P0[0] 外部唤醒使能。1：使能；0：禁用。
					    2、ENABLE:IO高电平唤醒
						   	 DISABLE：IO低电平唤醒
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0           HuangMG            创建
 *******************************************************************************/
void SYS_SetWakeIO(uint32_t nInterval, u8 POL)
{
	SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
	if (POL == ENABLE)
	{
		WAKE_PO = nInterval;
	}
	else
	{
		WAKE_PO &= ~nInterval;
	}
	 WAKE_EN = nInterval;
}


u32 AFE_REG5_RECORD = 0;
u32 AFE_REG6_RECORD = 0;
u32 CLK_CFG_RECORD = 0;
void Switch2PLL(void)
{
	  SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
    SYS_AFE_REG5 = AFE_REG5_RECORD;
    SoftDelay(200);
	  SYS_AFE_REG6 = AFE_REG6_RECORD;
    SYS_CLK_CFG = CLK_CFG_RECORD;     // Switch main clock to PLL  clock
	  SYS_WR_PROTECT = 0x0;  /*关闭寄存器写使能*/
}

/*******************************************************************************
 函数名称：    void SYS_FallSleepMode(void)
 功能描述：    触发系统进入休眠状态
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/5/24      V1.0           cfwu          创建
 *******************************************************************************/
void SYS_FallSleepMode(void)
{
	SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
	AFE_REG5_RECORD = SYS_AFE_REG5;
	AFE_REG6_RECORD = SYS_AFE_REG6;
	CLK_CFG_RECORD = SYS_CLK_CFG;
	SYS_AFE_REG5 = 0x0500;    // Prepare to shutdown PLL,HRC,BGP
  SYS_AFE_REG6|=1;          // Turn off power detection module in ANALOG
  SYS_CLK_CFG = 0;          // Switch to HRC clock
	SYS_CLK_SLP  = 0xDEAD;    // 进入休眠模式
	SYS_WR_PROTECT = 0x0; 
	__WFI();			   //PC指针停止运行
	SYS_UtimerFallSleep(); //在IO唤醒模式中，判断是Utimer唤醒则继续进入休眠
	Switch2PLL();
}

extern void InversP_Test(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
extern u8 Utimer_flag;
/*******************************************************************************
 函数名称：    void SYS_UtimerFallSleep(void)
 功能描述：    当工作在IO唤醒时，判断为Utimer唤醒，则执行该函数继续进行休眠
               如果不是Utimer唤醒，是IO唤醒则程序继续往下执行
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/9/6      V1.0             HMG               创建
 *******************************************************************************/
void SYS_UtimerFallSleep(void)
{
Sleep:
	if(Utimer_flag)				      /*判断是Utimer中断，则继续进入休眠*/
	{
		Utimer_flag = 0;	        /*Utimer唤醒标志位清零*/
		SYS_WR_PROTECT = 0x7a83;  /*开启寄存器写使能*/
		SYS_CLK_SLP = 0xDEAD;     /*进入休眠模式*/
		__WFI();			            /*PC指针停止运行*/
		SYS_WR_PROTECT = 0x0; 
		goto Sleep;			          /*返回到Sleep处*/
	}
	
}


/*******************************************************************************
 函数名称：    void Invers_GPIO(void)
 功能描述：    GPIO电平反转函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
                V1.0                                创建
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) //GPIO电平翻转函数
{
	u16 reg;
	reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); //读GPIO电平
	if (reg)
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin);
		return 0;
	}
	else
	{
		GPIO_SetBits(GPIOx, GPIO_Pin);
		return 1;
	}
}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        mingganghuang          创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}


