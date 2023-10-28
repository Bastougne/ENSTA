vlib work
vlib msim

vlib msim/xil_defaultlib

vmap xil_defaultlib msim/xil_defaultlib

vcom -work xil_defaultlib -64 -93 \
"../../../../axiCrossBar.srcs/sources_1/ip/axi_crossbar_0_1/axi_crossbar_0_sim_netlist.vhdl" \


