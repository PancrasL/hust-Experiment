`timescale 1ns / 1ps
module pipe3b_test();
reg sig_in=0;
reg clk=0;
wire q1,q2,sig_out;
pipe3b test(sig_in,clk,q1,q2,sig_out);
always begin
    #5  clk<=!clk;
end
always begin
    #7 sig_in<=!sig_in;
end
endmodule
