module JK(
    input IJ,
    input IK,
    input CI,
    output reg Q,
    output wire QB
    );
initial begin Q=0;end
always @(negedge CI) begin
    case({IJ,IK})
        2'b00:Q<=Q;
        2'b01:Q<=0;
        2'b10:Q<=1;
        2'b11:Q<=!Q;
        default:Q<=0;
    endcase  
end
assign QB=!Q;
endmodule
