---------------------------------------------------------------------------------------------------
-- Project          : Mercury XU5 Reference Design
-- File description : Top Level
-- File name        : system_top_PE1.vhd
-- Author           : Diana Ungureanu
---------------------------------------------------------------------------------------------------
-- Copyright (c) 2018 by Enclustra GmbH, Switzerland. All rights are reserved. 
-- Unauthorized duplication of this document, in whole or in part, by any means is prohibited
-- without the prior written permission of Enclustra GmbH, Switzerland.
-- 
-- Although Enclustra GmbH believes that the information included in this publication is correct
-- as of the date of publication, Enclustra GmbH reserves the right to make changes at any time
-- without notice.
-- 
-- All information in this document may only be published by Enclustra GmbH, Switzerland.
---------------------------------------------------------------------------------------------------
-- Description:
-- This is a top-level file for Mercury XU5 Reference Design
--    
---------------------------------------------------------------------------------------------------
-- File history:
--
-- Version | Date       | Author           | Remarks
-- ------------------------------------------------------------------------------------------------
-- 1.0     | 24.04.2016 | D. Ungureanu     | First released version
-- 2.0     | 11.06.2018 | D. Ungureanu     | Consistency checks
-- 3.0     | 13.09.2018 | A. Buerkler      | PL ETH1 added
--
---------------------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------------
-- libraries
---------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library unisim;
use unisim.vcomponents.all;

---------------------------------------------------------------------------------------------------
-- entity declaration
---------------------------------------------------------------------------------------------------

