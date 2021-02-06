----------------------------------------------------------------------
-- Fichero: MemProgSuma.vhd
-- Descripción: Memoria de programa para el MIPS. Contiene sumas entre un registro y un dato inmediato
-- Fecha última modificación: 2017-02-02

-- Autores: Alberto Sánchez (2012, 2017), Ángel de Castro (2010) 
-- Asignatura: E.C. 1º grado
-- Grupo de Prácticas:
-- Grupo de Teoría:
-- Práctica: 2
-- Ejercicio: 2
----------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


entity MemProgSuma is
	port (
		MemProgAddr : in unsigned(31 downto 0); -- Dirección para la memoria de programa
		MemProgData : out unsigned(31 downto 0) -- Código de operación
	);
end MemProgSuma;

architecture Simple of MemProgSuma is

begin

	LecturaMemProg: process(MemProgAddr)
	begin
		-- La memoria devuelve un valor para cada dirección.
		-- Estos valores son los códigos de programa de cada instrucción,
		-- estando situado cada uno en su dirección.
		case MemProgAddr is
			when X"00000000" => MemProgData <= X"2001000a";		-- R1 = R0 + 10
			when X"00000004" => MemProgData <= X"20220005";		-- R2 = R1 + 5
			when X"00000008" => MemProgData <= X"20430019";		-- R3 = R2 + 25	
			when X"0000000C" => MemProgData <= X"20000005";		-- R0 = R0 + 5
			when X"00000010" => MemProgData <= X"2064FFFB";		-- R4 = R3 -  5
			when others => MemProgData <= X"00000000"; 				-- Resto de memoria vacía
		end case;
	end process LecturaMemProg;

end Simple;
