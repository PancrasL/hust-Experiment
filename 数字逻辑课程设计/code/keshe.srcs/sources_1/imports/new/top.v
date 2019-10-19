`timescale 1ns / 1ps
module top(clk,rst,buy_sig,pay_sig,coin_type,drink_type,cancel_sig,power_led,hold_led,take_led,charge_led,an,seg,c_state,not_buy_led,not_pay_led);
input clk,rst,buy_sig,pay_sig,coin_type,drink_type,cancel_sig;//ʱ�ӣ����ã������źţ�֧���źţ�Ͷ�����ͣ��������ͣ�ȡ���ź�
output power_led,hold_led,take_led,charge_led;//��Դ�ƣ�ռ�õƣ�ȡ���ƣ��˱ҵ�
output [7:0]an,seg;//��������
output not_buy_led,not_pay_led;
output [2:0]c_state;//��̬

wire not_buy_dis,not_pay_dis;//����2s�������źźͽ�ֹͶ���źţ������������ʾnob��not buy����nop��not pay��
assign not_buy_dis=not_buy_led;//����ָʾ�ƣ�������ʱ���й������2s
assign not_pay_dis=not_pay_led;//Ͷ����ֵָʾ�ƣ���������63Ԫʱ����Ͷ�һ���2s��ͬʱ��������

wire [7:0] drink_val,coin_val;//���ϼ۸�Ͷ��ֵ
assign drink_val=drink_type?8'b00001010:8'b00000101;//drink_type=0,drink_val=2.5Ԫ,drink_type=1,drink_val=5Ԫ
assign coin_val=coin_type?8'b00010100:8'b00000010;//coin_type=1,coin_val=10Ԫ,coin_type=0,coin_val=1Ԫ
assign power_led=rst;//rst=1����Դ�����������Դ����
wire buy_sig_f;
wire pay_sig_f;
fangdou fang1(clk,buy_sig,buy_sig_f);//���򰴼��ķ�����
fangdou fang2(clk,pay_sig,pay_sig_f);//Ͷ�Ұ����ķ�����

wire hello_sig;//hello_sig=1,���hello������������
wire [7:0] cur_val;//��ǰ���
wire charge_sig;
wire [1:0] can_buy;//�ɹ����ź�
FSM f(clk,rst,cancel_sig,pay_sig_f,buy_sig_f,coin_type,cur_val,hold_led,charge_sig,hello_sig,can_buy,c_state);
cur_money c(rst,charge_sig,pay_sig_f&cur_val<=8'b01111110,buy_sig_f,coin_val,drink_val,can_buy,cur_val);

wire clk_dis;//�������ʾ��ˢ��ʱ��
divider #(50000)d1(clk,clk_dis);
display dis(rst,clk_dis,hello_sig,charge_led,not_buy_dis,not_pay_dis,cur_val,an,seg);

wire take_sig;
assign take_sig=buy_sig_f&cur_val>=drink_val;//���յ������źŲ������������ϼ۸�ʱ����ȡ����
wire not_buy_sig;
assign not_buy_sig=buy_sig_f&cur_val<drink_val;
wire clk_led;
divider #(100_000_000)d2(clk,clk_led);//clk_ledƵ��Ϊ1Hz�����Ƶ���
led_inc take(clk_led,take_sig,take_led);//ȡ���ϵ�
led_inc charge(clk_led,charge_sig,charge_led);//�����
led_inc #(2)not_pay(clk_led,pay_sig_f&&cur_val>8'b01111110,not_pay_led);
led_inc #(2)not_buy(clk_led,not_buy_sig,not_buy_led);//����ָʾ��
endmodule

