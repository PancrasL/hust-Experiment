`timescale 1ns / 1ps
module FSM(
    input clk,
    input rst,
    input start,
    input next_zero,
    output reg LD_SUM,
    output reg LD_NEXT,
    output reg SUM_SEL,
    output reg A_SEL,
    output reg NEXT_SEL,
    output reg done
    );
    parameter  IDLE = 0, ST1 = 1, ST2 = 2, ST3 = 3;
    reg [1:0]  c_state, n_state;
  // 3) Ê±ÐòÂß¼­
  always @ (posedge clk)
  begin: SEQ
    if (rst)
      c_state <= IDLE;
    else
      c_state <= n_state;
  end
  
  // 4) ×éºÏÂß¼­
  always @ (c_state,start,next_zero)
  begin: COMB
    case (c_state)
      IDLE: begin
                LD_SUM=0;
                LD_NEXT=0;
                SUM_SEL=0;
                NEXT_SEL=0;
                A_SEL=0;
                done=0;
                if(start==1)
                 n_state = ST1;
                else n_state=IDLE;
              end
      ST1: begin
                LD_SUM=1;
                LD_NEXT=0;
                SUM_SEL=1;
                NEXT_SEL=1;
                A_SEL=1;
                done=0;
                n_state=ST2;
              end
      ST2: begin
                LD_SUM=0;
                LD_NEXT=1;
                SUM_SEL=1;
                NEXT_SEL=1;
                A_SEL=0;
                done=0;
                if(next_zero==0)
                 n_state=ST1;
                else n_state=ST3;
              end
      ST3: begin
                LD_SUM=0;
                LD_NEXT=0;
                SUM_SEL=0;
                NEXT_SEL=0;
                A_SEL=0;
                done=1;
                if(start==0)
                 n_state=IDLE;
                else n_state=ST3;
              end
         default:
                begin
                    LD_SUM=0;
                    LD_NEXT=0;
                    SUM_SEL=0;
                    NEXT_SEL=0;
                    A_SEL=0;
                    done=0;
                    n_state=IDLE;
                 end
     endcase
  end
endmodule