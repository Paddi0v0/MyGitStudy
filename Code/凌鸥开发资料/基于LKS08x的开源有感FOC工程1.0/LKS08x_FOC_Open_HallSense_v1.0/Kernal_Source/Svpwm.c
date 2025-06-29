#include "global_variable.h"
#include "hardware_config.h"
#include "function_config.h" 

/*******************************************************************************
 函数名称：    void CurrentOffsetRead(void)
 功能描述：    测试电流Offset值
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2018/7/22      V1.0           Howlet Li          创建
 *******************************************************************************/

 void currentOffsetRead(void)
{
    volatile s32 t_offset1, t_offset2, t_offset3;
    volatile s32 t_offset4, t_offset5;
    volatile s32 t_offset6, t_offset7;
    volatile u32 t_dlay;   
    volatile u16 t_cnt;

    __disable_irq();
	
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Torque.wIntegral = 0;
    struFOC_CtrProc.struFOC_CurrLoop.struPI_Flux.wIntegral = 0;
    struFOC_CtrProc.struFOC_CurrLoop.struStatVolt_alfa_beta.qV_Value1 = 0;
    struFOC_CtrProc.struFOC_CurrLoop.struStatVolt_alfa_beta.qV_Value2 = 0;

    MCPWM_PRT = 0x0000DEAD; //enter password to unlock write protection
    MCPWM_TH00 = 0x00;
    MCPWM_TH01 = 0x00;
    MCPWM_TH10 = 0x00;
    MCPWM_TH11 = 0x00;
    MCPWM_TH20 = 0x00;
    MCPWM_TH21 = 0x00;
    MCPWM_UPDATE = 0xff;    //write whatever value to trigger update
    MCPWM_UPDATE = 0x00;
    MCPWM_PRT = 0x0000CAFE; //write any value other than 0xDEAD to enable write protection
    PWMOutputs(ENABLE);

    ADC0_CFG = 0;

    ADC0_CHN0 = ADC0_CUR_A_1ST_MSK | ADC1_CUR_B_1ST_MSK;
    ADC0_CHN1 = ADC0_CUR_B_1ST_MSK | ADC1_CUR_C_1ST_MSK;
    ADC0_CHN2 = ADC0_CUR_C_1ST_MSK | ADC1_CUR_A_1ST_MSK;
    ADC0_CHN3 = ADC0_BUS_CUR_CHANNEL | ADC1_4th_MSK;

    ADC0_CFG |= BIT2;

    for (t_dlay = 0; t_dlay < 0x2ffff; t_dlay++);

    t_offset1 = 0;
    t_offset2 = 0;
    t_offset3 = 0;
    t_offset4 = 0;
    t_offset5 = 0;
    t_offset6 = 0;
    t_offset7 = 0;

    ADC0_IF = 0x1f;

    ADC0_SWT = 0x00005AA5;

    /* get PGA offset */
    for (t_cnt = 0; t_cnt < ADC_GET_OFFSET_CNT; t_cnt++)
    {
        t_dlay = 0;
        for (t_dlay = 0; t_dlay < 1000; t_dlay++);
        ADC0_IF |= BIT1 | BIT0;

        t_offset1 += (s16)((ADC0_DAT0));
        t_offset2 += (s16)((ADC0_DAT1));
        t_offset3 += (s16)((ADC0_DAT2));
        t_offset4 += (s16)((ADC0_DAT3));
        t_offset5 += (s16)((ADC0_DAT4));
        t_offset6 += (s16)((ADC0_DAT5));
        t_offset7 += (s16)((ADC0_DAT6));
        /* Clear the ADC0 JEOC pending flag */
        ADC0_SWT = 0x00005AA5;
    }

    ADC_init();

    PWMOutputs(DISABLE);

    struFOC_CtrProc.struFOC_CurrLoop.bget_offset_flg = 1;
	 
	struFOC_CtrProc.struFOC_CurrLoop.nPhaseAOffset = (s16)(t_offset1 >> 9);
	struFOC_CtrProc.struFOC_CurrLoop.nPhaseBOffset1 = (s16)(t_offset2 >> 9);
	struFOC_CtrProc.struFOC_CurrLoop.nPhaseBOffset = (s16)(t_offset3 >> 9);
	struFOC_CtrProc.struFOC_CurrLoop.nPhaseCOffset = (s16)(t_offset4 >> 9);
	struFOC_CtrProc.struFOC_CurrLoop.nphaseAoffsetShift = (s16)(t_offset5 >> 9);
	struFOC_CtrProc.struFOC_CurrLoop.nphaseCoffsetShift = (s16)(t_offset6 >> 9);
	struFOC_CtrProc.struFOC_CurrLoop.nBusCurrentOffset = (s16)(t_offset7 >> 9);
 
    __enable_irq();
}

