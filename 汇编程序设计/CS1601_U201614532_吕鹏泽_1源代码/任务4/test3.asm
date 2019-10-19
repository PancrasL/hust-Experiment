.386
STACK SEGMENT USE16 STACK
DB 200 DUP(0)
STACK ENDS
	DATA SEGMENT USE16
	XUEHAO DB 4 DUP(0);声明变量

	DATA ENDS
CODE SEGMENT USE16
ASSUME CS:CODE,DS:DATA,SS:STACK
START:
	MOV AX,DATA
	MOV DS,AX
	MOV AH,'4'
	MOV BX,OFFSET XUEHAO;
	MOV [BX],AH						;第一位数字'4'采用寄存器间接寻址方式

	MOV AH,'5'
	MOV SI,1						;SI作为变址寄存器，初值为1
	MOV XUEHAO[SI],AH					;第二位数字'5'采用变址寻址方式

	MOV AH,'3'
	LEA BX,XUEHAO						;XUEHAO的偏移地址送到BX寄存器中，作为基址寄存器
	MOV SI,2						;SI作为变址寄存器，初值为2
	MOV [BX][SI],AH						;第三位数字'3'采用基址加变址寻址方式

	MOV AH,'2'
	MOV DS:[3H],AH						;第四位数字采用直接寻址方式

	MOV AH,0						;程序结束
CODE ENDS
END START
