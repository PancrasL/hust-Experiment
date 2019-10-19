NAME WAN1
EXTRN PRINT_IFO:NEAR
PUBLIC PRINTAX,PrintASCII,S1,S2,GA1,GB1,N,NEWKEY
.386
INCLUDE MACRO.LIB
STACK SEGMENT USE16 PARA STACK 'STACK'
DB 200 DUP(0)
STACK ENDS
DATA SEGMENT USE16 PARA PUBLIC 'D1'
BNAME DB 'L' XOR KEY  		;真实姓名为LVPENGZE。采用函数X XOR 57H 对用户名进行加密
	  DB 'V' XOR KEY,'P' XOR KEY,'E' XOR KEY,'N' XOR KEY,'G' XOR KEY,'Z' XOR KEY,'E' XOR KEY
	  DB ('#'-20H)*3			;用户名结束符
	  DB 34H					;随机字符

BPASS DB ('B' -20H)*3    		;真实密码为BOS。采用函数(X-20H)*3对保存的密码进行编码。
	  DB ('O' -20H)*3
	  DB ('S' -20H)*3 
	  DB ('#'-20H)*3			;密码结束符
	  DB 34H,57H				;随机字符
AUTH DB ?						;标记登陆状态
N EQU 3
KEY EQU ('B'-'O'+'S')	;加密密匙与密码相关
NEWKEY DB ?						;输入密码对应的密匙
S1 DB 'SHOP1','$'				;网店1
GA1 DB 'PEN',7 DUP(0)			
	DW 5 XOR KEY,56,70,50,?	;进货价、销售价、进货总数、已售数量、利润率
GA2 DB 'BOOK',6 DUP(0)			
	DW 23 XOR KEY,30,25,10,?
GA3 DB 'BAG',7 DUP(0)		
	DW 15 XOR KEY,30,30,0,?	

S2 DB 'SHOP2','$'				;网店2
GB1 DB 'PEN',7 DUP(0)			
	DW 4 XOR KEY,56,70,50,?	;进货价、销售价、进货总数、已售数量、利润率
GB2 DB 'BOOK',6 DUP(0)			
	DW 32 XOR KEY,30,25,10,?
GB3 DB 'BAG',7 DUP(0)		
	DW 13 XOR KEY,30,30,0,?	

MSG1 DB 0AH,0DH,'Input your account:',0DH,0AH,'$'
MSG2 DB 'Input your password:',0DH,0AH,'$'
MSG3 DB 'WRONG ACCOUNT',0DH,0AH,'$'
MSG4 DB 'Enter the name of the item:',0DH,0AH,'$'
MSG5 DB 0AH,0DH,'Input Your Option',0DH,0AH,'$'

MENU5 DB '5.Export all product information','$'
MENU6 DB '6.Program exit','$'

COUNT DB 3

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
		 
E       DW  EXIT             ;地址表（用于间接转移反跟踪）,E为退出程序
GN3     DW GONG_NENG3		;功能3的地址
MFUN5	DW PRINT_IFO		;菜单功能5地址
	


OLDINT1 DW  0,0               ;1号中断的原中断矢量（用于中断矢量表反跟踪）
OLDINT3 DW  0,0               ;3号中断的原中断矢量

DATA ENDS
CODE SEGMENT USE16 PARA PUBLIC 'CODE'
ASSUME CS:CODE,DS:DATA,SS:STACK
START:
	MOV AX,DATA
	MOV DS,AX
	
	   xor  ax,ax                  ;接管调试用中断，中断矢量表反跟踪
       mov  es,ax
       mov  ax,es:[1*4]            ;保存原1号和3号中断矢量
       mov  OLDINT1,ax
       mov  ax,es:[1*4+2]
       mov  OLDINT1+2,ax
       mov  ax,es:[3*4]
       mov  OLDINT3,ax
       mov  ax,es:[3*4+2]
       mov  OLDINT3+2,ax
       
GONG_NENG1:							;--------------------------------------------------功能1，提示登陆
	CALL ClearS
	WRITE MSG1	
	READ in_name
	CRLF
R1: 	cli                           ;设置新的中断矢量,混在程序中，使用jmp语句执行
		jmp R2
		db 'step1'

R9:
	WRITE MSG2
	READ in_pwd
	CRLF
	
	MOV AL,in_pwd[2]
	ADD AL,in_pwd[4]
	SUB AL,in_pwd[3]			;输入密码转换成的key，若输入正确则解密正确，否则解密错误
	MOV NEWKEY,AL
	
	CMP AUTH,2
	JNE EXIT
	MOV BL,in_name[2]
	CMP BL,'q'
	JE Y1
	JMP Y2
