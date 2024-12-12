---------------------------------------------------------------------------------------------------
-- Project          : Mercury+ XU8 Reference Design
-- File description : Top Level
-- File name        : system_top_PE1.vhd
-- Author           : Daniel Duerner
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
-- This is a top-level file for Mercury+ XU8 Reference Design
--    
---------------------------------------------------------------------------------------------------
-- File history:
--
-- Version | Date       | Author           | Remarks
-- ------------------------------------------------------------------------------------------------
-- 1.0     | 13.04.2018 | D. Duerner       | First released version
-- 2.0     | 11.06.2018 | D. Ungureanu     | Consistency checks
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
	Led2_N							: out	std_logic;

    -- I2C on PL side
    I2c_Scl							: inout	std_logic;
    I2c_Sda							: inout	std_logic;
	
	-- 	-- DDRPL	(bank 64 & 65)				
    DDR4PL_ACT_n					: out 	std_logic;
	
	-- DDR4PL_BG1_A17 is shared:	
	-- DDR with 18 Address Bits & 1 BankGroup Bits
    DDR4PL_A 						: out 	std_logic_vector ( 17 downto 0 );
	DDR4PL_BG 						: out 	std_logic_vector ( 0 to 0 );
	
	-- DDR with 17 Address Bits & 2 BankGroup Bits
