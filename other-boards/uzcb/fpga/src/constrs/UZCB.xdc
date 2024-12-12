# -------------------------------------------------------------------------------------------------
# -- Project          : Mercury XU5 Reference Design
# -- File description : Pin assignment and timing constraints file for Mercury PE1
# -- File name        : MercuryXU5_PE1.xdc
# -- Author           : Diana Ungureanu
# -------------------------------------------------------------------------------------------------
# -- Copyright (c) 2018 by Enclustra GmbH, Switzerland. All rights are reserved.
# -- Unauthorized duplication of this document, in whole or in part, by any means is prohibited
# -- without the prior written permission of Enclustra GmbH, Switzerland.
# --
# -- Although Enclustra GmbH believes that the information included in this publication is correct
# -- as of the date of publication, Enclustra GmbH reserves the right to make changes at any time
# -- without notice.
# --
# -- All information in this document may only be published by Enclustra GmbH, Switzerland.
# -------------------------------------------------------------------------------------------------
# -- Notes:
# -- The IO standards might need to be adapted to your design
# -------------------------------------------------------------------------------------------------
# -- File history:
# --
# -- Version | Date       | Author             | Remarks
# -- ----------------------------------------------------------------------------------------------
# -- 1.0     | 11.06.2018 | D. Ungureanu       | First released version
# -- 2.0     | 11.06.2018 | D. Ungureanu       | Consistency checks
# --
# -------------------------------------------------------------------------------------------------

set_property BITSTREAM.CONFIG.OVERTEMPSHUTDOWN ENABLE [current_design]

