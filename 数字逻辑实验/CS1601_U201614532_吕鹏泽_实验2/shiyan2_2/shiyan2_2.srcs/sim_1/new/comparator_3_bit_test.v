`timescale 1ns / 1ps
module comparator_3_bit_test();
reg [2:0] A;
reg [2:0] B;
wire F3,F2,F1;
comparator_3_bit test(A,B,F1,F2,F3);
initial begin 
A=0;B=0;
for(A=0;A<8;A=A+1)begin
    for(B=0;B<7;)
        #5 B=B+1;
    B=7;
    #5;
end
end
endmodule
