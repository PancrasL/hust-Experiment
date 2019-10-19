## Clock signal
##Bank = 35, Pin name = IO_L12P_T1_MRCC_35,					Sch name = CLK100MHZ
#set_property PACKAGE_PIN E3 [get_ports CP]							
#	set_property IOSTANDARD LVCMOS33 [get_ports CP]
#	create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports CP]
##Bank = 34, Pin name = IO_L24N_T3_34,				Sch name = LED0
#set_property PACKAGE_PIN T8 [get_ports {QA}]					
#    set_property IOSTANDARD LVCMOS33 [get_ports {QA}]
##Bank = 34, Pin name = IO_L21N_T3_DQS_34,			Sch name = LED1
#set_property PACKAGE_PIN V9 [get_ports {QB}]					
#    set_property IOSTANDARD LVCMOS33 [get_ports {QB}]
##Bank = 34, Pin name = IO_L24P_T3_34,				Sch name = LED2
#set_property PACKAGE_PIN R8 [get_ports {QC}]					
#    set_property IOSTANDARD LVCMOS33 [get_ports {QC}]
##Bank = 34, Pin name = IO_L23N_T3_34,				Sch name = LED3
#set_property PACKAGE_PIN T6 [get_ports {QD}]					
#set_property IOSTANDARD LVCMOS33 [get_ports {QD}]
##Bank = 34, Pin name = IO_L12P_T1_MRCC_34,			 Sch name = LED4
#set_property PACKAGE_PIN T5 [get_ports {Qcc}]                    
#set_property IOSTANDARD LVCMOS33 [get_ports {Qcc}]
# #Bank = 34, Pin name = IO_L21P_T3_DQS_34,           Sch name = SW0
#set_property PACKAGE_PIN U9 [get_ports M]                    
#set_property IOSTANDARD LVCMOS33 [get_ports M]
	