    AREA    |.text|, CODE, READONLY
    THUMB



;  Rx_0scan 功能描述
;  将Rx翻转到 0xFFFFFFFF,0xFFFFFFFE
;             0x7FFFFFFF,0xBFFFFFFF,0xDFFFFFFF,0xEFFFFFFF
;             0xF7FFFFFF,0xFBFFFFFF,0xFDFFFFFF,0xFEFFFFFF
;             0xFF7FFFFF,0xFFBFFFFF,0xFFDFFFFF,0xFFEFFFFF
;             ......    ,......    ,......    ,......
;             0xFFFFFFF7,0xFFFFFFFB,0xFFFFFFFD,循环结束
;   实现将Rx寄存器逐位有0变1的目的，检测寄存器各个位是否正常从0变1

r0_0scan PROC
    EXPORT r0_0scan

    PUSH   {R1,R4}

;0xFFFFFFFF assign
    MOVS   R4, #0            ;R4 = 0 
    MVNS   R2, R4            ;R4的值取反后赋给R2,R2 = 0xFFFFFFFF
    MOV    R0, R2            ;R0 = R2 = 0xFFFFFFFF
    CMP    R0, R2            ;比较R0和R2，如果不相等R0检测fail
    BNE    R0_0ScanFail
    
    MOVS   R4, #1            ;R4 = 1                  
    MVNS   R2, R4            ;R4取反后赋值给R2,R2 = 0xFFFFFFFE
    MVNS   R3, R4            ;R4 = R3 = 0xFFFFFFFE         

R0_0ScanStart

;0 assignment
    MOV    R0, R2            ;R0 = R2 = 0xFFFFFFFE
    CMP    R0, R2
    BNE    R0_0ScanFail
    

    RORS   R2, R4            ;R2向右移1位，R2 = 0x7FFFFFF
    CMP    R2, R3            ;比较R2和R3，不相同执行R0_0ScanStart                  
    BNE    R0_0ScanStart         

; R1 check
    MOV    R2, R1            ;测试相邻两个寄存器是否受影响
    POP   {R1, R4}                            
    CMP    R1, R2            
    BNE    R0_0ScanFail
    
R0_0ScanPass                 
    MOVS   R0, #0xCC
    B      R0_1ScanEnd      
    
R0_0ScanFail                              
    MOVS   R0, #0xDD       
    
R0_0ScanEnd
    
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R0
;   Cycles: 
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;  rx_1scan 功能描述
;  将Rx翻转到 0x00000000
;             0x80000000,0x40000000,0x20000000,0x10000000
;             0x08000000,0x04000000,0x02000000,0x01000000
;             0x00800000,0x00400000,0x00200000,0x00100000
;             ......    ,......    ,......    ,......
;             0x00000008,0x00000004,0x00000002,0x00000001,循环结束
;   实现将Rx寄存器逐位有1变0的目的，检测寄存器各个位是否正常从1变0
r0_1scan PROC
    EXPORT r0_1scan

    PUSH   {R1,R4}

;0x0000000
    MOVS   R4, #0            ;R4 = 0
    MOV    R0, R4            ;R0 = R4 = 0
    CMP    R0, R4            ;比较R0和R4，不相等则fail         
    BNE    R0_1ScanFail
    
    MOVS   R4, #1            ;R4 = 1                  
    LSLS   R4, R4, #31       ;R4向左移31位，R4 = 0x8000000

R0_1ScanStart
;1 assignment
    MOV    R0, R4
    CMP    R0, R4                  
    BNE    R0_1ScanFail

    LSRS   R4, R4, #1      
    CMP    R4, #0                              
    BNE    R0_1ScanStart         

; R1 check
    MOV    R2, R1            ;R2 = R1
    POP   {R1, R4}
    CMP    R1, R2
    BNE    R0_1ScanFail
    
R0_1ScanPass                 
    MOVS   R0, #0xCC
    B      R0_1ScanEnd      
    
R0_1ScanFail                              
    MOVS   R0, #0xDD       
    
R0_1ScanEnd
    BX     LR
    ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg scan: APSR
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
APSR_scan PROC
    EXPORT APSR_scan

    PUSH   {R0,R1,R2}
    MRS    R0,APSR
	
