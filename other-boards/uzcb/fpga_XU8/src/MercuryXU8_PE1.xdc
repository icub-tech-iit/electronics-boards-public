# -------------------------------------------------------------------------------------------------
# -- Project          : Mercury+ XU8 Reference Design
# -- File description : Pin assignment and timing constraints file for Mercury PE1
# -- File name        : MercuryXU8_PE1.xdc
# -- Author           : Daniel Duerner
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
# -- 1.0     | 13.04.2018 | D. Duerner         | First released version
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
# LEDs & I/Os (bank 64)
# -------------------------------------------------------------------------------------------------

set_property PACKAGE_PIN AF13 [get_ports {Led2_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {Led2_N}]

set_property PACKAGE_PIN AC19 [get_ports {IO_B64_AC19}]
set_property PACKAGE_PIN AF17 [get_ports {IO_B64_AF17}]
set_property PACKAGE_PIN AG19 [get_ports {IO_B64_AG19}]
set_property PACKAGE_PIN AH16 [get_ports {IO_B64_AH16}]

set_property IOSTANDARD LVCMOS12 [get_ports {IO_B64_AC19}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B64_AF17}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B64_AG19}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B64_AH16}]

# -------------------------------------------------------------------------------------------------
# I2C on PL side (bank 64)
# -------------------------------------------------------------------------------------------------

set_property PACKAGE_PIN AB13 [get_ports {I2c_Scl}]
set_property IOSTANDARD LVCMOS12 [get_ports {I2c_Scl}]
set_property drive 8 [get_ports [list I2c_Scl]]

set_property PACKAGE_PIN AH13 [get_ports {I2c_Sda}]
set_property IOSTANDARD LVCMOS12 [get_ports {I2c_Sda}]
set_property drive 8 [get_ports [list I2c_Sda]]

# -------------------------------------------------------------------------------------------------
# DDR4 (bank 64)
# -------------------------------------------------------------------------------------------------
set_property INTERNAL_VREF 0.600 [get_iobanks 64]

set_property PACKAGE_PIN AA13 [get_ports {DDR4PL_DM[0]}]
set_property PACKAGE_PIN AG13 [get_ports {DDR4PL_DM[1]}]
set_property PACKAGE_PIN AF16 [get_ports {DDR4PL_DM[2]}]
set_property PACKAGE_PIN AG16 [get_ports {DDR4PL_DM[3]}]

set_property PACKAGE_PIN AB15 [get_ports {DDR4PL_DQ[0]}]
set_property PACKAGE_PIN AE15 [get_ports {DDR4PL_DQ[1]}]
set_property PACKAGE_PIN AD15 [get_ports {DDR4PL_DQ[2]}]
set_property PACKAGE_PIN AE14 [get_ports {DDR4PL_DQ[3]}]
set_property PACKAGE_PIN AC14 [get_ports {DDR4PL_DQ[4]}]
set_property PACKAGE_PIN AD14 [get_ports {DDR4PL_DQ[5]}]
set_property PACKAGE_PIN AA15 [get_ports {DDR4PL_DQ[6]}]
set_property PACKAGE_PIN AE13 [get_ports {DDR4PL_DQ[7]}]
set_property PACKAGE_PIN AH14 [get_ports {DDR4PL_DQ[8]}]
set_property PACKAGE_PIN AK13 [get_ports {DDR4PL_DQ[9]}]
set_property PACKAGE_PIN AG15 [get_ports {DDR4PL_DQ[10]}]
set_property PACKAGE_PIN AK12 [get_ports {DDR4PL_DQ[11]}]
set_property PACKAGE_PIN AG14 [get_ports {DDR4PL_DQ[12]}]
set_property PACKAGE_PIN AK14 [get_ports {DDR4PL_DQ[13]}]
set_property PACKAGE_PIN AF15 [get_ports {DDR4PL_DQ[14]}]
set_property PACKAGE_PIN AJ14 [get_ports {DDR4PL_DQ[15]}]
set_property PACKAGE_PIN AC16 [get_ports {DDR4PL_DQ[16]}]
set_property PACKAGE_PIN AE19 [get_ports {DDR4PL_DQ[17]}]
set_property PACKAGE_PIN AD17 [get_ports {DDR4PL_DQ[18]}]
set_property PACKAGE_PIN AD19 [get_ports {DDR4PL_DQ[19]}]
set_property PACKAGE_PIN AC17 [get_ports {DDR4PL_DQ[20]}]
set_property PACKAGE_PIN AE17 [get_ports {DDR4PL_DQ[21]}]
set_property PACKAGE_PIN AC18 [get_ports {DDR4PL_DQ[22]}]
set_property PACKAGE_PIN AD16 [get_ports {DDR4PL_DQ[23]}]
set_property PACKAGE_PIN AE18 [get_ports {DDR4PL_DQ[24]}]
set_property PACKAGE_PIN AK16 [get_ports {DDR4PL_DQ[25]}]
set_property PACKAGE_PIN AG18 [get_ports {DDR4PL_DQ[26]}]
set_property PACKAGE_PIN AJ17 [get_ports {DDR4PL_DQ[27]}]
set_property PACKAGE_PIN AH17 [get_ports {DDR4PL_DQ[28]}]
set_property PACKAGE_PIN AH18 [get_ports {DDR4PL_DQ[29]}]
set_property PACKAGE_PIN AJ16 [get_ports {DDR4PL_DQ[30]}]
set_property PACKAGE_PIN AF18 [get_ports {DDR4PL_DQ[31]}]

