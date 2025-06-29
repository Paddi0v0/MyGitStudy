
#include "Global_Variable.h"
#include "MosTest.h"
#include "hardware_config.h"

void ADC_init(void);

stru_MOS_test MOS_Selftest;

s32 adcSum_old[5] = {0};


volatile s16 dbg_busCurrent;

#define MOS_SHORT_VALUE    5000  //30A
#define BUS_SHORT_VALUE    5000

 

void MosTest(void)
{
    volatile u8 i;

    MOS_Selftest.MosTest_start = 1;
    MOS_Selftest.MOSfail_flg = 0;	
	  MOS_Selftest.PWM_Setting = 400;
	
	  MOS_Selftest.Sample_Point = MOS_Selftest.PWM_Setting - 100;

    for(i = 0; i < 5; i++)
    {		
      MOS_Selftest.check_step = i;			
			MOS_Check_Step();

			MOS_Selftest.PWM_cnt = 0;
			while(MOS_Selftest.PWM_cnt < 1) {;}
			PWMOutputs(ENABLE);

			while(MOS_Selftest.PWM_cnt < 2) {;}
			PWMOutputs(DISABLE);
			
			MOS_Selftest.Bus_current[i] = ((s16)(ADC0_DAT0 - BLDC_SensorlessCtr.PeakCurrOffset));

			if((MOS_Selftest.Bus_current[i] > BUS_SHORT_VALUE) && (i < 2))
			{
				MOS_Selftest.MOSfail_flg = i;
			}
			else if(MOS_Selftest.Bus_current[i] > MOS_SHORT_VALUE)
			{
				MOS_Selftest.MOSfail_flg = i;
			} 
			
			MOS_Selftest.PWM_delay = 0;
			while(MOS_Selftest.PWM_delay < 5) {;}
			
      if((MOS_Selftest.MOSfail_flg) || (mBLDC_CtrProc.sys_error_flg))
      {
        mBLDC_CtrProc.sys_error_flg |= MOSFET_ERROR;		  
        break;
      }				
				
		}			

    MOS_Selftest.MosTest_start = 0;
    __disable_irq();
    ADC_init();
    MCPWM_init();
		ADC1_STATE_RESET();
    __enable_irq();
}


void MOS_Check_Step(void)
{
   MCPWM0_PRT = 0x0000DEAD;
	
	 switch (MOS_Selftest.check_step)
	 {
     case 0: 
		 {//上桥MOS测试：开三相下桥,关三相上桥
			 MCPWM0_IO01 = DRIVER_POLARITY | 0x0808;
			 MCPWM0_IO23 = DRIVER_POLARITY | 0x08;			 
			 break;
		 }		 
     case 1: 
		 {//下桥MOS测试：开三相上桥,关三相下桥
			 MCPWM0_IO01 = DRIVER_POLARITY | 0x0404;
			 MCPWM0_IO23 = DRIVER_POLARITY | 0x04;			 			 
			 break;
		 }
     case 2: 
		 {//测试AC相间短路：A相PWM，B相悬空，C相开下桥
			 MCPWM0_IO01 = DRIVER_POLARITY | 0x0c00;
			 MCPWM0_IO23 = DRIVER_POLARITY |0x1c;		 
			 break;
		 }		 
     case 3: 
		 {//测试AB相间短路：B相PWM，C相悬空，A相开下桥
			 MCPWM0_IO01 = DRIVER_POLARITY | 0x001c;
			 MCPWM0_IO23 = DRIVER_POLARITY | 0x0c;				 
			 break;
		 }	
     case 4: 
		 {//测试BC相间短路：C相PWM，A相悬空，B相开下桥
			 MCPWM0_IO01 = DRIVER_POLARITY | 0x1c0c;
			 MCPWM0_IO23 = DRIVER_POLARITY ;				 			 
			 break;
		 }	     		 
	 }

	 MCPWM0_TH00 = -MOS_Selftest.PWM_Setting;  /* 设置PWM输出占空比　*/
   MCPWM0_TH01 = MOS_Selftest.PWM_Setting;

   MCPWM0_TH10 = -MOS_Selftest.PWM_Setting;
   MCPWM0_TH11 = MOS_Selftest.PWM_Setting;

   MCPWM0_TH20 = -MOS_Selftest.PWM_Setting;
   MCPWM0_TH21 = MOS_Selftest.PWM_Setting;
	 
	 MCPWM0_TMR0 = MOS_Selftest.Sample_Point;

   MCPWM0_UPDATE = 0xffff;	   
	 MCPWM0_PRT = 0x0000CAFE;
	 
   ADC0_CHN0 = ADC_PEAK_CUR_CHANNEL | (ADC_PEAK_CUR_CHANNEL << 4) | ( ADC_PEAK_CUR_CHANNEL << 8) | (ADC_PEAK_CUR_CHANNEL << 12);
	 ADC1_STATE_RESET();
	 

}


