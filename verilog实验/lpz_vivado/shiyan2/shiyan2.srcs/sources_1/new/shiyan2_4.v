`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 10:57:47
// Design Name: 
// Module Name: shiyan2_4
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module shiyan2_4(sw, seg, an, led);
	input  [15:0] sw;                          // 16λ��������
	output [7:0]  seg;  // 7��������������͵�ƽ��Ч
	output [7:0] an;                          // 7�������Ƭѡ�źţ��͵�ƽ��Ч
	output [15:0] led;                        // 16λLED��ʾ���ߵ�ƽ��Ч
	
	assign led=sw;
	_7Seg_Driver_Choice(sw[14:12],an);//ѡ�����ĵ�
	shiyan2_4_2(sw[3:0],sw[15],seg);//��ʾBCD��
	
endmodule
