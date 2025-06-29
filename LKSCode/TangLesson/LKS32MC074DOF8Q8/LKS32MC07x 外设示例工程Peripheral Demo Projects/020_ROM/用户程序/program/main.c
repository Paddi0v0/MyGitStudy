#include <lks32mc07x.h>
volatile s16 i123;
volatile s16 j;
volatile s16 k;
typedef  s16 (*sin_fun)(u16 angle);
typedef  void (*void_fun)(void);

//    0x0001028c   0x0001028c   0x00000010   Code   RO           82    i.lks32_cos         program1.o
//    0x0001029c   0x0001029c   0x00000010   Code   RO           83    i.lks32_sin         program1.o
//    initflg                                  0x20002008   Data           4  main.o(.data)

#define rom_lks32_sin ((sin_fun)(u32 *)(0x0001028c|1))
#define rom_lks32_cos ((sin_fun)(u32 *)(0x0001029c|1))
#define rom_RESET ((void_fun)(u32 *)(0x00010000|1))
int main()
{
    i123=0;
    for(;;)
    {
        j=rom_lks32_sin(i123++);
        k=rom_lks32_cos(i123++);
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}
void SystemInit()
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_CLK_CFG = 0x000001ff; /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
    IWDG_CFG = 0x3c00;
    SYS_WR_PROTECT = 0;   /* 解除系统寄存器写保护 */
    if(REG32(0x20002008) != 0x12345678)
    {
        rom_RESET();
    }
}
