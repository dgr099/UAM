----------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores. Grado GII y DGIIM. 1� curso.
-- Fichero: MemProgMIPS.vhd
-- Descripci�n: Memoria de programa para el MIPS
-- Fichero de apoyo para: Pr�ctica: 4. Ejercicio: 3. Se utiliza en la primera prueba de validaci�n del Ejercicio 3
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;

entity MemProgMIPS is										-- Al crear el archivo MemProgVectores.asm, debe cambiar el nombre de la entidad
	port (
		MemProgAddr : in unsigned(31 downto 0);        		-- Direcci�n para la memoria de programa
		MemProgData : out unsigned(31 downto 0) 	-- C�digo de operaci�n
	);
end MemProgMIPS;											-- Al crear el archivo MemProgVectores.asm, debe cambiar el nombre de la entidad

architecture Simple of MemProgMIPS is						-- Al crear el archivo MemProgVectores.asm, debe cambiar el nombre de la entidad

begin

	-- Proceso para la escritura inicial en la memoria de c�digo o de programa. 
	-- La memoria de progrma es de solo lectura, el proceso de escritura es �nico y se realiza antes de ejecutar la simulaci�n.  
	EscrituraMemProg: process(all)
	begin
		-- La memoria devuelve un valor para cada direcci�n.
		-- Estos valores son los c�digos de programa de cada instrucci�n, estando situado cada uno en su direcci�n.
		-- C�digo para la escritura de los datos iniciales quedeben ser cargados previamente en memoria antes de la ejecuci�n del programa.
		
			
		case MemProgAddr is
-- *********************************************************************
			when x"00000000" => MemProgData <= x"8c042000";
			when x"00000004" => MemProgData <= x"20080000";
			when x"00000008" => MemProgData <= x"20090002";
			when x"0000000C" => MemProgData <= x"11090003";
			when x"00000010" => MemProgData <= x"00842020";
			when x"00000014" => MemProgData <= x"21080001";
			when x"00000018" => MemProgData <= x"08000003";
			when x"0000001C" => MemProgData <= x"00a52826";
			when x"00000020" => MemProgData <= x"1085000c";
			when x"00000024" => MemProgData <= x"8ca12004";
			when x"00000028" => MemProgData <= x"8ca2201c";
			when x"0000002c" => MemProgData <= x"20080000";
			when x"00000030" => MemProgData <= x"20090002";
			when x"00000034" => MemProgData <= x"11090003";
			when x"00000038" => MemProgData <= x"00421020";
			when x"0000003c" => MemProgData <= x"214b0002";
			when x"00000040" => MemProgData <= x"0800000d";
			when x"00000044" => MemProgData <= x"00221820";
			when x"00000048" => MemProgData <= x"aca32034";
			when x"0000004c" => MemProgData <= x"20a50004";
			when x"00000050" => MemProgData <= x"08000008";
			when x"00000054" => MemProgData <= x"08000015";		
-- *********************************************************************			
			when others => MemProgData <= x"00000000"; -- Resto de memoria vac�a
		end case;
	end process EscrituraMemProg;

		
	
end Simple;

