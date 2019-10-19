`timescale 1ns / 1ps
module divider(clk, clk_N);
input clk;                      // ϵͳʱ��
output reg clk_N=0;                   // ��Ƶ���ʱ��
parameter N = 50_000_000;      // 1Hz��ʱ��,N=fclk/fclk_N
reg [31:0] counter=0;             /* ������������ͨ������ʵ�ַ�Ƶ��
                                   ����������0������(N/2-1)ʱ��
                                   ���ʱ�ӷ�ת������������ */
always @(posedge clk)  begin    // ʱ��������
    if(counter==N/2-1) begin//������N/2-1ʱ���з�ת
        counter<=0;
        clk_N<=~clk_N;
    end
    else counter=counter+1;
end                           
endmodule