`timescale 1ns / 1ns
module register(clk,load,D,rst,Q);
parameter N=8;
input clk;
input load;
input rst;
input [N-1:0] D;
output reg [N-1:0] Q=0;
always @(posedge clk) begin
    if(rst)
      Q<=0;
    else if(load)
      Q<=D;
    else Q<=Q;
end
endmodule