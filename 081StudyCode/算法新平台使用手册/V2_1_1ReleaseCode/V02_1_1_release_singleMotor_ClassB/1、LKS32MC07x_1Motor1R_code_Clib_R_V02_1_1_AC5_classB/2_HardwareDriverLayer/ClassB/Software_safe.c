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
extern volatile u32 erase_flag;
extern volatile u32 progm_flag;
Micro_check microCheck;
void SoftDelay(u32 cnt);
void ADC_init(void);
void IWDG_init(void);
extern void setClassBFault(void);
/*******************************************************************************
 函数名称：    void RAM_init_result_check(void)
 功能描述：    RAM初始化检测
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
volatile u32 Code_Selftest_Buf[2];

volatile const Software_SafteyStruct struSaftey __at(SAFTEY_MEMORY_ADDR) =
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
	IWDG_init();                 /* 看门狗初始化 */  
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
	PC_Check();              //PC指针周期自检
	ADC_Period_Check();      //ADC周期自检
	WDT_Check();             //看门狗喂狗自检
	ROM_Error_insert();      //ROM自检插入故障

	 if(microCheck.check_err_flg)  //任何自检故障都要停机
	 {
//		  power = 0;
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
               erase_flag = 0x9A0D361F;
               EraseSector(SAFTEY_MEMORY_ADDR,Flash_MAIN);
			   erase_flag = 0x00;
               progm_flag = 0x9AFDA40C;
			   ProgramPage(SAFTEY_MEMORY_ADDR, 512, (unsigned char*) (&Code_Selftest_Buf[0]),Flash_MAIN);	
               progm_flag = 0;
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

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/

void flash_check_init(void)
{
	SYS_WR_PROTECT = 0x7a83;
	SYS_CLK_FEN |= BIT16; //CRC模块时钟使能
	SYS_WR_PROTECT = 0;
	
	 if(struSaftey.crc_golden != 0)
	 {
			microCheck.goldenCRC_flash = struSaftey.crc_golden;
	 }
	 else
	 {   
      	 
			REG32(CRC_RESULT_BUFFER) = 0;
			microCheck.goldenCRC_flash = crc_flash_block(0x00000000, FLASH_CRC_SIZE, CRC_RESULT_BUFFER);
		 	REG32(CRC_RESULT_BUFFER) = 0;			 
			
			Code_Selftest_Buf[0] = microCheck.goldenCRC_flash;
			Code_Selftest_Buf[1] = struSaftey.MarchC_result;
			
			__disable_irq();
		
            erase_flag = 0x9A0D361F;
            EraseSector(SAFTEY_MEMORY_ADDR,Flash_MAIN);
			erase_flag = 0;
            progm_flag = 0x9AFDA40C;
			ProgramPage(SAFTEY_MEMORY_ADDR, 512, (unsigned char*) (&Code_Selftest_Buf[0]),Flash_MAIN);	
            progm_flag = 0;		 
		
			__enable_irq(); 
						
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
    GPIO2_PIE |= BIT3;       /* P2.3开启输入输出使能 */
	GPIO2_POE |= BIT3;
	
	GPIO2_PDO |= BIT3;      /* P2.3输出高电平 */
	
	SoftDelay(10);
	
	if(microCheck.Insert_err_flg & GPIO_IN_ERROR)
	{
      GPIO2_PDO &= ~BIT3;     /*插入故障*/
	}
	
	if(GPIO2_PDI & BIT3)    /* 若输入寄存器判断为低电平，则GPIO异常 */
	{
	  microCheck.check_err_flg &= ~GPIO_IN_ERROR;	
	}
	else
	{
	  microCheck.check_err_flg |= GPIO_IN_ERROR;
	}
	
	GPIO2_PDO &= ~BIT3;	    /* P2.3输出低电平 */

	if(microCheck.Insert_err_flg & GPIO_OUT_ERROR)
	{
      GPIO2_PDO |= BIT3;      /*插入故障*/
	}	
	
    SoftDelay(10);
	
	if(GPIO2_PDI & BIT3)    /* 若输入寄存器判断为高电平，则GPIO异常 */
	{
	 microCheck.check_err_flg |= GPIO_OUT_ERROR;			
	}
	else
	{
	 microCheck.check_err_flg &= ~GPIO_OUT_ERROR;	
	}
	
	GPIO2_PIE &= ~BIT3;     /* 关闭P2.3输入输出使能 */
	GPIO2_POE &= ~BIT3;	

}
/*******************************************************************************
 函数名称：    void PC_Check(void)
 功能描述：    PC指针自检
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/30      V1.0           李四龙               创建
 *******************************************************************************/
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
/*******************************************************************************
 函数名称：    void Interrupt_Check(void)
 功能描述：    中断自检
 函数功能：    检测是否正常进中断，500us的timer中断，66us的ADC中断，每进一次timer中断大概进8次ADC中断，
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
    volatile s32 t_vss, t_temp;

    DAC_InitTypeDef DAC_InitStre;
    DAC_StructInit(&DAC_InitStre);                /* DAC结构体初始化 */
	
	DAC_InitStre.DAC_GAIN = DAC_RANGE_1V2;      /*DAC输出量程为4.85V*/
	DAC_InitStre.DACOUT_EN = DISABLE;				/*使能DAC输出到P0.0*/
	DAC_InitStre.TIG_CH_EN = DISABLE; 		    /*使能UTIMER触发*/
	DAC_InitStre.DAC_STEP = 0;				    /*步进值为0*/
	DAC_Init(DAC_Channel_1,&DAC_InitStre);       /* DAC初始化 */

	DAC_Cmd(DAC_Channel_1,ENABLE);				/*使能DAC时钟*/
        
	DAC_OutputValue(DAC_Channel_1,2048);
	 
    __disable_irq();	
	
    ADC0_TRIG = 0;		
    ADC0_CFG |= BIT11;  

    for(t_ADC_dlay = 0; t_ADC_dlay < 100; t_ADC_dlay++);
	
	  t_vss = 0; 
	  t_temp = 0;
		
    ADC_CHN_GAIN_CFG(ADC0,CHN0,ADC_CHANNEL_15,ADC_GAIN3V6);

    ADC0_IF = 0x1f;

    ADC0_SWT = 0x00005AA5;

    for (t_ADC_cnt = 0; t_ADC_cnt < 512; t_ADC_cnt++)
    {
        while((ADC0_IF & BIT0) == 0)
				{
					;
				}
        ADC0_IF = BIT1 | BIT0;

				t_vss  += (s16)((ADC0_DAT0));

        ADC0_SWT = 0x00005AA5;
    }

	  microCheck.VSS_ADC  = (s16)(t_vss >> 9);
	
	
	if((microCheck.VSS_ADC > 6007) || (microCheck.VSS_ADC < 4915))
	{/*DAC1输出电压在±10%以内，0.6V电压0.54V-0.66V之间，对应ADC值为4915-6007*/
	// 改为 8000
			microCheck.check_err_flg |= ADC_ERROR;	
		}
		
    ADC_init();

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
	if((microCheck.VSS_ADC > 8000) || (microCheck.VSS_ADC < 4915))
	{/*DAC1输出电压在±10%以内，0.6V电压0.54V-0.66V之间，对应ADC值为4915-6007*/
	// 改为8000
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
	
	SYS_WR_PROTECT = 0x7a83;
	SYS_CLK_FEN |= BIT7; //UTIMER3模块时钟使能
	SYS_WR_PROTECT = 0;	

	TIMER3_CFG |= BIT31;             //开启timer3使能
	
	TIMER3_TH = 96000000;             //设置timer3计数门限值
	TIMER3_CNT = 0;                   //清零timer0计数器
		
	SYS_WR_PROTECT = 0x7a83;
		
	IWDG_CFG = 0x1;                   //开启看门狗
			
	IWDG_PSW = 0xA6B4;            //看门狗解锁
	IWDG_RTH = 0x70000;            //设置看门狗计数门限值，并将看门狗计数器清零
		
	SoftDelay(20000);       //等待看门狗计数器成功加载
				
	while(IWDG_CNT > (0x70000 - WDT_WAIT_CNT))        //看门狗计数1000次
				{
      ;
		}
   
	microCheck.Timer_Cnt =  TIMER3_CNT;	  //看门狗计数1000次，Utimer计数次数
 
	IWDG_CFG = 0x3c00;              //关闭看门狗
	

  microCheck.LRC_frequency  = 1000000000/(microCheck.Timer_Cnt * 10.4/WDT_WAIT_CNT);   //根据时间算出LRC时钟频率
	
	if(microCheck.Insert_err_flg & CLOCK_ERROR)
	{
	   microCheck.LRC_frequency = 10000;
	}
	
	if((microCheck.LRC_frequency < 16000) || (microCheck.LRC_frequency > 64000))
	{//LKS07x低速时钟全温度范围内16000hz-64000hz
	  microCheck.check_err_flg |= CLOCK_ERROR;	
	}

  TIMER3_CFG &= ~BIT31; 
//  Timer3_init();	
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
//	  SYS_EnableWatchDog();//使能看门狗	
//	  SYS_FeedDog(1);//3:间隔2s ;2:间隔4S; 1：间隔8s; 0:间隔64s	//喂狗，设置间隔时间			
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
       IWDG_Feed();//看门狗喂狗
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
			
            erase_flag = 0x9A0D361F;
            EraseSector(ROM_INSERT_ERR_ADDR,Flash_MAIN);
			erase_flag = 0;
            progm_flag = 0x9AFDA40C;
			ProgramPage(ROM_INSERT_ERR_ADDR, 512, (unsigned char*) (&t_ROMBuf[0]),Flash_MAIN);	
            progm_flag = 0;
			
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

    CRC0_CR  = 0x0001;                          // CRC计算的数据来源选择CRC_INIT

    CRC0_INIT = REG32(crc_result_buffer_addr);  //恢复上次校验的结果到CRC_INIT

    //有些生成多项式的简记式中将生成多项式的最高位1 省略了，crc_pol是0x13, 但真正的多项式是x^8 + x^4 + x + 1
    CRC0_POL = 0x00000013;
   
    i = 0;
    while(i<size)
	  {       
        REG32(CRC0_BASE) = REG32(flash_start_addr+i);
        i = i + 4;                              //每次校验4个字节
    }
   
    REG32(crc_result_buffer_addr) = CRC0_DR;     //将crc结果保存到指定的RAM地址，以便进一步进行flash crc计算
    return CRC0_DR;
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
			 microCheck.crc_check = crc_flash_block((microCheck.index << 5),0x20,CRC_RESULT_BUFFER);
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
			 REG32(CRC_RESULT_BUFFER) = 0;   //周期自检一轮结束后清零存储CRC结果的RAM地址里的数据
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
void IWDG_init(void)
	{
    IWDG_InitTypeDef IWDG_InitStruct;
    IWDG_StrutInit(&IWDG_InitStruct);
    IWDG_InitStruct.WDG_EN  = ENABLE;      //使能看门狗
    IWDG_InitStruct.RTH     = SECOND2IWDGCNT(2.0);//设置看门狗
    IWDG_InitStruct.DWK_EN  = DISABLE;     // 深度休眠定时唤醒关闭   
    IWDG_InitStruct.WTH     = 0;           // 看门狗定时唤醒时间（21位计数器，但低12恒位0）
    IWDG_Init(&IWDG_InitStruct);
    IWDG_ENABLE();                         // 开启看门狗
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
