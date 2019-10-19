`timescale 1ns / 1ps
module auto_caculate_test();
reg start=0,rst=0,clk=0;
wire done;
wire [31:0] sum_out;
auto_caculation test(start,clk,rst,done,sum_out);
initial begin
    #50 rst=1;
    #50 rst=0;
    #50 start=1;
    #500 start=0;
end
always begin
   #20 clk=!clk;
end
endmodule
