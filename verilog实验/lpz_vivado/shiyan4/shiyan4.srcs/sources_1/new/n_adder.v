`timescale 1ns / 1ns
module adder(a, b, c);
parameter N = 8;      // 1Hz��ʱ��,N=fclk/fclk_N
input [N-1:0] a;                      // ϵͳʱ��
input [N-1:0] b;
output [N-1:0] c;

assign c=a+b;                         
endmodule