#include "Global_Variable.h"
#include "hardware_config.h"

/*******************************************************************************
 函数名称：    void VoltageRampControl(stru_FOC_CtrProcDef *pCtrProc)
 功能描述：    电压斜坡控制
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void VoltageRampControl(stru_FOC_CtrProcDef *pCtrProc)
{
	stru_FOC_CurrLoopDef *this;

    this = &pCtrProc->struFOC_CurrLoop;
	
    if (this->nBusVoltagefir > this->nBusVoltage)
    {   /* 电压输入给定斜坡信号加入*/
        if ((this->nBusVoltagefir - this->nBusVoltage) > VOLATAGE_RAMP)
        {
            this->nBusVoltagefir -= VOLATAGE_RAMP;
        }
        else
        {
            this->nBusVoltagefir--;
        }
    }
    else if (this->nBusVoltagefir < this->nBusVoltage)
    {
        if ((this->nBusVoltage - this->nBusVoltagefir) > VOLATAGE_RAMP)
        {   /* 20180830 HL 解决欠压多少开电机问题 */
            this->nBusVoltagefir += VOLATAGE_RAMP;
        }
        else
        {
            this->nBusVoltagefir++;
        }
    }
}

/*******************************************************************************
 函数名称：    void check_Vol_Temp(VoltageProtect_Struct *this)
 功能描述：    过欠压处理
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void check_Vol_Temp(VoltageProtect_Struct *this)
{
    if (struFOC_CtrProc.struFOC_CurrLoop.nBusVoltagefir < this->hLowVoltageThd)
    {
        if(this->slowvoltagecnt < 500)
		{
			this->slowvoltagecnt++;
		}
		else
		{
			this->low_error_flg = 1;
		}
    }
    else if (struFOC_CtrProc.struFOC_CurrLoop.nBusVoltagefir > this->hLowVoltageRsmThd)
    {
        this->low_error_flg = 0;
        this->slowvoltagecnt = 0;
    }

    if (struFOC_CtrProc.struFOC_CurrLoop.nBusVoltagefir > this->hOverVoltageThd)
    {
		StopMotorImmdly();
		this->shighvoltagecnt = 0; 
		stru_Faults.B.VoltOverError = 1;
    }
    else if (struFOC_CtrProc.struFOC_CurrLoop.nBusVoltagefir < this->hOverVoltageRsmThd)
    {
        if(stru_Faults.B.VoltOverError)
        {
            if(this->shighvoltagecnt < 1000)
            {
                this->shighvoltagecnt ++;
            }
            else
            {
                this->shighvoltagecnt = 0;
                stru_Faults.B.VoltOverError = 0;
            }
        }
    }

    if (struFOC_CtrProc.struFOC_CurrLoop.nBusVoltage < LOW_VOLATAGE_THD)
    {
        StopMotorImmdly(); /* 解决关电门锁，损坏MOS问题 181012 */
    }
}















