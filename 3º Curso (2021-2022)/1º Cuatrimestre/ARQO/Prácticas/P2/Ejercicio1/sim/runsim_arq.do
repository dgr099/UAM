--------------------------------------------------------------------------------
# Script ModelSim para la simulacion del procesador Arq2021-2022
--------------------------------------------------------------------------------

# Crear library, borrando cualquier compilacion previa:
if [file exists work] {
   vdel -lib work -all
}
vlib work

# Compilar RTL:
vcom -work work -2002 -explicit -check_synthesis ../rtl/reg_bank.vhd
vcom -work work -2002 -explicit -check_synthesis ../rtl/alu.vhd
vcom -work work -2002 -explicit -check_synthesis ../rtl/alu_control.vhd
vcom -work work -2002 -explicit -check_synthesis ../rtl/control_unit.vhd
vcom -work work -2002 -explicit -check_synthesis ../rtl/processor.vhd

# Compilar testbench:
vcom -work work -2002 -explicit memory.vhd
vcom -work work -2002 -explicit processor_tb.vhd

# Elaboracion:
vsim -novopt -gINIT_FILENAME_INST="instrucciones" -gINIT_FILENAME_DATA="datos" -gN_CYCLES=100 processor_tb

# Opcion para guardar todas las ondas:
log -r /*

# Mostrar las ondas:
do wave_arq.do

# Opcion del simulador para evitar warnings tipicos en tiempo 0 :
set StdArithNoWarnings 1
run 0 ns
set StdArithNoWarnings 0

# Lanzar la simulacion, hasta que pare sola:
run -all

--------------------------------------------------------------------------------
