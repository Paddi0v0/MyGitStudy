;/*******************************************************************************
; * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
; * 文件名称： MarchC+.s
; * 内容摘要： MarchC+自检代码
; * 其它说明： 无
; * 当前版本： V 1.0
; * 作    者： 李四龙
; * 完成日期： 2022年10月30日
; *******************************************************************************/ 

;March C+算法测试流程
;1、首先是初始化，对整个RAM单元写0，操作的地址顺序为升序或降序。
;2、以地址升序方式读单元，读出每个单元的值并检查是否为0，接着对该单元写1。再读出每个单元的值并检查是否为1。重复这样的操作过程直到所有的单元；
;3、以地址升序的方式读单元检查是否为1，接着对该单元写0，再读出每个单元的值并检查是否为0，重复这样的操作过程直到所有单元。
;4、以地址降序方式读单元，读出每个单元的值并检查是否为0，接着对该单元写1，在读出每个单元的值并检查是否为1，重复这样的操作过程直到所有的单元；
;5、以地址降序的方式读单元检查是否为1，接着对该单元写0，再读出每个单元的值并检查是否为0，重复这样的操作过程直到所有的单元。
;6、以地址降序或升序方式读单元，检查是否为0。

;PS:本代码以2个字节为一个单元
;08x系列为8K RAM，  检测时单元的起始地址为0x20000000，单元的结束地址为0x20001FFE
;05x系列为2.5K RAM，检测时单元的起始地址为0x20000000，单元的结束地址为0x200009FE
;03x系列为4K RAM，  检测时单元的起始地址为0x20000000，单元的结束地址为0x20000FFE
;07x系列为8K RAM，  检测时单元的起始地址为0x20000000，单元的结束地址为0x20002FFE

 AREA    |.text|, CODE, READONLY
    THUMB

RAM_init_test  PROC
  
  EXPORT RAM_init_test
;	IMPORT  __main
;	PUSH    {R1,R2,R3,R4,R5,R6}
    	
	;取R4为RAM初始地址
	MOVS    R0,#1
    LSLS    R0, R0, #29     ;R0 = 0x20000000  	
    MOV     R4,R0           ;R4 = R0,令R4等于RAM开始地址
	
;PS：此处08x、05x、03x、07x略有不同,需要设置不同的结束地址	
	;令R3为RAM结束地址,
    MOVS    R3, #3          ;R3赋值为1                   
    LSLS    R3, R3, #12     ;R3 = 0x3000       R3向左移12位
    SUBS    R3, #2          ;R3 = 0x2FFE
	
    ADD     R3,R0,R3	    ;R3 = 0x20002FFE，令R3等于RAM结束地址	

	;令R5为0xFFFF,用于给单元赋值0xFFFF,并作为单元判断是否为全1的条件
	MOVS    R5, #0 
	MVNS    R5, R5 
	LSRS    R5, R5, #16     ;R5 = 0xFFFF;用于后面赋值0xFFFF和检测比较时调用

	;令R6为0x0000,用于给单元赋值0x0000,并作为判断单元是否为全0的条件
    MOVS    R6, #0          ;R6 = 0  用于后面赋值0x0000和检测比较时调用

;1、升序将RAM全部写0
	MOVS    R1,#0           ;R1 = 0
	STRH    R1, [R0]        ;将R1的半字数据赋给R0代表的地址  
RAM_Clear0Rise
    ADDS    R0,R0,#2        ;R0 = R0+ 2
	STRH    R1, [R0]        ;把R1的半字数据赋值给R0
	
	CMP     R0, R3          ;先地址自加再执行循环，故执行到R0 = 0x20002FFE循环结束
    BNE     RAM_Clear0Rise  ;R1 - R3 ≠ 0   执行 RAM_Clear0Rise  

;2、升序检测RAM是否为0
	MOV     R0,R4           ;R0 = 0x20000000
	ADDS    R3,R3,#2        ;R3 = R3+ 2  R3 = 0x20003000
RAM_Test0Rise	
    MOV     R1,R0           ;R1 = R0
    LDRH    R1,[R1]	        ;将R1地址的数据赋给R1,并将R1的高16位清零  读回判断是否为0x0000
;    MOVS    R1,#5          ;	                                                              1、加入错误
    CMP     R1,R6           ;R6 = 0,比较R1和R6    ;检查单元是否为0
    BNE     RAM_TestFail    ;R1 - R6≠0,测试Fail
	
;3、升序对RAM全写1，并检验是否成功写入
RAM_Write1Rise
    STRH    R5,[R0]         ;将0xFFFF写进R0地址   ;对检测单元写0xFFFF
    LDRH    R1,[R0]	        ;将R0地址的数据赋给R1,并将R1的高16位清零  读回判断是否为0xFFFF
;    MOVS    R1,#5          ;	                                                              2、加入错误	
	CMP     R5,R1           ;检测单元0xFFF是否写入成功
    BNE     RAM_TestFail    ;R5 - R1≠0,测试Fail	
	
	ADDS    R0,R0,#2        ;R0 = R0+ 2
	CMP     R0,R3           ;先执行循环，再地址自加进行判断，故执行到R0 = 0x20003000时循环结束
    BNE     RAM_Test0Rise   ;R0 - R3 ≠ 0   执行 RAM_Test0Rise 	
	

;4、升序检测RAM是否为1
	MOV     R0,R4           ;R0 = 0x2000000
RAM_Test1Rise	
    MOV     R1,R0           ;R1 = R0
    LDRH    R1,[R1]	        ;将R1地址的数据赋给R1,并将R1的高16位清零
