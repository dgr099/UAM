--------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Fundamentos de Microprocesadores. Grado ITST. 2º curso.
-- Fichero: UnidadControl.vhd
-- Descripción: Unidad de Control para el microprocesador MIPS
-- Versión profesores. Indica nota.
-- Fichero de apoyo para: Práctica: 4. Ejercicio: 1
----------------------------------------------------------------------
----------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity UnidadControl is port(
		OPCode : in  std_logic_vector (5 downto 0); -- OPCode de la instrucción
		Funct : in std_logic_vector(5 downto 0); -- Funct de la instrucción
		-- Señales para el PC
		Jump : out  std_logic;
--		RegToPC : out std_logic;
		Branch : out  std_logic;
--		PCToReg : out std_logic;
		-- Señales para la memoria
		MemToReg : out  std_logic;
		MemWrite : out  std_logic;
		
		-- Señales para la ALU
		ALUSrc : out  std_logic;
		ALUControl : out  std_logic_vector (2 downto 0);
		ExtCero : out std_logic;
		
		-- Señales para el GPR
		RegWrite : out  std_logic;
		RegDest : out  std_logic
        );
end UnidadControl;
 
architecture behavior of UnidadControl is
begin
	ALUControl <=	"000" when (OPCode = "000000" and Funct = "100100") or (OpCode = "001100") else			-- and y andi
					"001" when (OPCode = "000000" and Funct = "100101") or (OpCode = "001101") else			-- or y ori
					"010" when (OPCode = "000000" and Funct = "100000") or (OpCode = "001000") or (OpCode = "100011") or (OpCode = "101011") else -- add, addi, lw y sw
					"011" when (OPCode = "000000" and Funct = "100110") else								-- xor 
					"110" when (OPCode = "000000" and Funct = "100010") or (OpCode = "000100") else			-- sub y beq
					"111" when (OPCode = "000000" and Funct = "101010") or (OpCode = "001010") else			-- slt y slti
					"100";
					
	Jump <= '1' when OPCode = "000010" else '0';
	Branch <= '1' when OPCode = "000100" else '0';
	MemToReg <= '1' when OPCode = "100011" else '0';
	MemWrite <= '1' when OPCode = "101011" else '0';
	ALUSrc <= '0' when OPCode = "000000" or OPCode = "000100" else '1';
	ExtCero <= '1' when OPCode = "001100" or OPCode = "001101" else '0';
	RegWrite <= '0' when OPCode = "000010" or OPCode = "000100" or OPCode = "101011" else '1';
	RegDest <= '1' when OPCode = "000000" else '0';



end behavior;

