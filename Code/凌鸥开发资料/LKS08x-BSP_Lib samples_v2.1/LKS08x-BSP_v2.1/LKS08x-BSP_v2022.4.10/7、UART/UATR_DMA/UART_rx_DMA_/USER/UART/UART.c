#include "UART.h"

u8 UART_Flag = 1; //UART������ɱ�־λ

/*****************  ����һ���ֽ� **********************/
void UART0_SendByte(uint8_t ch)
{
   UART_Flag = 1;
   UART0->BUFF = ch;
	 while(UART_Flag);
}

/****************** ����8λ������ ************************/
void UART0_SendArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	UART_Flag = 1;
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
		   UART_Flag = 1;
	     UART0->BUFF = array[i];	
		   while(UART_Flag);
  }
}

/*****************  �����ַ��� **********************/
void Usart_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
		   UART_Flag = 1;
       UART0->BUFF = *(str + k);
       k++;
		   while(UART_Flag);
  } while(*(str + k)!='\0');
  
 
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	UART_Flag = 1;
	UART0_SendByte(temp_h);	
	while(UART_Flag);
	
	/* ���͵Ͱ�λ */
	UART_Flag = 1;
	UART0_SendByte(temp_l);	
	while(UART_Flag);	
}

