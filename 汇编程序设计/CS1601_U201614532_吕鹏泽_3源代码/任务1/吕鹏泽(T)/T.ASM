NAME WAN1
EXTRN AVERAGR_PROFIT:NEAR,PROFIT_RANKING:NEAR,PRINT_IFO:NEAR
PUBLIC PRINTAX,PrintASCII,S1,S2,GA1,GB1
.386
INCLUDE MACRO.LIB
STACK SEGMENT USE16 PARA STACK 'STACK'
DB 200 DUP(0)
STACK ENDS
DATA SEGMENT USE16 PARA PUBLIC 'D1'
BNAME DB 'LVPENGZE',0,0			;管理员姓名
BPASS DB 'test',0,0				;密码
AUTH DB ?						;标记登陆状态
N EQU 10
S1 DB 'SHOP1','$'				;网店1
GA1 DB 'PEN',7 DUP(0)			
	DW 10,56,70,50,?			;进货价、销售价、进货总数、已售数量、利润率
GA2 DB 'BOOK',6 DUP(0)			
	DW 12,30,25,10,?
GA3 DB 'BAG',7 DUP(0)		
	DW 15,30,30,0,?	
GA4 DB 'CUP',7 DUP(0)		
	DW 10,23,40,12,?	
GA5 DB 'HAT',7 DUP(0)		
	DW 23,40,50,13,?	
GA6 DB 'JUICE',5 DUP(0)		
	DW 1,3,50,40,?	
GA7 DB 'RULER',5 DUP(0)		
	DW 3,8,30,10,?	
GA8 DB 'ERASER',4 DUP(0)		
	DW 1,2,30,12,?	
GAN DB N-8 DUP('TempValue',0,15,0,20,0,30,0,30,0,?,?)

S2 DB 'SHOP2','$'				;网店2
GB1 DB 'PEN',7 DUP(0)			
	DW 10,56,70,50,?			;进货价、销售价、进货总数、已售数量、利润率
GB2 DB 'BOOK',6 DUP(0)			
	DW 12,30,25,10,?
GB3 DB 'BAG',7 DUP(0)		
	DW 15,30,30,0,?	
GB4 DB 'CUP',7 DUP(0)		
	DW 10,23,40,12,?	
GB5 DB 'HAT',7 DUP(0)		
	DW 23,40,50,13,?	
GB6 DB 'JUICE',5 DUP(0)		
	DW 1,3,50,40,?	
GB7 DB 'RULER',5 DUP(0)		
	DW 3,8,30,10,?	
GB8 DB 'ERASER',4 DUP(0)		
	DW 1,2,30,12,?	
GBN DB N-8 DUP('TempValue',0,15,0,20,0,30,0,30,0,?,?)

PR1 DW 0						;商店1利润率 
PR2 DW 0						;商店2利润率 
APR DW 0						;平均利润率
MSG1 DB 0AH,0DH,'Input your account:',0DH,0AH,'$'
MSG2 DB 'Input your password:',0DH,0AH,'$'
MSG3 DB 'WRONG ACCOUNT',0DH,0AH,'$'
MSG4 DB 'Enter the name of the item:',0DH,0AH,'$'
MSG5 DB 0AH,0DH,'Input Your Option',0DH,0AH,'$'

MENU1 DB '1.Query commodity information','$'
MENU2 DB '2.Modify commodity information','$'
MENU3 DB '3.Calculate average profit margin','$'
MENU4 DB '4.Calculate profit rate ranking','$'
MENU5 DB '5.Export all product information','$'
MENU6 DB '6.Program exit','$'

SORT_BUF DW N DUP(0)
SORT_RAN DW N DUP(0)
Product_name DB 'Product name', '$'
Purchase_price DB 'Purchase price', '$'
Selling_price DB 'Selling price', '$'
Total_purchases DB 'Total purchases', '$'
Sold_quantity DB 'Sold Quantity', '$'
Profit_rate DB 'Profit rate', '$'
Ranking DB 'Ranking', '$'

SelectShop DB '1.SHOP1 2.SHOP2','$'
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
CODE SEGMENT USE16 PARA PUBLIC 'CODE'
ASSUME CS:CODE,DS:DATA,SS:STACK
START:
	MOV AX,DATA
	MOV DS,AX
GONG_NENG1:							;--------------------------------------------------功能1，提示登陆
	CALL ClearS
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
	JMP GONG_NENG2				;否则转登录
	
UNLOGIN:
	MOV AH,0
	MOV AUTH,AH					;标记登陆状态
	JMP GONG_NENG3				;未登录状态，转功能3
	
