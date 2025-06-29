#include "SMO.h" // Device header
#include "math.h"
void SMO_init(stru_SMODef *this);
void SMO_clear(stru_SMODef *this);
s16 SMO_CalcElAngle(stru_SMODef * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta);

/*******************************************************************************
 函数名称：    void SMO_init(stru_SMODef *this)
 功能描述：    滑膜观测器初始化
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void SMO_init(stru_SMODef *this)
{
	this->coef.Fsmopos = (s32)(exp((-RS/LS)/PWM_FREQ) * 32768);
	this->coef.Gsmopos = (s32)(U_RATED_VOLTAGE / 2 / ADC_SUPPLY_VOLTAGE / PHASE_RSHUNT / AMPLIFICATION_GAIN / RS *(1-exp((-RS/LS)/PWM_FREQ))*32768);
	this->coef.Kslide = 20000 ;
	this->coef.Kslf =20000;
	this->coef.E0= 32670 ;
    this->coef.wZeroSpeedTime = 1000;
}

/*******************************************************************************
 函数名称：    void SMO_clear(stru_SMODef *this)
 功能描述：    滑膜观测器复位
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void SMO_clear(stru_SMODef *this)
{
    memset(&this->variable, 0, sizeof(this->variable));
}

/*******************************************************************************
 函数名称：    s16 SMO_CalcElAngle(stru_SMODef * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta)
 功能描述：    触发滑膜观测器计算并得到角度
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/

s16 SMO_CalcElAngle(stru_SMODef * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta)
{
    s16 EstIalpha,EstIbeta,Ealpha ,Ebeta,Zalpha,Zbeta ;
    
    
    // 滑膜观测器
    Zalpha      = (sat(this->variable.EstIalpha - Ialfa_beta.nAlph,-this->coef.E0,this->coef.E0)*this->coef.Kslide)>>15;
    Zbeta       = (sat(this->variable.EstIbeta  - Ialfa_beta.nBeta ,-this->coef.E0,this->coef.E0)*this->coef.Kslide)>>15;
    Ealpha      = this->variable.Ealpha + ((this->coef.Kslf * (this->variable.Zalpha-this->variable.Ealpha))>>15);
    Ebeta       = this->variable.Ebeta  + ((this->coef.Kslf * (this->variable.Zbeta -this->variable.Ebeta))>>15);
    EstIalpha   = (this->coef.Fsmopos * this->variable.EstIalpha + this->coef.Gsmopos * (Valfa_beta.nAlph-this->variable.Ealpha-this->variable.Zalpha))>>15;
    EstIbeta    = (this->coef.Fsmopos * this->variable.EstIbeta + this->coef.Gsmopos * (Valfa_beta.nBeta -this->variable.Ebeta -this->variable.Zbeta ))>>15;

    this->variable.EstIalpha = EstIalpha;
    this->variable.EstIbeta  = EstIbeta;
    this->variable.Ealpha    = Ealpha;
    this->variable.Ebeta     = Ebeta;
    this->variable.Zalpha    = Zalpha;
    this->variable.Zbeta     = Zbeta;
    
    
    // 反正切得到角度
    this->variable.angle = -lks08x_dsp_arctan(this->variable.Ebeta,this->variable.Ealpha);

    // 开环角度处理
    if(this->variable.bAngleClosedLoop == 0)
    {
        s16 angle;
        this->variable.wOpenAngle += this->variable.wOpenSpeed;
        angle = this->variable.wOpenAngle>>16;
        this->variable.angleopentoclose = angle - this->variable.angle;
        return angle;
    }
    else
    {
        s16 angle;
        angle = this->variable.angle + this->variable.angleopentoclose;
        return angle;
    }
}