entity system_top is
  port (

    -------------------------------------------------------------------------------------------
    -- processor system
    -------------------------------------------------------------------------------------------

    -- LEDs            
    Led1_N                                      : out   std_logic;
    Led2_N                                      : out   std_logic;
    Led3_N                                      : out   std_logic;

    I2C_SCL_PL                                  : inout std_logic;
    I2C_SDA_PL                                  : inout std_logic;
    
    -- MIG                
    DDR4PL_ACT_n                                : out   std_logic;
    DDR4PL_A                                    : out   std_logic_vector ( 16 downto 0 );
    DDR4PL_BA                                   : out   std_logic_vector ( 1 downto 0 );
--    DDR4PL_BG                                   : out   std_logic_vector ( 1 downto 0 );
    DDR4PL_BG                                   : out   std_logic_vector ( 0 to 0 );
    DDR4PL_CK_P                                 : out   std_logic_vector ( 0 to 0 );
    DDR4PL_CK_N                                 : out   std_logic_vector ( 0 to 0 );
    DDR4PL_CKE                                  : out   std_logic_vector ( 0 to 0 );
    DDR4PL_CS_n                                 : out   std_logic_vector ( 0 to 0 );
    DDR4PL_DM                                   : inout std_logic_vector ( 1 downto 0 );
    DDR4PL_DQ                                   : inout std_logic_vector ( 15 downto 0 );
    DDR4PL_DQS_N                                : inout std_logic_vector ( 1 downto 0 );
    DDR4PL_DQS_P                                : inout std_logic_vector ( 1 downto 0 );
    DDR4PL_ODT                                  : out   std_logic_vector ( 0 to 0 );
    DDR4PL_RST_n_PL                             : out   std_logic;
                
    CLK100_PL_N                                 : in    std_logic;
    CLK100_PL_P                                 : in    std_logic;

    ---------------------------------------------------------------------------------------------------
    -- bank 65
    ---------------------------------------------------------------------------------------------------
    IO_B65_L1_W8                                : inout std_logic;
    IO_B65_L1_Y8                                : inout std_logic;
    IO_B65_L10_AD4_H3_N                         : inout std_logic;
    IO_B65_L10_AD4_H4_P                         : inout std_logic;
    IO_B65_L11_GC_K3_N                          : inout std_logic;
    IO_B65_L11_GC_K4_P                          : inout std_logic;
    IO_B65_L12_GC_L2_N                          : inout std_logic;
    IO_B65_L12_GC_L3_P                          : inout std_logic;
    IO_B65_L13_GC_L6_N                          : inout std_logic;
    IO_B65_L13_GC_L7_P                          : inout std_logic;
    IO_B65_L14_GC_L5_N                          : inout std_logic;
    IO_B65_L14_GC_M6_P                          : inout std_logic;
    IO_B65_L15_AD11_N6_N                        : inout std_logic;
    IO_B65_L15_AD11_N7_P                        : inout std_logic;
    IO_B65_L16_AD3_P6_N                         : inout std_logic;
    IO_B65_L16_AD3_P7_P                         : inout std_logic;
    IO_B65_L17_AD10_N8_N                        : inout std_logic;
    IO_B65_L17_AD10_N9_P                        : inout std_logic;
    IO_B65_L18_AD2_L8_N                         : inout std_logic;
    IO_B65_L18_AD2_M8_P                         : inout std_logic;
    IO_B65_L19_AD9_J4_N                         : inout std_logic;
    IO_B65_L19_AD9_J5_P                         : inout std_logic;
    IO_B65_L2_U9                                : inout std_logic;
    IO_B65_L2_V9                                : inout std_logic;
    IO_B65_L20_AD1_H6_N                         : inout std_logic;
    IO_B65_L20_AD1_J6_P                         : inout std_logic;
    IO_B65_L21_AD8_H7_N                         : inout std_logic;
    IO_B65_L21_AD8_J7_P                         : inout std_logic;
    IO_B65_L22_AD0_K7_N                         : inout std_logic;
    IO_B65_L22_AD0_K8_P                         : inout std_logic;
    IO_B65_L23_J9_N                             : inout std_logic;
    IO_B65_L23_SCLK_K9_P                        : inout std_logic;
    IO_B65_L24_PERSTN_H8_N                      : inout std_logic;
    IO_B65_L24_SDA_H9_P                         : inout std_logic;
    IO_B65_L3_AD15_U8_P                         : inout std_logic;
    IO_B65_L3_AD15_V8_N                         : inout std_logic;
    IO_B65_L4_AD7_ALERT_R8_P                    : inout std_logic;
    IO_B65_L4_AD7_T8_N                          : inout std_logic;
    IO_B65_L5_AD14_R7_P                         : inout std_logic;
    IO_B65_L5_AD14_T7_N                         : inout std_logic;
    IO_B65_L6_AD6_R6_P                          : inout std_logic;
    IO_B65_L6_AD6_T6_N                          : inout std_logic;
    IO_B65_L7_AD13_K1_N                         : inout std_logic;
    IO_B65_L7_AD13_L1_P                         : inout std_logic;
    IO_B65_L8_AD5_H1_N                          : inout std_logic;
    IO_B65_L8_AD5_J1_P                          : inout std_logic;
    IO_B65_L9_AD12_J2_N                         : inout std_logic;
    IO_B65_L9_AD12_K2_P                         : inout std_logic;    


    ---------------------------------------------------------------------------------------------------
    -- bank 66
    ---------------------------------------------------------------------------------------------------
    IO_B66_L1_F1_N                                : inout std_logic;
    IO_B66_L1_G1_P                                : inout std_logic;
    IO_B66_L10_AD4_A4_N                           : inout std_logic;
    IO_B66_L10_AD4_B4_P                           : inout std_logic;
    IO_B66_L11_GC_C4_N                            : inout std_logic;
    IO_B66_L11_GC_D4_P                            : inout std_logic;
    IO_B66_L12_GC_C2_N                            : inout std_logic;
    IO_B66_L12_GC_C3_P                            : inout std_logic;
    IO_B66_L13_GC_D6_N                            : inout std_logic;
    IO_B66_L13_GC_D7_P                            : inout std_logic;
    IO_B66_L14_GC_D5_N                            : inout std_logic;
    IO_B66_L14_GC_E5_P                            : inout std_logic;
    IO_B66_L15_AD11_F6_N                          : inout std_logic;
    IO_B66_L15_AD11_G6_P                          : inout std_logic;
    IO_B66_L16_AD3_F7_N                           : inout std_logic;
    IO_B66_L16_AD3_G8_P                           : inout std_logic;
    IO_B66_L17_AD10_E8_N                          : inout std_logic;
    IO_B66_L17_AD10_F8_P                          : inout std_logic;
    IO_B66_L18_AD2_D9_N                           : inout std_logic;
    IO_B66_L18_AD2_E9_P                           : inout std_logic;
    IO_B66_L19_AD9_A5_N                           : inout std_logic;
    IO_B66_L19_AD9_B5_P                           : inout std_logic;
    IO_B66_L2_D1_N                                : inout std_logic;
    IO_B66_L2_E1_P                                : inout std_logic;
    IO_B66_L20_AD1_B6_N                           : inout std_logic;
    IO_B66_L20_AD1_C6_P                           : inout std_logic;
    IO_B66_L21_AD8_A6_N                           : inout std_logic;
    IO_B66_L21_AD8_A7_P                           : inout std_logic;
    IO_B66_L22_AD0_B8_N                           : inout std_logic;
    IO_B66_L22_AD0_C8_P                           : inout std_logic;
    IO_B66_L23_A8_N                               : inout std_logic;
    IO_B66_L23_A9_P                               : inout std_logic;
    IO_B66_L24_B9_N                               : inout std_logic;
    IO_B66_L24_C9_P                               : inout std_logic;
    IO_B66_L3_AD15_E2_N                           : inout std_logic;
    IO_B66_L3_AD15_F2_P                           : inout std_logic;
    IO_B66_L4_AD7_F3_N                            : inout std_logic;
    IO_B66_L4_AD7_G3_P                            : inout std_logic;
    IO_B66_L5_AD14_E3_N                           : inout std_logic;
    IO_B66_L5_AD14_E4_P                           : inout std_logic;
    IO_B66_L6_AD6_F5_N                            : inout std_logic;
    IO_B66_L6_AD6_G5_P                            : inout std_logic;
    IO_B66_L7_AD13_B1_N                           : inout std_logic;
    IO_B66_L7_AD13_C1_P                           : inout std_logic;
    IO_B66_L8_AD5_A1_N                            : inout std_logic;
    IO_B66_L8_AD5_A2_P                            : inout std_logic;
    IO_B66_L9_AD12_A3_N                           : inout std_logic;
    IO_B66_L9_AD12_B3_P                           : inout std_logic;

    ---------------------------------------------------------------------------------------------------
    -- bank N - 24 (ZU2/3) or 44 (ZU4/5)
    ---------------------------------------------------------------------------------------------------
    IO_BN_L1_AD15_AE14_N                        : inout std_logic;
    IO_BN_L1_AD15_AE15_P                        : inout std_logic;
    IO_BN_L10_AD10_Y13_N                        : inout std_logic;
    IO_BN_L10_AD10_Y14_P                        : inout std_logic;
    IO_BN_L11_AD9_W11_N                         : inout std_logic;
    IO_BN_L11_AD9_W12_P                         : inout std_logic;
    IO_BN_L12_AD8_AA12_N                        : inout std_logic;
    IO_BN_L12_AD8_Y12_P                         : inout std_logic;
    IO_BN_L2_AD14_AG14_P                        : inout std_logic;
    IO_BN_L2_AD14_AH14_N                        : inout std_logic;
    IO_BN_L3_AD13_AG13_P                        : inout std_logic;
    IO_BN_L3_AD13_AH13_N                        : inout std_logic;
    IO_BN_L4_AD12_AE13_P                        : inout std_logic;
    IO_BN_L4_AD12_AF13_N                        : inout std_logic;
    IO_BN_L5_HDGC_AD14_N                        : inout std_logic;
    IO_BN_L5_HDGC_AD15_P                        : inout std_logic;
    IO_BN_L6_HDGC_AC13_N                        : inout std_logic;
    IO_BN_L6_HDGC_AC14_P                        : inout std_logic;
    IO_BN_L7_HDGC_AA13_P                        : inout std_logic;
    IO_BN_L7_HDGC_AB13_N                        : inout std_logic;
    IO_BN_L8_HDGC_AB14_N                        : inout std_logic;
    IO_BN_L8_HDGC_AB15_P                        : inout std_logic;
    IO_BN_L9_AD11_W13_N                         : inout std_logic;
    IO_BN_L9_AD11_W14_P                         : inout std_logic;

    ---------------------------------------------------------------------------------------------------
    -- bank O - 44 (ZU2/3) or 43 (ZU4/5)
    ---------------------------------------------------------------------------------------------------
    IO_BO_L1_AD11_AG10_P                        : inout std_logic;
    IO_BO_L1_AD11_AH10_N                        : inout std_logic;
    IO_BO_L10_AD2_W10_P                         : inout std_logic;
    IO_BO_L10_AD2_Y10_N                         : inout std_logic;
    IO_BO_L11_AD1_AA8_N                         : inout std_logic;
    IO_BO_L11_AD1_Y9_P                          : inout std_logic;
    IO_BO_L12_AD0_AB10_P                        : inout std_logic;
    IO_BO_L12_AD0_AB9_N                         : inout std_logic;
    IO_BO_L2_AD10_AF11_P                        : inout std_logic;
    IO_BO_L2_AD10_AG11_N                        : inout std_logic;
    IO_BO_L3_AD9_AH11_N                         : inout std_logic;
    IO_BO_L3_AD9_AH12_P                         : inout std_logic;
    IO_BO_L4_AD8_AE10_P                         : inout std_logic;
    IO_BO_L4_AD8_AF10_N                         : inout std_logic;
    IO_BO_L5_HDGC_AD7_AE12_P                    : inout std_logic;
    IO_BO_L5_HDGC_AD7_AF12_N                    : inout std_logic;
    IO_BO_L6_HDGC_AD6_AC12_P                    : inout std_logic;
    IO_BO_L6_HDGC_AD6_AD12_N                    : inout std_logic;
    IO_BO_L7_HDGC_AD5_AD10_N                    : inout std_logic;
    IO_BO_L7_HDGC_AD5_AD11_P                    : inout std_logic;
    IO_BO_L8_HDGC_AD4_AB11_P                    : inout std_logic;
    IO_BO_L8_HDGC_AD4_AC11_N                    : inout std_logic;
    IO_BO_L9_AD3_AA10_N                         : inout std_logic;
    IO_BO_L9_AD3_AA11_P                         : inout std_logic;

    ---------------------------------------------------------------------------------------------------
    -- bank 25 (ZU2/3) or 45 (ZU4/5)
    -- bank 26 (ZU2/3) or 46 (ZU4/5)
    ---------------------------------------------------------------------------------------------------    

    IO_BE_L8_HDGC_D11_N                         : inout std_logic;
    IO_BE_L8_HDGC_E12_P                         : inout std_logic;
    IO_BE_L7_HDGC_D10_N                         : inout std_logic;
    IO_BE_L7_HDGC_E10_P                         : inout std_logic;
    IO_BF_L8_HDGC_AD4_E15_N                     : inout std_logic;
    IO_BF_L8_HDGC_AD4_F15_P                     : inout std_logic;    
    
    ---------------------------------------------------------------------------------------------------
    -- Gigabit Ethernet interface 1 on PL side
    -- bank 25 (ZU2/3) or 45 (ZU4/5)
    ---------------------------------------------------------------------------------------------------
    ETH1_RXD                                : in    std_logic_vector ( 3 downto 0 );
    ETH1_RXCLK                              : in    std_logic;
    ETH1_RXCTL                              : in    std_logic;
    ETH1_TXD                                : out   std_logic_vector ( 3 downto 0 );
    ETH1_TXCLK                              : out   std_logic;
    ETH1_TXCTL                              : out   std_logic;
    ETH1_INT_n                              : in    std_logic;
    ETH1_RESET_n                            : out   std_logic;
    ETH1_MDC                                : out   std_logic;
    ETH1_MDIO                               : inout std_logic

  );