set_property PACKAGE_PIN AB14 [get_ports {DDR4PL_DQS_N[0]}]
set_property PACKAGE_PIN AA14 [get_ports {DDR4PL_DQS_P[0]}]
set_property PACKAGE_PIN AK15 [get_ports {DDR4PL_DQS_N[1]}]
set_property PACKAGE_PIN AJ15 [get_ports {DDR4PL_DQS_P[1]}]
set_property PACKAGE_PIN AB16 [get_ports {DDR4PL_DQS_N[2]}]
set_property PACKAGE_PIN AA16 [get_ports {DDR4PL_DQS_P[2]}]
set_property PACKAGE_PIN AK18 [get_ports {DDR4PL_DQS_N[3]}]
set_property PACKAGE_PIN AK17 [get_ports {DDR4PL_DQS_P[3]}]

set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DM[0]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DM[1]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DM[2]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DM[3]}]

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
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[16]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[17]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[18]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[19]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[20]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[21]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[22]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[23]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[24]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[25]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[26]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[27]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[28]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[29]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[30]}]
set_property IOSTANDARD POD12_DCI [get_ports {DDR4PL_DQ[31]}]

set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_N[0]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_P[0]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_N[1]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_P[1]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_N[2]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_P[2]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_N[3]}]
set_property IOSTANDARD DIFF_POD12_DCI [get_ports {DDR4PL_DQS_P[3]}]

# -------------------------------------------------------------------------------------------------
#  DDR (bank 65)
# -------------------------------------------------------------------------------------------------

set_property INTERNAL_VREF 0.600 [get_iobanks 65]

set_property PACKAGE_PIN AG6 [get_ports {DDR4PL_A[0]}]
set_property PACKAGE_PIN AG5 [get_ports {DDR4PL_A[1]}]
set_property PACKAGE_PIN AK7 [get_ports {DDR4PL_A[2]}]
set_property PACKAGE_PIN AK6 [get_ports {DDR4PL_A[3]}]
set_property PACKAGE_PIN AJ4 [get_ports {DDR4PL_A[4]}]
set_property PACKAGE_PIN AK4 [get_ports {DDR4PL_A[5]}]
set_property PACKAGE_PIN AF6 [get_ports {DDR4PL_A[6]}]
set_property PACKAGE_PIN AF5 [get_ports {DDR4PL_A[7]}]
set_property PACKAGE_PIN AH4 [get_ports {DDR4PL_A[8]}]
set_property PACKAGE_PIN AK3 [get_ports {DDR4PL_A[9]}]
set_property PACKAGE_PIN AK2 [get_ports {DDR4PL_A[10]}]
set_property PACKAGE_PIN AJ2 [get_ports {DDR4PL_A[11]}]
set_property PACKAGE_PIN AJ1 [get_ports {DDR4PL_A[12]}]
set_property PACKAGE_PIN AH3 [get_ports {DDR4PL_A[13]}]
set_property PACKAGE_PIN AH2 [get_ports {DDR4PL_A[14]}]
set_property PACKAGE_PIN AG4 [get_ports {DDR4PL_A[15]}]
set_property PACKAGE_PIN AG3 [get_ports {DDR4PL_A[16]}]
set_property PACKAGE_PIN AF7 [get_ports {DDR4PL_A[17]}]
#set_property PACKAGE_PIN AF7 [get_ports {DDR4PL_BG1_A17}]

