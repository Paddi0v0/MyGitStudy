#include "Global_Variable.h"
#include "hardware_config.h"
#include "MC_hall.h"
#include "function_config.h" 
#include "PID_regulators.h"

/*******************************************************************************
 函数名称：    void LowPass_Filter_Init(stru_FOC_CtrProcDef *this)
 功能描述：    低通滤波各参数初始化
 输入参数：    stru_FOC_CtrProcDef *this 结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void LowPass_Filter_Init(stru_FOC_CtrProcDef *this)
{
    this->struFOC_CurrLoop.struCurrA_RC.yk_1 = 0;
    this->struFOC_CurrLoop.struCurrA_RC.coef = 47000; /* 1000Hz */
    this->struFOC_CurrLoop.struCurrB_RC.yk_1 = 0;
    this->struFOC_CurrLoop.struCurrB_RC.coef = 47000; /* 1000Hz */

    this->struBusCurr_RC.yk_1 = 0;
    this->struBusCurr_RC.coef = 5000;
}

/*******************************************************************************
 函数名称：    void FOC_InitstruParama(void)
 功能描述：    FOC 相关控制变量及结构体初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void FOC_InitstruParama(void)
{
	struFOC_CtrProc.struFOC_CurrLoop.bget_offset_flg = 0;
	
    judgement_offset(&struFOC_CtrProc.struFOC_CurrLoop); /* 判断偏置是否正常 */
	
    if (struFOC_CtrProc.struFOC_CurrLoop.bget_offset_flg) /* 不正常重新获取 */
    {
        CurrentOffsetCalibration();
    }
	
		/* Q轴PI初始化 */
	struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.hKp_Gain = PID_TORQUE_KP_DEFAULT;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.hKp_Divisor = TF_KPDIV;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.hKi_Gain = PID_TORQUE_KI_DEFAULT;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.hKi_Divisor = TF_KIDIV;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.hLower_Limit_Output = -MAX_VQ_LIM; /* Lower Limit for Output limitation */
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.hUpper_Limit_Output = MAX_VQ_LIM; /* Upper Limit for Output limitation */
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.wLower_Limit_Integral = -(MAX_VQ_LIM << TF_KIDIV);
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.wUpper_Limit_Integral = MAX_VQ_LIM << TF_KIDIV;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.wIntegral = 0;

		/* D轴PI初始化 */	
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.hKp_Gain = PID_FLUX_KP_DEFAULT;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.hKp_Divisor = FLUX_KPDIV;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.hKi_Gain = PID_FLUX_KI_DEFAULT;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.hKi_Divisor = FLUX_KIDIV;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.hLower_Limit_Output = -MAX_VD_LIM; /* Lower Limit for Output limitation */
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.hUpper_Limit_Output = MAX_VD_LIM; /* Upper Limit for Output limitation */
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.wLower_Limit_Integral = -(MAX_VD_LIM << FLUX_KIDIV);
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.wUpper_Limit_Integral = MAX_VD_LIM << FLUX_KIDIV;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.wIntegral = 0;
	
	/* 扭矩滤波深度 */
	struFOC_CtrProc.struCur_lowFir_Q.coef = FRAC16(0.3);
    struFOC_CtrProc.struCur_lowFir_Q.yk_1 = 0;
	
	struFOC_CtrProc.max_bus_current = REG32(HALL_LEARN_ADDR + 12);/* 最大母线电流获取 */
	struFOC_CtrProc.originalmax_bus_current = struFOC_CtrProc.max_bus_current;
	
	struFOC_CtrProc.eSysState = IDLE;/* 系统状态机空闲 */

    struFOC_CtrProc.bMC_RunFlg = 0;
}

