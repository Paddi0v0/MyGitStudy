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
#include "Software_safe.h"

#if (CLASSB_ENABLE == FUNCTION_ON)
Micro_check microCheck;

extern void setClassBFault(void);

/*******************************************************************************
 函数名称：    void RAM_init_result_check(void)
 功能描述：    RAM初始化检测
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
volatile u32 Code_Selftest_Buf[2];

//volatile const Software_SafteyStruct struSaftey  __at(SAFTEY_MEMORY_ADDR)={0,0,0x55};
const u32 u32SafteyCrcBuff[2] __at(SAFTEY_MEMORY_ADDR) = { 0x5a5a5a5a,0x5a5a5a5a };  

const u8 u32SafteyReserveBuff[512-sizeof(u32SafteyCrcBuff)] __at(SAFTEY_MEMORY_ADDR+sizeof(u32SafteyCrcBuff)) = {0  };  

volatile u32 u32SafteyCrcRam __at(CRC_RESULT_BUFFER); 


//    0x5a5a5a5a,
//    0x5a5a5a5a,
//	  0x5a
//};
//=
//{
//  0xFF,0xFF ,0x55   /*FLASH CRC校验值 & RAM初始化March C+检测结果初始值*/
//};

//volatile const u32 TestBuff[(512>>2)] __at(0xfa00)= {1,1};
//volatile const u8 buffer_flash1[512] __at(0xfa00) = {0x55, 0x55};
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
	//CLOCK_Check();              /* 时钟初始化自检 */
	Interrupt_Check();		       /* 中断初始化自检 */		
   //WDT_init();               /* 看门狗初始化 */  
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
	FLASH_Period_check();
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
static u8 checkindex=0;

	switch (checkindex)
	{
		//5分频执行  执行周期5*62.5us
		case 0:		
			
       PC_Check();              //PC指针周期自检 1.82us
		  
			break;
		case 1:
			 ADC_Period_Check();      //ADC周期自检  2.08us
		 
			break;
//		case 2:		
//	  WDT_Check();             //看门狗喂狗自检 
//	  break;
		case 2:	

	    ROM_Error_insert();      //ROM自检插入故障
			__disable_irq();	
 		  FLASH_Period_check();	//  2.90us
		  __enable_irq();


			break;
		case 3:			
	    __disable_irq();		
		  REG_Period_check();//max 7.8us
	    __enable_irq();
 
			break;
		case 4:
	    __disable_irq();		
		RAM_Period_check();	//6.68us 
		  __enable_irq();	
			break;

		default:
			break;
	}
	if(checkindex<4)
		checkindex++;
	else
		checkindex = 0;
	 if(microCheck.check_err_flg)  //任何自检故障都要停机
	 {
	    PWMOutputs(DISABLE);
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
	 microCheck.ram_err_numb = 0;
	 microCheck.ram_index = 0;
	 microCheck.rom_err_numb = 0;
	 microCheck.rom_index = 0;
	 microCheck.rom_cnt = 0;
	 microCheck.reg_err_numb = 0;
	 microCheck.reg_index = 0;
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
				Code_Selftest_Buf[0] = u32SafteyCrcBuff[0];
				Code_Selftest_Buf[1] = 1;   //March C+自检有错误，flash该区域写1 
				
				__disable_irq();
				
        erase_flag = 0x9A0D361F;   //写擦除密码
				
        EraseSector(SAFTEY_MEMORY_ADDR,0);
				
        progm_flag = 0x9AFDA40C;   //写编程密码
				
				ProgramPage(SAFTEY_MEMORY_ADDR, 512, (unsigned char*) (&Code_Selftest_Buf[0]),0);	

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
	 if(u32SafteyCrcBuff[1] == 1)
	 {
	   microCheck.check_err_flg |= MARCHC_ERROR;
	 }
}