GONG_NENG2:						;---------------------------------------------------功能2，判断登陆
		XOR ECX,ECX
		MOV CL,in_name[1]		;循环比较姓名
		MOV ESI,0					
	LOOP1:							
		MOV BL,in_name[ESI+2]
		CMP BL,BNAME[ESI]
		JNE ACCOUNTWRONG		;姓名不匹配转ACCOUNTWRONG
		INC ESI
		DEC ECX				
		JNZ LOOP1
		
		MOV BL,0
		CMP BL,BNAME[ESI]
		JNZ ACCOUNTWRONG		;输入的字符串是定义字符串的子集
		
		XOR ECX,ECX
		MOV CL,in_pwd[1]	
		MOV ESI,0				;循环条件初始化
	LOOP2:					
		MOV BL,in_pwd[ESI+2]
		CMP BL,BPASS[ESI]
		JNE ACCOUNTWRONG		;密码不匹配转ACCOUNTWRONG
		INC ESI
		DEC ECX
		JNZ LOOP2
		
		MOV BL,0
		CMP BL,BPASS[ESI]
		JNZ ACCOUNTWRONG
		JMP	SUCCESS				;账号密码都相同转登陆成功
	
	ACCOUNTWRONG:				;登陆失败
		WRITE MSG3
		JMP GONG_NENG1
	
SUCCESS:						;登陆成功
	MOV AH,1
	MOV AUTH,AH
	JMP GONG_NENG3				;已登录状态，转功能3
	
GONG_NENG3:						;---------------------------------------------------功能3
	
	CALL ClearS
	CALL DisplayMenu
	CALL SelectFun
	
	CMP AL,'1'
	JE _FUN1
	CMP AL,'2'
	JE _FUN2
	CMP AL,'3'
	JE _FUN3
	CMP AL,'4'
	JE _FUN4
	CMP AL,'5'
	JE _FUN5
	CMP AL,'6'
	JE _FUN6
_FUN1:
	CALL QueryCommodity
	JMP _FUN_NEXT
_FUN2:
	CALL ModifyCommodity
	JMP _FUN_NEXT
_FUN3:
	CALL AVERAGR_PROFIT
	JMP _FUN_NEXT
_FUN4:
	CALL PROFIT_RANKING
	JMP _FUN_NEXT
_FUN5:
	CALL PRINT_IFO
	JMP _FUN_NEXT
_FUN6:
	JMP EXIT
_FUN_NEXT:
	MOV AH,01H
	INT 21H
	JMP GONG_NENG3
	
	
GONG_NENG4:						;---------------------------------------------------功能4，商品等级判断			
	MOV AX,PR1
	CMP AX,90
	JGE A_GRADE					;利润率大于90%
	CMP AX,50
	JGE B_GRADE					;利润率大于50%
	CMP AX,20
	JGE C_GRADE					;利润率大于20%
	CMP AX,0
	JGE D_GRADE					;利润率大于0%
	JMP F_GRADE

A_GRADE:
	OUT1 'A'
	CRLF
	JMP T
B_GRADE:
	OUT1 'B'
	CRLF
	JMP T
C_GRADE:
	OUT1 'C'
	CRLF
	JMP T
D_GRADE:
	OUT1 'D'
	CRLF
	JMP T
F_GRADE:
	OUT1 'F'
	CRLF
	JMP T
T:
	JMP GONG_NENG1

EXIT:
	MOV AH,4CH
    INT 21H						;退出程序
	
;------------------------------
;以10进制输出有符号整数
;EAX——需要输出的数
PRINTAX PROC 
	PUSH EBX
    PUSH CX
	PUSH EDX					;保护现场
	MOV EBX,10
	XOR CX,CX					;计数器清0
	CMP EAX,0
	JNL _LOP1
	NOT EAX
	ADD EAX,1
	PUSH EAX
	OUT1 '-'					;输出负号
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
	POP CX						
	POP EBX						;恢复现场
	RET
PRINTAX ENDP

;------------------------------
;重复输出字符
;AL——需要重复输出的字符
;AH——需要重复输出的字符数
PrintASCII PROC 
	PUSH ECX
	MOVSX ECX,AH
_PUTCHAR_:
	OUT1 AL
	LOOP _PUTCHAR_
	POP ECX
	RET
PrintASCII ENDP

;模块功能:显示菜单
;模块名称:DisplayMenu
;传入参数:无
;参数传入方式：无
;传出参数:无
;参数传出方式：无
;备注:负责人：吕鹏泽 同组同学：吴阳民
DisplayMenu PROC 
	PUSH AX
	
	MOV AL,' '
	MOV AH,10
	CALL PrintASCII
	MOV AL,'-'
	MOV AH,60
	CALL PrintASCII
	CRLF
	
	MOV AH,AUTH
	CMP AH,0
	JE _DM_UNLOGIN_
	JMP _DM_LOGIN_