# ----------------------------------------------------------------------------------
# Important! Do not remove this constraint!
# This property ensures that all unused pins are set to high impedance.
# If the constraint is removed, all unused pins have to be set to HiZ in the top level file.
set_property BITSTREAM.CONFIG.UNUSEDPIN PULLNONE [current_design]
# ----------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------------------
# LEDs
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN H2 [get_ports {Led1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {Led1_N}]

set_property PACKAGE_PIN P9 [get_ports {Led2_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {Led2_N}]

set_property PACKAGE_PIN K5 [get_ports {Led3_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {Led3_N}]

# -------------------------------------------------------------------------------------------------
# CLK 200
# -------------------------------------------------------------------------------------------------
set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {CLK100_PL_P}]
set_property PACKAGE_PIN AD5 [get_ports {CLK100_PL_P}]
set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {CLK100_PL_N}]
set_property PACKAGE_PIN AD4 [get_ports {CLK100_PL_N}]

# -------------------------------------------------------------------------------------------------
# PL DDR4
# -------------------------------------------------------------------------------------------------
set_property INTERNAL_VREF 0.600 [get_iobanks 64]

set_property PACKAGE_PIN AC4 [get_ports {DDR4PL_A[0]}]
set_property PACKAGE_PIN AC3 [get_ports {DDR4PL_A[1]}]
set_property PACKAGE_PIN AB4 [get_ports {DDR4PL_A[2]}]
set_property PACKAGE_PIN AB3 [get_ports {DDR4PL_A[3]}]
set_property PACKAGE_PIN AB2 [get_ports {DDR4PL_A[4]}]
set_property PACKAGE_PIN AC2 [get_ports {DDR4PL_A[5]}]
set_property PACKAGE_PIN AB1 [get_ports {DDR4PL_A[6]}]
set_property PACKAGE_PIN AC1 [get_ports {DDR4PL_A[7]}]
set_property PACKAGE_PIN AB5 [get_ports {DDR4PL_A[8]}]
set_property PACKAGE_PIN AG4 [get_ports {DDR4PL_A[9]}]
set_property PACKAGE_PIN AH4 [get_ports {DDR4PL_A[10]}]
set_property PACKAGE_PIN AG3 [get_ports {DDR4PL_A[11]}]
set_property PACKAGE_PIN AH3 [get_ports {DDR4PL_A[12]}]
set_property PACKAGE_PIN AE3 [get_ports {DDR4PL_A[13]}]
set_property PACKAGE_PIN AF3 [get_ports {DDR4PL_A[14]}]
set_property PACKAGE_PIN AE2 [get_ports {DDR4PL_A[15]}]
set_property PACKAGE_PIN AF2 [get_ports {DDR4PL_A[16]}]
set_property PACKAGE_PIN AH2 [get_ports {DDR4PL_ACT_n}]
set_property PACKAGE_PIN AH1 [get_ports {DDR4PL_BA[0]}]
set_property PACKAGE_PIN AF1 [get_ports {DDR4PL_BA[1]}]
set_property PACKAGE_PIN AG1 [get_ports {DDR4PL_BG[0]}]
set_property PACKAGE_PIN AC6 [get_ports {DDR4PL_DQ[1]}]
set_property PACKAGE_PIN AD1 [get_ports {DDR4PL_CK_N}]
set_property PACKAGE_PIN AD2 [get_ports {DDR4PL_CK_P}]
set_property PACKAGE_PIN AH6 [get_ports {DDR4PL_CKE}]
set_property PACKAGE_PIN AF5 [get_ports {DDR4PL_DQ[9]}]
set_property PACKAGE_PIN AB6 [get_ports {DDR4PL_DQ[0]}]
set_property PACKAGE_PIN AE5 [get_ports {DDR4PL_DQ[8]}]
set_property PACKAGE_PIN AC9 [get_ports {DDR4PL_DM[0]}]
#set_property PACKAGE_PIN AD9 [get_ports {DDR4PL_BG[1]}]
set_property PACKAGE_PIN AE9 [get_ports {DDR4PL_DQ[2]}]
set_property PACKAGE_PIN AE8 [get_ports {DDR4PL_DQ[3]}]
set_property PACKAGE_PIN AB8 [get_ports {DDR4PL_DQ[4]}]
set_property PACKAGE_PIN AC8 [get_ports {DDR4PL_DQ[5]}]
set_property PACKAGE_PIN AB7 [get_ports {DDR4PL_DQ[6]}]
set_property PACKAGE_PIN AC7 [get_ports {DDR4PL_DQ[7]}]
set_property PACKAGE_PIN AG9 [get_ports {DDR4PL_DM[1]}]
set_property PACKAGE_PIN AH9 [get_ports {DDR4PL_CS_n}]
set_property PACKAGE_PIN AF8 [get_ports {DDR4PL_DQ[10]}]
set_property PACKAGE_PIN AG8 [get_ports {DDR4PL_DQ[11]}]
set_property PACKAGE_PIN AH8 [get_ports {DDR4PL_DQ[12]}]
set_property PACKAGE_PIN AH7 [get_ports {DDR4PL_DQ[13]}]
set_property PACKAGE_PIN AF7 [get_ports {DDR4PL_DQ[14]}]
set_property PACKAGE_PIN AF6 [get_ports {DDR4PL_DQ[15]}]
set_property PACKAGE_PIN AE7 [get_ports {DDR4PL_DQS_N[0]}]
set_property PACKAGE_PIN AD7 [get_ports {DDR4PL_DQS_P[0]}]
set_property PACKAGE_PIN AG5 [get_ports {DDR4PL_DQS_N[1]}]
set_property PACKAGE_PIN AG6 [get_ports {DDR4PL_DQS_P[1]}]
set_property PACKAGE_PIN AE4 [get_ports {DDR4PL_ODT}]
set_property PACKAGE_PIN G4 [get_ports {DDR4PL_RST_n_PL}]


set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[0]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[1]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[2]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[3]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[4]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[5]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[6]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[7]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[8]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[9]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[10]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[11]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[12]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[13]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[14]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[15]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[16]}]

set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_ACT_n}]

set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BA[0]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BA[1]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BG[0]}]
#set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BG[1]}]

set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {DDR4PL_CK_N}]
set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {DDR4PL_CK_P}]

set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_CKE}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_CS_n}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DM[0]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DM[1]}]

set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[0]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[1]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[2]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[3]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[4]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[5]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[6]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[7]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[8]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[9]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[10]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[11]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[12]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[13]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[14]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[15]}]

set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_N[0]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_P[0]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_N[1]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_P[1]}]

set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_ODT}]
set_property IOSTANDARD LVCMOS18 [get_ports {DDR4PL_RST_n_PL}]

 -------------------------------------------------------------------------------------------------
