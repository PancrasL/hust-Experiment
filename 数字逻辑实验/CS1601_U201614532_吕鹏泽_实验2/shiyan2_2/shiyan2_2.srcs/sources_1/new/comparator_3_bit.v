`timescale 1ns / 1ps
module comparator_3_bit(A,B,F1,F2,F3);
input [2:0] A;
input [2:0] B;
output F1,F2,F3;
wire O1,O2,O3;
comparator C3(A[2],B[2],O3);
comparator C2(A[1],B[1],O2);
comparator C1(A[0],B[0],O1);
assign F1=(O3&{A[2]})|(!O3&O2&{A[1]})|(!O3&!O2&O1&{A[0]});//A>B包括：第2位不同且A[2]=1或第2位相同，第1位不同且A[1]=1或第2、1位相同，第0位不同且A=1
assign F2=!O3&!O2&!O1;
assign F3=!F1&!F2;
endmodule
