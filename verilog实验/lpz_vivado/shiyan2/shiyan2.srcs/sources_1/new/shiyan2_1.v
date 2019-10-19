`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 08:26:44
// Design Name: 
// Module Name: shiyan2_1
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
module _7Seg_Driver_Direct(sw, seg, an, led);
	input  [15:0] sw;                          // 16λ��������
	output [7:0]  seg;  // 7��������������͵�ƽ��Ч
	output [7:0] an;                          // 7�������Ƭѡ�źţ��͵�ƽ��Ч
	output [15:0] led;                        // 16λLED��ʾ���ߵ�ƽ��Ч
	
	assign led = sw;
	assign seg=~sw[7:0];
	assign an=~sw[15:8];
endmodule
