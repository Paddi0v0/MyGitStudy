
#include "lks32mc07x_lib.h"

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
    0x0,     //        0xD9,
    0x0,     //        0xBD,
    0x0,     //        0xBC,
    0x0,     //        0x0,
    0x0,     //        0x9C,
    0x0,     //        0x144,
    0x0,     //        0x147,
    0x0,     //        0x0,
    0x0,     //        0xFFFFFD93,
    0x0,     //        0xFFFFFB5B,
    0x0,     //        0xFFFFFB8D,     //10
    0x00272, //        0x0,
    0x00d0a, //        0x8C9,
    0x01d8d, //        0x139E,
    0x025ef, //        0x1C9A,
    0x0,     //        0x2018,         //15
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0000000f, // shift factor
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000};

const uint16_t test_code_array[512] = {
    0x0000b301,
    0x0000b2c6,
    0x0000b285,
    0x0000b243,
    0x0000b202,
    0x00000000,
    0x0000a510,
    0x0000b1c2,
    0x00000000,
    0x0000a738,
    0x000000bf,
    0x0000a298,
    0x00000028,
    0x0000415f,
    0x0000a6d8,
    0x0000b083,
    0x00000000,
    0x0000a550,
    0x0000b182,
    0x000000f2,
    0x0000a2c8,
    0x000041ce,
    0x0000b107,
    0x00000000,
    0x0000a6b0,
    0x0000a5b8,
    0x0000b147,
    0x0000019f,
    0x0000a310,
    0x0000a138,
    0x000041d3,
    0x0000b107,
    0x00000000,
    0x0000a650,
    0x0000a5d8,
    0x000000bb,
    0x0000b0c7,
    0x00000000,
    0x0000a348,
    0x0000a138,
    0x0000a0e8,
    0x000041cd,
    0x0000b107,
    0x00000000,
    0x0000a0b8,
    0x0000b707,
    0x0000b682,
    0x0000b6c6,
    0x00000000,
    0x0000a610,
    0x0000b642,
    0x00000000,
    0x0000aef0,
    0x0000a3a8,
    0x0000a138,
    0x000041ea,
    0x0000b107,
    0x0000b603,
    0x00000000,
    0x0000a178,
    0x0000b5c7,
    0x00000000,
    0x0000a1b8,
    0x0000b587,
    0x00000000,
    0x0000a1f8,
    0x0000b547,
    0x00000000,
    0x0000a138,
    0x000021bf,
    0x0000bfc7,
    0x0000e000,
    0x00000000,
    0x0000a210,
    0x0000a258,
    0x0000a2a8,
    0x0000a2f0,
    0x0000a308,
    0x0000c800,
    0x00000000};

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
}
void dsp_datain(int32_t val)
{
    DSP_MEM0->DATA[20] = val;
    DSP0_SC = 0x09;
}
void dsp_delay(void)
{
    // wait until irq set and dsp paused
    while (0x03 != (DSP0_SC & 0x03))
        ;
}
int32_t dsp_getexitdata(void)
{
    return DSP_MEM0->DATA[4];
}