# Gigabit Ethernet interface 1 on PL side
# bank 25 (ZU2/3) or 45 (ZU4/5)
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN J11 [get_ports {ETH1_RXD[0]}]
set_property PACKAGE_PIN J10 [get_ports {ETH1_RXD[1]}]
set_property PACKAGE_PIN K13 [get_ports {ETH1_RXD[2]}]
set_property PACKAGE_PIN K12 [get_ports {ETH1_RXD[3]}]
set_property PACKAGE_PIN H11 [get_ports {ETH1_TXD[0]}]
set_property PACKAGE_PIN G10 [get_ports {ETH1_TXD[1]}]
set_property PACKAGE_PIN J12 [get_ports {ETH1_TXD[2]}]
set_property PACKAGE_PIN H12 [get_ports {ETH1_TXD[3]}]
set_property PACKAGE_PIN G11 [get_ports {ETH1_RXCLK}]
set_property PACKAGE_PIN F10 [get_ports {ETH1_RXCTL}]
set_property PACKAGE_PIN F12 [get_ports {ETH1_TXCLK}]
set_property PACKAGE_PIN F11 [get_ports {ETH1_TXCTL}]
set_property PACKAGE_PIN C11 [get_ports {ETH1_INT_n}]
set_property PACKAGE_PIN B10 [get_ports {ETH1_RESET_n}]
set_property PACKAGE_PIN A10 [get_ports {ETH1_MDC}]
set_property PACKAGE_PIN B11 [get_ports {ETH1_MDIO}]

set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_RXD[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_RXD[1]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_RXD[2]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_RXD[3]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_TXD[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_TXD[1]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_TXD[2]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_TXD[3]}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_RXCLK}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_RXCTL}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_TXCLK}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_TXCTL}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_INT_n}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_RESET_n}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_MDC}]
set_property IOSTANDARD LVCMOS18 [get_ports {ETH1_MDIO}]

# -------------------------------------------------------------------------------------------------
# MGT
# -------------------------------------------------------------------------------------------------

# Reference clocks
set_property PACKAGE_PIN Y6 [get_ports REF0_MGT_CK_p]
set_property PACKAGE_PIN Y5 [get_ports REF0_MGT_CK_n]
set_property PACKAGE_PIN V6 [get_ports REF1_MGT_CK_p]
set_property PACKAGE_PIN V5 [get_ports REF1_MGT_CK_n]

# GTP Ports
set_property PACKAGE_PIN W4 [get_ports EDL_MGT_TX_p]          
set_property PACKAGE_PIN W3 [get_ports EDL_MGT_TX_n]        
set_property PACKAGE_PIN Y2 [get_ports EDL_MGT_RX_p]        
set_property PACKAGE_PIN Y1 [get_ports EDL_MGT_RX_n]            

set_property PACKAGE_PIN U4 [get_ports EDR_MGT_TX_p] 
set_property PACKAGE_PIN U3 [get_ports EDR_MGT_TX_n]        
set_property PACKAGE_PIN V2 [get_ports EDR_MGT_RX_p]        
set_property PACKAGE_PIN V1 [get_ports EDR_MGT_RX_n]            

set_property PACKAGE_PIN R4 [get_ports SPA_MGT_TX_p]
set_property PACKAGE_PIN R3 [get_ports SPA_MGT_TX_n]        
set_property PACKAGE_PIN T2 [get_ports SPA_MGT_RX_p]        
set_property PACKAGE_PIN T1 [get_ports SPA_MGT_RX_n]            

set_property PACKAGE_PIN N4 [get_ports SPB_MGT_TX_p]
set_property PACKAGE_PIN N3 [get_ports SPB_MGT_TX_n]        
set_property PACKAGE_PIN P2 [get_ports SPB_MGT_RX_p]        
set_property PACKAGE_PIN P1 [get_ports SPB_MGT_RX_n]        



# Frame Based Camera Right (J8)

































