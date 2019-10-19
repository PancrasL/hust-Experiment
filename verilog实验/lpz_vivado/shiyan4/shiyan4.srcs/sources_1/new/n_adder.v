`timescale 1ns / 1ns
module adder(a, b, c);
parameter N = 8;      // 1Hz的时钟,N=fclk/fclk_N
input [N-1:0] a;                      // 系统时钟
input [N-1:0] b;
output [N-1:0] c;

assign c=a+b;                         
endmodule