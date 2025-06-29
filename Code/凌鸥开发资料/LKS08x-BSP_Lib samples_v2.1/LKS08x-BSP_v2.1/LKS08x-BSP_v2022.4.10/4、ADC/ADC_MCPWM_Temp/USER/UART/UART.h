#ifndef __UART_H__
#define __UART_H__

#include "hardware_config.h"


extern u8 UART_Flag;

void UART0_SendByte(uint8_t ch);
void UART0_SendArray(uint8_t *array, uint16_t num);
void Usart_SendString(char *str);
void Usart_SendHalfWord( uint16_t ch);
int fputc(int ch, FILE *f);

//#define printf(str,value) (Usart_SendString(str),\
//                           UART0_SendByte(value))

#endif


