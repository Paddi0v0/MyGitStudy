/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc08x_can.c\n
 * 文件标识： 无 \n
 * 内容摘要： CAN外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月29日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */

#include "lks32mc08x_can.h"
 

/**
 *@brief @b 函数名称:   void CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct)
 *@brief @b 功能描述:   ADC初始化函数
 *@see被调用函数：      SYS_ModuleClockCmd()
 *@param输入参数：      CANx：CAN , CAN_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			CAN_InitTypeDef CAN_InitStruct;
			CAN_StructInit(&CAN_InitStruct);
			//Can波特率:500Kbps
			CAN_InitStruct.CAN_Btr0 = 0x05;
			CAN_InitStruct.CAN_Btr1 = 0x1C;
			CAN_InitStruct.CAN_DMAEn = DISABLE;              //无DMA搬运数据
			CAN_InitStruct.CAN_WorkMode = CAN_NORMAL_MODE;   //CAN正常收发工作模式
			CAN_InitStruct.CAN_ErrWarThre = 50;              //错误与警告门限值为50
			//开启接收中断使能,发送完毕当前帧中断使能,错误报警中断使能
	        CAN_InitStruct.IRQEna = CAN_IE_RFIFONOEMPTY | CAN_IE_TXDONE | CAN_IE_WERR;
			CAN_Init(CAN, &CAN_InitStruct);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_Init(CAN_TypeDef *CANx, CAN_InitTypeDef *CAN_InitStruct)
{
	SYS_ModuleClockCmd(SYS_Module_CAN, ENABLE);
	CAN->MOD |= 1 << 0; // 复位模式
	if (CAN_InitStruct->CAN_DMAEn)
	{
		CANx->CMR |= BIT5;
	}
	else
	{
		CANx->CMR &= ~BIT5;
	}
	CANx->EWLR = CAN_InitStruct->CAN_ErrWarThre;
	CANx->BTR0 = CAN_InitStruct->CAN_Btr0;
	CANx->BTR1 = CAN_InitStruct->CAN_Btr1;
	CANx->MOD = CAN_InitStruct->CAN_WorkMode;
	CANx->EIR = CAN_InitStruct->IRQEna;
}
/**
 *@brief @b 函数名称:   void CAN_StructInit(CAN_InitTypeDef *CAN_InitStruct)
 *@brief @b 功能描述:   CAN结构体初始化
 *@see被调用函数：       无
 *@param输入参数：      CAN_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无   
 *@par 示例代码：
 *@code    
           CAN_InitTypeDef CAN_InitStructure;
		   CAN_StructInit(&CAN_InitStructure); //初始化结构体
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_StructInit(CAN_InitTypeDef *CAN_InitStruct)
{
	CAN_InitStruct->CAN_DMAEn = DISABLE;
	CAN_InitStruct->CAN_WorkMode = CAN_NORMAL_MODE;
	CAN_InitStruct->CAN_ErrWarThre = 120;
	/*波特率选择500K*/
	CAN_InitStruct->CAN_Btr0 = 0x05;
	CAN_InitStruct->CAN_Btr1 = 0x1C;
	CAN_InitStruct->IRQEna = 0x0;
}