end system_top;

---------------------------------------------------------------------------------------------------
-- architecture declaration
---------------------------------------------------------------------------------------------------

architecture rtl of system_top is

    component UZCB_Core is
        port (
            DDR4_act_n      : out   std_logic;
            DDR4_adr        : out   std_logic_vector(16 downto 0);
            DDR4_ba         : out   std_logic_vector(1 downto 0);
            DDR4_bg         : out   std_logic_vector(0 to 0);
            DDR4_ck_c       : out   std_logic_vector(0 to 0);
            DDR4_ck_t       : out   std_logic_vector(0 to 0);
            DDR4_cke        : out   std_logic_vector(0 to 0);
            DDR4_cs_n       : out   std_logic_vector(0 to 0);
            DDR4_dm_n       : inout std_logic_vector(1 downto 0);
            DDR4_dq         : inout std_logic_vector(15 downto 0);
            DDR4_dqs_c      : inout std_logic_vector(1 downto 0);
            DDR4_dqs_t      : inout std_logic_vector(1 downto 0);
            DDR4_odt        : out   std_logic_vector(0 to 0);
            DDR4_reset_n    : out   std_logic;
            ETH_CLK         : out   std_logic;
            ETH_CLK_90      : out   std_logic;
            ETH_resetn      : out   std_logic;
            GMII_col        : in    std_logic;
            GMII_crs        : in    std_logic;
            GMII_rx_clk     : in    std_logic;
            GMII_rx_dv      : in    std_logic;
            GMII_rx_er      : in    std_logic;
            GMII_rxd        : in    std_logic_vector(7 downto 0);
            GMII_speed_mode : out   std_logic_vector(2 downto 0);
            GMII_tx_clk     : in    std_logic;
            GMII_tx_en      : out   std_logic;
            GMII_tx_er      : out   std_logic;
            GMII_txd        : out   std_logic_vector(7 downto 0);
            GPIO_tri_o      : out   std_logic_vector(7 downto 0);
            MDIO_mdc        : out   std_logic;
            MDIO_mdio_i     : in    std_logic;
            MDIO_mdio_o     : out   std_logic;
            MDIO_mdio_t     : out   std_logic;
            SYS_CLK_clk_n   : in    std_logic;
            SYS_CLK_clk_p   : in    std_logic;
            pl_clk1         : out   std_logic;
            pl_resetn0      : out   std_logic
        );
    end component UZCB_Core;

    component XU5_gmii2rgmii is
        port (
            Clk125          : in  std_logic;
            Clk125_90       : in  std_logic;
            Resetn          : in  std_logic;

            GMII_col        : out std_logic;
            GMII_crs        : out std_logic;
            GMII_rx_clk     : out std_logic;
            GMII_rx_dv      : out std_logic;
            GMII_rx_er      : out std_logic;
            GMII_rxd        : out std_logic_vector(7 downto 0);
            GMII_speed_mode : in  std_logic_vector(2 downto 0);
            GMII_tx_clk     : out std_logic;
            GMII_tx_en      : in  std_logic;
            GMII_tx_er      : in  std_logic;
            GMII_txd        : in  std_logic_vector(7 downto 0);

            RGMII_rxd       : in  std_logic_vector(3 downto 0);
            RGMII_rxclk     : in  std_logic;
            RGMII_rxctl     : in  std_logic;
            RGMII_txd       : out std_logic_vector(3 downto 0);
            RGMII_txclk     : out std_logic;
            RGMII_txctl     : out std_logic
        );
    end component XU5_gmii2rgmii;

