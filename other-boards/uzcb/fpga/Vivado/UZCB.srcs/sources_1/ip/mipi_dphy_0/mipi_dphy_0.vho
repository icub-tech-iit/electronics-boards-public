-- (c) Copyright 1995-2020 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: xilinx.com:ip:mipi_dphy:4.1
-- IP Revision: 3

-- The following code must appear in the VHDL architecture header.

------------- Begin Cut here for COMPONENT Declaration ------ COMP_TAG
COMPONENT mipi_dphy_0
  PORT (
    core_clk : IN STD_LOGIC;
    core_rst : IN STD_LOGIC;
    txclkesc_in : IN STD_LOGIC;
    txbyteclkhs_in : IN STD_LOGIC;
    clkoutphy_in : IN STD_LOGIC;
    system_rst_in : IN STD_LOGIC;
    pll_lock_in : IN STD_LOGIC;
    init_done : OUT STD_LOGIC;
    cl_txclkactivehs : OUT STD_LOGIC;
    cl_txrequesths : IN STD_LOGIC;
    cl_stopstate : OUT STD_LOGIC;
    cl_enable : IN STD_LOGIC;
    cl_txulpsclk : IN STD_LOGIC;
    cl_txulpsexit : IN STD_LOGIC;
    cl_ulpsactivenot : OUT STD_LOGIC;
    dl0_txdatahs : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl0_txrequesths : IN STD_LOGIC;
    dl0_txreadyhs : OUT STD_LOGIC;
    dl0_forcetxstopmode : IN STD_LOGIC;
    dl0_stopstate : OUT STD_LOGIC;
    dl0_enable : IN STD_LOGIC;
    dl0_txrequestesc : IN STD_LOGIC;
    dl0_txlpdtesc : IN STD_LOGIC;
    dl0_txulpsexit : IN STD_LOGIC;
    dl0_ulpsactivenot : OUT STD_LOGIC;
    dl0_txulpsesc : IN STD_LOGIC;
    dl0_txtriggeresc : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    dl0_txdataesc : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl0_txvalidesc : IN STD_LOGIC;
    dl0_txreadyesc : OUT STD_LOGIC;
    dl1_txdatahs : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl1_txrequesths : IN STD_LOGIC;
    dl1_txreadyhs : OUT STD_LOGIC;
    dl1_forcetxstopmode : IN STD_LOGIC;
    dl1_stopstate : OUT STD_LOGIC;
    dl1_enable : IN STD_LOGIC;
    dl1_txrequestesc : IN STD_LOGIC;
    dl1_txlpdtesc : IN STD_LOGIC;
    dl1_txulpsexit : IN STD_LOGIC;
    dl1_ulpsactivenot : OUT STD_LOGIC;
    dl1_txulpsesc : IN STD_LOGIC;
    dl1_txtriggeresc : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    dl1_txdataesc : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl1_txvalidesc : IN STD_LOGIC;
    dl1_txreadyesc : OUT STD_LOGIC;
    dl2_txdatahs : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl2_txrequesths : IN STD_LOGIC;
    dl2_txreadyhs : OUT STD_LOGIC;
    dl2_forcetxstopmode : IN STD_LOGIC;
    dl2_stopstate : OUT STD_LOGIC;
    dl2_enable : IN STD_LOGIC;
    dl2_txrequestesc : IN STD_LOGIC;
    dl2_txlpdtesc : IN STD_LOGIC;
    dl2_txulpsexit : IN STD_LOGIC;
    dl2_ulpsactivenot : OUT STD_LOGIC;
    dl2_txulpsesc : IN STD_LOGIC;
    dl2_txtriggeresc : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    dl2_txdataesc : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl2_txvalidesc : IN STD_LOGIC;
    dl2_txreadyesc : OUT STD_LOGIC;
    dl3_txdatahs : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl3_txrequesths : IN STD_LOGIC;
    dl3_txreadyhs : OUT STD_LOGIC;
    dl3_forcetxstopmode : IN STD_LOGIC;
    dl3_stopstate : OUT STD_LOGIC;
    dl3_enable : IN STD_LOGIC;
    dl3_txrequestesc : IN STD_LOGIC;
    dl3_txlpdtesc : IN STD_LOGIC;
    dl3_txulpsexit : IN STD_LOGIC;
    dl3_ulpsactivenot : OUT STD_LOGIC;
    dl3_txulpsesc : IN STD_LOGIC;
    dl3_txtriggeresc : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    dl3_txdataesc : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    dl3_txvalidesc : IN STD_LOGIC;
    dl3_txreadyesc : OUT STD_LOGIC;
    clk_txp : OUT STD_LOGIC;
    clk_txn : OUT STD_LOGIC;
    data_txp : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    data_txn : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
  );
END COMPONENT;
-- COMP_TAG_END ------ End COMPONENT Declaration ------------

