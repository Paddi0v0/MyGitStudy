/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Main.c
 * 文件标识：
 * 内容摘要： 工程主代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/
#include "LKS32MC07x_lib.h" // Device header

void Hardware_init(void);
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    使用硬件CRC计算常见的CRC数据
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/10     V1.0           YangZJ            创建
 *******************************************************************************/

u8 crc_data[5] = {1, 2, 3, 4, 5};
u8 crc8_answer, crc8_ITU_answer, crc8_ROHC_answer, crc8_MAXIM_answer;
u16 crc16_IBM_answer, crc16_MAXIM_answer, crc16_USB_answer, crc16_MODBUS_answer, crc16_CCITT_answer, crc16_CCITT_FALSE_answer, crc16_X25_answer, crc16_XMODEM_answer, crc16_DNP_answer;
u32 crc32_answer, crc32_MPEG_2_answer;

int main(void)
{
    //    Hardware_init(); /* CRC不需要初始化，可以直接使用 */

    crc8_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_8);                           ///< 计算CRC_8
    crc8_ITU_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_8_ITU);                   ///< 计算CRC_8_ITU
    crc8_ROHC_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_8_ROHC);                 ///< 计算CRC_8_ROHC
    crc8_MAXIM_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_8_MAXIMx);              ///< 计算CRC_8_MAXIMx
    crc16_IBM_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_IBMx1);               ///< 计算CRC_16_IBMx1
    crc16_MAXIM_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_MAXIM);             ///< 计算CRC_16_MAXIM
    crc16_USB_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_USBx1);               ///< 计算CRC_16_USBx1
    crc16_MODBUS_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_MODBU);            ///< 计算CRC_16_MODBU
    crc16_CCITT_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_CCITT);             ///< 计算CRC_16_CCITT
    crc16_CCITT_FALSE_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_CCITT_FALSE); ///< 计算CRC_16_CCITT_FALSE
    crc16_X25_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_X25);                 ///< 计算CRC_16_X25
    crc16_XMODEM_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_XMODEM);           ///< 计算CRC_16_XMODEM
    crc16_DNP_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_16_DNP);                 ///< 计算CRC_16_DNP
    crc32_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_32);                         ///< 计算CRC_32
    crc32_MPEG_2_answer = CRC_CalcCommon(CRC0, crc_data, sizeof(crc_data), CRC_MODEL_CRC_32_MPEG_2);           ///< 计算CRC_32_MPEG_2
    for (;;)
    {
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
