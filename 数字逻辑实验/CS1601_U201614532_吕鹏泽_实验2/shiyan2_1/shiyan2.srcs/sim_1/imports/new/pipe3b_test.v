`timescale 1ns / 1ps
module pipe3b_test();
reg sig_nsyn;
reg clk;
wire q1;
wire q2;
wire sig_syn;
pipe3b test(sig_nsyn,clk,q1,q2,sig_syn);
initial begin sig_nsyn=0;clk=0; end
always begin
    #5 clk<=!clk;
end
always begin
    #7 sig_nsyn<=!sig_nsyn;
end
endmodule
