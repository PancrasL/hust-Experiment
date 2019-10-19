.386
.model   flat,stdcall
option   casemap:none

;MessageBox proto:DWORD,:DWORD,:DWORD,:DWORD
WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
printeax proto
_AVERAGR_PROFIT PROTO :DWORD,:DWORD
include      menuID.INC

include      D:\Masm32\INCLUDE\windows.inc
include      D:\Masm32\INCLUDE\user32.inc
include      D:\Masm32\INCLUDE\kernel32.inc
include      D:\Masm32\INCLUDE\gdi32.inc
include      D:\Masm32\INCLUDE\shell32.inc

includelib   D:\Masm32\LIB\user32.lib
includelib   D:\Masm32\LIB\kernel32.lib
includelib   D:\Masm32\LIB\gdi32.lib
includelib   D:\Masm32\LIB\shell32.lib

commodity	     struct
	commodity_name  db  10 dup(0)
	purchase_price 	dw 0
	selling_price	dw 0
	total_num 		dw 0
	sell_num		dw 0
	prt				dw 0
commodity      ends

.data
ClassName    db       'TryWinClass',0
AppName      db       'Commodity information management platform',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'CS1601 LVPENGZE',0
hInstance    dd       0
CommandLine  dd       0
N EQU 5
H DD 0
good	 commodity  <'BAG       ',15,32,89,70,0>
	     commodity  <'PEN       ',10,25,30,2,0>
	     commodity  <'HAT       ',13,25,25,20,0>
	     commodity  <'CUP       ',5,15,40,24,0>
	     commodity  <'JUICE     ',1,4,45,30,0>
		 
BUF DB ?,?,?,?		  

msg_name     db       '  Commodity_Name',0	;14
msg_pur  	 db       'Purchase_Price',0	;14
msg_sell     db       'Selling_Price',0		;13
msg_total_n  db       'Total_Num',0			;9
msg_sell_n   db       'Sell_Num',0			;8
msg_prt   	 db       'Prt',0				;3

flag DB 0
.code
Start:	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
		 MOV H,eax
		 ;invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
		 
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop 
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD ;40100Ah
	     LOCAL  hdc:HDC
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             ;;your code
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	    .IF     wParam == IDM_FILE_EXIT
		    invoke SendMessage,hWnd,WM_CLOSE,0,0
	    .ELSEIF wParam == IDM_FILE_LIST
		    invoke Display,hWnd;004011F4
			MOV flag,1
		.ELSEIF wParam == IDM_FILE_AVG
			invoke _AVERAGR_PROFIT,OFFSET good,5
			MOV flag,0

	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
		.ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display      proc   hWnd:DWORD
             XX     equ  10
             YY     equ  10
	     XX_GAP equ  140
	     YY_GAP equ  30
             LOCAL  hdc:HDC
             invoke GetDC,hWnd
             mov    hdc,eax
             invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_name,16
             invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_pur,14
             invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_sell,13
             invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_total_n,9
             invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_sell_n,8
             invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_prt,3
             ;;
			 MOV ECX,N							;商品总数
			 MOV EBX,YY+YY_GAP					;控制输出行间距
			 MOV EDX,OFFSET good[0]				;遍历所有商品
L1:	
			 MOV EDI,XX							;控制输出列间距
			 
			 PUSHAD
             invoke TextOut,hdc,EDI,EBX,EDX,10	;输出商品名称
			 POPAD
			 ADD EDI,XX_GAP
			 ADD EDX,10
			 
			 PUSHAD
			 MOVSX EAX,WORD PTR [EDX]
			 MOV ESI,OFFSET BUF
			 invoke printeax
             invoke TextOut,hdc,EDI,EBX,OFFSET BUF,4;输出商品进价
			 POPAD
			 ADD EDX,2
			 ADD EDI,XX_GAP
			 
             PUSHAD
			 MOVSX EAX,WORD PTR [EDX]
			 MOV ESI,OFFSET BUF
			 invoke printeax
             invoke TextOut,hdc,EDI,EBX,OFFSET BUF,4;输出商品售价
			 POPAD
			 ADD EDX,2
			 ADD EDI,XX_GAP
			 
             PUSHAD
			 MOVSX EAX,WORD PTR [EDX]
			 MOV ESI,OFFSET BUF
			 invoke printeax
             invoke TextOut,hdc,EDI,EBX,OFFSET BUF,4;输出商品进货量
			 POPAD
			 ADD EDX,2
			 ADD EDI,XX_GAP
			 
             PUSHAD
			 MOVSX EAX,WORD PTR [EDX]
			 MOV ESI,OFFSET BUF
			 invoke printeax
             invoke TextOut,hdc,EDI,EBX,OFFSET BUF,4;输出商品售出量
			 POPAD
			 ADD EDX,2
			 ADD EDI,XX_GAP
			 
             PUSHAD
			 MOVSX EAX,WORD PTR [EDX]
			 MOV ESI,OFFSET BUF
			 invoke printeax
             invoke TextOut,hdc,EDI,EBX,OFFSET BUF,4;输出商品利润率
			 POPAD
			 ADD EDX,2
			 
			 ADD EBX,YY_GAP
			 DEC ECX
			 JNZ L1
             ret
Display      endp

printeax PROC
	PUSHAD					    ;保护现场
	MOV EBX,10
	XOR CX,CX					;计数器清0
	CMP EAX,0
	JGE _LOP1
	NEG EAX
	MOV BYTE PTR [ESI],'-'
	INC ESI
_LOP1:							;(EAX)除以P，所得商->EAX，余数入栈，CX++，记录余数个数
	XOR EDX,EDX
	DIV EBX
	PUSH DX
	INC CX
	OR EAX,EAX
	JNZ _LOP1
_LOP2:							;从栈中弹出一位P进制数，并将该数转换成ASCII码后输出
	XOR EBX,EBX
	POP AX
	CMP AL,10
	JB _L1
	ADD AL,7
_L1:							;输出P进制数
	ADD AL,30H
	MOV BYTE PTR [ESI],AL
	INC EBX
	INC ESI
	LOOP _LOP2
	CMP EBX,4
	JL _P_L2
	JMP _EXIT1
_P_L2:	
	MOV BYTE PTR [ESI],' '
	INC ESI
	INC EBX
	CMP EBX,4
	JL _P_L2
_EXIT1:
	POPAD					;恢复现场
	RET
printeax ENDP


_AVERAGR_PROFIT PROC GA1:DWORD,N1:DWORD
	PUSHAD
	XOR EBX,EBX
	MOV EBX, GA1
	MOV ESI, 5																				
LOOP_1:
	MOVSX EAX, WORD PTR [EBX][12]	;售价
	MOVSX EDX, WORD PTR [EBX][16]	;售出数
	IMUL EAX, EDX					;销售额

	MOVSX ECX, WORD PTR [EBX][10]	;进价
	MOVSX EDX, WORD PTR [EBX][14]	;进货量
	IMUL ECX, EDX					;成本

	SUB EAX, ECX
	IMUL EAX, 100
	CDQ
	IDIV ECX
	
	MOV WORD PTR [EBX][18], AX

	ADD EBX, 20
	DEC ESI

	JNZ LOOP_1
	POPAD
	RET
_AVERAGR_PROFIT ENDP

             end  Start

		 