# -------------------------------------------------------------------------------------------------
# bank 65
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN W8 [get_ports {IO_B65_L1_W8}]
set_property PACKAGE_PIN Y8 [get_ports {IO_B65_L1_Y8}]
set_property PACKAGE_PIN H3 [get_ports {IO_B65_L10_AD4_H3_N}]
set_property PACKAGE_PIN H4 [get_ports {IO_B65_L10_AD4_H4_P}]
set_property PACKAGE_PIN K3 [get_ports {IO_B65_L11_GC_K3_N}]
set_property PACKAGE_PIN K4 [get_ports {IO_B65_L11_GC_K4_P}]
set_property PACKAGE_PIN L2 [get_ports {IO_B65_L12_GC_L2_N}]
set_property PACKAGE_PIN L3 [get_ports {IO_B65_L12_GC_L3_P}]
set_property PACKAGE_PIN L6 [get_ports {IO_B65_L13_GC_L6_N}]
set_property PACKAGE_PIN L7 [get_ports {IO_B65_L13_GC_L7_P}]
set_property PACKAGE_PIN L5 [get_ports {IO_B65_L14_GC_L5_N}]
set_property PACKAGE_PIN M6 [get_ports {IO_B65_L14_GC_M6_P}]
set_property PACKAGE_PIN N6 [get_ports {IO_B65_L15_AD11_N6_N}]
set_property PACKAGE_PIN N7 [get_ports {IO_B65_L15_AD11_N7_P}]
set_property PACKAGE_PIN P6 [get_ports {IO_B65_L16_AD3_P6_N}]
set_property PACKAGE_PIN P7 [get_ports {IO_B65_L16_AD3_P7_P}]
set_property PACKAGE_PIN N8 [get_ports {IO_B65_L17_AD10_N8_N}]
set_property PACKAGE_PIN N9 [get_ports {IO_B65_L17_AD10_N9_P}]
set_property PACKAGE_PIN L8 [get_ports {IO_B65_L18_AD2_L8_N}]
set_property PACKAGE_PIN M8 [get_ports {IO_B65_L18_AD2_M8_P}]
set_property PACKAGE_PIN J4 [get_ports {IO_B65_L19_AD9_J4_N}]
set_property PACKAGE_PIN J5 [get_ports {IO_B65_L19_AD9_J5_P}]
set_property PACKAGE_PIN U9 [get_ports {IO_B65_L2_U9}]
set_property PACKAGE_PIN V9 [get_ports {IO_B65_L2_V9}]
set_property PACKAGE_PIN H6 [get_ports {IO_B65_L20_AD1_H6_N}]
set_property PACKAGE_PIN J6 [get_ports {IO_B65_L20_AD1_J6_P}]
set_property PACKAGE_PIN H7 [get_ports {IO_B65_L21_AD8_H7_N}]
set_property PACKAGE_PIN J7 [get_ports {IO_B65_L21_AD8_J7_P}]
set_property PACKAGE_PIN K7 [get_ports {IO_B65_L22_AD0_K7_N}]
set_property PACKAGE_PIN K8 [get_ports {IO_B65_L22_AD0_K8_P}]
set_property PACKAGE_PIN J9 [get_ports {IO_B65_L23_J9_N}]
set_property PACKAGE_PIN K9 [get_ports {IO_B65_L23_SCLK_K9_P}]
set_property PACKAGE_PIN H8 [get_ports {IO_B65_L24_PERSTN_H8_N}]
set_property PACKAGE_PIN H9 [get_ports {IO_B65_L24_SDA_H9_P}]
set_property PACKAGE_PIN U8 [get_ports {IO_B65_L3_AD15_U8_P}]
set_property PACKAGE_PIN V8 [get_ports {IO_B65_L3_AD15_V8_N}]
set_property PACKAGE_PIN R8 [get_ports {IO_B65_L4_AD7_ALERT_R8_P}]
set_property PACKAGE_PIN T8 [get_ports {IO_B65_L4_AD7_T8_N}]
set_property PACKAGE_PIN R7 [get_ports {IO_B65_L5_AD14_R7_P}]
set_property PACKAGE_PIN T7 [get_ports {IO_B65_L5_AD14_T7_N}]
set_property PACKAGE_PIN R6 [get_ports {IO_B65_L6_AD6_R6_P}]
set_property PACKAGE_PIN T6 [get_ports {IO_B65_L6_AD6_T6_N}]
set_property PACKAGE_PIN K1 [get_ports {IO_B65_L7_AD13_K1_N}]
set_property PACKAGE_PIN L1 [get_ports {IO_B65_L7_AD13_L1_P}]
set_property PACKAGE_PIN H1 [get_ports {IO_B65_L8_AD5_H1_N}]
set_property PACKAGE_PIN J1 [get_ports {IO_B65_L8_AD5_J1_P}]
set_property PACKAGE_PIN J2 [get_ports {IO_B65_L9_AD12_J2_N}]
set_property PACKAGE_PIN K2 [get_ports {IO_B65_L9_AD12_K2_P}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L1_W8}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L1_Y8}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L10_AD4_H3_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L10_AD4_H4_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L11_GC_K3_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L11_GC_K4_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L12_GC_L2_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L12_GC_L3_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L13_GC_L6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L13_GC_L7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L14_GC_L5_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L14_GC_M6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L15_AD11_N6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L15_AD11_N7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L16_AD3_P6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L16_AD3_P7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L17_AD10_N8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L17_AD10_N9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L18_AD2_L8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L18_AD2_M8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L19_AD9_J4_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L19_AD9_J5_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L2_U9}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L2_V9}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L20_AD1_H6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L20_AD1_J6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L21_AD8_H7_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L21_AD8_J7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L22_AD0_K7_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L22_AD0_K8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L23_J9_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L23_SCLK_K9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L24_PERSTN_H8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L24_SDA_H9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L3_AD15_U8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L3_AD15_V8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L4_AD7_ALERT_R8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L4_AD7_T8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L5_AD14_R7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L5_AD14_T7_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L6_AD6_R6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L6_AD6_T6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L7_AD13_K1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L7_AD13_L1_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L8_AD5_H1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L8_AD5_J1_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L9_AD12_J2_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B65_L9_AD12_K2_P}]

