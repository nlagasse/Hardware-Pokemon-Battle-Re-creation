# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\nlaga\Desktop\SFU\Spring2025\Ensc452\final_workspace\final_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\nlaga\Desktop\SFU\Spring2025\Ensc452\final_workspace\final_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {final_platform}\
-hw {C:\Users\nlaga\Downloads\design_1_wrapper_alt_address.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -fsbl-target {psu_cortexa53_0} -out {C:/Users/nlaga/Desktop/SFU/Spring2025/Ensc452/final_workspace}

platform write
platform generate -domains 
platform active {final_platform}
platform active {final_platform}
domain create -name {standalone_ps7_cortexa9_1} -display-name {standalone_ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform write
domain active {zynq_fsbl}
domain active {standalone_domain}
domain active {standalone_ps7_cortexa9_1}
platform generate -quick
domain active {standalone_ps7_cortexa9_1}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -DUSE_AMP=1"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp reload
bsp setlib -name xilffs -ver 4.4
bsp write
bsp reload
catch {bsp regenerate}
platform generate
