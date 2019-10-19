`timescale 1ns / 1ps
module cur_money(rst,clear,pay_sig,buy_sig,coin_val,drink_val,can_buy,cur_val);
input pay_sig,buy_sig,rst,clear;
input [1:0] can_buy;
input [7:0] coin_val,drink_val;
output [7:0] cur_val;
reg [15:0] all_val,buy_val;//��Ͷ��ֵ���ܹ���ֵ
wire[15:0] sub_val;
assign sub_val=all_val-buy_val;
assign cur_val=sub_val[7:0];
initial begin
all_val=0;buy_val=0;
end
always @(negedge pay_sig,posedge clear,negedge rst) begin
    if(!rst||clear) all_val=0;//����ź�
    else all_val=all_val+{8'b00000000,coin_val};//�����ź�
end
always @(negedge buy_sig,posedge clear,negedge rst) begin
    if(!rst||clear) buy_val=0;//����ź�
    else begin//�����ź�
         if(can_buy==2'b10)//�ɹ���5Ԫ����
           buy_val=buy_val+{8'b00000000,drink_val};
         else if(can_buy==2'b01&&drink_val==8'b00000101)//�ɹ���2.5Ԫ����
           buy_val=buy_val+16'b0000000000000101;
         else buy_val=buy_val;
         end
    
end
endmodule
