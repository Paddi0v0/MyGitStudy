#include <STC89C5xRC.H>

// 用定时器实现动态数码管显示
typedef unsigned char u8;
u8 code nums[] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F}; // 共阴极数码管段码表
u8 code LEDs[] = {0Xe3, 0Xe7, 0Xeb, 0Xef, 0Xf3, 0Xf7, 0Xfb, 0Xff};

void Timer0_Init()
{
    TMOD &= 0XF0; // 清除定时器0的模式位
    TMOD |= 0X01; // 设置定时器为模式1(16位定时器)
}

void Delay_10ms(unsigned int count)
{
    static const u8 TH0_VAL = 0XDC;
    static const u8 TL0_VAL = 0X00;
    unsigned int i;
    TR0 = 0; // 关闭定时器
    TF0 = 0; // 清除定时器标志位
    TH0 = TH0_VAL;
    TL0 = TL0_VAL;
    TR0 = 1; // 启动定时器
    for (i = 0; i < count; i++)
    {
        while (!TF0)
            ;
        TH0 = TH0_VAL;
        TL0 = TL0_VAL;
        TF0 = 0;
    }
    TR0 = 0; // 关闭定时器避免占用资源
}
/*
#define LEDS_LEN 8
#define NUMS_LEN 10

void main()
{
    u8 i, num_index = 0;
    Timer0_Init();
    while (1)
    {
        // 扫描8个数码管，每个都显示当前num_index对应的数字
        for (i = 0; i < LEDS_LEN; i++)
        {
            P0 = 0x00;            // 消影
            P2 &= 0xe3;           // 清零P2.2~P2.4
            P2 |= LEDs[i];        // 选中第i位
            P0 = nums[num_index]; // 显示当前数字
            Delay_10ms(1);        // 扫描速度
        }
        // 切换到下一个数字
        num_index++;
        if (num_index >= NUMS_LEN) num_index = 0;
        Delay_10ms(1); // 控制数字切换速度
    }
}
*/

void main()
{
    u8 i;
    Timer0_Init();
    while (1)
    {
        for (i = 0; i < 10; i++)
        {
            P0 = 0x00;     // 关闭段选(消影) P0 &= 0x00; 实际效果等价于 P0 = 0x00;  所以P0 &= 0x00这样写没意义
            P2 &= 0xe3;    // 关闭位选  虽然这样只是让P22,P23,P24为为0了,但是P2 = LEDs[0]直接赋值了,所以下面的P2要改成|=
            P2 |= LEDs[i]; // 开启当前位选
            P0 = nums[i];  // 设置段选
            Delay_10ms(50);
        }
    }
}