# -------------------------------------------------------------------------------------------------
# bank 66
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN F1 [get_ports {IO_B66_L1_F1_N}]
set_property PACKAGE_PIN G1 [get_ports {IO_B66_L1_G1_P}]
set_property PACKAGE_PIN A4 [get_ports {IO_B66_L10_AD4_A4_N}]
set_property PACKAGE_PIN B4 [get_ports {IO_B66_L10_AD4_B4_P}]
set_property PACKAGE_PIN C4 [get_ports {IO_B66_L11_GC_C4_N}]
set_property PACKAGE_PIN D4 [get_ports {IO_B66_L11_GC_D4_P}]
set_property PACKAGE_PIN C2 [get_ports {IO_B66_L12_GC_C2_N}]
set_property PACKAGE_PIN C3 [get_ports {IO_B66_L12_GC_C3_P}]
set_property PACKAGE_PIN D6 [get_ports {IO_B66_L13_GC_D6_N}]
set_property PACKAGE_PIN D7 [get_ports {IO_B66_L13_GC_D7_P}]
set_property PACKAGE_PIN D5 [get_ports {IO_B66_L14_GC_D5_N}]
set_property PACKAGE_PIN E5 [get_ports {IO_B66_L14_GC_E5_P}]
set_property PACKAGE_PIN F6 [get_ports {IO_B66_L15_AD11_F6_N}]
set_property PACKAGE_PIN G6 [get_ports {IO_B66_L15_AD11_G6_P}]
set_property PACKAGE_PIN F7 [get_ports {IO_B66_L16_AD3_F7_N}]
set_property PACKAGE_PIN G8 [get_ports {IO_B66_L16_AD3_G8_P}]
set_property PACKAGE_PIN E8 [get_ports {IO_B66_L17_AD10_E8_N}]
set_property PACKAGE_PIN F8 [get_ports {IO_B66_L17_AD10_F8_P}]
set_property PACKAGE_PIN D9 [get_ports {IO_B66_L18_AD2_D9_N}]
set_property PACKAGE_PIN E9 [get_ports {IO_B66_L18_AD2_E9_P}]
set_property PACKAGE_PIN A5 [get_ports {IO_B66_L19_AD9_A5_N}]
set_property PACKAGE_PIN B5 [get_ports {IO_B66_L19_AD9_B5_P}]
set_property PACKAGE_PIN D1 [get_ports {IO_B66_L2_D1_N}]
set_property PACKAGE_PIN E1 [get_ports {IO_B66_L2_E1_P}]
set_property PACKAGE_PIN B6 [get_ports {IO_B66_L20_AD1_B6_N}]
set_property PACKAGE_PIN C6 [get_ports {IO_B66_L20_AD1_C6_P}]
set_property PACKAGE_PIN A6 [get_ports {IO_B66_L21_AD8_A6_N}]
set_property PACKAGE_PIN A7 [get_ports {IO_B66_L21_AD8_A7_P}]
set_property PACKAGE_PIN B8 [get_ports {IO_B66_L22_AD0_B8_N}]
set_property PACKAGE_PIN C8 [get_ports {IO_B66_L22_AD0_C8_P}]
set_property PACKAGE_PIN A8 [get_ports {IO_B66_L23_A8_N}]
set_property PACKAGE_PIN A9 [get_ports {IO_B66_L23_A9_P}]
set_property PACKAGE_PIN B9 [get_ports {IO_B66_L24_B9_N}]
set_property PACKAGE_PIN C9 [get_ports {IO_B66_L24_C9_P}]
set_property PACKAGE_PIN E2 [get_ports {IO_B66_L3_AD15_E2_N}]
set_property PACKAGE_PIN F2 [get_ports {IO_B66_L3_AD15_F2_P}]
set_property PACKAGE_PIN F3 [get_ports {IO_B66_L4_AD7_F3_N}]
set_property PACKAGE_PIN G3 [get_ports {IO_B66_L4_AD7_G3_P}]
set_property PACKAGE_PIN E3 [get_ports {IO_B66_L5_AD14_E3_N}]
set_property PACKAGE_PIN E4 [get_ports {IO_B66_L5_AD14_E4_P}]
set_property PACKAGE_PIN F5 [get_ports {IO_B66_L6_AD6_F5_N}]
set_property PACKAGE_PIN G5 [get_ports {IO_B66_L6_AD6_G5_P}]
set_property PACKAGE_PIN B1 [get_ports {IO_B66_L7_AD13_B1_N}]
set_property PACKAGE_PIN C1 [get_ports {IO_B66_L7_AD13_C1_P}]
set_property PACKAGE_PIN A1 [get_ports {IO_B66_L8_AD5_A1_N}]
set_property PACKAGE_PIN A2 [get_ports {IO_B66_L8_AD5_A2_P}]
set_property PACKAGE_PIN A3 [get_ports {IO_B66_L9_AD12_A3_N}]
set_property PACKAGE_PIN B3 [get_ports {IO_B66_L9_AD12_B3_P}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L1_F1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L1_G1_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L10_AD4_A4_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L10_AD4_B4_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L11_GC_C4_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L11_GC_D4_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L12_GC_C2_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L12_GC_C3_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L13_GC_D6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L13_GC_D7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L14_GC_D5_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L14_GC_E5_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L15_AD11_F6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L15_AD11_G6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L16_AD3_F7_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L16_AD3_G8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L17_AD10_E8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L17_AD10_F8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L18_AD2_D9_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L18_AD2_E9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L19_AD9_A5_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L19_AD9_B5_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L2_D1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L2_E1_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L20_AD1_B6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L20_AD1_C6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L21_AD8_A6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L21_AD8_A7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L22_AD0_B8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L22_AD0_C8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L23_A8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L23_A9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L24_B9_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L24_C9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L3_AD15_E2_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L3_AD15_F2_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L4_AD7_F3_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L4_AD7_G3_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L5_AD14_E3_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L5_AD14_E4_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L6_AD6_F5_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L6_AD6_G5_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L7_AD13_B1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L7_AD13_C1_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L8_AD5_A1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L8_AD5_A2_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L9_AD12_A3_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L9_AD12_B3_P}]
	
