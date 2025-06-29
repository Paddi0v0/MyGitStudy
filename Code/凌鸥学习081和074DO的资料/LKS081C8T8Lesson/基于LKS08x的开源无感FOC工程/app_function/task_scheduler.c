#include "global_variable.h"
#include "hardware_config.h"
#include "SMO.h"
void Sys_State_Machine(stru_FOC_CtrProcDef *this);
void StopMotorImmdly(stru_FOC_CtrProcDef *this);
void Sys_State_Run(stru_FOC_CtrProcDef *this);
void Curr_rc_fir(Stru_Curr_RC * this);

/*******************************************************************************
 函数名称：    void Sys_State_Machine(stru_FOC_CtrProcDef *this)
 功能描述：    初始化全局变量
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void Sys_State_Machine(stru_FOC_CtrProcDef *this)
{
    switch (this->eSysState)
    {
    case IDLE:
    {
        if ((this->bMC_RunFlg) && (this->stru_Faults.R == 0))
        {
            this->eSysState = INIT;
        }
        break;
    }

    case INIT:
    {
        MCL_Init(this);
        PWMOutputs(ENABLE);
        this->eSysState = RUN;
        break;
    }

    case RUN:
    {
        if ((this->bMC_RunFlg == 0) || (this->stru_Faults.R))
        {
            this->eSysState = STOP;
        }
        Sys_State_Run(this);
        break;
    }

    case STOP:
    {
        StopMotorImmdly(this);
        MCL_Init(this);
        this->eSysState = IDLE;
        break;
    }
    }
}
/*******************************************************************************
 函数名称：    void StopMotorImmdly(stru_FOC_CtrProcDef *this)
 功能描述：    停机
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void StopMotorImmdly(stru_FOC_CtrProcDef *this)
{
    PWMOutputs(DISABLE); 
    this->bMC_RunFlg = 0;
    if (this->eSysState == RUN)
    {
        this->eSysState = STOP;
    }
}
/*******************************************************************************
 函数名称：    void Sys_State_Run(stru_FOC_CtrProcDef *this)
 功能描述：    初始化全局变量
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void Sys_State_Run(stru_FOC_CtrProcDef *this)
{
    // 开环速度处理
    if(this->stru_SMO.variable.bAngleClosedLoop == 0)
    {
        if(this->stru_SMO.variable.wZeroSpeedCnt < this->stru_SMO.coef.wZeroSpeedTime)
        {
            this->stru_SMO.variable.wZeroSpeedCnt++;
        }
        else
        {
            if(this->stru_SMO.variable.wOpenSpeed < (100<<16))
            {
                this->stru_SMO.variable.wOpenSpeed += 5000;
                this->struFOC_CurrLoop.stru_QCur.set =2000 ;
                this->struFOC_CurrLoop.stru_DCur.set = 0;
            }
            else
            {
                this->struSpeed_loop.wIntegral = this->struFOC_CurrLoop.stru_QCur.set<<this->struSpeed_loop.hKi_Divisor;
                this->stru_SMO.variable.bAngleClosedLoop = 1;
//                this->struFOC_CurrLoop.stru_DCur.set = 0;
            }
        }
    }
    else
    {
        if(this->stru_SMO.variable.speed < 0)
        {
            this->eSysState = STOP;
        }
//        if(this->stru_SMO.variable.speed > 32767)
//        {
//            this->eSysState = STOP;
//        }
    }
    // 开闭环切换
    if(ABS(this->stru_SMO.variable.angleopentoclose)>10)
    {
        if(this->stru_SMO.variable.angleopentoclose>0)
        {
            this->stru_SMO.variable.angleopentoclose -= 10;
        }
        else
        {
            this->stru_SMO.variable.angleopentoclose += 10;
        }
    }
    else
    {
            this->stru_SMO.variable.angleopentoclose = 0;
        this->struFOC_CurrLoop.stru_QCur.set = HL_PI_AntiDump(10000-this->stru_SMO.variable.speed, &this->struSpeed_loop);
//        this->struFOC_CurrLoop.stru_QCur.set = 5000;
    }
    // 电流给定
    Curr_rc_fir(&this->struFOC_CurrLoop.stru_QCur);
    Curr_rc_fir(&this->struFOC_CurrLoop.stru_DCur);
    // 速度计算
    this->stru_SMO.variable.speed =(s16)( this->stru_SMO.variable.angle - this->stru_SMO.variable.SpeedCalcOldAngle);
    this->stru_SMO.variable.SpeedCalcOldAngle = this->stru_SMO.variable.angle;
}
/*******************************************************************************
 函数名称：    void Curr_rc_fir(Stru_Curr_RC * this)
 功能描述：    初始化全局变量
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void Curr_rc_fir(Stru_Curr_RC * this)
{
    s16 old;
    old = this->ref ;
    this->ref = (this->set * this->coeff + this->ref*(32768 - this->coeff) + 16384)>>15;
    if(this->ref == old)
    {
        if(this->ref < this->set)
        {
            this->ref ++;
        }
        else if(this->ref > this->set)
        {
            this->ref --;
        }
    }
}