;clr APSR 
    MOVS   R1, #0               ;               
	MSR    APSR,R1
	MRS    R2,APSR
    CMP    R1, R2
    BNE    APSR_ScanFail


;set APSR 0101
    MOVS   R1, #5               ;                   
    LSLS   R1, R1, #28          ;  R1向左移28位
	MSR    APSR,R1
	MRS    R2,APSR
    CMP    R1, R2
    BNE    APSR_ScanFail

;set APSR 1010
    MOVS   R1, #0xa               ;R1赋值为1                   
    LSLS   R1, R1, #28            ;R1 = 0x8000       R1向左移28位
	MSR    APSR,R1
	MRS    R2,APSR
    CMP    R1, R2
    BNE    APSR_ScanFail
	
;Recover APSR
    MSR    APSR,R0
	MRS    R2,APSR
    CMP    R0, R2
	BNE    APSR_ScanFail
	
    POP    {R0,R1,R2}

APSR_ScanPass                 
    MOVS   R0, #0xCC
    B      APSR_ScanEnd      
    
APSR_ScanFail                              
    MOVS   R0, #0xDD       
    
APSR_ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg scan: PRIMASK
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PRIMASK_scan PROC
    EXPORT PRIMASK_scan

    PUSH   {R0,R1,R2}
    MRS    R0,PRIMASK
	
;clr PRIMASK
    MOVS   R1, #0               ;               
	MSR    PRIMASK,R1
	MRS    R2,PRIMASK
    CMP    R1, R2
    BNE    PRIMASK_ScanFail


;set PRIMASK 0101
    MOVS   R1, #1               ;    
	MSR    PRIMASK,R1
	MRS    R2,PRIMASK
    CMP    R1, R2
    BNE    PRIMASK_ScanFail


    MSR    PRIMASK,R0
    POP    {R0,R1,R2}

PRIMASK_ScanPass                 
    MOVS   R0, #0xCC
    B      PRIMASK_ScanEnd      
    
PRIMASK_ScanFail                              
    MOVS   R0, #0xDD       
    
PRIMASK_ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R1
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r1_0scan PROC
    EXPORT r1_0scan

    PUSH   {R0,R2,R4,R5}

;0xFFFFFFFF
    MOVS   R4, #0                            
    MVNS   R5, R4
    MOV    R1, R5
    CMP    R1, R5
    BNE    R1_0ScanFail

    MOVS   R4, #1                            
    MVNS   R5, R4
    MVNS   R3, R4

R1_0ScanStart
;0 assignment
    MOV    R1, R5
    CMP    R1, R5
    BNE    R1_0ScanFail
    
    RORS   R5, R4       
    CMP    R5, R3                              
    BNE    R1_0ScanStart         

;R0 R2 check
    MOV     R1, R0
    MOV     R3, R2
    POP    {R0,R2,R4,R5}
    CMP     R0,R1
    BNE    R1_0ScanFail
    CMP     R2,R3
    BNE    R1_0ScanFail

R1_0ScanPass                 
    MOVS   R0, #0xCC
    B      R1_0ScanEnd      
    
R1_0ScanFail                              
    MOVS   R0, #0xDD       
    
R1_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R1
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r1_1scan PROC
    EXPORT r1_1scan

    PUSH   {R0,R2}

;0x00000000
    MOVS   R3, #0
    MOV    R1, R3
    CMP    R1, R3                  
    BNE    R1_1ScanFail

    MOVS   R3, #1                            
    LSLS   R3, R3, #31       

R1_1ScanStart
;1 assignment
    MOV    R1, R3
    CMP    R1, R3                  
    BNE    R1_1ScanFail

    LSRS   R3, R3, #1        
    CMP    R3, #0                              
    BNE    R1_1ScanStart  

;R0 R2 check
    MOV     R1, R0
    MOV     R3, R2
    POP    {R0,R2}
    CMP     R0,R1
    BNE    R1_1ScanFail
    CMP     R2,R3
    BNE    R1_1ScanFail

R1_1ScanPass                 
    MOVS   R0, #0xCC
    B      R1_1ScanEnd      
    
