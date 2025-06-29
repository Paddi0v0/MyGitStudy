#include <STC89C5xRC.H>
#include <intrins.h>


/*
void Delay1ms(unsigned int n) {
    while(n--) {
        unsigned char i = 3, j = 215;  // 
        do {
            while(--j);
        } while(--i);
    }
}
*/
bit flag_1ms = 0;

void Timer0_Init() {
    TMOD |= 0x02;     // 定时器0，模式2（8位自动重装）
    TH0 = 0xFD;       // 初值（11.0592MHz 下 1ms）
    TL0 = 0xFD;
    ET0 = 1;          // 开中断
    EA = 1;
    TR0 = 1;          // 启动定时器
}

void Delay1ms(unsigned int n) {
    unsigned int i;
    for(i = 0; i < n; i++) {
        flag_1ms = 0;
        while(!flag_1ms);  // 等待1ms
    }
}

// 中断服务程序
void Timer0_ISR(void) interrupt 1 {
    flag_1ms = 1;
}

void main()
{
    while (1)
    {
        P20 = ~P20;
        Delay1ms(500);
        // Code
    }
}