--	DDR4PL_A 						: out 	std_logic_vector ( 16 downto 0 );
--	DDR4PL_BG 						: out 	std_logic_vector ( 1 to 0 );	
	
    DDR4PL_BA 						: out 	std_logic_vector ( 1 downto 0 );
    DDR4PL_CK_P 					: out 	std_logic_vector ( 0 to 0 );
    DDR4PL_CK_N 					: out 	std_logic_vector ( 0 to 0 );
    DDR4PL_CKE 						: out 	std_logic_vector ( 0 to 0 );
    DDR4PL_CS_n 					: out 	std_logic_vector ( 0 to 0 );
    DDR4PL_DM 						: inout std_logic_vector ( 3 downto 0 );
    DDR4PL_DQ 						: inout std_logic_vector ( 31 downto 0 );
    DDR4PL_DQS_N 					: inout std_logic_vector ( 3 downto 0 );
	DDR4PL_DQS_P 					: inout std_logic_vector ( 3 downto 0 );
    DDR4PL_ODT 						: out 	std_logic_vector ( 0 to 0 );
    DDR4PL_RST_n	 				: out 	std_logic;
				
    CLK100_N 						: in 	std_logic;
    CLK100_P 						: in 	std_logic;
    
	---------------------------------------------------------------------------------------------------
	-- HP bank 64 (1.2 V)
	---------------------------------------------------------------------------------------------------
	
	IO_B64_AC19										: inout	std_logic;
	IO_B64_AF17										: inout	std_logic;
	IO_B64_AG19										: inout	std_logic;
	IO_B64_AH16										: inout	std_logic;
	
	
	---------------------------------------------------------------------------------------------------
	-- HP bank 65 (1.2 V)
	---------------------------------------------------------------------------------------------------
	
	PL_PERST_n										: in	std_logic;

	IO_B65_L1_AH12_P					            : inout	std_logic;
	IO_B65_L1_AJ12_N					            : inout	std_logic;
	IO_B65_L11_GC_AG8_P					            : inout	std_logic;
	IO_B65_L11_GC_AH8_N					            : inout	std_logic;
	IO_B65_L12_GC_AH7_P					            : inout	std_logic;
	IO_B65_L12_GC_AJ7_N					            : inout	std_logic;
	IO_B65_L2_AF11_N					            : inout	std_logic;
	IO_B65_L2_AF12_P					            : inout	std_logic;
	IO_B65_L3_AD15_AG11_P				            : inout	std_logic;
	IO_B65_L3_AD15_AH11_N				            : inout	std_logic;
	IO_B65_L4_AD7_AK11_N				            : inout	std_logic;
	IO_B65_L4_AD7_ALERT_AJ11_P			            : inout	std_logic;
	IO_B65_L5_AD14_AJ10_P				            : inout	std_logic;
	IO_B65_L5_AD14_AK10_N				            : inout	std_logic;
	IO_B65_L6_AD6_AF10_P				            : inout	std_logic;
	IO_B65_L6_AD6_AG10_N				            : inout	std_logic;
	IO_B65_L7_AD13_AK8_N				            : inout	std_logic;
	IO_B65_L7_AD13_AK9_P				            : inout	std_logic;
	IO_B65_L8_AD5_AH9_P					            : inout	std_logic;
	IO_B65_L8_AD5_AJ9_N					            : inout	std_logic;


	---------------------------------------------------------------------------------------------------
	-- HP bank 66 (max 1.8 V)
	---------------------------------------------------------------------------------------------------
	IO_B66_AE3						                : inout	std_logic;
	IO_B66_L1_AC12_P				        		: inout	std_logic;
	IO_B66_L1_AD12_N				        		: inout	std_logic;
	IO_B66_L10_AD4_AA7_N			        		: inout	std_logic;
	IO_B66_L10_AD4_Y7_P				        		: inout	std_logic;
	IO_B66_L11_GC_AC7_N				        		: inout	std_logic;
	IO_B66_L11_GC_AC8_P				        		: inout	std_logic;
	IO_B66_L12_GC_AA8_P				        		: inout	std_logic;
	IO_B66_L12_GC_AB8_N				        		: inout	std_logic;
	IO_B66_L13_GC_AD7_P				        		: inout	std_logic;
	IO_B66_L13_GC_AE7_N				        		: inout	std_logic;
	IO_B66_L14_GC_AB5_N				        		: inout	std_logic;
	IO_B66_L14_GC_AB6_P				        		: inout	std_logic;
	IO_B66_L15_AD11_AD5_P			        		: inout	std_logic;
	IO_B66_L15_AD11_AE5_N			        		: inout	std_logic;
	IO_B66_L16_AD3_AD4_P			        		: inout	std_logic;
	IO_B66_L16_AD3_AE4_N			        		: inout	std_logic;
	IO_B66_L17_AD10_AB4_P			        		: inout	std_logic;
	IO_B66_L17_AD10_AC4_N			        		: inout	std_logic;
	IO_B66_L18_AD2_AA5_N			        		: inout	std_logic;
	IO_B66_L18_AD2_AA6_P			        		: inout	std_logic;
	IO_B66_L19_AD9_AD2_P			        		: inout	std_logic;
	IO_B66_L19_AD9_AE2_N			        		: inout	std_logic;
	IO_B66_L2_AA11_N				        		: inout	std_logic;
	IO_B66_L2_AA12_P				        		: inout	std_logic;
	IO_B66_L20_AD1_AD1_P			        		: inout	std_logic;
	IO_B66_L20_AD1_AE1_N			        		: inout	std_logic;
	IO_B66_L21_AD8_AC2_N			        		: inout	std_logic;
	IO_B66_L21_AD8_AC3_P			        		: inout	std_logic;
	IO_B66_L22_AD0_AA3_P			        		: inout	std_logic;
	IO_B66_L22_AD0_AB3_N			        		: inout	std_logic;
	IO_B66_L23_AB1_P				        		: inout	std_logic;
	IO_B66_L23_AC1_N				        		: inout	std_logic;
	IO_B66_L24_AA1_N				        		: inout	std_logic;
	IO_B66_L24_AA2_P				        		: inout	std_logic;
	IO_B66_L3_AD15_AB11_P			        		: inout	std_logic;
	IO_B66_L3_AD15_AC11_N			        		: inout	std_logic;
	IO_B66_L4_AD7_AD10_N			        		: inout	std_logic;
	IO_B66_L4_AD7_AD11_P			        		: inout	std_logic;
	IO_B66_L5_AD14_AB10_P			        		: inout	std_logic;
	IO_B66_L5_AD14_AB9_N			        		: inout	std_logic;
	IO_B66_L6_AD6_AA10_N			        		: inout	std_logic;
	IO_B66_L6_AD6_Y10_P				        		: inout	std_logic;
	IO_B66_L7_AD13_AC9_P			        		: inout	std_logic;
	IO_B66_L7_AD13_AD9_N			        		: inout	std_logic;
	IO_B66_L8_AD5_AC6_P				        		: inout	std_logic;
	IO_B66_L8_AD5_AD6_N				        		: inout	std_logic;
	IO_B66_L9_AD12_W8_P				        		: inout	std_logic;
	IO_B66_L9_AD12_Y8_N				        		: inout	std_logic;
	IO_B66_Y1						                : inout	std_logic;
    
	PWR_SYNC										: out	std_logic;

	---------------------------------------------------------------------------------------------------
	-- HD bank N - 46 (ZU4/5) or 47 (ZU7) (max. 3.3 V)
	---------------------------------------------------------------------------------------------------
	
	IO_BN_L1_AD11_K11_N						        : inout	std_logic;
	IO_BN_L1_AD11_K12_P						        : inout	std_logic;
	IO_BN_L10_AD2_B14_N						        : inout	std_logic;
	IO_BN_L10_AD2_C14_P						        : inout	std_logic;
	IO_BN_L11_AD1_A13_N						        : inout	std_logic;
	IO_BN_L11_AD1_A14_P						        : inout	std_logic;
	IO_BN_L12_AD0_A12_N						        : inout	std_logic;
	IO_BN_L12_AD0_B12_P						        : inout	std_logic;
	IO_BN_L2_AD10_J12_N						        : inout	std_logic;
	IO_BN_L2_AD10_K13_P						        : inout	std_logic;
	IO_BN_L3_AD9_H12_N						        : inout	std_logic;
	IO_BN_L3_AD9_H13_P						        : inout	std_logic;
	IO_BN_L4_AD8_G14_N						        : inout	std_logic;
	IO_BN_L4_AD8_H14_P						        : inout	std_logic;
	IO_BN_L5_HDGC_AD7_F13_N						    : inout	std_logic;
	IO_BN_L5_HDGC_AD7_G13_P						    : inout	std_logic;
	IO_BN_L6_HDGC_AD6_E12_N						    : inout	std_logic;
	IO_BN_L6_HDGC_AD6_F12_P						    : inout	std_logic;
	IO_BN_L7_HDGC_AD5_E13_N						    : inout	std_logic;
	IO_BN_L7_HDGC_AD5_E14_P						    : inout	std_logic;
	IO_BN_L8_HDGC_AD4_C13_N						    : inout	std_logic;
	IO_BN_L8_HDGC_AD4_D14_P						    : inout	std_logic;
	IO_BN_L9_AD3_C12_N						        : inout	std_logic;
	IO_BN_L9_AD3_D12_P						        : inout	std_logic;
	

	---------------------------------------------------------------------------------------------------
	-- HD bank O - 45 (ZU4/5) or 48 (ZU7) (max. 3.3 V)
	---------------------------------------------------------------------------------------------------
	
	IO_BO_L1_AD15_L14_N							    : inout	std_logic;
	IO_BO_L1_AD15_L15_P							    : inout	std_logic;
	IO_BO_L10_AD10_B16_N							: inout	std_logic;
	IO_BO_L10_AD10_C17_P							: inout	std_logic;
	IO_BO_L11_AD9_A16_N							    : inout	std_logic;
	IO_BO_L11_AD9_A17_P							    : inout	std_logic;
	IO_BO_L12_AD8_A15_N							    : inout	std_logic;
	IO_BO_L12_AD8_B15_P							    : inout	std_logic;
	IO_BO_L2_AD14_K14_N							    : inout	std_logic;
	IO_BO_L2_AD14_K15_P							    : inout	std_logic;
	IO_BO_L3_AD13_J14_N							    : inout	std_logic;
	IO_BO_L3_AD13_J15_P							    : inout	std_logic;
	IO_BO_L4_AD12_H16_N							    : inout	std_logic;
	IO_BO_L4_AD12_J16_P							    : inout	std_logic;
	IO_BO_L5_HDGC_G15_N							    : inout	std_logic;
	IO_BO_L5_HDGC_G16_P							    : inout	std_logic;
	IO_BO_L6_HDGC_F15_N							    : inout	std_logic;
	IO_BO_L6_HDGC_F16_P							    : inout	std_logic;
	IO_BO_L7_HDGC_D17_N							    : inout	std_logic;
	IO_BO_L7_HDGC_E17_P							    : inout	std_logic;
	IO_BO_L8_HDGC_D15_N							    : inout	std_logic;
	IO_BO_L8_HDGC_E15_P							    : inout	std_logic;
	IO_BO_L9_AD11_C16_N							    : inout	std_logic;
	IO_BO_L9_AD11_D16_P							    : inout	std_logic
	
  );
