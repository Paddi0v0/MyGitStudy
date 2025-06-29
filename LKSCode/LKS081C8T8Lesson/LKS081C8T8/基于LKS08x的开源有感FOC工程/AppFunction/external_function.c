#include "Global_Variable.h"
#include "hardware_config.h"
#include "function_config.h" 

/*******************************************************************************
 函数名称：    void key_in_proc(void) 
 功能描述：    外部功能程序
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void key_in_proc(void)
{
	key_capture(&stru_motorcomprehensive);  	/* 端口输入去抖 */
	
	motor_break();								/* 刹车 */

	Power_Options();							/* 工作电压 */
}

/*******************************************************************************
 函数名称：    void motor_break(void) 
 功能描述：    刹车程序
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void motor_break(void)
{
	if((stru_motorcomprehensive.nInputPort_State & BREAK_INPUT) == 0)		
	{   	
		strubreak_eabs.break_flg = 1;
	}
	else
	{	
		strubreak_eabs.break_flg = 0;
	}
}

/*******************************************************************************
 函数名称：    void Power_Options(void) 
 功能描述：    工作电压程序
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void Power_Options (void)
{
    if(strupower_up.power_up_time < 100)/* 上电1秒内判断电压选择 */
    {
		stru_VoltageProtect.hLowVoltageThd = VOLATAGE_42V;
		stru_VoltageProtect.hOverVoltageThd = VOLATAGE_62V;
		stru_VoltageProtect.hOverVoltageRsmThd = VOLATAGE_60V;
		stru_VoltageProtect.hLowVoltageRsmThd = stru_VoltageProtect.hLowVoltageThd + VOLATAGE_0_5V;
    }
}

/*******************************************************************************
 函数名称：    void key_capture(void) 
 功能描述：    按钮消抖程序
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void key_capture(stru_motor_comprehensive *this)
{
	if(BREAK_INPUT_MASK) 		
	{
		if(this->bInputCnt[1] < 0) this->bInputCnt[1] = 0;
		
		if(this->bInputCnt[1] < KEYIN_FILTER_TIME)
		{
			this->bInputCnt[1]++;
		}
		else
		{
			this->nInputPort_State |= BIT1;
		}
	}
	else
	{
		if(this->bInputCnt[1] > 0) this->bInputCnt[1] = 0;
		
		if(this->bInputCnt[1] > KEYIN_FILTER_TIME1)
		{
			this->bInputCnt[1]--;
		}
		else
		{
			this->nInputPort_State &= ~BIT1;
		}
	}
}