_DM_LOGIN_:
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU1
	CRLF
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU2
	CRLF
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU3
	CRLF
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU4
	CRLF
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU5
	CRLF
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU6
	CRLF
	JMP _DM_R_
_DM_UNLOGIN_:
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU1
	CRLF
	MOV AL,' '
	MOV AH,20
	CALL PrintASCII
	WRITE MENU6
	CRLF
	JMP _DM_R_
_DM_R_:
	MOV AL,' '
	MOV AH,10
	CALL PrintASCII
	MOV AL,'-'
	MOV AH,60
	CALL PrintASCII
	CRLF
	POP AX
	RET
DisplayMenu ENDP
;------------------------------
;根据登录状态选择功能
;AL——记录并返回选择的功能
SelectFun PROC
_S_RESTART:
	WRITE MSG5
	MOV AH,01H
	INT 21H
	MOV AH,AUTH
	CMP AH,0
	JE _S_UNLOGIN_
	JMP _S_LOGIN_
_S_LOGIN_:
	CMP AL,'1'
	JL _S_RESTART
	CMP AL,'6'
	JG _S_RESTART
	JMP _S_R_
_S_UNLOGIN_:
	CMP AL,'1'
	JE _S_R_
	CMP AL,'6'
	JE _S_R_
	JMP _S_RESTART
_S_R_:
	PUSH AX
	CRLF
	POP AX
	RET
SelectFun ENDP

;------------------------------清屏
ClearS PROC 
	PUSH AX
	MOV AH,00H
    MOV AL,03H
    INT 10H
	POP AX
	RET
ClearS ENDP

;功能 1
;模块功能:查询商品信息
;模块名称:QueryCommodity
;传入参数:无
;参数传入方式：无
;传出参数:无
;参数传出方式：无
;备注:负责人：吕鹏泽 同组同学：吴阳民
QueryCommodity PROC 
	PUSH ECX
	PUSH EBX
	PUSH ESI
	PUSH EDX
_QC_START:
	WRITE MSG4
	READ in_goods
	CRLF
	MOV ECX,N
	MOV EBX,0
_QC_LOOP1:						;第一层循环，顺序查询N件商品
	MOV ESI,0
	MOV AL,in_goods[1]
	CBW
	MOV DX,AX					;DX控制第二层循环
	_QC_LOOP2:					;第二层循环，比较商品名称
		MOV AH,GA1[EBX][ESI]
		CMP AH,in_goods[ESI+2]
		JNE _QC_UNFIND				;名称不同
		INC ESI					
		DEC DX								
		JZ _QC_JUDGE				;找到商品,转JUDGE
		JMP _QC_LOOP2	
		
_QC_UNFIND:
	ADD EBX,20
	DEC ECX
	JNZ _QC_LOOP1
	JMP _QC_START					;未找到商品，重新输入商品名称
_QC_JUDGE:
	MOV AH,GA1[EBX][ESI]
	CMP AH,0
	JNE _QC_UNFIND						;商品名称为子集,属于未找到
	JMP _QC_FIND
_QC_FIND:
;显示商店1商品
	MOV AH,40
	MOV AL,'-'
	CALL PRINTASCII
	CRLF
	WRITE S1
	OUT1 ':'
	OUT1 ' '

	MOVSX SI,BYTE PTR in_goods[1]
	MOV AH,'$'  
    MOV in_goods[SI+2],AH
	WRITE in_goods[2]
	CRLF
	
	WRITE Purchase_price
	OUT1 ':'
	MOVSX EAX,WORD PTR GA1[EBX+10]
	CALL PRINTAX
	CRLF
	
	WRITE Selling_price
	OUT1 ':'
	MOVSX EAX,WORD PTR GA1[EBX+12]
	CALL PRINTAX
	CRLF
	
	WRITE Total_purchases
	OUT1 ':'
	MOVSX EAX,WORD PTR GA1[EBX+14]
	CALL PRINTAX
	CRLF
	
	WRITE Sold_quantity
	OUT1 ':'
	MOVSX EAX,WORD PTR GA1[EBX+16]
	CALL PRINTAX
	CRLF
	
	