end system_top;

---------------------------------------------------------------------------------------------------
-- architecture declaration
---------------------------------------------------------------------------------------------------

architecture rtl of system_top is

  component MercuryXU8 is
  port (
    pl_resetn0 : out std_logic;
    pl_clk1 : out std_logic;
    gpio_tri_o : out std_logic_vector ( 7 downto 0 );
    SYS_CLK_clk_n : in STD_LOGIC :='0';
    SYS_CLK_clk_p : in STD_LOGIC :='0';
    DDR4_act_n : out STD_LOGIC;
--  DDR4_adr : out STD_LOGIC_VECTOR ( 17 downto 0 );
    DDR4_adr : out STD_LOGIC_VECTOR ( 16 downto 0 );
    DDR4_ba : out STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_bg : out STD_LOGIC_VECTOR ( 0 to 0 );
--	DDR4_bg : out STD_LOGIC_VECTOR ( 1 downto 0 );
    DDR4_ck_c : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_ck_t : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_cke : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_cs_n : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_dm_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR4_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR4_dqs_c : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR4_dqs_t : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR4_odt : out STD_LOGIC_VECTOR ( 0 to 0 );
    DDR4_reset_n : out STD_LOGIC
  );
  end component MercuryXU8;
  
-----------------------------------------------------------------------------------------------
-- signals
-----------------------------------------------------------------------------------------------

  signal Rst_N 			: std_logic := '1';
  
  signal Rst            : std_logic := '0';
  signal Clk			: std_logic;
  signal RstCnt         : unsigned (15 downto 0) := (others => '0');
  signal LedCount       : unsigned (23 downto 0);  
  
  signal Gpio			: std_logic_vector (7 downto 0);
  
