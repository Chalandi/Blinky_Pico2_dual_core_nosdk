#!/bin/bash

arm-none-eabi-gcc -E -P OsTcb.c -o OsTcb_pre.i -I$PWD/../Std/ -I$PWD/HwPlatform/ARM/ -I$PWD/../Appli -I$PWD/../OSEK -I$PWD/../Mcal/SysTickTimer

sed "/^[[:space:]]*$/N;/\n[[:space:]]*$/D" OsTcb_pre.i > OsTcb_clean.i

rm OsTcb_pre.i

mv OsTcb_clean.i OsTcb_pre.i

clang-format -style=WebKit -i OsTcb_pre.i