/*******************************************************************************
 函数名称：    void CurrentOffsetCalibration(void)
 功能描述：    读Flash中的电流Offset值
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/16      V1.0           Howlet Li          创建
 2017/7/5        V1.2           Howlet Li          修订Bug
 在电源电压低的时候，不学习偏置，增加一路B相偏置
 *******************************************************************************/

void CurrentOffsetCalibration(void)
{
    volatile u32 t_dlay;
    volatile u16 t_cnt;

    u32 t_FlashAddr;
    u32 t_FlashBuf[20];

    FlashParamaStruct *flashStru;

    flashStru = (FlashParamaStruct*)&t_FlashBuf[0];

    t_dlay = 0;
	
    while(struFOC_CtrProc.struFOC_CurrLoop.nBusVoltage < LOW_VOLATAGE_THD)
    {
        t_dlay++;
		
        if((t_dlay > 0x7ffff) || (struFOC_CtrProc.struFOC_CurrLoop.nBusVoltage > LOW_VOLATAGE_THD))
        {
            break;
        }
    }

    if(t_dlay < 0x6ffff)
    {
        for(t_dlay = 0; t_dlay < 0x6ffff; t_dlay++);

        for (t_cnt = 0; t_cnt < 20; t_cnt++)
        {
            currentOffsetRead();
			
            if(struFOC_CtrProc.struFOC_CurrLoop.bget_offset_flg)
            {
                break;
            }
        }

        if(struFOC_CtrProc.struFOC_CurrLoop.bget_offset_flg)
        {
            t_FlashAddr = HALL_LEARN_ADDR;
			
            for (t_cnt = 0; t_cnt < 20; t_cnt++)
            {
                t_FlashBuf[t_cnt] = REG32(t_FlashAddr);
                t_FlashAddr += 4;
            }

            flashStru->phaseAoffset = struFOC_CtrProc.struFOC_CurrLoop.nPhaseAOffset;
            flashStru->phaseBoffset = struFOC_CtrProc.struFOC_CurrLoop.nPhaseBOffset;
            flashStru->phaseCoffset = struFOC_CtrProc.struFOC_CurrLoop.nPhaseCOffset;
            flashStru->phaseBusOffset = struFOC_CtrProc.struFOC_CurrLoop.nBusCurrentOffset;
            flashStru->phaseB1offset = struFOC_CtrProc.struFOC_CurrLoop.nPhaseBOffset1;
			flashStru->phaseAoffset1 = struFOC_CtrProc.struFOC_CurrLoop.nphaseAoffsetShift;
            flashStru->phaseCoffset1 = struFOC_CtrProc.struFOC_CurrLoop.nphaseCoffsetShift;

            struFOC_CtrProc.struFOC_CurrLoop.bget_offset_flg = 0;
			
            judgement_offset(&struFOC_CtrProc.struFOC_CurrLoop);

            if(struFOC_CtrProc.struFOC_CurrLoop.bget_offset_flg == 0)
            {
                __disable_irq();
				erase_flag = 0x9A0D361F;   //写擦除密码
				EraseSector(0x7800,0);
				progm_flag = 0x9AFDA40C;   //写编程密码
				ProgramPage(0x7800, 512, (u8*)&t_FlashBuf[0], 0);
                __enable_irq();
                set_OPA_offset(&struFOC_CtrProc.struFOC_CurrLoop); /* 2018.08.22 偏置问题 */
            }
            else
            {
                stru_Faults.B.OffsetError = 1;
            }
        }
        else
        {
            stru_Faults.B.OffsetError = 1;
        }
    }
    else
    {
        stru_Faults.B.OffsetError = 1;
    }
}

/*******************************************************************************
 函数名称：    void judgement_offset(stru_FOC_CurrLoopDef *this)
 功能描述：    判断偏置是否正常
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void judgement_offset(stru_FOC_CurrLoopDef *this)
{
    s16 t_Value;

    if((this->nPhaseAOffset > PHASE_OFFSET_MAX) || (this->nPhaseAOffset < PHASE_OFFSET_MIN))
    {
        this->bget_offset_flg = 1;
    }

    if((this->nPhaseBOffset > PHASE_OFFSET_MAX) || (this->nPhaseBOffset < PHASE_OFFSET_MIN))
    {
        this->bget_offset_flg = 1;
    }

    if((this->nPhaseBOffset1 > PHASE_OFFSET_MAX) || (this->nPhaseBOffset1 < PHASE_OFFSET_MIN))
    {
        this->bget_offset_flg = 1;
    }

    if((this->nPhaseCOffset > PHASE_OFFSET_MAX) || (this->nPhaseCOffset < PHASE_OFFSET_MIN))
    {
        this->bget_offset_flg = 1;
    }

    if((this->nBusCurrentOffset > PHASE_OFFSET_MAX) || (this->nBusCurrentOffset < PHASE_OFFSET_MIN))
    {
        this->bget_offset_flg = 1;
    }

    t_Value = this->nPhaseAOffset + this->nPhaseBOffset 
			+ this->nPhaseCOffset + this->nBusCurrentOffset;

    if((t_Value == 0) || (t_Value == -4))
    {
        this->bget_offset_flg = 1;
    }
}

/*******************************************************************************
 函数名称：    void lowPass_filter(stru_RC_Def *rc, s16 signal)
 功能描述：    低通滤波器
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
s16 lowPass_filter(stru_RC_Def *rc, s16 signal)
{
    s32 wkg;
    wkg = (signal - (s16)(rc->yk_1 >> 16)) * (rc->coef);
    rc->yk_1 += wkg;
    return(rc->yk_1 >> 16);
}

/*******************************************************************************
 函数名称：    void SVPWM_2PH(stru_FOC_CtrProcDef *pCtrProc)
 功能描述：    生成SVPWM波形
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/06/15      V1.0         LiuH              创建
 *******************************************************************************/