-- The following code must appear in the VHDL architecture
-- body. Substitute your own instance name and net names.

------------- Begin Cut here for INSTANTIATION Template ----- INST_TAG
your_instance_name : mipi_dphy_0
  PORT MAP (
    core_clk => core_clk,
    core_rst => core_rst,
    txclkesc_in => txclkesc_in,
    txbyteclkhs_in => txbyteclkhs_in,
    clkoutphy_in => clkoutphy_in,
    system_rst_in => system_rst_in,
    pll_lock_in => pll_lock_in,
    init_done => init_done,
    cl_txclkactivehs => cl_txclkactivehs,
    cl_txrequesths => cl_txrequesths,
    cl_stopstate => cl_stopstate,
    cl_enable => cl_enable,
    cl_txulpsclk => cl_txulpsclk,
    cl_txulpsexit => cl_txulpsexit,
    cl_ulpsactivenot => cl_ulpsactivenot,
    dl0_txdatahs => dl0_txdatahs,
    dl0_txrequesths => dl0_txrequesths,
    dl0_txreadyhs => dl0_txreadyhs,
    dl0_forcetxstopmode => dl0_forcetxstopmode,
    dl0_stopstate => dl0_stopstate,
    dl0_enable => dl0_enable,
    dl0_txrequestesc => dl0_txrequestesc,
    dl0_txlpdtesc => dl0_txlpdtesc,
    dl0_txulpsexit => dl0_txulpsexit,
    dl0_ulpsactivenot => dl0_ulpsactivenot,
    dl0_txulpsesc => dl0_txulpsesc,
    dl0_txtriggeresc => dl0_txtriggeresc,
    dl0_txdataesc => dl0_txdataesc,
    dl0_txvalidesc => dl0_txvalidesc,
    dl0_txreadyesc => dl0_txreadyesc,
    dl1_txdatahs => dl1_txdatahs,
    dl1_txrequesths => dl1_txrequesths,
    dl1_txreadyhs => dl1_txreadyhs,
    dl1_forcetxstopmode => dl1_forcetxstopmode,
    dl1_stopstate => dl1_stopstate,
    dl1_enable => dl1_enable,
    dl1_txrequestesc => dl1_txrequestesc,
    dl1_txlpdtesc => dl1_txlpdtesc,
    dl1_txulpsexit => dl1_txulpsexit,
    dl1_ulpsactivenot => dl1_ulpsactivenot,
    dl1_txulpsesc => dl1_txulpsesc,
    dl1_txtriggeresc => dl1_txtriggeresc,
    dl1_txdataesc => dl1_txdataesc,
    dl1_txvalidesc => dl1_txvalidesc,
    dl1_txreadyesc => dl1_txreadyesc,
    dl2_txdatahs => dl2_txdatahs,
    dl2_txrequesths => dl2_txrequesths,
    dl2_txreadyhs => dl2_txreadyhs,
    dl2_forcetxstopmode => dl2_forcetxstopmode,
    dl2_stopstate => dl2_stopstate,
    dl2_enable => dl2_enable,
    dl2_txrequestesc => dl2_txrequestesc,
    dl2_txlpdtesc => dl2_txlpdtesc,
    dl2_txulpsexit => dl2_txulpsexit,
    dl2_ulpsactivenot => dl2_ulpsactivenot,
    dl2_txulpsesc => dl2_txulpsesc,
    dl2_txtriggeresc => dl2_txtriggeresc,
    dl2_txdataesc => dl2_txdataesc,
    dl2_txvalidesc => dl2_txvalidesc,
    dl2_txreadyesc => dl2_txreadyesc,
    dl3_txdatahs => dl3_txdatahs,
    dl3_txrequesths => dl3_txrequesths,
    dl3_txreadyhs => dl3_txreadyhs,
    dl3_forcetxstopmode => dl3_forcetxstopmode,
    dl3_stopstate => dl3_stopstate,
    dl3_enable => dl3_enable,
    dl3_txrequestesc => dl3_txrequestesc,
    dl3_txlpdtesc => dl3_txlpdtesc,
    dl3_txulpsexit => dl3_txulpsexit,
    dl3_ulpsactivenot => dl3_ulpsactivenot,
    dl3_txulpsesc => dl3_txulpsesc,
    dl3_txtriggeresc => dl3_txtriggeresc,
    dl3_txdataesc => dl3_txdataesc,
    dl3_txvalidesc => dl3_txvalidesc,
    dl3_txreadyesc => dl3_txreadyesc,
    clk_txp => clk_txp,
    clk_txn => clk_txn,
    data_txp => data_txp,
    data_txn => data_txn
  );
-- INST_TAG_END ------ End INSTANTIATION Template ---------

-- You must compile the wrapper file mipi_dphy_0.vhd when simulating
-- the core, mipi_dphy_0. When compiling the wrapper file, be sure to
-- reference the VHDL simulation library.

