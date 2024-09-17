@echo off

start /B ../../Tools/openocd/openocd.exe -f ../../Tools/openocd/rp2350_riscv.cfg

riscv32-unknown-elf-gdb -x gdb_riscv.cfg ../../Output/riscv_baremetal_pico2_dual_core_nosdk.elf

trap "taskkill /F /IM riscv32-unknown-elf-gdb.exe" EXIT
