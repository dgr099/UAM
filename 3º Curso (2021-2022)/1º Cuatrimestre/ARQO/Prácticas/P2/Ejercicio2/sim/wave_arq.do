onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label CLK /processor_tb/i_processor/Clk
add wave -noupdate -label RST /processor_tb/i_processor/Reset
add wave -noupdate -label PC_REG -radix hexadecimal /processor_tb/i_processor/PC_reg
TreeUpdate [SetDefaultTree]
quietly WaveActivateNextPane
add wave -noupdate -label muxA /processor_tb/i_processor/muxA
add wave -noupdate -label muxB /processor_tb/i_processor/muxB
add wave -noupdate -label ForwardA -radix binary /processor_tb/i_processor/ForwardA
add wave -noupdate -label ForwardB -radix binary /processor_tb/i_processor/ForwardB
add wave -noupdate -label LW_HazDet /processor_tb/i_processor/LW_hazard_detected
TreeUpdate [SetDefaultTree]
quietly WaveActivateNextPane
add wave -noupdate -label OpA /processor_tb/i_processor/Alu_MIPS/OpA
add wave -noupdate -label OpB /processor_tb/i_processor/Alu_MIPS/OpB
add wave -noupdate -label ALU_RES /processor_tb/i_processor/Alu_MIPS/Result
TreeUpdate [SetDefaultTree]
quietly WaveActivateNextPane
add wave -noupdate -label REGS -expand /processor_tb/i_processor/RegsMIPS/regs
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {264 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 111
configure wave -valuecolwidth 94
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
WaveRestoreZoom {312 ns} {375 ns}
