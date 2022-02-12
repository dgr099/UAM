--------------------------------------------------------------------------------
-- Procesador MIPS con pipeline curso Arquitectura 2021-2022
--
-- Daniel Cerrato Sánchez (daniel.cerrato@estudiante.uam.es)
-- David Teófilo Garitagoitia Romero (david.garitagoitia@estudiante.uam.es)
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity processor is
   port(
      Clk         : in  std_logic; -- Reloj activo en flanco subida
      Reset       : in  std_logic; -- Reset asincrono activo nivel alto
      -- Instruction memory
      IAddr      : out std_logic_vector(31 downto 0); -- Direccion Instr
      IDataIn    : in  std_logic_vector(31 downto 0); -- Instruccion leida
      -- Data memory
      DAddr      : out std_logic_vector(31 downto 0); -- Direccion
      DRdEn      : out std_logic;                     -- Habilitacion lectura
      DWrEn      : out std_logic;                     -- Habilitacion escritura
      DDataOut   : out std_logic_vector(31 downto 0); -- Dato escrito
      DDataIn    : in  std_logic_vector(31 downto 0)  -- Dato leido
   );
end processor;

architecture rtl of processor is
  --instanciación de la alu
  component alu
    port(
      OpA      : in std_logic_vector (31 downto 0);
      OpB      : in std_logic_vector (31 downto 0);
      Control  : in std_logic_vector (3 downto 0);
      Result   : out std_logic_vector (31 downto 0);
      Signflag : out std_logic;
      Zflag    : out std_logic
    );
  end component;

  --instanciación del banco de registros
  component reg_bank
     port (
        Clk   : in std_logic; -- Reloj activo en flanco de subida
        Reset : in std_logic; -- Reset as�ncrono a nivel alto
        A1    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd1
        Rd1   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd1
        A2    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd2
        Rd2   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd2
        A3    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Wd3
        Wd3   : in std_logic_vector(31 downto 0);  -- Dato de entrada Wd3
        We3   : in std_logic -- Habilitaci�n de la escritura de Wd3
     );
  end component reg_bank;

  --instanciación de la control unit
  component control_unit
     port (
      -- Entrada = codigo de operacion en la instruccion:
      OpCode  : in  std_logic_vector (5 downto 0);
      -- Seniales para el PC
      Branch : out  std_logic; -- 1 = Ejecutandose instruccion branch
      Jump : out std_logic; --señal de salto
      -- Seniales relativas a la memoria
      MemToReg : out  std_logic; -- 1 = Escribir en registro la salida de la mem.
      MemWrite : out  std_logic; -- Escribir la memoria
      MemRead  : out  std_logic; -- Leer la memoria
      -- Seniales para la ALU
      ALUSrc : out  std_logic;                     -- 0 = oper.B es registro, 1 = es valor inm.
      ALUOp  : out  std_logic_vector (2 downto 0); -- Tipo operacion para control de la ALU
      -- Seniales para el GPR
      RegWrite : out  std_logic; -- 1=Escribir registro
      RegDst   : out  std_logic  -- 0=Reg. destino es rt, 1=rd
   );
  end component;

  --instanciación de la alu control
  component alu_control is
   port (
      -- Entradas:
      ALUOp  : in std_logic_vector (2 downto 0); -- Codigo de control desde la unidad de control
      Funct  : in std_logic_vector (5 downto 0); -- Campo "funct" de la instruccion
      -- Salida de control para la ALU:
      ALUControl : out std_logic_vector (3 downto 0) -- Define operacion a ejecutar por la ALU
   );
 end component alu_control;

  signal Alu_Op2      : std_logic_vector(31 downto 0);
  signal ALU_Igual    : std_logic;
  signal AluControl   : std_logic_vector(3 downto 0);
  signal reg_RD_data  : std_logic_vector(31 downto 0);
  signal reg_RD       : std_logic_vector(4 downto 0);

  signal Regs_eq_branch : std_logic;
  signal PC_next        : std_logic_vector(31 downto 0);
  signal PC_reg         : std_logic_vector(31 downto 0);

  signal Inm_ext        : std_logic_vector(31 downto 0); -- La parte baja de la instrucción extendida de signo
  signal reg_RS, reg_RT : std_logic_vector(31 downto 0);

  signal dataIn_Mem     : std_logic_vector(31 downto 0); --From Data Memory
  signal Addr_Branch    : std_logic_vector(31 downto 0);

  signal Ctrl_Jump, Ctrl_Branch, Ctrl_MemWrite, Ctrl_MemRead,  Ctrl_ALUSrc, Ctrl_RegDest, Ctrl_MemToReg, Ctrl_RegWrite : std_logic;
  signal Ctrl_ALUOP     : std_logic_vector(2 downto 0);

  signal Addr_Jump      : std_logic_vector(31 downto 0);
  signal Addr_Jump_dest : std_logic_vector(31 downto 0);
  signal PC_src         : std_logic;
  signal Alu_Res        : std_logic_vector(31 downto 0);

