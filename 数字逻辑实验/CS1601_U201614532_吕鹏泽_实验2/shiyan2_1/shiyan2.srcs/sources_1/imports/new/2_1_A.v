`timescale 1ns / 1ps
module M2(
    input X,
    output reg Z=0,
    output Q1,Q2,Q3,Q4
    );
wire QB4;
reg temp1;
JK JK1(.IJ(1),.IK(1),.CI(X),.Q(Q1));
JK JK2(.IJ(QB4),.IK(1),.CI(Q1),.Q(Q2));
JK JK3(.IJ(1),.IK(1),.CI(Q2),.Q(Q3));
JK JK4(.IJ(temp1),.IK(1),.CI(Q1),.Q(Q4),.QB(QB4));
always @ (*) begin
    temp1=Q2&Q3;
    Z=Q4&Q1&X;
end
endmodule
