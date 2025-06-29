#ifndef _WDT_H
#define _WDT_H
#include "lks32mc08x_sys.h"

#define WDT_CLR64  0x7988 //看门狗64秒复位
#define WDT_CLR8   0x798A //看门狗8秒复位
#define WDT_CLR4   0x798C //看门狗4秒复位
#define WDT_CLR2   0x798E //看门狗2秒复位

#define WDT_CLRFeed  0x798F //复位看门狗计数器

void WDT_Init(void);
void WDT_Reset(void);

#endif

