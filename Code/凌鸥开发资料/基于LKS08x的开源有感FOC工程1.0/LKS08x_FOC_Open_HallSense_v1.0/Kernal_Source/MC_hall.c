#include "Global_Variable.h"
#include "time_process.h"
#include "MC_hall.h"
#include "PID_regulators.h"
#include "hardware_config.h"
#include "function_config.h" 

/*******************************************************************************
 函数名称：    void HALL_InitHallMeasure( stru_HallProcessDef *this )
 功能描述：    没有HALL信号反馈
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void HALL_InitHallMeasure( stru_HallProcessDef *this )  /* 没有HALL信号反馈 */
{
    u8 t_i;
	volatile u32 t_data;
	
	this->nReduceToqueDpp = 0;
	
	this->wCloseLoopPeriodThd = 5000000; //  4000000
		
    this->wOpenLoopPeriodThd = 6500000;  //  5500000

    this->nPhaseShiftOffset = S16_330_PHASE_SHIFT;
	
	t_data = REG32(HALL_LEARN_ADDR); /* 读取HALL相序 */
    CopyFromBuffer((u8*) & (struHallProcess.bHallCommTab[0]), (u8*)&t_data, 4);
    t_data = REG32(HALL_LEARN_ADDR + 4);
    CopyFromBuffer((u8*) & (struHallProcess.bHallCommTab[4]), (u8*)&t_data, 4);
    t_data = REG32(HALL_LEARN_ADDR + 8);
	
	this->bMotorDirtionCtrl = 0;  /* 初始化电机方向 0为正转 */

    hall_comm_VariableInit(&struHallProcess); /* 电机启动时HALL判断 */

    this->bSpeedFIFO_Index = HALL_SPEED_FIFO_SIZE - 1;

    this->bHallRunFlg |= HALL_COM_ERR;
	
	this->wMotorSpeedAvgCnt = ROTOR_SPEED_FACTOR / 3;

    for(t_i = 0; t_i < HALL_SPEED_FIFO_SIZE; t_i++)
    {
        this->wSensorPeriod[t_i] = this->wMotorSpeedAvgCnt;
    }
    
    HALL_Init_Electrical_Angle(&struHallProcess);
    this->bHallRunFlg &= ~HALL_COM_ERR;
}

