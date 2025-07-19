#include "basic.h"
#include "lks32mc07x.h"
#include "lks32mc07x_flash.h"
#include "lks32mc07x_sys.h"
#include "lks32mc07x_adc.h"
#include "absacc.h"
#include "hardware_config.h"
#include "lks32mc07x_MCPWM.h"
#include "lks32mc07x_sys.h"
#include "project_config.h"

void delay(u16 cnt);
void ADC_init(void);

#if (CLASSB_ENABLE == FUNCTION_ON)

#define   SAFTEY_MEMORY_ADDR       0x9C00             //MarchC+检测结果和flash校验golden结果存储地址，此地址一定要大于FLASH_SIZE
#define   ROM_INSERT_ERR_ADDR      0x8200             //ROM自检插入故障时的flash地址，此地址一定要小于FLASH_SIZE且是空闲没有被代码占用的

#define   CRC_RESULT_BUFFER        0x20001100         //flash crc自检中间结果存储RAM地址

#undef    RAM_SIZE
#undef    FLASH_CRC_SIZE
#define   RAM_SIZE                 0x1FFE              //要检测的RAM空间，LKS08x 最大设置0x1FFE,LKS05x 最大设置0x9FE,LKS03x 最大设置0xFFE,LKS07x 最大设置0x2FFE
#define   RAM_ITER                 (RAM_SIZE >> 1)    //(RAM_SIZE>>1)

#define   FLASH_CRC_SIZE           0x8400             //flash CRC校验的空间范围，CRC每次检测32位数据
#define   FLASH_ITER               (FLASH_CRC_SIZE >> 5)  //FLASH_SIZE/32

#define   TEST_PART1_NUMS          30                 //REG_ITER
#define   TEST_PART2_NUMS          RAM_ITER           //RAM_ITER+35
#define   TEST_PART3_NUMS          FLASH_ITER         //FLASH_ITER+RAM_ITER+35

#define   WDT_WAIT_CNT             1000               //设置看门狗递减次数，值越大计算越准确，建议设置500以上


/*------------------------------软件认证故障码 -------------------*/ 
#define   MARCHC_ERROR             BIT0         /* MarchC+自检故障 */
#define   REG_ERROR                BIT1         /* 核心寄存器故障 */
#define   RAM_ERROR                BIT2         /* RAM故障 */
#define   ROM_ERROR                BIT3         /* ROM故障 */
#define   GPIO_IN_ERROR            BIT4         /* GPIO输入自检故障 */
#define   GPIO_OUT_ERROR           BIT5         /* GPIO输出自检故障 */
#define   PC_ERROR                 BIT6         /* PC故障 */
#define   INTERRUPT_ERROR          BIT7         /* 中断故障 */
#define   ADC_ERROR                BIT8         /* ADC故障 */ 
#define   CLOCK_ERROR              BIT9         /* 时钟故障 */
#define   WDT_ERROR                BIT10        /* 看门狗故障 */

 
void Certification_init(void); 
void PC_Check(void);
void GPIO_Check(void);
void ADC_Init_Check(void);
void Interrupt_Check(void);
void CLOCK_Check(void);
void WDT_init(void);
void Period_TestSelf(void);
void MarchC_Result_init(void);
void ADC_Period_Check(void);
void Certification_init(void);
void WDT_Check(void);
void ROM_Error_insert(void);
void Certification_Check(void);
void Check_Data_init(void);

void REG_Period_check(void);
void RAM_Period_check(void);
void FLASH_Period_check(void);

u32 Micro_checkREG(u16 code);

void RAM_init_result_check(void);
void flash_check_init(void);
u32 crc_flash_block(u32 flash_start_addr, u32 size, u32 crc_result_buffer_addr);
void classBCheckInitProcess(void);


typedef struct
{
    u32 crc_golden;     
	  u32 MarchC_result;
    u8  null;	
} Software_SafteyStruct_o;

typedef struct
{   
    u32 crc_golden;            /* FLASH校验值 */
	  u32 MarchC_result;         /* MarchC+自检结果 */
	  u8  null;	
	  u8 buffer[512 - sizeof(Software_SafteyStruct_o)];
}Software_SafteyStruct;


typedef struct
{
	 volatile u16 check_err_flg;          /* 自检错误标志 */
	 volatile u16 Insert_err_flg;         /* 插入故障标志 */
	 volatile u16 index;                  /* REG & RAM & ROM 自检计数 */
	 volatile u16 err_numb;               /* REG & RAM & ROM 自检出故障的位置 */
	 volatile u32 crc_check;              /* CRC周期自检时自检结果 */
	 volatile u32 goldenCRC_flash;        /* 第一次flash校验的结果 */
	
	 volatile u16 state;                  /* REG & RAM & ROM 自检故障状态 */
	 volatile u16 error_state;            /* REG & RAM & ROM 自检故障状态 */	

	 volatile u16 Interrupt_TIMER_cnt;    /* 进timer中断次数计数 */
	 volatile u16 Interrupt_ADC_cnt;      /* 进ADC中断次数计数 */
	 volatile u16 Interrupt_cnt;          /* 每进一次timer中断进ADC中断的次数 */
	
	 volatile s16 VSS_ADC;                /* 内部GND ADC采样值 */
	 volatile s16 TEMP_ADC;               /* 内部温度传感器温度采样值 */
	
	 volatile u32 Timer_Cnt;              /* while等待到设置的看门狗递减次数时对应的UTIMER_UNT0_CNT计数值 */
	 volatile u32 LRC_frequency;          /* 低速时钟频率 */	
	
}Micro_check;

extern Micro_check microCheck;

extern volatile const Software_SafteyStruct struSaftey;

int RAM_Rsult(void);

int r0_test(void);
int r0_0scan(void);
int r1_0scan(void);
int r2_0scan(void);
int r3_0scan(void);
int r4_0scan(void);
int r5_0scan(void);
int r6_0scan(void);
int r7_0scan(void);
int r8_0scan(void);
int r9_0scan(void);
int r10_0scan(void);
int r11_0scan(void);
int r12_0scan(void);
int r13_0scan(void);
int r14_0scan(void);

int r0_1scan(void);
int r1_1scan(void);
int r2_1scan(void);
int r3_1scan(void);
int r4_1scan(void);
int r5_1scan(void);
int r6_1scan(void);
int r7_1scan(void);
int r8_1scan(void);
int r9_1scan(void);
int r10_1scan(void);
int r11_1scan(void);
int r12_1scan(void);
int r13_1scan(void);
int r14_1scan(void);

int occupied_halfword_scan(unsigned int addr);
#endif

/*****************************软件认证相关变量*****************************/

