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
函数名称: void CAN_Init(u8 tq,u8 tsge1,u8 tsge2)
功能描述: CAN初始化函数,采用2.0B协议
操作的表: Can波特率     BTR0    	 BTR1
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
输入参数:  BTR0   单元参数TQ
          BTR1   段时间
			    
输出参数: 无
返回值:   无
其它说明: 
修改日期  版本号 修改人 修改内容
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      创建
*******************************************************************************/
void CAN_Init(u8 BTR0,u8 BTR1)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	
    __disable_irq();         // 关闭中断 中断总开关
		SYS_WR_PROTECT = 0x7a83; // 打开写保护 
	
	  SYS_SFT_RST |= BIT7;     // 复位CAN
	  SYS_SFT_RST &= ~BIT7;    // 释放CAN复位
	
	  SYS_CLK_CFG = 0x01FF;    // 设置系统时钟?P选择PLL，不进行分频96mhz*/
		SYS_CLK_FEN |= 1 << 7;   // 使能CAN时钟门控
		SYS_CLK_DIV0 = 0x0000;   // spi 工作时钟分频为零，96MHZ
		FLASH_CFG |= 0x00080000; // FLASH 预取加速使能
	  
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
	
		CAN_MODE |= 1 << 0;           // 复位模式
  
	  CAN_BTR0 = BTR0;     // 波特率配置，计算CAN传输基本时间单元参数TQ
	  CAN_BTR1 = BTR1;     // SEG1 段时间

	  CAN_CMR |= (1 << 5);            //使能DMA传输功能
		
	  CAN_MODE &= ~(1 << 0);          //正常输出模式
	 
  	CAN_INTR_EN |= 1 << 0;          //RFIFO有新的数据被接收到，中断源使能
	  CAN_INTR_EN |= 1 << 1;					//发送完毕当前帧，中断源使能
	  CAN_INTR_EN |= 1 << 2;					//CAN_SR.7 或者 CAN_SR.6 有变化，中断源使能
	  CAN_INTR_EN |= 1 << 3;					//RFIFO 数据发生溢出，中断源使能
	  CAN_INTR_EN |= 1 << 5;					//反复进入错误状态或错误总是超规定值，中断源使能
	  CAN_INTR_EN |= 1 << 6;					//丢失仲裁，改成接收模式，中断源使能
	  CAN_INTR_EN |= 1 << 7;					//总线错误中断，中断源使能
}


/*******************************************************************************
函数名称:  void  SFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr,
                           u8 Byte1_acr,u8 Byte1_amr,u8 Byte2_acr,u8 Byte2_amr)
功能描述:  CAN标准帧单ID过滤,采用2.0B协议
操作的表:  无
输入参数: acr: ID值。
          amr：屏蔽位
          标准帧  11位ID长度
          rtr_acr: 接收（1远程/0标志帧）帧类型选择
          rtr_amr： 远程/数据帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志帧均接收
          Byte1_acr：数据第一个字节
          Byte1_amr：第一个字节屏蔽位
          Byte2_acr：数据第二个字节
          Byte2_amr：第二个字节屏蔽位         
输出参数: 无
返回值:   无
其它说明: 
修改日期  版本号 修改人 修改内容
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      创建
*******************************************************************************/
 void SFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr,u8 Byte1_acr,u8 Byte1_amr,u8 Byte2_acr,u8 Byte2_amr)
{ 
	  CAN_MODE |= 1 << 0;             // 复位模式
	  CAN_MODE |= 1 << 3;             // 单滤波ID,一个 32 位长的滤波ID
	
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
	
	  CAN_MODE &= ~(1 << 0);          //正常输出模式
	
}
/*******************************************************************************
函数名称:  void EFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr)
功能描述: CAN扩展帧单ID过滤,采用2.0B协议
操作的表: 无
输入参数: acr：ID值。
          amr：屏蔽位
       
          rtr_acr： 接收（1远程/0数据帧）帧类型选择
          rtr_amr： 远程/数据帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志帧均接收

          ide：0标准/1扩展帧
输出参数: 无
返回值:   无
其它说明: 
修改日期  版本号 修改人 修改内容
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      创建
*******************************************************************************/
 void EFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr)
{ 
	  CAN_MODE |= 1 << 0;             // 复位模式
	  CAN_MODE |= 1 << 3;             // 单滤波ID,一个 32 位长的滤波ID
	 
		acr &= 0x1fffffff;
		amr &= 0x1fffffff;
	  rtr_acr &= 0x1;
		rtr_amr &= 0x1;
	
		/*可接收的ID寄存器，当输入帧的 ID 同此匹配，则被 CAN 模块接受
		  配合 AMR 寄存器，可同一类 ID 匹配。*/
		CAN_ACR3 = (u8)(acr << 3)|(rtr_acr << 2); 
		CAN_ACR2 = (u8)(acr >> 5);
		CAN_ACR1 = (u8)(acr >> 13);
		CAN_ACR0 = (u8)(acr >> 21);
	 /*配合 ACR 寄存器，同输入 ID 进行匹配。AMR 寄存器某一位为 0，标识
     ID 对应位需要同 ACR 匹配；为 1，标识 ID 对应位不需要同 ACR 匹配*/
		CAN_AMR3 = (u8)((amr << 3)|(rtr_amr << 2)|0x03);
		CAN_AMR2 = (u8)(amr >> 5);
		CAN_AMR1 = (u8)(amr >> 13);
		CAN_AMR0 = (u8)(amr >> 21);
	
	  CAN_MODE &= ~(1 << 0);          //正常输出模式
}

