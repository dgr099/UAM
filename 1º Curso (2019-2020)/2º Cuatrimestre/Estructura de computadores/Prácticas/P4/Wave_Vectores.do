onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /micromipsvectorestb/clk
add wave -noupdate /micromipsvectorestb/nRst
add wave -noupdate -divider {Señales Memoria Programa}
add wave -noupdate -radix hexadecimal /micromipsvectorestb/memProgAddr
add wave -noupdate -radix hexadecimal /micromipsvectorestb/memProgData
add wave -noupdate -divider {Contenido GPR}
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(0)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(1)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(2)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(3)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(4)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(5)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(6)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(7)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(8)
add wave -noupdate -radix hexadecimal /micromipsvectorestb/uut/GPR/regs(9)
add wave -noupdate -divider {Señales Memoria de Datos}
add wave -noupdate -radix hexadecimal /micromipsvectorestb/mdata/MemDataAddr
add wave -noupdate -radix hexadecimal /micromipsvectorestb/mdata/MemDataDataWrite
add wave -noupdate -radix hexadecimal /micromipsvectorestb/memDataDataRead
add wave -noupdate -divider {Contenido Memoria Datos (en Decimal)}
add wave -noupdate -radix decimal /micromipsvectorestb/mdata/memData(2061)
add wave -noupdate -radix decimal /micromipsvectorestb/mdata/memData(2062)
add wave -noupdate -radix decimal /micromipsvectorestb/mdata/memData(2063)
add wave -noupdate -radix decimal /micromipsvectorestb/mdata/memData(2064)
add wave -noupdate -radix decimal /micromipsvectorestb/mdata/memData(2065)
add wave -noupdate -radix decimal /micromipsvectorestb/mdata/memData(2066)
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {115 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 291
configure wave -valuecolwidth 68
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ns} {131 ns}
