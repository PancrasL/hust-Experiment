module pipe3b(
    input sig_nsyn,
    input clk,
    output q1,
    output q2,
    output sig_syn
      );
    reg q1;
    reg q2;
    reg sig_syn;
   always@(posedge clk) q2=q1;
   always@(posedge clk) sig_syn=q2;
   always@(posedge clk) q1=sig_nsyn;     
endmodule
