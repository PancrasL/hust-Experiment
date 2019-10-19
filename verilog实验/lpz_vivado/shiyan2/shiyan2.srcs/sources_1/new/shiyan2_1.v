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
	input  [15:0] sw;                          // 16位拨动开关
	output [7:0]  seg;  // 7段数码管驱动，低电平有效
	output [7:0] an;                          // 7段数码管片选信号，低电平有效
	output [15:0] led;                        // 16位LED显示，高电平有效
	
	assign led = sw;
	assign seg=~sw[7:0];
	assign an=~sw[15:8];
endmodule
