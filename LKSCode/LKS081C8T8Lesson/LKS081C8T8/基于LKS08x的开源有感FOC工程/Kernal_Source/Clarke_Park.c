#include "global_variable.h"

#define divSQRT_3	(s16) 0x49E6    /* 1/sqrt(3) in q1.15 format=0.5773315*/
#define SIN_MASK 	0x0300
#define U0_90     	0x0200
#define U90_180   	0x0300
#define U180_270  	0x0000
#define U270_360  	0x0100

#define SIN_COS_TABLE { \
		0x0000,0x00C9,0x0192,0x025B,0x0324,0x03ED,0x04B6,0x057F,\
		0x0648,0x0711,0x07D9,0x08A2,0x096A,0x0A33,0x0AFB,0x0BC4,\
		0x0C8C,0x0D54,0x0E1C,0x0EE3,0x0FAB,0x1072,0x113A,0x1201,\
		0x12C8,0x138F,0x1455,0x151C,0x15E2,0x16A8,0x176E,0x1833,\
		0x18F9,0x19BE,0x1A82,0x1B47,0x1C0B,0x1CCF,0x1D93,0x1E57,\
		0x1F1A,0x1FDD,0x209F,0x2161,0x2223,0x22E5,0x23A6,0x2467,\
		0x2528,0x25E8,0x26A8,0x2767,0x2826,0x28E5,0x29A3,0x2A61,\
		0x2B1F,0x2BDC,0x2C99,0x2D55,0x2E11,0x2ECC,0x2F87,0x3041,\
		0x30FB,0x31B5,0x326E,0x3326,0x33DF,0x3496,0x354D,0x3604,\
		0x36BA,0x376F,0x3824,0x38D9,0x398C,0x3A40,0x3AF2,0x3BA5,\
		0x3C56,0x3D07,0x3DB8,0x3E68,0x3F17,0x3FC5,0x4073,0x4121,\
		0x41CE,0x427A,0x4325,0x43D0,0x447A,0x4524,0x45CD,0x4675,\
		0x471C,0x47C3,0x4869,0x490F,0x49B4,0x4A58,0x4AFB,0x4B9D,\
		0x4C3F,0x4CE0,0x4D81,0x4E20,0x4EBF,0x4F5D,0x4FFB,0x5097,\
		0x5133,0x51CE,0x5268,0x5302,0x539B,0x5432,0x54C9,0x5560,\
		0x55F5,0x568A,0x571D,0x57B0,0x5842,0x58D3,0x5964,0x59F3,\
		0x5A82,0x5B0F,0x5B9C,0x5C28,0x5CB3,0x5D3E,0x5DC7,0x5E4F,\
		0x5ED7,0x5F5D,0x5FE3,0x6068,0x60EB,0x616E,0x61F0,0x6271,\
		0x62F1,0x6370,0x63EE,0x646C,0x64E8,0x6563,0x65DD,0x6656,\
		0x66CF,0x6746,0x67BC,0x6832,0x68A6,0x6919,0x698B,0x69FD,\
		0x6A6D,0x6ADC,0x6B4A,0x6BB7,0x6C23,0x6C8E,0x6CF8,0x6D61,\
		0x6DC9,0x6E30,0x6E96,0x6EFB,0x6F5E,0x6FC1,0x7022,0x7083,\
		0x70E2,0x7140,0x719D,0x71F9,0x7254,0x72AE,0x7307,0x735E,\
		0x73B5,0x740A,0x745F,0x74B2,0x7504,0x7555,0x75A5,0x75F3,\
		0x7641,0x768D,0x76D8,0x7722,0x776B,0x77B3,0x77FA,0x783F,\
		0x7884,0x78C7,0x7909,0x794A,0x7989,0x79C8,0x7A05,0x7A41,\
		0x7A7C,0x7AB6,0x7AEE,0x7B26,0x7B5C,0x7B91,0x7BC5,0x7BF8,\
		0x7C29,0x7C59,0x7C88,0x7CB6,0x7CE3,0x7D0E,0x7D39,0x7D62,\
		0x7D89,0x7DB0,0x7DD5,0x7DFA,0x7E1D,0x7E3E,0x7E5F,0x7E7E,\
		0x7E9C,0x7EB9,0x7ED5,0x7EEF,0x7F09,0x7F21,0x7F37,0x7F4D,\
		0x7F61,0x7F74,0x7F86,0x7F97,0x7FA6,0x7FB4,0x7FC1,0x7FCD,\
		0x7FD8,0x7FE1,0x7FE9,0x7FF0,0x7FF5,0x7FF9,0x7FFD,0x7FFE}
	  