R1_1ScanFail                              
    MOVS   R0, #0xDD       
    
R1_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R2
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r2_0scan PROC
    EXPORT r2_0scan
    
    PUSH   {R1,R3,R4,R5}

;0xFFFFFFFF
    MOVS   R0, #0                            
    MVNS   R4, R0
    MOV    R2, R4
    CMP    R2, R4
    BNE    R2_0ScanFail

    MOVS   R0, #1                            
    MVNS   R4, R0
    MVNS   R5, R0

R2_0ScanStart
;0 assignment
    MOV    R2, R4
    CMP    R2, R4
    BNE    R2_0ScanFail
    
    RORS   R4, R0      
    CMP    R4, R5                             
    BNE    R2_0ScanStart         

; R1 R3 check
    MOV     R0,R1
    MOV     R2,R3
    POP     {R1,R3,R4,R5}
    CMP     R0,R1
    BNE     R2_0ScanFail
    CMP     R2,R3
    BNE     R2_0ScanFail

R2_0ScanPass                 
    MOVS   R0, #0xCC
    B      R2_0ScanEnd      
    
R2_0ScanFail                              
    MOVS   R0, #0xDD       
    
R2_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R2
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r2_1scan PROC
    EXPORT r2_1scan
    
    PUSH   {R1,R3}

;0x00000000
    MOVS   R0, #0
    MOV    R2, R0
    CMP    R2, R0                  
    BNE    R2_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R2_1ScanStart
;1 assignment
    MOV    R2, R0
    CMP    R2, R0                  
    BNE    R2_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R2_1ScanStart         

; R1 R3 check
    MOV     R0,R1
    MOV     R2,R3
    POP     {R1,R3}
    CMP     R0,R1
    BNE     R2_0ScanFail
    CMP     R2,R3
    BNE     R2_0ScanFail

R2_1ScanPass                 
    MOVS   R0, #0xCC
    B      R2_1ScanEnd      
    
R2_1ScanFail                              
    MOVS   R0, #0xDD       
    
R2_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R3
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r3_0scan PROC
    EXPORT r3_0scan

    PUSH   {R2,R4,R5}
;0xFFFFFFFF
    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R3, R1
    CMP    R3, R1
    BNE    R3_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R5, R0

R3_0ScanStart
;0 assignment
    MOV    R3, R1
    CMP    R3, R1
    BNE    R3_0ScanFail
    
    RORS   R1, R0       
    CMP    R1, R5                              
    BNE    R3_0ScanStart   

; R2 R4 check
    MOV     R0, R2
    MOV     R1, R4
    POP     {R2,R4,R5}
    CMP     R0, R2
    BNE     R3_0ScanFail
    CMP     R1, R4
    BNE     R3_0ScanFail

R3_0ScanPass                 
    MOVS   R0, #0xCC
    B      R3_0ScanEnd      
    
R3_0ScanFail                              
    MOVS   R0, #0xDD       
    
R3_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R3
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r3_1scan PROC
    EXPORT r3_1scan

    PUSH   {R2,R4}

;0x00000000
    MOVS   R0, #0
    MOV    R3, R0
    CMP    R3, R0                  
    BNE    R3_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R3_1ScanStart
;1 assignment
    MOV    R3, R0
    CMP    R3, R0                  
    BNE    R3_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R3_1ScanStart         

; R2 R4 check
    MOV     R0, R2
    MOV     R1, R4
    POP     {R2,R4}
    CMP     R0, R2
    BNE     R3_1ScanFail
    CMP     R1, R4
    BNE     R3_1ScanFail

R3_1ScanPass                 
    MOVS   R0, #0xCC
    B      R3_1ScanEnd      
    
R3_1ScanFail                              
    MOVS   R0, #0xDD       
    
R3_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R4
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r4_0scan PROC
    EXPORT r4_0scan

    PUSH   {R3,R4,R5}

;0xFFFFFFFF
    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R4, R1
    CMP    R4, R1
    BNE    R4_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R4_0ScanStart
;0 assignment
    MOV    R4, R1
    CMP    R4, R1
    BNE    R4_0ScanFail
    
    RORS   R1, R0       
    CMP    R1, R2                              
    BNE    R4_0ScanStart         

