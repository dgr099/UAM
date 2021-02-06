----------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Fundamentos de Microprocesadores. Grado ITST. 2º curso.
-- Fichero: MemProgMIPS.vhd
-- Descripción: Memoria de programa para el MIPS
-- Fichero de apoyo para: Práctica: 4. Ejercicio: 3. Se utiliza en la primera prueba de validación del Ejercicio 3
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;

entity MemProgMIPS is										-- Al crear el archivo MemProgVectores.asm, debe cambiar el nombre de la entidad
	port (
		MemProgAddr : in unsigned(31 downto 0);        		-- Dirección para la memoria de programa
		MemProgData : out unsigned(31 downto 0) 	-- Código de operación
	);
end MemProgMIPS;											-- Al crear el archivo MemProgVectores.asm, debe cambiar el nombre de la entidad

architecture Simple of MemProgMIPS is						-- Al crear el archivo MemProgVectores.asm, debe cambiar el nombre de la entidad

begin

	-- Proceso para la escritura inicial en la memoria de código o de programa. 
	-- La memoria de progrma es de solo lectura, el proceso de escritura es único y se realiza antes de ejecutar la simulación.  
	EscrituraMemProg: process(all)
	begin
		-- La memoria devuelve un valor para cada dirección.
		-- Estos valores son los códigos de programa de cada instrucción, estando situado cada uno en su dirección.
		-- Código para la escritura de los datos iniciales quedeben ser cargados previamente en memoria antes de la ejecución del programa.
		
		-- Se cargan a partir de una dirección dada, en MARS por la directiva .text, que en el ejemplo es 0x00000000.
		-- Como cada instruccción ocupa 4 bytes, las direcciones se incrementan de 4 en 4. 
			
		case MemProgAddr is
-- *********************************************************************
			when x"00000000" => MemProgData <= x"20010004";
			when x"00000004" => MemProgData <= x"3402000f";
			when x"00000008" => MemProgData <= x"30430004";
			when x"0000000C" => MemProgData <= x"2064ffec";
			when x"00000010" => MemProgData <= x"28057fff";
			when x"00000014" => MemProgData <= x"2805ffff";
			when x"00000018" => MemProgData <= x"0081302a";
			when x"0000001C" => MemProgData <= x"8c072000";
			when x"00000020" => MemProgData <= x"8c282000";
			when x"00000024" => MemProgData <= x"8c092008";
			when x"00000028" => MemProgData <= x"01075022";
			when x"0000002C" => MemProgData <= x"10240001";
			when x"00000030" => MemProgData <= x"11090001";
			when x"00000034" => MemProgData <= x"00005020";
			when x"00000038" => MemProgData <= x"214b0002";
			when x"0000003C" => MemProgData <= x"00016020";
			when x"00000040" => MemProgData <= x"ac0c200c";
			when x"00000044" => MemProgData <= x"8c0d200c";
			when x"00000048" => MemProgData <= x"00437026";
			when x"0000004C" => MemProgData <= x"01c07024";
			when x"00000050" => MemProgData <= x"00227825";
			when x"00000054" => MemProgData <= x"08000015";		
-- *********************************************************************			
			when others => MemProgData <= x"00000000"; -- Resto de memoria vacía
		end case;
	end process EscrituraMemProg;

		-- Al crear el archivo con la memoria MemProgVectores, debe cambiar los códigos de este archivo y sustituirlos por los 
		-- correspondientes del programa vectores.asm, asociando cada código a la dirección correspondiente.
	
	
end Simple;