;    MOVS    R1,#5          ;	                                                               3、加入错误	
    CMP     R1,R5           ;R5 = 0xFFFF,比较R1和R5    ;检查单元是否为0xFFFF
    BNE     RAM_TestFail    ;R1 - R6≠0,测试Fail
;5、升序对RAM写0，并检验是否为0
RAM_Write0Rise
    STRH    R6,[R0]         ;将0写进R0地址   ;对检测单元写0
    LDRH    R1,[R0]	        ;将R0地址的数据赋给R1,并将R1的高16位清零
;    MOVS    R1,#5          ;	                                                               4、加入错误	
	CMP     R6,R1           ;检测单元0x0000是否写入成功
    BNE     RAM_TestFail    ;R6 - R1≠0,测试Fail	
	
	ADDS    R0,R0,#2        ;R0 = R0+ 2
	CMP     R0,R3           ;先执行循环，再地址自加进行判断，故执行到R0 = 0x20003000时循环结束
    BNE     RAM_Test1Rise   ;R0 - R3 ≠ 0   执行 RAM_Test0Rise 	    


;6、降序检测RAM是否为0
    SUBS    R3, R3, #2      ;R3 = R3-2 = 0x20002FFE，降序时最先执行的地址是0x20001FFE
	SUBS    R4, R4, #2      ;降序检测时检测到0x1FFFFFFE循环结束
	MOV     R0, R3          ;R0 = 0x20002FFE,从0x20002FFE开始降序往下读值检测，赋值检测
RAM_Test0Fall	
    MOV     R1,R0           ;R1 = R0
    LDRH    R1,[R1]	        ;将R1地址的数据赋给R1,并将R1的高16位清零
;    MOVS    R1,#5          ;	                                                                5、加入错误	
    CMP     R1,R6           ;R6 = 0,比较R1和R6，检查单元是否为0
    BNE     RAM_TestFail    ;R1 - R6≠0,测试Fail

;7、降序对RAM进行写1并检验是否写入成功
RAM_Write1Fall
    STRH    R5,[R0]         ;将0xFFFF写进R0地址   ;对检测单元写0xFFFF
    LDRH    R1,[R0]	        ;将R0地址的数据赋给R1,并将R1的高16位清零
;    MOVS    R1,#5          ;	                                                                6、加入错误	
	CMP     R5,R1           ;检测单元0xFFFF是否写入成功
    BNE     RAM_TestFail    ;R5 - R1≠0,测试Fail	
	
    SUBS    R0, R0, #2      ;R0 = R0 - 2 
	CMP     R0,R4           ;先执行循环，再地址自减进行判断，故执行到R0 = 0x1FFFFFFE时循环结束
    BNE     RAM_Write1Fall  ;R0 - R4 ≠ 0   执行 RAM_Test0Rise 	


;8、降序检测RAM是否为1
	MOV     R0,R3           ;R0 = 0x20002FFE，降序时最先执行的地址是0x20002FFE	
RAM_Test1Fall	
    MOV     R1,R0           ;R1 = R0
    LDRH    R1,[R1]	        ;将R1地址的数据赋给R1,并将R1的高16位清零
;    MOVS    R1,#5          ;	                                                                7、加入错误
    CMP     R1,R5           ;R5 = 0XFFFF,比较R1和R6    ;检查单元是否为1
    BNE     RAM_TestFail    ;R1 - R5≠0,测试Fail
;9、降序对RAM写0，并检验是否写入成功
RAM_Write0Fall
    STRH    R6,[R0]         ;将0x0000写进R0地址   ;对检测单元写0x0000
    LDRH    R1,[R0]	        ;将R0地址的数据赋给R1,并将R1的高16位清零
;    MOVS    R1,#5          ;	                                                                8、加入错误	
	CMP     R6,R1           ;检测单元0x0000是否写入成功
    BNE     RAM_TestFail    ;R6 - R1≠0,测试Fail	
	
    SUBS    R0, R0, #2      ;R0 = R0 - 2 
	CMP     R0,R4           ;先执行循环，再地址自减进行判断，故执行到R0 = 0x1FFFFFFE时循环结束
    BNE     RAM_Test1Fall   ;R0 - R4 ≠ 0   执行 RAM_Test0Rise     

;10、降序对RAM检测，判断是否全为0
	MOV     R0,R3           ;R0 = 0x20002FFE
RAM_Zero_Test
	MOV     R1,R0           ;R1 = R0
    LDRH    R1,[R1]	        ;将R1地址的数据赋给R1,并将R1的高16位清零
;    MOVS    R1,#5          ;	                                                                9、加入错误	
    CMP     R1,R6           ;R6 = 0,比较R1和R6    ;检查单元是否为0
    BNE     RAM_TestFail    ;R1 - R6≠0,测试Fail	

    SUBS    R0, R0, #2      ;R0 = R0 - 2 
	CMP     R0,R4           ;先执行循环，再地址自减进行判断，故执行到R0 = 0x1FFFFFFE时循环结束 
    BNE     RAM_Zero_Test   ;R0 - R4 ≠ 0   执行 RAM_Test0Rise  

RAM_TestPass                 
    MOVS   R7, #0xCC
    B      RAM_TestEnd      
    
RAM_TestFail                              
    MOVS   R7, #0xDD
    B      RAM_TestEnd 	

RAM_TestEnd
  
    MOV    R0,R7
    BX LR

    ENDP	


RAM_Rsult  PROC
  
  EXPORT RAM_Rsult
	  
  MOV   R0,R7  
  BX LR	
  
  ENDP
	  
  
  NOP
  END


  
  
  
 