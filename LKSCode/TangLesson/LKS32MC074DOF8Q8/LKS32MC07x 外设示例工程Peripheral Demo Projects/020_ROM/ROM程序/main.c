#include <lks32mc07x.h>
void ROM_ENABLE(void);
s16 ( lks32_sin)(u16 hAngle);
    
s16 ( lks32_cos)(u16 hAngle);
volatile u16 i123;
volatile u16 j;
volatile u16 k;
volatile u16 l;
typedef  s16 (*sin_fun)(u16 angle);
volatile sin_fun lks32_sin1;
volatile sin_fun lks32_cos1;
volatile int user_key;

// 说明 ：
// 在设计rom的程序的时候，需要保证在主函数里对所有需要用到的程序都做了一次调
// 用，以保证编译器会把程序放到rom里面，同时需要保证rom中没有对外面应用程序的引用
// 在用户区调用rom内的程序的时候，可以使用宏进行调用，也可以使用函数指针
typedef  void (*void_fun)(void);
#define rom_RESET ((void_fun)(u32 *)(0+1))
volatile int32_t initflg;
int main()
{
    j=lks32_sin(i123++);
    k=lks32_cos(i123++);
    initflg = 0x12345678;
    NVIC_SystemReset();
    for(;;);
}
void SystemInit()
{
}
