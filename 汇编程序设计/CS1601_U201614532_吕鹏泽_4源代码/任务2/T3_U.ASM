.386

CODE SEGMENT USE16
	ASSUME CS:CODE
START:
	XOR AX,AX
	MOV DS,AX					;DS=0
	MOV SS,AX					;SS=0
	
	MOV SS,WORD PTR DS:[16H*4+2];新中断处理程序的cs
	MOV AX,WORD PTR SS:[4]
	CMP AX,0F1F1H
	JNE EXIT
	MOV AX,WORD PTR SS:[0]		;获取旧中断处理程序的ip
	MOV BX,WORD PTR SS:[2]		;获取旧中断处理程序的cs
	
	CLI							
	MOV DS:[16H*4],AX			;恢复旧中断的ip
	MOV DS:[16H*4+2],BX			;恢复旧中断的cs
	STI

EXIT:
	MOV AL,0
	MOV AH,31H
	INT 21H 
	
CODE ENDS

	END START

