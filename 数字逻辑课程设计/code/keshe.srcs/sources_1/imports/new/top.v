`timescale 1ns / 1ps
module top(clk,rst,buy_sig,pay_sig,coin_type,drink_type,cancel_sig,power_led,hold_led,take_led,charge_led,an,seg,c_state,not_buy_led,not_pay_led);
input clk,rst,buy_sig,pay_sig,coin_type,drink_type,cancel_sig;//时钟，重置，购买信号，支付信号，投币类型，饮料类型，取消信号
output power_led,hold_led,take_led,charge_led;//电源灯，占用灯，取货灯，退币灯
output [7:0]an,seg;//数码管相关
output not_buy_led,not_pay_led;
output [2:0]c_state;//现态

wire not_buy_dis,not_pay_dis;//持续2s的余额不足信号和禁止投币信号，用于数码管显示nob（not buy）和nop（not pay）
assign not_buy_dis=not_buy_led;//余额不足指示灯，在余额不足时进行购买会亮2s
assign not_pay_dis=not_pay_led;//投币阈值指示灯，当余额大于63元时进行投币会亮2s，同时余额不会增加

wire [7:0] drink_val,coin_val;//饮料价格，投币值
assign drink_val=drink_type?8'b00001010:8'b00000101;//drink_type=0,drink_val=2.5元,drink_type=1,drink_val=5元
assign coin_val=coin_type?8'b00010100:8'b00000010;//coin_type=1,coin_val=10元,coin_type=0,coin_val=1元
assign power_led=rst;//rst=1，电源灯亮，否则电源灯灭
wire buy_sig_f;
wire pay_sig_f;
fangdou fang1(clk,buy_sig,buy_sig_f);//购买按键的防抖动
fangdou fang2(clk,pay_sig,pay_sig_f);//投币按键的防抖动

wire hello_sig;//hello_sig=1,输出hello，否则输出余额
wire [7:0] cur_val;//当前余额
wire charge_sig;
wire [1:0] can_buy;//可购买信号
FSM f(clk,rst,cancel_sig,pay_sig_f,buy_sig_f,coin_type,cur_val,hold_led,charge_sig,hello_sig,can_buy,c_state);
cur_money c(rst,charge_sig,pay_sig_f&cur_val<=8'b01111110,buy_sig_f,coin_val,drink_val,can_buy,cur_val);

wire clk_dis;//数码管显示的刷新时钟
divider #(50000)d1(clk,clk_dis);
display dis(rst,clk_dis,hello_sig,charge_led,not_buy_dis,not_pay_dis,cur_val,an,seg);

wire take_sig;
assign take_sig=buy_sig_f&cur_val>=drink_val;//当收到购买信号并且余额大于饮料价格时可以取饮料
wire not_buy_sig;
assign not_buy_sig=buy_sig_f&cur_val<drink_val;
wire clk_led;
divider #(100_000_000)d2(clk,clk_led);//clk_led频率为1Hz，控制灯亮
led_inc take(clk_led,take_sig,take_led);//取饮料灯
led_inc charge(clk_led,charge_sig,charge_led);//找零灯
led_inc #(2)not_pay(clk_led,pay_sig_f&&cur_val>8'b01111110,not_pay_led);
led_inc #(2)not_buy(clk_led,not_buy_sig,not_buy_led);//余额不足指示灯
endmodule

