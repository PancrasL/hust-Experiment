`timescale 1ns / 1ps
module led_inc(clk,led_sig,led);//��sig�źų���������ʱ��led�źų��ֳ���SECONDS��ĵ�ƽ�ź�
input clk,led_sig;
output led;
parameter SECONDS=4;//�յ�led_sigʱ����5s
reg [3:0] count=6;
assign led=count<SECONDS?1:0;//��ʱ��С��5s���������������
always @(posedge clk,posedge led_sig) begin//��ʱ��
if(led_sig) count<=0;
else if(count<SECONDS) count=count+1;
else count=count;
end
endmodule
