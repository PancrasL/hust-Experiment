`timescale 1ns / 1ns
module auto_caculation(
    input start,
    input clk,
    input rst,
    output done,
    output [31:0]sum_out
    );
    wire LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,next_zero;
    
FSM t2(clk,rst,start,next_zero,LD_SUM,LD_NEXT,SUM_SEL,A_SEL,NEXT_SEL,done);
M1 t1(clk,rst,LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,next_zero,sum_out);

endmodule
