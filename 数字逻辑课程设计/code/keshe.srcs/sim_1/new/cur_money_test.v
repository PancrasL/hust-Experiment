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
#5 rst=0;//����ϵͳ
#5 rst=1;
#5 coin_val=8'b00000010;
#5 pay_sig=1;#5 pay_sig=0;//Ͷ��1Ԫ
#5 pay_sig=1;#5 pay_sig=0;//Ͷ��1Ԫ
#5 pay_sig=1;#5 pay_sig=0;//Ͷ��1Ԫ
#5 coin_val=8'b00010100;#5 pay_sig=1;#5 pay_sig=0;//Ͷ��10Ԫ
#5 pay_sig=1;#5 pay_sig=0;//Ͷ��10Ԫ
#20 can_buy=2'b10;//�ɹ���5Ԫ��Ʒ
#5 buy_sig=1;#5 buy_sig=0;//����2.5Ԫ����
#5 drink_val=8'b00001010;#5 buy_sig=1;#5 buy_sig=0;//����5Ԫ����
#5 can_buy=2'b00;//���ɹ�����Ʒ
#5 buy_sig=1;#5 buy_sig=0;//����5Ԫ���ϲ��ɹ�
#10 clear=1;#5 clear=0;//���
end
endmodule
