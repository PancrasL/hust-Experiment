module pipe3b(
    input sig_nsyn,
    input clk,
    output reg q1=0,
    output reg q2=0,
    output reg sig_syn=0
      );
   always@(posedge clk) q2<=q1;
   always@(posedge clk) sig_syn<=q2;
   always@(posedge clk) q1<=sig_nsyn;     
endmodule
