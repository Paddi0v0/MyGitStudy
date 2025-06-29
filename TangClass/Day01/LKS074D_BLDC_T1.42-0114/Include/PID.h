#ifndef PID_h
#define PID_h

#include "hardware_config.h"
#include "global_variable.h"

#define MAX_DUTY                      (u16)32767
#define MIN_DUTY                      (u16)1000    


	#define SSum_Kp  Q15(0.03)    //�ٶȻ�Kp
	#define SSum_Ki  Q15(0.005)   //�ٶȻ�Ki
	#define SSum_Kc  Q15(0.5)
	
	#define ISum_Kp  Q15(0.05)
	#define ISum_Ki  Q15(0.01)
	#define ISum_Kc  Q15(0.05)

  #define Q15(Float_Value)	\
			((Float_Value < 0.0) ? (s16)(32768 * (Float_Value) - 0.5) \
			: (s16)(32767 * (Float_Value) + 0.5))

	typedef struct {
	   signed   long  qdSum;
	   signed   int   qKp;
	   signed   int   qKi;
	   signed   int   qKc;
	   signed   int   qOutMax;
	   signed   int   qOutMin;
	   signed   int   qInRef;
	   signed   int   qInMeas;
	   signed   int   qOut;
	} tPIParm;

	extern tPIParm PIParmI;                //��������PI�ṹ����� 
	extern tPIParm PIParmS;                //�ٶȵ���PI�ṹ�����

	extern void InitPI(void);              //PI��ʼ������
	extern void CalcPI( tPIParm *pParm);   //PI�������

#endif
