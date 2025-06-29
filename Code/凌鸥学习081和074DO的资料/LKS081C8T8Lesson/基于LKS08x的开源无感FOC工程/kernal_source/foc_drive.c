#include "global_variable.h"
#include "hardware_config.h"
#include "SMO.h"
void FOC_InitstruParama(stru_FOC_CtrProcDef *this);
stru_CurrPhaseUVW get_adc_curr(stru_ADCOffset offset);
void FOC_Model(stru_FOC_CtrProcDef *this);
void MCL_Init(stru_FOC_CtrProcDef *this);

/*******************************************************************************
 函数名称：    stru_TrigComponents Trig_Functions(s16 hAngle)
 功能描述：    三角运算
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void FOC_InitstruParama(stru_FOC_CtrProcDef *this)
{
		/* Q轴PI初始化 */
	this->struFOC_CurrLoop.struPI_Q_Torque.hKp_Gain = PID_TORQUE_KP_DEFAULT;
    this->struFOC_CurrLoop.struPI_Q_Torque.hKp_Divisor = TF_KPDIV;
    this->struFOC_CurrLoop.struPI_Q_Torque.hKi_Gain = PID_TORQUE_KI_DEFAULT;
    this->struFOC_CurrLoop.struPI_Q_Torque.hKi_Divisor = TF_KIDIV;
    this->struFOC_CurrLoop.struPI_Q_Torque.hLower_Limit_Output = -MAX_VQ_LIM; /* Lower Limit for Output limitation */
    this->struFOC_CurrLoop.struPI_Q_Torque.hUpper_Limit_Output = MAX_VQ_LIM; /* Upper Limit for Output limitation */
    this->struFOC_CurrLoop.struPI_Q_Torque.wLower_Limit_Integral = -(MAX_VQ_LIM << TF_KIDIV);
    this->struFOC_CurrLoop.struPI_Q_Torque.wUpper_Limit_Integral = MAX_VQ_LIM << TF_KIDIV;
    this->struFOC_CurrLoop.struPI_Q_Torque.wIntegral = 0;

		/* D轴PI初始化 */	
    this->struFOC_CurrLoop.struPI_D_Flux.hKp_Gain = PID_FLUX_KP_DEFAULT;
    this->struFOC_CurrLoop.struPI_D_Flux.hKp_Divisor = FLUX_KPDIV;
    this->struFOC_CurrLoop.struPI_D_Flux.hKi_Gain = PID_FLUX_KI_DEFAULT;
    this->struFOC_CurrLoop.struPI_D_Flux.hKi_Divisor = FLUX_KIDIV;
    this->struFOC_CurrLoop.struPI_D_Flux.hLower_Limit_Output = -MAX_VD_LIM; /* Lower Limit for Output limitation */
    this->struFOC_CurrLoop.struPI_D_Flux.hUpper_Limit_Output = MAX_VD_LIM; /* Upper Limit for Output limitation */
    this->struFOC_CurrLoop.struPI_D_Flux.wLower_Limit_Integral = -(MAX_VD_LIM << FLUX_KIDIV);
    this->struFOC_CurrLoop.struPI_D_Flux.wUpper_Limit_Integral = MAX_VD_LIM << FLUX_KIDIV;
    this->struFOC_CurrLoop.struPI_D_Flux.wIntegral = 0;

    this->struFOC_CurrLoop.stru_QCur.coeff = 200;
    this->struFOC_CurrLoop.stru_DCur.coeff = 200;
    
	this->eSysState = IDLE;/* 系统状态机空闲 */

    this->bMC_RunFlg = 0;
    
		/* 速度环PI初始化 */	
    this->struSpeed_loop.hKp_Gain                 = PID_SPEED_KP_DEFAULT;
    this->struSpeed_loop.hKp_Divisor              = SP_KPDIV;
    this->struSpeed_loop.hKi_Gain                 = PID_SPEED_KI_DEFAULT;
    this->struSpeed_loop.hKi_Divisor              = SP_KIDIV;
    this->struSpeed_loop.hLower_Limit_Output      = -20000; /* Lower Limit for Output limitation */
    this->struSpeed_loop.hUpper_Limit_Output      = 20000; /* Upper Limit for Output limitation */
    this->struSpeed_loop.wLower_Limit_Integral    = -(20000 << SP_KIDIV);
    this->struSpeed_loop.wUpper_Limit_Integral    = 20000 << SP_KIDIV;
    this->struSpeed_loop.wIntegral                = 0;

    SMO_init(&this->stru_SMO);                               /* 滑膜观测器初始化 */ 
}
/*******************************************************************************
 函数名称：    stru_TrigComponents Trig_Functions(s16 hAngle)
 功能描述：    三角运算
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
stru_CurrPhaseUVW get_adc_curr(stru_ADCOffset offset)
{
    stru_CurrPhaseUVW curr;
    curr.nPhaseU = -ADC0_DAT0 + offset.Offset0;
    curr.nPhaseV = -ADC0_DAT1 + offset.Offset1;
    curr.nPhaseW = -curr.nPhaseU - curr.nPhaseV;
    return curr;
}

/*******************************************************************************
 函数名称：    void FOC_Model(stru_FOC_CtrProcDef *this)
 功能描述：    FOC环路
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/
void FOC_Model(stru_FOC_CtrProcDef *this)
{
    s16 theatae;
    stru_CurrPhaseUVW   CurrPhaseUVW;       // 三相电流
    stru_CurrAlphBeta   CurrAlphBeta;       // 静止坐标系电流
    stru_CurrVoctorDQ   CurrVoctorDQ;       // 旋转坐标系电流
    stru_VoltVoctorDQ   VoltVoctorDQ;       // 旋转坐标系电压
    stru_VoltPhaseUVW   VoltPhaseUVW;       // 三相电压
    stru_TrigComponents struTrigSinCos;     // 转子角度三角计算值
    
    
    /* 把相差120度的基于3轴的物理量变换到2轴的定子静止坐标系中 */
	CurrPhaseUVW = get_adc_curr(this->struFOC_CurrLoop.ADCOffset);
    CurrAlphBeta = Clarke(CurrPhaseUVW);
    
    /* 滑膜观测器计算得到当前角度 */
    theatae = SMO_CalcElAngle(&this->stru_SMO,
                                        CurrAlphBeta,
                                        this->struFOC_CurrLoop.VoltAlphBeta);
    
    /* 对角度做三角计算 */
    struTrigSinCos = Trig_Functions(theatae);
    
    /* 将Ialpha，Ibeta变换到旋转的dq坐标系下 */
    CurrVoctorDQ = Park(CurrAlphBeta,struTrigSinCos);

    /* 电流环处理 */
    VoltVoctorDQ.nAxisD = HL_PI_AntiDump(this->struFOC_CurrLoop.stru_DCur.ref-CurrVoctorDQ.nAxisD, &this->struFOC_CurrLoop.struPI_D_Flux);
    VoltVoctorDQ.nAxisQ = HL_PI_AntiDump(this->struFOC_CurrLoop.stru_QCur.ref-CurrVoctorDQ.nAxisQ, &this->struFOC_CurrLoop.struPI_Q_Torque);
    
	/* 电压极限圆限制, 防止Vd Vq过大，超出最大输出极限 */
	VoltVoctorDQ = RevPark_Circle_Limitation(VoltVoctorDQ);

	/* 将旋转坐标系下的Vd Vq 变换到静止坐标下的Valpha，Vbeta */
	this->struFOC_CurrLoop.VoltAlphBeta = Rev_Park(VoltVoctorDQ,struTrigSinCos);
	
	/*Valpha Vbeta 生成SVPWM空间矢量调制 */
    VoltPhaseUVW = SVPWM(this->struFOC_CurrLoop.VoltAlphBeta,PWM_PERIOD);
    
	/* SVPWM输出结果更新到寄存器，在CNT会到-TH时自动更新到MCPWM */
	MCPWM0_RegUpdate(VoltPhaseUVW);
}

/*******************************************************************************
 函数名称：    void MCL_Init(stru_FOC_CtrProcDef *this)
 功能描述：    复位全局变量
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/23    V1.0           YangZJ            创建
 *******************************************************************************/

void MCL_Init(stru_FOC_CtrProcDef *this)
{
    this->struFOC_CurrLoop.struPI_D_Flux.wIntegral = 0;
    this->struFOC_CurrLoop.struPI_Q_Torque.wIntegral = 0;
	
    this->struSpeed_loop.wIntegral = 0;
    this->struFOC_CurrLoop.stru_QCur.ref = 0;
    this->struFOC_CurrLoop.stru_DCur.ref = 0;
    SMO_clear(&this->stru_SMO);
}

/*****END OF FILE****/
