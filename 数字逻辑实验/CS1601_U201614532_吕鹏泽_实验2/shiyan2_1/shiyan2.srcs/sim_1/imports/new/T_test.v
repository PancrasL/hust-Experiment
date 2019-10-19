`timescale 1ns / 1ps
module T_test();
reg clk;
reg IT;
wire Q,QB;

initial begin
clk=0;
IT=0;
end
always begin
    #5 clk=!clk;
end
always begin
    #8 IT=!IT;
end
T test(IT,clk,Q,QB);
endmodule