-----------------------------------------------------------------------------------------------
-- signals
-----------------------------------------------------------------------------------------------

    signal Rst_N           : std_logic := '1';

    signal Rst             : std_logic := '0';
    signal Clk             : std_logic;
    signal RstCnt          : unsigned(15 downto 0) := (others => '0');
    signal LedCount        : unsigned(23 downto 0);  

    signal Gpio            : std_logic_vector (7 downto 0);

    signal ETH_CLK         : std_logic;
    signal ETH_CLK_90      : std_logic;
    signal ETH_resetn      : std_logic;
    signal GMII_col        : std_logic;
    signal GMII_crs        : std_logic;
    signal GMII_rx_clk     : std_logic;
    signal GMII_rx_dv      : std_logic;
    signal GMII_rx_er      : std_logic;
    signal GMII_rxd        : std_logic_vector(7 downto 0);
    signal GMII_speed_mode : std_logic_vector(2 downto 0);
    signal GMII_tx_clk     : std_logic;
    signal GMII_tx_en      : std_logic;
    signal GMII_tx_er      : std_logic;
    signal GMII_txd        : std_logic_vector(7 downto 0);

    signal MDIO_mdc           : std_logic;
    signal MDIO_mdio_in       : std_logic;
    signal MDIO_mdio_out      : std_logic;
    signal MDIO_mdio_tristate : std_logic;

