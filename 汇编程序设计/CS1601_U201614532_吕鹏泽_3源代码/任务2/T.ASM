
PUBLIC _QueryCommodity,_ModifyCommodity,_AVERAGR_PROFIT,_PROFIT_RANKING,_PRINT_IFO,_ClearS,_SETDS
INCLUDE MACRO.LIB
.386
_STACK1 SEGMENT USE16 PARA STACK 'STACK'
	DB 400 DUP(0)
_STACK1 ENDS
_DATA SEGMENT USE16 PARA PUBLIC 'DATA'

MSG4 DB 'Enter the name of the item:',0DH,0AH,'$'

SelectShop DB '1.SHOP1 2.SHOP2','$'
Product_name DB 'Commodity', '$'
Purchase_price DB ' cost ', '$'
Selling_price DB ' price ', '$',0
Total_purchases DB 'Total Quantity', '$'
Sold_quantity DB 'Sold Quantity', '$'
Profit_rate DB 'Profit rate', '$'
Ranking DB 'Ranking', '$'
S1 DB 'SHOP1','$'
S2 DB 'SHOP2','$'
in_goods DB 11					;商品名缓冲区
		 DB ?
		 DB 11 DUP(0)

_DATA ENDS
_TEXT SEGMENT USE16 PARA PUBLIC 'CODE'
ASSUME CS:_TEXT,DS:_DATA,SS:_STACK1
_SETDS PROC
	MOV AX,_DATA
	MOV DS,AX
	_SETDS ENDP
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
PRINTASCII PROC 
	PUSH ECX
	MOVSX ECX,AH
_PUTCHAR_:
	OUT1 AL
	LOOP _PUTCHAR_
	POP ECX
	RET
PRINTASCII ENDP
;------------------------------清屏
_ClearS PROC 
	PUSH AX
	MOV AH,00H
    MOV AL,03H
    INT 10H
	POP AX
	RET
_ClearS ENDP

;功能 1
;模块功能:查询商品信息
;模块名称:_QueryCommodity
;传入参数:无
;参数传入方式：无
;传出参数:无
;参数传出方式：无
;备注:使用了DB类型，10个字节的缓冲区in_name
_QueryCommodity PROC C GA1:WORD,GB1:WORD,N:WORD
	MOV AX,_DATA
	PUSHAD
_QC_START:
	WRITE MSG4
	READ in_goods
	CRLF
	MOV CX,N
	MOV BX,GA1
_QC_LOOP1:						;第一层循环，顺序查询N件商品
	MOV SI,0
	MOV AL,in_goods[1]
	CBW
	MOV DX,AX					;DX控制第二层循环
	_QC_LOOP2:					;第二层循环，比较商品名称
		MOV AH,DS:[BX][SI]
		CMP AH,in_goods[SI+2]
		JNE _QC_UNFIND				;名称不同
		INC SI					
		DEC DX								
		JZ _QC_JUDGE				;找到商品,转JUDGE
		JMP _QC_LOOP2	
		
_QC_UNFIND:
	ADD BX,20
	DEC CX
	JNZ _QC_LOOP1
	JMP _QC_START					;未找到商品，重新输入商品名称
_QC_JUDGE:
	MOV AH,DS:[BX][SI]
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
	MOVSX EAX,WORD PTR DS:[BX+10]
	CALL PRINTAX
	CRLF
	
	WRITE Selling_price
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+12]
	CALL PRINTAX
	CRLF
	
	WRITE Total_purchases
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+14]
	CALL PRINTAX
	CRLF
	
	WRITE Sold_quantity
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+16]
	CALL PRINTAX
	CRLF
	
	WRITE Profit_rate
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+18]
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
	SUB BX,GA1
	ADD BX,GB1
	MOVSX EAX,WORD PTR DS:[BX+10]
	CALL PRINTAX
	CRLF
	
	WRITE Selling_price
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+12]
	CALL PRINTAX
	CRLF
	
	WRITE Total_purchases
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+14]
	CALL PRINTAX
	CRLF
	
	WRITE Sold_quantity
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+16]
	CALL PRINTAX
	CRLF
	
	WRITE Ranking
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+18]
	CALL PRINTAX
	CRLF
	
	POPAD
	RET
_QueryCommodity ENDP
;功能 2
;模块功能:修改商品信息
;模块名称:_ModifyCommodity
;传入参数:无
;参数传入方式：无
;传出参数:无
;参数传出方式：无
;备注:无
_ModifyCommodity PROC C GA1:WORD,GB1:WORD,N:WORD
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
	MOV BX,GA1
	JMP _MC_3