; R3 R5 check
    MOV     R0, R3
    MOV     R1, R5
    POP     {R3,R4,R5}
    CMP     R0,R3
    BNE     R4_0ScanFail
    CMP     R1,R5
    BNE     R4_0ScanFail

R4_0ScanPass                 
    MOVS   R0, #0xCC
    B      R4_0ScanEnd      
    
R4_0ScanFail                              
    MOVS   R0, #0xDD       
    
R4_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R4
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r4_1scan PROC
    EXPORT r4_1scan

    PUSH    {R3,R4,R5}
    
;0x00000000
    MOVS   R0, #0
    MOV    R4, R0
    CMP    R4, R0                  
    BNE    R4_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R4_1ScanStart
;1 assignment
    MOV    R4, R0
    CMP    R4, R0                  
    BNE    R4_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R4_1ScanStart         

; R3 R5 check
    MOV     R0, R3
    MOV     R1, R5
    POP     {R3,R4,R5}
    CMP     R0,R3
    BNE     R4_1ScanFail
    CMP     R1,R5
    BNE     R4_1ScanFail

R4_1ScanPass                 
    MOVS   R0, #0xCC
    B      R4_1ScanEnd      
    
R4_1ScanFail                              
    MOVS   R0, #0xDD       
    
R4_1ScanEnd
    BX     LR
    ENDP




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R5
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r5_0scan PROC
    EXPORT r5_0scan

    MOV     R3, R6
    PUSH    {R4,R5}
;0xFFFFFFFF
    MOVS   R0, #0                          
    MVNS   R1, R0
    MOV    R5, R1
    CMP    R5, R1
    BNE    R5_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R5_0ScanStart
;0 assignment
    MOV    R5, R1
    CMP    R5, R1
    BNE    R5_0ScanFail
    
    RORS   R1, R0        
    CMP    R1, R2                             
    BNE    R5_0ScanStart         

; R4 R6 check
    MOV     R0, R4
    POP     {R4,R5}
    CMP     R0, R4
    BNE     R5_0ScanFail
    CMP     R3, R6
    BNE     R5_0ScanFail

R5_0ScanPass                 
    MOVS   R0, #0xCC
    B      R5_0ScanEnd      
    
R5_0ScanFail                              
    MOVS   R0, #0xDD       
    
R5_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R5
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r5_1scan PROC
    EXPORT r5_1scan

    MOV R1, R4
    MOV R2, R5
    MOV R3, R6

;0x00000000
    MOVS   R0, #0
    MOV    R5, R0
    CMP    R5, R0                  
    BNE    R5_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R5_1ScanStart
;1 assignment
    MOV    R5, R0
    CMP    R5, R0                  
    BNE    R5_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R5_1ScanStart         

; R4 R6 check
    MOV     R5, R2
    CMP     R1, R4
    BNE     R5_1ScanFail
    CMP     R3, R6
    BNE     R5_1ScanFail
    
R5_1ScanPass                 
    MOVS   R0, #0xCC
    B      R5_1ScanEnd      
    
R5_1ScanFail                              
    MOVS   R0, #0xDD       
    
R5_1ScanEnd
    BX     LR
    ENDP



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R6
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r6_0scan PROC
    EXPORT r6_0scan

    MOV     R3, R7
    PUSH    {R5,R6}
;0x00000000
    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R6, R1
    CMP    R6, R1
    BNE    R6_0ScanFailPop

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R6_0ScanStart
;0 assignment
    MOV    R6, R1
;	MOVS   R6, #8       ;ERROR injection
    CMP    R6, R1
    BNE    R6_0ScanFailPop
    
    RORS   R1, R0        
    CMP    R1, R2                              
    BNE    R6_0ScanStart         

; R5 R7 check
    MOV     R0, R5
    POP     {R5, R6}
    CMP     R0, R5
    BNE     R6_0ScanFail
    CMP     R3, R7
    BNE     R6_0ScanFail

R6_0ScanPass                 
    MOVS   R0, #0xCC
    B      R6_0ScanEnd      

R6_0ScanFailPop
    POP {R5,R6}  

