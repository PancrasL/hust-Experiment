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
input [15:0] sw;       // 16位拨动开关
output [7:0] seg;      // 7段数码管驱动，低电平有效
output [7:0] an;       // 7段数码管片选信号，低电平有效
output [15:0] led;     // 16位LED显示
_7Seg_Driver_Decode(sw[15:0],seg[7:0],led[15:0]);
_7Seg_Driver_Choice(sw[15:13],an[7:0]);
endmodule

