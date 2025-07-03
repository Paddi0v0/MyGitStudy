.syntax unified
.cpu cortex-m0
.thumb

/* 栈堆大小配置（与链接脚本保持一致） */
.equ Stack_Size, 0x00000600  /* 1.5KB栈空间 */
.equ Heap_Size,  0x00000400  /* 1KB堆空间 */

/* 中断向量表（严格匹配手册定义） */
.section .isr_vector, "a", %progbits
.align 2
.global __Vectors
.global __Vectors_End

__Vectors:
    /* Cortex-M0核心异常向量 */
    .word __initial_sp              /* 0: 栈顶指针 */
    .word Reset_Handler             /* 1: 复位处理函数 */
    .word NMI_Handler               /* 2: NMI中断 */
    .word HardFault_Handler         /* 3: 硬故障中断 */
    .word 0, 0, 0, 0, 0, 0, 0      /* 4-10: 保留 */
    .word SVC_Handler               /* 11: 系统调用 */
    .word 0, 0                      /* 12-13: 调试保留 */
    .word PendSV_Handler            /* 14: PendSV */
    .word SysTick_Handler           /* 15: 系统滴答定时器 */
    
    /* 外设中断（按手册顺序） */
    .word TIMER0_IRQHandler         /* 16: 通用定时器0 */
    .word TIMER1_IRQHandler         /* 17: 通用定时器1 */
    .word TIMER2_IRQHandler         /* 18: 通用定时器2 */
    .word TIMER3_IRQHandler         /* 19: 通用定时器3 */
    .word ENCODER0_IRQHandler       /* 20: 编码器0 */
    .word ENCODER1_IRQHandler       /* 21: 编码器1 */
    .word I2C0_IRQHandler           /* 22: I2C0 */
    .word GPIO_IRQHandler           /* 23: GPIO中断 */
    .word UART0_IRQHandler          /* 24: UART0 */
    .word HALL_IRQHandler           /* 25: 霍尔传感器 */
    .word SPI0_IRQHandler           /* 26: SPI0 */
    .word ADC0_IRQHandler           /* 27: ADC0 */
    .word DSP_IRQHandler            /* 28: 电机控制DSP */
    .word MCPWM_IRQHandler          /* 29: 电机PWM模块 */
    .word UART1_IRQHandler          /* 30: UART1 */
    .word CMP_IRQHandler            /* 31: 比较器 */
    .word WAKE_IRQHandler           /* 32: 唤醒中断 */
    .word PVD_IRQHandler            /* 33: 掉电检测 */
    .word DMA_IRQHandler            /* 34: DMA */
    .word 0                         /* 35: 保留（无CAN） */
    .word SIF_IRQHandler            /* 36: 单线通信 */
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  /* 37-48: 保留 */
__Vectors_End:

.section .text.Reset_Handler, "ax", %progbits
.align 2
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* 初始化主栈指针 */
    ldr r0, =__initial_sp
    mov sp, r0

    /* 1. 开启基准电压源BGP（手册4.4节） */
    ldr r1, =0x40000034     /* SYS_AFE_REG5地址 */
    ldr r2, [r1]
    movs r3, #0x01          /* 清除BGPPD位（0=开启） */
    bics r2, r3
    str r2, [r1]
    
    /* 2. 初始化4MHz内部RC时钟（手册4.3节） */
    ldr r1, =0x40000038     /* SYS_AFE_REG6地址 */
    movs r2, #0x00          /* 选择HSI作为PLL源 */
    str r2, [r1]
    
    ldr r1, =0x40000034     /* SYS_AFE_REG5 */
    ldr r2, [r1]
    ldr r3, =0x8000         /* PLLPDN位掩码（位15） */
    orrs r2, r3
    str r2, [r1]
    
    /* 3. 等待PLL稳定（约6μs） */
    movs r3, #100
1:  subs r3, #1
    bne 1b

    /* 4. 切换系统时钟到PLL（96MHz） */
    ldr r1, =0x40000080     /* SYS_CLK_CFG地址 */
    ldr r2, =0x01FF         /* CLK_SEL=1, CLK_DIV=0xFF（96MHz） */
    str r2, [r1]

    /* 5. 复制.data段 - 修复后变址问题 */
    ldr r0, =_sidata        /* Flash数据源地址 */
    ldr r1, =_sdata         /* RAM目标起始地址 */
    ldr r2, =_edata         /* RAM目标结束地址 */
copy_data_loop:
    cmp r1, r2              /* 比较当前地址与结束地址 */
    beq zero_bss            /* 相等则跳转到.bss清零 */
    ldr r3, [r0]            /* 从Flash加载数据 */
    str r3, [r1]            /* 存储到RAM */
    adds r0, #4             /* 手动增加源地址 */
    adds r1, #4             /* 手动增加目标地址 */
    b copy_data_loop        /* 继续循环 */

zero_bss:
    /* 6. 清零.bss段 */
    ldr r0, =_sbss          /* .bss起始地址 */
    ldr r1, =_ebss          /* .bss结束地址 */
    movs r2, #0
zero_bss_loop:
    cmp r0, r1              /* 比较当前地址与结束地址 */
    beq init_array          /* 相等则跳转到数组初始化 */
    str r2, [r0]            /* 存储0 */
    adds r0, #4             /* 手动增加地址 */
    b zero_bss_loop         /* 继续循环 */

init_array:
    /* 7. 调用库初始化 */
    bl __libc_init_array

    /* 8. 调用用户SystemInit */
    bl SystemInit

    /* 9. 跳转到main */
    bl main

    /* 10. 主函数返回处理 */
infinite_loop:
    b infinite_loop
.size Reset_Handler, . - Reset_Handler

/* 弱定义系统初始化 */
.section .text.SystemInit, "ax", %progbits
.weak SystemInit
.type SystemInit, %function
SystemInit:
    bx lr
.size SystemInit, . - SystemInit

/* 中断默认处理 */
.macro DEFAULT_HANDLER name
.section .text.\name, "ax", %progbits
.weak \name
.type \name, %function
\name:
1:  b 1b
.size \name, . - \name
.endm

DEFAULT_HANDLER NMI_Handler
DEFAULT_HANDLER HardFault_Handler
DEFAULT_HANDLER SVC_Handler
DEFAULT_HANDLER PendSV_Handler
DEFAULT_HANDLER SysTick_Handler
DEFAULT_HANDLER TIMER0_IRQHandler
DEFAULT_HANDLER TIMER1_IRQHandler
DEFAULT_HANDLER TIMER2_IRQHandler
DEFAULT_HANDLER TIMER3_IRQHandler
DEFAULT_HANDLER ENCODER0_IRQHandler
DEFAULT_HANDLER ENCODER1_IRQHandler
DEFAULT_HANDLER I2C0_IRQHandler
DEFAULT_HANDLER GPIO_IRQHandler
DEFAULT_HANDLER UART0_IRQHandler
DEFAULT_HANDLER HALL_IRQHandler
DEFAULT_HANDLER SPI0_IRQHandler
DEFAULT_HANDLER ADC0_IRQHandler
DEFAULT_HANDLER DSP_IRQHandler
DEFAULT_HANDLER MCPWM_IRQHandler
DEFAULT_HANDLER UART1_IRQHandler
DEFAULT_HANDLER CMP_IRQHandler
DEFAULT_HANDLER WAKE_IRQHandler
DEFAULT_HANDLER PVD_IRQHandler
DEFAULT_HANDLER DMA_IRQHandler
DEFAULT_HANDLER SIF_IRQHandler

/* 文件末尾添加空行解决警告 */