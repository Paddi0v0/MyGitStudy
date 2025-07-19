/*******************************************************************************
 函数名称：    int Software_safe(void)
 功能描述：    软件认证代码
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
#include "project_config.h"
#include "Software_safe.h"


#if (CLASSB_ENABLE == FUNCTION_ON)

extern void setClassBFault(void);
extern void ADC0_init(void);

Micro_check microCheck;

/*******************************************************************************
 函数名称：    void RAM_init_result_check(void)
 功能描述：    RAM初始化检测
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
volatile u32 Code_Selftest_Buf[2];

const Software_SafteyStruct struSaftey __at(SAFTEY_MEMORY_ADDR) =
{
    0,0 ,0x55   /*FLASH CRC校验值 & RAM初始化March C+检测结果初始值*/
};

volatile u32 u32SafteyCrcRam __at(CRC_RESULT_BUFFER); 

/*******************************************************************************
 函数名称：    void Certification_init(void)
 功能描述：    软件认证代码初始化
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void Certification_init(void)
{
	Check_Data_init();          /* 软件认证变量数据初始化 */
	MarchC_Result_init();       /* MarchC+结果读取 */
	flash_check_init();         /* flash校验初始化自检 */
	GPIO_Check();               /* GPIO初始化自检 */
	PC_Check();                 /* PC指针初始化自检 */
	ADC_Init_Check();           /* ADC初始化自检 */
	CLOCK_Check();              /* 时钟初始化自检 */
	Interrupt_Check();		       /* 中断初始化自检 */		
	 WDT_init();                 /* 看门狗初始化 */  
}
/*******************************************************************************
 函数名称：    void Period_TestSelf(void)
 功能描述：    REG & RAM & ROM等在ADC中断中周期性自检
 函数功能：    

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void Period_TestSelf(void)
{
	__disable_irq();

	REG_Period_check();
	RAM_Period_check();
	//FLASH_Period_check();
	__enable_irq();

}
/*******************************************************************************
 函数名称：    void Certification_Check(void)
 功能描述：    软件认证周期自检
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void Certification_Check(void)
{
	PC_Check();              //PC指针周期自检
	ADC_Period_Check();      //ADC周期自检
	WDT_Check();             //看门狗喂狗自检
	ROM_Error_insert();      //ROM自检插入故障

	 if(microCheck.check_err_flg)  //任何自检故障都要停机
	 {
//		  power = 0;
	    PWMOutputs(MCPWM0,ENABLE);
		setClassBFault();
	 }
	 
}

/*******************************************************************************
 函数名称：    void Check_Data_init(void)
 功能描述：    软件自检数据初始化
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void Check_Data_init(void)
{
	 microCheck.check_err_flg = 0;
	 microCheck.crc_check = 0;
	 microCheck.err_numb = 0;
	 microCheck.index = 0;
	 microCheck.state = 0;
	 microCheck.error_state = 0;
}

/*******************************************************************************
 函数名称：    void RAM_init_result_check(void)
 功能描述：    RAM初始化自检
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
volatile u8  gRAM_error_flg1;
void RAM_init_result_check(void)
{
	  if(0xDD == RAM_Rsult())
		{
			gRAM_error_flg1 = 1;
			if(gRAM_error_flg1 == 1)
			{		    
			   Code_Selftest_Buf[0] = struSaftey.crc_golden;
				Code_Selftest_Buf[1] = 1;   //March C+自检有错误，flash该区域写1 
				
				__disable_irq();
        erase_flag = 0x9A0D361F;//擦除解锁
        EraseSector(SAFTEY_MEMORY_ADDR);
			   erase_flag = 0x00;
               progm_flag = 0x9AFDA40C;
				ProgramPage(SAFTEY_MEMORY_ADDR, 512, (unsigned char*) (&Code_Selftest_Buf[0]));	
				progm_flag = 0x00;
				__enable_irq(); 
				
        gRAM_error_flg1 = 2;				
			}					
		}		
}
/*******************************************************************************
 函数名称：   void MarchC+_Result_init(void)
 功能描述：   MarchC+自检结果初始化
 函数功能：   读取MarchC+检测结果，结果若为1则检测失败

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void MarchC_Result_init(void)
{
	 if(struSaftey.MarchC_result == 1)
	 {
	   microCheck.check_err_flg |= MARCHC_ERROR;
	 }
}

/*******************************************************************************
 函数名称：   void flash_check_init(void)
 功能描述：   flash初始化自检
 函数功能：   只在第一次上电对flash指定区间进行crc校验，并将校验结果存储到指定的flash地址，
              后续每次初始化时将该结果读出，并该结果做为flash周期自检结果是否正确的判断条件

 PS:03x没有硬件CRC模块，软件CRC速度较慢，初始上电时可以不用做整体CRC校验，而是将CRC结果直接写到flash的指定地址，
    用周期性校验的结果跟该值做对比，从而节省校验时间


 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
u8 CRC_test_flg;
void flash_check_init(void)
{
	 if(CRC_test_flg)
	 {   
			REG32(CRC_RESULT_BUFFER) = 0xffffffff;
			microCheck.goldenCRC_flash = crc_flash_block(0x00000000, FLASH_SIZE, CRC_RESULT_BUFFER);
		 	REG32(CRC_RESULT_BUFFER) = 0xffffffff;			 
			
			Code_Selftest_Buf[0] = microCheck.goldenCRC_flash;
			Code_Selftest_Buf[1] = struSaftey.MarchC_result;
			
			__disable_irq();
		
			erase_flag = 0x9A0D361F;//擦除解锁
			EraseSector(SAFTEY_MEMORY_ADDR);
			erase_flag = 0x00;

            progm_flag = 0x9AFDA40C;
			ProgramPage(SAFTEY_MEMORY_ADDR, 512, (unsigned char*) (&Code_Selftest_Buf[0]));	
			progm_flag = 0x00;
		
			__enable_irq(); 
						
	 }

	 if(struSaftey.crc_golden != 0)
	 {
			microCheck.goldenCRC_flash = struSaftey.crc_golden;
	 }	 
	 
}

/*******************************************************************************
 函数名称：    void GPIO_Check(void)
 功能描述：    GPIO自检函数
 函数功能：    GPIO输入输出功能测试 

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
#define GPIO_OUT_EN       GPIO1_POE
#define GPIO_IN_EN        GPIO1_PIE
#define GPIO_OUT_SET      GPIO1_PDO
#define GPIO_IN_SET       GPIO1_PDI
#define GPIO_PORT         BIT4
void GPIO_Check(void)
{		
  GPIO_IN_EN |= GPIO_PORT;       /* P2.6开启输入输出使能 */
	GPIO_OUT_EN |= GPIO_PORT;
	
	GPIO_OUT_SET |= GPIO_PORT;      /* P2.6输出高电平 */
	
	softdelay(10);
	
	if(microCheck.Insert_err_flg & GPIO_IN_ERROR)
	{
    GPIO_OUT_SET &= ~GPIO_PORT;     /*插入故障*/
	}
	
	if(GPIO_IN_SET & GPIO_PORT)    /* 若输入寄存器判断为低电平，则GPIO异常 */
	{
	  microCheck.check_err_flg &= ~GPIO_IN_ERROR;	
	}
	else
	{
	  microCheck.check_err_flg |= GPIO_IN_ERROR;
	}
	
	GPIO_OUT_SET &= ~GPIO_PORT;	    /* 输出低电平 */

	if(microCheck.Insert_err_flg & GPIO_OUT_ERROR)
	{
    GPIO_OUT_SET |= GPIO_PORT;      /*插入故障*/
	}	
	
  softdelay(10);
	
	if(GPIO_IN_SET & GPIO_PORT)    /* 若输入寄存器判断为高电平，则GPIO异常 */
	{
	 microCheck.check_err_flg |= GPIO_OUT_ERROR;			
	}
	else
	{
	 microCheck.check_err_flg &= ~GPIO_OUT_ERROR;	
	}
	
	GPIO_IN_EN &= ~GPIO_PORT;     /* 关闭输入输出使能 */
	GPIO_OUT_EN &= ~GPIO_PORT;	

}
/*******************************************************************************
 函数名称：    void PC_Check(void)
 功能描述：    PC指针自检
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
unsigned char __attribute__((section(".ARM.__at_0x3FF0"))) PC_TEST1(void)
{
	volatile unsigned char result1;
	result1 = 0x0a;
	return result1;
}

unsigned char __attribute__((section(".ARM.__at_0x400E")))PC_TEST2(void)
{
	volatile unsigned char result2;
	result2 = 0x4b;
	return result2;
}

void PC_Check(void)
{
	if((PC_TEST1() != 0X0a || (PC_TEST2() != 0x4b)))
	{
	  microCheck.check_err_flg |= PC_ERROR;	
	}
	else
	{
	  microCheck.check_err_flg &= ~PC_ERROR;	
	}
}
/*******************************************************************************
 函数名称：    void Interrupt_Check(void)
 功能描述：    中断自检
 函数功能：    检测是否正常进中断，500us的timer中断，PWM频率15K,66us的ADC中断，每进一次timer中断大概进8次ADC中断，
               如果大于9次或者小于6次则表明进中断的时机不对，中断异常

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
void Interrupt_Check(void)
{
	while(microCheck.Interrupt_TIMER_cnt < 6)
	{
		if(((microCheck.Interrupt_cnt > 9) || (microCheck.Interrupt_cnt < 6)) && (microCheck.Interrupt_TIMER_cnt > 3))
			{
				microCheck.check_err_flg |= INTERRUPT_ERROR;
			}
			else
			{
				microCheck.check_err_flg &= ~INTERRUPT_ERROR;
			}	
	}

}

/*******************************************************************************
 函数名称：    void ADC_Init_Check(void)
 功能描述：    ADC自检
 函数功能：    检测芯片内部GND和温度传感器的电压，电压超出范围检测失败

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
void ADC_Init_Check(void)
{
    volatile u32 t_ADC_dlay;
    volatile u16 t_ADC_cnt;
    volatile s32 t_vss, t_REF;
	 
    __disable_irq();	
	
    ADC_SOFTWARE_TRIG_ONLY();		  //ADC触发方式软触发
	  ADC_CFG |= BIT10;            //数据格式右对齐
    ADC_STATE_RESET();     

    for(t_ADC_dlay = 0; t_ADC_dlay < 100; t_ADC_dlay++);
	
	  t_vss = 0; 
	  t_REF = 0;
		
    ADC_CHN0 = (INTERNAL_VSS_CHANNEL) | (INTERNAL_REF_CHANNEL << 4);  //GND和内部AD基准

    ADC_IF = 0x1f;

    ADC_SWT = 0x00005AA5;

    for (t_ADC_cnt = 0; t_ADC_cnt < 512; t_ADC_cnt++)
    {
        while((ADC_IF & BIT0) == 0)
				{
					;
				}
        ADC_IF = BIT1 | BIT0;

				t_REF  += (s16)((ADC_DAT1));
     	  t_vss  += (s16)((ADC_DAT0));

        ADC_SWT = 0x00005AA5;
    }

	  microCheck.VSS_ADC  = (s16)(t_vss >> 9);
	  microCheck.REF_ADC = (s16)(t_REF >> 9);	
	
		if((microCheck.REF_ADC > 1406) || (microCheck.REF_ADC < 1324) || (microCheck.VSS_ADC > 25) || (microCheck.VSS_ADC < -25))
		{/*REF偏差3%，2.328-2.472对应AD值为1324-1406，GND偏差0.05V以内，对应正常ADC范围为-25 - 25*/
			microCheck.check_err_flg |= ADC_ERROR;	
		}
		
    ADC0_init();

    __enable_irq();

}
/*******************************************************************************
 函数名称：    void ADC_Period_Check(void)
 功能描述：    ADC周期自检
 函数功能：    程序运行过程中检测芯片内部GND和温度传感器的电压，电压超出范围检测失败

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
void ADC_Period_Check(void)
{
	if((microCheck.REF_ADC > 1406) || (microCheck.REF_ADC < 1324) || (microCheck.VSS_ADC > 25) || (microCheck.VSS_ADC < -25))
	{/*REF偏差3%，2.328-2.472对应AD值为1324-1406，GND偏差0.05V以内，对应正常ADC范围为-25 - 25*/
		microCheck.check_err_flg |= ADC_ERROR;	
	}
	else
	{
	  microCheck.check_err_flg &= ~ADC_ERROR;	
	}
}
/*******************************************************************************
 函数名称：    void CLOCK_Check(void)
 功能描述：    时钟自检
 函数功能：    用HRC检测LRC

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
void CLOCK_Check(void)
{
	__disable_irq();
	
  SYS_ModuleClockCmd(SYS_Module_TIMER1,ENABLE);     //打开Timer时钟	
	UTIMER1_CFG |= BIT31;             //开启timer1使能

	UTIMER1_TH = 96000000;            //设置timer1计数门限值
	UTIMER1_CNT = 0;                  //清零timer1计数器
	
	AON_EVT_RCD = 0xCA40;	           //清除看门狗唤醒事件	
		
	while(UTIMER1_CNT < 2500)        //等待50us，清零完毕
	{
	  ;
	}	
	
	IWDG_PSW = 0xA6B4;
	IWDG_RTH = 0x80000;
	
	IWDG_PSW = 0xA6B4;
	IWDG_WTH = 0x7F000;	                   //低11位只能是0，0x80000->0x7F000计数4096次
		
	IWDG_PSW = 0xA6B4;
	IWDG_CLR = 0x798D;
			
	IWDG_CFG |= BIT4;	
		
	UTIMER1_CNT = 0; 	
				
	while((AON_EVT_RCD & BIT9) == 0)        //看门狗计数4096次
				{
      ;
		}
   
	microCheck.Timer_Cnt =  UTIMER1_CNT;	  //看门狗计数4096次，Utimer计数次数
 
  microCheck.LRC_frequency  = 1000000000/(microCheck.Timer_Cnt * 20.8/WDT_WAIT_CNT);   //根据时间算出LRC时钟频率
	
	if(microCheck.Insert_err_flg & CLOCK_ERROR)
	{
	   microCheck.LRC_frequency = 30000;
	}
	
	if((microCheck.LRC_frequency < 32000) || (microCheck.LRC_frequency > 96000))
	{//LKS03x低速时钟全温度范围内32000hz-96000hz
	  microCheck.check_err_flg |= CLOCK_ERROR;	
	}

//  UTIMER1_CFG &= ~BIT31;                             //关闭Timer1模块
//  SYS_ModuleClockCmd(SYS_Module_TIMER1,DISABLE);     //关闭Timer1时钟		
	IWDG_CFG &= ~BIT4;	                               //关闭看门狗定时唤醒
	IWDG_CFG = 0x3c00;                                 //关闭看门狗
	
//  UTimer_init();	
	__enable_irq();

}

/*******************************************************************************
 函数名称：    void WDT_init(void)
 功能描述：    看门狗初始化
 函数功能：    初始化配置看门狗

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
void WDT_init(void)
{
	IWDG_InitTypeDef IWDG_InitStruct;
	
	IWDG_StrutInit(&IWDG_InitStruct);    //初始化结构体
	IWDG_InitStruct.WDG_EN  = ENABLE ;    //使能看门狗
	IWDG_InitStruct.RTH  = SECOND2IWDGCNT(8.0);//设置看门狗2S后复位芯片
	IWDG_Init(&IWDG_InitStruct);
}
/*******************************************************************************
 函数名称：    void WDT_Check(void)
 功能描述：    喂狗
 函数功能：    

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
void WDT_Check(void)
{
  if(microCheck.Insert_err_flg & WDT_ERROR)
	{
	  microCheck.check_err_flg |= WDT_ERROR;		
	}
	else
	{
		microCheck.check_err_flg &= ~WDT_ERROR;	
	  IWDG_Feed();
	}	 
}

/*******************************************************************************
 函数名称：    void ROM_Error_insert(void)
 功能描述：    ROM故障插入
 函数功能：    在flash校验的空间范围内选择一个没有用到的扇区，对该扇区进行写入数据，
               再进行CRC校验时golden值会改变，从而检测失败

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
volatile u32 t_ROMBuf[3] = {0x55,0xAA,0xFF};
volatile u8 ROM_test_flg;	
void ROM_Error_insert(void)
{
		if((microCheck.Insert_err_flg & ROM_ERROR) && (ROM_test_flg == 0))
		{
			t_ROMBuf[0] = 0x55;
			t_ROMBuf[1] = 0xAA;
			t_ROMBuf[2] = 0xFF;

			__disable_irq();

			erase_flag = 0x9A0D361F;//擦除解锁
			EraseSector(ROM_INSERT_ERR_ADDR);
			erase_flag = 0x00;

			progm_flag = 0x9AFDA40C;
			ProgramPage(ROM_INSERT_ERR_ADDR, 512, (unsigned char*) (&t_ROMBuf[0]));	
			progm_flag = 0x00;

			__enable_irq(); /* FLASH写入函数*/
				
			ROM_test_flg = 1;			
		}
}
/*******************************************************************************
 函数名称：crc_flash_block(u32 flash_start_addr, u32 size, u32 crc_result_buffer_addr)
 功能描述：crc自检函数
 函数功能：   设置flash校验起始地址及该地址后要校验的字节数，对该字段flash进行crc校验，并将结果存储
              到指定的ram位置供进一步使用，校验的中间结果会被反复存储和恢复，注意每个检测周期结束后
              都要对该ram地址清零

 flash_start_addr: CRC计算的flash起始地址
 size: 要校验的字节数
 crc_result_buffer_addr: 保存32个位crc结果的ram地址

 PS:03x没有硬件CRC模块，软件CRC速度较慢，4字节运算约20us左右，用户也可以改成自己的CRC校验算法，节约运行时间
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
volatile u32 crc_value_result;
u32 crc_flash_block(u32 flash_start_addr, u32 size, u32 crc_result_buffer_addr)
{ 
 const uint32_t st_const_value = 0x04c11db7;
 uint32_t  xbit;
 uint32_t  bits;
 uint32_t  i;
 uint32_t  CRC_data;

 crc_value_result = REG32(crc_result_buffer_addr);
   
    i = 0;
    while(i<size)
	  {       
  xbit = 0x80000000;
	
	CRC_data = REG32(flash_start_addr+i);
	 
  for (bits = 0; bits < 32; bits++)
  {
   if (crc_value_result & 0x80000000)
   {
    crc_value_result <<= 1;
    crc_value_result ^= st_const_value;
   }
   else
   {
    crc_value_result <<= 1;
    }
   
   if (CRC_data & xbit)
   {
    crc_value_result ^= st_const_value;
   }
   xbit >>= 1;
}

	i = i+ 4;
 }
  REG32(crc_result_buffer_addr) = crc_value_result;
  return crc_value_result;
}
//u32 crc_flash_block(u32 flash_start_addr, u32 size, u32 crc_result_buffer_addr)
//{
// uint32_t  i;
// uint32_t  CRC_data;

// crc_value_result = REG32(crc_result_buffer_addr);
//	
// i = 0;
// while(i < size)
// {
//	 CRC_data = REG8(flash_start_addr+i);
//	 
//	 crc_value_result ^= CRC_data;
//	
//	 i ++;
// }
//  REG32(crc_result_buffer_addr) = crc_value_result;
//  return crc_value_result;
//}

/*******************************************************************************
 函数名称：    void REG_Period_check(void)
 功能描述：    REG在ADC中断中周期性自检
 函数功能：    

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void REG_Period_check(void)
{
	 if(microCheck.state == 0)
	 {
	   if(microCheck.index < TEST_PART1_NUMS)
		 {
			 if(Micro_checkREG(microCheck.index) != 0xcc)  //error
			 {
					microCheck.err_numb = microCheck.index;			 
				  microCheck.error_state |= BIT0;
			 }
			 microCheck.index++;		 
		 }
		 else
		 {
			  if(microCheck.error_state & BIT0)
				{
			    microCheck.check_err_flg |= REG_ERROR;				
				}
				else
				{
			    microCheck.check_err_flg &= ~REG_ERROR;				
				}
				
			  microCheck.error_state = 0;				 
			  microCheck.index = 0;
			  microCheck.state = 1;
		 }	 	 
	 }
}
/*******************************************************************************
 函数名称：    void RAM_Period_check(void)
 功能描述：    RAM在ADC中断中周期性自检
 函数功能：    

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void RAM_Period_check(void)
{
	if(microCheck.state == 1)
		{
	  if(microCheck.index < TEST_PART2_NUMS) 
		{
			 if(0xcc != occupied_halfword_scan(0x20000000 + (microCheck.index << 1)))  //error
			 {
				  microCheck.err_numb = microCheck.index;
					microCheck.error_state |= BIT1;
			 }
			 microCheck.index++;				
		}
		else
		{
			  if(microCheck.error_state & BIT1)
				{
			    microCheck.check_err_flg |= RAM_ERROR;				
				}
				else
				{
			    microCheck.check_err_flg &= ~RAM_ERROR;				
				}			
			 microCheck.error_state = 0;
			 microCheck.index = 0;
		   microCheck.state = 2;			
		}
		}
	

}
/*******************************************************************************
 函数名称：    void FLASH_Period_check(void)
 功能描述：    flash在ADC中断中周期性自检
 函数功能：    

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
void FLASH_Period_check(void)
{
	if(microCheck.state == 2)
		{		
		if(microCheck.index < TEST_PART3_NUMS)
		{
			 microCheck.crc_check = crc_flash_block((microCheck.index << 2),0x04,CRC_RESULT_BUFFER);
			 microCheck.index++;		  
		}
		else
		{
		
			 if(microCheck.crc_check  != microCheck.goldenCRC_flash)  //周期自检结果与整体自检结果若不一致，flash被篡改，测试fail
			 {
	 			 microCheck.err_numb = microCheck.index;			 
				 microCheck.check_err_flg |= ROM_ERROR;	
			 }
			 else
			 {
				 microCheck.check_err_flg &= ~ROM_ERROR;	
			 }										
			 
			 microCheck.crc_check = 0;			 //crc周期自检结果清零
			 REG32(CRC_RESULT_BUFFER) = 0xffffffff;   //周期自检一轮结束后清零存储CRC结果的RAM地址里的数据
			 microCheck.index = 0;
			 microCheck.state = 0;				
		}	
		}	

}


u32 Micro_checkREG(u16 code)
{
	    u32 scan_result =0;
      switch (code)
			{			
				case 0:
					scan_result = r0_0scan();
					break;
				case 1:
					scan_result = r1_0scan();
					break;
				case 2:
					scan_result = r2_0scan();
					break;
				case 3:
					scan_result = r3_0scan();
					break;
				case 4:
					scan_result = r4_0scan();
					break;
				case 5:
					scan_result = r5_0scan();
					break;
				case 6:
					scan_result = r6_0scan();
					break;
				case 7:
					scan_result = r7_0scan();
					break;
				case 8:
					scan_result = r8_0scan();
					break;
				case 9:
					scan_result = r9_0scan();
					break;
				case 10:
					scan_result = r10_0scan();
					break;
				case 11:
					scan_result = r11_0scan();
					break;
				case 12:
					scan_result = r12_0scan();
					break;
				case 13:
					scan_result = r13_0scan();
					break;
				case 14:
					scan_result = r14_0scan();
					break; 
				case 15:
					scan_result = r0_1scan();
					break; 
        case 16:
					scan_result = r1_1scan();
					break;       
        case 17:
					scan_result = r2_1scan();
					break;
        case 18:
					scan_result = r3_1scan();
					break;
        case 19:
					scan_result = r4_1scan();
					break;
        case 20:
					scan_result = r5_1scan();
					break;
        case 21:
					scan_result = r6_1scan();
					break;
        case 22:
					scan_result = r7_1scan();
					break;
        case 23:
					scan_result = r8_1scan();
					break;
				case 24:
					scan_result = r9_1scan();
					break;
				case 25:
					scan_result = r10_1scan();
					break;
				case 26:
					scan_result = r11_1scan();
					break;
				case 27:
					scan_result = r12_1scan();
					break;
				case 28:
					scan_result = r13_1scan();
					break;
				case 29:
					scan_result = r14_1scan();
					break;
				default:
					scan_result = 0xcc;
					break;
			}
			return scan_result;
			
}

/*******************************************************************************
 函数名称：    void Softdelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/15      V1.0           李四龙          创建
 *******************************************************************************/
void softdelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}


extern bool getIfPwrONReset(void);
extern bool getIfWDReset(void);

void classBCheckInitProcess(void)
{
	if(getIfPwrONReset())           //存在上电复位标志位记录
	{		
    	Certification_init();		//ClassB认证代码初始化
		 // SYS_ClearRst();			//清除复位源标志位
	}

	if(!getIfWDReset())				//没有看门狗复位
	{
		if(getIfPwrONReset())		//存在上电复位标志位记录
		{
			   //WDT_init();		//看门狗检测	
		}							
	}
}

#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
