----------------------------------------------------------------------
-- Fichero: RegsMIPS.vhd
-- Descripción: Testbench del banco completo de registros del microprocesador MIPS
-- Fecha última modificación: 2012-01-19

-- Autores: Alberto Sánchez (2012), Ángel de Castro (2011) 
-- Asignatura: E.C. 1º grado
-- Grupo de Prácticas:
-- Grupo de Teoría:
-- Práctica: 2
-- Ejercicio: 1
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity RegsMIPSTb is
end RegsMIPSTb;

architecture Practica of RegsMIPSTb is

component RegsMIPS
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
	end component;

	-- Constantes
	constant TAMANO   : integer := 32;
	constant INSTANTE : time := 10 ns;
	constant PERIOD   : time := 50 ns;       -- Periodo de la senal de reloj

	-- Señales
	signal rd1, rd2, wd3 : signed(31 downto 0):=(others=>'0');
	signal a1, a2, a3 : unsigned(4 downto 0):= (others=>'0');
	signal clk, we3, nRst : std_logic;
	signal endSim : boolean := false;    -- Senal para parar el reloj

begin  -- Practica

	-- Instanciar el banco de registros
	UUT : RegsMIPS
	port map (
		Clk => clk,
		NRst=> nRst,
		A1 => a1,
		Rd1 => rd1,
		A2 => a2,
		Rd2 => rd2,
		A3 => a3,
		Wd3 => wd3,
		We3 => we3
	);


	-- Proceso de reloj. Se para cuando la senal endSim se pone a TRUE
	process
	begin
		while not endSim loop
			clk <= '0';
			wait for PERIOD/2;
			clk <= '1';
			wait for PERIOD/2;
		end loop;
		wait;
	end process;

	-----------------------------------------------------------------------------
	-- Proceso principal de pruebas
	-----------------------------------------------------------------------------
	process
	begin
		---------------------------------------------------------------------------
		-- Prueba de reset
		-- Todos los registros deben tener el valor de 0
		---------------------------------------------------------------------------
		
		-- Primero probamos a resetear mientras solicitamos una escritura
		
		we3 <= '1';
		a1 <= (others => '0');
		a2 <= (others => '0');
		a3 <= (others => '0');
		wd3 <= x"FFFFFFFF" ;
		nRst <= '0';

		wait until rising_edge(clk);
		
		-- y comprobamos que no se ha escrito nada en ningun registro:

		for i in 0 to TAMANO-1 loop
			A1 <= to_unsigned(i,5);
			wait for INSTANTE;
			-- Comprobar la salida de RS1
			assert rd1 = 0
			report "Error en el reset con escritura activa"
			severity FAILURE;
		end loop;  -- i

		-- Poner ahora todas las senales a '0' y despues liberar reset

		we3 <= '0';
		a1 <= (others => '0');
		a2 <= (others => '0');
		a3 <= (others => '0');
		wd3 <= (others => '0');
		nRst <= '0';
		wait for INSTANTE;
		nRst <= '1';

		-- Volver a comprobar que todos los registros tienen el valor de 0

		for i in 0 to TAMANO-1 loop
			A1 <= to_unsigned(i,5);
			wait for INSTANTE;
			-- Comprobar la salida de RS1
			assert rd1 = 0
			report "Error en el reset"
			severity FAILURE;
		end loop;  -- i

		---------------------------------------------------------------------------
		-- Prueba de escritura
		-- En cada registro se escribe el valor de su direccion + 16
		---------------------------------------------------------------------------
		for i in 0 to TAMANO-1 loop
			-- Colocar dato a guardar
			wd3 <= to_signed(i+16,32);
			-- Colocar direccion destino
			a3 <= to_unsigned(i,5);
			-- Indicar que queremos escribir
			we3 <= '1';
			-- Esperar un flanco de subida de reloj, que es donde se hace la
			-- escritura
			wait until rising_edge(clk);
		end loop;  -- i

		---------------------------------------------------------------------------
		-- Pruebas de lectura. Se lee simultaneamente por rd1 y rd2
		-- Por Rd1 se recorre la memoria en sentido ascendente
		-- Por Rd2 en sentido descendente
		---------------------------------------------------------------------------
		we3 <= '0';
		wait for INSTANTE;

		for i in 1 to TAMANO-1 loop
			-- En a1 se colocan las direcciones ascendentes
			a1 <= to_unsigned(i,5);

			-- En a2 se colocan las direcciones descendentes
			a2 <= to_unsigned(32-i,5);

			wait for INSTANTE;
			
			-- Comprobar la salida de rd1
			assert rd1 = to_signed(i+16,32)
				report "Error en la lectura de rd1"
					severity FAILURE;

			-- Comprobar la salida de RS2
			assert rd2 = to_signed((32-i)+16,32)
				report "Error en la lectura de rd2"
					severity FAILURE;
		end loop;  -- i

		-- Comprobar que del registro 0 se lee '0'
		a1 <= (others => '0');
		a2 <= (others => '0');
		wait for INSTANTE;

		-- Comprobar registro rd1
		assert rd1 = 0
			report "Error. Al leer registro 0 por RS1 no se obtiene 0"
				severity FAILURE;

		-- Comprobar registro rd2
		assert rd2 = 0
			report "Error. Al leer registro 0 por RS2 no se obtiene 0"
				severity FAILURE;

		-- Comprueba que cambie rd1 y rd2 cuando cambia
		-- el valor del registro manteniéndose la misma dirección

		for i in 1 to TAMANO-1 loop

			a1 <= to_unsigned(i,5);
			a2 <= to_unsigned(i,5);
			a3 <= to_unsigned(i,5);
			wait for INSTANTE;

			-- Cambia el valor del registro sin cambiar la dirección

			wd3 <= x"0f0f0f0f";
			we3 <= '1';
			wait until rising_edge(clk);
			wait for INSTANTE;

			assert rd1 = x"0f0f0f0f" 
				report "Error. Salida rd1 no cambia cuando varía contenido de registro pero no su dirección."
					severity FAILURE;  

			assert rd2 = x"0f0f0f0f" 
				report "Error. Salida rd2 no cambia cuando varía contenido de registro pero no su dirección."
					severity FAILURE;  

		end loop;
		
		-- Comprueba la escritura en R0
		we3 <= '1';
		wd3 <= x"fabada00";
		a3 <= "00000";
		a1 <= "00000";
		wait until rising_edge(clk);
		wait for INSTANTE;
		assert rd1 = x"00000000"
			report "Error. No se está bloqueando la escritura en R0"
				severity FAILURE;
		
		-- Comprueba el Write Enable
		we3 <= '1';
		wd3 <= x"bebecafe";
		a3 <= "00001";
		a1 <= "00001";
		wait until rising_edge(clk); --Escritura para que haya un dato conocido en R1
		wait for INSTANTE;
		we3 <= '0';
		wd3 <= x"fabada00";
		wait until rising_edge(clk);
		wait for INSTANTE;
		assert rd1 = x"bebecafe"  -- Se comprueba que R1 no cambia si We3='0'
			report "Error. No está funcionando el Write Enable"
				severity FAILURE;
		
		
  

		report "SIMULACION FINALIZADA. Compruebe si previamente se han generado errores" severity note;
		endSim<=TRUE;
		wait;
	end process;


end Practica;
