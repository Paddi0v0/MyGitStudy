#ifndef __CAN__H__
#define __CAN__H__
#include "lks32mc08x_sys.h"

typedef struct
{
	u32 id;
	u8 ide;
	u8 rtr;
	u8 TX[8];
	u8 RX[8];
	u8 rx_sta;
}can_parameter;

extern can_parameter can_par ;
void CAN_Init(u8 BTR0,u8 BTR1);
u8 My_CAN_Send_Msg(u32 id,u8 ide,u8 rtr, u8 *msg,u8 len);
u8 CAN_Receive_Msg(u32* id,u8* ide,u8* rtr,u8 *buf);
void DMA_Init_CANRX( u8* memaddr);
void DMA_Init_CANTX( u8* memaddr);
void  SFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr,u8 Byte1_acr,u8 Byte1_amr,u8 Byte2_acr,u8 Byte2_amr);
void  EFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr);
void  ID1_Filter_Dual(u32 acr1 ,u32 amr1,u8 rtr_acr1,u8 rtr_amr1,u8 Byte_acr1,u8 Byte_amr1,u8 ide);
void  ID2_Filter_Dual(u32 acr2 ,u32 amr2,u8 rtr_acr2,u8 rtr_amr2 ,u8 ide);
#endif




