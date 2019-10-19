`timescale 1ns / 1ps
module divider(clk, clk_N);
input clk;                      // 系统时钟
output reg clk_N;                   // 分频后的时钟
parameter N = 100_000_000;      // 1Hz的时钟,N=fclk/fclk_N
reg [31:0] counter;             /* 计数器变量，通过计数实现分频。
                                   当计数器从0计数到(N/2-1)时，
                                   输出时钟翻转，计数器清零 */
always @(posedge clk)  begin    // 时钟上升沿
    counter=counter+1;
    if(counter==N/2-1) begin
        counter=0;
        clk_N=~clk_N;
    end
end                           
endmodule