/*******************************************************************************
 函数名称：   void flash_check_init(void)
 功能描述：   flash初始化自检
 函数功能：   只在第一次上电对flash指定区间进行crc校验，并将校验结果存储到指定的flash地址，
              后续每次初始化时将该结果读出，并该结果做为flash周期自检结果是否正确的判断条件

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/

void flash_check_init(void)
{
	 u32 flashcrctemp;
	 if( (u32SafteyCrcBuff[0] != 0x5A5A5A5A) && (u32SafteyCrcBuff[0] != 0xFFFFFFFF))
	 {
			microCheck.goldenCRC_flash = u32SafteyCrcBuff[0];
	 }
	 else
	 {   
      	 
			REG32(CRC_RESULT_BUFFER) = 0;
			flashcrctemp = crc_flash_block_init(0x00000000, SAFTEY_MEMORY_ADDR, CRC_RESULT_BUFFER);
			microCheck.goldenCRC_flash = crc_flash_block_init(SAFTEY_MEMORY_ADDR+CRC_SECTOR_SIZE, (FLASH_SIZE-(CRC_SECTOR_SIZE+SAFTEY_MEMORY_ADDR)), CRC_RESULT_BUFFER);//0x200 = 512字节 留作存放crc

		 	REG32(CRC_RESULT_BUFFER) = 0;			 
			
			Code_Selftest_Buf[0] = microCheck.goldenCRC_flash;
			Code_Selftest_Buf[1] = u32SafteyCrcBuff[1];
			
			__disable_irq();
		  erase_flag = 0x9A0D361F;   //写擦除密码
      EraseSector(SAFTEY_MEMORY_ADDR,0);		 
		  progm_flag = 0x9AFDA40C;   //写编程密码
			ProgramPage(SAFTEY_MEMORY_ADDR, 512, (unsigned char*) (&Code_Selftest_Buf[0]),0);	
		
		
			//__enable_irq(); 
						
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
void GPIO_Check(void)
{		
  GPIO2_PIE |= BIT10;       /* P2.12开启输入输出使能 */
	GPIO2_POE |= BIT10;
	
	GPIO2_PDO |= BIT10;        /* P2.12输出高电平 */
	
	SoftDelay(10);
	
	if(microCheck.Insert_err_flg & GPIO_IN_ERROR)
	{
    GPIO2_PDO &= ~BIT10;     /*插入故障*/
	}
	
	if(GPIO2_PDI & BIT10)    /* 若输入寄存器判断为低电平，则GPIO异常 */
	{
	  microCheck.check_err_flg &= ~GPIO_IN_ERROR;	
	}
	else
	{
	  microCheck.check_err_flg |= GPIO_IN_ERROR;
	}
	
	GPIO2_PDO &= ~BIT10;	    /* P2.12输出低电平 */

	if(microCheck.Insert_err_flg & GPIO_OUT_ERROR)
	{
    GPIO2_PDO |= BIT10;      /*插入故障*/
	}	
	
  SoftDelay(10);
	
	if(GPIO2_PDI & BIT10)    /* 若输入寄存器判断为高电平，则GPIO异常 */
	{
	 microCheck.check_err_flg |= GPIO_OUT_ERROR;			
	}
	else
	{
	 microCheck.check_err_flg &= ~GPIO_OUT_ERROR;	
	}
	
	GPIO2_PIE &= ~BIT10;     /* 关闭P2.12输入输出使能 */
	GPIO2_POE &= ~BIT10;	

}
/*******************************************************************************
 函数名称：    void PC_Check(void)
 功能描述：    PC指针自检
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
#pragma push
#pragma O0
unsigned char __attribute__((section(".ARM.__at_0x7FFE"))) PC_TEST1(void)
{
	volatile unsigned char result1;
	result1 = 0x0a;
	return result1;
}

unsigned char __attribute__((section(".ARM.__at_0x800E")))PC_TEST2(void)
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
#pragma pop
/*******************************************************************************
 函数名称：    void Interrupt_Check(void)
 功能描述：    中断自检
 函数功能：    检测是否正常进中断，500us的timer中断，62.5us的ADC中断，每进200次timer中断大概进1600次ADC中断，
               如果大于1920次或者小于1280次则表明进中断的时机不对，中断异常

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 2024/01/30      V1.1          石苏新              修改
 *******************************************************************************/
