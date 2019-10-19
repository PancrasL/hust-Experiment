`timescale 1ns / 1ps
module cur_money_test();
reg rst,clear,pay_sig,buy_sig;
reg [1:0]can_buy;
reg [7:0]drink_val,coin_val;
wire [7:0] cur_val;
cur_money test(rst,clear,pay_sig,buy_sig,coin_val,drink_val,can_buy,cur_val);
initial begin
rst=1;
pay_sig=0;buy_sig=0;coin_val=0;drink_val=8'b00000101;clear=0;can_buy=00;
#5 rst=0;//重置系统
#5 rst=1;
#5 coin_val=8'b00000010;
#5 pay_sig=1;#5 pay_sig=0;//投币1元
#5 pay_sig=1;#5 pay_sig=0;//投币1元
#5 pay_sig=1;#5 pay_sig=0;//投币1元
#5 coin_val=8'b00010100;#5 pay_sig=1;#5 pay_sig=0;//投币10元
#5 pay_sig=1;#5 pay_sig=0;//投币10元
#20 can_buy=2'b10;//可购买5元商品
#5 buy_sig=1;#5 buy_sig=0;//购买2.5元饮料
#5 drink_val=8'b00001010;#5 buy_sig=1;#5 buy_sig=0;//购买5元饮料
#5 can_buy=2'b00;//不可购买商品
#5 buy_sig=1;#5 buy_sig=0;//购买5元饮料不成功
#10 clear=1;#5 clear=0;//清空
end
endmodule
