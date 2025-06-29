#include "lks32mc07x_lib.h"

#define DSP_GPIO_P2_14  BIT15 
#define DSP_GPIO_P2_7   BIT14 
#define DSP_GPIO_P2_6   BIT13 
#define DSP_GPIO_P2_5   BIT12 
#define DSP_GPIO_P2_4   BIT11 
#define DSP_GPIO_P2_3   BIT10 
#define DSP_GPIO_P1_0   BIT9  
#define DSP_GPIO_P0_15  BIT8  
#define DSP_GPIO_P0_14  BIT7  
#define DSP_GPIO_P0_13  BIT6  
#define DSP_GPIO_P0_12  BIT5  
#define DSP_GPIO_P0_11  BIT4  
#define DSP_GPIO_P0_4   BIT3  
#define DSP_GPIO_P0_3   BIT2  
#define DSP_GPIO_P0_2   BIT1  
#define DSP_GPIO_P0_0   BIT0  

char t[256] = {0};


typedef struct
{
    __IO uint32_t CODE[512];
    __IO uint32_t null[512 - 64];
    __IO uint32_t DATA[60];
    __IO uint32_t PDI;
    __IO uint32_t BSRR;
    __IO uint32_t BRR_OP;
    __IO uint32_t RES;
} DSP_Code_TypeDef;
#define DSP_MEM0 ((DSP_Code_TypeDef *)DSP0_BASE)

const uint32_t test_data_array[64] = {
    0x00000000,  // 0
    0x00000000,  // 1
    0x00000000,  // 2
    0x00000000,  // 3
    0x00000000,  // 4
    0x00000000,  // 5
    0x00000000,  // 6
    0x00000000,  // 7
    0x00000001,  // 8
    0x00010000,  // 9
    0x000100A2,  // 115200 baud rate
    0x00090080,
    0x00000000,
    0x00000000,
};

const uint16_t test_code_array[] = {
    //-----------------------------------------------------------------------------
    0x0000f2fe,
    0x00000020,
    0x00000028,
    0x0000af88,
    0x0000f293,
    0x0000c244,
    0x000010ac,
    0x00003152,
    0x00000889,
    0x0000c07c,
    0x0000c101,
    0x0000bf46,
    0x0000bf46,
    0x0000bf46,
    0x0000c803,
    0x0000bf86,
    0x0000bf86,
    0x0000bf86,
    0x0000f291,
    0x0000c081,
    0x00001089,
    0x0000cbfd,
    0x0000d8a7,
    0x000000a4,
    0x0000cbea,
    0x0000a208,
    0x0000bc41,
    0x0000e000,
    0x00000000,
    0x00000000,
};
void dsp_uart_tx(int8_t data)
{
    DSP0_SC = BIT1;
    DSP0_SC = BIT3;
    DSP_MEM0->BRR_OP = data;
    DSP0_PC = 0;
    DSP0_SC = BIT0 | BIT8;
}
void dsp_fun_init()
{
    UINT32 i;
    SYS_ModuleClockCmd(SYS_Module_DSP0, ENABLE);
    SYS_ModuleClockCmd(SYS_Module_GPIO, ENABLE);

    DSP0_SC |= BIT1;
    DSP0_SC |= BIT3;
    // dsp data mem flush
    for (i = 0; i < 60; i += 1)
    {
        DSP_MEM0->DATA[i] = 0;
    }
    // dsp code mem flush
    for (i = 0; i < 512; i += 1)
    {
        DSP_MEM0->CODE[i] = 0;
    }
    // dsp data mem init
    for (i = 0; i < (sizeof(test_data_array) / 4); i += 1)
    {
        DSP_MEM0->DATA[i] = test_data_array[i];
    }
    for (i = 0; i < (sizeof(test_code_array) / 2); i += 1)
    {
        DSP_MEM0->CODE[i] = test_code_array[i];
    }
    {
        // 设置波特率
        // 其中23和5是固定系数
        uint32_t baud;
        uint32_t val;
        baud = 9600;
        val = (96000000 / baud - 23) / 5;
        DSP_MEM0->DATA[10] = 0x10000 | val;
    }
    {
        // 设置输出IO
        uint32_t DSP_GPIO_x;
        
        DSP_GPIO_x = DSP_GPIO_P0_14;
        DSP_MEM0->DATA[11] = 0x90000 | DSP_GPIO_x;
    }
    GPIO0_POE = BIT14;
    GPIO0_PDO = BIT14;
    NVIC_EnableIRQ(DSP0_IRQn);
    __enable_irq();

    dsp_uart_tx(0xff);
}
void DSP0_IRQHandler(void)
{
    dsp_uart_tx(0x0f);
    DSP_MEM0->DATA[0x31] = 0; // clear uart0 tx done flag

}
