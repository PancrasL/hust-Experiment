`timescale 1ns / 1ps
module counter_top(CP,CLR,M,LD,D,C,B,A,QD,QC,QB,QA,Qcc);
input CP,CLR,M,LD;//CLR,LD低电平有效
input D,C,B,A;
output reg QD,QC,QB,QA;
output reg Qcc=0;
wire CP_N;
divider d(CP,CP_N);
counter c1(CP_N,CLR,M,LD,D,C,B,A,QD,QC,QB,QA,Qcc);
endmodule