/*******************************************************************************
 函数名称：    void Get_PhaseCurrent_AndFilter(stru_FOC_CtrProcDef *this)
 功能描述：    读取ADC采样到的相电流值，并运行斜率滤波和低通滤波
 输入参数：    stru_FOC_CtrProcDef *this 结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void Get_PhaseCurrent_AndFilter(stru_FOC_CurrLoopDef *this)
{
    s32 t_value;
	s16 hPhaseCurrA, hPhaseCurrB;

    this->StatCurr_a_b_test = SVPWM_2PH_3ShuntGetPhaseCurrentValues(this);

    t_value = this->StatCurr_a_b_test.qI_Value1 - this->struLastStatCurr_a_b.qI_Value1; 
	
    if (ABS(t_value) > 1000)
    {
        hPhaseCurrA = this->struLastStatCurr_a_b.qI_Value1;
        this->bCntFirCurA++;
		
        if (this->bCntFirCurA > 3)
        {
            this->struLastStatCurr_a_b.qI_Value1 = this->StatCurr_a_b_test.qI_Value1;
			hPhaseCurrA = this->struLastStatCurr_a_b.qI_Value1;
            this->bCntFirCurA = 0;
        }
    }
    else
    {
        this->bCntFirCurA = 0;
        this->struLastStatCurr_a_b.qI_Value1 = this->StatCurr_a_b_test.qI_Value1;
		hPhaseCurrA = this->StatCurr_a_b_test.qI_Value1;
    }

    t_value = this->StatCurr_a_b_test.qI_Value2 - this->struLastStatCurr_a_b.qI_Value2;
	
    if (ABS(t_value) > 1000)
    {
        hPhaseCurrB = this->struLastStatCurr_a_b.qI_Value2;
        this->bCntFirCurB++;
		
        if (this->bCntFirCurB > 3)
        {
            this->struLastStatCurr_a_b.qI_Value2 = this->StatCurr_a_b_test.qI_Value2;
			hPhaseCurrB = this->struLastStatCurr_a_b.qI_Value2;
			this->bCntFirCurB = 0;
        }
    }
    else
    {
        this->bCntFirCurB = 0;
        this->struLastStatCurr_a_b.qI_Value2 = this->StatCurr_a_b_test.qI_Value2;
		hPhaseCurrB = this->StatCurr_a_b_test.qI_Value2;
    }

    hPhaseCurrA = lowPass_filter(&this->struCurrA_RC, hPhaseCurrA);
    hPhaseCurrB = lowPass_filter(&this->struCurrB_RC, hPhaseCurrB);
	
	this->struStatCurr_a_b.qI_Value1 = hPhaseCurrA >> 1;
	this->struStatCurr_a_b.qI_Value2 = hPhaseCurrB >> 1;
}

/*******************************************************************************
 函数名称：    FOC_CtrProcFilterInit(this)
 功能描述：    启动电机运行的前4拍滤波器初始化
 输入参数：    stru_FOC_CtrProcDef *this 结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void FOC_CtrProcFilterInit(stru_FOC_CurrLoopDef *this)
{
	this->bFirstOpenMosFlgCnt++;
	this->struStatVolt_q_d.qV_Value2 = 0;
	this->struStatVolt_q_d.qV_Value1 = this->struPI_Torque.wIntegral >> this->struPI_Torque.hKi_Divisor;
	this->struLastStatCurr_a_b.qI_Value1 = this->StatCurr_a_b_test.qI_Value1;
	this->struLastStatCurr_a_b.qI_Value2 = this->StatCurr_a_b_test.qI_Value2;

	this->struStatCurr_a_b.qI_Value1 = 0;
	this->struStatCurr_a_b.qI_Value2 = 0;
	this->struCurrA_RC.yk_1 = 0;
	this->struCurrB_RC.yk_1 = 0;
	this->struStatCurr_q_d.qI_Value1 = 0;
	this->struStatCurr_q_d.qI_Value2 = 0;
}
/*******************************************************************************
 函数名称：    void FOC_Model(stru_FOC_CtrProcDef *pCtrProc)
 功能描述：    FOC运行环路
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void FOC_Model(stru_FOC_CtrProcDef *pCtrProc)
{
    s16 theatae;
	
	stru_FOC_CurrLoopDef *this;
	
	this = &pCtrProc->struFOC_CurrLoop;
	
	Get_PhaseCurrent_AndFilter(this); /* 读出电流，并进行电流滤波处理　*/
	
	if (struHallProcess.bCloseLoopAngleFlg)
	{
		closeLoopAnglePLL(&struHallProcess);
	}
	else
	{
		reduceToqueAnglePll(&struHallProcess);
	}
	
	theatae = GET_ELECTRICAL_ANGLE;	/* 获取角度 */

		/* 把相差120度的基于3轴的物理量变换到2轴的定子静止坐标系中 */
    this->struStatCurr_alfa_beta = Clarke(this->struStatCurr_a_b); 
	
		/* 将Ialpha，Ibeta变换到旋转的dq坐标系下 */
    this->struStatCurr_q_d = Park(this->struStatCurr_alfa_beta, theatae, &struFOC_CtrProc.struFOC_CurrLoop);

    if (this->bFirstOpenMosFlgCnt < 3)
    {   /* 启动电机运行的前3拍滤波器初始化 */
        FOC_CtrProcFilterInit(this);
    }
    else
    {
		s32 t_value;

			/* D轴 闭环PI控制，Q轴开环给定 */
		this->struStatVolt_q_d.qV_Value2 = HL_PI_AntiDump((this->nDCur_Reference >> 1),
									  this->struStatCurr_q_d.qI_Value2, &this->struPI_Flux);							
				
		t_value = this->nRequestPower;
		
		if (t_value < 0)
		{
			t_value = 0;
		}

		if (struHallProcess.bMotorDirtionCtrl)
		{
			this->struStatVolt_q_d.qV_Value1 = -t_value;
		}
		else
		{
			this->struStatVolt_q_d.qV_Value1 = t_value;
		}
		
		if(ABS(this->struStatVolt_q_d.qV_Value2) > t_value)
		{
			if(this->struStatVolt_q_d.qV_Value2 > 0)
			{
				this->struStatVolt_q_d.qV_Value2 = t_value;
			}
			else
			{
				this->struStatVolt_q_d.qV_Value2 = -t_value;
			}
		}
    }
	
	/* 电压极限圆限制, 防止Vd Vq过大，超出最大输出极限 */
	RevPark_Circle_Limitation(pCtrProc);

	/* 将旋转坐标系下的Vd Vq 变换到静止坐标下的Valpha，Vbeta */
	this->struStatVolt_alfa_beta = Rev_Park(this->struStatVolt_q_d, &struFOC_CtrProc.struFOC_CurrLoop);
	
	/*Valpha Vbeta 生成SVPWM空间矢量调制 */
	SVPWM_2PH(pCtrProc);

	/* 加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值 */
	MCPWM0_RegUpdate(this);
}

