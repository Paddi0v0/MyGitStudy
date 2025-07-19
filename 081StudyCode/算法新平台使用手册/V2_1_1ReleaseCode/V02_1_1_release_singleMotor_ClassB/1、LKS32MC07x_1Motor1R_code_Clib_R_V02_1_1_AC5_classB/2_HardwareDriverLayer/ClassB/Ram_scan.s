    AREA    |.text|, CODE, READONLY
    THUMB


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Occupied Half word Scan
;   Cycles: 338
;   Parameters
;       R0: ram addr, aligned by 2

;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;occupied_halfword_scan函数翻转流程；
;                 0x0000,0xFFFF，
;                 0x8000,0x7FFF,0x4000,0xBFFF,0x2000,0xDFFF,0x1000,0xEFFF
;                 0x0800,0xF7FF,0x0400,0xFBFF,0x0200,0xFDFF,0x0100,0xFEFF
;                 0x0080,0xFF7F,0x0040,0xFFBF,0x0020,0xFFDF,0x0010,0xFFEF
;                 0x0008,0xFFF7,0x0004,0xFFFB,0x0002,0xFFFD,0x0001,0xFFFE
occupied_halfword_scan PROC
    EXPORT occupied_halfword_scan
    PUSH    {R4, R5, R6, R7}
    SUBS    R0, R0, #2           ;R0 = R0 - 2   
    LDRH    R2, [R0, #2]         ;扫描破坏RAM之前先保存RAM中的内容。
    LDRH    R6, [R0, #0]         
    LDRH    R7, [R0, #4]         ;保存检测地址及前2个字节和后2个字节的数据，共6个字节数据
	
    MOVS    R1, #1               ;R1赋值为1                   
    LSLS    R1, R1, #15          ;R1 = 0x8000       R1向左移15位
    MVNS    R5, R1               ;R5 = 0xFFFF7FFF   R5等于R1取反
    LSRS    R5, R5, #16          ;R5 = 0xFFFF       R5等于R5向右移16位   

;0x0000
    MOVS    R3, #0               ;R3 = 0; 
    STRH    R3, [R0, #2]         ;把R3的半字数据赋值给地址R0+2，即被检测的地址
    LDRH    R4, [R0, #2]         ;将R0+2地址的数据赋值给R4，并将R4的高16位清零
    CMP     R4, R3               ;比较R4和R3
    BNE     Halfword_ScanFail    ;如果R4-R3≠0执行 Halfword_ScanFail
;0xFFFF
    STRH    R5, [R0, #2]         ;将R5的半字数据赋值给地址R0+2
    LDRH    R4, [R0, #2]         ;将R0+2地址的数据赋值给R4，并将R4的高16位清零
;	MOVS    R5, #1               ;ERROR injection                                  加入错误
    CMP     R4, R5       
    BNE     Halfword_ScanFail    ;如果R4-R5≠0执行 Halfword_ScanFail

Halfword_ScanStart
;1 scan  逐位由0写1    0x8000,0x4000,0x2000,0x1000
;                      0x0800,0x0400,0x0200,0x0100
;                      0x0080,0x0040,0x0020,0x0010
;                      0x0008,0x0004,0x0002,0x0001

    STRH   R1, [R0, #2]          ;把R1的半字数据赋值给地址R0+2
    LDRH   R3, [R0, #2]          ;将R0+2地址的数据赋值给R3，并将R3的高16位清零
;	MOVS   R3, #1                ;ERROR injection                                  加入错误
    CMP    R1, R3                  
    BNE    Halfword_ScanFail     ;如果R1-R3≠0执行 Halfword_ScanFail

;0 scan 逐位由1写0     0x7FFF,0xBFFF,0xDFFF,0xEFFF
;                      0xF7FF,0xFBFF,0xFDFF,0xFEFF
;                      0xFF7F,0xFFBF,0xFFDF,0xFFEF
;                      0xFFF7,0xFFFB,0xFFFD,0xFFFE

    MVNS   R4, R1                ;R4 = R1,并对R4取反
    ANDS   R4, R5                ;R4 = R4 & R5;
    STRH   R4, [R0, #2]          ;把R4的半字数据赋值给地址R0+2
    LDRH   R3, [R0, #2]          ;将R0+2地址的数据赋值给R3，并将R3的高16位清零
    CMP    R4, R3                  
    BNE    Halfword_ScanFail     ;如果R4-R3≠0执行 Halfword_ScanFail
    
    LSRS   R1, R1, #1            ;R1 = R1 >> 1
    CMP    R1, #0                              
    BNE    Halfword_ScanStart    ;R1 - 0 ≠ 0   执行 Halfword_ScanFail   

;check adjacent contect
    LDRH    R4, [R0, #0]         ;将R0+0地址的数据赋值给R4，并将R4的高16位清零
    LDRH    R5, [R0, #4]         ;将R0+4地址的数据赋值给R5，并将R5的高16位清零
    CMP     R4, R6               ;检测被检测地址前2个字节有没有被修改
    BNE     Halfword_ScanFail    ;如果R4-R6≠0执行 Halfword_ScanFail
    CMP     R5, R7               ;检测被检测地址后2个字节有没有被修改
    BNE     Halfword_ScanFail    ;如果R5-R7≠0执行 Halfword_ScanFail
    
Halfword_ScanPass                 
    MOVS   R1, #0xCC
    B      Halfword_ScanEnd      
    
Halfword_ScanFail                              
    MOVS   R1, #0xDD       
    
Halfword_ScanEnd
    ;Restore ram content
    STRH    R2, [R0, #2]         ;把R2的半字数据赋值给地址R0+2，复原现场
    ;Assign return value
    MOV     R0, R1               ;R0 = R1
    ;Restore variables
    POP    {R4, R5, R6, R7}      ;出栈
    BX LR
    ENDP
       
        
    END
        