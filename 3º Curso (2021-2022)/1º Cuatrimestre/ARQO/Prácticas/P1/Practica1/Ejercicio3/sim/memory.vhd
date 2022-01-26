--------------------------------------------------------------------------------
-- Universidad Autonoma de Madrid
-- Escuela Politecnica Superior
-- Laboratorio de Arq0 2021-2022
--
-- Memoria sincrona simple.
--------------------------------------------------------------------------------

library std;
use std.textio.all;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_textio.all;

entity memory is
   generic(
      INIT_FILENAME   : string := "instrucciones"; -- nombre fichero con datos iniciales
      MEM_SIZE        : integer := 1024            -- tamanio, en bytes
   );
   Port (
      Clk     : in std_logic ;                     -- Reloj
      Addr    : in std_logic_vector(31 downto 0);  -- Direccion de lectura o escritura
      RdEn    : in std_logic ;                     -- Habilitacion de lectura (si =1)
      WrEn    : in std_logic ;                     -- Habilitacion de escritura (si =1)
      DataIn  : in std_logic_vector(31 downto 0);  -- Dato a escribir
      DataOut : out std_logic_vector(31 downto 0)  -- Dato leido
   );
end memory;

architecture Behavioral of memory is 
        
   type matrix is array(0 to (MEM_SIZE/4)-1) of std_logic_vector(31 downto 0);
   signal memo: matrix;

   signal rAddr : std_logic_vector(31 downto 0);
   
begin

process (clk)
   variable initial_load : boolean := true;
   variable address : std_logic_vector(31 downto 0);
   variable datum : std_logic_vector(31 downto 0);
   file bin_file : text open READ_MODE is INIT_FILENAME;
   variable  current_line : line;
begin

   if initial_load then 
      -- primero iniciamos la memoria con ceros
      for i in 0 to (MEM_SIZE/4)-1 loop
         memo(i) <= (others => '0');
      end loop; 

      -- luego cargamos el archivo en la misma
      while (not endfile (bin_file)) loop
         readline (bin_file, current_line);
         hread(current_line, address);
         hread(current_line, datum);
         assert CONV_INTEGER(address(31 downto 0))<MEM_SIZE 
            report "Direccion fuera de rango en el fichero de la memoria"
            severity failure;
         memo( CONV_INTEGER( address(31 downto 2) ) ) <= datum;
      end loop;

      -- por ultimo cerramos el archivo y actualizamos el flag de memoria cargada
      file_close (bin_file);
      initial_load := false;

      report "Se ha cargado la memoria '" & INIT_FILENAME & "'" severity note;

   elsif rising_edge(clk) then                    
      if (WrEn = '1') then
         assert ( CONV_INTEGER(Addr(31 downto 0)) <MEM_SIZE )
            report "Direccion fuera de rango en el fichero de la memoria"
            severity failure;
         memo( CONV_INTEGER( Addr(31 downto 2) ) ) <= DataIn;
      end if;

   end if;
end process;

rAddr   <= Addr when RdEn = '1'; -- latch: no ejecutan nuevas lecturas si no se activa RdEn
DataOut <= memo( CONV_INTEGER( rAddr(31 downto 2) ) ) when  CONV_INTEGER(rAddr(31 downto 2)) < ((MEM_SIZE/4)-1) else x"FABADA00";

end Behavioral;
