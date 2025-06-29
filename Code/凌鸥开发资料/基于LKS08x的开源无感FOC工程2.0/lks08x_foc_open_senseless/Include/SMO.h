#include "lks32mc08x_lib.h"
#include "hardware_config.h"
#include "mc_type.h"


typedef struct
{
    stru_CurrAlphBeta Ialfa_beta;
    stru_VoltAlphBeta Valfa_beta;
} stru_SMO_InputsDef;

void SMO_clear(stru_SMODef * this);
 int16_t SMO_CalcElAngle(stru_SMODef * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta);
s32 HL_PI_AntiDump(s32 InputError, stru_PIparams *pParams);
void SMO_init(stru_SMODef *this);
