.386
INCLUDE MACRO.LIB
STACK SEGMENT USE16 STACK
DB 200 DUP(0)
STACK ENDS
DATA SEGMENT USE16
BNAME DB 'LVPENGZE',0,0			;管理员姓名
BPASS DB 'test',0,0				;密码
AUTH DB ?						;标记登陆状态
N EQU 300
M EQU 1000
S1 DB 'SHOP1',0					;网店1名称，用0结束
GA1 DB 'PEN',7 DUP(0)			;商品1
	DW 35,56,70,50,?			;进货价、销售价、进货总数、已售数量、利润率
GA2 DB 'BOOK',6 DUP(0)			;商品2
	DW 12,30,25,25,?
GA3 DB 'BAG',7 DUP(0)			;商品3
	DW 15,30,M,0,?	
GAN DB N-3 DUP('Temp-Value',15,0,20,0,30,0,30,0,?,?);其他商品

S2 DB 'SHOP2',0					;网店2名称，用0结束,商品类型同网店1
GB1 DB 'PEN',7 DUP(0)			;商品1		
	DW 35,56,70,50,?			;进货价、销售价、进货总数、已售数量、利润率	
GB2 DB 'BOOK',6 DUP(0)			;商品2    
	DW 12,30,25,25,?
GB3 DB 'BAG',7 DUP(0)			;商品3
	DW 15,30,M,0,?
GBN DB N-3 DUP('Temp-Value',15,0,20,0,30,0,30,0,?,?);其他商品

PR1 DW 0						;商店1利润率 
PR2 DW 0						;商店2利润率 
APR DW 0						;平均利润率
MSG1 DB 0AH,0DH,'Input your account:',0DH,0AH,'$'
MSG2 DB 'Input your password:',0DH,0AH,'$'
MSG3 DB 'WRONG ACCOUNT',0DH,0AH,'$'
MSG4 DB 'Enter the name of the item:',0DH,0AH,'$'

CRLF1 DB 0DH,0AH,'$'				;回车换行
in_name  DB 11					;姓名缓冲区  
         DB ? 
         DB 11 DUP(0)
in_pwd	 DB 7					;密码缓冲区  
         DB ? 
         DB 7 DUP(0)
in_goods DB 11					;商品名缓冲区
		 DB ?
		 DB 11 DUP(0)


DATA ENDS
CODE SEGMENT USE16
ASSUME CS:CODE,DS:DATA,SS:STACK
START:
	MOV AX,DATA
	MOV DS,AX
NEXT:							;功能1，提示登陆
	WRITE MSG1	
	READ in_name
	CRLF
	
	WRITE MSG2
	READ in_pwd
	CRLF
	
	MOV BL,in_name[2]
	CMP BL,'q'
	JE	EXIT					;输入'q'，退出程序
	
	MOV BL,in_name[1]
	CMP BL,0
	JE UNLOGIN					;输入回车,转未登录
	JMP LOGIN					;否则转登录
	
UNLOGIN:
	MOV AH,0
	MOV AUTH,AH					;标记登陆状态
	JMP PROFIT					;转利润率计算
	
LOGIN:							;功能2，判断登陆
	XOR ECX,ECX
	MOV CL,in_name[1]
	MOV ESI,0					;循环条件初始化
LOOP1:							;循环比较姓名
	MOV BL,in_name[ESI+2]
	CMP BL,BNAME[ESI]
	JNE ACCOUNTWRONG			;姓名不匹配转ACCOUNTWRONG
	INC ESI
	DEC ECX				
	JNZ LOOP1
	
	MOV BL,0
	CMP BL,BNAME[ESI]
	JNZ ACCOUNTWRONG			;输入的字符串是定义字符串的子集
	
	XOR ECX,ECX
	MOV CL,in_pwd[1]	
	MOV ESI,0					;循环条件初始化
LOOP2:					
	MOV BL,in_pwd[ESI+2]
	CMP BL,BPASS[ESI]
	JNE ACCOUNTWRONG			;密码不匹配转ACCOUNTWRONG
	INC ESI
	DEC ECX
	JNZ LOOP2
	
	MOV BL,0
	CMP BL,BPASS[ESI]
	JNZ ACCOUNTWRONG			;输入为子集，转ACCOUNTWRONG
	JMP	SUCCESS					;账号密码都相同转登陆成功
	
ACCOUNTWRONG:					;登陆失败
	WRITE MSG3
	JMP NEXT					;回到初始状态
	
SUCCESS:						;登陆成功
	MOV AH,1
	MOV AUTH,AH
	JMP PROFIT
	
PROFIT:							;功能3，计算利润率
	WRITE MSG4
	READ in_goods
	CRLF
	
	MOV BL,in_goods[1]			
	CMP BL,0
	JE NEXT						;输入回车,回到初始状态
	MOV AX,0					
	CALL TIMER					;开始计时
	
	MOV EDI,M
R:
	MOV ECX,N
	MOV EBX,0					;BX基址寄存器
LOOP3:							;第一层循环，顺序查询N件商品
	MOV ESI,0
	MOV AL,in_goods[1]
	CBW
	MOV DX,AX					;DX控制第二层循环
	LOOP4:						;第二层循环，比较商品名称
		MOV AH,GA1[EBX][ESI]
		CMP AH,in_goods[ESI+2]
		JNE F1					;名称不同
		INC ESI					;变址++
		DEC DX								
		JZ JUDGE				;找到商品,转JUDGE
		JMP LOOP4	
		
F1:
	ADD EBX,20
	DEC ECX
	JNZ LOOP3
	JMP PROFIT					;未找到商品，重新输入商品名称
