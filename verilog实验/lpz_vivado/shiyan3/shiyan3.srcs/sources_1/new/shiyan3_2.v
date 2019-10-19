module counter(clk, out);
input clk;                    // 计数时钟
output reg [2:0] out;             // 计数值

initial begin
    out=0;
end
always @(posedge clk)  begin  // 在时钟上升沿计数器加1
                           // 功能实现
    out=out+1;
end                           
endmodule