/**
 *@brief @b 函数名称:   void CAN_Sleep(u32 Baud)
 *@brief @b 功能描述:   CAN开启休眠函数
 *@see被调用函数：       无
 *@param输入参数：       Baud：波特率，单位Kbps
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       休眠唤醒有两种：1、软件清零CAN_MOD[4]，即自动退出休眠模式。，2、一旦检
			           测到CAN总线的活动，即自动退出休眠模式。
 *@warning             无   
 *@par 示例代码：
 *@code    
           CAN_Sleep(500);//开启CAN休眠，CAN比特率500kbps
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_Sleep(u32 Baud)
{
	u32 rate = 0 , t_cnt = 0;
	CAN_MODE &= ~BIT0;//正常输出模式
	rate = 1152000 / Baud; //此值为主频96MHz进行计算，主频48MHz写入的Baud适当加大
	for (t_cnt = 0; t_cnt < rate; t_cnt++)//等待11个波特率周期,进入正常工作模式
	{
		__NOP();
	}
	CAN_MODE |= BIT4;
	rate = 1632000 / Baud; //此值为主频96MHz进行计算，主频48MHz写入的Baud适当加大
	// 等待16个波特率周期，正式进入休眠等待16个波特率周期，正式进入休眠
	for (t_cnt = 0; t_cnt < rate; t_cnt++)
	{
	   __NOP();
	}
}

/**
 *@brief @b 函数名称:   void CAN_Manual_Awake(void)
 *@brief @b 功能描述:   CAN手动休眠唤醒函数
 *@see被调用函数：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           CAN_Manual_Awake();//唤醒CAN休眠
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_Manual_Awake(void)
{
	CAN_MODE &= ~BIT0;
	CAN_MODE &= ~BIT4;
}

/**
 *@brief @b 函数名称:   void  SFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr,
						   u8 Byte1_acr,u8 Byte1_amr,u8 Byte2_acr,u8 Byte2_amr)
 *@brief @b 功能描述:   CAN标准帧单ID过滤,采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：       acr: ID值。 \n
 *                      amr：屏蔽位                     
 *                      rtr_acr:   接收（1远程/0数据帧）帧类型选择 \n
 *                      rtr_amr：  远程/数据帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志帧均接收 \n
 *                      Byte1_acr：数据第一个字节 \n
 *                      Byte1_amr：第一个字节屏蔽位 \n
 *                      Byte2_acr：数据第二个字节 \n
 *                      Byte2_amr：第二个字节屏蔽位 \n
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：         
                        1、标准帧  11位ID长度 \n
                        2、amr：屏蔽位对应位0表示此为对应ID必须匹配才会接收
 *@warning              无   
 *@par 示例代码：
 *@code    
         示例1： 
           //标准帧接收单滤波： ID:0x5A ,数据帧，BYTE1:0x81,BYTE:0x23
            SFF_ID_Filter(0X5A, 0x00, 0x0, 0x0, 0x81, 0x00, 0x23, 0x00);
		   //接收的标准帧只有满足ID地址为0x5A的数据帧且第一个数据字节为0x81，第二个字节为0x23才会接收

	     示例2： 
           //标准帧接收单滤波： ID:0x5A和0x5B(因为amr第一位为1，所以第一位可以为1或0，
		                       无需匹配即可接收) ,数据帧，BYTE1:0x81,BYTE:0x23
            SFF_ID_Filter(0X5A, 0x01, 0x0, 0x0, 0x81, 0x00, 0x23, 0x00);
		   //接收的标准帧只有满足ID地址为0x5A和0x5B的数据帧且第一个数据字节为0x81，第二个字节为0x23才会接收
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void SFF_ID_Filter(u32 acr, u32 amr, u8 rtr_acr, u8 rtr_amr, u8 Byte1_acr, u8 Byte1_amr, u8 Byte2_acr, u8 Byte2_amr)
{
	CAN->MOD |= 1 << 0; // 复位模式
	CAN->MOD |= 1 << 3; // 单滤波ID,一个 32 位长的滤波ID

	acr &= 0x7ff;
	amr &= 0x7ff;

	rtr_acr &= 0x1;
	rtr_amr &= 0x1;

	CAN_ACR0 = (u8)(acr >> 3);
	CAN_ACR1 = (u8)(acr << 5) | (rtr_acr << 4);
	CAN_ACR2 = Byte1_acr;
	CAN_ACR3 = Byte2_acr;

	CAN_AMR0 = (u8)(amr >> 3);
	CAN_AMR1 = (u8)(amr << 5) | (rtr_amr << 4) | 0x0f;
	CAN_AMR2 = Byte1_amr;
	CAN_AMR3 = Byte2_amr;

	CAN->MOD &= ~(1 << 0); //正常输出模式
}

/**
 *@brief @b 函数名称:   void EFF_ID_Filter(u32 acr,u32 amr,u8 rtr_acr,u8 rtr_amr)
 *@brief @b 功能描述:   CAN扩展帧单ID过滤,采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：       acr: ID值。 \n
 *                      amr：屏蔽位           
 *                      rtr_acr:   接收（1远程/0数据帧）帧类型选择 \n
 *                      rtr_amr：  远程/数据帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志帧均接收 \n
 *                 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        
                        1、扩展帧  29位ID长度 \n
                        2、amr：屏蔽位对应位0表示此为对应ID必须匹配才会接收
 *@warning              无   
 *@par 示例代码：
 *@code   
      示例1： 
           //扩展帧接收滤波： ID:0X10005A5A ,数据帧
           EFF_ID_Filter(0X10005A5A, 0x00, 0x0, 0x0);
		   //接收的扩展帧只有满足ID地址为0X10005A5A且为数据帧才会接收
      示例2：
           //扩展帧接收滤波： ID:0X10005A5A ,数据帧和远程帧（因为rtr_amr为1，所以接收帧类型不需要匹配也可以接收）
		   EFF_ID_Filter(0X10005A5A, 0x00, 0x0, 0x1);
		   //接收的扩展帧只有满足ID地址为0X10005A5A的数据帧和远程帧才会接收
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void EFF_ID_Filter(u32 acr, u32 amr, u8 rtr_acr, u8 rtr_amr)
{
	CAN->MOD |= 1 << 0; // 复位模式
	CAN->MOD |= 1 << 3; // 单滤波ID,一个 32 位长的滤波ID

	acr &= 0x1fffffff;
	amr &= 0x1fffffff;
	rtr_acr &= 0x1;
	rtr_amr &= 0x1;

	/*可接收的ID寄存器，当输入帧的 ID 同此匹配，则被 CAN 模块接受
	  配合 AMR 寄存器，可同一类 ID 匹配。*/
	CAN_ACR3 = (u8)(acr << 3) | (rtr_acr << 2);
	CAN_ACR2 = (u8)(acr >> 5);
	CAN_ACR1 = (u8)(acr >> 13);
	CAN_ACR0 = (u8)(acr >> 21);
	/*配合 ACR 寄存器，同输入 ID 进行匹配。AMR 寄存器某一位为 0，标识
   ID 对应位需要同 ACR 匹配；为 1，标识 ID 对应位不需要同 ACR 匹配*/
	CAN_AMR3 = (u8)((amr << 3) | (rtr_amr << 2) | 0x03);
	CAN_AMR2 = (u8)(amr >> 5);
	CAN_AMR1 = (u8)(amr >> 13);
	CAN_AMR0 = (u8)(amr >> 21);

	CAN->MOD &= ~(1 << 0); //正常输出模式
}


