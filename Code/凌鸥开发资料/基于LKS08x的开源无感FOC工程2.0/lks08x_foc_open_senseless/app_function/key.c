#include "global_variable.h"
void Key_in(stru_FOC_CtrProcDef *this)
{
    if(GPIO_ReadInputDataBit(GPIO2,GPIO_Pin_12)==0)
    {
        this->bMC_RunFlg = 0;
    }
    else if(GPIO_ReadInputDataBit(GPIO2,GPIO_Pin_11)==0)
    {
        this->bMC_RunFlg = 1;
    }
}
