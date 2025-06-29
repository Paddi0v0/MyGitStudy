#include "UART.h"

u8 UART_Flag = 1; //UART发送完成标志位

/*****************  发送一个字节 **********************/
void UART0_SendByte(uint8_t ch)
{
   UART_Flag = 1;
   UART0->BUFF = ch;
	 while(UART_Flag);
}

/****************** 发送8位的数组 ************************/
void UART0_SendArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	UART_Flag = 1;
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
		   UART_Flag = 1;
	     UART0->BUFF = array[i];	
		   while(UART_Flag);
  }
}

/*****************  发送字符串 **********************/
void Usart_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
		   UART_Flag = 1;
       UART0->BUFF = *(str + k);
       k++;
		   while(UART_Flag);//判断发送是否完成
  } while(*(str + k)!='\0');
  
 
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	UART_Flag = 1;
	UART0_SendByte(temp_h);	
	while(UART_Flag);
	
	/* 发送低八位 */
	UART_Flag = 1;
	UART0_SendByte(temp_l);	
	while(UART_Flag);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		UART_SendData(UART0, (uint8_t) ch);	
//		/* 等待发送完毕 */
		 while(!(UART0_STT&BIT0));		
	
		return (ch);
}


