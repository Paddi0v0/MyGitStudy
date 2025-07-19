/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： main.c
 * 文件标识：
 * 内容摘要： 硬件CRC校验例程
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：
 * 完成日期： 2021年3月12日
 *
 * 修改记录1：
 * 修改日期：2021年3月12日
 * 版 本 号：V 1.0
 * 修 改 人：yangzj
 * 修改内容：创建

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
#include "hardware_config.h"
#include "CRC_fun.h"
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
 *******************************************************************************/

#define crc_data_define crc_data
#define crc_data_len_define 5
u8 crc_data[5] = {1, 2, 3, 4, 5};
u8 crc8_answer, crc8_ITU_answer, crc8_ROHC_answer, crc8_MAXIM_answer;
u16 crc16_IBM_answer, crc16_MAXIM_answer, crc16_USB_answer, crc16_MODBUS_answer, crc16_CCITT_answer, crc16_CCITT_FALSE_answer, crc16_X25_answer, crc16_XMODEM_answer, crc16_DNP_answer;
u32 crc32_answer, crc32_MPEG_2_answer;

int main(void)
{
    Hardware_init(); /* 硬件初始化 */
    crc8_answer = crc8(crc_data_define, crc_data_len_define);
    crc8_ITU_answer = crc8_ITU(crc_data_define, crc_data_len_define);
    crc8_ROHC_answer = crc8_ROHC(crc_data_define, crc_data_len_define);
    crc8_MAXIM_answer = crc8_MAXIM(crc_data_define, crc_data_len_define);

    crc16_IBM_answer = crc16_IBM(crc_data_define, crc_data_len_define);
    crc16_MAXIM_answer = crc16_MAXIM(crc_data_define, crc_data_len_define);
    crc16_USB_answer = crc16_USB(crc_data_define, crc_data_len_define);
    crc16_MODBUS_answer = crc16_MODBUS(crc_data_define, crc_data_len_define);
    crc16_CCITT_answer = crc16_CCITT(crc_data_define, crc_data_len_define);
    crc16_CCITT_FALSE_answer = crc16_CCITT_FALSE(crc_data_define, crc_data_len_define);
    crc16_X25_answer = crc16_X25(crc_data_define, crc_data_len_define);
    crc16_XMODEM_answer = crc16_XMODEM(crc_data_define, crc_data_len_define);
    crc16_DNP_answer = crc16_DNP(crc_data_define, crc_data_len_define);

    crc32_answer = crc32(crc_data_define, crc_data_len_define);
    crc32_MPEG_2_answer = crc32_MPEG_2(crc_data_define, crc_data_len_define);
    for (;;)
    {
    }
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
