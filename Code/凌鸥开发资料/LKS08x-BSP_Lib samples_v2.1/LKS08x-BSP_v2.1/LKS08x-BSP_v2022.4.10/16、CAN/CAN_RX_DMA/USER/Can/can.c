#include "can.h"
#include "lks32mc08x_Gpio.h"
#include "lks32mc08x_DMA.h"

can_parameter can_par =
{
	0x00,
	0x00,
	0x00,
	{0,0},
	{0,0},
	0x00,
};

/*******************************************************************************
��������: void CAN_Init(u8 tq,u8 tsge1,u8 tsge2)
��������: CAN��ʼ������,����2.0BЭ��
�����ı�: Can������     BTR0    	 BTR1
					1Mbps 			  0x05 		 	 0x14
					800Kbps 		  0x05			 0x16
					666Kbps 			0x85 			 0xB6
					500Kbps 			0x05       0x1C
					400Kbps 			0x05			 0xFA
					250Kbps 			0x0B 			 0x1C
					200Kbps 			0x05 			 0xFA
					125Kbps 			0x17  		 0x1C???
					100Kbps 			0x1D       0x1C
					83.33Kbps 		0x17       0x6F
					80Kbps 				0x97       0xFF
					66.66Kbps 		0x1D       0x6F
					50Kbps 				0x3B       0x1C
					40Kbps 				0xAF       0xFF
�������:  BTR0   ��Ԫ����TQ
          BTR1   ��ʱ��
			    
�������: ��
����ֵ:   ��
����˵��: 
�޸�����  �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      ����
*******************************************************************************/
void CAN_Init(u8 BTR0,u8 BTR1)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	
    __disable_irq();         // �ر��ж� �ж��ܿ���
		SYS_WR_PROTECT = 0x7a83; // ��д���� 
	
	  SYS_SFT_RST |= BIT7;     // ��λCAN
	  SYS_SFT_RST &= ~BIT7;    // �ͷ�CAN��λ
	
	  SYS_CLK_CFG = 0x01FF;    // ����ϵͳʱ��?Pѡ��PLL�������з�Ƶ96mhz*/
		SYS_CLK_FEN |= 1 << 7;   // ʹ��CANʱ���ſ�
		SYS_CLK_DIV0 = 0x0000;   // spi ����ʱ�ӷ�ƵΪ�㣬96MHZ
		FLASH_CFG |= 0x00080000; // FLASH Ԥȡ����ʹ��
	  
    /*P0.7 CAN TX*/
	  GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    /*P0.6 CAN RX*/
	  GPIO_StructInit(&GPIO_InitStruct);
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
		
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF10_CAN);	
	  GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF10_CAN);
	
		CAN_MODE |= 1 << 0;           // ��λģʽ
  
	  CAN_BTR0 = BTR0;     // ���������ã�����CAN�������ʱ�䵥Ԫ����TQ
	  CAN_BTR1 = BTR1;     // SEG1 ��ʱ��

	  CAN_CMR |= (1 << 5);            //ʹ��DMA���书��
		
	  CAN_MODE &= ~(1 << 0);          //�������ģʽ
	 
  	CAN_INTR_EN |= 1 << 0;          //RFIFO���µ����ݱ����յ����ж�Դʹ��
	  CAN_INTR_EN |= 1 << 1;					//������ϵ�ǰ֡���ж�Դʹ��
	  CAN_INTR_EN |= 1 << 2;					//CAN_SR.7 ���� CAN_SR.6 �б仯���ж�Դʹ��
	  CAN_INTR_EN |= 1 << 3;					//RFIFO ���ݷ���������ж�Դʹ��
	  CAN_INTR_EN |= 1 << 5;					//�����������״̬��������ǳ��涨ֵ���ж�Դʹ��
	  CAN_INTR_EN |= 1 << 6;					//��ʧ�ٲã��ĳɽ���ģʽ���ж�Դʹ��
	  CAN_INTR_EN |= 1 << 7;					//���ߴ����жϣ��ж�Դʹ��
}


