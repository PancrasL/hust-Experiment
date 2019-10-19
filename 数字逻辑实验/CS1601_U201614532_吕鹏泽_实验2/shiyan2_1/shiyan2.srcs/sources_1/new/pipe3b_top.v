`timescale 1ns / 1ps
module pipe3b_top(
   input sig_nsyn,
   input clk,
   output q1,q2,sig_syn
);
wire clk_N;
divider d(clk,clk_N);
pipe3b p(sig_nsyn,clk_N,q1,q2,sig_syn);
endmodule
