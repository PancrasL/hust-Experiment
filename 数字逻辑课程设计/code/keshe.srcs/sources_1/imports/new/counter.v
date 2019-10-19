`timescale 1ns / 1ps
module counter(clk, out);
input clk;                    // 计数时钟
output reg [2:0] out;             // 计数值
parameter N=3;
initial begin
    out=0;
end
always @(posedge clk)  begin  // 在时钟上升沿计数器加1
    if(out>=N) out<=0;
    else out<=out+1;
end                           
endmodule
