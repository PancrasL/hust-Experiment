`timescale 1ns / 1ps
module M1(clk,rst,LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,next_zero,sum_out);
input clk,rst,LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL;
output next_zero;
output [31:0] sum_out;//寄存器SUM的输出
wire [31:0] data;//从存储器中获得的数据
wire [3:0] addr;//存储器需要读取的单元地址
wire [31:0] M1_out;//MUX_NEXT的输出
wire [31:0] M3_out;//MUX_SUM的输出
wire [31:0] NEXT_out;//寄存器R_NEXT的输出
wire [31:0] A1_out;//加法器ADDER1的输出
wire [31:0] A2_out;//加法器ADDER2的输出
defparam ROM.N=32,ROM.M=4;//4位寻址线，32位数据
romN #(32)ROM(.addr(addr),.data(data));

mux #(32)NEXT_MUX(NEXT_SEL,data,0,M1_out);
mux #(4)A_MUX(A_SEL,A1_out[3:0],NEXT_out[3:0],addr);
mux #(32)SUM_MUX(SUM_SEL,A2_out,0,M3_out);

register #(32)SUM_R(clk,LD_SUM,M3_out,rst,sum_out);
register #(32)NEXT_R(clk,LD_NEXT,M1_out,rst,NEXT_out);
adder #(32)ADDER1(1,NEXT_out,A1_out);
adder #(32)ADDER2(sum_out,data,A2_out);

compare #(32)COMP(M1_out,0,next_zero);

endmodule

