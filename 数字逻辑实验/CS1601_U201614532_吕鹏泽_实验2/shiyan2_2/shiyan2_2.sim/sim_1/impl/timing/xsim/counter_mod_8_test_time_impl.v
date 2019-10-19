// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
// Date        : Tue Jun 12 20:30:04 2018
// Host        : DESKTOP-4FFCO4E running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               E:/shu_zi_luo_ji/shiyan2_2/shiyan2_2.sim/sim_1/impl/timing/xsim/counter_mod_8_test_time_impl.v
// Design      : counter_mod_8
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module counter
   (QA_OBUF,
    QB_OBUF,
    QC_OBUF,
    QD_OBUF,
    Qcc_reg,
    CP_IBUF_BUFG);
  output QA_OBUF;
  output QB_OBUF;
  output QC_OBUF;
  output QD_OBUF;
  output Qcc_reg;
  input CP_IBUF_BUFG;

  wire CP_IBUF_BUFG;
  wire QA_OBUF;
  wire QA_i_1_n_0;
  wire QB_OBUF;
  wire QB_i_1_n_0;
  wire QC_OBUF;
  wire QC_i_1_n_0;
  wire QD_OBUF;
  wire QD_i_1_n_0;
  wire Qcc_reg;

  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'h00BF)) 
    QA_i_1
       (.I0(QC_OBUF),
        .I1(QB_OBUF),
        .I2(QD_OBUF),
        .I3(QA_OBUF),
        .O(QA_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    QA_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QA_i_1_n_0),
        .Q(QA_OBUF),
        .R(1'b0));
  LUT2 #(
    .INIT(4'h6)) 
    QB_i_1
       (.I0(QB_OBUF),
        .I1(QA_OBUF),
        .O(QB_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    QB_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QB_i_1_n_0),
        .Q(QB_OBUF),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    QC_i_1
       (.I0(QC_OBUF),
        .I1(QB_OBUF),
        .I2(QA_OBUF),
        .O(QC_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    QC_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QC_i_1_n_0),
        .Q(QC_OBUF),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'h7B80)) 
    QD_i_1
       (.I0(QC_OBUF),
        .I1(QB_OBUF),
        .I2(QA_OBUF),
        .I3(QD_OBUF),
        .O(QD_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    QD_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QD_i_1_n_0),
        .Q(QD_OBUF),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h0020)) 
    Qcc_i_1
       (.I0(QD_OBUF),
        .I1(QA_OBUF),
        .I2(QB_OBUF),
        .I3(QC_OBUF),
        .O(Qcc_reg));
endmodule

(* ECO_CHECKSUM = "a5fef52f" *) 
(* NotValidForBitStream *)
module counter_mod_8
   (CP,
    QD,
    QC,
    QB,
    QA,
    Qcc);
  input CP;
  output QD;
  output QC;
  output QB;
  output QA;
  output Qcc;

  wire CP;
  wire CP_IBUF;
  wire CP_IBUF_BUFG;
  wire QA;
  wire QA_OBUF;
  wire QB;
  wire QB_OBUF;
  wire QC;
  wire QC_OBUF;
  wire QD;
  wire QD_OBUF;
  wire Qcc;
  wire Qcc_OBUF;
  wire c1_n_4;

initial begin
 $sdf_annotate("counter_mod_8_test_time_impl.sdf",,,,"tool_control");
end
  BUFG CP_IBUF_BUFG_inst
       (.I(CP_IBUF),
        .O(CP_IBUF_BUFG));
  IBUF CP_IBUF_inst
       (.I(CP),
        .O(CP_IBUF));
  OBUF QA_OBUF_inst
       (.I(QA_OBUF),
        .O(QA));
  OBUF QB_OBUF_inst
       (.I(QB_OBUF),
        .O(QB));
  OBUF QC_OBUF_inst
       (.I(QC_OBUF),
        .O(QC));
  OBUF QD_OBUF_inst
       (.I(QD_OBUF),
        .O(QD));
  OBUF Qcc_OBUF_inst
       (.I(Qcc_OBUF),
        .O(Qcc));
  FDRE #(
    .INIT(1'b1)) 
    Qcc_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(c1_n_4),
        .Q(Qcc_OBUF),
        .R(1'b0));
  counter c1
       (.CP_IBUF_BUFG(CP_IBUF_BUFG),
        .QA_OBUF(QA_OBUF),
        .QB_OBUF(QB_OBUF),
        .QC_OBUF(QC_OBUF),
        .QD_OBUF(QD_OBUF),
        .Qcc_reg(c1_n_4));
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
