#include "PID.h"	
#include "hardware_config.h"

tPIParm PIParmI;//��������PI�ṹ����� 
tPIParm PIParmS;//�ٶȵ���PI�ṹ�����
//////////////////////////////////////////////////////////////////////////

//��������:  CalcPI( tPIParm *pParm)PI������

//��������˵��: ���ڵ���ٶȻ��ıջ�����

//���������pParm->qInMeas�ο����� pParm->qInRef��������

//���������PIParmI.qOut PI�������

//���ú�������

//������ڣ�2017-2-21

///////////////////////////////////////////////////////////////

void CalcPI( tPIParm *pParm)
{
	signed int   Error;
	signed int   Exc;
	signed long  U;
	Error =  pParm->qInRef - pParm->qInMeas;
	U =  pParm->qdSum + pParm-> qKp * Error;
	U  >>= 15;
	if( U  >  pParm-> qOutMax)
	{
		pParm->qOut = pParm-> qOutMax ;
	}
	else if( U  <  pParm-> qOutMin)
	{
		pParm->qOut = pParm-> qOutMin;
	}
	else
	{
		pParm->qOut  =  U;
	}
	Exc = U - pParm->qOut;
	pParm->qdSum +=  pParm-> qKi* Error - pParm-> qKc * Exc;
}


void InitPI(void)
{
	PIParmI.qOutMax    = MAX_DUTY;
	PIParmI.qOutMin    = MIN_DUTY;
	PIParmI.qKp        = ISum_Kp ;
	PIParmI.qKi        = ISum_Ki ;
	PIParmI.qKc        = ISum_Kc ;
	PIParmI.qdSum      = 0;
	PIParmI.qInMeas    = 0;
	PIParmI.qOut       = MIN_DUTY;
	
	PIParmS.qOutMax    = MAX_DUTY;
	PIParmS.qOutMin    = MIN_DUTY;
	PIParmS.qKp        = SSum_Kp ;
	PIParmS.qKi        = SSum_Ki ;
	PIParmS.qKc        = SSum_Kc ;
	PIParmS.qdSum      = 0;
	PIParmS.qInMeas    = 0;
	PIParmS.qOut       = MIN_DUTY;
}