/*******************************************************************************
��������:  void  SFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr,
                           u8 Byte1_acr,u8 Byte1_amr,u8 Byte2_acr,u8 Byte2_amr)
��������:  CAN��׼֡��ID����,����2.0BЭ��
�����ı�:  ��
�������: acr: IDֵ��
          amr������λ
          ��׼֡  11λID����
          rtr_acr: ���գ�1Զ��/0��־֡��֡����ѡ��
          rtr_amr�� Զ��/����֡�˲�����λ��0��ʾֻ����rtr_acr����֡��Ϊ1��ʾԶ��/0��־֡������
          Byte1_acr�����ݵ�һ���ֽ�
          Byte1_amr����һ���ֽ�����λ
          Byte2_acr�����ݵڶ����ֽ�
          Byte2_amr���ڶ����ֽ�����λ         
�������: ��
����ֵ:   ��
����˵��: 
�޸�����  �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      ����
*******************************************************************************/
 void SFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr,u8 Byte1_acr,u8 Byte1_amr,u8 Byte2_acr,u8 Byte2_amr)
{ 
	  CAN_MODE |= 1 << 0;             // ��λģʽ
	  CAN_MODE |= 1 << 3;             // ���˲�ID,һ�� 32 λ�����˲�ID
	
		acr &= 0x7ff;
		amr &= 0x7ff;
		
	  rtr_acr &= 0x1;
		rtr_amr &= 0x1;
	
		CAN_ACR0 = (u8)(acr >> 3);
		CAN_ACR1 = (u8)(acr << 5)|(rtr_acr << 4);
		CAN_ACR2 = Byte1_acr;
		CAN_ACR3 = Byte2_acr;
    
		CAN_AMR0 = (u8)(amr >> 3);
		CAN_AMR1 = (u8)(amr << 5) |(rtr_amr << 4) | 0x0f;
		CAN_AMR2 = Byte1_amr;
		CAN_AMR3 = Byte2_amr;
	
	  CAN_MODE &= ~(1 << 0);          //�������ģʽ
	
}
/*******************************************************************************
��������:  void EFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr)
��������: CAN��չ֡��ID����,����2.0BЭ��
�����ı�: ��
�������: acr��IDֵ��
          amr������λ
       
          rtr_acr�� ���գ�1Զ��/0����֡��֡����ѡ��
          rtr_amr�� Զ��/����֡�˲�����λ��0��ʾֻ����rtr_acr����֡��Ϊ1��ʾԶ��/0��־֡������

          ide��0��׼/1��չ֡
�������: ��
����ֵ:   ��
����˵��: 
�޸�����  �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      ����
*******************************************************************************/
 void EFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr)
{ 
	  CAN_MODE |= 1 << 0;             // ��λģʽ
	  CAN_MODE |= 1 << 3;             // ���˲�ID,һ�� 32 λ�����˲�ID
	 
		acr &= 0x1fffffff;
		amr &= 0x1fffffff;
	  rtr_acr &= 0x1;
		rtr_amr &= 0x1;
	
		/*�ɽ��յ�ID�Ĵ�����������֡�� ID ͬ��ƥ�䣬�� CAN ģ�����
		  ��� AMR �Ĵ�������ͬһ�� ID ƥ�䡣*/
		CAN_ACR3 = (u8)(acr << 3)|(rtr_acr << 2); 
		CAN_ACR2 = (u8)(acr >> 5);
		CAN_ACR1 = (u8)(acr >> 13);
		CAN_ACR0 = (u8)(acr >> 21);
	 /*��� ACR �Ĵ�����ͬ���� ID ����ƥ�䡣AMR �Ĵ���ĳһλΪ 0����ʶ
     ID ��Ӧλ��Ҫͬ ACR ƥ�䣻Ϊ 1����ʶ ID ��Ӧλ����Ҫͬ ACR ƥ��*/
		CAN_AMR3 = (u8)((amr << 3)|(rtr_amr << 2)|0x03);
		CAN_AMR2 = (u8)(amr >> 5);
		CAN_AMR1 = (u8)(amr >> 13);
		CAN_AMR0 = (u8)(amr >> 21);
	
	  CAN_MODE &= ~(1 << 0);          //�������ģʽ
}