void Interrupt_Check(void)
{
	if(microCheck.Interrupt_TIMER_cnt>=200)
	{
		  microCheck.Interrupt_cnt = microCheck.Interrupt_ADC_cnt;

			if((microCheck.Interrupt_cnt > 1920) || (microCheck.Interrupt_cnt < 1280))//±20% 1600 16k
			{
				microCheck.check_err_flg |= INTERRUPT_ERROR;
			}
			else
			{
				microCheck.check_err_flg &= ~INTERRUPT_ERROR;
			}	
  		microCheck.Interrupt_ADC_cnt = 0;					   
		microCheck.Interrupt_TIMER_cnt=0;
	
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
    volatile s32 t_vss, t_temp;

    __disable_irq();
	  SYS_WR_PROTECT = 0x7A83;
	  SYS_AFE_REG1 &= ~BIT4;  /* ADC以5V为基准 */
    SYS_WR_PROTECT = 0xCAFE;	
	
    ADC0_CFG = 0;	
    ADC0_CFG |=  BIT0|BIT2;    //32767 注意左右对齐 左对齐量程32767 右对齐量程 2048 

	  if((ADC0_CFG & BIT0) == 0)//左右对齐校正
    {
        ADC0_DC_A0 = Read_Trim(0x00000310) << 4 ;
        ADC0_DC_A1 = Read_Trim(0x00000314) << 4 ;
        ADC0_DC_B0 = Read_Trim(0x00000320) << 4 ;
        ADC0_DC_B1 = Read_Trim(0x00000324) << 4 ;
        
    }
    else
    {

        ADC0_DC_A0 = Read_Trim(0x00000310);
        ADC0_DC_A1 = Read_Trim(0x00000314);
        ADC0_DC_B0 = Read_Trim(0x00000320);
        ADC0_DC_B1 = Read_Trim(0x00000324);
    }
    for(t_ADC_dlay = 0; t_ADC_dlay < 100; t_ADC_dlay++);
	
	  t_vss = 0; 
	  t_temp = 0;
		
    //ADC0_GAIN0=1<<1;
    ADC0_CHN0 = (ADC_CHANNEL_19) | (ADC_CHANNEL_18 << 8);  //ADC_CHANNEL_19内部GND  ADC_CHANNEL_18内部温度传感器
    ADC0_IF = 0x1f;
    ADC0_SWT = 0x00005AA5;  //软件触发

    for (t_ADC_cnt = 0; t_ADC_cnt < 512; t_ADC_cnt++)
    {
        while((ADC0_IF & BIT0) == 0)
				{
					;
				}
        ADC0_IF = BIT1 | BIT0;

				t_vss  += (s16)((ADC0_DAT0));
				t_temp += (s16)((ADC0_DAT1));

        ADC0_SWT = 0x00005AA5;
    }

	  microCheck.VSS_ADC  = (s16)(t_vss >> 9);
	  microCheck.TEMP_ADC = (s16)(t_temp >> 9);	
	
		if((microCheck.TEMP_ADC > 670) || (microCheck.TEMP_ADC < 430) || (microCheck.VSS_ADC > 25) || (microCheck.VSS_ADC < -25))
		{/*右对齐时，Temp = -0.6032x + 364.96, 芯片工作温度-40 - 105度，对应ADC为 670 - 430，GND偏差0.05V以内，对应正常ADC范围为-25 - 25*/
			microCheck.check_err_flg |= ADC_ERROR;	
		}
		
    SYS_WR_PROTECT = 0x7A83;
    ADC0_init();
	  SYS_WR_PROTECT = 0xCAFE;

    //__enable_irq();

}
/*******************************************************************************
 函数名称：    void ADC_Period_Check(void)
 功能描述：    ADC周期自检
 函数功能：    程序运行过程中检测芯片内部GND和温度传感器的电压，电压超出范围检测失败

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0          李四龙              创建
 *******************************************************************************/
void ADC_Period_Check(void)//ADC左对齐
{
	microCheck.TEMP_ADC = GET_MCU_TEMP;
	microCheck.VSS_ADC	= GET_UVSS_VOLT;
	if(((microCheck.TEMP_ADC>>4) > 670) || ((microCheck.TEMP_ADC>>4) < 430) || (microCheck.VSS_ADC > 445) || (microCheck.VSS_ADC < -445))
	{/*Temp = -0.6032x + 364.96, 芯片工作温度-40 - 105度，对应ADC为 670 - 430，GND偏差0.05V以内，对应正常ADC范围为-25 - 25*/
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
volatile u8 GPIO_state,Old_GPIO_state,High_filter_cnt,Low_filter_cnt,LRC_Period_cnt;

void CLOCK_Check(void)
{
	u16 c_dlay;

	__disable_irq();
	PWMOutputs(DISABLE);
	GPIO1_PIE = BIT4;/*P1.4设置成输入输出状态,注意P1.4同时可复用为PWM输出，要注意空闲电平，此时应关闭PWM*/
	GPIO1_POE = BIT4;
	GPIO1_F7654 = BIT0;/*P1.4设置成AF1的LRC时钟功能*/
	
	for(c_dlay = 0; c_dlay < 100; c_dlay++); /*配置好IO口后延时等IO口状态稳定*/
	
	UTIMER_CFG |= BIT7;             //开启timer3使能

	UTIMER_UNT3_TH = 96000000;    //设置timer3计数门限值
	UTIMER_UNT3_CNT = 0;            //清零timer0计数器
	LRC_Period_cnt = 0;
	
  while(LRC_Period_cnt < 22)
  {
    if(GPIO1_PDI & BIT4)
		{
			Low_filter_cnt = 0;
		  if(High_filter_cnt < 2)
		  {
		    High_filter_cnt++;
		  }
			else
			{
			  GPIO_state = 1;
			}
		
		
		}
		else
		{
		  High_filter_cnt = 0;
			
		  if(Low_filter_cnt < 2)
		  {
		    Low_filter_cnt++;
		  }
			else
			{
			  GPIO_state = 0;
			}		
		}
		
		if(GPIO_state != Old_GPIO_state)
		{//低电平变成高电平时刻
			if(GPIO_state == 1)
			{
			  LRC_Period_cnt++;
				
				if(LRC_Period_cnt == 2)//前两次舍去
				{
				  UTIMER_UNT3_CNT = 0;
				}
				if(LRC_Period_cnt == 22)//取20次LRC周期的时间
				{
				  microCheck.Timer_Cnt = UTIMER_UNT3_CNT;
				}				
			}		
		}
   
    Old_GPIO_state = GPIO_state;
 
  }
	
  GPIO1_PIE &= ~BIT4;
	GPIO1_F7654 &= ~BIT1;	//关闭LRC复用
  GPIO_init(); 
  UTIMER_CFG &= ~BIT7;	//关闭timer3使能

  microCheck.LRC_frequency  = 1000000000/(microCheck.Timer_Cnt * 10.4f/20);   //根据时间算出LRC时钟频率	
	
	if(microCheck.Insert_err_flg & CLOCK_ERROR)
	{
	   microCheck.LRC_frequency = 15000;
	}
	
	if((microCheck.LRC_frequency < 16000) || (microCheck.LRC_frequency > 48000))
	{//LKS08x低速时钟全温度范围内16000hz-48000hz
	  microCheck.check_err_flg |= CLOCK_ERROR;	
	}
  else
	{
	  microCheck.check_err_flg &= ~CLOCK_ERROR;	
	}		
	PWMOutputs(DISABLE);
	//__enable_irq();

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
	  SYS_WatchDogCmd(ENABLE); //使能看门狗	
	  SYS_FeedDog(1);//3:间隔2s ;2:间隔4S; 1：间隔8s; 0:间隔64s	//喂狗，设置间隔时间			
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
	  SYS_FeedDog(1);
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
			
			  erase_flag = 0x9A0D361F;   //写擦除密码
			
        EraseSector(ROM_INSERT_ERR_ADDR,0);
			
        progm_flag = 0x9AFDA40C;   //写编程密码
			
			  ProgramPage(ROM_INSERT_ERR_ADDR, 512, (unsigned char*) (&t_ROMBuf[0]),0);	
			
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
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
u32 crc_flash_block(u32 flash_start_addr, u32 size, u32 crc_result_buffer_addr)
{ 
    unsigned int i;

    CRC_CR  = 0x0001;                          // CRC计算的数据来源选择CRC_INIT

    CRC_INIT = REG32(crc_result_buffer_addr);  //恢复上次校验的结果到CRC_INIT

    //有些生成多项式的简记式中将生成多项式的最高位 1 省略了，crc_pol是0x13, 但真正的多项式是x^8 + x^4 + x + 1
    CRC_POL = 0x00000013;
   
    i = 0;
    while(i<size)
	  {       
        REG32(CRC_BASE) = REG32(flash_start_addr+i);
        i = i + 4;                              //每次校验4个字节
    }
   
    REG32(crc_result_buffer_addr) = CRC_DR;     //将crc结果保存到指定的RAM地址，以便进一步进行flash crc计算
    return CRC_DR;
}

u32 crc_flash_block_init(u32 flash_start_addr, u32 size, u32 crc_result_buffer_addr)
{ 
    unsigned int i;

    CRC_CR  = 0x0001;                          // CRC计算的数据来源选择CRC_INIT

    CRC_INIT = REG32(crc_result_buffer_addr);  //恢复上次校验的结果到CRC_INIT

    //有些生成多项式的简记式中将生成多项式的最高位1 省略了，crc_pol是0x13, 但真正的多项式是x^8 + x^4 + x + 1
    CRC_POL = 0x00000013;
   
    i = 0;
    while(i<size)
	  {       
        REG32(CRC_BASE) = REG32(flash_start_addr+i);
        i = i + 4;                              //每次校验4个字节
    }
   
    REG32(crc_result_buffer_addr) = CRC_DR;     //将crc结果保存到指定的RAM地址，以便进一步进行flash crc计算
    return CRC_DR;
}



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
	 {
	   if(microCheck.reg_index < TEST_PART1_NUMS)
		 {
			 if(Micro_checkREG(microCheck.reg_index) != 0xcc)  //error
			 {
					microCheck.reg_err_numb = microCheck.reg_index;			 
				  microCheck.error_state |= BIT0;
			 }
			 microCheck.reg_index++;		 
			 
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
			  microCheck.reg_index = 0;
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

	
	  if(microCheck.ram_index < TEST_PART2_NUMS) 
		{
			 if(0xcc != occupied_halfword_scan(0x20000000 + (microCheck.ram_index << 1)))  //error
			 {
				  microCheck.ram_err_numb = microCheck.ram_index;
					microCheck.error_state |= BIT1;
			 }
			 microCheck.ram_index++;				
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
			 microCheck.ram_index = 0;

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
		if(microCheck.rom_cnt < TEST_PART3_NUMS)
		{		
			 if(microCheck.rom_index==(SAFTEY_MEMORY_ADDR>>2))
				 microCheck.rom_index = (SAFTEY_MEMORY_ADDR>>2)+(CRC_SECTOR_SIZE>>2);
			 microCheck.crc_check = crc_flash_block((microCheck.rom_index << 2),0x04,CRC_RESULT_BUFFER);	
			 microCheck.rom_index++;	
			 microCheck.rom_cnt++;	
			 
		}
		else
		{
		
			 if(microCheck.crc_check  != microCheck.goldenCRC_flash)  //周期自检结果与整体自检结果若不一致，flash被篡改，测试fail
			 {
	 			 microCheck.rom_err_numb = microCheck.rom_index;			 
				 microCheck.check_err_flg |= ROM_ERROR;	
			 }
			 else
			 {
				 microCheck.check_err_flg &= ~ROM_ERROR;	
			 }										
			 
			 microCheck.crc_check = 0;			 //crc周期自检结果清零
			 REG32(CRC_RESULT_BUFFER) = 0;   //周期自检一轮结束后清零存储CRC结果的RAM地址里的数据
			 microCheck.rom_index = 0;
			 microCheck.rom_cnt = 0;

			 		
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
				case 30:
					scan_result = APSR_scan();
					break;
				case 31:
					scan_result = PRIMASK_scan();
				break;
				default:
					scan_result = 0xcc;
					break;
			}
			return scan_result;
			
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
