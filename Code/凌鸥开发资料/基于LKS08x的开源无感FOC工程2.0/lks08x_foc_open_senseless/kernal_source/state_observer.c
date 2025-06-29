#include "state_observer.h" // Device header

void SMO_init(stru_SMODef *this);
void SMO_clear(stru_SMODef *this);
s16 SMO_CalcElAngle(stru_SMODef * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta,s16 Vbus);

/*******************************************************************************
 函数名称：    void SMO_init(stru_SMODef *this)
 功能描述：    状态观测器初始化
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
 #define F1 ((COEF_DIV1==15)?32767:1<<COEF_DIV1)
void SMO_init(stru_SMODef *this)
{
    this->coef.hC1                             = (s16)(F1 * C1);
    this->coef.hC2                             = (s16)C2;
    this->coef.hC3                             = (s16)(F1 * C3);
    this->coef.hC4                             = (s16)C4;
    this->coef.hC5                             = (s16)(F1 * C5);
    this->coef.hC6                             = (int16_t)(F2 * EFFECTIVE_NUM((C6_COMP_CONST1 / F2)) / C6_COMP_CONST2);
    this->coef.hF1                             = (s16)F1;
    this->coef.hF2                             = F2;
    this->coef.hF3                             = 1 << EFFECTIVE_NUM((C6_COMP_CONST1 / F2));
    this->coef.hF1LOG                          = COEF_DIV1;
    this->coef.hF2LOG                          = F2_LOG;
    this->coef.hF3LOG                          = EFFECTIVE_NUM((C6_COMP_CONST1 / F2)) + F2_LOG;
    this->coef.wBemf_est_max                   = F2*32767;
    this->coef.wCurr_est_max                   = F1*32767;
    this->coef.wOpenSpeedMax                   = 200<<16;
    this->coef.hOpenAcc                        = 500;
    this->coef.hOpenCurr                       = 6000;
    this->STO_PIStruct.hKp_Gain                = PLL_KP_GAIN;
    this->STO_PIStruct.hKp_Divisor             = PLL_KPDIV;
    this->STO_PIStruct.hKi_Gain                = PLL_KI_GAIN;
    this->STO_PIStruct.hKi_Divisor             = PLL_KIDIV;
    this->STO_PIStruct.hLower_Limit_Output     = -S16_MAX;
    this->STO_PIStruct.hUpper_Limit_Output     = S16_MAX;
    this->STO_PIStruct.wLower_Limit_Integral   = -S32_MAX;
    this->STO_PIStruct.wUpper_Limit_Integral   = S32_MAX;
}

/*******************************************************************************
 函数名称：    void SMO_clear(stru_SMODef *this)
 功能描述：    状态观测器复位
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
    this->STO_PIStruct.wIntegral = 0;
}

/*******************************************************************************
 函数名称：    s16 SMO_CalcElAngle(stru_SMODef * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta,s16 Vbus)
 功能描述：    触发状态观测器计算并得到角度
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
s16 SMO_CalcElAngle(stru_SMODef * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta,s16 Vbus)
{
    s16 hRotor_Speed;

    s32 wBemf_alfa_est;
    s32 wBemf_beta_est;
    s32 wIalfa_est;
    s32 wIbeta_est;
    // 电机方程，估算反电动势
    wIalfa_est = this->variable.wIalfa_est
                     - this->coef.hC1 * (s16)(this->variable.wIalfa_est >> this->coef.hF1LOG)
                     + this->coef.hC2 * (this->variable.wIalfa_est >> this->coef.hF1LOG)
                     - this->coef.hC2 * Ialfa_beta.nAlph
                     + this->coef.hC5 * (((s32)Vbus * Valfa_beta.nAlph) >> 16)
                     - this->coef.hC3 * (this->variable.wBemf_alfa_est >> this->coef.hF2LOG);


    wBemf_alfa_est = this->variable.wBemf_alfa_est
                     + this->coef.hC4 * ((this->variable.wIalfa_est >> this->coef.hF1LOG) - Ialfa_beta.nAlph)
                     + this->coef.hC6 * this->variable.hElSpeedDpp * (this->variable.wBemf_beta_est >> this->coef.hF3LOG);


    wIbeta_est =   this->variable.wIbeta_est
                     - this->coef.hC1 * (s16)(this->variable.wIbeta_est >> this->coef.hF1LOG)
                     + this->coef.hC2 * (this->variable.wIbeta_est >> this->coef.hF1LOG)
                     - this->coef.hC2 * Ialfa_beta.nBeta
                     + this->coef.hC5 * (((s32)Vbus * Valfa_beta.nBeta) >> 16)
                     - this->coef.hC3 * (this->variable.wBemf_beta_est >> this->coef.hF2LOG);


    wBemf_beta_est = this->variable.wBemf_beta_est
                     + this->coef.hC4 * (this->variable.wIbeta_est >> this->coef.hF1LOG)
                     - this->coef.hC4 * Ialfa_beta.nBeta
                     - this->coef.hC6 * this->variable.hElSpeedDpp * (this->variable.wBemf_alfa_est >> this->coef.hF3LOG);
                     
    this->variable.wBemf_alfa_est   = sat(wBemf_alfa_est, -this->coef.wBemf_est_max, this->coef.wBemf_est_max);
    this->variable.wBemf_beta_est   = sat(wBemf_beta_est, -this->coef.wBemf_est_max, this->coef.wBemf_est_max);
    this->variable.wIalfa_est       = sat(wIalfa_est, -this->coef.wCurr_est_max, this->coef.wCurr_est_max);
    this->variable.wIbeta_est       = sat(wIbeta_est, -this->coef.wCurr_est_max, this->coef.wCurr_est_max);


    // 反正切+PLL
    {
        s16 error;
        s16 x,y;
        if(this->variable.hElSpeedDpp >= 0)
        {
            x = (s16)(-(this->variable.wBemf_beta_est >> this->coef.hF2LOG));
            y = (s16)((this->variable.wBemf_alfa_est >> this->coef.hF2LOG));
        }
        else
        {
            x = (s16)((this->variable.wBemf_beta_est >> this->coef.hF2LOG));
            y = (s16)(-(this->variable.wBemf_alfa_est >> this->coef.hF2LOG));
        }
        error = (s16)(this->variable.hElAngle - lks08x_dsp_arctan(x,y));
        hRotor_Speed = HL_PI_AntiDump(error, &this->STO_PIStruct);
        this->variable.hElAngle += hRotor_Speed;
    }
    // 速度滤波
    {
        s16 old;
        this->variable.bSpeed_Buffer_Index++;
        old = this->variable.hSpeed_Buffer[this->variable.bSpeed_Buffer_Index&0x3f];
        this->variable.hSpeed_Buffer[this->variable.bSpeed_Buffer_Index&0x3f] = hRotor_Speed;
        this->variable.wDppBufferSum = this->variable.wDppBufferSum + hRotor_Speed - old;
        this->variable.hElSpeedDpp = (s16)(this->variable.wDppBufferSum >> 6);
    }
    // 开环角度处理
    if(this->variable.bAngleClosedLoop == 0)
    {
        this->variable.wOpenAngle += this->variable.wOpenSpeed;
        this->STO_PIStruct.wIntegral = (this->variable.wOpenSpeed >> 16)<< this->STO_PIStruct.hKi_Divisor ;
//        return (s16)this->variable.hElAngle;
        return this->variable.wOpenAngle>>16;
    }
    else
    {
        return (s16)this->variable.hElAngle;
    }
}