set_property PACKAGE_PIN AK5 [get_ports {DDR4PL_CK_N}]
set_property PACKAGE_PIN AJ5 [get_ports {DDR4PL_CK_P}]

set_property PACKAGE_PIN AG1 [get_ports {DDR4PL_ACT_n}]
set_property PACKAGE_PIN AH1 [get_ports {DDR4PL_BA[0]}]
set_property PACKAGE_PIN AF3 [get_ports {DDR4PL_BA[1]}]
set_property PACKAGE_PIN AF1 [get_ports {DDR4PL_ODT}]
set_property PACKAGE_PIN AF8 [get_ports {DDR4PL_BG[0]}]
#set_property PACKAGE_PIN AF7 [get_ports {DDR4PL_BG[1]}]
set_property PACKAGE_PIN AE9 [get_ports {DDR4PL_CS_n}]
set_property PACKAGE_PIN AE8 [get_ports {DDR4PL_CKE}]
set_property PACKAGE_PIN AG9 [get_ports {DDR4PL_RST_n}]

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

set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_A[17]}]
#set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BG1_A[17]}]

set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {DDR4PL_CK_N}]
set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {DDR4PL_CK_P}]

set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_ACT_n}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BA[0]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BA[1]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_ODT}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BG[0]}]
#set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_BG[1]}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_CS_n}]
set_property IOSTANDARD SSTL12_DCI [get_ports {DDR4PL_CKE}]
set_property IOSTANDARD LVCMOS12 [get_ports {DDR4PL_RST_n}]

# -------------------------------------------------------------------------------------------------
# PL CLK 100 (bank 65)
# -------------------------------------------------------------------------------------------------
set_property PACKAGE_PIN AH6 [get_ports {CLK100_P}]
set_property PACKAGE_PIN AJ6 [get_ports {CLK100_N}]

set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {CLK100_P}]
set_property IOSTANDARD DIFF_SSTL12_DCI [get_ports {CLK100_N}]

# -------------------------------------------------------------------------------------------------
# PCIe Reset & IOs (bank 65)
# -------------------------------------------------------------------------------------------------

set_property PACKAGE_PIN AF2 [get_ports {PL_PERST_n}]
set_property IOSTANDARD SSTL12_DCI [get_ports {PL_PERST_n}]

