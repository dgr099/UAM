----------------------------------------------------------------------------------
----------------------------------------------------------------------------------
-- Asignatura: Fundamentos de Microprocesadores. Grado ITST. 2º curso.
-- Fichero: ALUMIPSTb.vhd
-- Descripción: Testbench para la ALU del microprocesador MIPS
-- Fichero de apoyo para: Práctica: 2. Ejercicio: 2
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity ALUMIPS is
	port(
   		Op1 : in signed(31 downto 0);
		Op2 : in signed(31 downto 0);
		ALUControl : in std_logic_vector (2 downto 0);
		Res : out signed(31 downto 0);
		Z : out std_logic
		);
end ALUMIPS;

architecture Practica of ALUMIPS is

begin
Process(all)
begin
case ALUControl is 
	when "000" => Res <= Op1 and Op2; 
	when "001" => Res <= Op1 or Op2;
	when "010" => Res <= Op1 + Op2;
	when "011" => Res <= Op1 xor Op2;
	when "101" => Res <= Op1 nor Op2;
	when "110" => Res <= Op1 - Op2;
	when "111" => 
		if Op1 < Op2 then 
			Res <= (0 => '1', others => '0');
		else
			Res <= (others => '0');
		end if;
	when others => res <= (others => '1');
end case;
end process;

	Z <= '1' when Res = 0 else '0';



end Practica;
