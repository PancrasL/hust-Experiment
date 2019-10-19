// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
// Date        : Tue Jun 12 19:38:09 2018
// Host        : DESKTOP-4FFCO4E running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               E:/shu_zi_luo_ji/shiyan2_2/shiyan2_2.sim/sim_1/impl/timing/xsim/counter_test_time_impl.v
// Design      : counter
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

(* ECO_CHECKSUM = "cf5455e2" *) 
(* NotValidForBitStream *)
module counter
   (CP,
    CLR,
    M,
    LD,
    D,
    C,
    B,
    A,
    QD,
    QC,
    QB,
    QA,
    Qcc);
  input CP;
  input CLR;
  input M;
  input LD;
  input D;
  input C;
  input B;
  input A;
  output QD;
  output QC;
  output QB;
  output QA;
  output Qcc;

  wire A;
  wire A_IBUF;
  wire B;
  wire B_IBUF;
  wire C;
  wire CLR;
  wire CLR_IBUF;
  wire CP;
  wire CP_IBUF;
  wire CP_IBUF_BUFG;
  wire C_IBUF;
  wire D;
  wire D_IBUF;
  wire LD;
  wire LD_IBUF;
  wire M;
  wire M_IBUF;
  wire QA;
  wire QA_OBUF;
  wire QA_i_1_n_0;
  wire QB;
  wire QB_OBUF;
  wire QB_i_1_n_0;
  wire QC;
  wire QC_OBUF;
  wire QC_i_1_n_0;
  wire QC_i_2_n_0;
  wire QD;
  wire QD0_out;
  wire QD_OBUF;
  wire QD_i_1_n_0;
  wire Qcc;
  wire Qcc_OBUF;
  wire Qcc_i_1_n_0;
  wire Qcc_i_2_n_0;

initial begin
 $sdf_annotate("counter_test_time_impl.sdf",,,,"tool_control");
end
  IBUF A_IBUF_inst
       (.I(A),
        .O(A_IBUF));
  IBUF B_IBUF_inst
       (.I(B),
        .O(B_IBUF));
  IBUF CLR_IBUF_inst
       (.I(CLR),
        .O(CLR_IBUF));
  BUFG CP_IBUF_BUFG_inst
       (.I(CP_IBUF),
        .O(CP_IBUF_BUFG));
  IBUF CP_IBUF_inst
       (.I(CP),
        .O(CP_IBUF));
  IBUF C_IBUF_inst
       (.I(C),
        .O(C_IBUF));
  IBUF D_IBUF_inst
       (.I(D),
        .O(D_IBUF));
  IBUF LD_IBUF_inst
       (.I(LD),
        .O(LD_IBUF));
  IBUF M_IBUF_inst
       (.I(M),
        .O(M_IBUF));
  OBUF QA_OBUF_inst
       (.I(QA_OBUF),
        .O(QA));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'h22F0)) 
    QA_i_1
       (.I0(CLR_IBUF),
        .I1(QA_OBUF),
        .I2(A_IBUF),
        .I3(LD_IBUF),
        .O(QA_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    QA_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QA_i_1_n_0),
        .Q(QA_OBUF),
        .R(1'b0));
  OBUF QB_OBUF_inst
       (.I(QB_OBUF),
        .O(QB));
  LUT6 #(
    .INIT(64'h28822882FFFF0000)) 
    QB_i_1
       (.I0(CLR_IBUF),
        .I1(M_IBUF),
        .I2(QB_OBUF),
        .I3(QA_OBUF),
        .I4(B_IBUF),
        .I5(LD_IBUF),
        .O(QB_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    QB_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QB_i_1_n_0),
        .Q(QB_OBUF),
        .R(1'b0));
  OBUF QC_OBUF_inst
       (.I(QC_OBUF),
        .O(QC));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h5D)) 
    QC_i_1
       (.I0(QC_i_2_n_0),
        .I1(C_IBUF),
        .I2(LD_IBUF),
        .O(QC_i_1_n_0));
  LUT6 #(
    .INIT(64'h871EFFFFFFFFFFFF)) 
    QC_i_2
       (.I0(QB_OBUF),
        .I1(QA_OBUF),
        .I2(QC_OBUF),
        .I3(M_IBUF),
        .I4(CLR_IBUF),
        .I5(LD_IBUF),
        .O(QC_i_2_n_0));
  FDRE #(
    .INIT(1'b0)) 
    QC_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QC_i_1_n_0),
        .Q(QC_OBUF),
        .R(1'b0));
  OBUF QD_OBUF_inst
       (.I(QD_OBUF),
        .O(QD));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    QD_i_1
       (.I0(QD0_out),
        .I1(D_IBUF),
        .I2(LD_IBUF),
        .O(QD_i_1_n_0));
  LUT6 #(
    .INIT(64'h28A0A0A0A0A0A082)) 
    QD_i_2
       (.I0(CLR_IBUF),
        .I1(M_IBUF),
        .I2(QD_OBUF),
        .I3(QB_OBUF),
        .I4(QA_OBUF),
        .I5(QC_OBUF),
        .O(QD0_out));
  FDRE #(
    .INIT(1'b0)) 
    QD_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(QD_i_1_n_0),
        .Q(QD_OBUF),
        .R(1'b0));
  OBUF Qcc_OBUF_inst
       (.I(Qcc_OBUF),
        .O(Qcc));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT2 #(
    .INIT(4'h7)) 
    Qcc_i_1
       (.I0(CLR_IBUF),
        .I1(Qcc_i_2_n_0),
        .O(Qcc_i_1_n_0));
  LUT6 #(
    .INIT(64'h8000000100000000)) 
    Qcc_i_2
       (.I0(QC_OBUF),
        .I1(QB_OBUF),
        .I2(M_IBUF),
        .I3(QD_OBUF),
        .I4(QA_OBUF),
        .I5(LD_IBUF),
        .O(Qcc_i_2_n_0));
  FDRE #(
    .INIT(1'b1)) 
    Qcc_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(Qcc_i_1_n_0),
        .Q(Qcc_OBUF),
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