-- IF
  signal PC_plus4_IF       : std_logic_vector(31 downto 0);
  signal Instruction_IF    : std_logic_vector(31 downto 0);

-- ID
  signal PC_plus4_ID       : std_logic_vector(31 downto 0);
  signal Instruction_ID    : std_logic_vector(31 downto 0);

-- EX
  signal PC_plus4_EX       : std_logic_vector(31 downto 0);
  signal Rd1_EX            : std_logic_vector(31 downto 0);
  signal Rd2_EX            : std_logic_vector(31 downto 0);
  signal Inm_ext_EX        : std_logic_vector(31 downto 0);
  signal Instruction_EX    : std_logic_vector(31 downto 0);
  signal Ctrl_Branch_EX    : std_logic;
  signal Ctrl_Jump_EX      : std_logic;
  signal Ctrl_MemToReg_EX  : std_logic;
  signal Ctrl_MemWrite_EX  : std_logic;
  signal Ctrl_MemRead_EX   : std_logic;
  signal Ctrl_ALUSrc_EX    : std_logic;
  signal Ctrl_ALUOP_EX     : std_logic_vector (2 downto 0);
  signal Ctrl_RegWrite_EX  : std_logic;
  signal Ctrl_RegDst_EX    : std_logic;
  signal reg_RD_EX         : std_logic_vector(4 downto 0);
  signal muxA              : std_logic_vector(31 downto 0) := (others => '0');
  signal muxB              : std_logic_vector(31 downto 0) := (others => '0');

-- MEM
  signal Ctrl_Branch_MEM   : std_logic;
  signal Ctrl_Jump_MEM     : std_logic;
  signal Ctrl_MemToReg_MEM : std_logic;
  signal Ctrl_MemWrite_MEM : std_logic;
  signal Ctrl_MemRead_MEM  : std_logic;
  signal Ctrl_RegWrite_MEM : std_logic;
  signal Addr_Jump_MEM     : std_logic_vector(31 downto 0);
  signal Addr_Branch_MEM   : std_logic_vector(31 downto 0);
  signal ALU_Z_MEM         : std_logic;
  signal Alu_Res_Mem	   : std_logic_vector(31 downto 0);
  signal Rd2_MEM	   : std_logic_vector(31 downto 0);
  signal reg_RD_MEM	   : std_logic_vector(4 downto 0);

-- WB
  signal Ctrl_RegWrite_WB : std_logic;
  signal Ctrl_MemToReg_WB : std_logic;
  signal DataIn_Mem_WB    : std_logic_vector(31 downto 0);
  signal Alu_Res_WB       : std_logic_vector(31 downto 0);
  signal reg_RD_WB        : std_logic_vector(4 downto 0);