;显示商店2商品
	MOV AH,40
	MOV AL,'-'
	CALL PRINTASCII
	CRLF
	WRITE S2
	OUT1 ':'
	OUT1 ' '
	WRITE in_goods[2]
	CRLF
	
	WRITE Purchase_price
	OUT1 ':'
	MOVSX EAX,WORD PTR GB1[EBX+10]
	CALL PRINTAX
	CRLF
	
	WRITE Selling_price
	OUT1 ':'
	MOVSX EAX,WORD PTR GB1[EBX+12]
	CALL PRINTAX
	CRLF
	
	WRITE Total_purchases
	OUT1 ':'
	MOVSX EAX,WORD PTR GB1[EBX+14]
	CALL PRINTAX
	CRLF
	
	WRITE Sold_quantity
	OUT1 ':'
	MOVSX EAX,WORD PTR GB1[EBX+16]
	CALL PRINTAX
	CRLF
	POP EDX
	POP ESI
	POP EBX
	POP ECX
	RET
QueryCommodity ENDP

;功能 2
;模块功能:修改商品信息
;模块名称:ModifyCommodity
;传入参数:无
;参数传入方式：无
;传出参数:无
;参数传出方式：无
;备注:负责人：吕鹏泽 同组同学：吴阳民
ModifyCommodity PROC
	PUSHAD
_MC_START:
	WRITE SelectShop
	CRLF
	MOV AH,01H
	INT 21H
	CMP AL,'1'					;选择商店1
	JE _MC_1
	CMP AL,'2'
	JE _MC_2					;选择商店2
	JMP _MC_START				;输入错误
_MC_1:
	LEA EBX,GA1
	JMP _MC_3
_MC_2:
	LEA EBX,GB1
	JMP _MC_3
_MC_3:
	CRLF
	WRITE MSG4
	READ in_goods
	CRLF
	CMP in_goods[1],0
	JE _MC_R					;输入回车
	
	MOV ECX,N					;查询商品
_MC_LOOP1:						
	MOV ESI,0
	MOV AL,in_goods[1]
	CBW
	MOV DX,AX					;DX控制第二层循环
	_MC_LOOP2:					;第二层循环，比较商品名称
		MOV AH,DS:[EBX][ESI]
		CMP AH,in_goods[ESI+2]
		JNE _MC_UNFIND				;名称不同
		INC ESI					
		DEC DX								
		JZ _MC_JUDGE				;找到商品,转JUDGE
		JMP _MC_LOOP2	
		
_MC_UNFIND:
	ADD EBX,20
	DEC ECX
	JNZ _MC_LOOP1
	JMP _MC_START					;未找到商品，重新输入商品名称
_MC_JUDGE:
	MOV AH,DS:[EBX][ESI]
	CMP AH,0
	JNE _MC_UNFIND						;商品名称为子集,属于未找到
	JMP _MC_FIND
_MC_FIND:

_MC_T1:
	CRLF
	WRITE Purchase_price
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[EBX+10]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T1
	CMP CX,-2
	JE _MC_T2
	MOV WORD PTR DS:[EBX+10],CX
	CRLF
_MC_T2:
	CRLF
	WRITE Selling_price
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[EBX+12]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T2
	CMP CX,-2
	JE _MC_T3
	MOV WORD PTR DS:[EBX+12],CX
	CRLF
_MC_T3:
	CRLF
	WRITE Total_purchases
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[EBX+14]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T3
	CMP CX,-2
	JE _MC_T4
	MOV WORD PTR DS:[EBX+14],CX
	CRLF
_MC_T4:
	CRLF
	WRITE Sold_quantity
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[EBX+16]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T4
	CMP CX,-2
	JE _MC_R
	MOV WORD PTR DS:[EBX+16],CX
	CRLF
	
_MC_R:
	POPAD
	RET
ModifyCommodity ENDP

;------------------------------
;从键盘输入10进制数，结果存在CX中
;传出参数：CX,输入的10进制数,如果输入错误则CX=-1,如果输入回车CX=-2
INPUT_NEW_INFO PROC 
	PUSH AX
	PUSH BX
	MOV CX,0
	MOV AH,01H
	INT 21H
	CMP AL,0DH
	JE _INI_0DH					;只输入了回车
	JMP _INI_JUDGE
_INI_START:
	MOV AH,01H
	INT 21H
	CMP	AL,0DH
	JE	_INI_R
_INI_JUDGE:	
	CMP AL,'0'
	JL _INI_WRONG				;输入字符不合法
	CMP AL,'9'
	JG _INI_WRONG				;输入字符不合法
	SUB AL,'0'					;转换成数字
	MOVSX BX,AL	
	IMUL CX,10
	ADD CX,BX
	JMP _INI_START
_INI_WRONG:
	MOV CX,-1
	JMP _INI_R
_INI_0DH:
	MOV CX,-2
	JMP _INI_R
_INI_R:
	POP BX
	POP AX
	RET
INPUT_NEW_INFO ENDP

CODE ENDS
END START
