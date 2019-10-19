`timescale 1ns / 1ps
module display(rst,clk,hello_sig,charge_sig,not_buy_sig,not_pay_sig,cur_val,an,seg);
input rst,clk,hello_sig,charge_sig,not_buy_sig,not_pay_sig;
input [7:0] cur_val;
output [7:0] an;
output [7:0] seg;
wire [2:0] num1,num2,num;
assign num=!rst?3'b111:hello_sig?num1:num2;//��hello_sig==1,num��0������4������num��0������2
counter #(4)c1(clk,num1);
counter #(2)c2(clk,num2);
decoder3_8 d(num,an);//��numѡ�����������
seven_transfer t(hello_sig,charge_sig,not_buy_sig,not_pay_sig,cur_val,num,seg);//��num��hello_sigѡ���������������
endmodule
