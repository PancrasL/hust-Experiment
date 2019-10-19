`timescale 1ns / 1ps
module counter(clk, out);
input clk;                    // ����ʱ��
output reg [2:0] out;             // ����ֵ
parameter N=3;
initial begin
    out=0;
end
always @(posedge clk)  begin  // ��ʱ�������ؼ�������1
    if(out>=N) out<=0;
    else out<=out+1;
end                           
endmodule
