#############################################################
# Clock Period Constraints                                 
#############################################################
create_clock -period 1.000 [get_ports  shared_pll0_clkoutphy_in]
create_clock -period 8.000 [get_ports  shared_pll0_clkout0_in]
create_clock -period 5.000 [get_ports  riu_clk]
