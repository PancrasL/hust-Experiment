`timescale 1ns / 1ns
module mux(sel,op1,op2,out);
parameter N=8;
input sel;
input [N-1:0] op1;
input [N-1:0] op2;
output reg [N-1:0] out;
always @ (sel or op1 or op2) begin
    if(sel)
      out=op1;
    else out=op2;
 end
endmodule