    AREA    |.text|, CODE, READONLY
    THUMB


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   ASM Instruction Regression
;   Cycles: 
;   Parameters:
;       R0: a unused ram location to test load/store 未使用的RAM地址进行测试
;       R1: data seed, should be even                地址应为偶数
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
asm_test PROC
    EXPORT asm_test
    ; r0 addr, r1, data
;mov test
    ALIGN
    ldr r1, = 0xFFFFFFFF           ;R1 = 0xFFFFFFFF
    mov r2, r1                     ;R2 = R1 = 0xFFFFFFFF
    cmp r1, r2                     ;比较R1和R2，如果不相等，测试失败
    bne ASM_Fail
    
;push pop test    
    push {r2}                      ;？？？？？
    pop {r2}
    cmp r1, r2
    bne ASM_Fail

;mov test    
    movs r1,#0                     ;R1 = 0
    mov r2, r1                     ;R2 = R1 =0
    cmp r1, r2                     ;比较R1和R2，如果不相等，测试失败
    bne ASM_Fail
    
;push pop test    
    push {r2}
    pop {r2}
    cmp r1, r2
    bne ASM_Fail

;lsls test
    ALIGN
    ldr r1, = 0xF000500A           ;R1 = 0xF000500A
    ldr r2, = 0xC0014028           ;R2 = 0xC0014028
    lsls r1, #2                    ;R1左移2位，R1 = C0014028
    BCC ASM_Fail        ;if C clear
    BEQ ASM_Fail        ;if Z set
    BPL ASM_Fail        ;if N clear
    cmp r1,r2                      ;比较R1和R2，如果不相等，测试失败
    bne ASM_Fail
    
    movs r1, #0                    ;R1 = 0
    lsls r1, #2                    ;R1左移2位，R1 = 0
    BCS ASM_Fail        ;if C set
    BNE ASM_Fail        ;if Z clear
    BMI ASM_Fail        ;if N set
    movs r2, #0                    ;R2 = 0                
    cmp r1,r2
    bne ASM_Fail
    
;lsrs test
    ALIGN
    ldr r1, =0xFFFF0003            ;R1 = 0xFFFF0003
    ldr r2, =0x7FFF8001            ;R2 = 0x7FFF8001
    lsrs r1, #1                    ;R1右移1位，R1 = 0x7FFF8001
    BEQ ASM_Fail        ;if Z set
    BMI ASM_Fail        ;if N set
    cmp r1, r2
    bne ASM_Fail
    
    movs r1, #1                    ;R1 = 1
    movs r2, #0                    ;R2 = 0
    lsrs r1, #1                    ;R1右移1位，R1 = 0
    BNE ASM_Fail        ;if Z clear
    BMI ASM_Fail        ;if N set
    cmp r1, r2
    bne ASM_Fail

;asrs test
    ALIGN
    ldr r1, =0xFFFF0003            ;R1 = 0xFFFF0003
    ldr r2, =0xFFFF8001            ;R2 = 0xFFFF8001
    asrs r1, #1                    ;R1当做有符号数右移1位，最高位符号位不变，R1 = 0xFFFF8001
    BEQ ASM_Fail        ;if Z set
    BPL ASM_Fail        ;if N clear
    cmp r1, r2
    bne ASM_Fail
    
    movs r1, #1                    ;R1 = 1
    movs r2, #0                    ;R2 = 0
    asrs r1, #1                    ;R1当做有符号数右移1位，最高位符号位不变，R1 = 0
    BNE ASM_Fail        ;if Z clear
    BMI ASM_Fail        ;if N set
    cmp r1, r2
    bne ASM_Fail

;mvns test
    ALIGN
    ldr  r1, =0xFFFFFFFE           ;R1 = 0xFFFFFFFE
    movs r2, #1                    ;R2 = 1
    mvns r3, r2                    ;R3等于R2取反,R3 = 0xFFFFFFFE

    BPL ASM_Fail        ;if N clear
    BEQ ASM_Fail        ;if Z set
    cmp r1, r3
    BNE ASM_Fail
     
    ALIGN
    ldr  r1, =0xFFFFFFFF           ;R1 = 0xFFFFFFFF
    movs r2, #0                    ;R2 = 0
    mvns r3, r1                    ;R3等于R1取反，R3 = 0 
    BMI ASM_Fail        ;if N set
    BNE ASM_Fail        ;if Z clear
    cmp r3, r2
    BNE ASM_Fail

;str ldr test
    ALIGN
    ldr r1, =0x5aa56789            ;R1 = 0x5aa56789
    str r1, [r0,#0]                ;将R1中的数据写入R0 + 0 的地址的存储器中
    ldr r2, [r0,#0]                ;将R0 + 0地址中的数据给R2
    cmp r2, r1
    bne ASM_Fail

    ALIGN
    ldr r1, =0x3344                ;R1 = 0x3344
    movs r2, #0                    ;R2 = 0
    strh r1, [r0,#0]               ;将R1中的数据写入R0 + 0 的地址的存储器中
    ldrh r2, [r0,#0]               ;将R0 + 0地址中的数据给R2
    cmp r2, r1
    bne ASM_Fail
    
    ALIGN
    ldr r1, =0x88                  ;R1 = 0x88
    movs r2, #0
    strb r1, [r0,#0]
    ldrb r2, [r0,#0]
    cmp r2, r1
    bne ASM_Fail
    
;ands test
    ALIGN
    ldr r1, =0xFFFFFFFF            ;R1 = 0xFFFFFFFF
    ldr r2, =0xFFFFFFFF            ;R2 = 0xFFFFFFFF
    ands r1, r2                    ;R1 = R1 & R2
    BPL ASM_Fail        ;if N clear
    BEQ ASM_Fail        ;if Z set
    cmp r1, r2
    BNE ASM_Fail
    
    movs r1, #0                    ;R1 = 0
    ands r1, r2                    ;R1 = R1 & R2 = 0 & 0xFFFFFFFF = 0
    BMI ASM_Fail        ;if N set
    BNE ASM_Fail        ;if Z clear
    cmp r1, #0
    BNE ASM_Fail
    
;rors test
    movs r3, #1                    ;R3 = 1
    mov r1, r2                     ;R1 = R2 = 0xFFFFFFFF
    rors r2, r3                    ;R2向右移1位，移出的位补到最高位,R2 = 0xFFFFFFFF
    BEQ ASM_Fail        ;if Z set
    BPL ASM_Fail        ;if N clear
    cmp r1, r2
    BNE ASM_Fail
    
    ALIGN
    ldr r2, =0x80000000            ;R2 = 0x80000000
    movs r1, #1                    ;R1 = 1
    rors r1, r3                    ;R1向右移1位，移出的位补到最高位,R1 = 0x80000000
    BEQ ASM_Fail        ;if Z set
    BPL ASM_Fail        ;if N clear
    cmp r1, r2
    BNE ASM_Fail
    
    ALIGN
    ldr r2, =0x40000000            ;R2 = 0x40000000
    rors r1, r3                    ;R1向右移1位，移出的位补到最高位,R1 = 0x04000000
    BEQ ASM_Fail        ;if Z set
    BMI ASM_Fail        ;if N set
    cmp r1, r2
    BNE ASM_Fail
    
ASM_Pass
    movs r0, #0xCC
    b ASM_End

ASM_Fail
    movs r0, #0xDD

ASM_End
    bx lr
    ENDP        
        
        
    END
        