const s16 hSin_Cos_Table[256] = SIN_COS_TABLE;
		
#define START_INDEX     63

const u16 circle_limit_table[65] =
{ 32767, 32390, 32146, 31907, 31673, 31444, 31220, 31001, 30787, 30577, 30371,
      30169, 29971, 29777, 29587, 29400, 29217, 29037, 28861, 28687, 28517,
      28350, 28185, 28024, 27865, 27709, 27555, 27404, 27256, 27110, 26966,
      26824, 26685, 26548, 26413, 26280, 26149, 26019, 25892, 25767, 25643,
      25521, 25401, 25283, 25166, 25051, 24937, 24825, 24715, 24606, 24498,
      24392, 24287, 24183, 24081, 23980, 23880, 23782, 23684, 23588, 23493,
      23400, 23307, 23215, 23125 };

/*******************************************************************************
 函数名称：    stru_CurrVoctor Clarke(stru_CurrVoctor Curr_Input)
 功能描述：    Clarke变换
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
stru_CurrVoctor Clarke(stru_CurrVoctor Curr_Input)
{
   stru_CurrVoctor Curr_Output = { 0, 0 };

   s16 qIa_divSQRT3;
   s16 qIb_divSQRT3;

   // qIalpha = qIas
   Curr_Output.qI_Value1 = Curr_Input.qI_Value1;

   qIa_divSQRT3 = (s32) divSQRT_3 * Curr_Input.qI_Value1 >> 15;
   qIb_divSQRT3 = (s32) divSQRT_3 * Curr_Input.qI_Value2 >> 15;

   //qIbeta = -(2*qIbs+qIas)/sqrt(3)
   Curr_Output.qI_Value2 = (-(qIa_divSQRT3) - (qIb_divSQRT3) - (qIb_divSQRT3));

   return (Curr_Output);
}
/*******************************************************************************
 函数名称：    stru_CurrVoctor Park(stru_CurrVoctor Curr_Input, s16 Theta, stru_FOC_CurrLoopDef *this)
 功能描述：    Park变换
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
stru_CurrVoctor Park(stru_CurrVoctor Curr_Input, s16 Theta, stru_FOC_CurrLoopDef *this)
{
   stru_CurrVoctor Curr_Output = { 0, 0 };
   
   s16 qId_1, qId_2;
   s16 qIq_1, qIq_2;

   this->struTrigSinCos = Trig_Functions(Theta);

   qIq_1 = (s32) Curr_Input.qI_Value1 * this->struTrigSinCos.hCos >> 15;
   qIq_2 = (s32) Curr_Input.qI_Value2 * this->struTrigSinCos.hSin >> 15;
   //Iq component in Q1.15 Format 
   Curr_Output.qI_Value1 = ((qIq_2) - (qIq_1));

   qId_1 = (s32) Curr_Input.qI_Value1 * this->struTrigSinCos.hSin >> 15;
   qId_2 = (s32) Curr_Input.qI_Value2 * this->struTrigSinCos.hCos >> 15;
   //Id component in Q1.15 Format   
   Curr_Output.qI_Value2 = ((qId_1) + (qId_2));

   return (Curr_Output);
}

/*******************************************************************************
 函数名称：    stru_VoltVoctor Rev_Park(stru_VoltVoctor Volt_Input, stru_FOC_CurrLoopDef *this)
 功能描述：    Rev_Park 反Park变换
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
stru_VoltVoctor Rev_Park(stru_VoltVoctor Volt_Input, stru_FOC_CurrLoopDef *this)
{
   s16 qValpha_1, qValpha_2, qVbeta_1, qVbeta_2;
   stru_VoltVoctor Volt_Output = { 0, 0 };

   qValpha_1 = (s32) Volt_Input.qV_Value2 * this->struTrigSinCos.hCos >> 15;
   qValpha_2 = (s32) Volt_Input.qV_Value1 * this->struTrigSinCos.hSin >> 15;

   Volt_Output.qV_Value2 = ((qValpha_1) + (qValpha_2));

   qVbeta_1 = (s32) Volt_Input.qV_Value2 * this->struTrigSinCos.hSin >> 15;
   qVbeta_2 = (s32) Volt_Input.qV_Value1 * this->struTrigSinCos.hCos >> 15;

   Volt_Output.qV_Value1 = -(qVbeta_1) + (qVbeta_2);

   return (Volt_Output);
}
/*******************************************************************************
 函数名称：    stru_TrigComponents Trig_Functions(s16 hAngle)
 功能描述：    三角运算
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
stru_TrigComponents Trig_Functions(s16 hAngle)
{
   u16 hindex;
   stru_TrigComponents Local_Components =
   { 0, 0 };
 
   hindex = (u16)(hAngle + 32768) >> 6;

   switch (hindex & SIN_MASK)
   {
      case U0_90:
         Local_Components.hSin = hSin_Cos_Table[(u8)(hindex)];
         Local_Components.hCos = hSin_Cos_Table[(u8)(0xFF - (u8)(hindex))];
         break;

      case U90_180:
         Local_Components.hSin = hSin_Cos_Table[(u8)(0xFF - (u8)(hindex))];
         Local_Components.hCos = -hSin_Cos_Table[(u8)(hindex)];
         break;

      case U180_270:
         Local_Components.hSin = -hSin_Cos_Table[(u8)(hindex)];
         Local_Components.hCos = -hSin_Cos_Table[(u8)(0xFF - (u8)(hindex))];
         break;

      case U270_360:
         Local_Components.hSin = -hSin_Cos_Table[(u8)(0xFF - (u8)(hindex))];
         Local_Components.hCos = hSin_Cos_Table[(u8)(hindex)];
         break;
      default:
         break;
   }
   
   return (Local_Components);
}
/*******************************************************************************
 函数名称：    void RevPark_Circle_Limitation(stru_FOC_CtrProcDef *pCtrProc)
 功能描述：    电压极限圆限制
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void RevPark_Circle_Limitation(stru_FOC_CtrProcDef *pCtrProc)
{
	s32 t_value;
	
	stru_FOC_CurrLoopDef *this;

    this = &pCtrProc->struFOC_CurrLoop;

    t_value = (this->struStatVolt_q_d.qV_Value1 * this->struStatVolt_q_d.qV_Value1) 
			 + this->struStatVolt_q_d.qV_Value2 * this->struStatVolt_q_d.qV_Value2;
	
	if (t_value > (u32)(( 32767 * 32767) ) )
	{
		u16 index;

		t_value /= (u32)(512*32768);  // min value START_INDEX, max value 127
		t_value -= START_INDEX;// min value 0, max value 127 - START_INDEX
		index = circle_limit_table[(u8)t_value];

		t_value = (s16)this->struStatVolt_q_d.qV_Value1 * (u16)(index);
		this->struStatVolt_q_d.qV_Value1 = (s16)(t_value/32768);

		t_value = (s16)this->struStatVolt_q_d.qV_Value2 * (u16)(index);
		this->struStatVolt_q_d.qV_Value2 = (s16)(t_value/32768);
	}
}


