
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

const int32_t test_data_array[64] = 
{
        0x0, //
        0x0, //
        0x0, //
        0x0, //
        0x0, //
        0x0, //
        0x0, //
        0x0, //
        0x0, //
        0x0, //

        256, // 10 Ba
        -710,
        773,
        -385,
        74,
        0x00000000,
        0x3A, // 16 Bb
        0xEA,
        0x15E,
        0xEA,
        0x3A,
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
        0x00000008, // 58 shift factor for a*d
        0x0000000f, // 59 shift factor for b*d
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000};

const uint16_t test_code_array[512] = {
        0x0000b206,
        0x0000b1c5,
        0x0000b183,
        0x0000b142,
        0x00000000,
        0x0000a628,
        0x0000a390,
        0x00000018,
        0x000040ea,
        0x0000b107,
        0x00000000,
        0x0000a510,
        0x000040ea,
        0x0000a5d0,
        0x0000a4d8,
        0x000041d3,
        0x0000b087,
        0x00000000,
        0x0000a358,
        0x0000a138,
        0x000041d3,
        0x0000a598,
        0x0000a328,
        0x000041dd,
        0x0000b0c7,
        0x00000000,
        0x0000a4a8,
        0x0000a0b8,
        0x000041dd,
        0x0000b602,
        0x0000b5c3,
        0x00000000,
        0x0000a550,
        0x0000a458,
        0x000041d3,
        0x0000b107,
        0x00000000,
        0x0000a2d8,
        0x0000a0f8,
        0x000041d3,
        0x0000b582,
        0x00000000,
        0x0000ae90,
        0x000020bf,
        0x0000a790,
        0x000011da,
        0x0000b543,
        0x00000000,
        0x0000a410,
        0x0000a138,
        0x000041da,
        0x0000aed0,
        0x000020bf,
        0x0000bfc7,
        0x0000e000,
        0x00000000,
        0x0000a150,
        0x0000a198,
        0x0000a1e8,
        0x0000a230,
        0x0000c800,
        0x00000000,
        0x00000000,
        0x00000000,
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