_MC_2:
	MOV BX,GB1
	JMP _MC_3
_MC_3:
	CRLF
	WRITE MSG4
	READ in_goods
	CRLF
	CMP in_goods[1],0
	JE _MC_R					;输入回车
	
	MOV CX,N					;查询商品
_MC_LOOP1:						
	MOV SI,0
	MOV AL,in_goods[1]
	CBW
	MOV DX,AX					;DX控制第二层循环
	_MC_LOOP2:					;第二层循环，比较商品名称
		MOV AH,DS:[BX][SI]
		CMP AH,in_goods[SI+2]
		JNE _MC_UNFIND				;名称不同
		INC SI					
		DEC DX								
		JZ _MC_JUDGE				;找到商品,转JUDGE
		JMP _MC_LOOP2	
		
_MC_UNFIND:
	ADD BX,20
	DEC CX
	JNZ _MC_LOOP1
	JMP _MC_START					;未找到商品，重新输入商品名称
_MC_JUDGE:
	MOV AH,DS:[BX][SI]
	CMP AH,0
	JNE _MC_UNFIND						;商品名称为子集,属于未找到
	JMP _MC_FIND
_MC_FIND:

_MC_T1:
	CRLF
	WRITE Purchase_price
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+10]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T1
	CMP CX,-2
	JE _MC_T2
	MOV WORD PTR DS:[BX+10],CX
	CRLF
_MC_T2:
	CRLF
	WRITE Selling_price
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+12]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T2
	CMP CX,-2
	JE _MC_T3
	MOV WORD PTR DS:[BX+12],CX
	CRLF
_MC_T3:
	CRLF
	WRITE Total_purchases
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+14]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T3
	CMP CX,-2
	JE _MC_T4
	MOV WORD PTR DS:[BX+14],CX
	CRLF
_MC_T4:
	CRLF
	WRITE Sold_quantity
	OUT1 ':'
	MOVSX EAX,WORD PTR DS:[BX+16]
	CALL PRINTAX
	OUT1 '>'
	CALL INPUT_NEW_INFO
	CMP CX,-1
	JE _MC_T4
	CMP CX,-2
	JE _MC_R
	MOV WORD PTR DS:[BX+16],CX
	CRLF
	
_MC_R:
	POPAD
	RET
_ModifyCommodity ENDP
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
;功能 3
;模块功能:计算平均利润率
;模块名称:_AVERAGR_PROFIT
;传入参数:无
;参数传入方式
;传出参数:无
;参数传出方式：无
;备注:无
_AVERAGR_PROFIT PROC C GA1:WORD,GB1:WORD,N:WORD
	PUSHA
	MOV BX, GA1
	MOV SI, N																					
LOOP_1:
	MOVSX EAX, WORD PTR [BX][12]	;售价
	MOVSX EDX, WORD PTR [BX][16]	;售出数
	IMUL EAX, EDX					;销售额

	MOVSX ECX, WORD PTR [BX][10]	;进价
	MOVSX EDX, WORD PTR [BX][14]	;进货量
	IMUL ECX, EDX					;成本

	SUB EAX, ECX
	IMUL EAX, 100
	CDQ
	IDIV ECX

	PUSH AX						;商店1商品利润率进栈
	
	SUB BX,GA1
	ADD BX,GB1
	MOVSX EAX, WORD PTR [BX][12]
	MOVSX EDX, WORD PTR [BX][16]
	IMUL EAX, EDX

	MOVSX ECX, WORD PTR [BX][10]
	MOVSX EDX, WORD PTR [BX][14]
	IMUL ECX, EDX
	
	SUB EAX, ECX
	IMUL EAX, 100
	CDQ
	IDIV ECX
	
	POP CX						;商店2商品利润率出栈
	ADD AX,CX
	
	SAR AX, 1					;计算平均利润率
	
	SUB BX,GB1
	ADD BX,GA1
	MOV WORD PTR [BX][18], AX

	ADD EBX, 20
	DEC SI

	JNZ LOOP_1
	POPA
	RET
_AVERAGR_PROFIT ENDP

;功能4 
;模块功能:计算利润率排名
;模块名称:_PROFIT_RANKING
;传入参数:无
;参数传入方式:无
;传出参数:无
;参数传出方式：无
;备注:无


