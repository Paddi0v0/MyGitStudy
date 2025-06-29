#ifndef __GPIO_KEY_H__
#define __GPIO_KEY_H__
#include "lks32mc08x_sys.h"

#define start_PRES 	1	//start按下
#define stop_PRES	2	  //stop按下

/* 定义KEY连接的GPIO端口 */
//START P2.11 
#define START_GPIO_PORT    	GPIO2			             /* GPIO端口 */
#define START_GPIO_Mode 	  GPIO_Mode_IN          /*GPIO输出模式*/
#define START_GPIO_PuPd     GPIO_PuPd_NOPULL       /*GPIO既不上拉也不下拉*/
#define START_GPIO_PIN		  GPIO_Pin_11			       /*输出GPIO端口号*/

//STOP  P2.12
#define STOP_GPIO_PORT    	GPIO2			             /* GPIO端口 */
#define STOP_GPIO_Mode 	    GPIO_Mode_IN          /*GPIO输出模式*/
#define STOP_GPIO_PuPd      GPIO_PuPd_NOPULL       /*GPIO既不上拉也不下拉*/
#define STOP_GPIO_PIN		    GPIO_Pin_12			       /*输出GPIO端口号*/

#define key_start GPIO_ReadInputDataBit(START_GPIO_PORT , START_GPIO_PIN)
#define key_stop  GPIO_ReadInputDataBit(STOP_GPIO_PORT , STOP_GPIO_PIN)

int GPIO_KEY_Scan(u8 mode);

#endif