/*******************************************************************************
 函数名称：    void hall_comm_VariableInit(stru_HallProcessDef *this)
 功能描述：    电机启动时HALL判断
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void hall_comm_VariableInit(stru_HallProcessDef *this)
{
    u8 t_i, t_j;

    for (t_i = 1; t_i < 7; t_i++)
    {
        for (t_j = 0; t_j < 6; t_j++)
        {
            if (this->bHallCommTab[t_j] == t_i)
            {
                if (t_j != 5)
                {
                    this->bHallPossableTab[t_i] = this->bHallCommTab[t_j + 1];
                }
                else
                {
                    this->bHallPossableTab[t_i] = this->bHallCommTab[0];
                }
				
                break;
            }
        }

        for (t_j = 0; t_j < 6; t_j++)
        {
            if (this->bHallCommTab[t_j] == t_i)
            {
                if (t_j == 0)
                {
                    this->bHallPossableTab2[t_i] = this->bHallCommTab[5];
                }
                else
                {
                    this->bHallPossableTab2[t_i] = this->bHallCommTab[t_j - 1];
                }
				
                break;
            }
        }
    }
}

/*******************************************************************************
 函数名称：    void HALL_Init_Electrical_Angle(stru_HallProcessDef *this)
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void HALL_Init_Electrical_Angle(stru_HallProcessDef *this)
{
	if((this->wMotorSpeedAvgCnt < this->wCloseLoopPeriodThd))
    {   /* 速度大于闭环门限，开通闭环控制 */
        this->bCloseLoopAngleFlg = 1;

		if(this->bHallRunFlg & HALL_DIR_FLG)
		{
			this->nPhaseShift = this->nPhaseShiftOffset - S16_30_PHASE_SHIFT;
		}
		else
		{   /* 电机反转命令 */
			this->nPhaseShift = this->nPhaseShiftOffset + S16_30_PHASE_SHIFT;
		}
    }
    else
    {
        /* 速度小于开环门限，开通开环控制 */
        this->bCloseLoopAngleFlg = 0;
        this->nPhaseShift = this->nPhaseShiftOffset;
    }

    if(this->bHallState == this->bHallCommTab[0])
    {
        this->nTabElectrical_Angle = S16_60_PHASE_SHIFT;
    }
    else if(this->bHallState == this->bHallCommTab[1])
    {
        this->nTabElectrical_Angle = S16_120_PHASE_SHIFT;
    }
    else if(this->bHallState == this->bHallCommTab[2])
    {
        this->nTabElectrical_Angle = S16_180_PHASE_SHIFT;
    }
    else if(this->bHallState == this->bHallCommTab[3])
    {
        this->nTabElectrical_Angle = S16_240_PHASE_SHIFT;
    }
    else if(this->bHallState == this->bHallCommTab[4])
    {
        this->nTabElectrical_Angle = S16_300_PHASE_SHIFT;
    }
    else if(this->bHallState == this->bHallCommTab[5])
    {
        this->nTabElectrical_Angle = 0;
    }

    this->nTabElectrical_Angle += this->nPhaseShift;

    if(this->bCloseLoopAngleFlg)
    {
        if(this->wMotorSpeedAvgCnt > this->wOpenLoopPeriodThd)
        {
            this->nElectrical_Angle = this->nTabElectrical_Angle;
        }

        closeLoopAnglePLLInit(&struHallProcess);
        this->nMaxIncAngle = 0;
    }
    else
    {
        this->nRotorFreqDpp = ROTOR_SPEED_FACTOR / this->wMotorSpeedAvgCnt;

        if(this->bHallRunFlg & HALL_COM_ERR)
        {   /* 换相错误，直接给出角度 */
            this->nElectrical_Angle = this->nTabElectrical_Angle;
            this->bReduceToqueFlg = 0;
        }
        else
        {   /* 正常换相时，给出最终换相角 */
            calc_first_ElectAngle(this->nTabElectrical_Angle, &struHallProcess);
        }
    }
}

/*******************************************************************************
 函数名称：    void closeLoopAnglePLLInit(stru_HallProcessDef *this)
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void closeLoopAnglePLLInit(stru_HallProcessDef *this)
{
    s16 t_detAngle;
    s32 t_RotorSpeedFactor;

    if (this->bMotorDirtionCtrl)
    {
        t_detAngle = this->nOldElectrical_Angle - this->nTabElectrical_Angle;
    }
    else
    {
        t_detAngle = this->nTabElectrical_Angle - this->nOldElectrical_Angle;
    }

    if (ABS(t_detAngle) > S16_20_PHASE_SHIFT)
    {
		this->nElectrical_Angle = this->nTabElectrical_Angle;
        this->nRotorFreqDpp = ROTOR_SPEED_FACTOR / this->wMotorSpeedAvgCnt;
    }
	else
	{
		t_RotorSpeedFactor = t_detAngle * ROTOR_SPEED_FACTOR_PER_UNIT;
		t_RotorSpeedFactor += ROTOR_SPEED_FACTOR;
		this->nRotorFreqDpp = ((t_RotorSpeedFactor / this->wMotorSpeedAvgCnt) + this->nRotorFreqDpp) >> 1;
	}
}

/*******************************************************************************
 函数名称：    void calc_first_ElectAngle(u16 angle, stru_HallProcessDef *this)
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void calc_first_ElectAngle(u16 angle, stru_HallProcessDef *this)
{
    u16 t_hElectrical_Angle;

    t_hElectrical_Angle = angle;
	
	this->nReduceToqueAngle = 0;
    this->nMaxReduceIncAngle = S16_60_PHASE_SHIFT;

    if (this->bMotorDirtionCtrl)
    {   /* 电机反转命令 */
        if (this->bHallRunFlg & HALL_DIR_FLG)
        {   /* 电机实际正转，角度正向累加 */
            this->nElectrical_Angle = t_hElectrical_Angle - S16_60_PHASE_SHIFT;
			this->bReduceToqueFlg = REDUCE_TOQUE_PUSE;
        }
        else
        {   /* 电机实际正转，角度递减 */
            this->nElectrical_Angle = t_hElectrical_Angle + S16_60_PHASE_SHIFT;
            this->bReduceToqueFlg = REDUCE_TOQUE_MINUS;
        }
    }
    else
    {   /* 电机正转命令 */
        if (this->bHallRunFlg & HALL_DIR_FLG)
        {   /* 电机正转 */
            this->bReduceToqueFlg = REDUCE_TOQUE_PUSE;
            this->nElectrical_Angle = t_hElectrical_Angle - S16_60_PHASE_SHIFT;
        }
        else
        {
            this->bReduceToqueFlg = REDUCE_TOQUE_MINUS;
            this->nElectrical_Angle = t_hElectrical_Angle + S16_60_PHASE_SHIFT;
        }
    }
}

