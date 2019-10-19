`timescale 1ns / 1ps
module counter_mod_8_test();
reg CP,M;
wire QD,QC,QB,QA,Qcc;
counter_mod_8 test(CP,M,QD,QC,QB,QA,Qcc);
initial begin
CP=0;
M=1;
#1100 M=0;
end
always begin
    #10 CP=!CP;
end
endmodule
