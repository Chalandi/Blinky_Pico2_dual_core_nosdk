Blinky_Pico2_dual_core_nosdk
==================

[![Build Status](https://github.com/chalandi/Blinky_Pico2_dual_core_nosdk/actions/workflows/Blinky_Pico2_dual_core_nosdk.yml/badge.svg)](https://github.com/chalandi/Blinky_Pico2_dual_core_nosdk/actions)

This repository implements an entirely manually-written,
Blinky Project for the RaspberryPi(R) Pico2 RP2350 dual-core
ARM(R) Cortex(R)-M33 / RISC-V Hazard3 (RPI PICO2 RP2350).
It exhibits pure _bare_ _metal_ programming
on on the RaspberryPi(R) Pico2 RP22350
dual-core ARM(R) Cortex(R)-M33 / RISC-V Hazard3 and uses no sdk.

Features include:
  - CPU, dual-core both ARM and RISC-V supported, clock and PLL initialization,
  - timebase derived from SysTick,
  - blinky LED show on the green user LED on `pin 19`,
  - implementation in C99 with absolute minimal use of assembly.

A clear and easy-to-understand build system based on GNUmake
completes this fun and educational project.

This repository provides keen insight on starting up
a _bare_ _metal_ RaspberryPi(R) Pico2 RP2350 using no sdk.

## Details on the Application

The application boots from the secondary boot-loader (SBL)
at the start location. This low-level startup boots through
core 0. Core 0 then starts up core 1 (via a specific protocol).
Core 1 subsequently carries out the blinky application,
while core 0 enters an endless, idle loop.

Low-level initialization brings the CPU up to full speed
at $133~MHz$. Hardware settings such as wait states
have seemingly been set by the boot-loader.

The blinky LED show utilizes the green user LED on `port25`.

## Building the Application

Build on `*nix*` is easy using an installed `gcc-arm-none-eabi` or/and `riscv32-unknown-elf`

Build an ARM binary using the following command:

```sh
cd Blinky_Pico2_dual_core_nosdk
Rebuild.sh ARM
```

Build an RISC-V binary using the following command:

```sh
cd Blinky_Pico2_dual_core_nosdk
Rebuild.sh RISC-V
```

The build results including ELF-file, HEX-mask, MAP-file
and assembly list file are created in the `Output` directory.

## Continuous Integration

CI runs on pushes and pull-requests with a simple
build and result verification on `ubuntu-latest`
using GutHub Actions.
