#ifndef __MYTIMER_INIT_H
#define __MYTIMER_INIT_H
#include "lks32mc08x_lib.h"

void Timer_init(void);
void set_cmp(uint16_t value);
int getTh_Value();
#endif