/**
 *@brief @b 函数名称:   void  ID1_Filter_Dual(u32 acr1 ,u32 amr1,u8 rtr_acr1,
							   u8 rtr_amr1,u8 Byte_acr1,u8 Byte_amr1,u8 ide)
 *@brief @b 功能描述:   CAN双ID过滤中ID1滤波设置 采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：       
 *                      acr1：ID1值（标志帧ID11位，扩展帧ID范围1D28~ID13即ID高16位有效） \n 
 *                      amr1：ID1屏蔽位                     
 *		                rtr_acr1： 接收（1远程/0数据帧）帧类型选择（只支持SFF模式，扩展帧配置无效） \n
 *		                rtr_amr1： 远程/标志帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志帧均接收
                                  （只支持SFF模式，扩展帧配置无效） \n
 *		                Byte_acr1：数据帧第1个Byte低4位滤波选择（只支持SFF模式，扩展帧配置无效） \n
 *		                Byte_amr1：数据帧第1个Byte低4位屏蔽位（只支持SFF模式，扩展帧配置无效） \n
 *                      ide：0标准(SFF模式)/1扩展帧 \n
 *                 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        
 *                      1、SFF模式为标准帧模式 \n
 *                      2、扩展帧时，只对ID的bit13- bit28即ID高16位进行筛选过滤 \n
 *                      3、因为双滤波ID1函数兼容标志准和扩展帧滤波（标准帧和扩展帧的双滤波有区别），所以该函数的形
 *                         参部分只支持标准帧模式配置使用，扩展帧模式配置无效。
 *@warning              无   
 *@par 示例代码：
 *@code   
      示例1： 
           //标准帧ID1接收滤波： ID:0X75A ,数据帧
           ID1_Filter_Dual(0X75A, 0x00, 0x0, 0x0，0x0F, 0x00, 0);
		   //接收的标准帧只有满足ID地址为0X75A且为数据帧且接收数据（不是帧的第一个数据，而是数据区的第一个数据）的第1个
		     Byte低4位为0XF才会接收。
      示例2：
           //扩展帧ID1接收滤波： ID:0XFECB的扩展帧
		   ID1_Filter_Dual(0XFECB, 0x00, 0x0, 0x0，0x00, 0x00,1);
		   //接收的扩展帧只有满足ID地址为0XFECB才会接收
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void ID1_Filter_Dual(u32 acr1, u32 amr1, u8 rtr_acr1, u8 rtr_amr1, u8 Byte_acr1, u8 Byte_amr1, u8 ide)
{
	CAN->MOD |= 1 << 0;	   // RESET MODE
	CAN->MOD &= ~(1 << 3); // 双滤波ID
	rtr_acr1 &= 0x1;
	rtr_amr1 &= 0x1;

	if (ide) /*扩展帧*/
	{
		acr1 &= 0x1fffffff;
		CAN_ACR1 = (u8)(acr1 >> 13);
		CAN_ACR0 = (u8)(acr1 >> 21);

		CAN_AMR1 = (u8)(amr1 >> 13);
		CAN_AMR0 = (u8)(amr1 >> 21);
	}
	else /*标准帧*/
	{
		acr1 &= 0x7ff;
		CAN_ACR0 = (u8)(acr1 >> 3);
		CAN_ACR1 = (u8)(acr1 << 5) | (rtr_acr1 << 4) | (Byte_acr1 >> 4);
		CAN_ACR3 &= 0xF0;
		CAN_ACR3 |= (u8)(Byte_acr1 & 0x0F);

		CAN_AMR0 = (u8)(amr1 >> 3);
		CAN_AMR1 = (u8)(amr1 << 5) | (rtr_amr1 << 4) | (Byte_amr1 >> 4);
		CAN_AMR3 &= 0xF0;
		CAN_AMR3 |= (u8)(Byte_amr1 & 0x0F);
	}
	CAN->MOD &= ~(1 << 0); //正常输出模式
}

