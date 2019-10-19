`timescale 1ns / 1ps
module dynamic_scan(clk,  seg, an);
input clk;              // 系统时钟
output [7:0] seg;  		// 分别对应CA、CB、CC、CD、CE、CF、CG和DP
output [7:0] an;        // 8位数码管片选信号
wire clk_N;
wire [2:0]num;
wire [3:0]code;
divider #(50000)(clk,clk_N);
counter(clk_N,num);
decoder3_8(num,an);
rom8x4(num,code);
pattern(code,seg);
endmodule
