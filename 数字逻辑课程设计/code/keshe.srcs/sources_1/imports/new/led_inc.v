`timescale 1ns / 1ps
module led_inc(clk,led_sig,led);//当sig信号出现上升沿时，led信号出现持续SECONDS秒的电平信号
input clk,led_sig;
output led;
parameter SECONDS=4;//收到led_sig时灯亮5s
reg [3:0] count=6;
assign led=count<SECONDS?1:0;//当时间小于5s，灯亮，否则灯灭
always @(posedge clk,posedge led_sig) begin//计时器
if(led_sig) count<=0;
else if(count<SECONDS) count=count+1;
else count=count;
end
endmodule