/**
 *@brief @b 函数名称:   void ID2_Filter_Dual(u32 acr2 ,u32 amr2,u8 rtr_acr2,u8 rtr_amr2 ,u8 ide)
 *@brief @b 功能描述:   CAN双ID过滤中ID2滤波设置 采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：       
 *                      acr2：ID2值（范围1D28~ID13即ID高16位有效） \n 
 *                      amr2：ID2屏蔽位                      
 *		                rtr_acr2: 接收（1远程/0数据帧）帧类型选择（只支持SFF标准帧模式，扩展帧配置无效） \n
 *		                rtr_amr2：远程/标志帧滤波屏蔽位，0表示只接收rtr_acr类型帧，为1表示远程/0标志
 *					              帧均接收（只支持SFF标准帧模式，扩展帧配置无效） \n             
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        
 *                      1、SFF模式为标准帧模式 \n
 *                      2、扩展帧时，只对ID的bit13- bit28即ID高16位进行筛选过滤 \n
 *                      3、因为双滤波ID1函数兼容标志准和扩展帧滤波（标准帧和扩展帧的双滤波有区别），所以该函数的形
 *                         参部分只支持标准帧模式配置使用，扩展帧模式配置无效。
 *@warning              无   
 *@par 示例代码：
 *@code   
      示例1： 
           //标准帧ID2接收滤波： ID:0X75A ,数据帧
           ID2_Filter_Dual(0X75A, 0x00, 0x0, 0x0, 0);
		   //接收的标准帧只有满足ID地址为0X75A且为数据帧才会接收。
      示例2：
           //扩展帧ID2接收滤波： ID:0XFECB的扩展帧
		   ID2_Filter_Dual(0XFECB, 0x00, 0x0, 0x0,1);
		   //接收的扩展帧只有满足ID地址为0XFECB才会接收
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void ID2_Filter_Dual(u32 acr2, u32 amr2, u8 rtr_acr2, u8 rtr_amr2, u8 ide)
{
	CAN->MOD |= 1 << 0;	   // RESET MODE
	CAN->MOD &= ~(1 << 3); //双滤波ID
	rtr_acr2 &= 0x1;
	rtr_amr2 &= 0x1;
	if (ide) // externed
	{
		acr2 &= 0x1fffffff;
		CAN_ACR3 = (u8)(acr2 >> 13);
		CAN_ACR2 = (u8)(acr2 >> 21);

		CAN_AMR3 = (u8)(amr2 >> 13);
		CAN_AMR2 = (u8)(amr2 >> 21);
	}
	else
	{
		acr2 &= 0x7ff;
		CAN_ACR3 &= 0x0f;
		CAN_ACR2 = (u8)(acr2 >> 3);
		CAN_ACR3 |= (u8)(acr2 << 5) | (rtr_acr2 << 4);

		CAN_AMR3 &= 0x0f;
		CAN_AMR2 = (u8)(amr2 >> 3);
		CAN_AMR3 |= (u8)(amr2 << 5) | (rtr_amr2 >> 4);
	}
	CAN->MOD &= ~(1 << 0); //正常输出模式
}

/**
 *@brief @b 函数名称:   u8 My_CAN_Send_Msg(u32 id,u8 ide,u8 rtr,const u8 *msg,u8 len)
 *@brief @b 功能描述:   CAN轮询发送数据程序  采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：       
 *                      id: 发送id \n 
 *                      ide: 标准/扩展帧                      
 *		                rtr：远程帧/数据帧 \n
 *		                *msg: 发送的数据    
 *                      len:发送字节长度 \n          
 *@param输出参数：       无
 *@return返 回 值：      0：发送成功 !0：发送失败
 *@note其它说明：        
 *                      1、id:标准ID(11位)/扩展ID(11位+18位) \n
 *                      2、ide:0,标准帧;1,扩展帧 \n
 *                      3、rtr:0,数据帧;1,远程帧。
 *@warning              无   
 *@par 示例代码：
 *@code   
      示例1： 
	       u8 Can_TX[8] = {0x81, 0x23, 0x33, 0x44, 0x15, 0x26, 0x37, 0x48};
           // 发送数据 ID:0x03,标准帧,数据帧，数据，数据长度8字节
		   My_CAN_Send_Msg(0x5A, 0, 0, Can_TX, 8);
      示例2：
           u8 Can_TX[8] = {0x81, 0x23, 0x33, 0x44, 0x15, 0x26, 0x37, 0x48};
           // 发送数据 ID:0x03,扩展帧,数据帧，数据，数据长度8字节
		   My_CAN_Send_Msg(0X10005A5A, 1, 0, Can_TX, 8);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2018年08月10日 <td>1.0      <td>ZKW        <td>创建
 * </table>
 *@par 修改日志:增加自测模式发送数据功能
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年01月16日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */

u8 My_CAN_Send_Msg(u32 id, u8 ide, u8 rtr, u8 *msg, u8 len)
{
	u8 frame_inf = 0;
	u16 i = 0;

	if (CAN->SR & 0X04) // TFIFO 空
	{
		CAN->MOD &= ~(1 << 0);	//正常输出模式
		frame_inf |= ide << 7;	// 0标准/1扩展帧
		frame_inf |= rtr << 6;	// 0,数据帧;1,遥控帧
		frame_inf |= len << 0;	//发送数据长度
		CAN->TXRX0 = frame_inf; //发送TX帧信息
		if (0 == ide)			//标准帧
		{
			id &= 0x7ff;
			//发送接收寄存器1
			CAN->TXRX1 = id >> 3;		   // TX ID0
			CAN->TXRX2 = (id & 0X07) << 5; // TX ID1
			CAN->TXRX3 = msg[0];		   // TX DATA0
			CAN->TXRX4 = msg[1];		   // TX DATA1
			CAN->TXRX5 = msg[2];		   // TX DATA2
			CAN->TXRX6 = msg[3];		   // TX DATA3
			CAN->TXRX7 = msg[4];		   // TX DATA4
			CAN->TXRX8 = msg[5];		   // TX DATA5
			CAN->TXRX9 = msg[6];		   // TX DATA6
			CAN->TXRXA = msg[7];		   // TX DATA7
		}
		else //扩展帧
		{
			id &= 0X1FFFFFFF;
			CAN->TXRX1 = (u8)(id >> 21);		  // TX ID0
			CAN->TXRX2 = (u8)((id >> 13) & 0xFF); // TX ID1
			CAN->TXRX3 = (u8)((id >> 5) & 0xFF);  // TX ID2
			CAN->TXRX4 = (u8)((id & 0xff) << 3);  // TX ID3
			CAN->TXRX5 = msg[0];				  // TX DATA0
			CAN->TXRX6 = msg[1];				  // TX DATA1
			CAN->TXRX7 = msg[2];				  // TX DATA2
			CAN->TXRX8 = msg[3];				  // TX DATA3
			CAN->TXRX9 = msg[4];				  // TX DATA4
			CAN->TXRXA = msg[5];				  // TX DATA5
			CAN->TXRXB = msg[6];				  // TX DATA6
			CAN->TXRXC = msg[7];				  // TX DATA7
		}
		if ((CAN->MOD) & CAN_SELFTEST_MODE) /*CAN工作在自测模式*/
		{
			CAN->CMR |= 1 << 4; // CAN发送数据的同时也将数据接收回来
		}
		else
		{
			CAN->CMR |= 1 << 0; // CAN发送传输请求
		}
		while (!(CAN->SR & 0X08)) //最近一次是否传输完成
		{
			if ((i++) >= 0xfff)
			{
				return 0xff; //发送失败
			}
		};
		return 0; //发送完成
	}
	else // TFIFO非空
	{
		return 0xff; //发送失败
	}
}