void SVPWM_2PH(stru_FOC_CtrProcDef *pCtrProc)
{
   volatile s32 wX, wY, wZ, wUAlpha, wUBeta;
	
	stru_FOC_CurrLoopDef *this;

    this = &pCtrProc->struFOC_CurrLoop;
	
	wUAlpha = (this->struStatVolt_alfa_beta.qV_Value1 * 28378) >> 15;
    wUBeta = (this->struStatVolt_alfa_beta.qV_Value2 >> 1);
	
	wX = this->struStatVolt_alfa_beta.qV_Value2; /* REF1 = wX */
	wY = (wUBeta + wUAlpha); /* REF3 = -wY */
	wZ = (wUBeta - wUAlpha);
	
	if (wY > 0)
	{
		if (wZ > 0)
		{
			this->bSector = 2;
		}
		else
		{
			if (wX <= 0)
			{
				this->bSector = 6;
			}
			else
			{
				this->bSector = 1;
			}
		}
	}
	else
	{
		if (wZ <= 0)
		{
			this->bSector = 5;
		}
		else
		{
			if (wX <= 0)
			{
				this->bSector = 4;
			}
			else
			{
				this->bSector = 3;
			}
		}
	}
	
	switch (this->bSector)
	{
		case 1:
			this->struVoltUVW_PWM.w = 0; /* T1 = 0 */
			this->struVoltUVW_PWM.v = wX;/* T2 = T_1 */
			this->struVoltUVW_PWM.u = this->struVoltUVW_PWM.v - wZ;  /* T3 = T2 + T_2 */
			/* 采样 B C 相电流 */
			ADC0_CHN0 = this->Stru_ADC_sampParama.ADC0_B_C_Cur_First;
			ADC0_CHN1 = this->Stru_ADC_sampParama.ADC0_B_C_Cur_First;
			break;

		case 2:
			this->struVoltUVW_PWM.w = 0; /* T1 = 0 */
			this->struVoltUVW_PWM.u = wY;/* T2 = T_1 */
			this->struVoltUVW_PWM.v = this->struVoltUVW_PWM.u + wZ;  /* T3 = T2 + T_2 */
			/* 采样 A C 相电流 */
			ADC0_CHN0 = this->Stru_ADC_sampParama.ADC0_A_C_Cur_First;
			ADC0_CHN1 = this->Stru_ADC_sampParama.ADC0_A_C_Cur_First;
			break;

		case 3:
			this->struVoltUVW_PWM.u = 0; /* T1 = 0 */
			this->struVoltUVW_PWM.w = -wY;/* T2 = T_1 */
			this->struVoltUVW_PWM.v = this->struVoltUVW_PWM.w + wX;  /* T3 = T2 + T_2 */
			/* 采样 A C 相电流 */
			ADC0_CHN0 = this->Stru_ADC_sampParama.ADC0_A_C_Cur_First;
			ADC0_CHN1 = this->Stru_ADC_sampParama.ADC0_A_C_Cur_First;
			break;

		case 4:
			this->struVoltUVW_PWM.u = 0; /* T1 = 0 */
			this->struVoltUVW_PWM.v = wZ;/* T2 = T_1 */
			this->struVoltUVW_PWM.w = this->struVoltUVW_PWM.v - wX;  /* T3 = T2 + T_2 */
			/* 采样 A B 相电流 */
			ADC0_CHN0 = this->Stru_ADC_sampParama.ADC0_A_B_Cur_First;
			ADC0_CHN1 = this->Stru_ADC_sampParama.ADC0_A_B_Cur_First;
			break;

		case 5:
			this->struVoltUVW_PWM.v = 0; /* T1 = 0 */
			this->struVoltUVW_PWM.u = -wZ;/* T2 = T_1 */
			this->struVoltUVW_PWM.w = this->struVoltUVW_PWM.u - wY;  /* T3 = T2 + T_2 */
			/* 采样 A B 相电流 */
			ADC0_CHN0 = this->Stru_ADC_sampParama.ADC0_A_B_Cur_First;
			ADC0_CHN1 = this->Stru_ADC_sampParama.ADC0_A_B_Cur_First;
			break;

		case 6:
			this->struVoltUVW_PWM.v = 0; /* T1 = 0 */
			this->struVoltUVW_PWM.w = -wX;/* T2 = T_1 */
			this->struVoltUVW_PWM.u = this->struVoltUVW_PWM.w + wY;  /* T3 = T2 + T_2 */
			/* 采样 B C 相电流 */
			ADC0_CHN0 = this->Stru_ADC_sampParama.ADC0_B_C_Cur_First;
			ADC0_CHN1 = this->Stru_ADC_sampParama.ADC0_B_C_Cur_First;
			break;

		default:
			break;
	}
	
	this->struVoltUVW_PWM.u = (this->struVoltUVW_PWM.u * PWM_PERIOD) >> 15;
	this->struVoltUVW_PWM.v = (this->struVoltUVW_PWM.v * PWM_PERIOD) >> 15;
	this->struVoltUVW_PWM.w = (this->struVoltUVW_PWM.w * PWM_PERIOD) >> 15;
}

