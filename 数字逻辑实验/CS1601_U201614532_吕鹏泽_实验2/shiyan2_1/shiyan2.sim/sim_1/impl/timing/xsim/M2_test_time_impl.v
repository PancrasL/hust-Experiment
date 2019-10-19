// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
// Date        : Fri Jun  8 16:54:21 2018
// Host        : DESKTOP-4FFCO4E running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               E:/shiyan2/shiyan2.sim/sim_1/impl/timing/xsim/M2_test_time_impl.v
// Design      : M2
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module JK
   (Q1_OBUF,
    X_IBUF_BUFG);
  output Q1_OBUF;
  input X_IBUF_BUFG;

  wire Q1_OBUF;
  wire Q_i_1_n_0;
  wire X_IBUF_BUFG;

  LUT1 #(
    .INIT(2'h1)) 
    Q_i_1
       (.I0(Q1_OBUF),
        .O(Q_i_1_n_0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    Q_reg
       (.C(X_IBUF_BUFG),
        .CE(1'b1),
        .D(Q_i_1_n_0),
        .Q(Q1_OBUF),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "JK" *) 
module JK_0
   (Q2_OBUF,
    Q_reg_0,
    Q1_OBUF);
  output Q2_OBUF;
  input Q_reg_0;
  input Q1_OBUF;

  wire Q1_OBUF;
  wire Q2_OBUF;
  wire Q_reg_0;

  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    Q_reg
       (.C(Q1_OBUF),
        .CE(1'b1),
        .D(Q_reg_0),
        .Q(Q2_OBUF),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "JK" *) 
module JK_1
   (Q3_OBUF,
    Q_reg_0,
    Q2_OBUF,
    Q4_OBUF);
  output Q3_OBUF;
  output Q_reg_0;
  input Q2_OBUF;
  input Q4_OBUF;

  wire Q2_OBUF;
  wire Q3_OBUF;
  wire Q4_OBUF;
  wire Q_i_1__0_n_0;
  wire Q_reg_0;

  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT1 #(
    .INIT(2'h1)) 
    Q_i_1__0
       (.I0(Q3_OBUF),
        .O(Q_i_1__0_n_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'h08)) 
    Q_i_1__1
       (.I0(Q3_OBUF),
        .I1(Q2_OBUF),
        .I2(Q4_OBUF),
        .O(Q_reg_0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    Q_reg
       (.C(Q2_OBUF),
        .CE(1'b1),
        .D(Q_i_1__0_n_0),
        .Q(Q3_OBUF),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "JK" *) 
module JK_2
   (Q4_OBUF,
    Z_OBUF,
    Q_reg_0,
    Q_reg_1,
    Q1_OBUF,
    X_IBUF,
    Q2_OBUF);
  output Q4_OBUF;
  output Z_OBUF;
  output Q_reg_0;
  input Q_reg_1;
  input Q1_OBUF;
  input X_IBUF;
  input Q2_OBUF;

  wire Q1_OBUF;
  wire Q2_OBUF;
  wire Q4_OBUF;
  wire Q_reg_0;
  wire Q_reg_1;
  wire X_IBUF;
  wire Z_OBUF;

  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'h1)) 
    Q_i_1__2
       (.I0(Q4_OBUF),
        .I1(Q2_OBUF),
        .O(Q_reg_0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    Q_reg
       (.C(Q1_OBUF),
        .CE(1'b1),
        .D(Q_reg_1),
        .Q(Q4_OBUF),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h80)) 
    Z_OBUF_inst_i_1
       (.I0(Q4_OBUF),
        .I1(Q1_OBUF),
        .I2(X_IBUF),
        .O(Z_OBUF));
endmodule

(* ECO_CHECKSUM = "5ca1ccad" *) 
(* NotValidForBitStream *)
module M2
   (X,
    Z,
    Q1,
    Q2,
    Q3,
    Q4);
  input X;
  output Z;
  output Q1;
  output Q2;
  output Q3;
  output Q4;

  wire JK3_n_1;
  wire JK4_n_2;
  wire Q1;
  wire Q1_OBUF;
  wire Q2;
  wire Q2_OBUF;
  wire Q3;
  wire Q3_OBUF;
  wire Q4;
  wire Q4_OBUF;
  wire X;
  wire X_IBUF;
  wire X_IBUF_BUFG;
  wire Z;
  wire Z_OBUF;

initial begin
 $sdf_annotate("M2_test_time_impl.sdf",,,,"tool_control");
end
  JK JK1
       (.Q1_OBUF(Q1_OBUF),
        .X_IBUF_BUFG(X_IBUF_BUFG));
  JK_0 JK2
       (.Q1_OBUF(Q1_OBUF),
        .Q2_OBUF(Q2_OBUF),
        .Q_reg_0(JK4_n_2));
  JK_1 JK3
       (.Q2_OBUF(Q2_OBUF),
        .Q3_OBUF(Q3_OBUF),
        .Q4_OBUF(Q4_OBUF),
        .Q_reg_0(JK3_n_1));
  JK_2 JK4
       (.Q1_OBUF(Q1_OBUF),
        .Q2_OBUF(Q2_OBUF),
        .Q4_OBUF(Q4_OBUF),
        .Q_reg_0(JK4_n_2),
        .Q_reg_1(JK3_n_1),
        .X_IBUF(X_IBUF),
        .Z_OBUF(Z_OBUF));
  OBUF Q1_OBUF_inst
       (.I(Q1_OBUF),
        .O(Q1));
  OBUF Q2_OBUF_inst
       (.I(Q2_OBUF),
        .O(Q2));
  OBUF Q3_OBUF_inst
       (.I(Q3_OBUF),
        .O(Q3));
  OBUF Q4_OBUF_inst
       (.I(Q4_OBUF),
        .O(Q4));
  BUFG X_IBUF_BUFG_inst
       (.I(X_IBUF),
        .O(X_IBUF_BUFG));
  IBUF X_IBUF_inst
       (.I(X),
        .O(X_IBUF));
  OBUF Z_OBUF_inst
       (.I(Z_OBUF),
        .O(Z));
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