/*******************************************************************************
 函数名称：    void MCL_Init(stru_FOC_CtrProcDef *this)
 功能描述：    电机运行前，各变量初始化
 输入参数：    stru_FOC_CtrProcDef *this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void MCL_Init(stru_FOC_CtrProcDef *pCtrProc)
{
    s32 t_speed_lim; 
    volatile u16 t_timer;
	
	stru_FOC_CurrLoopDef *this;

    this = &pCtrProc->struFOC_CurrLoop;

    LowPass_Filter_Init(&struFOC_CtrProc);

    t_speed_lim = 0;

    if (t_speed_lim > S16_MAX)
    {
        t_speed_lim = S16_MAX;
    }

    if (struHallProcess.bMotorDirtionCtrl)
    {   
        this->struPI_Torque.wIntegral = -(t_speed_lim << this->struPI_Torque.hKi_Divisor);
    }
    else
    {
        this->struPI_Torque.wIntegral = t_speed_lim << this->struPI_Torque.hKi_Divisor;
    }
	
    this->struPI_Flux.wIntegral = 0;

	this->nRequestPower = 100;

    if (struHallProcess.bCloseLoopAngleFlg == 0)
    {
       this->bFirstOpenMosFlgCnt = 0;
		struHallProcess.bReduceToqueFlg = 0;
		struHallProcess.wHallPWMTimerCnt = 0;
        struHallProcess.bHallRunFlg |= HALL_COM_ERR;
        struHallProcess.nPhaseShift = struHallProcess.nPhaseShiftOffset;
        HALL_Init_Electrical_Angle(&struHallProcess);
        struHallProcess.bFstHallSigFlg = 1;
    }
	
	struFOC_CtrProc.max_bus_current = struFOC_CtrProc.originalmax_bus_current; 

    __disable_irq();
    FOC_Model(&struFOC_CtrProc);
    MCPWM_UPDATE_REG();
    __enable_irq();

    EN_HPWM_FUNC();
    struFOC_CtrProc.nSys_TimerPWM = 0;

    while (struFOC_CtrProc.nSys_TimerPWM < 2)
    {
        ;
    }
}

/*****END OF FILE****/
