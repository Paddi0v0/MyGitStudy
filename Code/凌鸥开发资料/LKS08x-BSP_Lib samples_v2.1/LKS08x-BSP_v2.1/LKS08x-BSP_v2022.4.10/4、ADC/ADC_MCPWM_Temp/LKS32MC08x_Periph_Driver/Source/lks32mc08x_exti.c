/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc081_exti.c
 * 文件标识：
 * 内容摘要： EXTI外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： 
 * 完成日期： 
 *
 * 修改记录1：
 * 修改日期：
 * 版 本 号：V 1.0
 * 修 改 人：
 * 修改内容：创建
 *
 * 修改记录2：
 * 修改日期： 2016年6月19日
 * 版 本 号： v1.1
 * 修 改 人： cfwu
 * 修改内容： 按照ChanHomB定义修改
 *
 *******************************************************************************/
#include "lks32mc08x_exti.h"
#include "lks32mc08x.h"

/*******************************************************************************
 函数名称：    void EXTI_Init(EXTI_TypeDef* EXTIx, EXTI_InitTypeDef* EXTI_InitStruct)
 功能描述：    EXTI初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/04/19      V1.0           cfwu              创建
 *******************************************************************************/
void EXTI_Init(EXTI_TypeDef* EXTIx, EXTI_InitTypeDef* EXTI_InitStruct)
{
/*   EXTIx->CR0 = (EXTI_InitStruct->Pad0Trig) | (EXTI_InitStruct->Pad1Trig << 2)
	            | (EXTI_InitStruct->Pad2Trig << 4) | (EXTI_InitStruct->Pad3Trig << 6)
                | (EXTI_InitStruct->Pad4Trig << 8) | (EXTI_InitStruct->Pad5Trig << 10)
	            | (EXTI_InitStruct->Pad6Trig << 12) | (EXTI_InitStruct->Pad7Trig << 14);

   EXTIx->CR1 = (EXTI_InitStruct->Pad8Trig) | (EXTI_InitStruct->Pad9Trig << 2)
	            | (EXTI_InitStruct->Pad10Trig << 4) | (EXTI_InitStruct->Pad11Trig << 6)
                | (EXTI_InitStruct->Pad12Trig << 8) | (EXTI_InitStruct->Pad13Trig << 10)
	            | (EXTI_InitStruct->Pad14Trig << 12) | (EXTI_InitStruct->Pad15Trig << 14);*/
	
   uint32_t padpos = 0x00, pos = 0x00, currentpad = 0x00, tempreg = 0x00;

   /*-------------------------- Configure the port pins -----------------------*/
   for (padpos = 0x00; padpos < 0x10; padpos++)
   {
      pos = ((uint32_t)0x01) << padpos;
		
      /* Get the port pins position */
      currentpad = (EXTI_InitStruct->EXTI_Pad) & pos;
      if (currentpad > 0)
      {
				 if (padpos <= 7)                     /*EXTI0->CR0*/
				 {
						 tempreg = EXTIx->CR0;
						 tempreg &= ~(0x0003 << (2*(padpos)));
						 tempreg |= (EXTI_InitStruct->EXTI_Trig << (2*padpos));
						 EXTIx->CR0 = tempreg;
				 }
         else                                 /*EXTI0->CR1*/
				 {
						 tempreg = EXTIx->CR1;
						 tempreg &= ~(0x0003 << (2*(padpos-8)));
						 tempreg |= (EXTI_InitStruct->EXTI_Trig << (2*(padpos-8)));
						 EXTIx->CR1 = tempreg;					 
				 }
			}
	 }	
}

/*******************************************************************************
 函数名称：    void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
 功能描述：    EXTI结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/4/19      V1.0           cfwu              创建
 *******************************************************************************/
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
   EXTI_InitStruct->EXTI_Pad = EXTI_Pad_None;
   EXTI_InitStruct->EXTI_Trig = EXTI_TRG_None;	
/*   EXTI_InitStruct->Pad0Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad1Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad2Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad3Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad4Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad5Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad6Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad7Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad8Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad9Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad10Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad11Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad12Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad13Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad14Trig = EXTI_NONE_TRG;
   EXTI_InitStruct->Pad15Trig = EXTI_NONE_TRG;*/
}

/*******************************************************************************
 函数名称：    uint32_t EXTI_ReadIFFlag(EXTI_TypeDef* EXTIx)
 功能描述：    读取EXTI中断标志
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/4/19      V1.0           cfwu              创建
 *******************************************************************************/
uint32_t EXTI_ReadIFFlag(EXTI_TypeDef* EXTIx)
{
   return EXTIx->IF;
}

/*******************************************************************************
 函数名称：    void EXTI_Reset(EXTI_TypeDef* EXTIx)
 功能描述：    EXTI清除中断标志
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/4/19      V1.0           cfwu              创建
 *******************************************************************************/
void EXTI_ResetIF(EXTI_TypeDef* EXTIx, uint32_t temp)
{
   EXTIx->IF = temp;
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
