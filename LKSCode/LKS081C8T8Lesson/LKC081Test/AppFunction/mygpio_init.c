#include "mygpio_init.h"
#include "lks32mc08x_lib.h"

void GPIO_init(void)
{
    /*
需求:
点亮LED1 --> P0.6引脚,LED2 --> P0.7引脚,LED3 --> P0.3引脚.
LED1和LED2原理图都是高电平点亮,LED3原理图是低电平点亮.
在电路设计上LED1和LED2为高电平才可以点亮,所以不能配置为开漏输出,因为开漏输出默认输出是低电平.
而LED3的电路设计是低电平点亮,所以既可以输出为开漏模式,也可以设置为推挽模式,因为推挽模式既可以输出高电平,也可以输出低电平
所有LED1和LED2配置为推挽输出,LED3配置为开漏输出.
*/
    GPIO_InitTypeDef GPIO_InitStruct;

    // 配置LED1(P0.6)和LED2(P0.7) - 推挽输出
    GPIO_StructInit(&GPIO_InitStruct); // 初始化结构体

    // 配置LED1和LED2（高电平点亮）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 同时配置P0.6和P0.7
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;          // 输出模式
    // GPIO_PuPd（上拉配置）共有两种选项: 无上拉 GPIO_PuPd_NOPULL, 上拉
    // GPIO_PuPd_UP（LKS32 系列不支持内部下拉） 在输出模式（推挽/开漏）下，PUE
    // 位不会影响实际输出电平，电平由 PDO 寄存器决定。
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_PODEna = 0;    // 0是禁用开漏输出，他就是推挽输出,1是启用开漏输出
    GPIO_Init(GPIO0, &GPIO_InitStruct); // 应用配置

    // 单独配置LED3(P0.3) - 开漏输出
    GPIO_StructInit(&GPIO_InitStruct);            // 重新初始化结构体
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;        // 只配置P0.3
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;    // 输出模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // 无上拉
    GPIO_InitStruct.GPIO_PODEna = 1;              // 开漏输出
    GPIO_Init(GPIO0, &GPIO_InitStruct);           // 应用配置
}
void Led_12on(void)
{
    GPIO_SetBits(GPIO0, GPIO_Pin_6 | GPIO_Pin_7);
}
void Led_12off(void)
{
    GPIO_ResetBits(GPIO0, GPIO_Pin_6 | GPIO_Pin_7);
}
void Led_3on(void)
{
    GPIO_ResetBits(GPIO0, GPIO_Pin_3);
}
void Led_3off(void)
{
    GPIO_SetBits(GPIO0, GPIO_Pin_3);
}