# -------------------------------------------------------------------------------------------------
# bank N - 24 (ZU2/3) or 44 (ZU4/5)
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN AE14 [get_ports {IO_BN_L1_AD15_AE14_N}]
set_property PACKAGE_PIN AE15 [get_ports {IO_BN_L1_AD15_AE15_P}]
set_property PACKAGE_PIN Y13 [get_ports {IO_BN_L10_AD10_Y13_N}]
set_property PACKAGE_PIN Y14 [get_ports {IO_BN_L10_AD10_Y14_P}]
set_property PACKAGE_PIN W11 [get_ports {IO_BN_L11_AD9_W11_N}]
set_property PACKAGE_PIN W12 [get_ports {IO_BN_L11_AD9_W12_P}]
set_property PACKAGE_PIN AA12 [get_ports {IO_BN_L12_AD8_AA12_N}]
set_property PACKAGE_PIN Y12 [get_ports {IO_BN_L12_AD8_Y12_P}]
set_property PACKAGE_PIN AG14 [get_ports {IO_BN_L2_AD14_AG14_P}]
set_property PACKAGE_PIN AH14 [get_ports {IO_BN_L2_AD14_AH14_N}]
set_property PACKAGE_PIN AG13 [get_ports {IO_BN_L3_AD13_AG13_P}]
set_property PACKAGE_PIN AH13 [get_ports {IO_BN_L3_AD13_AH13_N}]
set_property PACKAGE_PIN AE13 [get_ports {IO_BN_L4_AD12_AE13_P}]
set_property PACKAGE_PIN AF13 [get_ports {IO_BN_L4_AD12_AF13_N}]
set_property PACKAGE_PIN AD14 [get_ports {IO_BN_L5_HDGC_AD14_N}]
set_property PACKAGE_PIN AD15 [get_ports {IO_BN_L5_HDGC_AD15_P}]
set_property PACKAGE_PIN AC13 [get_ports {IO_BN_L6_HDGC_AC13_N}]
set_property PACKAGE_PIN AC14 [get_ports {IO_BN_L6_HDGC_AC14_P}]
set_property PACKAGE_PIN AA13 [get_ports {IO_BN_L7_HDGC_AA13_P}]
set_property PACKAGE_PIN AB13 [get_ports {IO_BN_L7_HDGC_AB13_N}]
set_property PACKAGE_PIN AB14 [get_ports {IO_BN_L8_HDGC_AB14_N}]
set_property PACKAGE_PIN AB15 [get_ports {IO_BN_L8_HDGC_AB15_P}]
set_property PACKAGE_PIN W13 [get_ports {IO_BN_L9_AD11_W13_N}]
set_property PACKAGE_PIN W14 [get_ports {IO_BN_L9_AD11_W14_P}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L1_AD15_AE14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L1_AD15_AE15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L10_AD10_Y13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L10_AD10_Y14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L11_AD9_W11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L11_AD9_W12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L12_AD8_AA12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L12_AD8_Y12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L2_AD14_AG14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L2_AD14_AH14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L3_AD13_AG13_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L3_AD13_AH13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L4_AD12_AE13_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L4_AD12_AF13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L5_HDGC_AD14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L5_HDGC_AD15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L6_HDGC_AC13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L6_HDGC_AC14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L7_HDGC_AA13_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L7_HDGC_AB13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L8_HDGC_AB14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L8_HDGC_AB15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L9_AD11_W13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L9_AD11_W14_P}]

