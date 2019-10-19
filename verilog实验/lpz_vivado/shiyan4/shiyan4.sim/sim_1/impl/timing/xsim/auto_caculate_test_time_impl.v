// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
// Date        : Tue Jun 12 11:49:22 2018
// Host        : DESKTOP-4FFCO4E running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               E:/verilog/lpz_vivado/shiyan4/shiyan4.sim/sim_1/impl/timing/xsim/auto_caculate_test_time_impl.v
// Design      : auto_caculation
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module FSM
   (out,
    O,
    \Q_reg[11] ,
    \Q_reg[15] ,
    \Q_reg[19] ,
    \Q_reg[23] ,
    \Q_reg[27] ,
    \Q_reg[31] ,
    sum_out_OBUF,
    NEXT_ZERO,
    start_IBUF,
    CO,
    SS,
    CLK);
  output [2:0]out;
  output [3:0]O;
  output [3:0]\Q_reg[11] ;
  output [3:0]\Q_reg[15] ;
  output [3:0]\Q_reg[19] ;
  output [3:0]\Q_reg[23] ;
  output [3:0]\Q_reg[27] ;
  output [3:0]\Q_reg[31] ;
  input [27:0]sum_out_OBUF;
  input NEXT_ZERO;
  input start_IBUF;
  input [0:0]CO;
  input [0:0]SS;
  input CLK;

  wire CLK;
  wire [0:0]CO;
  wire \FSM_onehot_c_state[0]_i_1_n_0 ;
  wire \FSM_onehot_c_state[1]_i_1_n_0 ;
  wire \FSM_onehot_c_state[3]_i_1_n_0 ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_c_state_reg_n_0_[0] ;
  wire NEXT_ZERO;
  wire [3:0]O;
  wire \Q[12]_i_2_n_0 ;
  wire \Q[12]_i_3_n_0 ;
  wire \Q[12]_i_4_n_0 ;
  wire \Q[12]_i_5_n_0 ;
  wire \Q[16]_i_2_n_0 ;
  wire \Q[16]_i_3_n_0 ;
  wire \Q[16]_i_4_n_0 ;
  wire \Q[16]_i_5_n_0 ;
  wire \Q[20]_i_2_n_0 ;
  wire \Q[20]_i_3_n_0 ;
  wire \Q[20]_i_4_n_0 ;
  wire \Q[20]_i_5_n_0 ;
  wire \Q[24]_i_2_n_0 ;
  wire \Q[24]_i_3_n_0 ;
  wire \Q[24]_i_4_n_0 ;
  wire \Q[24]_i_5_n_0 ;
  wire \Q[28]_i_2_n_0 ;
  wire \Q[28]_i_3_n_0 ;
  wire \Q[28]_i_4_n_0 ;
  wire \Q[28]_i_5_n_0 ;
  wire \Q[4]_i_2_n_0 ;
  wire \Q[4]_i_3_n_0 ;
  wire \Q[4]_i_4_n_0 ;
  wire \Q[4]_i_5_n_0 ;
  wire \Q[8]_i_2_n_0 ;
  wire \Q[8]_i_3_n_0 ;
  wire \Q[8]_i_4_n_0 ;
  wire \Q[8]_i_5_n_0 ;
  wire [3:0]\Q_reg[11] ;
  wire \Q_reg[12]_i_1_n_0 ;
  wire [3:0]\Q_reg[15] ;
  wire \Q_reg[16]_i_1_n_0 ;
  wire [3:0]\Q_reg[19] ;
  wire \Q_reg[20]_i_1_n_0 ;
  wire [3:0]\Q_reg[23] ;
  wire \Q_reg[24]_i_1_n_0 ;
  wire [3:0]\Q_reg[27] ;
  wire [3:0]\Q_reg[31] ;
  wire \Q_reg[4]_i_1_n_0 ;
  wire \Q_reg[8]_i_1_n_0 ;
  wire [0:0]SS;
  (* RTL_KEEP = "yes" *) wire [2:0]out;
  wire start_IBUF;
  wire [27:0]sum_out_OBUF;
  wire [2:0]\NLW_Q_reg[12]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_Q_reg[16]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_Q_reg[20]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_Q_reg[24]_i_1_CO_UNCONNECTED ;
  wire [3:0]\NLW_Q_reg[28]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_Q_reg[4]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_Q_reg[8]_i_1_CO_UNCONNECTED ;

  LUT3 #(
    .INIT(8'h32)) 
    \FSM_onehot_c_state[0]_i_1 
       (.I0(\FSM_onehot_c_state_reg_n_0_[0] ),
        .I1(start_IBUF),
        .I2(out[2]),
        .O(\FSM_onehot_c_state[0]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_c_state[1]_i_1 
       (.I0(start_IBUF),
        .I1(\FSM_onehot_c_state_reg_n_0_[0] ),
        .I2(NEXT_ZERO),
        .I3(out[1]),
        .O(\FSM_onehot_c_state[1]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hF888)) 
    \FSM_onehot_c_state[3]_i_1 
       (.I0(NEXT_ZERO),
        .I1(out[1]),
        .I2(start_IBUF),
        .I3(out[2]),
        .O(\FSM_onehot_c_state[3]_i_1_n_0 ));
  (* FSM_ENCODED_STATES = "ST2:0100,ST1:0010,IDLE:0001,ST3:1000" *) 
  (* KEEP = "yes" *) 
  FDSE #(
    .INIT(1'b1)) 
    \FSM_onehot_c_state_reg[0] 
       (.C(CLK),
        .CE(1'b1),
        .D(\FSM_onehot_c_state[0]_i_1_n_0 ),
        .Q(\FSM_onehot_c_state_reg_n_0_[0] ),
        .S(SS));
  (* FSM_ENCODED_STATES = "ST2:0100,ST1:0010,IDLE:0001,ST3:1000" *) 
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_c_state_reg[1] 
       (.C(CLK),
        .CE(1'b1),
        .D(\FSM_onehot_c_state[1]_i_1_n_0 ),
        .Q(out[0]),
        .R(SS));
  (* FSM_ENCODED_STATES = "ST2:0100,ST1:0010,IDLE:0001,ST3:1000" *) 
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_c_state_reg[2] 
       (.C(CLK),
        .CE(1'b1),
        .D(out[0]),
        .Q(out[1]),
        .R(SS));
  (* FSM_ENCODED_STATES = "ST2:0100,ST1:0010,IDLE:0001,ST3:1000" *) 
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_c_state_reg[3] 
       (.C(CLK),
        .CE(1'b1),
        .D(\FSM_onehot_c_state[3]_i_1_n_0 ),
        .Q(out[2]),
        .R(SS));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[12]_i_2 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[11]),
        .O(\Q[12]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[12]_i_3 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[10]),
        .O(\Q[12]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[12]_i_4 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[9]),
        .O(\Q[12]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[12]_i_5 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[8]),
        .O(\Q[12]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[16]_i_2 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[15]),
        .O(\Q[16]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[16]_i_3 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[14]),
        .O(\Q[16]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[16]_i_4 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[13]),
        .O(\Q[16]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[16]_i_5 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[12]),
        .O(\Q[16]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[20]_i_2 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[19]),
        .O(\Q[20]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[20]_i_3 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[18]),
        .O(\Q[20]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[20]_i_4 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[17]),
        .O(\Q[20]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[20]_i_5 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[16]),
        .O(\Q[20]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[24]_i_2 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[23]),
        .O(\Q[24]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[24]_i_3 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[22]),
        .O(\Q[24]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[24]_i_4 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[21]),
        .O(\Q[24]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[24]_i_5 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[20]),
        .O(\Q[24]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[28]_i_2 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[27]),
        .O(\Q[28]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[28]_i_3 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[26]),
        .O(\Q[28]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[28]_i_4 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[25]),
        .O(\Q[28]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[28]_i_5 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[24]),
        .O(\Q[28]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[4]_i_2 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[3]),
        .O(\Q[4]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[4]_i_3 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[2]),
        .O(\Q[4]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[4]_i_4 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[1]),
        .O(\Q[4]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[4]_i_5 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[0]),
        .O(\Q[4]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[8]_i_2 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[7]),
        .O(\Q[8]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[8]_i_3 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[6]),
        .O(\Q[8]_i_3_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[8]_i_4 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[5]),
        .O(\Q[8]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \Q[8]_i_5 
       (.I0(out[1]),
        .I1(out[0]),
        .I2(sum_out_OBUF[4]),
        .O(\Q[8]_i_5_n_0 ));
  CARRY4 \Q_reg[12]_i_1 
       (.CI(\Q_reg[8]_i_1_n_0 ),
        .CO({\Q_reg[12]_i_1_n_0 ,\NLW_Q_reg[12]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(\Q_reg[15] ),
        .S({\Q[12]_i_2_n_0 ,\Q[12]_i_3_n_0 ,\Q[12]_i_4_n_0 ,\Q[12]_i_5_n_0 }));
  CARRY4 \Q_reg[16]_i_1 
       (.CI(\Q_reg[12]_i_1_n_0 ),
        .CO({\Q_reg[16]_i_1_n_0 ,\NLW_Q_reg[16]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(\Q_reg[19] ),
        .S({\Q[16]_i_2_n_0 ,\Q[16]_i_3_n_0 ,\Q[16]_i_4_n_0 ,\Q[16]_i_5_n_0 }));
  CARRY4 \Q_reg[20]_i_1 
       (.CI(\Q_reg[16]_i_1_n_0 ),
        .CO({\Q_reg[20]_i_1_n_0 ,\NLW_Q_reg[20]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(\Q_reg[23] ),
        .S({\Q[20]_i_2_n_0 ,\Q[20]_i_3_n_0 ,\Q[20]_i_4_n_0 ,\Q[20]_i_5_n_0 }));
  CARRY4 \Q_reg[24]_i_1 
       (.CI(\Q_reg[20]_i_1_n_0 ),
        .CO({\Q_reg[24]_i_1_n_0 ,\NLW_Q_reg[24]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(\Q_reg[27] ),
        .S({\Q[24]_i_2_n_0 ,\Q[24]_i_3_n_0 ,\Q[24]_i_4_n_0 ,\Q[24]_i_5_n_0 }));
  CARRY4 \Q_reg[28]_i_1 
       (.CI(\Q_reg[24]_i_1_n_0 ),
        .CO(\NLW_Q_reg[28]_i_1_CO_UNCONNECTED [3:0]),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(\Q_reg[31] ),
        .S({\Q[28]_i_2_n_0 ,\Q[28]_i_3_n_0 ,\Q[28]_i_4_n_0 ,\Q[28]_i_5_n_0 }));
  CARRY4 \Q_reg[4]_i_1 
       (.CI(CO),
        .CO({\Q_reg[4]_i_1_n_0 ,\NLW_Q_reg[4]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(O),
        .S({\Q[4]_i_2_n_0 ,\Q[4]_i_3_n_0 ,\Q[4]_i_4_n_0 ,\Q[4]_i_5_n_0 }));
  CARRY4 \Q_reg[8]_i_1 
       (.CI(\Q_reg[4]_i_1_n_0 ),
        .CO({\Q_reg[8]_i_1_n_0 ,\NLW_Q_reg[8]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(\Q_reg[11] ),
        .S({\Q[8]_i_2_n_0 ,\Q[8]_i_3_n_0 ,\Q[8]_i_4_n_0 ,\Q[8]_i_5_n_0 }));
endmodule

module M1
   (sum_out_OBUF,
    NEXT_ZERO,
    CO,
    out,
    clk_IBUF_BUFG,
    O,
    \FSM_onehot_c_state_reg[2] ,
    \FSM_onehot_c_state_reg[2]_0 ,
    \FSM_onehot_c_state_reg[2]_1 ,
    \FSM_onehot_c_state_reg[2]_2 ,
    \FSM_onehot_c_state_reg[2]_3 ,
    \FSM_onehot_c_state_reg[2]_4 );
  output [31:0]sum_out_OBUF;
  output NEXT_ZERO;
  output [0:0]CO;
  input [1:0]out;
  input clk_IBUF_BUFG;
  input [3:0]O;
  input [3:0]\FSM_onehot_c_state_reg[2] ;
  input [3:0]\FSM_onehot_c_state_reg[2]_0 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_1 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_2 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_3 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_4 ;

  wire [0:0]CO;
  wire [3:0]\FSM_onehot_c_state_reg[2] ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_0 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_1 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_2 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_3 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_4 ;
  wire NEXT_ZERO;
  wire [3:0]O;
  wire R_NEXT_n_2;
  wire R_NEXT_n_3;
  wire R_NEXT_n_4;
  wire R_NEXT_n_5;
  wire clk_IBUF_BUFG;
  wire [1:0]out;
  wire [31:0]sum_out_OBUF;

  register R_NEXT
       (.CO(CO),
        .NEXT_ZERO(NEXT_ZERO),
        .O({R_NEXT_n_2,R_NEXT_n_3,R_NEXT_n_4,R_NEXT_n_5}),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .out(out),
        .sum_out_OBUF(sum_out_OBUF[3:0]));
  register_0 R_SUM
       (.\FSM_onehot_c_state_reg[2] (O),
        .\FSM_onehot_c_state_reg[2]_0 (\FSM_onehot_c_state_reg[2] ),
        .\FSM_onehot_c_state_reg[2]_1 (\FSM_onehot_c_state_reg[2]_0 ),
        .\FSM_onehot_c_state_reg[2]_2 (\FSM_onehot_c_state_reg[2]_1 ),
        .\FSM_onehot_c_state_reg[2]_3 (\FSM_onehot_c_state_reg[2]_2 ),
        .\FSM_onehot_c_state_reg[2]_4 (\FSM_onehot_c_state_reg[2]_3 ),
        .\FSM_onehot_c_state_reg[2]_5 (\FSM_onehot_c_state_reg[2]_4 ),
        .O({R_NEXT_n_2,R_NEXT_n_3,R_NEXT_n_4,R_NEXT_n_5}),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .out(out[0]),
        .sum_out_OBUF(sum_out_OBUF));
endmodule

(* ECO_CHECKSUM = "ad223e51" *) 
(* NotValidForBitStream *)
module auto_caculation
   (start,
    clk,
    rst,
    done,
    sum_out);
  input start;
  input clk;
  input rst;
  output done;
  output [31:0]sum_out;

  wire A_SEL;
  wire LD_NEXT;
  wire NEXT_ZERO;
  wire clk;
  wire clk_IBUF;
  wire clk_IBUF_BUFG;
  wire done;
  wire rst;
  wire rst_IBUF;
  wire start;
  wire start_IBUF;
  wire [31:0]sum_out;
  wire [31:0]sum_out_OBUF;
  wire t1_n_33;
  wire t2_n_0;
  wire t2_n_10;
  wire t2_n_11;
  wire t2_n_12;
  wire t2_n_13;
  wire t2_n_14;
  wire t2_n_15;
  wire t2_n_16;
  wire t2_n_17;
  wire t2_n_18;
  wire t2_n_19;
  wire t2_n_20;
  wire t2_n_21;
  wire t2_n_22;
  wire t2_n_23;
  wire t2_n_24;
  wire t2_n_25;
  wire t2_n_26;
  wire t2_n_27;
  wire t2_n_28;
  wire t2_n_29;
  wire t2_n_3;
  wire t2_n_30;
  wire t2_n_4;
  wire t2_n_5;
  wire t2_n_6;
  wire t2_n_7;
  wire t2_n_8;
  wire t2_n_9;

initial begin
 $sdf_annotate("auto_caculate_test_time_impl.sdf",,,,"tool_control");
end
  BUFG clk_IBUF_BUFG_inst
       (.I(clk_IBUF),
        .O(clk_IBUF_BUFG));
  IBUF clk_IBUF_inst
       (.I(clk),
        .O(clk_IBUF));
  OBUF done_OBUF_inst
       (.I(t2_n_0),
        .O(done));
  IBUF rst_IBUF_inst
       (.I(rst),
        .O(rst_IBUF));
  IBUF start_IBUF_inst
       (.I(start),
        .O(start_IBUF));
  OBUF \sum_out_OBUF[0]_inst 
       (.I(sum_out_OBUF[0]),
        .O(sum_out[0]));
  OBUF \sum_out_OBUF[10]_inst 
       (.I(sum_out_OBUF[10]),
        .O(sum_out[10]));
  OBUF \sum_out_OBUF[11]_inst 
       (.I(sum_out_OBUF[11]),
        .O(sum_out[11]));
  OBUF \sum_out_OBUF[12]_inst 
       (.I(sum_out_OBUF[12]),
        .O(sum_out[12]));
  OBUF \sum_out_OBUF[13]_inst 
       (.I(sum_out_OBUF[13]),
        .O(sum_out[13]));
  OBUF \sum_out_OBUF[14]_inst 
       (.I(sum_out_OBUF[14]),
        .O(sum_out[14]));
  OBUF \sum_out_OBUF[15]_inst 
       (.I(sum_out_OBUF[15]),
        .O(sum_out[15]));
  OBUF \sum_out_OBUF[16]_inst 
       (.I(sum_out_OBUF[16]),
        .O(sum_out[16]));
  OBUF \sum_out_OBUF[17]_inst 
       (.I(sum_out_OBUF[17]),
        .O(sum_out[17]));
  OBUF \sum_out_OBUF[18]_inst 
       (.I(sum_out_OBUF[18]),
        .O(sum_out[18]));
  OBUF \sum_out_OBUF[19]_inst 
       (.I(sum_out_OBUF[19]),
        .O(sum_out[19]));
  OBUF \sum_out_OBUF[1]_inst 
       (.I(sum_out_OBUF[1]),
        .O(sum_out[1]));
  OBUF \sum_out_OBUF[20]_inst 
       (.I(sum_out_OBUF[20]),
        .O(sum_out[20]));
  OBUF \sum_out_OBUF[21]_inst 
       (.I(sum_out_OBUF[21]),
        .O(sum_out[21]));
  OBUF \sum_out_OBUF[22]_inst 
       (.I(sum_out_OBUF[22]),
        .O(sum_out[22]));
  OBUF \sum_out_OBUF[23]_inst 
       (.I(sum_out_OBUF[23]),
        .O(sum_out[23]));
  OBUF \sum_out_OBUF[24]_inst 
       (.I(sum_out_OBUF[24]),
        .O(sum_out[24]));
  OBUF \sum_out_OBUF[25]_inst 
       (.I(sum_out_OBUF[25]),
        .O(sum_out[25]));
  OBUF \sum_out_OBUF[26]_inst 
       (.I(sum_out_OBUF[26]),
        .O(sum_out[26]));
  OBUF \sum_out_OBUF[27]_inst 
       (.I(sum_out_OBUF[27]),
        .O(sum_out[27]));
  OBUF \sum_out_OBUF[28]_inst 
       (.I(sum_out_OBUF[28]),
        .O(sum_out[28]));
  OBUF \sum_out_OBUF[29]_inst 
       (.I(sum_out_OBUF[29]),
        .O(sum_out[29]));
  OBUF \sum_out_OBUF[2]_inst 
       (.I(sum_out_OBUF[2]),
        .O(sum_out[2]));
  OBUF \sum_out_OBUF[30]_inst 
       (.I(sum_out_OBUF[30]),
        .O(sum_out[30]));
  OBUF \sum_out_OBUF[31]_inst 
       (.I(sum_out_OBUF[31]),
        .O(sum_out[31]));
  OBUF \sum_out_OBUF[3]_inst 
       (.I(sum_out_OBUF[3]),
        .O(sum_out[3]));
  OBUF \sum_out_OBUF[4]_inst 
       (.I(sum_out_OBUF[4]),
        .O(sum_out[4]));
  OBUF \sum_out_OBUF[5]_inst 
       (.I(sum_out_OBUF[5]),
        .O(sum_out[5]));
  OBUF \sum_out_OBUF[6]_inst 
       (.I(sum_out_OBUF[6]),
        .O(sum_out[6]));
  OBUF \sum_out_OBUF[7]_inst 
       (.I(sum_out_OBUF[7]),
        .O(sum_out[7]));
  OBUF \sum_out_OBUF[8]_inst 
       (.I(sum_out_OBUF[8]),
        .O(sum_out[8]));
  OBUF \sum_out_OBUF[9]_inst 
       (.I(sum_out_OBUF[9]),
        .O(sum_out[9]));
  M1 t1
       (.CO(t1_n_33),
        .\FSM_onehot_c_state_reg[2] ({t2_n_7,t2_n_8,t2_n_9,t2_n_10}),
        .\FSM_onehot_c_state_reg[2]_0 ({t2_n_11,t2_n_12,t2_n_13,t2_n_14}),
        .\FSM_onehot_c_state_reg[2]_1 ({t2_n_15,t2_n_16,t2_n_17,t2_n_18}),
        .\FSM_onehot_c_state_reg[2]_2 ({t2_n_19,t2_n_20,t2_n_21,t2_n_22}),
        .\FSM_onehot_c_state_reg[2]_3 ({t2_n_23,t2_n_24,t2_n_25,t2_n_26}),
        .\FSM_onehot_c_state_reg[2]_4 ({t2_n_27,t2_n_28,t2_n_29,t2_n_30}),
        .NEXT_ZERO(NEXT_ZERO),
        .O({t2_n_3,t2_n_4,t2_n_5,t2_n_6}),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .out({LD_NEXT,A_SEL}),
        .sum_out_OBUF(sum_out_OBUF));
  FSM t2
       (.CLK(clk_IBUF_BUFG),
        .CO(t1_n_33),
        .NEXT_ZERO(NEXT_ZERO),
        .O({t2_n_3,t2_n_4,t2_n_5,t2_n_6}),
        .\Q_reg[11] ({t2_n_7,t2_n_8,t2_n_9,t2_n_10}),
        .\Q_reg[15] ({t2_n_11,t2_n_12,t2_n_13,t2_n_14}),
        .\Q_reg[19] ({t2_n_15,t2_n_16,t2_n_17,t2_n_18}),
        .\Q_reg[23] ({t2_n_19,t2_n_20,t2_n_21,t2_n_22}),
        .\Q_reg[27] ({t2_n_23,t2_n_24,t2_n_25,t2_n_26}),
        .\Q_reg[31] ({t2_n_27,t2_n_28,t2_n_29,t2_n_30}),
        .SS(rst_IBUF),
        .out({t2_n_0,LD_NEXT,A_SEL}),
        .start_IBUF(start_IBUF),
        .sum_out_OBUF(sum_out_OBUF[31:4]));
endmodule

module register
   (NEXT_ZERO,
    CO,
    O,
    out,
    sum_out_OBUF,
    clk_IBUF_BUFG);
  output NEXT_ZERO;
  output [0:0]CO;
  output [3:0]O;
  input [1:0]out;
  input [3:0]sum_out_OBUF;
  input clk_IBUF_BUFG;

  wire [0:0]CO;
  wire NEXT_ZERO;
  wire [3:0]NEXT_out;
  wire [3:0]O;
  wire \Q[0]_i_1_n_0 ;
  wire \Q[0]_i_2_n_0 ;
  wire \Q[0]_i_3_n_0 ;
  wire \Q[0]_i_4_n_0 ;
  wire \Q[0]_i_5_n_0 ;
  wire \Q[0]_i_6_n_0 ;
  wire \Q[0]_i_7_n_0 ;
  wire \Q[0]_i_8_n_0 ;
  wire \Q[0]_i_9_n_0 ;
  wire \Q[1]_i_1_n_0 ;
  wire \Q[2]_i_1_n_0 ;
  wire \Q[3]_i_1_n_0 ;
  wire clk_IBUF_BUFG;
  wire [1:0]out;
  wire [3:0]sum_out_OBUF;
  wire [2:0]\NLW_Q_reg[0]_i_1_CO_UNCONNECTED ;

  LUT4 #(
    .INIT(16'h0001)) 
    \FSM_onehot_c_state[3]_i_2 
       (.I0(NEXT_out[2]),
        .I1(NEXT_out[3]),
        .I2(NEXT_out[1]),
        .I3(NEXT_out[0]),
        .O(NEXT_ZERO));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h80002289)) 
    \Q[0]_i_1 
       (.I0(NEXT_out[1]),
        .I1(NEXT_out[0]),
        .I2(NEXT_out[2]),
        .I3(out[0]),
        .I4(NEXT_out[3]),
        .O(\Q[0]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h1800180020400000)) 
    \Q[0]_i_2 
       (.I0(NEXT_out[0]),
        .I1(NEXT_out[3]),
        .I2(NEXT_out[2]),
        .I3(NEXT_out[1]),
        .I4(out[1]),
        .I5(out[0]),
        .O(\Q[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h2202220202140000)) 
    \Q[0]_i_3 
       (.I0(NEXT_out[1]),
        .I1(NEXT_out[3]),
        .I2(NEXT_out[2]),
        .I3(NEXT_out[0]),
        .I4(out[1]),
        .I5(out[0]),
        .O(\Q[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h80C580C5018B0000)) 
    \Q[0]_i_4 
       (.I0(NEXT_out[0]),
        .I1(NEXT_out[1]),
        .I2(NEXT_out[2]),
        .I3(NEXT_out[3]),
        .I4(out[1]),
        .I5(out[0]),
        .O(\Q[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h8022802200890000)) 
    \Q[0]_i_5 
       (.I0(NEXT_out[1]),
        .I1(NEXT_out[0]),
        .I2(NEXT_out[2]),
        .I3(NEXT_out[3]),
        .I4(out[1]),
        .I5(out[0]),
        .O(\Q[0]_i_5_n_0 ));
  LUT4 #(
    .INIT(16'h666A)) 
    \Q[0]_i_6 
       (.I0(\Q[0]_i_2_n_0 ),
        .I1(sum_out_OBUF[3]),
        .I2(out[0]),
        .I3(out[1]),
        .O(\Q[0]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'h666A)) 
    \Q[0]_i_7 
       (.I0(\Q[0]_i_3_n_0 ),
        .I1(sum_out_OBUF[2]),
        .I2(out[0]),
        .I3(out[1]),
        .O(\Q[0]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'h666A)) 
    \Q[0]_i_8 
       (.I0(\Q[0]_i_4_n_0 ),
        .I1(sum_out_OBUF[1]),
        .I2(out[0]),
        .I3(out[1]),
        .O(\Q[0]_i_8_n_0 ));
  LUT4 #(
    .INIT(16'h666A)) 
    \Q[0]_i_9 
       (.I0(\Q[0]_i_5_n_0 ),
        .I1(sum_out_OBUF[0]),
        .I2(out[0]),
        .I3(out[1]),
        .O(\Q[0]_i_9_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h8001C85B)) 
    \Q[1]_i_1 
       (.I0(NEXT_out[0]),
        .I1(NEXT_out[1]),
        .I2(out[0]),
        .I3(NEXT_out[2]),
        .I4(NEXT_out[3]),
        .O(\Q[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h22020214)) 
    \Q[2]_i_1 
       (.I0(NEXT_out[1]),
        .I1(NEXT_out[3]),
        .I2(NEXT_out[2]),
        .I3(NEXT_out[0]),
        .I4(out[0]),
        .O(\Q[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h06801000)) 
    \Q[3]_i_1 
       (.I0(out[0]),
        .I1(NEXT_out[0]),
        .I2(NEXT_out[3]),
        .I3(NEXT_out[2]),
        .I4(NEXT_out[1]),
        .O(\Q[3]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(out[1]),
        .D(\Q[0]_i_1_n_0 ),
        .Q(NEXT_out[0]),
        .R(1'b0));
  CARRY4 \Q_reg[0]_i_1 
       (.CI(1'b0),
        .CO({CO,\NLW_Q_reg[0]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({\Q[0]_i_2_n_0 ,\Q[0]_i_3_n_0 ,\Q[0]_i_4_n_0 ,\Q[0]_i_5_n_0 }),
        .O(O),
        .S({\Q[0]_i_6_n_0 ,\Q[0]_i_7_n_0 ,\Q[0]_i_8_n_0 ,\Q[0]_i_9_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(out[1]),
        .D(\Q[1]_i_1_n_0 ),
        .Q(NEXT_out[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(out[1]),
        .D(\Q[2]_i_1_n_0 ),
        .Q(NEXT_out[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(out[1]),
        .D(\Q[3]_i_1_n_0 ),
        .Q(NEXT_out[3]),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "register" *) 
module register_0
   (sum_out_OBUF,
    out,
    O,
    clk_IBUF_BUFG,
    \FSM_onehot_c_state_reg[2] ,
    \FSM_onehot_c_state_reg[2]_0 ,
    \FSM_onehot_c_state_reg[2]_1 ,
    \FSM_onehot_c_state_reg[2]_2 ,
    \FSM_onehot_c_state_reg[2]_3 ,
    \FSM_onehot_c_state_reg[2]_4 ,
    \FSM_onehot_c_state_reg[2]_5 );
  output [31:0]sum_out_OBUF;
  input [0:0]out;
  input [3:0]O;
  input clk_IBUF_BUFG;
  input [3:0]\FSM_onehot_c_state_reg[2] ;
  input [3:0]\FSM_onehot_c_state_reg[2]_0 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_1 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_2 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_3 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_4 ;
  input [3:0]\FSM_onehot_c_state_reg[2]_5 ;

  wire [3:0]\FSM_onehot_c_state_reg[2] ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_0 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_1 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_2 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_3 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_4 ;
  wire [3:0]\FSM_onehot_c_state_reg[2]_5 ;
  wire [3:0]O;
  wire clk_IBUF_BUFG;
  wire [0:0]out;
  wire [31:0]sum_out_OBUF;

  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(O[0]),
        .Q(sum_out_OBUF[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[10] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_0 [2]),
        .Q(sum_out_OBUF[10]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[11] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_0 [3]),
        .Q(sum_out_OBUF[11]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[12] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_1 [0]),
        .Q(sum_out_OBUF[12]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[13] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_1 [1]),
        .Q(sum_out_OBUF[13]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[14] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_1 [2]),
        .Q(sum_out_OBUF[14]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[15] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_1 [3]),
        .Q(sum_out_OBUF[15]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[16] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_2 [0]),
        .Q(sum_out_OBUF[16]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[17] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_2 [1]),
        .Q(sum_out_OBUF[17]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[18] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_2 [2]),
        .Q(sum_out_OBUF[18]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[19] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_2 [3]),
        .Q(sum_out_OBUF[19]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(O[1]),
        .Q(sum_out_OBUF[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[20] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_3 [0]),
        .Q(sum_out_OBUF[20]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[21] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_3 [1]),
        .Q(sum_out_OBUF[21]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[22] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_3 [2]),
        .Q(sum_out_OBUF[22]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[23] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_3 [3]),
        .Q(sum_out_OBUF[23]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[24] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_4 [0]),
        .Q(sum_out_OBUF[24]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[25] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_4 [1]),
        .Q(sum_out_OBUF[25]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[26] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_4 [2]),
        .Q(sum_out_OBUF[26]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[27] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_4 [3]),
        .Q(sum_out_OBUF[27]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[28] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_5 [0]),
        .Q(sum_out_OBUF[28]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[29] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_5 [1]),
        .Q(sum_out_OBUF[29]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(O[2]),
        .Q(sum_out_OBUF[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[30] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_5 [2]),
        .Q(sum_out_OBUF[30]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[31] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_5 [3]),
        .Q(sum_out_OBUF[31]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(O[3]),
        .Q(sum_out_OBUF[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[4] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2] [0]),
        .Q(sum_out_OBUF[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[5] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2] [1]),
        .Q(sum_out_OBUF[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[6] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2] [2]),
        .Q(sum_out_OBUF[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[7] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2] [3]),
        .Q(sum_out_OBUF[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[8] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_0 [0]),
        .Q(sum_out_OBUF[8]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \Q_reg[9] 
       (.C(clk_IBUF_BUFG),
        .CE(out),
        .D(\FSM_onehot_c_state_reg[2]_0 [1]),
        .Q(sum_out_OBUF[9]),
        .R(1'b0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
