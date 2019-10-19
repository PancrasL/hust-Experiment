`timescale 1ns / 1ps
module dynamic_scan(clk,  seg, an);
input clk;              // ϵͳʱ��
output [7:0] seg;  		// �ֱ��ӦCA��CB��CC��CD��CE��CF��CG��DP
output [7:0] an;        // 8λ�����Ƭѡ�ź�
wire clk_N;
wire [2:0]num;
wire [3:0]code;
divider #(50000)(clk,clk_N);
counter(clk_N,num);
decoder3_8(num,an);
rom8x4(num,code);
pattern(code,seg);
endmodule
