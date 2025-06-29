/*******************************************************************************
 * ��Ȩ���� (
 *
 * �ļ����ƣ� GPIO_LED.c
 * �ļ���ʶ��
 * ����ժҪ�� LED��ʾ���ó���
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� 
 * ������ڣ� 2021��2��23��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�
 * �� �� �ţ�
 * �� �� �ˣ�
 * �޸����ݣ�
 *
 *******************************************************************************/

#include "gpio_led.h"
#include "delay.h"

//LED״̬��ʾ����
//mode:1,ȫ��
//     2,ȫ��
//     3,��˸
//		 4,��ˮ��
void GPIO_LED(u8 mode)
{
	 int i = 0;
   switch(mode)
	 {
	   case ALL_ON:
			    LED1_ON;
		      LED2_ON;
		      LED3_ON;
		 break;
			 
		 case ALL_OFF:
					LED1_OFF;
					LED2_OFF;
					LED3_OFF;
		 break;
			 
		 case Blink:
			  
			   for(i = 0 ; i<250 ; i++)
		      {
						LED1_ON;
						LED2_ON;
						LED3_ON;
						delay(0xffff);
		      }
				 for(i = 0 ; i<250 ; i++)
		      {	
						LED1_OFF;
						LED2_OFF;
						LED3_OFF;
						delay(0xffff);
					}
		 break;
			 
		 case waterfall_light:
			    LED1_ON;
		      LED2_OFF;
					LED3_OFF; 
		      for(i = 0 ; i<100 ; i++)
		      {
		       delay(0xffff);
					}
		      LED2_ON;
		      LED1_OFF;
					LED3_OFF; 
		      for(i = 0 ; i<100 ; i++)
		      {
		       delay(0xffff);
					}
		      LED3_ON;		    
					LED1_OFF;
					LED2_OFF;
		      for(i = 0 ; i<100 ; i++)
		      {
		       delay(0xffff);
					}
		 break;	 
	 }		 
}







