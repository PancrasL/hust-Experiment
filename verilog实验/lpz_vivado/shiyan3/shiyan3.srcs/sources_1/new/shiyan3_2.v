module counter(clk, out);
input clk;                    // ����ʱ��
output reg [2:0] out;             // ����ֵ

initial begin
    out=0;
end
always @(posedge clk)  begin  // ��ʱ�������ؼ�������1
                           // ����ʵ��
    out=out+1;
end                           
endmodule