-- Forwarding unit
  signal ForwardA         : std_logic_vector(1 downto 0);
  signal ForwardB         : std_logic_vector(1 downto 0);

-- Hazard Detection Unit 
  signal enable_PC     : std_logic;
  signal enable_IF_ID  : std_logic;
--  signal enable_ID_EX  : std_logic;
--  signal enable_EX_MEM : std_logic;
--  signal enable_MEM_WB : std_logic;
  signal LW_hazard_detected : std_logic := '0';

begin

  PC_next <= Addr_Jump_dest when PC_src = '1' else PC_plus4_IF; -- mux_ini

  PC_reg_proc: process(Clk, Reset)
  begin
    if Reset = '1' then
      PC_reg <= (others => '0');
    elsif rising_edge(Clk) and enable_PC = '1' then
      PC_reg <= PC_next;
    end if;
  end process;

-- IF
  PC_plus4_IF    <= PC_reg + 4;
  IAddr          <= PC_reg;
  Instruction_IF <= IDataIn;

  IF_ID_reg: process(Clk, Reset)
  begin
    if Reset = '1' then
	PC_plus4_ID    <= (others => '0');
	Instruction_ID <= (others => '0');
    elsif rising_edge(Clk) and enable_IF_ID = '1' then
	PC_plus4_ID    <= PC_plus4_IF;
	Instruction_ID <= Instruction_IF;
    end if;
  end process;

-- ID

  RegsMIPS : reg_bank
  port map (
    Clk   => Clk,
    Reset => Reset,
    A1    => Instruction_ID(25 downto 21),
    Rd1   => reg_RS,
    A2    => Instruction_ID(20 downto 16),
    Rd2   => reg_RT,
    A3    => reg_RD,
    Wd3   => reg_RD_data,
    We3   => Ctrl_RegWrite_WB
  );

  UnidadControl : control_unit
  port map(
    OpCode   => Instruction_ID(31 downto 26),
    -- Señales para el PC
    Branch   => Ctrl_Branch,
    Jump   => Ctrl_Jump,
    -- Señales para la memoria
    MemToReg => Ctrl_MemToReg,
    MemWrite => Ctrl_MemWrite,
    MemRead  => Ctrl_MemRead,
    -- Señales para la ALU
    ALUSrc   => Ctrl_ALUSrc,
    ALUOP    => Ctrl_ALUOP,
    -- Señales para el GPR
    RegWrite => Ctrl_RegWrite,
    RegDst   => Ctrl_RegDest
  );

  Inm_ext     <= x"FFFF" & Instruction_ID(15 downto 0) when Instruction_ID(15)='1' else
                 x"0000" & Instruction_ID(15 downto 0);

