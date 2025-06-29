/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Main.c
 * 文件标识：
 * 内容摘要： 工程主代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： HuangMG
 * 完成日期： 2023年3月2日
 *******************************************************************************/
#include "hardware_init.h"

void Hardware_init(void);
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
 u8  FLASH_WRITE[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
 u32 FLASH_Trim = 0;
 u32 FLASH_READ[2] = {0,0};
int main(void)
{
    Hardware_init();                         //硬件初始化
	  erase_flag = 0x9A0D361F;                 //开启FLASH擦除模式
    EraseSector(0x0,Flash_NVR);              //擦除FLASH NVR用户区
	  erase_flag = 0;                          //关闭FLASH擦除模式
	
	  progm_flag = 0x9AFDA40C;                 //开启FLASH编程模式
    ProgramPage(0x0,8,FLASH_WRITE,Flash_NVR);//FLASH NVR用户区写入值
	  progm_flag = 0;                          //关闭FLASH 编程模式
	
    Read_More_Flash(0x0,2,FLASH_READ,Flash_NVR);//读取FLASH NVR用户区值

	  FLASH_Trim = Read_Trim(0x00001454);      //读取ADC校准参数
    for(;;)
    {
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

