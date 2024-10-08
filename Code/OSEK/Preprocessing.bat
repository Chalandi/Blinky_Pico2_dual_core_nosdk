@echo off

arm-none-eabi-gcc -E -P OsTcb.c -o OsTcb_pre.i -I%CD%/../Std/ -I%CD%/HwPlatform/ARM/ -I%CD%/../Appli -I%CD%/../OSEK -I%CD%/../Mcal/SysTickTimer

sed "/^[[:space:]]*$/N;/\n[[:space:]]*$/D" OsTcb_pre.i > OsTcb_clean.i

del OsTcb_pre.i

mv OsTcb_clean.i OsTcb_pre.i


pause