// (c) Copyright 1995-2020 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.

// IP VLNV: xilinx.com:ip:mipi_dphy:4.1
// IP Revision: 3

// The following must be inserted into your Verilog file for this
// core to be instantiated. Change the instance name and port connections
// (in parentheses) to your own signal names.

//----------- Begin Cut here for INSTANTIATION Template ---// INST_TAG
mipi_dphy_0 your_instance_name (
  .core_clk(core_clk),                        // input wire core_clk
  .core_rst(core_rst),                        // input wire core_rst
  .txclkesc_in(txclkesc_in),                  // input wire txclkesc_in
  .txbyteclkhs_in(txbyteclkhs_in),            // input wire txbyteclkhs_in
  .clkoutphy_in(clkoutphy_in),                // input wire clkoutphy_in
  .system_rst_in(system_rst_in),              // input wire system_rst_in
  .pll_lock_in(pll_lock_in),                  // input wire pll_lock_in
  .init_done(init_done),                      // output wire init_done
  .cl_txclkactivehs(cl_txclkactivehs),        // output wire cl_txclkactivehs
  .cl_txrequesths(cl_txrequesths),            // input wire cl_txrequesths
  .cl_stopstate(cl_stopstate),                // output wire cl_stopstate
  .cl_enable(cl_enable),                      // input wire cl_enable
  .cl_txulpsclk(cl_txulpsclk),                // input wire cl_txulpsclk
  .cl_txulpsexit(cl_txulpsexit),              // input wire cl_txulpsexit
  .cl_ulpsactivenot(cl_ulpsactivenot),        // output wire cl_ulpsactivenot
  .dl0_txdatahs(dl0_txdatahs),                // input wire [7 : 0] dl0_txdatahs
  .dl0_txrequesths(dl0_txrequesths),          // input wire dl0_txrequesths
  .dl0_txreadyhs(dl0_txreadyhs),              // output wire dl0_txreadyhs
  .dl0_forcetxstopmode(dl0_forcetxstopmode),  // input wire dl0_forcetxstopmode
  .dl0_stopstate(dl0_stopstate),              // output wire dl0_stopstate
  .dl0_enable(dl0_enable),                    // input wire dl0_enable
  .dl0_txrequestesc(dl0_txrequestesc),        // input wire dl0_txrequestesc
  .dl0_txlpdtesc(dl0_txlpdtesc),              // input wire dl0_txlpdtesc
  .dl0_txulpsexit(dl0_txulpsexit),            // input wire dl0_txulpsexit
  .dl0_ulpsactivenot(dl0_ulpsactivenot),      // output wire dl0_ulpsactivenot
  .dl0_txulpsesc(dl0_txulpsesc),              // input wire dl0_txulpsesc
  .dl0_txtriggeresc(dl0_txtriggeresc),        // input wire [3 : 0] dl0_txtriggeresc
  .dl0_txdataesc(dl0_txdataesc),              // input wire [7 : 0] dl0_txdataesc
  .dl0_txvalidesc(dl0_txvalidesc),            // input wire dl0_txvalidesc
  .dl0_txreadyesc(dl0_txreadyesc),            // output wire dl0_txreadyesc
  .dl1_txdatahs(dl1_txdatahs),                // input wire [7 : 0] dl1_txdatahs
  .dl1_txrequesths(dl1_txrequesths),          // input wire dl1_txrequesths
  .dl1_txreadyhs(dl1_txreadyhs),              // output wire dl1_txreadyhs
  .dl1_forcetxstopmode(dl1_forcetxstopmode),  // input wire dl1_forcetxstopmode
  .dl1_stopstate(dl1_stopstate),              // output wire dl1_stopstate
  .dl1_enable(dl1_enable),                    // input wire dl1_enable
  .dl1_txrequestesc(dl1_txrequestesc),        // input wire dl1_txrequestesc
  .dl1_txlpdtesc(dl1_txlpdtesc),              // input wire dl1_txlpdtesc
  .dl1_txulpsexit(dl1_txulpsexit),            // input wire dl1_txulpsexit
  .dl1_ulpsactivenot(dl1_ulpsactivenot),      // output wire dl1_ulpsactivenot
  .dl1_txulpsesc(dl1_txulpsesc),              // input wire dl1_txulpsesc
  .dl1_txtriggeresc(dl1_txtriggeresc),        // input wire [3 : 0] dl1_txtriggeresc
  .dl1_txdataesc(dl1_txdataesc),              // input wire [7 : 0] dl1_txdataesc
  .dl1_txvalidesc(dl1_txvalidesc),            // input wire dl1_txvalidesc
  .dl1_txreadyesc(dl1_txreadyesc),            // output wire dl1_txreadyesc
  .dl2_txdatahs(dl2_txdatahs),                // input wire [7 : 0] dl2_txdatahs
  .dl2_txrequesths(dl2_txrequesths),          // input wire dl2_txrequesths
  .dl2_txreadyhs(dl2_txreadyhs),              // output wire dl2_txreadyhs
  .dl2_forcetxstopmode(dl2_forcetxstopmode),  // input wire dl2_forcetxstopmode
  .dl2_stopstate(dl2_stopstate),              // output wire dl2_stopstate
  .dl2_enable(dl2_enable),                    // input wire dl2_enable
  .dl2_txrequestesc(dl2_txrequestesc),        // input wire dl2_txrequestesc
  .dl2_txlpdtesc(dl2_txlpdtesc),              // input wire dl2_txlpdtesc
  .dl2_txulpsexit(dl2_txulpsexit),            // input wire dl2_txulpsexit
  .dl2_ulpsactivenot(dl2_ulpsactivenot),      // output wire dl2_ulpsactivenot
  .dl2_txulpsesc(dl2_txulpsesc),              // input wire dl2_txulpsesc
  .dl2_txtriggeresc(dl2_txtriggeresc),        // input wire [3 : 0] dl2_txtriggeresc
  .dl2_txdataesc(dl2_txdataesc),              // input wire [7 : 0] dl2_txdataesc
  .dl2_txvalidesc(dl2_txvalidesc),            // input wire dl2_txvalidesc
  .dl2_txreadyesc(dl2_txreadyesc),            // output wire dl2_txreadyesc
  .dl3_txdatahs(dl3_txdatahs),                // input wire [7 : 0] dl3_txdatahs
  .dl3_txrequesths(dl3_txrequesths),          // input wire dl3_txrequesths
  .dl3_txreadyhs(dl3_txreadyhs),              // output wire dl3_txreadyhs
  .dl3_forcetxstopmode(dl3_forcetxstopmode),  // input wire dl3_forcetxstopmode
  .dl3_stopstate(dl3_stopstate),              // output wire dl3_stopstate
  .dl3_enable(dl3_enable),                    // input wire dl3_enable
  .dl3_txrequestesc(dl3_txrequestesc),        // input wire dl3_txrequestesc
  .dl3_txlpdtesc(dl3_txlpdtesc),              // input wire dl3_txlpdtesc
  .dl3_txulpsexit(dl3_txulpsexit),            // input wire dl3_txulpsexit
  .dl3_ulpsactivenot(dl3_ulpsactivenot),      // output wire dl3_ulpsactivenot
  .dl3_txulpsesc(dl3_txulpsesc),              // input wire dl3_txulpsesc
  .dl3_txtriggeresc(dl3_txtriggeresc),        // input wire [3 : 0] dl3_txtriggeresc
  .dl3_txdataesc(dl3_txdataesc),              // input wire [7 : 0] dl3_txdataesc
  .dl3_txvalidesc(dl3_txvalidesc),            // input wire dl3_txvalidesc
  .dl3_txreadyesc(dl3_txreadyesc),            // output wire dl3_txreadyesc
  .clk_txp(clk_txp),                          // output wire clk_txp
  .clk_txn(clk_txn),                          // output wire clk_txn
  .data_txp(data_txp),                        // output wire [3 : 0] data_txp
  .data_txn(data_txn)                        // output wire [3 : 0] data_txn
);
// INST_TAG_END ------ End INSTANTIATION Template ---------

// You must compile the wrapper file mipi_dphy_0.v when simulating
// the core, mipi_dphy_0. When compiling the wrapper file, be sure to
// reference the Verilog simulation library.