R6_0ScanFail                              
    MOVS   R0, #0xDD       
    
R6_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R6
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r6_1scan PROC
    EXPORT r6_1scan

    MOV     R1, R5
    MOV     R2, R6
    MOV     R3, R7
;0x00000000
    MOVS   R0, #0                            
    MOV    R6, R0
    CMP    R6, R0                  
    BNE    R6_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R6_1ScanStart
;1 assignment
    MOV    R6, R0
    CMP    R6, R0                  
    BNE    R6_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R6_1ScanStart         

; R5 R7 check
    MOV     R6, R2
    CMP     R1, R5
    BNE     R6_1ScanFail
    CMP     R3, R7
    BNE     R6_1ScanFail

R6_1ScanPass                 
    MOVS   R0, #0xCC
    B      R6_1ScanEnd      
    
R6_1ScanFail                              
    MOVS   R0, #0xDD       
    
R6_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R7
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r7_0scan PROC
    EXPORT r7_0scan

    PUSH    {R6,R7}
    MOV     R3, R8
;0xFFFFFFFF
    MOVS   R0, #0                           
    MVNS   R1, R0
    MOV    R7, R1
    CMP    R7, R1
    BNE    R7_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R7_0ScanStart
;0 assignment
    MOV    R7, R1
    CMP    R7, R1
    BNE    R7_0ScanFail
    
    RORS   R1, R0        
    CMP    R1, R2                              
    BNE    R7_0ScanStart         

; R6 R8 check
    MOV     R0, R6
    POP     {R6,R7}
    CMP     R0, R6
    BNE     R7_0ScanFail
    CMP     R3, R8
    BNE     R7_0ScanFail

R7_0ScanPass                 
    MOVS   R0, #0xCC
    B      R7_0ScanEnd      
    
R7_0ScanFail                              
    MOVS   R0, #0xDD       
    
R7_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R7
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r7_1scan PROC
    EXPORT r7_1scan

    MOV     R1, R6
    MOV     R2, R7
    MOV     R3, R8
;0x00000000
    MOVS   R0, #0                            
    MOV    R7, R0
    CMP    R7, R0                  
    BNE    R7_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R7_1ScanStart
;1 assignment
    MOV    R7, R0
    CMP    R7, R0                  
    BNE    R7_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R7_1ScanStart         

; R6 R8 check
    MOV     R7, R2
    CMP     R1, R6
    BNE     R7_1ScanFail
    CMP     R3, R8
    BNE     R7_1ScanFail
    
R7_1ScanPass                 
    MOVS   R0, #0xCC
    B      R7_1ScanEnd      
    
R7_1ScanFail                              
    MOVS   R0, #0xDD       
    
R7_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R8
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r8_0scan PROC
    EXPORT r8_0scan

    MOV     R0, R8
    MOV     R1, R9
    MOV     R3, R7
    PUSH    {R0,R1}
;0xFFFFFFFF
    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R8, R1
    CMP    R8, R1
    BNE    R8_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R8_0ScanStart
;0 assignment
    MOV    R8, R1
    CMP    R8, R1
    BNE    R8_0ScanFail
    
    RORS   R1, R0        
    CMP    R1, R2                              
    BNE    R8_0ScanStart         

; R7 R9 check
    POP     {R0,R1}
    MOV     R8, R0
    CMP     R3, R7
    BNE     R8_0ScanFail
    CMP     R1, R9
    BNE     R8_0ScanFail

R8_0ScanPass                 
    MOVS   R0, #0xCC
    B      R8_0ScanEnd      
    
R8_0ScanFail                              
    MOVS   R0, #0xDD       
    
R8_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R8
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r8_1scan PROC
    EXPORT r8_1scan

    MOV     R1, R7
    MOV     R2, R8
    MOV     R3, R9
;0x00000000
    MOVS   R0, #0                            
    MOV    R8, R0
    CMP    R8, R0                  
    BNE    R8_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R8_1ScanStart
;1 assignment
    MOV    R8, R0
    CMP    R8, R0                  
    BNE    R8_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R8_1ScanStart         

