-- Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2019.1 (win64) Build 2552052 Fri May 24 14:49:42 MDT 2019
-- Date        : Wed Sep  2 13:43:56 2020
-- Host        : IITICUBLAP127 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Progetti/electronics/projects/boards/P2017_08_UZCB_UltraZynqCarrierBoard/fpga/Vivado/UZCB.srcs/sources_1/ip/mipi_dphy_0/mipi_dphy_0_stub.vhdl
-- Design      : mipi_dphy_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu5ev-sfvc784-2-i
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity mipi_dphy_0 is
  Port ( 
    core_clk : in STD_LOGIC;
    core_rst : in STD_LOGIC;
    txclkesc_in : in STD_LOGIC;
    txbyteclkhs_in : in STD_LOGIC;
    clkoutphy_in : in STD_LOGIC;
    pll_lock_in : in STD_LOGIC;
    system_rst_in : in STD_LOGIC;
    init_done : out STD_LOGIC;
    cl_txclkactivehs : out STD_LOGIC;
    cl_txrequesths : in STD_LOGIC;
    cl_stopstate : out STD_LOGIC;
    cl_enable : in STD_LOGIC;
    cl_txulpsclk : in STD_LOGIC;
    cl_txulpsexit : in STD_LOGIC;
    cl_ulpsactivenot : out STD_LOGIC;
    dl0_txdatahs : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl0_txrequesths : in STD_LOGIC;
    dl0_txreadyhs : out STD_LOGIC;
    dl0_forcetxstopmode : in STD_LOGIC;
    dl0_stopstate : out STD_LOGIC;
    dl0_enable : in STD_LOGIC;
    dl0_txrequestesc : in STD_LOGIC;
    dl0_txlpdtesc : in STD_LOGIC;
    dl0_txulpsexit : in STD_LOGIC;
    dl0_ulpsactivenot : out STD_LOGIC;
    dl0_txulpsesc : in STD_LOGIC;
    dl0_txtriggeresc : in STD_LOGIC_VECTOR ( 3 downto 0 );
    dl0_txdataesc : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl0_txvalidesc : in STD_LOGIC;
    dl0_txreadyesc : out STD_LOGIC;
    dl1_txdatahs : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl1_txrequesths : in STD_LOGIC;
    dl1_txreadyhs : out STD_LOGIC;
    dl1_forcetxstopmode : in STD_LOGIC;
    dl1_stopstate : out STD_LOGIC;
    dl1_enable : in STD_LOGIC;
    dl1_txrequestesc : in STD_LOGIC;
    dl1_txlpdtesc : in STD_LOGIC;
    dl1_txulpsexit : in STD_LOGIC;
    dl1_ulpsactivenot : out STD_LOGIC;
    dl1_txulpsesc : in STD_LOGIC;
    dl1_txtriggeresc : in STD_LOGIC_VECTOR ( 3 downto 0 );
    dl1_txdataesc : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl1_txvalidesc : in STD_LOGIC;
    dl1_txreadyesc : out STD_LOGIC;
    dl2_txdatahs : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl2_txrequesths : in STD_LOGIC;
    dl2_txreadyhs : out STD_LOGIC;
    dl2_forcetxstopmode : in STD_LOGIC;
    dl2_stopstate : out STD_LOGIC;
    dl2_enable : in STD_LOGIC;
    dl2_txrequestesc : in STD_LOGIC;
    dl2_txlpdtesc : in STD_LOGIC;
    dl2_txulpsexit : in STD_LOGIC;
    dl2_ulpsactivenot : out STD_LOGIC;
    dl2_txulpsesc : in STD_LOGIC;
    dl2_txtriggeresc : in STD_LOGIC_VECTOR ( 3 downto 0 );
    dl2_txdataesc : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl2_txvalidesc : in STD_LOGIC;
    dl2_txreadyesc : out STD_LOGIC;
    dl3_txdatahs : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl3_txrequesths : in STD_LOGIC;
    dl3_txreadyhs : out STD_LOGIC;
    dl3_forcetxstopmode : in STD_LOGIC;
    dl3_stopstate : out STD_LOGIC;
    dl3_enable : in STD_LOGIC;
    dl3_txrequestesc : in STD_LOGIC;
    dl3_txlpdtesc : in STD_LOGIC;
    dl3_txulpsexit : in STD_LOGIC;
    dl3_ulpsactivenot : out STD_LOGIC;
    dl3_txulpsesc : in STD_LOGIC;
    dl3_txtriggeresc : in STD_LOGIC_VECTOR ( 3 downto 0 );
    dl3_txdataesc : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dl3_txvalidesc : in STD_LOGIC;
    dl3_txreadyesc : out STD_LOGIC;
    clk_txp : out STD_LOGIC;
    clk_txn : out STD_LOGIC;
    data_txp : out STD_LOGIC_VECTOR ( 3 downto 0 );
    data_txn : out STD_LOGIC_VECTOR ( 3 downto 0 )
  );

end mipi_dphy_0;

architecture stub of mipi_dphy_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "core_clk,core_rst,txclkesc_in,txbyteclkhs_in,clkoutphy_in,pll_lock_in,system_rst_in,init_done,cl_txclkactivehs,cl_txrequesths,cl_stopstate,cl_enable,cl_txulpsclk,cl_txulpsexit,cl_ulpsactivenot,dl0_txdatahs[7:0],dl0_txrequesths,dl0_txreadyhs,dl0_forcetxstopmode,dl0_stopstate,dl0_enable,dl0_txrequestesc,dl0_txlpdtesc,dl0_txulpsexit,dl0_ulpsactivenot,dl0_txulpsesc,dl0_txtriggeresc[3:0],dl0_txdataesc[7:0],dl0_txvalidesc,dl0_txreadyesc,dl1_txdatahs[7:0],dl1_txrequesths,dl1_txreadyhs,dl1_forcetxstopmode,dl1_stopstate,dl1_enable,dl1_txrequestesc,dl1_txlpdtesc,dl1_txulpsexit,dl1_ulpsactivenot,dl1_txulpsesc,dl1_txtriggeresc[3:0],dl1_txdataesc[7:0],dl1_txvalidesc,dl1_txreadyesc,dl2_txdatahs[7:0],dl2_txrequesths,dl2_txreadyhs,dl2_forcetxstopmode,dl2_stopstate,dl2_enable,dl2_txrequestesc,dl2_txlpdtesc,dl2_txulpsexit,dl2_ulpsactivenot,dl2_txulpsesc,dl2_txtriggeresc[3:0],dl2_txdataesc[7:0],dl2_txvalidesc,dl2_txreadyesc,dl3_txdatahs[7:0],dl3_txrequesths,dl3_txreadyhs,dl3_forcetxstopmode,dl3_stopstate,dl3_enable,dl3_txrequestesc,dl3_txlpdtesc,dl3_txulpsexit,dl3_ulpsactivenot,dl3_txulpsesc,dl3_txtriggeresc[3:0],dl3_txdataesc[7:0],dl3_txvalidesc,dl3_txreadyesc,clk_txp,clk_txn,data_txp[3:0],data_txn[3:0]";
begin
end;
