.386
STACK SEGMENT USE16 STACK
DB 200 DUP(0)
STACK ENDS
	DATA SEGMENT USE16
	XUEHAO DB 4 DUP(0);��������

	DATA ENDS
CODE SEGMENT USE16
ASSUME CS:CODE,DS:DATA,SS:STACK
START:
	MOV AX,DATA
	MOV DS,AX
	MOV AH,'4'
	MOV BX,OFFSET XUEHAO;
	MOV [BX],AH						;��һλ����'4'���üĴ������Ѱַ��ʽ

	MOV AH,'5'
	MOV SI,1						;SI��Ϊ��ַ�Ĵ�������ֵΪ1
	MOV XUEHAO[SI],AH					;�ڶ�λ����'5'���ñ�ַѰַ��ʽ

	MOV AH,'3'
	LEA BX,XUEHAO						;XUEHAO��ƫ�Ƶ�ַ�͵�BX�Ĵ����У���Ϊ��ַ�Ĵ���
	MOV SI,2						;SI��Ϊ��ַ�Ĵ�������ֵΪ2
	MOV [BX][SI],AH						;����λ����'3'���û�ַ�ӱ�ַѰַ��ʽ

	MOV AH,'2'
	MOV DS:[3H],AH						;����λ���ֲ���ֱ��Ѱַ��ʽ

	MOV AH,0						;�������
CODE ENDS
END START