; R7 R9 check
    MOV     R8, R2        ;recover R8
    CMP     R1, R7
    BNE     R8_1ScanFail
    CMP     R3, R9
    BNE     R8_1ScanFail

R8_1ScanPass                 
    MOVS   R0, #0xCC
    B      R8_1ScanEnd      
    
R8_1ScanFail                              
    MOVS   R0, #0xDD       
    
R8_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R9
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r9_0scan PROC
    EXPORT r9_0scan

    MOV     R0, R8
    MOV     R1, R9
    MOV     R3, R10
    PUSH    {R0,R1}
;0xFFFFFFFF
    MOVS   R0, #0                           
    MVNS   R1, R0
    MOV    R9, R1
    CMP    R9, R1
    BNE    R9_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R9_0ScanStart
;0 scan
    MOV    R9, R1
    CMP    R9, R1
    BNE    R9_0ScanFail
    
    RORS   R1, R0       
    CMP    R1, R2                              
    BNE    R9_0ScanStart         

; R8 R10 check
    POP     {R0,R1}
    MOV     R9, R1  ;Recover R9
    CMP     R0, R8
    BNE     R9_0ScanFail
    CMP     R3, R10
    BNE     R9_0ScanFail

R9_0ScanPass                 
    MOVS   R0, #0xCC
    B      R9_0ScanEnd      
    
R9_0ScanFail                              
    MOVS   R0, #0xDD       
    
R9_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R9
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r9_1scan PROC
    EXPORT r9_1scan

    MOV     R1, R8
    MOV     R2, R9
    MOV     R3, R10
;0x00000000
    MOVS   R0, #0                            
    MOV    R9, R0
    CMP    R9, R0                  
    BNE    R9_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R9_1ScanStart
;1 scan
    MOV    R9, R0
    CMP    R9, R0                  
    BNE    R9_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R9_1ScanStart         

; R8 R10 check
    MOV     R9, R2  ;Recover R9
    CMP     R1, R8
    BNE     R9_1ScanFail
    CMP     R3, R10
    BNE     R9_1ScanFail

R9_1ScanPass                 
    MOVS   R0, #0xCC
    B      R9_1ScanEnd      
    
R9_1ScanFail                              
    MOVS   R0, #0xDD       
    
R9_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R10
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r10_0scan PROC
    EXPORT r10_0scan

    MOV     R1, R9
    MOV     R2, R10
    MOV     R3, R11 
    PUSH    {R1,R2}
;0xFFFFFFFF
    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R10, R1
    CMP    R10, R1
    BNE    R10_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R10_0ScanStart
;0 scan
    MOV    R10, R1
    CMP    R10, R1
    BNE    R10_0ScanFail
    
    RORS   R1, R0        
    CMP    R1, R2                              
    BNE    R10_0ScanStart         

; R9 R11 check
    POP     {R1,R2}
    MOV     R10, R2     ;Recover R10
    CMP     R1, R9
    BNE     R10_0ScanFail
    CMP     R3, R11
    BNE     R10_0ScanFail

R10_0ScanPass                 
    MOVS   R0, #0xCC
    B      R10_0ScanEnd      
    
R10_0ScanFail                              
    MOVS   R0, #0xDD       
    
R10_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R10
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r10_1scan PROC
    EXPORT r10_1scan

    MOV     R1, R9
    MOV     R2, R10
    MOV     R3, R11
;0x00000000
    MOVS   R0, #0                            
    MOV    R10, R0
    CMP    R10, R0                  
    BNE    R10_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R10_1ScanStart
;1 scan
    MOV    R10, R0
    CMP    R10, R0                  
    BNE    R10_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R10_1ScanStart         

;R9 R11 check
    MOV     R10, R2     ;Recover R10
    CMP     R1, R9
    BNE     R10_1ScanFail
    CMP     R3, R11
    BNE     R10_1ScanFail

R10_1ScanPass                 
    MOVS   R0, #0xCC
    B      R10_1ScanEnd      
    
R10_1ScanFail                              
    MOVS   R0, #0xDD       
    
R10_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R11
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r11_0scan PROC
    EXPORT r11_0scan

    MOV     R1, R10
    MOV     R2, R11
    MOV     R3, R12
    PUSH    {R1,R2}

    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R11, R1
    CMP    R11, R1
    BNE    R11_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R11_0ScanStart
