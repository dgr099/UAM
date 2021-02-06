---------------------------------------------------------------------
----------------------------------------------------------------------
-- Fichero: RegsMIPS.vhd
-- Descripción: Banco completo de registros del microprocesador MIPS
-- Fichero de apoyo para: Práctica: 2. Ejercicio: 1
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity RegsMIPS is
	port (
		Clk : in std_logic; -- Reloj
		NRst : in std_logic; -- Reset asíncrono a nivel bajo
		A1 : in unsigned(4 downto 0); -- Dirección para el puerto Rd1
		Rd1 : out signed(31 downto 0); -- Dato del puerto Rd1
		A2 : in unsigned(4 downto 0); -- Dirección para el puerto Rd2
		Rd2 : out signed(31 downto 0); -- Dato del puerto Rd2
		A3 : in unsigned(4 downto 0); -- Dirección para el puerto Wd3
		Wd3 : in signed(31 downto 0); -- Dato de entrada Wd3
		We3 : in std_logic -- Habilitación del banco de registros
	);
end RegsMIPS;

architecture Practica of RegsMIPS is

	-- Tipo para almacenar los registros
	type regs_t is array (0 to 31) of signed(31 downto 0);

	-- Esta es la señal que contiene los registros. El acceso es de la  siguiente manera: regs(i) acceso al registro i, donde i es  un entero. 
	-- Para convertir del tipo unsigned a entero se  hace de la siguiente manera: to_integer(us), donde us es un elemento de tipo unsigned

	signal regs : regs_t;

begin  -- PRACTICA

	------------------------------------------------------
	-- Escritura del registro Wd
	------------------------------------------------------
	-- Escribe el contenido de Wd3 en el registro indicado
	-- por A3 cuando hay flanco de subida de reloj y
	-- la señal de habilitación de escritura We3 está activa.
	-- Tiene reset asíncrono. Si está habilitado el reset, 
	-- todos los registros se inicializan a valor 0

process (all)
begin
	if NRst = '0' then
		for i in 0 to 31 loop
			regs(i) <= (others => '0');
		end loop;
	elsif (rising_edge(clk) and We3 = '1' and A3 /= 0) then
		regs(to_integer(A3)) <= Wd3;
	end if;
end process;

	------------------------------------------------------
	-- Lectura del registro Rd1
	------------------------------------------------------
	-- Lee en Rd1 el registro indicado por A1. 
	-- La lectura del registro R0 siempre devuelve 0.
	Rd1 <= regs(to_integer(A1)); 

	------------------------------------------------------
	-- Lectura del registro Rd2
	------------------------------------------------------
	-- Lee en Rd2 el registro indicado por A2. 
	-- La lectura del registro R0 siempre devuelve 0.
	Rd2 <= regs(to_integer(A2)); 

end Practica;

