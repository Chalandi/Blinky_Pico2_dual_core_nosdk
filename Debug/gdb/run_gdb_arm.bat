@echo off

start /B ../../Tools/openocd/openocd.exe -f ../../Tools/openocd/rp2350_arm.cfg

arm-none-eabi-gdb -x gdb_arm.cfg ../../Output/arm_baremetal_pico2_dual_core_nosdk.elf

trap "taskkill /F /IM riscv32-unknown-elf-gdb.exe" EXIT