/*******************************************************************************
函数名称:  void  ID1_Filter_Dual(u32 acr1 ,u32 amr1,u8 rtr_acr1,
                               u8 rtr_amr1,u8 Byte_acr1,u8 Byte_amr1,u8 ide)
                   
功能描述: CAN双ID过滤中ID1滤波设置 采用2.0B协议
操作的表: 无
输入参数:  acr1：ID1值（范围1D28~ID13共ID高16位有效）   amr1：ID1屏蔽位  ide：0标准/1扩展帧
          
          rtr_acr：  接收（1远程/0数据帧）帧类型选择（只支持SFF模式）
          rtr_amr：  远程/标志帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志
                     帧均接收（只支持SFF模式）

          Byte_acr1：数据帧第1个Byte滤波选择（只支持SFF模式）
          Byte_amr1：数据帧第1个Byte屏蔽位（只支持SFF模式）
输出参数: 无
返回值:   0：发送成功 !0：发送失败
多任务访问: 
其它说明: 扩展帧时，只对ID的bit13- bit28 进行筛选过滤
修改日期 版本号 修改人 修改内容
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      创建
*******************************************************************************/
u8 ACR1 = 0;
u8 ACR0 = 0;
 void  ID1_Filter_Dual(u32 acr1 ,u32 amr1,u8 rtr_acr1,u8 rtr_amr1,u8 Byte_acr1,u8 Byte_amr1,u8 ide)
{
	CAN_MODE |= 1 << 0;   // RESET MODE
	CAN_MODE &= ~(1 << 3);//双滤波ID,
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
	CAN_MODE &= ~(1 << 0);          //正常输出模式
}

/*******************************************************************************
函数名称:  void ID2_Filter_Dual(u32 acr2 ,u32 amr2,u8 rtr_acr2,u8 rtr_amr2 ,u8 ide)
功能描述: CAN双ID过滤中ID2滤波设置 采用2.0B协议
操作的表: 无
输入参数:  acr2：ID2值（范围1D28~ID13共ID高16位有效）   amr2：ID2屏蔽位  ide：0标准/1扩展帧
          
          rtr_acr2: 接收（1远程/0数据帧）帧类型选择（只支持SFF标准帧模式）
          rtr_amr2： 远程/标志帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志
                    帧均接收（只支持SFF标准帧模式）
输出参数: 无
返回值:   0：发送成功 !0：发送失败
多任务访问: 
其它说明: 扩展帧时，只对ID的bit13- bit28 进行筛选过滤
修改日期 版本号 修改人 修改内容
-----------------------------------------------------------------------------
2022/1/16  V1.0   HMG      创建
*******************************************************************************/
 void ID2_Filter_Dual(u32 acr2 ,u32 amr2,u8 rtr_acr2,u8 rtr_amr2 ,u8 ide)
{
	CAN_MODE |= 1 << 0;   // RESET MODE
	CAN_MODE &= ~(1 << 3);//双滤波ID,
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
	CAN_MODE &= ~(1 << 0);          //正常输出模式
}

/*******************************************************************************
函数名称: u8 My_CAN_Send_Msg(u32 id,u8 ide,u8 rtr,const u8 *msg,u8 len)
功能描述: CAN轮询发送数据程序  采用2.0B协议
操作的表: 无
输入参数: id: 发送id ide: 标准/扩展帧 rtr：远程帧/数据帧 *msg: 发送的数据  len:发送字节长度
输出参数: 无
返回值:   0：发送成功 !0：发送失败
多任务访问: 
其它说明: id:标准ID(11位)/扩展ID(11位+18位)	    
          ide:0,标准帧;1,扩展帧
          rtr:0,数据帧;1,遥控帧
修改日期 版本号 修改人 修改内容
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      创建
*******************************************************************************/
u8 My_CAN_Send_Msg(u32 id,u8 ide,u8 rtr, u8 *msg,u8 len)
{
	u8 frame_inf = 0 ;
	u16 i = 0;
	
	if(CAN_SR & 0X04)//TFIFO 空
  {
		frame_inf |= ide << 7;          //0标准/1扩展帧
		frame_inf |= rtr << 6;          //0,数据帧;1,遥控帧
		frame_inf |= len << 0;          //发送数据长度
		CAN_TXRX0 = frame_inf;          //发送TX帧信息
		if(0 == ide)//标准帧
		{
			id &= 0x7ff;		
			//发送接收寄存器1
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
			
		}else//扩展帧
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
		  CAN_CMR |= 1 << 0;           //CAN 发送传输请求
		while(!(CAN_SR & 0X08))      //最近一次是否传输完成
		{
		
			if((i++) >= 0xfff) 
			{
				return 0xff;             //发送失败
			}
		};
		   return 0;                   //发送完成
	}
	else //TFIFO非空
	{
//		can_par.rx_sta = CAN_SR;    //状态寄存器
//		can_par.rx_sta = CAN_INTR;  //中断状态寄存器
		   return 0xff;               //发送失败
	}
}

