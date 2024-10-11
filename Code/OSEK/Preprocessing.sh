#!/bin/bash

arm-none-eabi-gcc -E -P OsTcb.c -o OsTcb_pre.i -DCORE_FAMILY_ARM -I$PWD/../Std/ -I$PWD/HwPlatform/ARM/ -I$PWD/../Appli -I$PWD/../OSEK -I$PWD/../Mcal/SysTickTimer

sed "/^[[:space:]]*$/N;/\n[[:space:]]*$/D" OsTcb_pre.i > OsTcb_clean.i

rm OsTcb_pre.i

mv OsTcb_clean.i OsTcb_pre.i

clang-format -style=WebKit -i OsTcb_pre.i


# compile the file
arm-none-eabi-gcc  -mcpu=cortex-m33 -mthumb -march=armv8-m.main+fp+dsp -mfloat-abi=softfp -x c -std=c11  OsTcb_pre.i -o OsTcb_pre.o

# Press any key to exit
read -s -p " "
