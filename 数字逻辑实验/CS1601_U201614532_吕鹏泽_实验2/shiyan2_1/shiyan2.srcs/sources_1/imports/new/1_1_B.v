`timescale 1ns / 1ps
module M1(
    input X,
    input CP,
    output reg Y,
    output Q0,
    output Q1
);
wire QB1;
 T T1(.IT(1),.CI(CP),.Q(Q0));
 T T2(.IT(X^Q0),.CI(CP),.Q(Q1),.QB(QB1));
always @ (*) begin
   Y<=!(QB1&X);
end
endmodule