/*******************************************************************************
 函数名称：    s16 HALL_GetElectricalAngle(stru_HallProcessDef *this)
 功能描述：    霍尔角度获取
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/

s16 HALL_GetElectricalAngle(stru_HallProcessDef *this)
{
    return(this->nElectrical_Angle);
}

/*******************************************************************************
 函数名称：    u8 check_hall_state(u8 t_hall, stru_HallProcessDef *this)
 功能描述：    查询霍尔状态
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
u8 check_hall_state(u8 t_hall, stru_HallProcessDef *this)
{
    u8 t_ReturnFlg;

    t_ReturnFlg = 1;
	
	if ((t_hall == 0) || (t_hall == 7))
	{
		this->ErrCnt++;
		this->bHallRunFlg = HALL_COM_ERR;
		
		if (this->ErrCnt > 3)
		{
			this->ErrCnt = 0;
			this->bHallState = t_hall;
		}

		t_ReturnFlg = 0;
	}
	else
	{
		if (t_hall == this->bHallPossableTab[this->bHallState])
		{	 
			this->ErrCnt = 0;
			
			this->bHallState = t_hall;

			this->bHallRunFlg &= ~HALL_COM_ERR;

			this->bHallRunFlg |= HALL_DIR_FLG;
		}
		else if (t_hall == this->bHallPossableTab2[this->bHallState])
		{	
			this->ErrCnt = 0;
			
			this->bHallState = t_hall;
			
			this->bHallRunFlg &= (~HALL_COM_ERR);
			
			this->bHallRunFlg &= (~HALL_DIR_FLG);
		}	

		this->bHallState_org = t_hall;
	}

    return t_ReturnFlg;
}

/*******************************************************************************
 函数名称：    void HALL_IRQHandler(void)
 功能描述：    Hall中断处理函数
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/

void HALL_IRQProcess(stru_HallProcessDef *this)
{
    unsigned char temp_state, t_FuncState;
    volatile u8 t_i, t_cnt;

    if(HALL_INFO & BIT16)
    {   /* Hall 变化中断 */
        this->wHallCapCnt += HALL_WIDTH;
        HALL_INFO = BIT16;
 
        temp_state = ReadHallState();

		/* 返回为0是干扰错误换相，不为0是正常换相 */ 
        t_FuncState = check_hall_state(temp_state, &struHallProcess);

        if(t_FuncState)
        {
            hall_sensor_period(&struHallProcess);

            if(this->bFstHallSigFlg)
            {
                this->bFstHallSigFlg = 0;
            }
            else
            {
				if(this->wHallCapCnt < MAX_SPEED_DPP)
				{
					this->wHallCapCnt = MAX_SPEED_DPP;
				}

                this->wSensorPeriod[this->bSpeedFIFO_Index] = this->wHallCapCnt;
            }

            this->wHallCapCnt = 0;
            this->wHallPWMTimerCnt = 0;

            this->wMotorSpeedAvgCnt = GetAvrgHallPeriod(&struHallProcess);

            HALL_Init_Electrical_Angle(&struHallProcess);
        }
    }

    if(HALL_INFO & BIT17)
    {   /* Hall超时中断 */
        HALL_INFO = BIT17;

        this->bHallRunFlg |= HALL_COM_ERR;

        this->bSpeedFIFO_Index = 0;
		
		this->wMotorSpeedAvgCnt = ROTOR_SPEED_FACTOR / 3;

        for(t_i = 0; t_i < HALL_SPEED_FIFO_SIZE; t_i++)
        {
            this->wSensorPeriod[t_i] = this->wMotorSpeedAvgCnt;
        }

        this->nRotorFreqDpp = 3;

        temp_state = ReadHallStateMix(); 

        t_FuncState = check_hall_state(temp_state, &struHallProcess);

        HALL_Init_Electrical_Angle(&struHallProcess);

        this->bCloseLoopAngleFlg = 0;
    }

    HALL_INFO = 0;
}

