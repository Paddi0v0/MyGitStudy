#ifndef __GPIO_LED_H__
#define __GPIO_LED__H__
#include "lks32mc08x_sys.h"

#define ALL_ON 1          //全亮
#define ALL_OFF 2         //全灭
#define Blink 3           //闪烁
#define waterfall_light 4 //流水灯

/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
//LED1  P0.6
#define LED1_GPIO_PORT GPIO0            /* GPIO端口 */
#define LED1_GPIO_Mode GPIO_Mode_OUT;   /*GPIO输出模式*/
#define LED1_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO上下拉模式选择*/
#define LED1_GPIO_PIN GPIO_Pin_15       /*输出GPIO端口号*/

//LED2  P0.7
#define LED2_GPIO_PORT GPIO0            /* GPIO端口 */
#define LED2_GPIO_Mode GPIO_Mode_OUT;   /*GPIO输出模式*/
#define LED2_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO上下拉模式选择*/
#define LED2_GPIO_PIN  GPIO_Pin_7        /*输出GPIO端口号*/

//LED3  P0.3
#define LED3_GPIO_PORT GPIO0            /* GPIO端口 */
#define LED3_GPIO_Mode GPIO_Mode_OUT;   /*GPIO输出模式*/
#define LED3_GPIO_PuPd GPIO_PuPd_NOPULL /*GPIO既不上拉也不下拉*/
#define LED3_GPIO_PIN GPIO_Pin_3        /*输出GPIO端口号*/

//LED1 2 3输出低
#define LED1_OFF GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED2_OFF GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED3_OFF GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN)

//LED1 2 3输出高
#define LED1_ON GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED2_ON GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED3_ON GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN)

void GPIO_LED(u8 mode);

#endif