/*******************************************************************************
��������:  void  ID1_Filter_Dual(u32 acr1 ,u32 amr1,u8 rtr_acr1,
                               u8 rtr_amr1,u8 Byte_acr1,u8 Byte_amr1,u8 ide)
                   
��������: CAN˫ID������ID1�˲����� ����2.0BЭ��
�����ı�: ��
�������:  acr1��ID1ֵ����Χ1D28~ID13��ID��16λ��Ч��   amr1��ID1����λ  ide��0��׼/1��չ֡
          
          rtr_acr��  ���գ�1Զ��/0����֡��֡����ѡ��ֻ֧��SFFģʽ��
          rtr_amr��  Զ��/��־֡�˲�����λ��0��ʾֻ����rtr_acr����֡��Ϊ1��ʾԶ��/0��־
                     ֡�����գ�ֻ֧��SFFģʽ��

          Byte_acr1������֡��1��Byte�˲�ѡ��ֻ֧��SFFģʽ��
          Byte_amr1������֡��1��Byte����λ��ֻ֧��SFFģʽ��
�������: ��
����ֵ:   0�����ͳɹ� !0������ʧ��
���������: 
����˵��: ��չ֡ʱ��ֻ��ID��bit13- bit28 ����ɸѡ����
�޸����� �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      ����
*******************************************************************************/
u8 ACR1 = 0;
u8 ACR0 = 0;
 void  ID1_Filter_Dual(u32 acr1 ,u32 amr1,u8 rtr_acr1,u8 rtr_amr1,u8 Byte_acr1,u8 Byte_amr1,u8 ide)
{
	CAN_MODE |= 1 << 0;   // RESET MODE
	CAN_MODE &= ~(1 << 3);//˫�˲�ID,
	rtr_acr1 &= 0x1;
	rtr_amr1 &= 0x1;
	
	if(ide)//externed
	{
		acr1 &= 0x1fffffff;
		CAN_ACR1 = (u8)(acr1 >> 13);
		ACR1 = CAN_ACR1;
		CAN_ACR0 = (u8)(acr1 >> 21);
		ACR0 = CAN_ACR0;
		 
		CAN_AMR1 = (u8)(amr1 >> 13);
		CAN_AMR0 = (u8)(amr1 >> 21);
		
	}else
	{
		acr1 &= 0x7ff;
		CAN_ACR0 = (u8)(acr1 >> 3);
		CAN_ACR1 = (u8)(acr1 << 5) | (rtr_acr1 << 4) | (Byte_acr1>>4);
		CAN_ACR3 &= 0xF0;
		CAN_ACR3 |= (u8)(Byte_acr1 & 0x0F);
    
		CAN_AMR0 = (u8)(amr1 >> 3);
		CAN_AMR1 = (u8)(amr1 << 5) | (rtr_amr1 << 4) | (Byte_amr1>>4);
		CAN_AMR3 &= 0xF0;
		CAN_AMR3 |= (u8)(Byte_amr1 & 0x0F);
	}
	CAN_MODE &= ~(1 << 0);          //�������ģʽ
}

/*******************************************************************************
��������:  void ID2_Filter_Dual(u32 acr2 ,u32 amr2,u8 rtr_acr2,u8 rtr_amr2 ,u8 ide)
��������: CAN˫ID������ID2�˲����� ����2.0BЭ��
�����ı�: ��
�������:  acr2��ID2ֵ����Χ1D28~ID13��ID��16λ��Ч��   amr2��ID2����λ  ide��0��׼/1��չ֡
          
          rtr_acr2: ���գ�1Զ��/0����֡��֡����ѡ��ֻ֧��SFF��׼֡ģʽ��
          rtr_amr2�� Զ��/��־֡�˲�����λ��0��ʾֻ����rtr_acr����֡��Ϊ1��ʾԶ��/0��־
                    ֡�����գ�ֻ֧��SFF��׼֡ģʽ��
�������: ��
����ֵ:   0�����ͳɹ� !0������ʧ��
���������: 
����˵��: ��չ֡ʱ��ֻ��ID��bit13- bit28 ����ɸѡ����
�޸����� �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      ����
*******************************************************************************/
 void ID2_Filter_Dual(u32 acr2 ,u32 amr2,u8 rtr_acr2,u8 rtr_amr2 ,u8 ide)
{
	CAN_MODE |= 1 << 0;   // RESET MODE
	CAN_MODE &= ~(1 << 3);//˫�˲�ID,
	rtr_acr2 &= 0x1;
	rtr_amr2 &= 0x1;
	if(ide)//externed
	{
		acr2 &= 0x1fffffff;
		CAN_ACR3 = (u8)(acr2 >> 13);
		CAN_ACR2 = (u8)(acr2 >> 21);
		 
		CAN_AMR3 = (u8)(amr2 >> 13);
		CAN_AMR2 = (u8)(amr2 >> 21);
		
	}else
	{
		acr2 &= 0x7ff;
		CAN_ACR3 &= 0x0f;
		CAN_ACR2 = (u8)(acr2 >> 3);
		CAN_ACR3 |= (u8)(acr2 << 5) | (rtr_acr2 << 4);

		CAN_AMR3 &= 0x0f;
		CAN_AMR2 = (u8)(amr2 >> 3);
		CAN_AMR3 |= (u8)(amr2 << 5) | (rtr_amr2 >> 4);
	}
	CAN_MODE &= ~(1 << 0);          //�������ģʽ
}

