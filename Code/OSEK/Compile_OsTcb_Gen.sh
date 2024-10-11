#!/bin/bash

# compile the file
arm-none-eabi-gcc  -mcpu=cortex-m33 -mthumb -march=armv8-m.main+fp+dsp -mfloat-abi=softfp -x c -std=c11 -c OsTcb_Gen.c -o OsTcb_Gen.o

# Press any key to exit
read -s -p " "
