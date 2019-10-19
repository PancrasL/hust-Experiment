`timescale 1ns / 1ps
module FSM(clk,rst,cancel_sig,pay_sig,buy_sig,coin_type,cur_val,hold_led,charge_sig,hello_sig,can_buy,cur_state);
input clk,rst,cancel_sig,pay_sig,buy_sig,coin_type;
input [7:0] cur_val;
output reg hold_led,charge_sig,hello_sig;
parameter  START = 0, NOT = 1, BUY1=2,BUY2 = 3, CHARGE=4;
reg [2:0]  c_state, n_state;
output [2:0] cur_state;
assign cur_state=c_state;
// 3) 时序逻辑
output reg [1:0] can_buy;
  always @ (posedge clk)
  begin
    if (rst==0)
      c_state <= START;
    else
      c_state <= n_state;
  end
  
  // 4) 组合逻辑
  always @ (c_state,pay_sig,cancel_sig,cur_val)
  begin
    case (c_state)
    START: begin
    hold_led<=0;
    charge_sig<=0;
    hello_sig<=1;
    can_buy<=2'b00;
    if(pay_sig&&coin_type==0) n_state=NOT;//投币1元，进入到余额不足状态
    else if(pay_sig&&coin_type==1) n_state=BUY2;//投币10元，进入到购买2状态
    else n_state=START;//否则保持状态不变
    end
    NOT: begin
    hold_led<=1;
    can_buy<=2'b00;
    hello_sig<=0;
    if(cancel_sig) n_state<=CHARGE;
    else if(cur_val>=7'b0001010) n_state<=BUY2;//余额大于等于5元
    else if(cur_val>=7'b0000101) n_state<=BUY1;//余额大于等于2.5元
    else n_state<=NOT;//余额小于2.5元
    end
    BUY1: begin
    hold_led<=1;
    can_buy<=2'b01;
    hello_sig<=0;
    if(cancel_sig) n_state<=CHARGE;
    else if(buy_sig&&cur_val==7'b0000000) n_state<=START;//余额为0
    else if(cur_val>=7'b0001010) n_state<=BUY2;//余额大于等于5元
    else if(cur_val>=7'b0000101) n_state<=BUY1;//余额大于等于2.5元
    else n_state=NOT;//余额小于2.5元
    end
    BUY2: begin
    hold_led<=1;
    can_buy<=2'b10;
    hello_sig<=0;
    if(cancel_sig) n_state<=CHARGE;
    else if(buy_sig&&cur_val==7'b0000000) n_state<=START;//有购买信号并且购买后余额为0
    else if(cur_val>=7'b0001010) n_state<=BUY2;//余额大于等于5元
    else if(cur_val>=7'b0000101) n_state<=BUY1;//余额大于等于2.5元
    else n_state<=NOT;//余额小于2.5元
    end
    CHARGE: begin
    charge_sig<=1;//找零信号，同时作为余额模块的清零信号
    hello_sig<=0;
    n_state<=START;
    end
     endcase
  end
endmodule