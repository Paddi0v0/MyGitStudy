    AREA    |.text|, CODE, READONLY
    THUMB


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   ram addr test
;   Cycles: 
;   Parameters:
;       no parameters
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;ram_addr_test 函数功能描述
;1、将RAM地址0x20000000的值先保存在R2,然后对该地址分别写0x00000000，0x55555555，0xAAAAAAAA,0xFFFFFFFF,
;   再用R3读出做比较，不相等则测试失败，检测该地址存储数据是否正常，
;   最后复原0x20000000地址的数据。
;
;2、将RAM地址0x20001555的值先保存在R2,然后对该地址分别写0x00，0x55，0xAA，0xFF，
;   再用R3读出做比较，不相等则测试失败，检测该地址存储数据是否正常，
;   最后复原0x20001555地址的数据。
;
;3、将RAM地址0x20001FFF的值先保存在R2,然后对该地址分别写0x00，0x55，0xAA，0xFF，
;   再用R3读出做比较，不相等则测试失败，检测该地址存储数据是否正常，
;   最后复原0x20001FFF地址的数据。
;
;4、将RAM地址0x20000AAA的值先保存在R2,然后对该地址分别写0x0000，0x5555，0xAAAA，0xFFFF，
;   再用R3读出做比较，不相等则测试失败，检测该地址存储数据是否正常，
;   最后复原0x20000AAA地址的数据。

ram_addr_test PROC
    EXPORT ram_addr_test
    ; r0 addr, r1, data
    ldr r0, =0x20000000              ;R0 = 0x20000000
    ldr r2, [r0, #0]                 ;将R0 + 0地址中的数据给R2，保存数据，后面复原使用
    ldr r1, =0x00000000              ;R1 = 0x00000000
    str r1, [r0, #0]                 ;将R1中的数据写入R0 + 0 的地址的存储器中
    ldr r3, [r0, #0]                 ;将R0 + 0地址中的数据给R3
    cmp r1, r3                       ;比较R1和R3，不相等测试fail
    bne ram_addr_fail
    ldr r1, =0x55555555              ;R1 = 0x55555555
    str r1, [r0, #0]                 ;将R1中的数据写入R0 + 0 的地址的存储器中
    ldr r3, [r0, #0]                 ;将R0 + 0地址中的数据给R3
    cmp r1, r3                       ;比较R1和R3，不相等测试fail
    bne ram_addr_fail
    ldr r1, =0xAAAAAAAA              ;R1 = 0xAAAAAAAA
    str r1, [r0, #0]                 ;将R1中的数据写入R0 + 0 的地址的存储器中
    ldr r3, [r0, #0]                 ;将R0 + 0地址中的数据给R3
    cmp r1, r3                       ;比较R1和R3，不相等测试fail
    bne ram_addr_fail
    ldr r1, =0xFFFFFFFF              ;R1 = 0xFFFFFFFF
    str r1, [r0, #0]                 ;将R1中的数据写入R0 + 0 的地址的存储器中      
    ldr r3, [r0, #0]                 ;将R0 + 0地址中的数据给R3
    cmp r1, r3                       ;比较R1和R3，不相等测试fail
    bne ram_addr_fail
    ;restore ram 
    str r2, [r0, #0]                 ;将R2中的数据写入R0 + 0 的地址的存储器中,复原0x20000000地址的数据 
    
    ldr r0, =0x20001555              ;R0 = 0x20001555
    ldrb r2, [r0, #0]                ;将R0 + 0地址中的数据给R2
    ldr r1, =0x00                    ;R1 = 0x00
    movs r1, #0                      ;R1 = 0
    movs r3, #0                      ;R3 = 0
    strb r1, [r0, #0]                ;将R1中的数据写入R0 + 0 的地址的存储器中 
    ldrb r3, [r0, #0]                ;将R0 + 0地址中的数据给R3
    cmp r1, r3                       ;比较R1和R3，不相等测试fail
    bne ram_addr_fail
    ldr r1, =0x55                    ;R1 = 0x55
    strb r1, [r0, #0]                ;将R1中的数据写入R0 + 0 的地址的存储器中 
    ldrb r3, [r0, #0]                ;将R0 + 0地址中的数据给R3
    cmp r1, r3                       ;比较R1和R3，不相等测试fail
    bne ram_addr_fail
    ldr r1, =0xAA                    ;R1 = 0xAA
    strb r1, [r0, #0]
    ldrb r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ldr r1, =0xFF                    ;R1 = 0xFF
    strb r1, [r0, #0]
    ldrb r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ;restore ram 
    strb r2, [r0, #0]                ;将R2中的数据写入R0 + 0 的地址的存储器中,复原0x20001555地址的数据    
        
    ldr r0, =0x20001FFF
    ldrb r2, [r0, #0]
    ldr r1, =0x00
    strb r1, [r0, #0]
    ldrb r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ldr r1, =0x55
    strb r1, [r0, #0]
    ldrb r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ldr r1, =0xAA
    strb r1, [r0, #0]
    ldrb r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ldr r1, =0xFF
    strb r1, [r0, #0]
    ldrb r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ;restore ram 
    strb r2, [r0, #0]
    
    ldr r0, =0x20000AAA
    ldrh r2, [r0, #0]
    ldr r1, =0x0000
    strh r1, [r0, #0]
    ldrh r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ldr r1, =0x5555
    strh r1, [r0, #0]
    ldrh r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ldr r1, =0xAAAA
    strh r1, [r0, #0]
    ldrh r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ldr r1, =0xFFFF
    strh r1, [r0, #0]
    ldrh r3, [r0, #0]
    cmp r1, r3
    bne ram_addr_fail
    ;restore ram 
    strh r2, [r0, #0]

    
ram_addr_pass
    movs r0, #0xCC
    b ram_addr_end

ram_addr_fail
    ;restore ram 
    str r2, [r0, #0]
    movs r0, #0xDD

ram_addr_end
    bx lr
    ENDP
        
        
    DCB 0x00
    DCB 0x00
    END
        