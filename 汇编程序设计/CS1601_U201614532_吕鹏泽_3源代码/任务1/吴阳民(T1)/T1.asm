
;corporation@tortoiselala
;
;data:20180413
;partner:pengzeLv

	INCLUDE MACRO.LIB
	EXTRN  GA1:BYTE, GB1:BYTE, S1:BYTE, S2:BYTE, PrintASCII:NEAR, PRINTAX:NEAR
	PUBLIC AVERAGR_PROFIT, PROFIT_RANKING, PRINT_IFO

.386
DATA SEGMENT USE16 PARA PUBLIC 'D1'
	N EQU 10
	
	SORT_BUF DW N DUP(0)
	SORT_RAN DW N DUP(0)
	Product_name DB 'Product name', '$'
	Purchase_price DB 'Purchase price', '$'
	Selling_price DB 'Selling price', '$'
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


;功能 3
;模块功能:计算平均利润率
;模块名称:AVERAGR_PROFIT
;传入参数:无
;参数传入方式
;传出参数:无
;参数传出方式：无
;备注:无
AVERAGR_PROFIT PROC
	PUSHA																						;�������мĴ�������
	MOV EBX, 0
	LEA AX, GA1
	MOV SI, N																					;��һ��ѭ��ֵΪn�����Ʒ���n����Ʒ
LOOP_1:
	MOVSX EAX, WORD PTR GA1[EBX][12]
	MOVSX EDX, WORD PTR GA1[EBX][16]
	IMUL EAX, EDX

	MOVSX ECX, WORD PTR GA1[EBX][10]
	MOVSX EDX, WORD PTR GA1[EBX][14]
	IMUL ECX, EDX

	SUB EAX, ECX
	IMUL EAX, 100
	CDQ
	IDIV ECX

	MOV WORD PTR GA1[EBX][18], AX

	MOVSX EAX, WORD PTR GB1[EBX][12]
	MOVSX EDX, WORD PTR GB1[EBX][16]
	IMUL EAX, EDX

	MOVSX ECX, WORD PTR GB1[EBX][10]
	MOVSX EDX, WORD PTR GB1[EBX][14]
	IMUL ECX, EDX

	SUB EAX, ECX
	IMUL EAX, 100
	CDQ
	IDIV ECX

	MOV WORD PTR GB1[EBX][18], AX

	MOV AX, WORD PTR GA1[EBX][18]
	ADD AX, WORD PTR GB1[EBX][18]

	SAR AX, 1
	MOV WORD PTR GA1[EBX][18], AX

	ADD EBX, 20
	DEC SI

	JNZ LOOP_1

	POPA
	RET

AVERAGR_PROFIT ENDP

;功能4 
;模块功能:计算利润率排名
;模块名称:PROFIT_RANKING
;传入参数:无
;参数传入方式:无
;传出参数:无
;参数传出方式：无
;备注:使用冒泡排序，使用两个一维数组来分别保存平均利润率和原偏移地址，之后再根据偏移地址写入排名    perfect


PROFIT_RANKING PROC
	PUSHA																				;保护现场

	MOV AL, N
	MOV EBX, 0
	LOOP_2:
		MOV AH, N		;内层循环计数
		MOV CX, 0		;计数器，大于该利润的商品数量
		MOV EBP, 0

		LOOP_3:
			MOV DX, WORD PTR GA1[EBP][18]
			CMP DX, WORD PTR GA1[EBX][18]

			JNG CONTINUE
			INC CX

		CONTINUE:
			ADD EBP, 20
			
			DEC AH
			JNZ LOOP_3
		INC CX
		MOV WORD PTR GB1[EBX][18], CX
		ADD EBX, 20

		DEC AL
		JNZ LOOP_2

	POPA
	RET

PROFIT_RANKING ENDP


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

	CMP AL, 0
	JZ CALL_1
	JMP CALL_2
CALL_1:
	CALL PRINT_SHOP1
	JMP EXIT_FUN
CALL_2:
	CALL PRINT_SHOP2
	JMP EXIT_FUN
EXIT_FUN:
	POPA
	RET
PRINT_IFO ENDP

PRINT_SHOP1 PROC
	PUSH EAX
	PUSH SI
	PUSH BP
	;输出店铺名称
	WRITE S1
	CRLF
	;输出标题栏
	WRITE Product_name
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Purchase_price
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Selling_price
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Total_purchases
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Sold_quantity
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE  Profit_rate
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII
	;输出标题栏的换行
	CRLF

	;循环输出shop1信息，循环条件为bp
	MOV BP, N
	LEA SI, GA1
	START_PRINT_IFO:
		;首先输出商品名称
		MOV BX, SI
		CALL WRITE_TEN_CHAR
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII
		;将5个数字有符号数字转换为ascii，并输出
		MOVSX EAX, WORD PTR [SI][10]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][12]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][14]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][16]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][18]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		;输出空格
		CRLF
		ADD SI, 20
		DEC BP
		JNZ START_PRINT_IFO
	
	
	POP BP
	POP SI
	POP EAX
	RET
PRINT_SHOP1 ENDP



PRINT_SHOP2 PROC
	PUSHA
	;输出店铺名称
	WRITE S2
	CRLF
	;输出标题栏

	WRITE Product_name
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Purchase_price
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Selling_price
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Total_purchases
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE Sold_quantity
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII

	WRITE  Ranking
	MOV AL, ' '
	MOV AH, 5
	CALL PrintASCII
	;输出标题栏的换行
	CRLF

	;循环输出shop1信息，循环条件为bp
	MOV BP,	N
	LEA SI, GB1
	START_PRINT_IFO_:
		;首先输出商品名称
		MOV BX, SI
		CALL WRITE_TEN_CHAR
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		;将5个数字有符号数字转换为ascii，并输出
		MOVSX EAX, WORD PTR [SI][10]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][12]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][14]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][16]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		MOVSX EAX, WORD PTR [SI][18]
		CALL PRINTAX
		MOV AL, ' '
		MOV AH, 5
		CALL PrintASCII

		;输出空格
		CRLF
		ADD SI, 20
		DEC BP
		JNZ START_PRINT_IFO_

	POPA
	RET
PRINT_SHOP2 ENDP

;函数write_ten_char用于输出连续的10个字符，bx为起始字符偏移地址
;调用方法
;MOV BX, OFFSET GA1
;LEA BX, GA1
;（GA1为ds段的变量名）
WRITE_TEN_CHAR PROC
	;现场保护
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
	RET
WRITE_TEN_CHAR ENDP

CODE ENDS  
    END START
