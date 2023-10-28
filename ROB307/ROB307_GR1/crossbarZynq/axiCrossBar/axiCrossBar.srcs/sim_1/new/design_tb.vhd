----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2016 10:12:27
-- Design Name: 
-- Module Name: design_tb - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity design_tb is
--  Port ( );
end design_tb;

architecture Behavioral of design_tb is

component design_1_wrapper is
port (
  myReset : in STD_LOGIC;
  m00_axi_init_axi_txn : in STD_LOGIC;
  m00_axi_init_axi_txn_1 : in STD_LOGIC;
  m00_axi_init_axi_txn_2 : in STD_LOGIC;
  myClock : in STD_LOGIC
);
end component design_1_wrapper;

signal s_myReset : STD_LOGIC;
signal s_m00_axi_init_axi_txn : STD_LOGIC;
signal s_m00_axi_init_axi_txn_1 : STD_LOGIC;
signal s_m00_axi_init_axi_txn_2: STD_LOGIC;
signal s_myClock : STD_LOGIC;

begin

    design_1_wrapper_i: component design_1_wrapper
    port map (
          m00_axi_init_axi_txn => s_m00_axi_init_axi_txn,
          m00_axi_init_axi_txn_1 => s_m00_axi_init_axi_txn_1,
          m00_axi_init_axi_txn_2 => s_m00_axi_init_axi_txn_2,
          myClock => s_myClock,
          myReset => s_myReset
    );
    
    tb : process
    begin		-- Wait 100 ns for global reset to finish
        wait for 100 ns;
        s_myReset    <= '0', '1' after 200 ns;      
        wait; -- will wait forever
    end process;

    pGenTx: process
    begin
 
        s_m00_axi_init_axi_txn <= '0';
        s_m00_axi_init_axi_txn_1 <= '0';
        s_m00_axi_init_axi_txn_2 <= '0';
        wait for 2 us;
        wait on s_myClock until s_myClock = '1'; 
        s_m00_axi_init_axi_txn <= '1';
        s_m00_axi_init_axi_txn_1 <= '1';
         s_m00_axi_init_axi_txn_2 <= '1';
        wait on s_myClock until s_myClock = '1';
        s_m00_axi_init_axi_txn <= '0';
        s_m00_axi_init_axi_txn_1 <= '0';
        s_m00_axi_init_axi_txn_2 <= '0';

        
        wait;
    end process pGenTx;
    
    pClk: process
    constant periodClkNs : time    := 20 ns;
    begin
        s_myClock  <= '0';
        wait for periodClkNs/2;
        s_myClock <= '1';
        wait for periodClkNs/2;
    end process pClk;
end Behavioral;
