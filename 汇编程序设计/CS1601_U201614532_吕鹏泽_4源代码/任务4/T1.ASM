

	INCLUDE MACRO.LIB
	EXTRN  GA1:BYTE, GB1:BYTE, S1:BYTE, S2:BYTE, PrintASCII:NEAR, PRINTAX:NEAR,N:ABS,NEWKEY:BYTE
	PUBLIC PRINT_IFO

.386
DATA SEGMENT USE16 PARA PUBLIC 'D1'
	SelectShop DB '1.SHOP1 2.SHOP2','$'
	Product_name DB 'Product', '$'
	Purchase_price DB '  cost  ', '$'
	Selling_price DB '  Price  ', '$'
	Total_purchases DB 'Total purchases', '$'
	Sold_quantity DB 'Sold Quantity', '$'
	Profit_rate DB 'Profit rate', '$'
	Ranking DB 'Ranking', '$'
DATA ENDS
STACK SEGMENT USE16 PARA STACK 'STACK'
	DB 200 DUP(0)
STACK ENDS

CODE SEGMENT USE16 PARA PUBLIC 'CODE'	
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:  
    MOV AX, DATA
    MOV DS, AX  

;功能5 
;模块功能:输出商品信息
;模块名称:PRINT_IFO
;传入参数:0,1,(0代表输出shop1信息，1代表输出shop2信息）
;参数传入方式:al
;传出参数:无
;参数传出方式：无
;备注:;如果入口参数为0，输出shop1信息（利润率），入口参数为1， 输出shop2信息（排名）,al为传参寄存器

PRINT_IFO PROC
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
	LEA BX, GA1
	START_PRINT_IFO:
		;首先输出商品名称
		CALL WRITE_TEN_CHAR
		MOV AL, ' '
		MOV AH, 3
		CALL PRINTASCII
		;将2个数字有符号数字转换为ascii，并输出
		MOVSX EAX, WORD PTR DS:[BX][10]
		MOVSX DI,NEWKEY
		XOR AX,DI
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
		JNZ START_PRINT_IFO
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
	LEA BX, GB1
	START_PRINT_IFO_:
		;首先输出商品名称
		CALL WRITE_TEN_CHAR
		MOV AL, ' '
		MOV AH, 3
		CALL PRINTASCII

		;将2个数字有符号数字转换为ascii，并输出
		MOVSX EAX, WORD PTR DS:[BX][10]
		MOVSX DI,NEWKEY
		XOR AX,DI
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
		JNZ START_PRINT_IFO_

	JMP EXIT_FUN
EXIT_FUN:
	POPA
	RET
PRINT_IFO ENDP

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

CODE ENDS  
    END START