# -------------------------------------------------------------------------------------------------
# bank O - 44 (ZU2/3) or 43 (ZU4/5)
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN AG10 [get_ports {IO_BO_L1_AD11_AG10_P}]
set_property PACKAGE_PIN AH10 [get_ports {IO_BO_L1_AD11_AH10_N}]
set_property PACKAGE_PIN W10 [get_ports {IO_BO_L10_AD2_W10_P}]
set_property PACKAGE_PIN Y10 [get_ports {IO_BO_L10_AD2_Y10_N}]
set_property PACKAGE_PIN AA8 [get_ports {IO_BO_L11_AD1_AA8_N}]
set_property PACKAGE_PIN Y9 [get_ports {IO_BO_L11_AD1_Y9_P}]
set_property PACKAGE_PIN AB10 [get_ports {IO_BO_L12_AD0_AB10_P}]
set_property PACKAGE_PIN AB9 [get_ports {IO_BO_L12_AD0_AB9_N}]
set_property PACKAGE_PIN AF11 [get_ports {IO_BO_L2_AD10_AF11_P}]
set_property PACKAGE_PIN AG11 [get_ports {IO_BO_L2_AD10_AG11_N}]
set_property PACKAGE_PIN AH11 [get_ports {IO_BO_L3_AD9_AH11_N}]
set_property PACKAGE_PIN AH12 [get_ports {IO_BO_L3_AD9_AH12_P}]
set_property PACKAGE_PIN AE10 [get_ports {IO_BO_L4_AD8_AE10_P}]
set_property PACKAGE_PIN AF10 [get_ports {IO_BO_L4_AD8_AF10_N}]
set_property PACKAGE_PIN AE12 [get_ports {IO_BO_L5_HDGC_AD7_AE12_P}]
set_property PACKAGE_PIN AF12 [get_ports {IO_BO_L5_HDGC_AD7_AF12_N}]
set_property PACKAGE_PIN AC12 [get_ports {IO_BO_L6_HDGC_AD6_AC12_P}]
set_property PACKAGE_PIN AD12 [get_ports {IO_BO_L6_HDGC_AD6_AD12_N}]
set_property PACKAGE_PIN AD10 [get_ports {IO_BO_L7_HDGC_AD5_AD10_N}]
set_property PACKAGE_PIN AD11 [get_ports {IO_BO_L7_HDGC_AD5_AD11_P}]
set_property PACKAGE_PIN AB11 [get_ports {IO_BO_L8_HDGC_AD4_AB11_P}]
set_property PACKAGE_PIN AC11 [get_ports {IO_BO_L8_HDGC_AD4_AC11_N}]
set_property PACKAGE_PIN AA10 [get_ports {IO_BO_L9_AD3_AA10_N}]
set_property PACKAGE_PIN AA11 [get_ports {IO_BO_L9_AD3_AA11_P}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L1_AD11_AG10_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L1_AD11_AH10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L10_AD2_W10_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L10_AD2_Y10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L11_AD1_AA8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L11_AD1_Y9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L12_AD0_AB10_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L12_AD0_AB9_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L2_AD10_AF11_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L2_AD10_AG11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L3_AD9_AH11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L3_AD9_AH12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L4_AD8_AE10_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L4_AD8_AF10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L5_HDGC_AD7_AE12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L5_HDGC_AD7_AF12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L6_HDGC_AD6_AC12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L6_HDGC_AD6_AD12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L7_HDGC_AD5_AD10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L7_HDGC_AD5_AD11_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L8_HDGC_AD4_AB11_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L8_HDGC_AD4_AC11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L9_AD3_AA10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L9_AD3_AA11_P}]

