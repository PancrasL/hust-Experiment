`timescale 1ns / 1ps
module display_test();
reg clk,hello_sig;
reg [5:0] cur_val;
wire [7:0] an,seg;
display test(clk,hello_sig,cur_val,an,seg);
initial begin
clk<=0;
#5 hello_sig<=1;
cur_val<=6'b110011;
#500 hello_sig<=0;
end
always begin
#1.3 clk=!clk;
end
endmodule
