`timescale 1ns / 1ps
module M2_test();
reg X;
wire Z;
wire Q1,Q2,Q3,Q4;
M2 test(X,Z,Q1,Q2,Q3,Q4);
initial begin
    X=0;
end
always begin
    #5 X=!X;
end
endmodule
