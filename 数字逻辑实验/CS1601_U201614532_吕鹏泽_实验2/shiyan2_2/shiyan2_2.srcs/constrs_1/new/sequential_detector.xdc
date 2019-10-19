## Switches
# #Bank = 34, Pin name = IO_L21P_T3_DQS_34,           Sch name = SW0
#set_property PACKAGE_PIN U9 [get_ports {CP}]                    
#set_property IOSTANDARD LVCMOS33 [get_ports {CP}]
#set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets CP_IBUF]
#	#Bank = 34, Pin name = IO_L14P_T2_SRCC_34,					Sch name = SW15
#    set_property PACKAGE_PIN P4 [get_ports X]                    
#        set_property IOSTANDARD LVCMOS33 [get_ports X]
##Bank = 34, Pin name = IO_L23P_T3_34,			     Sch name = SW2
#set_property PACKAGE_PIN R7 [get_ports {RST}]					
#	set_property IOSTANDARD LVCMOS33 [get_ports {RST}]

##Bank = 34, Pin name = IO_L24N_T3_34,				Sch name = LED0
#set_property PACKAGE_PIN T8 [get_ports {Z}]					
#    set_property IOSTANDARD LVCMOS33 [get_ports {Z}]
##Bank = 34, Pin name = IO_L7P_T1_34,						Sch name = LED13
#    set_property PACKAGE_PIN U1 [get_ports {c_state[0]}]                    
#        set_property IOSTANDARD LVCMOS33 [get_ports {c_state[0]}]
#    #Bank = 34, Pin name = IO_L15N_T2_DQS_34,                    Sch name = LED14
#    set_property PACKAGE_PIN R2 [get_ports {c_state[1]}]                    
#        set_property IOSTANDARD LVCMOS33 [get_ports {c_state[1]}]
#    #Bank = 34, Pin name = IO_L15P_T2_DQS_34,                    Sch name = LED15
#    set_property PACKAGE_PIN P2 [get_ports {c_state[2]}]                    
#        set_property IOSTANDARD LVCMOS33 [get_ports {c_state[2]}]