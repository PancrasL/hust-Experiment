`timescale 1ns / 1ns
module compare(a,b,c);
parameter N=8;
input [N-1:0] a;
input [N-1:0] b;
output reg c;
always @(a or b) begin
    if(a==b)
      c=1;
    else c=0;
end 
endmodule