;0 scan
    MOV    R11, R1
    CMP    R11, R1
    BNE    R11_0ScanFail
    
    RORS   R1, R0        
    CMP    R1, R2                              
    BNE    R11_0ScanStart         

; R10 R12 check
    POP     {R1,R2}
    MOV     R11, R2     ;Recover R11
    CMP     R1, R10
    BNE     R11_0ScanFail
    CMP     R3, R12
    BNE     R11_0ScanFail

R11_0ScanPass                 
    MOVS   R0, #0xCC
    B      R11_0ScanEnd      
    
R11_0ScanFail                              
    MOVS   R0, #0xDD       
    
R11_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R11
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r11_1scan PROC
    EXPORT r11_1scan

    MOV     R1, R10
    MOV     R2, R11
    MOV     R3, R12
;0x00000000
    MOVS   R0, #0                            
    MOV    R11, R0
    CMP    R11, R0                  
    BNE    R11_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R11_1ScanStart
;1 scan
    MOV    R11, R0
    CMP    R11, R0                  
    BNE    R11_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R11_1ScanStart         

; R10 R12 check
    MOV     R11, R2     ;Recoveer R11
    CMP     R1, R10
    BNE     R11_1ScanFail
    CMP     R3, R12
    BNE     R11_1ScanFail

R11_1ScanPass                 
    MOVS   R0, #0xCC
    B      R11_1ScanEnd      
    
R11_1ScanFail                              
    MOVS   R0, #0xDD       
    
R11_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R12
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r12_0scan PROC
    EXPORT r12_0scan

    MOV     R1, R11
    MOV     R2, R12
    MOV     R3, R13
    PUSH    {R1,R2}
;0xFFFFFFFF
    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R12, R1
    CMP    R12, R1
    BNE    R12_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R12_0ScanStart
;0 scan
    MOV    R12, R1
    CMP    R12, R1
    BNE    R12_0ScanFail
    
    RORS   R1, R0        
    CMP    R1, R2                              
    BNE    R12_0ScanStart         

; R11 R13 check
    POP     {R1,R2}
    MOV     R12, R2     ;Recover R12
    CMP     R11, R1
    BNE     R12_0ScanFail
    CMP     R13, R3
    BNE     R12_0ScanFail

R12_0ScanPass                 
    MOVS   R0, #0xCC
    B      R12_0ScanEnd      
    
R12_0ScanFail                              
    MOVS   R0, #0xDD       
    
R12_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R12
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r12_1scan PROC
    EXPORT r12_1scan

    MOV     R1, R11
    MOV     R2, R12
    MOV     R3, R13
;0x00000000
    MOVS   R0, #0                            
    MOV    R12, R0
    CMP    R12, R0                  
    BNE    R12_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R12_1ScanStart
;1 scan
    MOV    R12, R0
    CMP    R12, R0                  
    BNE    R12_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R12_1ScanStart         

;R11 R13 check
    MOV     R12, R2     ;Recover R12
    CMP     R11, R1
    BNE     R12_1ScanFail
    CMP     R13, R3
    BNE     R12_1ScanFail

R12_1ScanPass                 
    MOVS   R0, #0xCC
    B      R12_1ScanEnd      
    
R12_1ScanFail                              
    MOVS   R0, #0xDD       
    
R12_1ScanEnd
    BX     LR
    ENDP



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R13
;   Attention! R13 is SP, so push/pop carefully
;   R13's lower 2bit are constant zero
;   Cycles: 
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r13_0scan PROC
    EXPORT r13_0scan

    MOV     R0, R12
    MOV     R2, R14
    PUSH   {R0,R2,R4}
    MOV     R4, R13

;0xFFFFFF00
    MOVS   R0, #0
    MVNS   R1, R0
    LSLS   R2, R1, #2
    MOV    R13, R2
    CMP    R13, R2
    BNE    R13_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    LSLS   R0, #2
    MVNS   R2, R0                                  
    MOVS   R0, #1 