/*******************************************************************************
 函数名称：    void SVPWM_2PH_3ShuntGetPhaseCurrentValues(void)
 功能描述：    读电流值
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/16      V1.0           Howlet Li          创建
 2017/7/5        V1.2           Howlet Li          修订Bug
 不同ADC采样B相电流的时候，偏置不同，B相电流有两个偏置
 *******************************************************************************/

stru_CurrVoctor SVPWM_2PH_3ShuntGetPhaseCurrentValues(stru_FOC_CurrLoopDef *this)
{
	volatile s32 wAux;
	s16 t_current_a, t_current_b;
    stru_CurrVoctor Local_Stator_Currents = { 0, 0 };
	
	switch (this->bSector)
	{
		case 4:
		case 5: /* Current on Phase C not accessible  */
			wAux = (s16)(ADC0_DAT0) - this->nPhaseAOffset;

			if (wAux < S16_MIN)
			{
				t_current_a = S16_MIN;
			}
			else  if (wAux > S16_MAX)
			{
				t_current_a = S16_MAX;
			}
			else
			{
				t_current_a = (s16)wAux;
			}

			wAux = (s16)(ADC0_DAT1) - this->nPhaseBOffset;

			if (wAux < S16_MIN)
			{
				t_current_b = S16_MIN;
			}
			else  if (wAux > S16_MAX)
			{
				t_current_b = S16_MAX;
			}
			else
			{
				t_current_b = (s16)wAux;
			}

			break;

		case 1:  /* Current on Phase A not accessible  采样 B C 相电流   */
		case 6:
			wAux = (s16)(ADC0_DAT0) - this->nPhaseBOffset;

			if (wAux < S16_MIN)
			{
				t_current_b = S16_MIN;
			}
			else  if (wAux > S16_MAX)
			{
				t_current_b = S16_MAX;
			}
			else
			{
				t_current_b = (s16)wAux;
			}

			wAux = this->nPhaseCOffset - (s16)ADC0_DAT1;
			wAux -=  t_current_b;

			if (wAux > S16_MAX)
			{
				t_current_a = S16_MAX;
			}
			else  if (wAux < S16_MIN)
			{
				t_current_a = S16_MIN;
			}
			else
			{
				t_current_a = (s16)wAux;
			}

			break;

		case 3:  /* Current on Phase B not accessible 采样 A C 相电流 */
		case 2:
			wAux = (s16)(ADC0_DAT0) - this->nPhaseAOffset;

			if (wAux < S16_MIN)
			{
				t_current_a = S16_MIN;
			}
			else  if (wAux > S16_MAX)
			{
				t_current_a = S16_MAX;
			}
			else
			{
				t_current_a = (s16)wAux;
			}

			wAux = this->nPhaseCOffset - (s16)ADC0_DAT1;
			wAux -= t_current_a;

			if (wAux > S16_MAX)
			{
				t_current_b = S16_MAX;
			}
			else  if (wAux < S16_MIN)
			{
				t_current_b = S16_MIN;
			}
			else
			{
				t_current_b = (s16)wAux;
			}

			break;

		default:
			break;
	}

    Local_Stator_Currents.qI_Value1 = t_current_a;
    Local_Stator_Currents.qI_Value2 = t_current_b;

    return (Local_Stator_Currents);
}

/******************* (C) COPYRIGHT 2008 LINKO Semiconductor *****END OF FILE****/
