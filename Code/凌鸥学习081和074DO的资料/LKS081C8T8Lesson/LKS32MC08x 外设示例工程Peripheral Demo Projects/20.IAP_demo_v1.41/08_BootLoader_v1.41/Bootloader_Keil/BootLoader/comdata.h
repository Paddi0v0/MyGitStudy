#ifndef COMDATA_H_
#define COMDATA_H_

#include "lks32mc08x.h"


#define    APP_ADDR     0XA00 

#define MAXSEND_LEN  		8
#define MAXFILEDATA_LEN		200

#define MINRECV_LEN		    12
#define MAXRECV_LEN		    (MAXFILEDATA_LEN+10)	//接收报文最大长度

#define INDEX_LEN		6				//报文长度的字节序号
#define INDEX_CMD		7				//命令类型的字节序号
#define INDEX_VERIFYCRC	8
#define INDEX_CONTI		8				//文件内容后续标志位字节序号
#define INDEX_FILEDATA	9				//文件内容起始字节序号

#define CMD_VERIFYREQ	0x05			//校验请求
#define CMD_DOWNREQ		0x06			//烧写请求
#define CMD_REQCONF		0x07			//确认

#define CMD_ERASEOK		0x17			//flash擦除完毕，可以下发文件
#define CMD_DOWNFINISH	0x08			//chip上送下载完成
#define CMD_FILE		0x2B			//
#define CMD_ERRCRC		0x09			//
#define CMD_ERRLEN		0x0A			//
#define CMD_DATACONFIRM	0x0B			//chip上送数据确认

#define CMD_VERIFYOK	0x0C
#define CMD_VERIFYFAIL	0x0D


// 同步字EB90 EB90 EB90
#define ISSYNC(buf)	\
	( (buf[0]==0xEB) && (buf[2]==0xEB) && (buf[4]==0xEB) && \
      (buf[1]==0x90) && (buf[3]==0x90) && (buf[5]==0x90) )
	
void InitCom(void);														//初始化通信串口参数

void InitRecvData(void);
void InitHexData(void);
void AddRecvData(u8 data);

void CheckRecvData(void);
void HandleCmd(void);
void HandleError(void);

void HandleDownload(void);
void HandleVerify(void);
void HandleFileData(void);
void DoVerify(void);

void SendToPC(UINT8 byCMD);
void StartUserProc(void);

UINT8 CalcByteCRC(UINT8 *pData, UINT8 len);
UINT32 CharToLong(UINT8 *pData);

#endif

