`timescale 1ns / 1ps
module FSM(clk,rst,cancel_sig,pay_sig,buy_sig,coin_type,cur_val,hold_led,charge_sig,hello_sig,can_buy,cur_state);
input clk,rst,cancel_sig,pay_sig,buy_sig,coin_type;
input [7:0] cur_val;
output reg hold_led,charge_sig,hello_sig;
parameter  START = 0, NOT = 1, BUY1=2,BUY2 = 3, CHARGE=4;
reg [2:0]  c_state, n_state;
output [2:0] cur_state;
assign cur_state=c_state;
// 3) ʱ���߼�
output reg [1:0] can_buy;
  always @ (posedge clk)
  begin
    if (rst==0)
      c_state <= START;
    else
      c_state <= n_state;
  end
  
  // 4) ����߼�
  always @ (c_state,pay_sig,cancel_sig,cur_val)
  begin
    case (c_state)
    START: begin
    hold_led<=0;
    charge_sig<=0;
    hello_sig<=1;
    can_buy<=2'b00;
    if(pay_sig&&coin_type==0) n_state=NOT;//Ͷ��1Ԫ�����뵽����״̬
    else if(pay_sig&&coin_type==1) n_state=BUY2;//Ͷ��10Ԫ�����뵽����2״̬
    else n_state=START;//���򱣳�״̬����
    end
    NOT: begin
    hold_led<=1;
    can_buy<=2'b00;
    hello_sig<=0;
    if(cancel_sig) n_state<=CHARGE;
    else if(cur_val>=7'b0001010) n_state<=BUY2;//�����ڵ���5Ԫ
    else if(cur_val>=7'b0000101) n_state<=BUY1;//�����ڵ���2.5Ԫ
    else n_state<=NOT;//���С��2.5Ԫ
    end
    BUY1: begin
    hold_led<=1;
    can_buy<=2'b01;
    hello_sig<=0;
    if(cancel_sig) n_state<=CHARGE;
    else if(buy_sig&&cur_val==7'b0000000) n_state<=START;//���Ϊ0
    else if(cur_val>=7'b0001010) n_state<=BUY2;//�����ڵ���5Ԫ
    else if(cur_val>=7'b0000101) n_state<=BUY1;//�����ڵ���2.5Ԫ
    else n_state=NOT;//���С��2.5Ԫ
    end
    BUY2: begin
    hold_led<=1;
    can_buy<=2'b10;
    hello_sig<=0;
    if(cancel_sig) n_state<=CHARGE;
    else if(buy_sig&&cur_val==7'b0000000) n_state<=START;//�й����źŲ��ҹ�������Ϊ0
    else if(cur_val>=7'b0001010) n_state<=BUY2;//�����ڵ���5Ԫ
    else if(cur_val>=7'b0000101) n_state<=BUY1;//�����ڵ���2.5Ԫ
    else n_state<=NOT;//���С��2.5Ԫ
    end
    CHARGE: begin
    charge_sig<=1;//�����źţ�ͬʱ��Ϊ���ģ��������ź�
    hello_sig<=0;
    n_state<=START;
    end
     endcase
  end
endmodule