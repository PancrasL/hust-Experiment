`timescale 1ns / 1ps
module led_inc_test();
reg clk,sig;
wire led;
led_inc test(clk,sig,led);
initial begin
clk=0;
#5 sig=1;
#5 sig=0;
#500 sig=1;
#5 sig=0;
end
always begin
    #1.3 clk=!clk;
end
endmodule