JUDGE:
	CMP ESI,10					;商品名称恰好10个字符
	JE F2
	
	MOV AH,GA1[EBX][ESI]
	CMP AH,0
	JNE F1						;商品名称为子集,属于未找到
	
F2:	
	MOV AH,AUTH
	CMP AH,1
	JE L1						;登陆状态转L1
	JMP L2						;未登录状态转L2
L1:								;计算商品利润率
	MOV EAX,0					
    LEA EBP,GA1[EBX][10]		;S1中商品信息基址
	
	MOV AX,DS:[EBP+4]			;进货总数
	CMP AX,DS:[EBP+6]
	JLE NEXT					;进货数<售出数，转NEXT
	MOV AX,1
	ADD DS:[EBP+6],AX			;售出数+1
	
	MOV SI,N					
	MOV EBP,0					;0172H
R_PROFIT:
	MOVSX EAX,WORD PTR GA1[EBP][10]	
	MOVSX EDX,WORD PTR GA1[EBP][14]
	IMUL EAX,EDX	
	MOV EBX,EAX						;ebx=成本
	
	MOVSX EAX,WORD PTR GA1[EBP][12]	
	MOVSX EDX,WORD PTR GA1[EBP][16]
	IMUL EAX,EDX				;eax=收入
	
	SUB EAX,EBX					;EAX=利润
	IMUL EAX,100
	CDQ
	IDIV EBX					;EAX=利润率
	MOV PR1,AX
	
	MOVSX EAX,WORD PTR GB1[EBP][10]	
	MOVSX EDX,WORD PTR GB1[EBP][14]
	IMUL EAX,EDX		
	MOV EBX,EAX						;ebx=成本
	
	MOVSX EAX,WORD PTR GB1[EBP][12]	
	MOVSX EDX,WORD PTR GB1[EBP][16]
	IMUL EAX,EDX				;eax=收入
		
	SUB EAX,EBX					;EAX=利润
	IMUL EAX,100
	CDQ
	IDIV EBX					;EAX=利润率
	MOV PR2,AX
	MOV WORD PTR GB1[EBP][18],AX;存储商店2商品利润率到商品利润字段中
	
	ADD AX,PR1
	SAR AX,1				
	MOV APR,AX
	MOV WORD PTR GA1[EBP][18],AX	;总利润率
	;CALL PRINTAX
	;CRLF
	;MOV AH,01H
	;INT 21H					;调试，观察利润率是否计算正确
	ADD EBP,20
	DEC SI						
	JNZ R_PROFIT
	
	DEC EDI
	JNZ R						;循环计算M次
	
	MOV AX,WORD PTR GA1[40][18]
	JMP LEVEL
	
L2:
    MOV AL,in_goods[1]
    CBW
    MOV SI,AX
	MOV AH,'$'  
    MOV in_goods[SI+2],AH
	WRITE in_goods[2]
	CRLF						;输出商品名称
	JMP NEXT					;回到初始状态
LEVEL:							;功能4，商品等级判断			
	MOVSX EAX,WORD PTR GA3[18]		;输出BAG的利润率025DH
	MOV EBX,10
	CALL PRINTAX	
	OUT1 '%'
	CRLF
	MOV AX,WORD PTR GA3[18]
	CMP AX,90
	JGE _A						;利润率大于90%
	CMP AX,50
	JGE _B						;利润率大于50%
	CMP AX,20
	JGE _C						;利润率大于20%
	CMP AX,0
	JGE _D						;利润率大于0%
	JMP _F

_A:
	OUT1 'A'
	CRLF
	JMP T
_B:
	OUT1 'B'
	CRLF
	JMP T
_C:
	OUT1 'C'
	CRLF
	JMP T
_D:
	OUT1 'D'
	CRLF
	JMP T
_F:
	OUT1 'F'
	CRLF
	JMP T
T:
	MOV AX,1
	CALL TIMER					;结束计时
	JMP NEXT
EXIT:
	MOV AH,4CH
    INT 21H						;退出程序
	
;------------------------------以10进制输出AX中的无符号整数
PRINTAX PROC 
	MOV EBX,10
    PUSH CX
	PUSH EDX					;保护现场
	XOR CX,CX					;计数器清0
	CMP EAX,0
	JNL _LOP1
	NOT EAX
	ADD EAX,1
	PUSH EAX
	MOV AH,2
	MOV DL,'-'
	INT 21H						;输出负号
	POP EAX
_LOP1:							;(EAX)除以P，所得商->EAX，余数入栈，CX++，记录余数个数
	XOR EDX,EDX
	DIV EBX
	PUSH DX
	INC CX
	OR EAX,EAX
	JNZ _LOP1
_LOP2:							;从栈中弹出一位P进制数，并将该数转换成ASCII码后输出
	POP AX
	CMP AL,10
	JB _L1
	ADD AL,7
_L1:							;输出P进制数
	ADD AL,30H
	MOV DL,AL
	MOV AH,2
	INT 21H
	LOOP _LOP2
	POP EDX
	POP CX						;恢复现场
	RET
PRINTAX ENDP
;------------------------------
;时间计数器(ms),在屏幕上显示程序的执行时间(ms)
;使用方法:
;	   MOV  AX, 0	;表示开始计时
;	   CALL TIMER
;	   ... ...	;需要计时的程序
;	   MOV  AX, 1	
;	   CALL TIMER	;终止计时并显示计时结果(ms)
;输出: 改变了AX和状态寄存器
TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP

CODE ENDS
END START