/*******************************************************************************
 函数名称：    u32 GetAvrgHallPeriod(stru_HallProcessDef *this)
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
u32 GetAvrgHallPeriod(stru_HallProcessDef *this)
{
    u32 wAvrgBuffer;

    wAvrgBuffer = 0;

    wAvrgBuffer = (this->wOldSensorPeriod + this->wSensorPeriod[this->bSpeedFIFO_Index]) >> 1;
		
	if(wAvrgBuffer < ROTOR_SPEED_FACTOR >> 11)
	{
		wAvrgBuffer = ROTOR_SPEED_FACTOR / 3;
	}
	
    this->wOldSensorPeriod = this->wSensorPeriod[this->bSpeedFIFO_Index];

    return (wAvrgBuffer);
}

/*******************************************************************************
 函数名称：    void closeLoopAnglePLL(stru_HallProcessDef *this)
 功能描述：    电压斜坡控制
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void closeLoopAnglePLL(stru_HallProcessDef *this)
{
    if (this->bCloseLoopAngleFlg)
    {
        if (this->bMotorDirtionCtrl)
        {   /* 电机反转 */
            if (this->nMaxIncAngle < S16_75_PHASE_SHIFT)
            {
                this->nMaxIncAngle += this->nRotorFreqDpp;
                this->nElectrical_Angle -= this->nRotorFreqDpp;
            }
        }
        else
        {   /* 电机正转 */
            if (this->nMaxIncAngle < S16_75_PHASE_SHIFT)
            {
                this->nMaxIncAngle += this->nRotorFreqDpp;
                this->nElectrical_Angle += this->nRotorFreqDpp;
            }
        }

        this->nOldElectrical_Angle = this->nElectrical_Angle;
    }
}

/*******************************************************************************
 函数名称：    reduceToqueAnglePll(stru_HallProcessDef *this)
 功能描述：    减小扭矩波动时完成角度的累加或递减
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2014/9/19      V1.0           Howlet Li          创建
 *******************************************************************************/
void reduceToqueAnglePll(stru_HallProcessDef *this)
{
    if ((this->bCloseLoopAngleFlg == 0) && this->bReduceToqueFlg)
    {
        if (this->nReduceToqueAngle < this->nMaxReduceIncAngle)
        {
            /* 确保角度累加不大于上限 */
            this->nReduceToqueAngle += this->nReduceToqueDpp;

            if (this->bReduceToqueFlg == REDUCE_TOQUE_MINUS)
            {
                this->nElectrical_Angle -= this->nReduceToqueDpp;
            }
            else
            {
                this->nElectrical_Angle += this->nReduceToqueDpp;
            }
        }
        else
        {
            this->bReduceToqueFlg = 0;
        }
    }
}

