@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.3\\bin
call %xv_path%/xelab  -wto 79fa206957e0461a92a50121621d7449 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot design_tb_func_synth xil_defaultlib.design_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