/**
 *@brief @b 函数名称:   u8 CAN_Receive_Msg(uint32_t* id,u8* ide,u8* rtr,u8 *buf)
 *@brief @b 功能描述:   CAN轮询接收数据程序
 *@see被调用函数：       无
 *@param输入参数：       无                                
 *@param输出参数：       id:  接收帧id \n 
 *                      ide: 接收帧的类型，标准/扩展帧                      
 *		                rtr：接收帧的类型，远程帧/数据帧 \n 
 *		                *buf: 接收帧的数据存储缓存区    
 *@return返 回 值：      0：接收完成 !0：接收失败
 *@note其它说明：        
 *                      1、id:标准ID(11位)/扩展ID(11位+18位) \n
 *                      2、ide:0,标准帧;1,扩展帧 \n
 *                      3、rtr:0,数据帧;1,远程帧。
 *@warning              无   
 *@par 示例代码：
 *@code    
        //can_par.id存储接收帧ID，can_par.ide存储接收帧类型标准/扩展帧，
		  can_par.rtr存储接收帧类型远程帧/数据帧，can_par.RX存储接收帧数据
        CAN_Receive_Msg(&( can_par.id),&(can_par.ide),&(can_par.rtr),can_par.RX) ;
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2018年08月10日 <td>1.0      <td>ZKW        <td>创建
 * </table>
 */

u8 CAN_Receive_Msg(uint32_t *id, u8 *ide, u8 *rtr, u8 *buf)
{
	u8 reg_inf;

	if (CAN->SR & 0X01) // RFIFO 存有一帧或多帧数据，可以通过 RFIFO 寄存器读取
	{
		CAN->MOD &= ~(1 << 0); //正常输出模式
		reg_inf = CAN->TXRX0;  //读取的一帧或多帧数据
		if (reg_inf & 0x80)	   // EFF（扩展）帧
		{
			*ide = 1;
			*id = (CAN->TXRX1 << 21) | (CAN->TXRX2 << 13) | (CAN->TXRX3 << 5) | (CAN->TXRX4 >> 3); //获取ID
			if (reg_inf & 0x40)
			{
				*rtr = 1; //遥控帧
			}
			else
			{
				*rtr = 0; //数据帧
			}
			buf[0] = CAN->TXRX5; //获取数据
			buf[1] = CAN->TXRX6;
			buf[2] = CAN->TXRX7;
			buf[3] = CAN->TXRX8;
			buf[4] = CAN->TXRX9;
			buf[5] = CAN->TXRXA;
			buf[6] = CAN->TXRXB;
			buf[7] = CAN->TXRXC;
		}
		else // SFF（标准）帧
		{
			*ide = 0;
			if (reg_inf & 0x40)
			{
				*rtr = 1;
			}
			else
			{
				*rtr = 0;
			}

			*id = ((CAN->TXRX1 << 3) | (CAN->TXRX2 >> 5));
			buf[0] = CAN->TXRX3;
			buf[1] = CAN->TXRX4;
			buf[2] = CAN->TXRX5;
			buf[3] = CAN->TXRX6;
			buf[4] = CAN->TXRX7;
			buf[5] = CAN->TXRX8;
			buf[6] = CAN->TXRX9;
			buf[7] = CAN->TXRXA;
		}

		CAN->CMR |= 0x04; //释放接收缓冲区

		return 0; //接收完成
	}
	else // fifo is empty
	{
		return 0xff; //接收异常
	}
}


