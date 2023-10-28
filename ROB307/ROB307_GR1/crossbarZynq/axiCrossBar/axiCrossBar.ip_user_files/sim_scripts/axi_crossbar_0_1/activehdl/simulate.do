onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+axi_crossbar_0 -L xil_defaultlib -L secureip -O5 xil_defaultlib.axi_crossbar_0

do {wave.do}

view wave
view structure

do {axi_crossbar_0.udo}

run -all

endsim

quit -force
