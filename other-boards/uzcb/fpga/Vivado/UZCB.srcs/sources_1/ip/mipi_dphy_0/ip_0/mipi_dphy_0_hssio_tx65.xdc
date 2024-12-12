# file: mipi_dphy_0_hssio_tx65.xdc
# (c) Copyright 2013 - 2015 Xilinx, Inc. All rights reserved.
# 
# This file contains confidential and proprietary information
# of Xilinx, Inc. and is protected under U.S. and
# international copyright and other intellectual property
# laws.
# 
# DISCLAIMER
# This disclaimer is not a license and does not grant any
# rights to the materials distributed herewith. Except as
# otherwise provided in a valid license issued to you by
# Xilinx, and to the maximum extent permitted by applicable
# law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
# WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
# AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
# BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
# INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
# (2) Xilinx shall not be liable (whether in contract or tort,
# including negligence, or under any other theory of
# liability) for any loss or damage of any kind or nature
# related to, arising under or in connection with these
# materials, including for any direct, or any indirect,
# special, incidental, or consequential loss or damage
# (including loss of data, profits, goodwill, or any type of
# loss or damage suffered as a result of any action brought
# by a third party) even if such damage or loss was
# reasonably foreseeable or Xilinx had been advised of the
# possibility of the same.
# 
# CRITICAL APPLICATIONS
# Xilinx products are not designed or intended to be fail-
# safe, or for use in any application requiring fail-safe
# performance, such as life-support or safety devices or
# systems, Class III medical devices, nuclear facilities,
# applications related to the deployment of airbags, or any
# other applications that could lead to death, personal
# injury, or severe property or environmental damage
# (individually and collectively, "Critical
# Applications"). Customer assumes the sole risk and
# liability of any use of Xilinx products in Critical
# Applications, subject only to applicable laws and
# regulations governing limitations on product liability.
# 
# THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
# PART OF THIS FILE AT ALL TIMES.
set_false_path -to [get_pins -hier *sync_flop_0*/D]

########### Set the DIfferential IO standard from the supported Differential IO standards###############
set diff_std MIPI_DPHY_DCI


######################################## I/O constraints ##############################################
set_property PACKAGE_PIN W8 [get_ports data_txp0]
set_property DATA_RATE DDR [get_ports data_txp0]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txp0]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN Y8 [get_ports data_txn0]
set_property DATA_RATE DDR [get_ports data_txn0]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txn0]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN U9 [get_ports data_txp2]
set_property DATA_RATE DDR [get_ports data_txp2]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txp2]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN V9 [get_ports data_txn2]
set_property DATA_RATE DDR [get_ports data_txn2]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txn2]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN U8 [get_ports data_txp1]
set_property DATA_RATE DDR [get_ports data_txp1]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txp1]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN V8 [get_ports data_txn1]
set_property DATA_RATE DDR [get_ports data_txn1]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txn1]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN R7 [get_ports data_txp3]
set_property DATA_RATE DDR [get_ports data_txp3]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txp3]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN T7 [get_ports data_txn3]
set_property DATA_RATE DDR [get_ports data_txn3]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  data_txn3]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN J1 [get_ports clk_txp]
set_property DATA_RATE DDR [get_ports clk_txp]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  clk_txp]

######################################## I/O constraints ##############################################
set_property PACKAGE_PIN H1 [get_ports clk_txn]
set_property DATA_RATE DDR [get_ports clk_txn]
################## Need to set diff_std before uncommenting the below line#############################
set_property IOSTANDARD $diff_std [get_ports  clk_txn]








# # 
# # 
# # ################ Tx output impedance constraints ######################################################
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txp0]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txn0]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txp2]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txn2]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txp1]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txn1]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txp3]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports data_txn3]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports clk_txp]   
# # 
# # 
# # 
# # 
# # 
# # set_property OUTPUT_IMPEDANCE RDRV_NONE_NONE [get_ports clk_txn]   
# # 
# # 
# # 
# # 
# # 









