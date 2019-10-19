`timescale 1ns / 1ps
module counter_mod_8(CP,M,QD,QC,QB,QA,Qcc);
input CP,M;
output QD,QC,QB,QA;
output Qcc;
wire T;
wire LD;
wire [3:0] rst;
wire CP_N;
divider d(CP,CP_N);
assign rst=M?4'b0010:4'b1001;
assign LD=M?(QD&!QC&!QB&QA):(!QD&!QC&QB&!QA);
assign Qcc=M?(!QD&!QC&QB&!QA):(QD&!QC&!QB&QA);
counter c1(CP_N,1,M,!LD,rst[3],rst[2],rst[1],rst[0],QD,QC,QB,QA,T);
endmodule