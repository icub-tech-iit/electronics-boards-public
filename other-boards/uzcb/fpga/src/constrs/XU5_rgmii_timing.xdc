# ----------------------------------------------------------------------------------------------------
# --  Customer         : Enclustra GmbH
# --  Project          : Mercury XU5 Reference Design
# --  File description : Timing constraints file for RGMII of PL ETH
# --  File name        : XU5_rgmii_timing.xdc
# --  Authors          : Andreas Buerkler
# ----------------------------------------------------------------------------------------------------
# --  Copyright (c) 2018 by Enclustra GmbH, Switzerland
# --  All rights reserved.
# ----------------------------------------------------------------------------------------------------

# RGMII RX clock (1.2ns shifted clock)
create_clock -name RGMII_RX_CLK -period 8.000 -waveform { 1.2 5.2 } [get_ports {ETH1_RXCLK}]
create_clock -name RGMII_RX_CLK_VIRT  -period 8.000 -waveform { 1.2 5.2 }

# RGMII TX clock (90° shifted)
set RGMII_TX_CLK "clk_out1_MercuryXU5_clk_wiz_0_0"
set RGMII_TX_CLK_90 "clk_out2_MercuryXU5_clk_wiz_0_0"

# RX clock and local clocks are asynchronous
set_false_path -from [get_clocks RGMII_RX_CLK] -to [get_clocks $RGMII_TX_CLK]
set_false_path -from [get_clocks $RGMII_TX_CLK] -to [get_clocks RGMII_RX_CLK]

# RGMII RX timing
set_input_delay -clock {RGMII_RX_CLK_VIRT} -min -2.8 [get_ports {ETH1_RXD[0] ETH1_RXD[1] ETH1_RXD[2] ETH1_RXD[3] ETH1_RXCTL}]
set_input_delay -clock {RGMII_RX_CLK_VIRT} -max -1.2 [get_ports {ETH1_RXD[0] ETH1_RXD[1] ETH1_RXD[2] ETH1_RXD[3] ETH1_RXCTL}]
set_input_delay -clock {RGMII_RX_CLK_VIRT} -clock_fall -min -2.8 -add_delay [get_ports {ETH1_RXD[0] ETH1_RXD[1] ETH1_RXD[2] ETH1_RXD[3] ETH1_RXCTL}]
set_input_delay -clock {RGMII_RX_CLK_VIRT} -clock_fall -max -1.2 -add_delay [get_ports {ETH1_RXD[0] ETH1_RXD[1] ETH1_RXD[2] ETH1_RXD[3] ETH1_RXCTL}]

set_false_path -rise_from [get_clocks RGMII_RX_CLK_VIRT] -fall_to [get_clocks RGMII_RX_CLK] -setup
set_false_path -fall_from [get_clocks RGMII_RX_CLK_VIRT] -rise_to [get_clocks RGMII_RX_CLK] -setup
set_false_path -rise_from [get_clocks RGMII_RX_CLK_VIRT] -rise_to [get_clocks RGMII_RX_CLK] -hold
set_false_path -fall_from [get_clocks RGMII_RX_CLK_VIRT] -fall_to [get_clocks RGMII_RX_CLK] -hold

# RGMII TX timing
set_output_delay -clock [get_clocks $RGMII_TX_CLK_90] -min -1.0 [get_ports {ETH1_TXD[0] ETH1_TXD[1] ETH1_TXD[2] ETH1_TXD[3] ETH1_TXCTL}]
set_output_delay -clock [get_clocks $RGMII_TX_CLK_90] -max 1.0 [get_ports {ETH1_TXD[0] ETH1_TXD[1] ETH1_TXD[2] ETH1_TXD[3] ETH1_TXCTL}]
set_output_delay -clock [get_clocks $RGMII_TX_CLK_90] -clock_fall -min -1.0 -add_delay [get_ports {ETH1_TXD[0] ETH1_TXD[1] ETH1_TXD[2] ETH1_TXD[3] ETH1_TXCTL}]
set_output_delay -clock [get_clocks $RGMII_TX_CLK_90] -clock_fall -max 1.0 -add_delay [get_ports {ETH1_TXD[0] ETH1_TXD[1] ETH1_TXD[2] ETH1_TXD[3] ETH1_TXCTL}]

set_false_path -fall_from [get_clocks $RGMII_TX_CLK] -rise_to [get_clocks $RGMII_TX_CLK_90] -setup
set_false_path -rise_from [get_clocks $RGMII_TX_CLK] -fall_to [get_clocks $RGMII_TX_CLK_90] -setup
set_false_path -fall_from [get_clocks $RGMII_TX_CLK] -fall_to [get_clocks $RGMII_TX_CLK_90] -hold
set_false_path -rise_from [get_clocks $RGMII_TX_CLK] -rise_to [get_clocks $RGMII_TX_CLK_90] -hold