begin

-----------------------------------------------------------------------------------------------
-- processor system
-----------------------------------------------------------------------------------------------

    UZCB_Core_i: component UZCB_Core
        port map (
            DDR4_act_n      => DDR4PL_ACT_n,
            DDR4_adr        => DDR4PL_A,
            DDR4_ba         => DDR4PL_BA,
            DDR4_bg         => DDR4PL_BG,
            DDR4_ck_c       => DDR4PL_CK_N,
            DDR4_ck_t       => DDR4PL_CK_P,
            DDR4_cke        => DDR4PL_CKE,
            DDR4_cs_n       => DDR4PL_CS_n,
            DDR4_dm_n       => DDR4PL_DM,
            DDR4_dq         => DDR4PL_DQ,
            DDR4_dqs_c      => DDR4PL_DQS_N,
            DDR4_dqs_t      => DDR4PL_DQS_P,
            DDR4_odt        => DDR4PL_ODT,
            DDR4_reset_n    => DDR4PL_RST_n_PL,
            ETH_CLK         => ETH_CLK,
            ETH_CLK_90      => ETH_CLK_90,
            ETH_resetn      => ETH_resetn,
            GMII_col        => GMII_col,
            GMII_crs        => GMII_crs,
            GMII_rx_clk     => GMII_rx_clk,
            GMII_rx_dv      => GMII_rx_dv,
            GMII_rx_er      => GMII_rx_er,
            GMII_rxd        => GMII_rxd,
            GMII_speed_mode => GMII_speed_mode,
            GMII_tx_clk     => GMII_tx_clk,
            GMII_tx_en      => GMII_tx_en,
            GMII_tx_er      => GMII_tx_er,
            GMII_txd        => GMII_txd,
            GPIO_tri_o      => GPIO(7 downto 0),
            MDIO_mdc        => MDIO_mdc,
            MDIO_mdio_i     => MDIO_mdio_in,
            MDIO_mdio_o     => MDIO_mdio_out,
            MDIO_mdio_t     => MDIO_mdio_tristate,
            SYS_CLK_clk_n   => CLK100_PL_N,
            SYS_CLK_clk_p   => CLK100_PL_P,
            pl_clk1         => Clk,
            pl_resetn0      => Rst_N

        );

