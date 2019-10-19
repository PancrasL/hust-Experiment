`timescale 1ns / 1ps
module shiyan3_3(clk,,led);
    input clk;
    output [2:0] led;
    wire clk_N;
    wire [2:0]out;
    divider(clk,clk_N);
    counter(clk_N,out[2:0]);
    assign led=out;
endmodule