/*******************************************************************************
函数名称: u8 CAN_Receive_Msg(u32* id,u8* ide,u8* rtr,u8 *buf)
功能描述: CAN轮询接收数据程序
操作的表: 无
输入参数: id: 发送id ide: 标准/扩展帧 rtr：数据帧/遥控帧 *msg: 发送的数据  len:发送字节长度
输出参数: 无
返回值:   0：接收成功 !0：接收失败
多任务访问: 
其它说明: 
修改日期 版本号 修改人 修改内容
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      创建
*******************************************************************************/
u8 CAN_Receive_Msg(u32* id,u8* ide,u8* rtr,u8 *buf)
{
	u8 reg_inf; 
//	u8 temp;
  if(CAN_SR & 0X01)   //RFIFO 存有一帧或多帧数据，可以通过 RFIFO 寄存器读取
	{
		reg_inf = CAN_TXRX0;  //读取的一帧或多帧数据
		
		if(reg_inf & 0x80)    //EFF（扩展）帧
		{
			*ide = 1;
		//	temp = (CAN_TXRX2 << 21) | (CAN_TXRX2 << 13 )|(CAN_TXRX3 << 5 )|(CAN_TXRX4 >> 3);
			*id = (CAN_TXRX1 << 21) | (CAN_TXRX2 << 13 )|(CAN_TXRX3 << 5 )|(CAN_TXRX4 >> 3); //获取ID
		  if(reg_inf & 0x40)
			{
				*rtr = 1;   //遥控帧
			}else
			{
				*rtr = 0;   //数据帧
			}
			buf[0] = CAN_TXRX5; //获取数据
			buf[1] = CAN_TXRX6;
			buf[2] = CAN_TXRX7;
			buf[3] = CAN_TXRX8;
			buf[4] = CAN_TXRX9;
			buf[5] = CAN_TXRXA;
			buf[6] = CAN_TXRXB;
			buf[7] = CAN_TXRXC;	
		}else    //SFF（标准）帧
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
		
		CAN_CMR |=  0x04;//释放接收缓冲区
		
		return 0 ;       //接收完成
	}
	else // fifo is empty
	{
		return 0xff;     //接收异常
	}
	
}

/*******************************************************************************
函数名称: void DMA_Init_CANRX( u32* memaddr , len , ide)
功能描述: DMA接收搬运配置
操作的表: 无
输入参数: id: 发送id ide: 0标准/1扩展帧  *memaddr: 发送的数据  len:内存存储允许帧个数
输出参数: 无
返回值:   0：接收成功 !0：接收失败
多任务访问: 
其它说明: 
修改日期 版本号 修改人 修改内容
-----------------------------------------------------------------------------
2018/08/10 V1.0   ZKW      创建
*******************************************************************************/
void DMA_Init_CANRX(u32* memaddr,u8 len ,u8 ide)
{ 
	  u8 size = 0;
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);   
	  if(ide)
		{
		  size = 13; /*扩展帧*/
		}else{
		  size = 11; /*标准帧*/
		}
    /*DMA接收使能，接收到10个数据后，产生DMA中断*/
    DMA_InitStruct.DMA_Channel_EN = ENABLE;           /* DMA 通道使能*/
    DMA_InitStruct.DMA_IRQ_EN = DMA_TCIE;             /* DMA 传输完成中断使能 */
    DMA_InitStruct.DMA_DIR = PERI2MEMORY;             /* 外设至内存 */
    DMA_InitStruct.DMA_CIRC = DISABLE;                /* DMA传输模式：循环模式，高有效 */
    DMA_InitStruct.DMA_PINC = ENABLE;                 /* 外设地址每轮内是否递增,高有效 */
    DMA_InitStruct.DMA_MINC = ENABLE;                 /* 内存地址第二轮是否在第一轮地址的基础上递增,高有效 */
    DMA_InitStruct.DMA_PBTW = DMA_WORD_TRANS;         /* 外设访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_MBTW = DMA_WORD_TRANS;         /* 内存访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_CH3_CAN_REQ_EN;   /* Channel_0 ADC0 DMA请求使能，高有效 */
    DMA_InitStruct.DMA_TIMES = size;                    /* DMA 通道 x 每轮数据搬运次数 1~511 */
    DMA_InitStruct.DMA_ROUND = len;                     /* DMA 通道 x 采样轮数 1~255 */
    DMA_InitStruct.DMA_CPAR = (u32)&CAN_TXRX0;        /* DMA 通道 x 外设地址 */
    DMA_InitStruct.DMA_CMAR = (u32)memaddr;           /* DMA 通道 x 内存地址 */
    DMA_Init(DMA_CH3, &DMA_InitStruct);		
	  NVIC_EnableIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, 0);
};