--    Led1_N   <= not Gpio(0);
--    Led2_N   <= not Gpio(1);
    Led3_N   <= not Gpio(2);

    ------------------------------------------------------------------------------------------------
    --  Clock and Reset
    ------------------------------------------------------------------------------------------------ 
       
    process (Clk)
    begin
        if rising_edge (Clk) then
            if (not RstCnt) = 0 then
                Rst    <= '0';
            else
                Rst    <= '1';
                RstCnt <= RstCnt + 1;
            end if;
        end if;
    end process;
    
    ------------------------------------------------------------------------------------------------
    -- Blinking LED counter & LED assignment
    ------------------------------------------------------------------------------------------------
   
    process (Clk)
    begin
        if rising_edge (Clk) then
            if Rst = '1' then
                LedCount    <= (others => '0');
            else
                LedCount <= LedCount + 1;
            end if;
        end if;
    end process;    
    
    Led1_N <= not LedCount(LedCount'high);
    Led2_N <= not LedCount(LedCount'high-1); -- 2 times faster

    I2C_SCL_PL <= 'Z';
    I2C_SDA_PL <= 'Z';

    ------------------------------------------------------------------------------------------------
    -- PL Ethernet
    ------------------------------------------------------------------------------------------------

    i_gmii2rgmii : XU5_gmii2rgmii
        port map (
            Clk125          => ETH_CLK,
            Clk125_90       => ETH_CLK_90,
            Resetn          => ETH_resetn,

            GMII_col        => GMII_col,
            GMII_crs        => GMII_crs,
            GMII_rx_clk     => GMII_rx_clk,
            GMII_rx_dv      => GMII_rx_dv,
            GMII_rx_er      => GMII_rx_er,
            GMII_rxd        => GMII_rxd,
            GMII_speed_mode => GMII_speed_mode,
            GMII_tx_clk     => GMII_tx_clk,
            GMII_tx_en      => GMII_tx_en,
            GMII_tx_er      => GMII_tx_er,
            GMII_txd        => GMII_txd,

            RGMII_rxd       => ETH1_RXD,
            RGMII_rxclk     => ETH1_RXCLK,
            RGMII_rxctl     => ETH1_RXCTL,
            RGMII_txd       => ETH1_TXD,
            RGMII_txclk     => ETH1_TXCLK,
            RGMII_txctl     => ETH1_TXCTL
        );

    ETH1_RESET_n        <= ETH_resetn;

    ETH1_MDC <= MDIO_mdc;
    ETH1_MDIO <= MDIO_mdio_out when (MDIO_mdio_tristate = '0') else 'Z';
    MDIO_mdio_in <= ETH1_MDIO;

end rtl;

---------------------------------------------------------------------------------------------------
-- eof
---------------------------------------------------------------------------------------------------