set_property PACKAGE_PIN AH12 [get_ports {IO_B65_L1_AH12_P}]
set_property PACKAGE_PIN AJ12 [get_ports {IO_B65_L1_AJ12_N}]
set_property PACKAGE_PIN AG8 [get_ports {IO_B65_L11_GC_AG8_P}]
set_property PACKAGE_PIN AH8 [get_ports {IO_B65_L11_GC_AH8_N}]
set_property PACKAGE_PIN AH7 [get_ports {IO_B65_L12_GC_AH7_P}]
set_property PACKAGE_PIN AJ7 [get_ports {IO_B65_L12_GC_AJ7_N}]
set_property PACKAGE_PIN AF11 [get_ports {IO_B65_L2_AF11_N}]
set_property PACKAGE_PIN AF12 [get_ports {IO_B65_L2_AF12_P}]
set_property PACKAGE_PIN AG11 [get_ports {IO_B65_L3_AD15_AG11_P}]
set_property PACKAGE_PIN AH11 [get_ports {IO_B65_L3_AD15_AH11_N}]
set_property PACKAGE_PIN AK11 [get_ports {IO_B65_L4_AD7_AK11_N}]
set_property PACKAGE_PIN AJ11 [get_ports {IO_B65_L4_AD7_ALERT_AJ11_P}]
set_property PACKAGE_PIN AJ10 [get_ports {IO_B65_L5_AD14_AJ10_P}]
set_property PACKAGE_PIN AK10 [get_ports {IO_B65_L5_AD14_AK10_N}]
set_property PACKAGE_PIN AF10 [get_ports {IO_B65_L6_AD6_AF10_P}]
set_property PACKAGE_PIN AG10 [get_ports {IO_B65_L6_AD6_AG10_N}]
set_property PACKAGE_PIN AK8 [get_ports {IO_B65_L7_AD13_AK8_N}]
set_property PACKAGE_PIN AK9 [get_ports {IO_B65_L7_AD13_AK9_P}]
set_property PACKAGE_PIN AH9 [get_ports {IO_B65_L8_AD5_AH9_P}]
set_property PACKAGE_PIN AJ9 [get_ports {IO_B65_L8_AD5_AJ9_N}]

set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L1_AH12_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L1_AJ12_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L11_GC_AG8_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L11_GC_AH8_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L12_GC_AH7_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L12_GC_AJ7_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L2_AF11_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L2_AF12_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L3_AD15_AG11_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L3_AD15_AH11_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L4_AD7_AK11_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L4_AD7_ALERT_AJ11_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L5_AD14_AJ10_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L5_AD14_AK10_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L6_AD6_AF10_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L6_AD6_AG10_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L7_AD13_AK8_N}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L7_AD13_AK9_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L8_AD5_AH9_P}]
set_property IOSTANDARD LVCMOS12 [get_ports {IO_B65_L8_AD5_AJ9_N}]

# -------------------------------------------------------------------------------------------------
# bank 66
# -------------------------------------------------------------------------------------------------

set_property PACKAGE_PIN W9 [get_ports {PWR_SYNC}]