/*******************************************************************************
��������: u8 My_CAN_Send_Msg(u32 id,u8 ide,u8 rtr,const u8 *msg,u8 len)
��������: CAN��ѯ�������ݳ���  ����2.0BЭ��
�����ı�: ��
�������: id: ����id ide: ��׼/��չ֡ rtr��Զ��֡/����֡ *msg: ���͵�����  len:�����ֽڳ���
�������: ��
����ֵ:   0�����ͳɹ� !0������ʧ��
���������: 
����˵��: id:��׼ID(11λ)/��չID(11λ+18λ)	    
          ide:0,��׼֡;1,��չ֡
          rtr:0,����֡;1,ң��֡
�޸����� �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      ����
*******************************************************************************/
u8 My_CAN_Send_Msg(u32 id,u8 ide,u8 rtr, u8 *msg,u8 len)
{
	u8 frame_inf = 0 ;
	u16 i = 0;
	
	if(CAN_SR & 0X04)//TFIFO ��
  {
		frame_inf |= ide << 7;          //0��׼/1��չ֡
		frame_inf |= rtr << 6;          //0,����֡;1,ң��֡
		frame_inf |= len << 0;          //�������ݳ���
		CAN_TXRX0 = frame_inf;          //����TX֡��Ϣ
		if(0 == ide)//��׼֡
		{
			id &= 0x7ff;		
			//���ͽ��ռĴ���1
			CAN_TXRX1 = id >> 3;          //TX ID0
			CAN_TXRX2 = (id & 0X07) << 5; //TX ID1
			CAN_TXRX3 =  msg[0];          //TX DATA0
			CAN_TXRX4 =  msg[1];          //TX DATA1  
			CAN_TXRX5 =  msg[2];          //TX DATA2
			CAN_TXRX6 =  msg[3];          //TX DATA3
			CAN_TXRX7 =  msg[4];          //TX DATA4
			CAN_TXRX8 =  msg[5];          //TX DATA5
			CAN_TXRX9 =  msg[6];          //TX DATA6
			CAN_TXRXA =  msg[7];          //TX DATA7
			
		}else//��չ֡
		{
			id &= 0X1FFFFFFF;
			CAN_TXRX1 = (u8)(id >> 21);         //TX ID0
			CAN_TXRX2 = (u8)((id >> 13) & 0xFF);//TX ID1
			CAN_TXRX3 = (u8)((id >> 5)  & 0xFF);//TX ID2
			CAN_TXRX4 = (u8)((id & 0xff) << 3); //TX ID3
			CAN_TXRX5 = msg[0];          //TX DATA0
			CAN_TXRX6 = msg[1];          //TX DATA1
			CAN_TXRX7 = msg[2];          //TX DATA2
			CAN_TXRX8 = msg[3];          //TX DATA3
			CAN_TXRX9 = msg[4];          //TX DATA4
			CAN_TXRXA = msg[5];          //TX DATA5
			CAN_TXRXB = msg[6];          //TX DATA6
			CAN_TXRXC = msg[7];          //TX DATA7
			
		}
		  CAN_CMR |= 1 << 0;           //CAN ���ʹ�������
		while(!(CAN_SR & 0X08))      //���һ���Ƿ������
		{
		
			if((i++) >= 0xfff) 
			{
				return 0xff;             //����ʧ��
			}
		};
		   return 0;                   //�������
	}
	else //TFIFO�ǿ�
	{
//		can_par.rx_sta = CAN_SR;    //״̬�Ĵ���
//		can_par.rx_sta = CAN_INTR;  //�ж�״̬�Ĵ���
		   return 0xff;               //����ʧ��
	}
}

