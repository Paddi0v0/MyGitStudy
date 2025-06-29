/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： CRC_fun.c
 * 文件标识：
 * 内容摘要： 硬件CRC校验程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：
 * 完成日期： 2021年3月12日
 *
 * 修改记录1：
 * 修改日期：2021年3月12日
 * 版 本 号：V 1.0
 * 修 改 人：
 * 修改内容：

 * 修改记录2：
 * 修改日期：2021年7月05日
 * 版 本 号：V 1.1
 * 修 改 人：yangzj
 * 修改内容：补全crc公式
 
 * 修改记录2：
 * 修改日期：2021年3月24日
 * 版 本 号：V 1.2
 * 修 改 人：yangzj
 * 修改内容：修复CRC16/CRC32输入数据必须为u16/u32的问题
 *
 *******************************************************************************/
#include "lks32mc08x.h"
#include "CRC_fun.h"
#include "basic.h"
/*******************************************************************************
 函数名称：    u32 crc32(u32 *pData,u32 uLen)
 功能描述：    crc32计算程序
 输入参数：    *pData 指向待计算crc的数组
			   uLen  数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u32 crc32(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, val_REFOUT, val_REFIN, POLY_SIZE;
	u32 val_XOROUT, val_POLY, val_INIT;

	val_POLY = 0x04c11db7;
	val_INIT = 0xffffffff;
	val_XOROUT = 0xffffffff;

	val_REFOUT = ENABLE; //输出数据反转使能
	val_REFIN = ENABLE;	 //输入数据反转使能

	REV_OUT_TYPE = val_REFOUT;
	REV_IN_TYPE = (val_REFIN) ? 3 : 0;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 0;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0; //复位
	CRC_POL = val_POLY;
	CRC_INIT = val_INIT;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	return (REG32(&CRC_DR)) ^ val_XOROUT;
}

/*******************************************************************************
 函数名称：    u32 crc32_MPEG_2(u32 *pData,u32 uLen)
 功能描述：    crc32_MPEG_2计算
 输入参数：    *pData 指向待计算crc的数组
			   uLen  数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u32 crc32_MPEG_2(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, val_REFOUT, val_REFIN, POLY_SIZE;
	u32 val_XOROUT, val_POLY, val_INIT;

	val_POLY = 0x04c11db7;	 //多项式
	val_INIT = 0xffffffff;	 //初始值
	val_XOROUT = 0x00000000; //结果异或值

	val_REFOUT = DISABLE; //输出数据反转使能
	val_REFIN = DISABLE;  //输入数据反转使能

	REV_OUT_TYPE = val_REFOUT;
	REV_IN_TYPE = (val_REFIN) ? 3 : 0;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 0;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0; //复位
	CRC_POL = val_POLY;
	CRC_INIT = val_INIT;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	return (REG32(&CRC_DR)) ^ val_XOROUT;
}
u16 crc16_IBM(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;
	out_XOR = 0x0000;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能
	REV_IN_TYPE = 2;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x8005; // crc16计算公式
	CRC_INIT = 0x0000;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			if (REV_IN_TYPE)
			{
				REG8(&CRC_DR) = *pData;
			}
			else
			{
				REG8(&CRC_DR) = (((*pData & 0xff00) >> 8) | ((*pData & 0x00ff) << 8));
			}
			// crc_dr地址是32位的数据
			//计算CRC8和CRC16时需要按照8/16位写入
			//按照32位写入数据会造成错误的结果
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_MAXIM(u16 *pData,u16 uLen)
 功能描述：    crc16_MAXIM算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_MAXIM(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;
	out_XOR = 0xffff;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能
	REV_IN_TYPE = 2;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x8005; // crc16计算公式
	CRC_INIT = 0x0000;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_USB(u16 *pData,u16 uLen)
 功能描述：    crc16_USB算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_USB(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;

	out_XOR = 0xffff;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能

	REV_IN_TYPE = 2;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x8005; // crc16计算公式
	CRC_INIT = 0xffff;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_MODBUS(u16 *pData,u16 uLen)
 功能描述：    crc16_MODBUS算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_MODBUS(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;

	out_XOR = 0x0000;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能

	REV_IN_TYPE = 2;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x8005; // crc16计算公式
	CRC_INIT = 0xffff;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_CCITT(u16 *pData,u16 uLen)
 功能描述：    crc16_CCITT算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_CCITT(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;

	out_XOR = 0x0000;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能

	REV_IN_TYPE = 2;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x1021; // crc16计算公式
	CRC_INIT = 0x0000;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_CCITT_FALSE(u16 *pData,u16 uLen)
 功能描述：    crc16_CCITT_FALSE算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_CCITT_FALSE(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;

	out_XOR = 0x0000;
	REV_OUT_TYPE = DISABLE; //输出数据反转使能

	REV_IN_TYPE = 0;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x1021; // crc16计算公式
	CRC_INIT = 0xffff;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_X25(u16 *pData,u16 uLen)
 功能描述：    crc16_X25算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_X25(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;

	out_XOR = 0xffff;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能

	REV_IN_TYPE = 2;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x1021; // crc16计算公式
	CRC_INIT = 0xffff;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_XMODEM(u16 *pData,u16 uLen)
 功能描述：    crc16_XMODEM算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_XMODEM(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;
	out_XOR = 0x0000;
	REV_OUT_TYPE = DISABLE; //输出数据反转使能
	REV_IN_TYPE = 0;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x1021; // crc16计算公式
	CRC_INIT = 0x0000;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc16_DNP(u16 *pData,u16 uLen)
 功能描述：    crc16_DNP算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u16 crc16_DNP(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u16 out_XOR;

	out_XOR = 0xffff;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能

	REV_IN_TYPE = 2;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 1;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0;	  //复位
	CRC_POL = 0x3d65; // crc16计算公式
	CRC_INIT = 0x0000;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u16)(CRC_DR >> 16)) ^ out_XOR;
	}
	else
	{
		return (REG16(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u8 crc8(u8 *pData,u32 uLen)
 功能描述：    crc8计算程序
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u8 crc8(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u8 out_XOR;
	out_XOR = 0x00;
	REV_OUT_TYPE = DISABLE; //输出数据反转使能
	REV_IN_TYPE = 0;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 2;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0; //复位
	CRC_POL = 0x07; // crc8计算公式
	CRC_INIT = 0x00;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u8)(CRC_DR >> 24)) ^ out_XOR;
	}
	else
	{
		return (REG8(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u8 crc8_ITU(u8 *pData,u32 uLen)
 功能描述：    crc8_ITU计算程序
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u8 crc8_ITU(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u8 out_XOR;
	out_XOR = 0x55;
	REV_OUT_TYPE = DISABLE; //输出数据反转使能
	REV_IN_TYPE = 0;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 2;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0; //复位
	CRC_POL = 0x07; // crc8计算公式
	CRC_INIT = 0x00;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u8)(CRC_DR >> 24)) ^ out_XOR;
	}
	else
	{
		return (REG8(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc8_ROHC(u16 *pData,u16 uLen)
 功能描述：    crc8_ROHC算法参考
 输入参数：    *pData指向待计算crc的数组
			  uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u8 crc8_ROHC(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u8 out_XOR;

	out_XOR = 0x00;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能

	REV_IN_TYPE = 1;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 2;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0; //复位
	CRC_POL = 0x07; // crc8计算公式
	CRC_INIT = 0xff;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			// crc_dr地址是32位的数据
			//计算CRC8和CRC16时需要按照8/16位写入
			//按照32位写入数据会造成错误的结果
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u8)(CRC_DR >> 24)) ^ out_XOR;
	}
	else
	{
		return (REG8(&CRC_DR)) ^ out_XOR;
	}
}
/*******************************************************************************
 函数名称：    u16 crc8_MAXIM(u16 *pData,u16 uLen)
 功能描述：    crc8_MAXIM算法参考
 输入参数：    *pData指向待计算crc的数组
			   uLen数组长度
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 *******************************************************************************/
u8 crc8_MAXIM(u8 *pData, u32 uLen)
{
	u8 REV_OUT_TYPE, REV_IN_TYPE, POLY_SIZE;
	u8 out_XOR;

	out_XOR = 0x00;
	REV_OUT_TYPE = ENABLE; //输出数据反转使能

	REV_IN_TYPE = 1;
	/*
		REV_IN_TYPE
		待编码数据反转类型
		0:不反转
		1:按字节反转，即 b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]
		2:按半字（ 16bit ） 反 转 ， 即 b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]
		3:按字反转，即 b[31]=b[0], b[30]=b[1],… [b0]=b[31]
	*/
	POLY_SIZE = 2;
	/*
		输出编码（多项式）位宽
		0: 32bits
		1: 16bits
		2: 8bits
		3: 7bits
	*/
	CRC_CR = (REV_OUT_TYPE << 12 | REV_IN_TYPE << 8 | POLY_SIZE << 4);
	CRC_CR |= BIT0; //复位
	CRC_POL = 0x31; // crc8计算公式
	CRC_INIT = 0x00;
	if (uLen == 0)
		return 0;
	else
		while (uLen--)
		{
			REG8(&CRC_DR) = *pData;
			// crc_dr地址是32位的数据
			//计算CRC8和CRC16时需要按照8/16位写入
			//按照32位写入数据会造成错误的结果
			pData++;
		}
	if (REV_OUT_TYPE == ENABLE)
	{
		return ((u8)(CRC_DR >> 24)) ^ out_XOR;
	}
	else
	{
		return (REG8(&CRC_DR)) ^ out_XOR;
	}
}
