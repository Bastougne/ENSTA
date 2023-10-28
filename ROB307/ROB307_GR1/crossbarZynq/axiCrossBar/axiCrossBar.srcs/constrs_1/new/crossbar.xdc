create_clock -period 7.000 -name myClock -waveform {0.000 3.500} [get_ports -filter { NAME =~  "*Clock*" && DIRECTION == "IN" }]
# ----------------------------------------------------------------------------
# Clock Source - Bank 13
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN Y9 [get_ports {myClock}];  # "PL clock"
set_property IOSTANDARD LVCMOS33 [get_ports {myClock}]

set_property PACKAGE_PIN F22 [get_ports {myReset}]; # "SW0"
set_property IOSTANDARD LVCMOS18 [get_ports {myReset}]

set_property PACKAGE_PIN T18 [get_ports {m00_axi_init_axi_txn}]; # "BTNU"
set_property IOSTANDARD LVCMOS18 [get_ports {m00_axi_init_axi_txn}]

set_property PACKAGE_PIN R16 [get_ports {m00_axi_init_axi_txn_2}]; # "BTND"
set_property IOSTANDARD LVCMOS18 [get_ports {m00_axi_init_axi_txn_2}]

set_property PACKAGE_PIN P16 [get_ports {m00_axi_init_axi_txn_1}]; # "BTNC"
set_property IOSTANDARD LVCMOS18 [get_ports {m00_axi_init_axi_txn_1}]
