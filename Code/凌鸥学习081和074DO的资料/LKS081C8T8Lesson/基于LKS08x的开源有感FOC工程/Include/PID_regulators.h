/******************** (C) COPYRIGHT 2008 LINKO Semiconductor ********************

*******************************************************************************/

 
#ifndef __PI_REGULATORS__H
#define __PI_REGULATORS__H

/* ---------------------------------PID参数设置------------------------------- */

#define MAX_VQ_LIM             		(u16)32767    /* Q轴最大输出限制，Q15格式，取值范围0~32767 */
#define MAX_VD_LIM             		(u16)30000    /* D轴最大输出限制，Q15格式，取值范围0~32767 */  

/* Toruqe/Flux/SP PID  parameter dividers */

#define TF_KPDIV 					((u16)(12))     
#define TF_KIDIV 					((u16)(13))

#define FLUX_KPDIV 					((u16)(11))
#define FLUX_KIDIV 					((u16)(14))

#define SP_KPDIV 					((u16)2) 
#define SP_KIDIV 					((u16)(7))

/* default values for Flux control loop */

#define PID_FLUX_KP_DEFAULT  		(s16)5800     
#define PID_FLUX_KI_DEFAULT  		(s16)200    

#define PID_TORQUE_KP_DEFAULT  		(s16)16000   
#define PID_TORQUE_KI_DEFAULT  		(s16)50   

#define PID_SPEED_KP_DEFAULT      	(s16)212
#define PID_SPEED_KI_DEFAULT      	(s16)60


#define FLUX_KP_CHANGE_STEP       	200


#define ID_dKp 						1
#define ID_dKi 						2
#define ID_dKd 						3

#define NL  						0
#define NM  						1
#define NS  						2
#define ZE  						3
#define PS  						4
#define PM  						5
#define PL  						6

static const s16 fuzzyRuleKp[7][7] = {

    NL, NL, NM, NM, NS, NS, ZE,
    NL, NL, NM, NM, NS, ZE, ZE,
    NM, NM, NM, NS, ZE, PS, PM,
    NM, NS, NS, ZE, PS, PM, PM,
    NS, NS, ZE, PS, PS, PM, PM,
    ZE, ZE, PS, PM, PM, PM, PL,
    ZE, PS, PS, PM, PM, PL, PL

};//dKp 模糊控制规则表

/* Exported variables ------------------------------------------------------- */

#endif 

/******************* (C) COPYRIGHT 2008 LINKO Semiconductor *****END OF FILE****/
