module T(
    input IT,
    input CI,
    output reg Q,
    output wire QB
    );
initial begin Q<=0; end
assign QB=!Q;
always @ (negedge CI)  begin
   Q=Q^IT;
end
endmodule