begin

-----------------------------------------------------------------------------------------------
-- processor system
-----------------------------------------------------------------------------------------------	

	MercuryXU8_i: component MercuryXU8
       port map (
        gpio_tri_o(7 downto 0) 	=> Gpio(7 downto 0),
        pl_clk1 				=> Clk,
        pl_resetn0 				=> Rst_N,
		DDR4_act_n  			=> DDR4PL_ACT_n,
		DDR4_adr(16 downto 0) 	=> DDR4PL_A(16 downto 0),
--		DDR4_adr(17 downto 0) 	=> DDR4PL_A(17 downto 0),
		DDR4_ba(1 downto 0) 	=> DDR4PL_BA(1 downto 0),
		DDR4_bg(0) 				=> DDR4PL_BG(0),
--		DDR4_bg(1 downto 0) 	=> DDR4PL_BG(1 downto 0),
		DDR4_ck_c(0) 			=> DDR4PL_CK_N(0),
		DDR4_ck_t(0) 			=> DDR4PL_CK_P(0),
		DDR4_cke(0) 			=> DDR4PL_CKE(0),
		DDR4_cs_n(0) 			=> DDR4PL_CS_n(0),
		DDR4_dm_n(3 downto 0) 	=> DDR4PL_DM(3 downto 0),
		DDR4_dq(31 downto 0) 	=> DDR4PL_DQ(31 downto 0),
		DDR4_dqs_c(3 downto 0) 	=> DDR4PL_DQS_N(3 downto 0),
		DDR4_dqs_t(3 downto 0) 	=> DDR4PL_DQS_P(3 downto 0),
		DDR4_odt(0) 			=> DDR4PL_ODT(0),
		DDR4_reset_n 			=> DDR4PL_RST_n,
		SYS_CLK_clk_n 			=> CLK100_N,
		SYS_CLK_clk_p 			=> CLK100_P
      );

    ------------------------------------------------------------------------------------------------
    --  Clock and Reset
    ------------------------------------------------------------------------------------------------ 
       
    process (Clk)
    begin
        if rising_edge (Clk) then
            if (not RstCnt) = 0 then
                Rst         <= '0';
            else
                Rst         <= '1';
                RstCnt      <= RstCnt + 1;
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
    
    Led2_N <= LedCount(23);	
--    Led2_N <= Gpio(2);


    I2c_Sda <= 'Z';
    I2c_Scl <= 'Z';

    PWR_SYNC <= 'Z';
    
end rtl;


---------------------------------------------------------------------------------------------------
-- eof
---------------------------------------------------------------------------------------------------

