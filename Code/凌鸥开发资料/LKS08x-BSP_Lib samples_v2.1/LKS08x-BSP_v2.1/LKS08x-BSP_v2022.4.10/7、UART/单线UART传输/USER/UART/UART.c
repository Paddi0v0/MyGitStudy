#include "UART.h"

u8 UART_TXFlag = 1; //UART������ɱ�־λ
u8 UART_RXFlag = 0; //UART������ɱ�־λ
/*****************  ����һ���ֽ� **********************/
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

/****************** ����8λ������ ************************/
void UART0_SendArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	UART_TXFlag = 1;
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
		   UART_TXFlag = 1;
	     UART0_SendByte(array[i]);	
		   while(UART_TXFlag);
  }
}

/*****************  �����ַ��� **********************/
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

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( uint16_t ch)
{
	uint8_t temp_h, temp_l;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO0, &GPIO_InitStruct);
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	UART_TXFlag = 1;
	 UART0->BUFF = temp_h;	
	while(UART_TXFlag);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO0, &GPIO_InitStruct);
	/* ���͵Ͱ�λ */
	UART_TXFlag = 1;
	UART0->BUFF = temp_l;	
	while(UART_TXFlag);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		UART_SendData(UART0, (uint8_t) ch);	
//		/* �ȴ�������� */
		 while(UART_TXFlag);		
	
		return (ch);
}

