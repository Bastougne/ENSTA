@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.4\\bin
call %xv_path%/xelab  -wto 79fa206957e0461a92a50121621d7449 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L generic_baseblocks_v2_1_0 -L axi_infrastructure_v1_1_0 -L axi_register_slice_v2_1_11 -L fifo_generator_v13_1_3 -L axi_data_fifo_v2_1_10 -L axi_crossbar_v2_1_12 -L blk_mem_gen_v8_3_5 -L axi_bram_ctrl_v4_0_10 -L unisims_ver -L unimacro_ver -L secureip -L xpm --snapshot design_tb_behav xil_defaultlib.design_tb xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
