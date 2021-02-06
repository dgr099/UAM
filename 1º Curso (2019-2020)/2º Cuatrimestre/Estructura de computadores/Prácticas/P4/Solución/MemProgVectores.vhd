----------------------------------------------------------------------
-- Fichero: MemProgPlantilla.vhd
-- Descripción: Plantilla para la memoria de programa para el MIPS
-- Fecha última modificación: 2017-03-27

-- Autores: Alberto Sánchez (2012-2017), Ángel de Castro (2010-2015) 
-- Asignatura: EC 1º grado
-- Grupo de Prácticas:
-- Grupo de Teoría:
-- Práctica: 5
-- Ejercicio: 3
----------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;

entity MemProgVectores is
	port (
		MemProgAddr : in  unsigned(31 downto 0);      -- Dirección para la memoria de programa
		MemProgData : out unsigned(31 downto 0)  -- Código de operación
	);
end MemProgVectores;

architecture Simple of MemProgVectores is

begin

	LecturaMemProg: process(MemProgAddr)
	begin
		-- La memoria devuelve un valor para cada dirección.
		-- Estos valores son los códigos de programa de cada instrucción,
		-- estando situado cada uno en su dirección.
		case MemProgAddr is
		-------------------------------------------------------------
		-- Sólo introducir cambios desde aquí	
			when x"00000000" => MemProgData <= x"8c042000";
			when x"00000004" => MemProgData <= x"00842020";
			when x"00000008" => MemProgData <= x"00842020";
			when x"0000000C" => MemProgData <= x"00a52826";
			when x"00000010" => MemProgData <= x"10850008";
			when x"00000014" => MemProgData <= x"8ca12004";
			when x"00000018" => MemProgData <= x"8ca2201c";
			when x"0000001C" => MemProgData <= x"00421020";
			when x"00000020" => MemProgData <= x"00421020";
			when x"00000024" => MemProgData <= x"00221820";
			when x"00000028" => MemProgData <= x"aca32034";
			when x"0000002C" => MemProgData <= x"20a50004";
			when x"00000030" => MemProgData <= x"08000004";
			when x"00000034" => MemProgData <= x"0800000d";
			-- Por cada instrucción en .text, agregar una línea del tipo:
			-- when DIRECCION => MemProgData <= INSTRUCCION;
			-- Por ejemplo, si la posición 0x00000000 debe guardarse la instrucción con código máquina 0x20010004, poner:
			--when X"00000000" => MemProgData <= X"20010004";
		-- Hasta aquí	
		---------------------------------------------------------------------	
			
			when others => MemProgData <= X"00000000"; -- Resto de memoria vacía
		end case;
	end process LecturaMemProg;

end Simple;