#

# -------------------------------------------------------------------------------------------------
# I2C bus on PL side
# bank 25 (ZU2/3) or 45 (ZU4/5)
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN D12 [get_ports {I2C_SCL_PL}]
set_property PACKAGE_PIN C12 [get_ports {I2C_SDA_PL}]
set_property IOSTANDARD LVCMOS18 [get_ports {I2C_SCL_PL}]
set_property IOSTANDARD LVCMOS18 [get_ports {I2C_SDA_PL}]

# -------------------------------------------------------------------------------------------------
# User I/Os
# bank 25 (ZU2/3) or 45 (ZU4/5)
# bank 26 (ZU2/3) or 46 (ZU4/5)
# -------------------------------------------------------------------------------------------------

set_property PACKAGE_PIN D11 [get_ports {IO_BE_L8_HDGC_D11_N}]
set_property PACKAGE_PIN E12 [get_ports {IO_BE_L8_HDGC_E12_P}]
set_property PACKAGE_PIN D10 [get_ports {IO_BE_L7_HDGC_D10_N}]
set_property PACKAGE_PIN E10 [get_ports {IO_BE_L7_HDGC_E10_P}]
set_property PACKAGE_PIN E15 [get_ports {IO_BF_L8_HDGC_AD4_E15_N}]
set_property PACKAGE_PIN F15 [get_ports {IO_BF_L8_HDGC_AD4_F15_P}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_BE_L8_HDGC_D11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BE_L8_HDGC_E12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BE_L7_HDGC_D10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BE_L7_HDGC_E10_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BF_L8_HDGC_AD4_E15_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BF_L8_HDGC_AD4_F15_P}]

# -------------------------------------------------------------------------------------------------
# PS banks defined in the block design
# -------------------------------------------------------------------------------------------------

