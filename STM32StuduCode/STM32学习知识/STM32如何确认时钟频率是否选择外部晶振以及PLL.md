# 确认外部晶振和PLL设置
_Exported on 2025/7/5 at GMT+8 0:13:48 from Cursor (0.51.2)_

---

**User**

现在我的时钟是72Mhz吗?我的外部是中是8M的晶振,请通读全部代码,告诉我如何看,在哪里设置,来确定和保证我选择的是外部HSE的8M晶振,以及PLL倍频得到的是72Mhz

---

**Cursor**

结论  
当前工程已经按照 “外部 8 MHz 晶振(HSE) → PLL×9 → 72 MHz 系统时钟” 的思路配置完毕；只要代码正常启动，就会工作在 72 MHz。下面给出判定和修改要点。

────────────────────────────────────────
一、晶振频率的来源  
DriversInclude/stm32f10x.h 中默认把 HSE_VALUE 设成 8 MHz：

```112:118:DriversInclude/stm32f10x.h
#if !defined  HSE_VALUE
 #ifdef STM32F10X_CL   
  #define HSE_VALUE    ((uint32_t)25000000) /*!< 25 MHz，仅 Connectivity Line 用 */
 #else 
  #define HSE_VALUE    ((uint32_t)8000000)  /*!< 8 MHz，普通 F103 默认 */
 #endif
#endif
```

只要你没有在编译器宏里重新覆盖 HSE_VALUE，它就是 8 000 000 Hz，对应你的 8 MHz 外部晶振。

────────────────────────────────────────
二、PLL 倍频 & 72 MHz 的设置位置  
1. CMSIS 的启动文件  
SystemInit() 在上电复位后首先执行，里面根据预定义宏决定时钟。工程默认启用了 72 MHz 方案：

```380:450:DriversSource/system_stm32f10x.c
/* 已经打开的宏 */
#define SYSCLK_FREQ_72MHz  72000000
...
static void SetSysClock(void)
{
...
#elif defined SYSCLK_FREQ_72MHz
  SetSysClockTo72();        // 实际调用
#endif
```

SetSysClockTo72() 里用 HSE 作为 PLL 输入，倍频系数 9：

```1030:1046:DriversSource/system_stm32f10x.c
/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
RCC->CFGR |=  (RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
```

2. 用户自写的备用函数  
HardwareSRC/sys.c 里又写了一份 RCC_Configuration()，同样是 HSE×9：

```22:30:HardwareSRC/sys.c
RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // 8 MHz ×9 = 72 MHz
```

目前 main() 里并未调用 RCC_Configuration()，所以真正生效的是 SystemInit() 里的设置；保留这段代码对结果无影响。

────────────────────────────────────────
三、如何自行验证  
1. 在 main() 开头加一句  
```c
/* 打印或在调试器里观察 */
SystemCoreClockUpdate();
printf("SYSCLK=%lu\n", SystemCoreClock);   // 应该输出 72000000
```
或在调试器里直接查看全局变量 SystemCoreClock，应为 72 000 000。

2. 查看 SYSTICK 计数频率  
delay.c 里用到的 AHB_INPUT 常量已经按 72 MHz 填写：

```3:4:HardwareSRC/delay.c
#define AHB_INPUT 72 // 单位 MHz
```
如果时钟不是 72 MHz，延时时间会明显不准。

────────────────────────────────────────
四、若需修改/确认的关键点  
1. 改晶振频率  
   • 只改 DriversInclude/stm32f10x.h 中的 HSE_VALUE  
   • 或者在编译器宏里加 `-DHSE_VALUE=xxx`

2. 改系统时钟  
   • DriversSource/system_stm32f10x.c 顶部，注释掉不需要的 `#define SYSCLK_FREQ_xxMHz`，只保留目标频率那一行  
   • 对应 SetSysClockToxx() 里的 PLLMUL 也会自动匹配，无需手工改寄存器。

────────────────────────────────────────
五、结论  
• HSE_VALUE = 8 MHz → PLLMUL9 → SYSCLK = 72 MHz  
• SystemInit() 已自动完成配置，工程开机即运行在 72 MHz，不需要额外手动调用。  

如需进一步确认，可用示波器量 PB6/PB7 的 MCO 输出、或利用调试器查看 RCC->CFGR、FLASH->ACR 等寄存器的当前值。

```plaintext
#if !defined  HSE_VALUE
 #ifdef STM32F10X_CL   
  #define HSE_VALUE    ((uint32_t)25000000) /*!< 25 MHz，仅 Connectivity Line 用 */
 #else 
  #define HSE_VALUE    ((uint32_t)8000000)  /*!< 8 MHz，普通 F103 默认 */
 #endif
#endif
```

```c
/* 已经打开的宏 */
#define SYSCLK_FREQ_72MHz  72000000
...
static void SetSysClock(void)
{
...
#elif defined SYSCLK_FREQ_72MHz
  SetSysClockTo72();        // 实际调用
#endif
```

```c
/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
RCC->CFGR |=  (RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
```

```c
RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // 8 MHz ×9 = 72 MHz
```

```c
/* 打印或在调试器里观察 */
SystemCoreClockUpdate();
printf("SYSCLK=%lu\n", SystemCoreClock);   // 应该输出 72000000
```

```c
#define AHB_INPUT 72 // 单位 MHz
```