R13_0ScanStart
;0 scan
    MOV    R13, R1
    ;clear the lower two bits of R0 since SP is always multiple of 4
    ;BIC    R1, R0, #%11
    LSRS   R3, R1, #2
    LSLS   R3, #2
    CMP    R13, R3
    BNE    R13_0ScanFail
    
    RORS   R1, R0
    CMP    R1, R2                                
    BNE    R13_0ScanStart         

;R12 R14 check
    MOV     R13, R4
    POP     {R0,R2,R4}
    CMP     R12, R0
    BNE     R13_0ScanFail
    CMP     R14, R2 
    BNE     R13_0ScanFail

R13_0ScanPass                 
    MOVS   R0, #0xCC
    B      R13_0ScanEnd      
    
R13_0ScanFail                              
    MOVS   R0, #0xDD       
    
R13_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R13
;   Attention! R13 is SP, so push/pop carefully
;   Cycles: 
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r13_1scan PROC
    EXPORT r13_1scan

    PUSH   {R4}
    MOV    R1, R12
    MOV    R2, R14
    MOV    R4, R13     ; saves SP

;0x00000000
    MOVS   R0, #0
    MOV    R13, R0
    CMP    R13, R0                 
    BNE    R13_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       
    ASRS   R3, R0, #29 ;R3 = 0xFFFFFFFC
    
R13_1ScanStart
;1 scan
    MOV    R13, R0
    CMP    R13, R0                 
    BNE    R13_1ScanFail
    
    LSRS   R0, R0, #1
    CMP    R0, #2                                
    BNE    R13_1ScanStart         

;R12 R14 check
    MOV     R13, R4
    POP    {R4}
    CMP    R12, R1
    BNE    R13_1ScanFail
    CMP    R14, R2
    BNE    R13_1ScanFail

R13_1ScanPass                 
    MOVS   R0, #0xCC
    B      R13_1ScanEnd      
    
R13_1ScanFail                              
    MOVS   R0, #0xDD       
    
R13_1ScanEnd
    BX     LR
    ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 0-scan: R14, R14 is LR
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r14_0scan PROC
    EXPORT r14_0scan

    MOV    R1, R13
    PUSH   {R1}
    MOV    R3, R14

;0xFFFFFFFF
    MOVS   R0, #0                            
    MVNS   R1, R0
    MOV    R14, R1
    CMP    R14, R1
    BNE    R14_0ScanFail

    MOVS   R0, #1                            
    MVNS   R1, R0
    MVNS   R2, R0

R14_0ScanStart
;0 scan
    MOV    R14, R1
    CMP    R14, R1
    BNE    R14_0ScanFail
    
    RORS   R1, R0       
    CMP    R1, R2                              
    BNE    R14_0ScanStart         

; R13 check
    MOV    R14, R3
    POP    {R1}
    CMP     R13, R1
    BNE    R14_0ScanStart         

R14_0ScanPass                 
    MOVS   R0, #0xCC
    B      R14_0ScanEnd      
    
R14_0ScanFail                              
    MOVS   R0, #0xDD       
    
R14_0ScanEnd
    BX     LR
    ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Specific cpu reg 1-scan: R14, R14 is LR
;   Return value:
;       0xCC, Test passed
;       0xDD, Test failed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
r14_1scan PROC
    EXPORT r14_1scan

    MOV    R2, R13
    MOV    R3, R14
;0x00000000
    MOVS   R0, #0
    MOV    R14, R0
    CMP    R14, R0                  
    BNE    R14_1ScanFail

    MOVS   R0, #1                            
    LSLS   R0, R0, #31       

R14_1ScanStart
;1 scan
    MOV    R14, R0
    CMP    R14, R0                  
    BNE    R14_1ScanFail
    
    LSRS   R0, R0, #1        
    CMP    R0, #0                              
    BNE    R14_1ScanStart         
;R13 check
    MOV    R14, R3
    CMP    R13, R2  
    BNE    R14_1ScanFail

R14_1ScanPass                 
    MOVS   R0, #0xCC
    B      R14_1ScanEnd      
    
R14_1ScanFail                              
    MOVS   R0, #0xDD       
    
R14_1ScanEnd
    BX     LR
    ENDP
        
        
        
    END
        