_PROFIT_RANKING PROC C GA1:WORD,GB1:WORD,N:BYTE
	PUSHA		;保护现场
	MOV AL, N
	MOV BX, GA1
	LOOP_2:
		MOV AH, N		;内层循环计数
		MOV CX, 0		;计数器，大于该利润的商品数量
		MOV DI, GA1

		LOOP_3:
			MOV DX, WORD PTR DS:[DI][18]
			CMP DX, WORD PTR [BX][18]

			JNG CONTINUE
			INC CX

		CONTINUE:
			ADD DI, 20
			
			DEC AH
			JNZ LOOP_3
		INC CX
		PUSH BX
		SUB BX,GA1
		ADD BX,GB1
		MOV WORD PTR [BX][18], CX
		POP BX
		ADD BX, 20

		DEC AL
		JNZ LOOP_2
	POPA
	RET

_PROFIT_RANKING ENDP
;功能5 
;模块功能:输出商品信息
;模块名称:_PRINT_IFO
;传入参数:0,1,(0代表输出shop1信息，1代表输出shop2信息）
;参数传入方式:al
;传出参数:无
;参数传出方式：无
;备注:;如果入口参数为0，输出shop1信息（利润率），入口参数为1， 输出shop2信息（排名）,al为传参寄存器

_PRINT_IFO PROC C GA1:WORD,GB1:WORD,N:WORD
	PUSHA
_PT_START:	
	WRITE SelectShop
	CRLF
	MOV AH,01H
	INT 21H
	CMP AL,'1'					;选择商店1
	JE CALL_1
	CMP AL,'2'
	JE CALL_2					;选择商店2
	JMP _PT_START				;输入错误
CALL_1:
	;输出店铺名称
	WRITE S1
	CRLF
	;输出标题栏
	WRITE Product_name
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Purchase_price
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Selling_price
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Total_purchases
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Sold_quantity
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE  Profit_rate
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII
	;输出标题栏的换行
	CRLF

	;循环输出shop1信息，循环条件为bp
	MOV CX, N
	MOV BX, GA1
	START__PRINT_IFO:
		;首先输出商品名称
		CALL WRITE_TEN_CHAR
		MOV AL, ' '
		MOV AH, 3
		CALL PRINTASCII
		;将2个数字有符号数字转换为ascii，并输出
		MOVSX EAX, WORD PTR DS:[BX][10]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 7
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][12]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 10
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][14]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 12
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][16]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 12
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][18]
		CALL PRINTAX
		

		;输出空格
		CRLF
		ADD BX, 20
		DEC CX
		JNZ START__PRINT_IFO
	JMP EXIT_FUN
CALL_2:
	;输出店铺名称
	WRITE S2
	CRLF
	;输出标题栏

	WRITE Product_name
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Purchase_price
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Selling_price
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Total_purchases
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE Sold_quantity
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII

	WRITE  Ranking
	MOV AL, ' '
	MOV AH, 2
	CALL PRINTASCII
	;输出标题栏的换行
	CRLF

	;循环输出shop1信息，循环条件为bp
	MOV CX,	N
	MOV BX, GB1
	START__PRINT_IFO_:
		;首先输出商品名称
		CALL WRITE_TEN_CHAR
		MOV AL, ' '
		MOV AH, 3
		CALL PRINTASCII

		;将2个数字有符号数字转换为ascii，并输出
		MOVSX EAX, WORD PTR DS:[BX][10]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 7
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][12]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 10
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][14]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 12
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][16]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 12
		CALL PRINTASCII

		MOVSX EAX, WORD PTR DS:[BX][18]
		CALL PRINTAX
		

		;输出空格
		CRLF
		ADD BX, 20
		DEC CX
		JNZ START__PRINT_IFO_

	JMP EXIT_FUN
EXIT_FUN:
	POPA
	RET
_PRINT_IFO ENDP

;函数write_ten_char用于输出连续的10个字符，bx为起始字符偏移地址
;调用方法
;MOV BX, OFFSET GA1
;LEA BX, GA1
;（GA1为ds段的变量名）
WRITE_TEN_CHAR PROC
	;现场保护
	PUSH BX
	PUSH DX
	PUSH AX
	;初始化循环条件
	MOV DH, 10
	;开始循环
	START_PRINT:
		;调用系统功能输出
		MOV DL, DS:[BX]
		MOV AH, 2
		INT 21H

		INC BX
		DEC DH
		JNZ START_PRINT
	POP AX
	POP DX
	POP BX
	RET
WRITE_TEN_CHAR ENDP
_TEXT ENDS  
	END 

