`timescale 1ns / 1ps
module comparator_test();
reg a,b;
wire c;
comparator test(a,b,c);
initial begin 
a=0;
b=0;
#50 a=1;
#50 b=1;
#50 a=0;b=1;
$stop;
end
reg [3:0] x=4'b0000;
wire [3:0] xout;
wire [3:0] xout1;
not(xout,xout1);
wire outand,outor;
assign outand=&x;
assign outor=|x;
endmodule