set_property PACKAGE_PIN AE3  [get_ports {IO_B66_AE3}]
set_property PACKAGE_PIN AC12 [get_ports {IO_B66_L1_AC12_P}]
set_property PACKAGE_PIN AD12 [get_ports {IO_B66_L1_AD12_N}]
set_property PACKAGE_PIN AA7  [get_ports {IO_B66_L10_AD4_AA7_N}]
set_property PACKAGE_PIN Y7   [get_ports {IO_B66_L10_AD4_Y7_P}]
set_property PACKAGE_PIN AC7  [get_ports {IO_B66_L11_GC_AC7_N}]
set_property PACKAGE_PIN AC8  [get_ports {IO_B66_L11_GC_AC8_P}]
set_property PACKAGE_PIN AA8  [get_ports {IO_B66_L12_GC_AA8_P}]
set_property PACKAGE_PIN AB8  [get_ports {IO_B66_L12_GC_AB8_N}]
set_property PACKAGE_PIN AD7  [get_ports {IO_B66_L13_GC_AD7_P}]
set_property PACKAGE_PIN AE7  [get_ports {IO_B66_L13_GC_AE7_N}]
set_property PACKAGE_PIN AB5  [get_ports {IO_B66_L14_GC_AB5_N}]
set_property PACKAGE_PIN AB6  [get_ports {IO_B66_L14_GC_AB6_P}]
set_property PACKAGE_PIN AD5  [get_ports {IO_B66_L15_AD11_AD5_P}]
set_property PACKAGE_PIN AE5  [get_ports {IO_B66_L15_AD11_AE5_N}]
set_property PACKAGE_PIN AD4  [get_ports {IO_B66_L16_AD3_AD4_P}]
set_property PACKAGE_PIN AE4  [get_ports {IO_B66_L16_AD3_AE4_N}]
set_property PACKAGE_PIN AB4  [get_ports {IO_B66_L17_AD10_AB4_P}]
set_property PACKAGE_PIN AC4  [get_ports {IO_B66_L17_AD10_AC4_N}]
set_property PACKAGE_PIN AA5  [get_ports {IO_B66_L18_AD2_AA5_N}]
set_property PACKAGE_PIN AA6  [get_ports {IO_B66_L18_AD2_AA6_P}]
set_property PACKAGE_PIN AD2  [get_ports {IO_B66_L19_AD9_AD2_P}]
set_property PACKAGE_PIN AE2  [get_ports {IO_B66_L19_AD9_AE2_N}]
set_property PACKAGE_PIN AA11 [get_ports {IO_B66_L2_AA11_N}]
set_property PACKAGE_PIN AA12 [get_ports {IO_B66_L2_AA12_P}]
set_property PACKAGE_PIN AD1  [get_ports {IO_B66_L20_AD1_AD1_P}]
set_property PACKAGE_PIN AE1  [get_ports {IO_B66_L20_AD1_AE1_N}]
set_property PACKAGE_PIN AC2  [get_ports {IO_B66_L21_AD8_AC2_N}]
set_property PACKAGE_PIN AC3  [get_ports {IO_B66_L21_AD8_AC3_P}]
set_property PACKAGE_PIN AA3  [get_ports {IO_B66_L22_AD0_AA3_P}]
set_property PACKAGE_PIN AB3  [get_ports {IO_B66_L22_AD0_AB3_N}]
set_property PACKAGE_PIN AB1  [get_ports {IO_B66_L23_AB1_P}]
set_property PACKAGE_PIN AC1  [get_ports {IO_B66_L23_AC1_N}]
set_property PACKAGE_PIN AA1  [get_ports {IO_B66_L24_AA1_N}]
set_property PACKAGE_PIN AA2  [get_ports {IO_B66_L24_AA2_P}]
set_property PACKAGE_PIN AB11 [get_ports {IO_B66_L3_AD15_AB11_P}]
set_property PACKAGE_PIN AC11 [get_ports {IO_B66_L3_AD15_AC11_N}]
set_property PACKAGE_PIN AD10 [get_ports {IO_B66_L4_AD7_AD10_N}]
set_property PACKAGE_PIN AD11 [get_ports {IO_B66_L4_AD7_AD11_P}]
set_property PACKAGE_PIN AB10 [get_ports {IO_B66_L5_AD14_AB10_P}]
set_property PACKAGE_PIN AB9  [get_ports {IO_B66_L5_AD14_AB9_N}]
set_property PACKAGE_PIN AA10 [get_ports {IO_B66_L6_AD6_AA10_N}]
set_property PACKAGE_PIN Y10  [get_ports {IO_B66_L6_AD6_Y10_P}]
set_property PACKAGE_PIN AC9  [get_ports {IO_B66_L7_AD13_AC9_P}]
set_property PACKAGE_PIN AD9  [get_ports {IO_B66_L7_AD13_AD9_N}]
set_property PACKAGE_PIN AC6  [get_ports {IO_B66_L8_AD5_AC6_P}]
set_property PACKAGE_PIN AD6  [get_ports {IO_B66_L8_AD5_AD6_N}]
set_property PACKAGE_PIN W8   [get_ports {IO_B66_L9_AD12_W8_P}]
set_property PACKAGE_PIN Y8   [get_ports {IO_B66_L9_AD12_Y8_N}]
set_property PACKAGE_PIN Y1   [get_ports {IO_B66_Y1}]

