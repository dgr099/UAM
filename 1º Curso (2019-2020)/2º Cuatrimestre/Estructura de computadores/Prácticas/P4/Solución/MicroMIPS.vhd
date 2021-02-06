----------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores. Grado Ing. Informática. Curso 1º.
-- Fichero: MicroMIPS.vhd
-- Descripción: Diseño del microprocesador MIPS
-- Fichero de apoyo para: Práctica: 4. Ejercicio: 3
-- Este archivo sirve para la primera prueba de validación del Ejercicio 3
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity MicroMIPS is	port (
	Clk : in std_logic; -- Reloj
	NRst : in std_logic; -- Reset activo a nivel bajo
	MemProgAddr : out unsigned(31 downto 0); -- Dirección para la memoria de programa
	MemProgData : in unsigned(31 downto 0); -- Código de operación
	MemDataAddr : out unsigned(31 downto 0); -- Dirección para la memoria de datos
	MemDataDataRead : in signed(31 downto 0); -- Dato a leer en la memoria de datos
	MemDataDataWrite : out signed(31 downto 0); -- Dato a guardar en la memoria de datos
	MemDataWE : out std_logic
	);
end MicroMIPS;
 
architecture Test OF MicroMIPS is
 
--------------------------------------------------------------
-- Declaración de los componentes y de las señales auxiliares
-------------------------------------------------------------- 
-- Banco Registros
component RegsMIPS is
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

-- Unidad Aritmético Lógica
component ALUMIPS is
	port(
   		Op1 : in signed(31 downto 0);
		Op2 : in signed(31 downto 0);
		ALUControl : in std_logic_vector (2 downto 0);
		Res : out signed(31 downto 0);
		Z : out std_logic
		);
end component;

-- Unidad de Control
component UnidadControl is port(
		OPCode : in  std_logic_vector (5 downto 0); 
		Funct : in std_logic_vector(5 downto 0); 
		Jump : out  std_logic;
		Branch : out  std_logic;
		MemToReg : out  std_logic;
		MemWrite : out  std_logic;
		ALUSrc : out  std_logic;
		ALUControl : out  std_logic_vector (2 downto 0);
		ExtCero : out std_logic;
		RegWrite : out  std_logic;
		RegDest : out  std_logic
        );
end component;

-- Señales auxiliares
signal Instr_Sig, ALUA , ALUB, ALUC, Wd3_aux, ExtSigno, ExtCero_aux: signed(31 downto 0);
signal PC, pcmas4, BTA, JTA: unsigned(31 downto 0);
signal Instr_Slv : std_logic_vector(31 downto 0);
signal A3_aux : unsigned(4 downto 0);
signal jump, branch, memtoreg, memwrite, alusrc, extcero, regwrite, regdst, z, pcsrc : std_logic; 
signal alucontrol : std_logic_vector(2 downto 0);


begin

------------------------------------------------------
-- Instanciar los componentes usados
------------------------------------------------------
Instr_Slv <= std_logic_vector(MemProgData);
Instr_Sig <= signed(MemProgData);


GPR: RegsMIPS port map (
		Clk=>clk, NRst=>nRst, A1=>MemProgData(25 downto 21), Rd1=>ALUA, A2=>MemProgData(20 downto 16), Rd2=>MemDataDataWrite, A3=>A3_aux, Wd3=>Wd3_aux, We3=>regwrite);

ALU: ALUMIPS port map (
   		Op1=>ALUA, Op2=>ALUB, ALUControl=>alucontrol, Res=>ALUC, Z=>z);

UC: UnidadControl port map (
		OPCode=>Instr_Slv(31 downto 26), Funct=>Instr_Slv(5 downto 0), Jump=>jump, Branch=>branch, MemToReg=>memtoreg, MemWrite=>memwrite, ALUSrc=>alusrc, ALUControl=>alucontrol, ExtCero=>extcero, RegWrite=>regwrite, RegDest=>regdst);

		
-- Diseño de la extensión de signo
	ExtSigno <= resize(Instr_Sig(15 downto 0), 32);

-- Diseño de la extension de cero
	ExtCero_aux <= signed(resize(MemProgData(15 downto 0), 32));		
		
-- Diseño de los dos MUX para la entrada ALUB
	ALUB <= MemDataDataWrite when alusrc = '0' else ExtCero_aux when extcero = '1' else ExtSigno; 

-- Diseño del MUX para la entrada A3
	A3_aux <= MemProgData(15 downto 11) when regdst = '1' else MemProgData(20 downto 16); 		

-- Diseño del MUX para la entrada Wd3
	Wd3_aux <= ALUC when memtoreg = '0' else MemDataDataRead;

-- Señales para la ruta del PC, secuencial y saltos condicionales e incondicionales
	pcsrc <= branch and z ;								 
	BTA <= pcmas4 + unsigned(ExtSigno(29 downto 0) & "00");		
	pcmas4 <= PC + 4 ;	
	JTA <= pcmas4(31 downto 28) & MemProgData(25 downto 0) & "00" ; 	
-- Señales de acceso a la memoria de datos
	MemDataAddr <= unsigned(ALUC) ;
	MemDataWE <= memwrite;

 
	
	
	
	

-- Diseño de la ruta del PC
Process(all)
begin
	if nRst = '0' then PC  <= (others => '0');
	elsif rising_edge(clk) then
		if jump = '1' then
			PC <= JTA ;
		elsif pcsrc = '1' then
			PC <= BTA ;
		else PC <= pcmas4 ;
		end if;
	end if;
end process;
	
	MemProgAddr <= PC;

end Test;