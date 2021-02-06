onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /micromipstb/clk
add wave -noupdate /micromipstb/nRst
add wave -noupdate -divider {Señales Memoria Programa}
add wave -noupdate -radix hexadecimal /micromipstb/memProgAddr
add wave -noupdate -radix hexadecimal /micromipstb/memProgData
add wave -noupdate -divider {Contenido GPR}
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(0)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(1)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(2)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(3)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(4)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(5)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(6)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(7)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(8)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(9)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(10)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(11)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(12)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(13)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(14)
add wave -noupdate -radix hexadecimal /micromipstb/uut/GPR/regs(15)
add wave -noupdate -divider {Señales Memoria de Datos}
add wave -noupdate -radix hexadecimal /micromipstb/mdata/MemDataAddr
add wave -noupdate -radix hexadecimal /micromipstb/mdata/MemDataDataWrite
add wave -noupdate -radix hexadecimal /micromipstb/mdata/MemDataDataRead
add wave -noupdate -divider {Contenido Memoria Datos (en Decimal)}
add wave -noupdate -radix decimal /micromipstb/mdata/memData(2048)
add wave -noupdate -radix decimal /micromipstb/mdata/memData(2049)
add wave -noupdate -radix decimal /micromipstb/mdata/memData(2050)
add wave -noupdate -radix decimal /micromipstb/mdata/memData(2051)
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
WaveRestoreZoom {0 ns} {112 ns}