/*******************************************************************************
��������: u8 CAN_Receive_Msg(u32* id,u8* ide,u8* rtr,u8 *buf)
��������: CAN��ѯ�������ݳ���
�����ı�: ��
�������: id: ����id ide: ��׼/��չ֡ rtr������֡/ң��֡ *msg: ���͵�����  len:�����ֽڳ���
�������: ��
����ֵ:   0�����ճɹ� !0������ʧ��
���������: 
����˵��: 
�޸����� �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      ����
*******************************************************************************/
u8 CAN_Receive_Msg(u32* id,u8* ide,u8* rtr,u8 *buf)
{
	u8 reg_inf; 
//	u8 temp;
  if(CAN_SR & 0X01)   //RFIFO ����һ֡���֡���ݣ�����ͨ�� RFIFO �Ĵ�����ȡ
	{
		reg_inf = CAN_TXRX0;  //��ȡ��һ֡���֡����
		
		if(reg_inf & 0x80)    //EFF����չ��֡
		{
			*ide = 1;
		//	temp = (CAN_TXRX2 << 21) | (CAN_TXRX2 << 13 )|(CAN_TXRX3 << 5 )|(CAN_TXRX4 >> 3);
			*id = (CAN_TXRX1 << 21) | (CAN_TXRX2 << 13 )|(CAN_TXRX3 << 5 )|(CAN_TXRX4 >> 3); //��ȡID
		  if(reg_inf & 0x40)
			{
				*rtr = 1;   //ң��֡
			}else
			{
				*rtr = 0;   //����֡
			}
			buf[0] = CAN_TXRX5; //��ȡ����
			buf[1] = CAN_TXRX6;
			buf[2] = CAN_TXRX7;
			buf[3] = CAN_TXRX8;
			buf[4] = CAN_TXRX9;
			buf[5] = CAN_TXRXA;
			buf[6] = CAN_TXRXB;
			buf[7] = CAN_TXRXC;	
		}else    //SFF����׼��֡
		{
			*ide = 0;
			if(reg_inf & 0x40)  
			{
				*rtr = 1;
			}else
			{
				*rtr = 0;
			}

			*id =((CAN_TXRX1 << 3) | (CAN_TXRX2 >> 5));
			buf[0] = CAN_TXRX3;
			buf[1] = CAN_TXRX4;
			buf[2] = CAN_TXRX5;
			buf[3] = CAN_TXRX6;
			buf[4] = CAN_TXRX7;
			buf[5] = CAN_TXRX8;
			buf[6] = CAN_TXRX9;
			buf[7] = CAN_TXRXA;		
		}
		
		CAN_CMR |=  0x04;//�ͷŽ��ջ�����
		
		return 0 ;       //�������
	}
	else // fifo is empty
	{
		return 0xff;     //�����쳣
	}
	
}

/*******************************************************************************
��������: void DMA_Init_CANRX( u32* memaddr , len , ide)
��������: DMA���հ�������
�����ı�: ��
�������: id: ����id ide: 0��׼/1��չ֡  *memaddr: ���͵�����  len:�ڴ�洢����֡����
�������: ��
����ֵ:   0�����ճɹ� !0������ʧ��
���������: 
����˵��: 
�޸����� �汾�� �޸��� �޸�����
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      ����
*******************************************************************************/
void DMA_Init_CANRX(u32* memaddr,u8 len ,u8 ide)
{ 
	  u8 size = 0;
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);   
	  if(ide)
		{
		  size = 13; /*��չ֡*/
		}else{
		  size = 11; /*��׼֡*/
		}
    /*DMA����ʹ�ܣ����յ�10�����ݺ󣬲���DMA�ж�*/
    DMA_InitStruct.DMA_Channel_EN = ENABLE;           /* DMA ͨ��ʹ��*/
    DMA_InitStruct.DMA_IRQ_EN = DMA_TCIE;             /* DMA ��������ж�ʹ�� */
    DMA_InitStruct.DMA_DIR = PERI2MEMORY;             /* �������ڴ� */
    DMA_InitStruct.DMA_CIRC = DISABLE;                /* DMA����ģʽ��ѭ��ģʽ������Ч */
    DMA_InitStruct.DMA_PINC = ENABLE;                 /* �����ַÿ�����Ƿ����,����Ч */
    DMA_InitStruct.DMA_MINC = ENABLE;                 /* �ڴ��ַ�ڶ����Ƿ��ڵ�һ�ֵ�ַ�Ļ����ϵ���,����Ч */
    DMA_InitStruct.DMA_PBTW = DMA_WORD_TRANS;         /* �������λ�� 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_MBTW = DMA_WORD_TRANS;         /* �ڴ����λ�� 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_CH3_CAN_REQ_EN;   /* Channel_0 ADC0 DMA����ʹ�ܣ�����Ч */
    DMA_InitStruct.DMA_TIMES = size;                    /* DMA ͨ�� x ÿ�����ݰ��˴��� 1~511 */
    DMA_InitStruct.DMA_ROUND = len;                     /* DMA ͨ�� x �������� 1~255 */
    DMA_InitStruct.DMA_CPAR = (u32)&CAN_TXRX0;        /* DMA ͨ�� x �����ַ */
    DMA_InitStruct.DMA_CMAR = (u32)memaddr;           /* DMA ͨ�� x �ڴ��ַ */
    DMA_Init(DMA_CH3, &DMA_InitStruct);		
	  NVIC_EnableIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, 0);
};




