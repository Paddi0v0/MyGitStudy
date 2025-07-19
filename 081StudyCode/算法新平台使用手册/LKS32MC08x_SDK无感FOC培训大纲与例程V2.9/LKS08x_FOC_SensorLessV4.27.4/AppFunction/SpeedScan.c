/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： SpeedScan.c
 * 文件标识：
 * 内容摘要： 电位器调速，PWM调速处理程序
 * 其它说明： 
 * 当前版本： V1.0
 * 作    者：   HuangMG
 * 完成日期： 2022年5月30日
 *
 *******************************************************************************/
#include "speedscan.h"
#include "MC_type.h"
#include "fault_detection.h"
#include "Global_Variable.h"

/*****************************************************************************
 * 函数名   : VspSpeedScan(void)
 * 说明     : 
 * 设计思路 ：1.根据检测到电压计算对应转速
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
void VspSpeedScan(void)
{
    if(struAppCommData.nVspADC < VSP_OFF)
    {
        struFOC_CtrProc.bMC_RunFlg = 0;
    }
    else if(struAppCommData.nVspADC < VSP_MIN)
    {
         struAppCommData.wVSPSpeedSet = VSP_SPEED_MIN;
        
        if((struFOC_CtrProc.bMC_RunFlg == 0) && (stru_Faults.R == 0))
        {
            struFOC_CtrProc.bMC_RunFlg = 1;
        }
    }
    else if(struAppCommData.nVspADC  < VSP_MAX)
    {
        struAppCommData.wVSPSpeedSet = (VSP_SPEED_SCALE * (struAppCommData.nVspADC - VSP_MIN)) + VSP_SPEED_MIN;
        
        if((struFOC_CtrProc.bMC_RunFlg == 0) && (stru_Faults.R == 0))
        {
            struFOC_CtrProc.bMC_RunFlg = 1;
        }
        
    }
    else
    {
        struAppCommData.wVSPSpeedSet = VSP_SPEED_MAX;

        if((struFOC_CtrProc.bMC_RunFlg == 0) && (stru_Faults.R == 0))
        {
            struFOC_CtrProc.bMC_RunFlg = 1;
        }
    }
    struAppCommData.wSpeedValue = App2CoreFreqTrans(User2AppFreqTrans(struAppCommData.wVSPSpeedSet));
 		
}


void KEY_Scan(void)
{
  if( GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_11) == 0)
	{
		struFOC_CtrProc.bMC_RunFlg = 1;
	}
	
	 if(GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_12) == 0)
	{
		struFOC_CtrProc.bMC_RunFlg = 0;
	
	}

}