/**
 *@brief @b 函数名称:   uint8_t CAN_ReadState(CAN_TypeDef* CANx , uint32_t sr)
 *@brief @b 功能描述:   获取CAN状态
 *@see被调用函数：       无
 *@param输入参数：       sr:读取指定状态或者所有状态结果 \n 
 * <table>              <tr><th>CAN_ONBUS 	        <td>1：CAN 模块，处于 BUS OFF 状态，无数据发送接收动作 \n 
 *                                                      0：CAN 模块，可以发送数据到 CAN 总线，或接收 CAN 总线数据                          
 *						<tr><th>CAN_ERROV 			<td>1：CAN 传输产生的错误总数达到或超过 CAN_EWL 规定值 \n 
 *                                                      0：CAN 传输产生的错误总数低于 CAN_EWL 规定值
 *						<tr><th>CAN_TXING 			<td>1：CAN 模块正在发送一帧数据 \n 
 *                                                      0：CAN 模块没有发送数据的动作
 *						<tr><th>CAN_RXING 			<td>1：CAN 模块正在接收一帧数据 \n
 *                                                      0：CAN 模块没有接收数据的动作
 *						<tr><th>CAN_TRNASDONE 	    <td>1：最近一次传输已完成 \n 
 *                                                      0：最近一次传输未完成
 *						<tr><th>CAN_TFIFOEMPTY      <td>1：TFIFO 空，可以写入发送数据 \n 
 *                                                      0：TFIFO 非空，内部数据没有发送完毕
 *						<tr><th>CAN_RFIFOEMPTY      <td>1：RFIFO 存入的帧太多，已满，导致数据丢失 \n 
 *                                                      0：RFIFO 未满
 *						<tr><th>CAN_DATAAVAIL 	    <td>1：RFIFO 存有一帧或多帧数据，可以通过 RFIFO 寄存器读取 \n 
 *                                                      0：RFIFO 没有有效帧数据
 *						<tr><th>CAN_ALLSR 			<td>读取全部状态
 * </table>     
 *@param输出参数：       无
 *@return返 回 值：      返回指定状态结果或者所有状态结果
 * <table>              <tr><th>CAN_ONBUS 	        <td>1：CAN 模块，处于 BUS OFF 状态，无数据发送接收动作 \n 
 *                                                      0：CAN 模块，可以发送数据到 CAN 总线，或接收 CAN 总线数据                          
 *						<tr><th>CAN_ERROV 			<td>1：CAN 传输产生的错误总数达到或超过 CAN_EWL 规定值 \n 
 *                                                      0：CAN 传输产生的错误总数低于 CAN_EWL 规定值
 *						<tr><th>CAN_TXING 			<td>1：CAN 模块正在发送一帧数据 \n 
 *                                                      0：CAN 模块没有发送数据的动作
 *						<tr><th>CAN_RXING 			<td>1：CAN 模块正在接收一帧数据 \n
 *                                                      0：CAN 模块没有接收数据的动作
 *						<tr><th>CAN_TRNASDONE 	    <td>1：最近一次传输已完成 \n 
 *                                                      0：最近一次传输未完成
 *						<tr><th>CAN_TFIFOEMPTY      <td>1：TFIFO 空，可以写入发送数据 \n 
 *                                                      0：TFIFO 非空，内部数据没有发送完毕
 *						<tr><th>CAN_RFIFOEMPTY      <td>1：RFIFO 存入的帧太多，已满，导致数据丢失 \n 
 *                                                      0：RFIFO 未满
 *						<tr><th>CAN_DATAAVAIL 	    <td>1：RFIFO 存有一帧或多帧数据，可以通过 RFIFO 寄存器读取 \n 
 *                                                      0：RFIFO 没有有效帧数据
 *						<tr><th>CAN_ALLSR 			<td>读取全部状态
 * </table>   
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
        //判断CAN的RFIFO是否存有一帧或多帧数据，此时是否可以通过RFIFO寄存器读取 
		if(CAN_ReadState(CAN , CAN_DATAAVAIL) == CAN_DATAAVAIL)
		{
		}
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年04月29日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
uint8_t CAN_ReadState(CAN_TypeDef *CANx, uint32_t sr)
{
	return (uint8_t)(CANx->SR & sr);
}

/**
 *@brief @b 函数名称:   enumLossposition CAN_ReadALC(void)
 *@brief @b 功能描述:   获取仲裁丢失的具体位置
 *@see被应用枚举：       enumLossposition
 *@param输入参数：       无                                
 *@param输出参数：       无   
 *@return返 回 值：      返回仲裁丢失具体位置 enumLossposition
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
        if(CAN_ReadALC() == CAN_LOST_ID0)//总线仲裁丢失在ID的第一位
		{
		}
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年04月29日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
enumLossposition CAN_ReadALC(void)
{
	return (enumLossposition)CAN_ALC;
}

/**
 *@brief @b 函数名称:   uint8_t CAN_ReadRXERRCNT(void)
 *@brief @b 功能描述:   获取接收错误计数值
 *@see被应用枚举：       enumLossposition
 *@param输入参数：       无                                
 *@param输出参数：       无   
 *@return返 回 值：      返回接收错误计数值
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
        u8 err_value = 0;
		err_value = CAN_ReadRXERRCNT();//获取错误计数值个数
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年04月29日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
uint8_t CAN_ReadRXERRCNT(void)
{
	return CAN_RXERR;
}

/**
 *@brief @b 函数名称:   uint8_t CAN_ReadTXERRCNT(void)
 *@brief @b 功能描述:   获取发送错误计数值
 *@see被应用枚举：       enumLossposition
 *@param输入参数：       无                                
 *@param输出参数：       无   
 *@return返 回 值：      返回发送错误计数值
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
        u8 err_value = 0;
		err_value = CAN_ReadTXERRCNT();//获取错误计数值个数
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年04月29日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
uint8_t CAN_ReadTXERRCNT(void)
{
	return CAN_TXERR;
}

/**
 *@brief @b 函数名称:   void CAN_ReceFramInfor(uint8_t* cnt , uint8_t* rbsa )
 *@brief @b 功能描述:   获取接收缓冲区有效接收帧数与第一帧有效接收数据在 RFIFO的位置
 *@see被应用枚举：       enumLossposition
 *@param输入参数：       无                                
 *@param输出参数：       cnt：有效帧个数 \n
			            rbsa：RFIFO 的大小为 32 字节，rbsa存储第一帧有效接收数据在 RFIFO的位置0-31   
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
        u8 frames_number = 0 ， RFIFO_location = 0;//存储变量申请
		CAN_ReceFramInfor(frames_number，RFIFO_location);
		//frames_number接收缓冲区存储帧个数，RFIFO_location缓冲区最早读取的帧位置
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年04月29日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_ReceFramInfor(uint8_t *cnt, uint8_t *rbsa)
{
	*cnt = CAN_RMC;
	*rbsa = CAN_RBSA;
}

/**
 *@brief @b 函数名称:   void CAN_ReadErrorCode(enumErrortype* errtype , enumErrortime* errtim
									  , enumErrposition* errpos)
 *@brief @b 功能描述:   获取总线错误类型和错误位置
 *@see被应用枚举：       enumErrortype ， enumErrortime ， enumErrposition
 *@param输入参数：       errtype：总线错误类型     \n
						errtim： 总线错误发生时刻 \n
						errpos： 错误发生的位置   \n                               
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
        u8 err_type = 0 ， err_time = 0 , err_location = 0;//存储变量申请
		CAN_ReadErrorCode(err_type,err_time,err_location);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年04月29日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_ReadErrorCode(enumErrortype *errtype, enumErrortime *errtim, enumErrposition *errpos)
{
	*errtype = (enumErrortype)((CAN_ECC & 0xC0) >> 6);
	*errtim = (enumErrortime)((CAN_ECC & 0x20) >> 5);
	*errpos = (enumErrposition)(CAN_ECC & 0x1f);
}

/**
 *@brief @b 函数名称:   uint32_t CAN_GetIRQFlag(void)
 *@brief @b 功能描述:   获取中断标志与清除中断标志位
 *@see被应用枚举：       enumErrortype ， enumErrortime ， enumErrposition
 *@param输入参数：       无                              
 *@param输出参数：       无
 *@return返 回 值：      TIM中断标志
 *@note其它说明：        CAN中断标志位为读清除
 *@warning              无   
 *@par 示例代码：
 *@code    
        u8 CAN_SR 0;
		CAN_SR = CAN_GetIRQFlag();//获取CAN中断标志位且清除CAN中断标志位
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2022年04月29日 <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
uint32_t CAN_GetIRQFlag(void)
{
	return CAN_INTR;
}



