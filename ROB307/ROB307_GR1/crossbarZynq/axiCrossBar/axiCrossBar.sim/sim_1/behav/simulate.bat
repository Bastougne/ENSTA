@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.4\\bin
call %xv_path%/xsim design_tb_behav -key {Behavioral:sim_1:Functional:design_tb} -tclbatch design_tb.tcl -view C:/Users/leprovo/workspace/coursENSTA/exerciceCrossbar/axiCrossBar/design_tb_behav.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
