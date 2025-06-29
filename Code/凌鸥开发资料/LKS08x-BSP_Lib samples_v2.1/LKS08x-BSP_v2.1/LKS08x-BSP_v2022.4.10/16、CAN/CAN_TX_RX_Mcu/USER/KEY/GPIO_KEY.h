#ifndef __GPIO_KEY_H__
#define __GPIO_KEY_H__
#include "lks32mc08x_sys.h"

#define start_PRES 	1	//start按下
#define stop_PRES	2	  //stop按下


#define key_start GPIO_ReadInputDataBit(GPIO2 , GPIO_Pin_11)
#define key_stop  GPIO_ReadInputDataBit(GPIO2 , GPIO_Pin_12)

int GPIO_KEY_Scan(u8 mode);

#endif


