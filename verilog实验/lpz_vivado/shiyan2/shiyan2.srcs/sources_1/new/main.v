`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 10:42:06
// Design Name: 
// Module Name: main
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


module main(sw, seg, an, led);
input [15:0] sw;       // 16λ��������
output [7:0] seg;      // 7��������������͵�ƽ��Ч
output [7:0] an;       // 7�������Ƭѡ�źţ��͵�ƽ��Ч
output [15:0] led;     // 16λLED��ʾ
_7Seg_Driver_Decode(sw[15:0],seg[7:0],led[15:0]);
_7Seg_Driver_Choice(sw[15:13],an[7:0]);
endmodule

