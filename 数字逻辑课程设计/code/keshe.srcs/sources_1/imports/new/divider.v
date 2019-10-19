`timescale 1ns / 1ps
module divider(clk, clk_N);
input clk;                      // 系统时钟
output reg clk_N=0;                   // 分频后的时钟
parameter N = 50_000_000;      // 1Hz的时钟,N=fclk/fclk_N
reg [31:0] counter=0;             /* 计数器变量，通过计数实现分频。
                                   当计数器从0计数到(N/2-1)时，
                                   输出时钟翻转，计数器清零 */
always @(posedge clk)  begin    // 时钟上升沿
    if(counter==N/2-1) begin//计数到N/2-1时进行反转
        counter<=0;
        clk_N<=~clk_N;
    end
    else counter=counter+1;
end                           
endmodule