/*******************************************************************************
 函数名称：    void Verify_Hall_State(stru_HallProcessDef *this)
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void Verify_Hall_State(stru_HallProcessDef *this)
{
    u8 temp_state1, temp_state;
    u8 t_cnt = 0, t_i;
    u8 t_funcState;
    u32 t_CapCnt;

    temp_state = ReadHallStateMix();

    if(temp_state != this->bHallState_org)
	{
		for (t_i = 0; t_i < 4; t_i++)
		{
			temp_state1 = ReadHallStateMix(); /* 读霍尔状态 */

			if (temp_state == temp_state1)
			{
				t_cnt++;
			}
		}

		if (t_cnt > 2)
		{
			NVIC_DisableIRQ (HALL_IRQn);
			t_funcState = check_hall_state(temp_state, &struHallProcess); /* 查询霍尔状态函数 */
			
			if (t_funcState)
			{
				hall_sensor_period(&struHallProcess);

				t_CapCnt = this->wHallPWMTimerCnt * ROTOR_SPEED_FACTOR_PER_UNIT;
				this->wSensorPeriod[this->bSpeedFIFO_Index] = t_CapCnt;

				this->wMotorSpeedAvgCnt = GetAvrgHallPeriod(&struHallProcess);

				this->wHallPWMTimerCnt = 0;
				HALL_Init_Electrical_Angle(&struHallProcess);
			}
			
			NVIC_EnableIRQ (HALL_IRQn);
		}
	}
}

/*******************************************************************************
 函数名称：    void Hall_ElecAnglePWM_Process(stru_HallProcessDef *this)
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void Hall_ElecAnglePWM_Process(stru_HallProcessDef *this)
{
	if(this->bFastAddElecAngleFlg)
    {
        u16 t_addAngleStep;

        t_addAngleStep = COMM_PER_TIME_5MS;

        if(this->nEndElectricalAngle  > 0)
        {
            if(this->nEndElectricalAngle  > t_addAngleStep)
            {
                this->nEndElectricalAngle  -= t_addAngleStep;
                this->nElectrical_Angle += t_addAngleStep;
            }
            else
            {
                this->bFastAddElecAngleFlg = 0;
            }
        }
        else
        {
            if(this->nEndElectricalAngle  < -t_addAngleStep)
            {
                this->nEndElectricalAngle += t_addAngleStep;
                this->nElectrical_Angle -= t_addAngleStep;
            }
            else
            {
                this->bFastAddElecAngleFlg = 0;
            }
        }
    }
}

/*******************************************************************************
 函数名称：    u8 ReadHallStateMix(void)
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
u8 ReadHallStateMix(void)
{
    u8 t_hall;

    t_hall = ReadHallState();
	
    return t_hall;
}

/*******************************************************************************
 函数名称：    void hall_sensor_period(stru_HallProcessDef *this) 
 功能描述：    
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void hall_sensor_period(stru_HallProcessDef *this) 
{
	if (this->bSpeedFIFO_Index < (HALL_SPEED_FIFO_SIZE - 1))
	{
		this->bSpeedFIFO_Index++;
	}
	else
	{
		this->bSpeedFIFO_Index = 0;
	}
}

/*******************************************************************************
 函数名称：    u8 ReadHallState(void)
 功能描述：    获取当前霍尔信号
 输入参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
u8 ReadHallState(void)
{
    volatile u8 ReadValue;
	
	ReadValue = HALL_INFO & 0x07;

    return(ReadValue);
}

/******************* (C) COPYRIGHT 2008 LINKO Semiconductor *****END OF FILE****/
