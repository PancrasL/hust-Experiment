`timescale 1ns / 1ps
module top_test();
reg clk,rst,buy_sig,pay_sig,coin_type,drink_type,cancel_sig;
wire power_led,hold_led,take_led,charge_led;
wire [7:0]an,seg;
wire [2:0]c_state;
wire not_buy_led,not_pay_led;
top t(clk,rst,buy_sig,pay_sig,coin_type,drink_type,cancel_sig,power_led,hold_led,take_led,charge_led,an,seg,c_state,not_buy_led,not_pay_led);
initial begin
clk<=0;
rst<=1;
buy_sig<=0;
pay_sig<=0;
coin_type<=0;
drink_type<=0;
cancel_sig<=0;
#5 rst=0;
#5 rst=1;
coin_type=0;drink_type=0;
#50 pay_sig=1;#5 pay_sig=0;//Ͷ��1Ԫ*3��
#5 pay_sig=1;#5 pay_sig=0;
#5 pay_sig=1;#5 pay_sig=0;

#10coin_type=1;
#10 pay_sig=1;#5 pay_sig=0;//Ͷ��10Ԫ
//��ʱ���23Ԫ
#5 buy_sig=1;#5 buy_sig=0;//����2.5Ԫ��Ʒ
#10drink_type=1;
#20 buy_sig=1;#5 buy_sig=0;//����5Ԫ��Ʒ
#20 buy_sig=1;#5 buy_sig=0;
#20 buy_sig=1;#5 buy_sig=0;//��ʱ����
#20 cancel_sig=1;//�˱�
#5 cancel_sig=0;

#50 pay_sig=1;#5 pay_sig=0;//����ϵͳ
#10 rst=0;
#10 rst=1;
end
always begin
    #1.3 clk=!clk;
end
endmodule