-- Hazard Detection Unit
  LW_hazard_detected <= '1' when Ctrl_MemRead_EX = '1' and (Instruction_EX(20 downto 16) = Instruction_ID(26 downto 21) or Instruction_EX(20 downto 16) = Instruction_ID(20 downto 16))
                        else '0';

  enable_PC <= '0' when LW_hazard_detected = '1' else '1';
  enable_IF_ID <= '0' when LW_hazard_detected = '1' else '1';

  ID_EX_reg: process(Clk, Reset)
    begin
      if Reset = '1' then
        Ctrl_Branch_EX   <= '0';
        Ctrl_Jump_EX     <= '0';
        Ctrl_MemToReg_EX <= '0';
        Ctrl_MemWrite_EX <= '0';
        Ctrl_MemRead_EX  <= '0';
        Ctrl_ALUSrc_EX   <= '0';
        Ctrl_ALUOP_EX    <= (others => '0');
        Ctrl_RegWrite_EX <= '0';
        Ctrl_RegDst_EX   <= '0';
        PC_plus4_EX      <= (others => '0');
        Rd1_EX           <= (others => '0');
        Rd2_EX           <= (others => '0');
        Inm_ext_EX       <= (others => '0');
        Instruction_EX   <= (others => '0');	
      elsif rising_edge(Clk) then -- and enable_ID_EX = '1'
        if LW_hazard_detected = '0' then
       	  Ctrl_Branch_EX   <= Ctrl_Branch;
          Ctrl_Jump_EX     <= Ctrl_Jump;
          Ctrl_MemToReg_EX <= Ctrl_MemToReg;
          Ctrl_MemWrite_EX <= Ctrl_MemWrite;
          Ctrl_MemRead_EX  <= Ctrl_MemRead;
          Ctrl_ALUSrc_EX   <= Ctrl_ALUSrc;
          Ctrl_ALUOP_EX    <= Ctrl_ALUOP;
          Ctrl_RegWrite_EX <= Ctrl_RegWrite;
          Ctrl_RegDst_EX   <= Ctrl_RegDest;
        else
          Ctrl_Branch_EX   <= '0';
          Ctrl_Jump_EX     <= '0';
          Ctrl_MemToReg_EX <= '0';
          Ctrl_MemWrite_EX <= '0';
          Ctrl_MemRead_EX  <= '0';
          Ctrl_ALUSrc_EX   <= '0';
          Ctrl_ALUOP_EX    <= (others => '0');
          Ctrl_RegWrite_EX <= '0';
          Ctrl_RegDst_EX   <= '0';
        end if;
        PC_plus4_EX      <= PC_plus4_ID;
        Rd1_EX           <= reg_RS;
        Rd2_EX           <= reg_RT;
        Inm_ext_EX       <= Inm_ext;
        Instruction_EX   <= Instruction_ID;
      end if;
    end process;

-- EX
  Alu_control_i: alu_control
  port map(
    -- Entradas:
    ALUOp  => Ctrl_ALUOP_EX, -- Codigo de control desde la unidad de control
    Funct  => Instruction_EX(5 downto 0), -- Campo "funct" de la instruccion
    -- Salida de control para la ALU:
    ALUControl => AluControl -- Define operacion a ejecutar por la ALU
  );

  Alu_MIPS : alu
  port map (
    OpA      => muxA,
    OpB      => Alu_Op2,
    Control  => AluControl,
    Result   => Alu_Res,
    Signflag => open,
    Zflag    => ALU_Igual
  );

  Addr_Jump <= PC_plus4_EX(31 downto 28) & Instruction_EX(25 downto 0) & "00";
  Addr_Branch <= PC_plus4_EX + ( Inm_ext_EX(29 downto 0) & "00");
  reg_RD_EX <= Instruction_EX(20 downto 16) when Ctrl_RegDst_EX = '0' else Instruction_EX(15 downto 11);
  muxB <= Rd2_EX when ForwardB = "00" else
            reg_RD_data when ForwardB = "01" else
            Alu_Res_MEM when ForwardB = "10";
  Alu_Op2 <= muxB when Ctrl_ALUSrc_EX = '0' else Inm_ext_EX;
  muxA <= Rd1_EX when ForwardA = "00" else
            reg_RD_data when ForwardA = "01" else
            Alu_Res_MEM when ForwardA = "10";

