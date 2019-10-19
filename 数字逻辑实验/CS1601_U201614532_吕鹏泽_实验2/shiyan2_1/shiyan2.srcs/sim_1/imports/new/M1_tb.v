`timescale 1ns / 1ps
module M1_test( );
reg clk_in;
reg X_in;
wire Y_out,Q0_out,Q1_out;
wire IT1;
M1 test(.X(X_in),.CP(clk_in),.Y(Y_out),.Q0(Q0_out),.Q1(Q1_out));
assign IT1=X_in^Q0_out;
initial begin
    X_in=0;
    clk_in=0;
end
always begin
    #5 clk_in<=!clk_in;
end
always begin
    #9.3 X_in=!X_in;
end
endmodule
