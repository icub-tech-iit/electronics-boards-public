--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.1 (win64) Build 2552052 Fri May 24 14:49:42 MDT 2019
--Date        : Mon Dec  7 16:48:34 2020
--Host        : IITICUBLAP127 running 64-bit major release  (build 9200)
--Command     : generate_target UZCB_uP_wrapper.bd
--Design      : UZCB_uP_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity UZCB_uP_wrapper is
  port (
    DDR4_act_n : out STD_LOGIC;
    DDR4_adr : out STD_LOGIC_VECTOR ( 16 downto 0 );
    DDR4_ba : out STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_bg : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_ck_c : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_ck_t : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_cke : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_cs_n : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_dm_n : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_dq : inout STD_LOGIC_VECTOR ( 15 downto 0 );
    DDR4_dqs_c : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_dqs_t : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_odt : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_reset_n : out STD_LOGIC;
    ETH_CLK : out STD_LOGIC;
    ETH_CLK_90 : out STD_LOGIC;
    ETH_resetn : out STD_LOGIC;
    GMII_col : in STD_LOGIC;
    GMII_crs : in STD_LOGIC;
    GMII_rx_clk : in STD_LOGIC;
    GMII_rx_dv : in STD_LOGIC;
    GMII_rx_er : in STD_LOGIC;
    GMII_rxd : in STD_LOGIC_VECTOR ( 7 downto 0 );
    GMII_speed_mode : out STD_LOGIC_VECTOR ( 2 downto 0 );
    GMII_tx_clk : in STD_LOGIC;
    GMII_tx_en : out STD_LOGIC;
    GMII_tx_er : out STD_LOGIC;
    GMII_txd : out STD_LOGIC_VECTOR ( 7 downto 0 );
    GPIO_tri_o : out STD_LOGIC_VECTOR ( 7 downto 0 );
    MDIO_mdc : out STD_LOGIC;
    MDIO_mdio_io : inout STD_LOGIC;
    SYS_CLK_clk_n : in STD_LOGIC;
    SYS_CLK_clk_p : in STD_LOGIC;
    pl_clk1 : out STD_LOGIC;
    pl_resetn0 : out STD_LOGIC
  );
end UZCB_uP_wrapper;

architecture STRUCTURE of UZCB_uP_wrapper is
  component UZCB_uP is
  port (
    ETH_CLK : out STD_LOGIC;
    ETH_CLK_90 : out STD_LOGIC;
    ETH_resetn : out STD_LOGIC;
    pl_clk1 : out STD_LOGIC;
    pl_resetn0 : out STD_LOGIC;
    GPIO_tri_o : out STD_LOGIC_VECTOR ( 7 downto 0 );
    DDR4_act_n : out STD_LOGIC;
    DDR4_adr : out STD_LOGIC_VECTOR ( 16 downto 0 );
    DDR4_ba : out STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_bg : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_ck_c : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_ck_t : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_cke : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_cs_n : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_dm_n : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_dq : inout STD_LOGIC_VECTOR ( 15 downto 0 );
    DDR4_dqs_c : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_dqs_t : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_odt : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_reset_n : out STD_LOGIC;
    SYS_CLK_clk_n : in STD_LOGIC;
    SYS_CLK_clk_p : in STD_LOGIC;
    GMII_rx_clk : in STD_LOGIC;
    GMII_speed_mode : out STD_LOGIC_VECTOR ( 2 downto 0 );
    GMII_crs : in STD_LOGIC;
    GMII_col : in STD_LOGIC;
    GMII_rxd : in STD_LOGIC_VECTOR ( 7 downto 0 );
    GMII_rx_er : in STD_LOGIC;
    GMII_rx_dv : in STD_LOGIC;
    GMII_tx_clk : in STD_LOGIC;
    GMII_txd : out STD_LOGIC_VECTOR ( 7 downto 0 );
    GMII_tx_en : out STD_LOGIC;
    GMII_tx_er : out STD_LOGIC;
    MDIO_mdc : out STD_LOGIC;
    MDIO_mdio_i : in STD_LOGIC;
    MDIO_mdio_o : out STD_LOGIC;
    MDIO_mdio_t : out STD_LOGIC
  );
  end component UZCB_uP;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal MDIO_mdio_i : STD_LOGIC;
  signal MDIO_mdio_o : STD_LOGIC;
  signal MDIO_mdio_t : STD_LOGIC;
begin
MDIO_mdio_iobuf: component IOBUF
     port map (
      I => MDIO_mdio_o,
      IO => MDIO_mdio_io,
      O => MDIO_mdio_i,
      T => MDIO_mdio_t
    );
UZCB_uP_i: component UZCB_uP
     port map (
      DDR4_act_n => DDR4_act_n,
      DDR4_adr(16 downto 0) => DDR4_adr(16 downto 0),
      DDR4_ba(1 downto 0) => DDR4_ba(1 downto 0),
      DDR4_bg(0) => DDR4_bg(0),
      DDR4_ck_c(0) => DDR4_ck_c(0),
      DDR4_ck_t(0) => DDR4_ck_t(0),
      DDR4_cke(0) => DDR4_cke(0),
      DDR4_cs_n(0) => DDR4_cs_n(0),
      DDR4_dm_n(1 downto 0) => DDR4_dm_n(1 downto 0),
      DDR4_dq(15 downto 0) => DDR4_dq(15 downto 0),
      DDR4_dqs_c(1 downto 0) => DDR4_dqs_c(1 downto 0),
      DDR4_dqs_t(1 downto 0) => DDR4_dqs_t(1 downto 0),
      DDR4_odt(0) => DDR4_odt(0),
      DDR4_reset_n => DDR4_reset_n,
      ETH_CLK => ETH_CLK,
      ETH_CLK_90 => ETH_CLK_90,
      ETH_resetn => ETH_resetn,
      GMII_col => GMII_col,
      GMII_crs => GMII_crs,
      GMII_rx_clk => GMII_rx_clk,
      GMII_rx_dv => GMII_rx_dv,
      GMII_rx_er => GMII_rx_er,
      GMII_rxd(7 downto 0) => GMII_rxd(7 downto 0),
      GMII_speed_mode(2 downto 0) => GMII_speed_mode(2 downto 0),
      GMII_tx_clk => GMII_tx_clk,
      GMII_tx_en => GMII_tx_en,
      GMII_tx_er => GMII_tx_er,
      GMII_txd(7 downto 0) => GMII_txd(7 downto 0),
      GPIO_tri_o(7 downto 0) => GPIO_tri_o(7 downto 0),
      MDIO_mdc => MDIO_mdc,
      MDIO_mdio_i => MDIO_mdio_i,
      MDIO_mdio_o => MDIO_mdio_o,
      MDIO_mdio_t => MDIO_mdio_t,
      SYS_CLK_clk_n => SYS_CLK_clk_n,
      SYS_CLK_clk_p => SYS_CLK_clk_p,
      pl_clk1 => pl_clk1,
      pl_resetn0 => pl_resetn0
    );
end STRUCTURE;
