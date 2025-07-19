#include "delay.h"
#include "hardware_init.h"
#include "lks32mc08x_lib.h"
#include "mygpio_init.h"
/*
需求:
1、GPIO实验
配置GPIOX.X为输出模式，交替输出高低电平，用示波器观察;答案提交:示波器测量波形截图。
*/
int main(void)
{
    Hardware_init(); /* 硬件初始化*/
    

    while (1)
    {
        //       GPIO_WriteBit(GPIO0, GPIO_Pin_6, Bit_SET);
        Invers_GPIO(GPIO0, GPIO_Pin_6);

    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR
 * **********************/
/* ------------------------------END OF FILE------------------------------------
 */
