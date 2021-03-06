----------------------------------------------------------------------
-- Fichero: MicroSuma.vhd
-- Descripci�n: Micro MIPS muy simplificado, s�lo suma con dato inmediato
-- Fecha �ltima modificaci�n: 

-- Autores: Alberto S�nchez (2012), �ngel de Castro (2011) 
-- Asignatura: E.C. 1� grado
-- Grupo de Pr�cticas:
-- Grupo de Teor�a:
-- Pr�ctica: 2
-- Ejercicio: 3
----------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
							
entity MicroSuma is
	port (
		Clk : in std_logic; -- Reloj
		NRst : in std_logic; -- Reset activo a nivel bajo
		MemProgAddr : out unsigned(31 downto 0); -- Direcci�n para la memoria de programa
		MemProgData : in unsigned(31 downto 0) -- C�digo de operaci�n
	);
	end MicroSuma;

architecture Practica of MicroSuma is

	-- Declaraci�n de RegMIPS
	COMPONENT RegsMIPS is
		port (
			Clk : in std_logic; -- Reloj
			NRst : in std_logic; -- Reset as�ncrono a nivel bajo
			A1 : in unsigned(4 downto 0); -- Direcci�n para el puerto Rd1
			Rd1 : out signed(31 downto 0); -- Dato del puerto Rd1
			A2 : in unsigned(4 downto 0); -- Direcci�n para el puerto Rd2
			Rd2 : out signed(31 downto 0); -- Dato del puerto Rd2
			A3 : in unsigned(4 downto 0); -- Direcci�n para el puerto Wd3
			Wd3 : in signed(31 downto 0); -- Dato de entrada Wd3
			We3 : in std_logic -- Habilitaci�n del banco de registros
		); 
	end COMPONENT;
	-- Declaraci�n de ALUMIPS
	COMPONENT ALUMIPS is
		port(
			Op1 : in signed(31 downto 0);
			Op2 : in signed(31 downto 0);
			ALUControl : in std_logic_vector (2 downto 0);
			Res : out signed(31 downto 0);
			Z : out std_logic
			);
	end COMPONENT;
	
	-- Declaraci�n de se�ales auxiliares
	SIGNAL	dato_inm: signed(15 downto 0);
	--SIGNAL Rs: unsigned (25 downto 21);
	--SIGNAL Rt:	unsigned (20 downto 16);
	SIGNAL Op2:	signed	(31 downto 0);
	SIGNAL Op1:	signed (31 downto 0);
	SIGNAL Wd3:	signed (31 downto 0);
	
begin

	-- Instancia de RegMIPS
	RegMIPS PORT MAP (A1=>MemProgData(25 downto 21), A3=>MemProgData(20 downto 16), Wd3=>Wd3, Rd1=>Op1);
	
	-- Instancia de ALUMIPS
	ALUMIPS	PORT MAP (ALUControl=>"010", Op1=>Op1, Op2=>Op2, Res=>Wd3);
	-- Extensi�n de signo
	 Op2(31 downto 16)<=(others=>'0') when MemProgData(15)='0' else "-1";
	 Op2(15 downto 0)<=signed(MemProgData(15 downto 0));
	-- Ruta del PC
	process(all)
	begin process
		if NRst = '0' then
			MemProgAddr <= (others=>'0');
		elsif rising_edge(Clk) then
			MemProgAddr <= MemProgAddr + 4;
	end if;
	end process; 	

end Practica;