set_property IOSTANDARD LVCMOS18 [get_ports {PWR_SYNC}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_AE3}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L1_AC12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L1_AD12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L10_AD4_AA7_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L10_AD4_Y7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L11_GC_AC7_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L11_GC_AC8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L12_GC_AA8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L12_GC_AB8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L13_GC_AD7_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L13_GC_AE7_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L14_GC_AB5_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L14_GC_AB6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L15_AD11_AD5_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L15_AD11_AE5_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L16_AD3_AD4_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L16_AD3_AE4_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L17_AD10_AB4_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L17_AD10_AC4_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L18_AD2_AA5_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L18_AD2_AA6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L19_AD9_AD2_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L19_AD9_AE2_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L2_AA11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L2_AA12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L20_AD1_AD1_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L20_AD1_AE1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L21_AD8_AC2_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L21_AD8_AC3_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L22_AD0_AA3_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L22_AD0_AB3_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L23_AB1_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L23_AC1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L24_AA1_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L24_AA2_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L3_AD15_AB11_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L3_AD15_AC11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L4_AD7_AD10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L4_AD7_AD11_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L5_AD14_AB10_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L5_AD14_AB9_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L6_AD6_AA10_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L6_AD6_Y10_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L7_AD13_AC9_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L7_AD13_AD9_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L8_AD5_AC6_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L8_AD5_AD6_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L9_AD12_W8_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_L9_AD12_Y8_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_B66_Y1}]

# -------------------------------------------------------------------------------------------------
# bank N - 46 (ZU4/5) or 47 (ZU7)
# -------------------------------------------------------------------------------------------------

set_property PACKAGE_PIN K11 [get_ports {IO_BN_L1_AD11_K11_N}]
set_property PACKAGE_PIN K12 [get_ports {IO_BN_L1_AD11_K12_P}]
set_property PACKAGE_PIN B14 [get_ports {IO_BN_L10_AD2_B14_N}]
set_property PACKAGE_PIN C14 [get_ports {IO_BN_L10_AD2_C14_P}]
set_property PACKAGE_PIN A13 [get_ports {IO_BN_L11_AD1_A13_N}]
set_property PACKAGE_PIN A14 [get_ports {IO_BN_L11_AD1_A14_P}]
set_property PACKAGE_PIN A12 [get_ports {IO_BN_L12_AD0_A12_N}]
set_property PACKAGE_PIN B12 [get_ports {IO_BN_L12_AD0_B12_P}]
set_property PACKAGE_PIN J12 [get_ports {IO_BN_L2_AD10_J12_N}]
set_property PACKAGE_PIN K13 [get_ports {IO_BN_L2_AD10_K13_P}]
set_property PACKAGE_PIN H12 [get_ports {IO_BN_L3_AD9_H12_N}]
set_property PACKAGE_PIN H13 [get_ports {IO_BN_L3_AD9_H13_P}]
set_property PACKAGE_PIN G14 [get_ports {IO_BN_L4_AD8_G14_N}]
set_property PACKAGE_PIN H14 [get_ports {IO_BN_L4_AD8_H14_P}]
set_property PACKAGE_PIN F13 [get_ports {IO_BN_L5_HDGC_AD7_F13_N}]
set_property PACKAGE_PIN G13 [get_ports {IO_BN_L5_HDGC_AD7_G13_P}]
set_property PACKAGE_PIN E12 [get_ports {IO_BN_L6_HDGC_AD6_E12_N}]
set_property PACKAGE_PIN F12 [get_ports {IO_BN_L6_HDGC_AD6_F12_P}]
set_property PACKAGE_PIN E13 [get_ports {IO_BN_L7_HDGC_AD5_E13_N}]
set_property PACKAGE_PIN E14 [get_ports {IO_BN_L7_HDGC_AD5_E14_P}]
set_property PACKAGE_PIN C13 [get_ports {IO_BN_L8_HDGC_AD4_C13_N}]
set_property PACKAGE_PIN D14 [get_ports {IO_BN_L8_HDGC_AD4_D14_P}]
set_property PACKAGE_PIN C12 [get_ports {IO_BN_L9_AD3_C12_N}]
set_property PACKAGE_PIN D12 [get_ports {IO_BN_L9_AD3_D12_P}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L1_AD11_K11_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L1_AD11_K12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L10_AD2_B14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L10_AD2_C14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L11_AD1_A13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L11_AD1_A14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L12_AD0_A12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L12_AD0_B12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L2_AD10_J12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L2_AD10_K13_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L3_AD9_H12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L3_AD9_H13_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L4_AD8_G14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L4_AD8_H14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L5_HDGC_AD7_F13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L5_HDGC_AD7_G13_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L6_HDGC_AD6_E12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L6_HDGC_AD6_F12_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L7_HDGC_AD5_E13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L7_HDGC_AD5_E14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L8_HDGC_AD4_C13_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L8_HDGC_AD4_D14_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L9_AD3_C12_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BN_L9_AD3_D12_P}]

