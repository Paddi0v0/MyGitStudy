#ifndef _WDT_H
#define _WDT_H
#include "lks32mc08x_sys.h"

#define WDT_CLR64  0x7988 //���Ź�64�븴λ
#define WDT_CLR8   0x798A //���Ź�8�븴λ
#define WDT_CLR4   0x798C //���Ź�4�븴λ
#define WDT_CLR2   0x798E //���Ź�2�븴λ

#define WDT_CLRFeed  0x798F //��λ���Ź�������

void WDT_Init(void);
void WDT_Reset(void);

#endif

