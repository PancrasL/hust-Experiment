// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
// Date        : Tue Jun 19 14:52:19 2018
// Host        : DESKTOP-4FFCO4E running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               E:/shu_zi_luo_ji/shiyan2_1/shiyan2.sim/sim_1/impl/timing/xsim/pipe3b_test_time_impl.v
// Design      : pipe3b
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

(* ECO_CHECKSUM = "23baeb4f" *) 
(* NotValidForBitStream *)
module pipe3b
   (sig_nsyn,
    clk,
    q1,
    q2,
    sig_syn);
  input sig_nsyn;
  input clk;
  output q1;
  output q2;
  output sig_syn;

  wire clk;
  wire clk_IBUF;
  wire clk_IBUF_BUFG;
  wire q1;
  wire q1_OBUF;
  wire q2;
  wire q2_OBUF;
  wire q2_reg_lopt_replica_1;
  wire sig_nsyn;
  wire sig_nsyn_IBUF;
  wire sig_syn;
  wire sig_syn_OBUF;

initial begin
 $sdf_annotate("pipe3b_test_time_impl.sdf",,,,"tool_control");
end
  BUFG clk_IBUF_BUFG_inst
       (.I(clk_IBUF),
        .O(clk_IBUF_BUFG));
  IBUF clk_IBUF_inst
       (.I(clk),
        .O(clk_IBUF));
  OBUF q1_OBUF_inst
       (.I(q1_OBUF),
        .O(q1));
  FDRE #(
    .INIT(1'b0)) 
    q1_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(sig_nsyn_IBUF),
        .Q(q1_OBUF),
        .R(1'b0));
  OBUF q2_OBUF_inst
       (.I(q2_reg_lopt_replica_1),
        .O(q2));
  FDRE #(
    .INIT(1'b0)) 
    q2_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(q1_OBUF),
        .Q(q2_OBUF),
        .R(1'b0));
  (* OPT_INSERTED_REPDRIVER *) 
  FDRE #(
    .INIT(1'b0)) 
    q2_reg_lopt_replica
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(q1_OBUF),
        .Q(q2_reg_lopt_replica_1),
        .R(1'b0));
  IBUF sig_nsyn_IBUF_inst
       (.I(sig_nsyn),
        .O(sig_nsyn_IBUF));
  OBUF sig_syn_OBUF_inst
       (.I(sig_syn_OBUF),
        .O(sig_syn));
  FDRE #(
    .INIT(1'b0)) 
    sig_syn_reg
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(q2_OBUF),
        .Q(sig_syn_OBUF),
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