Y1:									
	JMP WORD PTR E					;输入'q'，退出程序
	 db 'login success'				;干扰
	
Y2:	MOV BL,in_name[1]
	
	CMP BL,0
	JE UNLOGIN					;输入回车,转未登录
	JMP GONG_NENG2			    ;否则转功能2
	 db 'maybe next time'		;干扰
	 
UNLOGIN:
	 lea bx,AUTH
 	 mov byte ptr DS:[BX],0		;标记登陆状态
	 jmp word ptr GN3			;未登录状态，转功能3


GONG_NENG2:						;---------------------------------------------------功能2，判断登陆
		XOR ECX,ECX				;循环比较姓名
		MOV CL,in_name[1]		
		MOV ESI,0					
	LOOP1:							
		MOV BL,in_name[ESI+2]
		XOR BL,NEWKEY
		CMP BL,BNAME[ESI]
		JNE ACCOUNTWRONG		;姓名不匹配转ACCOUNTWRONG
		INC ESI
		DEC ECX				
		JNZ LOOP1
		
		MOV BX,'#'
		SUB BX,20H
		IMUL BX,3
		CMP BL,BNAME[ESI]
		JNZ ACCOUNTWRONG		;输入的字符串是定义字符串的子集
		
		XOR ECX,ECX				;循环比较密码
		MOV CL,in_pwd[1]	
		MOV ESI,0				
	LOOP2:					
		MOVSX BX,in_pwd[ESI+2]
		SUB BX,20H
		IMUL BX,3
		CMP BL,BPASS[ESI]
		JNE ACCOUNTWRONG		;密码不匹配转ACCOUNTWRONG
		INC ESI
		DEC ECX
		JNZ LOOP2
		
		;XOR BX,BX
		MOV BX,'#'
		SUB BX,20H
		IMUL BX,3
		CMP BL,BPASS[ESI]
		

	JNZ ACCOUNTWRONG
	JMP	SUCCESS				;账号密码都相同转登陆成功
	
ACCOUNTWRONG:				;登陆失败
	DEC COUNT
	JZ UNLOGIN
	WRITE MSG3
	MOV AH,01H
	INT 21H
	JMP GONG_NENG1
	
SUCCESS:						;登陆成功	
	LEA BX,AUTH
	MOV BYTE PTR DS:[BX],1		;间接赋值，干扰修改登录状态
	 jmp word ptr GN3[0]			;已登录状态，转功能3
	DB 'GOOD JOB'				;干扰
GONG_NENG3:						;---------------------------------------------------功能3
	 mov  bx,es:[1*4]            ;检查中断矢量表是否被调试工具阻止修改或恢复
     inc  bx
     jmp  bx                 ;正常修改了的化，这里将转移到TESTINT，否则就不知道转到哪了
Y3:	CALL ClearS
	CALL DisplayMenu
	CALL SelectFun

	CMP AL,'5'
	JE _FUN5
	CMP AL,'6'
	JE _FUN6
_FUN5:
	CALL WORD PTR MFUN5
	JMP _FUN_NEXT
_FUN6:
	JMP EXIT
	
_FUN_NEXT:
	MOV AH,01H
	INT 21H
	JMP WORD PTR GN3


EXIT:
	   cli                           ;还原中断矢量
       mov  ax,OLDINT1
       mov  es:[1*4],ax
       mov  ax,OLDINT1+2
       mov  es:[1*4+2],ax
       mov  ax,OLDINT3
       mov  es:[3*4],ax
       mov  ax,OLDINT3+2
       mov  es:[3*4+2],ax 
       sti

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
R2:      mov  ax,OFFSET NEWINT
		 jmp R3
		db 'step2'
R3:      mov  es:[1*4],ax
		 jmp R4
		 db 'step3'
R4:      mov  es:[1*4+2],cs
		 jmp R5
		 db 'step4'
R5:	     mov  AUTH,2					;标记这一段程序被执行
		 jmp R6
		 db 'step5'
R6:      mov  es:[3*4],ax
		 jmp R7
		 db 'step6'
R7:      mov  es:[3*4+2],cs
	 	 jmp R8
		 db 'step7'
R8:      sti
		 jmp R9
		 db 'step8'
;模块功能:显示菜单
;模块名称:DisplayMenu
;传入参数:无
;参数传入方式：无
;传出参数:无
;参数传出方式：无
;备注:负责人：吕鹏泽
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
	CMP AL,'5'
	JE _S_R_
	CMP AL,'6'
	JE _S_R_
	JMP _S_RESTART
_S_UNLOGIN_:
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

NEWINT: iret
TESTINT: jmp Y3						 ;进入正常功能区
	DB 'WRONG'
CODE ENDS
END START
