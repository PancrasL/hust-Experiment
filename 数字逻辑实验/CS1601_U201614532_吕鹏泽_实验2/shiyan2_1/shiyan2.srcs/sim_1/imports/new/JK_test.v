`timescale 1ns / 1ps
module JK_test();
reg J;
reg K;
reg clk;
wire Q;
wire QB;
JK test(J,K,clk,Q,QB);
initial begin J=0;K=0;clk=0;end
always begin
    #5 J=~J;
end;
always begin
    #4 K=~K;
end;
always begin
    #3 clk=~clk;
end;
endmodule
