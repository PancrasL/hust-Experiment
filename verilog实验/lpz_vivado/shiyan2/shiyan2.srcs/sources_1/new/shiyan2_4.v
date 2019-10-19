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
	input  [15:0] sw;                          // 16位拨动开关
	output [7:0]  seg;  // 7段数码管驱动，低电平有效
	output [7:0] an;                          // 7段数码管片选信号，低电平有效
	output [15:0] led;                        // 16位LED显示，高电平有效
	
	assign led=sw;
	_7Seg_Driver_Choice(sw[14:12],an);//选择亮的灯
	shiyan2_4_2(sw[3:0],sw[15],seg);//显示BCD码
	
endmodule
