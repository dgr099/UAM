----------------------------------------------------------------------
-- Fichero: ALUMIPS.vhd
-- Descripción: ALU del microprocesador MIPS
-- Fecha última modificación: 2016-02-29

-- Autores: Sofía Martínez (2020), Alberto Sánchez (2012, 2013, 2016), Ángel de Castro (2010, 2014,
-- 2015)
-- Asignatura: E.C. 1º grado
-- Grupo de Prácticas:
-- Grupo de Teoría:
-- Práctica: 2
-- Ejercicio: 2
----------------------------------------------------------------------


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
	process(all)
	begin
	case ALUControl is
	
			when "000" => Res <= (Op1 and Op2);
			when "001" => Res <= (Op1 or Op2);
			when "010" => Res <= (Op1 + Op2);
			when "011" => Res <= (Op1 xor Op2);
			when "101" => Res <= (Op1 nor Op2);
			when "110" => Res <= (Op1 - Op2);
			when "111" => Res <= (0=>'1', others=>'0')	when (Op1<Op2)	else (others=>'0');
			when others => Res <= (others=>'1');

		end case;

	end process;
	Z <= '1' when Res = "0" else '0';
	
end Practica;
