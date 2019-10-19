`timescale 10ns / 10ps
module counter_test();
reg CP,CLR,M,LD,D,C,B,A;
wire QD,QC,QB,QA,Qcc;
counter test(CP,CLR,M,LD,D,C,B,A,QD,QC,QB,QA,Qcc);
initial begin
{D,C,B,A}=4'b1101;
LD=1;
CLR=1;
CP=0;
M=1;
#20 CLR=0;
#2 CLR=1;
#20 LD=0;
#2 LD=1;
#40 M=0;
#20 CLR=0;
#2 CLR=1;
#20 LD=0;
#2 LD=1;
end
always begin
#0.5 CP=!CP;
end
endmodule
