#include "UART.h"

u8 UART_TXFlag = 1; //UART发送完成标志位
u8 UART_RXFlag = 0; //UART发送完成标志位
/*****************  发送一个字节 **********************/
void UART0_SendByte(uint8_t ch)
{
	 GPIO_InitTypeDef GPIO_InitStruct;
	 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_Init(GPIO0, &GPIO_InitStruct);
   UART_TXFlag = 1;
   UART0->BUFF = ch;
	 while(UART_TXFlag);
}

/****************** 发送8位的数组 ************************/
void UART0_SendArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	UART_TXFlag = 1;
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
		   UART_TXFlag = 1;
	     UART0_SendByte(array[i]);	
		   while(UART_TXFlag);
  }
}

/*****************  发送字符串 **********************/
void Usart_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
		   UART_TXFlag = 1;
       UART0_SendByte(*(str + k));
       k++;
		   while(UART_TXFlag);
  } while(*(str + k)!='\0');

}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( uint16_t ch)
{
	uint8_t temp_h, temp_l;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO0, &GPIO_InitStruct);
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	UART_TXFlag = 1;
	 UART0->BUFF = temp_h;	
	while(UART_TXFlag);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO0, &GPIO_InitStruct);
	/* 发送低八位 */
	UART_TXFlag = 1;
	UART0->BUFF = temp_l;	
	while(UART_TXFlag);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		UART_SendData(UART0, (uint8_t) ch);	
//		/* 等待发送完毕 */
		 while(UART_TXFlag);		
	
		return (ch);
}

