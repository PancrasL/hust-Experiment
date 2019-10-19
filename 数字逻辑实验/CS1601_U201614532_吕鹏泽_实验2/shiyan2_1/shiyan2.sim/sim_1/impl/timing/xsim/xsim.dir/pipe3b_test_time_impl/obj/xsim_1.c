/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
typedef void (*funcp)(char *, char *);
extern int main(int, char**);
extern void execute_35(char*, char *);
extern void execute_36(char*, char *);
extern void execute_37(char*, char *);
extern void execute_242(char*, char *);
extern void execute_243(char*, char *);
extern void execute_3(char*, char *);
extern void vlog_const_rhs_process_execute_0_fast_no_reg_no_agg(char*, char*, char*);
extern void execute_230(char*, char *);
extern void execute_231(char*, char *);
extern void execute_232(char*, char *);
extern void execute_233(char*, char *);
extern void execute_234(char*, char *);
extern void execute_235(char*, char *);
extern void execute_236(char*, char *);
extern void execute_237(char*, char *);
extern void execute_238(char*, char *);
extern void execute_239(char*, char *);
extern void execute_240(char*, char *);
extern void execute_241(char*, char *);
extern void execute_42(char*, char *);
extern void execute_43(char*, char *);
extern void vlog_timingcheck_execute_0(char*, char*, char*);
extern void execute_46(char*, char *);
extern void execute_6(char*, char *);
extern void execute_47(char*, char *);
extern void execute_8(char*, char *);
extern void execute_48(char*, char *);
extern void execute_49(char*, char *);
extern void execute_50(char*, char *);
extern void execute_10(char*, char *);
extern void execute_11(char*, char *);
extern void execute_12(char*, char *);
extern void execute_13(char*, char *);
extern void execute_51(char*, char *);
extern void execute_52(char*, char *);
extern void execute_53(char*, char *);
extern void execute_54(char*, char *);
extern void execute_55(char*, char *);
extern void execute_56(char*, char *);
extern void execute_57(char*, char *);
extern void execute_58(char*, char *);
extern void execute_59(char*, char *);
extern void execute_60(char*, char *);
extern void execute_61(char*, char *);
extern void execute_62(char*, char *);
extern void execute_63(char*, char *);
extern void execute_64(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_1(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_2(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_79(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_80(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_81(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_82(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_83(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_84(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_85(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_86(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_87(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_88(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_89(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_90(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_91(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_92(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_93(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_94(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_95(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_96(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_97(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_98(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_99(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_100(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_101(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_102(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_27(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_28(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_29(char*, char *);
extern void timing_checker_condition_m_72e76bc6_67151b0a_30(char*, char *);
extern void execute_83(char*, char *);
extern void vlog_simple_process_execute_0_fast_no_reg_no_agg(char*, char*, char*);
extern void execute_88(char*, char *);
extern void execute_89(char*, char *);
extern void execute_90(char*, char *);
extern void execute_91(char*, char *);
extern void execute_39(char*, char *);
extern void execute_40(char*, char *);
extern void execute_41(char*, char *);
extern void execute_244(char*, char *);
extern void execute_245(char*, char *);
extern void execute_246(char*, char *);
extern void execute_247(char*, char *);
extern void execute_248(char*, char *);
extern void transaction_2(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_3(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_4(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_5(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_6(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_7(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_8(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_9(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_10(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_11(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_12(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_13(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_14(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_15(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_16(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_17(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_18(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_19(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_20(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_21(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_22(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_23(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_24(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_25(char*, char*, unsigned, unsigned, unsigned);
extern void vlog_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_44(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_71(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_97(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_124(char*, char*, unsigned, unsigned, unsigned);
funcp funcTab[120] = {(funcp)execute_35, (funcp)execute_36, (funcp)execute_37, (funcp)execute_242, (funcp)execute_243, (funcp)execute_3, (funcp)vlog_const_rhs_process_execute_0_fast_no_reg_no_agg, (funcp)execute_230, (funcp)execute_231, (funcp)execute_232, (funcp)execute_233, (funcp)execute_234, (funcp)execute_235, (funcp)execute_236, (funcp)execute_237, (funcp)execute_238, (funcp)execute_239, (funcp)execute_240, (funcp)execute_241, (funcp)execute_42, (funcp)execute_43, (funcp)vlog_timingcheck_execute_0, (funcp)execute_46, (funcp)execute_6, (funcp)execute_47, (funcp)execute_8, (funcp)execute_48, (funcp)execute_49, (funcp)execute_50, (funcp)execute_10, (funcp)execute_11, (funcp)execute_12, (funcp)execute_13, (funcp)execute_51, (funcp)execute_52, (funcp)execute_53, (funcp)execute_54, (funcp)execute_55, (funcp)execute_56, (funcp)execute_57, (funcp)execute_58, (funcp)execute_59, (funcp)execute_60, (funcp)execute_61, (funcp)execute_62, (funcp)execute_63, (funcp)execute_64, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_1, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_2, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_79, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_80, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_81, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_82, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_83, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_84, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_85, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_86, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_87, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_88, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_89, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_90, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_91, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_92, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_93, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_94, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_95, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_96, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_97, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_98, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_99, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_100, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_101, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_102, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_27, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_28, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_29, (funcp)timing_checker_condition_m_72e76bc6_67151b0a_30, (funcp)execute_83, (funcp)vlog_simple_process_execute_0_fast_no_reg_no_agg, (funcp)execute_88, (funcp)execute_89, (funcp)execute_90, (funcp)execute_91, (funcp)execute_39, (funcp)execute_40, (funcp)execute_41, (funcp)execute_244, (funcp)execute_245, (funcp)execute_246, (funcp)execute_247, (funcp)execute_248, (funcp)transaction_2, (funcp)transaction_3, (funcp)transaction_4, (funcp)transaction_5, (funcp)transaction_6, (funcp)transaction_7, (funcp)transaction_8, (funcp)transaction_9, (funcp)transaction_10, (funcp)transaction_11, (funcp)transaction_12, (funcp)transaction_13, (funcp)transaction_14, (funcp)transaction_15, (funcp)transaction_16, (funcp)transaction_17, (funcp)transaction_18, (funcp)transaction_19, (funcp)transaction_20, (funcp)transaction_21, (funcp)transaction_22, (funcp)transaction_23, (funcp)transaction_24, (funcp)transaction_25, (funcp)vlog_transfunc_eventcallback, (funcp)transaction_44, (funcp)transaction_71, (funcp)transaction_97, (funcp)transaction_124};
const int NumRelocateId= 120;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/pipe3b_test_time_impl/xsim.reloc",  (void **)funcTab, 120);

	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/pipe3b_test_time_impl/xsim.reloc");
}

void simulate(char *dp)
{
	iki_schedule_processes_at_time_zero(dp, "xsim.dir/pipe3b_test_time_impl/xsim.reloc");
	// Initialize Verilog nets in mixed simulation, for the cases when the value at time 0 should be propagated from the mixed language Vhdl net
	iki_execute_processes();

	// Schedule resolution functions for the multiply driven Verilog nets that have strength
	// Schedule transaction functions for the singly driven Verilog nets that have strength

}
#include "iki_bridge.h"
void relocate(char *);

void sensitize(char *);

void simulate(char *);

extern SYSTEMCLIB_IMP_DLLSPEC void local_register_implicit_channel(int, char*);
extern void implicit_HDL_SCinstatiate();

extern int xsim_argc_copy ;
extern char** xsim_argv_copy ;

int main(int argc, char **argv)
{
    iki_heap_initialize("ms", "isimmm", 0, 2147483648) ;
    iki_set_sv_type_file_path_name("xsim.dir/pipe3b_test_time_impl/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/pipe3b_test_time_impl/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/pipe3b_test_time_impl/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}
