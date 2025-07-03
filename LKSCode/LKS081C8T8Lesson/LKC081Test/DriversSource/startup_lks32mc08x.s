.syntax unified
.cpu cortex-m0
.thumb

/* ջ�Ѵ�С���ã������ӽű�����һ�£� */
.equ Stack_Size, 0x00000600  /* 1.5KBջ�ռ� */
.equ Heap_Size,  0x00000400  /* 1KB�ѿռ� */

/* �ж��������ϸ�ƥ���ֲᶨ�壩 */
.section .isr_vector, "a", %progbits
.align 2
.global __Vectors
.global __Vectors_End

__Vectors:
    /* Cortex-M0�����쳣���� */
    .word __initial_sp              /* 0: ջ��ָ�� */
    .word Reset_Handler             /* 1: ��λ������ */
    .word NMI_Handler               /* 2: NMI�ж� */
    .word HardFault_Handler         /* 3: Ӳ�����ж� */
    .word 0, 0, 0, 0, 0, 0, 0      /* 4-10: ���� */
    .word SVC_Handler               /* 11: ϵͳ���� */
    .word 0, 0                      /* 12-13: ���Ա��� */
    .word PendSV_Handler            /* 14: PendSV */
    .word SysTick_Handler           /* 15: ϵͳ�δ�ʱ�� */
    
    /* �����жϣ����ֲ�˳�� */
    .word TIMER0_IRQHandler         /* 16: ͨ�ö�ʱ��0 */
    .word TIMER1_IRQHandler         /* 17: ͨ�ö�ʱ��1 */
    .word TIMER2_IRQHandler         /* 18: ͨ�ö�ʱ��2 */
    .word TIMER3_IRQHandler         /* 19: ͨ�ö�ʱ��3 */
    .word ENCODER0_IRQHandler       /* 20: ������0 */
    .word ENCODER1_IRQHandler       /* 21: ������1 */
    .word I2C0_IRQHandler           /* 22: I2C0 */
    .word GPIO_IRQHandler           /* 23: GPIO�ж� */
    .word UART0_IRQHandler          /* 24: UART0 */
    .word HALL_IRQHandler           /* 25: ���������� */
    .word SPI0_IRQHandler           /* 26: SPI0 */
    .word ADC0_IRQHandler           /* 27: ADC0 */
    .word DSP_IRQHandler            /* 28: �������DSP */
    .word MCPWM_IRQHandler          /* 29: ���PWMģ�� */
    .word UART1_IRQHandler          /* 30: UART1 */
    .word CMP_IRQHandler            /* 31: �Ƚ��� */
    .word WAKE_IRQHandler           /* 32: �����ж� */
    .word PVD_IRQHandler            /* 33: ������ */
    .word DMA_IRQHandler            /* 34: DMA */
    .word 0                         /* 35: ��������CAN�� */
    .word SIF_IRQHandler            /* 36: ����ͨ�� */
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  /* 37-48: ���� */
__Vectors_End:

.section .text.Reset_Handler, "ax", %progbits
.align 2
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* ��ʼ����ջָ�� */
    ldr r0, =__initial_sp
    mov sp, r0

    /* 1. ������׼��ѹԴBGP���ֲ�4.4�ڣ� */
    ldr r1, =0x40000034     /* SYS_AFE_REG5��ַ */
    ldr r2, [r1]
    movs r3, #0x01          /* ���BGPPDλ��0=������ */
    bics r2, r3
    str r2, [r1]
    
    /* 2. ��ʼ��4MHz�ڲ�RCʱ�ӣ��ֲ�4.3�ڣ� */
    ldr r1, =0x40000038     /* SYS_AFE_REG6��ַ */
    movs r2, #0x00          /* ѡ��HSI��ΪPLLԴ */
    str r2, [r1]
    
    ldr r1, =0x40000034     /* SYS_AFE_REG5 */
    ldr r2, [r1]
    ldr r3, =0x8000         /* PLLPDNλ���루λ15�� */
    orrs r2, r3
    str r2, [r1]
    
    /* 3. �ȴ�PLL�ȶ���Լ6��s�� */
    movs r3, #100
1:  subs r3, #1
    bne 1b

    /* 4. �л�ϵͳʱ�ӵ�PLL��96MHz�� */
    ldr r1, =0x40000080     /* SYS_CLK_CFG��ַ */
    ldr r2, =0x01FF         /* CLK_SEL=1, CLK_DIV=0xFF��96MHz�� */
    str r2, [r1]

    /* 5. ����.data�� - �޸����ַ���� */
    ldr r0, =_sidata        /* Flash����Դ��ַ */
    ldr r1, =_sdata         /* RAMĿ����ʼ��ַ */
    ldr r2, =_edata         /* RAMĿ�������ַ */
copy_data_loop:
    cmp r1, r2              /* �Ƚϵ�ǰ��ַ�������ַ */
    beq zero_bss            /* �������ת��.bss���� */
    ldr r3, [r0]            /* ��Flash�������� */
    str r3, [r1]            /* �洢��RAM */
    adds r0, #4             /* �ֶ�����Դ��ַ */
    adds r1, #4             /* �ֶ�����Ŀ���ַ */
    b copy_data_loop        /* ����ѭ�� */

zero_bss:
    /* 6. ����.bss�� */
    ldr r0, =_sbss          /* .bss��ʼ��ַ */
    ldr r1, =_ebss          /* .bss������ַ */
    movs r2, #0
zero_bss_loop:
    cmp r0, r1              /* �Ƚϵ�ǰ��ַ�������ַ */
    beq init_array          /* �������ת�������ʼ�� */
    str r2, [r0]            /* �洢0 */
    adds r0, #4             /* �ֶ����ӵ�ַ */
    b zero_bss_loop         /* ����ѭ�� */

init_array:
    /* 7. ���ÿ��ʼ�� */
    bl __libc_init_array

    /* 8. �����û�SystemInit */
    bl SystemInit

    /* 9. ��ת��main */
    bl main

    /* 10. ���������ش��� */
infinite_loop:
    b infinite_loop
.size Reset_Handler, . - Reset_Handler

/* ������ϵͳ��ʼ�� */
.section .text.SystemInit, "ax", %progbits
.weak SystemInit
.type SystemInit, %function
SystemInit:
    bx lr
.size SystemInit, . - SystemInit

/* �ж�Ĭ�ϴ��� */
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

/* �ļ�ĩβ��ӿ��н������ */