--Forwarding Data Unit 
  ForwardA <= "10" when (Ctrl_RegWrite_MEM = '1') and (reg_RD_MEM /= (reg_RD_MEM'range => '0')) and (reg_RD_MEM = Instruction_EX(25 downto 21)) else
              "01" when (Ctrl_RegWrite_WB = '1') and (reg_RD_WB /= (reg_RD_WB'range => '0')) and not ((Ctrl_RegWrite_MEM = '1') and (reg_RD_MEM /= (reg_RD_MEM'range => '0')) and (reg_RD_MEM = Instruction_EX(25 downto 21))) and (reg_RD_WB = Instruction_EX(25 downto 21)) else
              "00";
  ForwardB <= "10" when Ctrl_RegWrite_MEM = '1' and (reg_RD_MEM /= (reg_RD_MEM'range => '0')) and (reg_RD_MEM = Instruction_EX(20 downto 16)) else
              "01" when Ctrl_RegWrite_WB = '1' and (reg_RD_WB /= (reg_RD_WB'range => '0')) and not ((Ctrl_RegWrite_MEM = '1') and (reg_RD_MEM /= (reg_RD_MEM'range => '0')) and (reg_RD_MEM = Instruction_EX(20 downto 16))) and (reg_RD_WB = Instruction_EX(20 downto 16)) else
              "00";

  EX_MEM_reg: process(Clk, Reset)
  begin
      if Reset = '1' then
  	Ctrl_Branch_MEM   <= '0';
    	Ctrl_Jump_MEM     <= '0';
    	Ctrl_MemToReg_MEM <= '0';
    	Ctrl_MemWrite_MEM <= '0';
  	Ctrl_MemRead_MEM  <= '0';
    	Ctrl_RegWrite_MEM <= '0';
	Addr_Jump_MEM     <= (others => '0');
	Addr_Branch_MEM   <= (others => '0');
	ALU_Z_MEM         <= '0';
	Alu_Res_MEM       <= (others => '0');
	Rd2_MEM           <= (others => '0');
	reg_RD_MEM        <= (others => '0');
      elsif rising_edge(Clk) then -- and enable_EX_MEM = '1'
  	Ctrl_Branch_MEM   <= Ctrl_Branch_EX;
    	Ctrl_Jump_MEM     <= Ctrl_Jump_EX;
    	Ctrl_MemToReg_MEM <= Ctrl_MemToReg_EX;
    	Ctrl_MemWrite_MEM <= Ctrl_MemWrite_EX;
  	Ctrl_MemRead_MEM  <= Ctrl_MemRead_EX;
    	Ctrl_RegWrite_MEM <= Ctrl_RegWrite_EX;
	Addr_Jump_MEM     <= Addr_Jump;
	Addr_Branch_MEM   <= Addr_Branch;
	ALU_Z_MEM         <= ALU_Igual;
	Alu_Res_MEM       <= Alu_Res;
	Rd2_MEM           <= muxB;
	reg_RD_MEM        <= reg_RD_EX;
      end if;
    end process;

-- MEM
  PC_src  <= Ctrl_Jump_MEM or (Ctrl_Branch_MEM and ALU_Z_MEM);
  Addr_Jump_dest <= Addr_Jump_MEM   when Ctrl_Jump_MEM ='1' else
                    Addr_Branch_MEM when Ctrl_Branch_MEM ='1' else
                    (others =>'0');
 
  DAddr      <= Alu_Res_MEM;
  DDataOut   <= Rd2_MEM;
  DWrEn      <= Ctrl_MemWrite_MEM;
  dRdEn      <= Ctrl_MemRead_MEM;
  dataIn_Mem <= DDataIn;

  MEM_WB_reg: process(Clk, Reset)
  begin
      if Reset = '1' then
	Ctrl_MemToReg_WB <= '0';
	Ctrl_RegWrite_WB <= '0';
	dataIn_Mem_WB    <= (others => '0');
	Alu_Res_WB       <= (others => '0');
	reg_RD_WB        <= (others => '0');
      elsif rising_edge(Clk) then -- and enable_MEM_WB = '1'
	Ctrl_MemToReg_WB <= Ctrl_MemToReg_MEM;
	Ctrl_RegWrite_WB <= Ctrl_RegWrite_MEM;
	dataIn_Mem_WB    <= dataIn_Mem;
	Alu_Res_WB       <= Alu_Res_MEM;
	reg_RD_WB        <= reg_RD_MEM;
      end if;
    end process;

-- WB
  reg_RD_data <= dataIn_Mem_WB when Ctrl_MemToReg_WB = '1' else Alu_Res_WB;
  reg_RD <= reg_RD_WB;

end architecture;
