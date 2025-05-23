# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\nlaga\Desktop\SFU\Spring2025\Ensc452\final_workspace\project_system\_ide\scripts\systemdebugger_project_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\nlaga\Desktop\SFU\Spring2025\Ensc452\final_workspace\project_system\_ide\scripts\systemdebugger_project_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zed 210248469786" && level==0 && jtag_device_ctx=="jsn-Zed-210248469786-03727093-0"}
fpga -file C:/Users/nlaga/Desktop/SFU/Spring2025/Ensc452/final_workspace/audio_project/_ide/bitstream/design_1_wrapper_alt_address.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/nlaga/Desktop/SFU/Spring2025/Ensc452/final_workspace/final_platform/export/final_platform/hw/design_1_wrapper_alt_address.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/nlaga/Desktop/SFU/Spring2025/Ensc452/final_workspace/audio_project/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/nlaga/Desktop/SFU/Spring2025/Ensc452/final_workspace/audio_project/Debug/audio_project.elf
targets -set -nocase -filter {name =~ "*A9*#1"}
dow C:/Users/nlaga/Desktop/SFU/Spring2025/Ensc452/final_workspace/video_project/Debug/video_project.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
targets -set -nocase -filter {name =~ "*A9*#1"}
con