# -------------------------------------------------------------------------------------------------
# bank O - 45 (ZU4/5) or 48 (ZU7)
# -------------------------------------------------------------------------------------------------

set_property PACKAGE_PIN L14 [get_ports {IO_BO_L1_AD15_L14_N}]
set_property PACKAGE_PIN L15 [get_ports {IO_BO_L1_AD15_L15_P}]
set_property PACKAGE_PIN B16 [get_ports {IO_BO_L10_AD10_B16_N}]
set_property PACKAGE_PIN C17 [get_ports {IO_BO_L10_AD10_C17_P}]
set_property PACKAGE_PIN A16 [get_ports {IO_BO_L11_AD9_A16_N}]
set_property PACKAGE_PIN A17 [get_ports {IO_BO_L11_AD9_A17_P}]
set_property PACKAGE_PIN A15 [get_ports {IO_BO_L12_AD8_A15_N}]
set_property PACKAGE_PIN B15 [get_ports {IO_BO_L12_AD8_B15_P}]
set_property PACKAGE_PIN K14 [get_ports {IO_BO_L2_AD14_K14_N}]
set_property PACKAGE_PIN K15 [get_ports {IO_BO_L2_AD14_K15_P}]
set_property PACKAGE_PIN J14 [get_ports {IO_BO_L3_AD13_J14_N}]
set_property PACKAGE_PIN J15 [get_ports {IO_BO_L3_AD13_J15_P}]
set_property PACKAGE_PIN H16 [get_ports {IO_BO_L4_AD12_H16_N}]
set_property PACKAGE_PIN J16 [get_ports {IO_BO_L4_AD12_J16_P}]
set_property PACKAGE_PIN G15 [get_ports {IO_BO_L5_HDGC_G15_N}]
set_property PACKAGE_PIN G16 [get_ports {IO_BO_L5_HDGC_G16_P}]
set_property PACKAGE_PIN F15 [get_ports {IO_BO_L6_HDGC_F15_N}]
set_property PACKAGE_PIN F16 [get_ports {IO_BO_L6_HDGC_F16_P}]
set_property PACKAGE_PIN D17 [get_ports {IO_BO_L7_HDGC_D17_N}]
set_property PACKAGE_PIN E17 [get_ports {IO_BO_L7_HDGC_E17_P}]
set_property PACKAGE_PIN D15 [get_ports {IO_BO_L8_HDGC_D15_N}]
set_property PACKAGE_PIN E15 [get_ports {IO_BO_L8_HDGC_E15_P}]
set_property PACKAGE_PIN C16 [get_ports {IO_BO_L9_AD11_C16_N}]
set_property PACKAGE_PIN D16 [get_ports {IO_BO_L9_AD11_D16_P}]

set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L1_AD15_L14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L1_AD15_L15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L10_AD10_B16_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L10_AD10_C17_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L11_AD9_A16_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L11_AD9_A17_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L12_AD8_A15_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L12_AD8_B15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L2_AD14_K14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L2_AD14_K15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L3_AD13_J14_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L3_AD13_J15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L4_AD12_H16_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L4_AD12_J16_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L5_HDGC_G15_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L5_HDGC_G16_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L6_HDGC_F15_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L6_HDGC_F16_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L7_HDGC_D17_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L7_HDGC_E17_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L8_HDGC_D15_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L8_HDGC_E15_P}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L9_AD11_C16_N}]
set_property IOSTANDARD LVCMOS18 [get_ports {IO_BO_L9_AD11_D16_P}]

# -------------------------------------------------------------------------------------------------
# PS banks defined in the block design
# -------------------------------------------------------------------------------------------------

