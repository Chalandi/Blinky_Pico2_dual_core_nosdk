Blinky_Pico2_dual_core_nosdk
==================

[![Build Status](https://github.com/chalandi/Blinky_Pico2_dual_core_nosdk/actions/workflows/Blinky_Pico2_dual_core_nosdk.yml/badge.svg)](https://github.com/chalandi/Blinky_Pico2_dual_core_nosdk/actions)

This repository implements an entirely manually-written,
Blinky Project for the RaspberryPi(R) Pico2 RP2350 dual-core
ARM(R) Cortex(R)-M33 / RISC-V Hazard3.
It exhibits pure _bare_ _metal_ programming on RP22350
dual-core ARM(R) Cortex(R)-M33 / RISC-V Hazard3 and uses no sdk.

Features include:
  - CPU, dual-core boot both ARM and RISC-V supported, clock and PLL initialization,
  - timebase derived from SysTick,
  - blinky LEDs,
  - implementation in C99 with absolute minimal use of assembly.

A clear and easy-to-understand build system based on GNUmake
completes this fun and educational project.

This repository provides keen insight on starting up
a _bare_ _metal_ RaspberryPi(R) Pico2 RP2350 using no sdk.

## Details on the Application

This low-level startup boots through core 0 which then starts up core 1 (via a specific protocol).
Core 1 subsequently carries out the blinky application,
while core 0 enters an endless, idle loop.

Low-level initialization brings the CPU up to full speed
at $150~MHz$. Hardware settings such as wait states
have seemingly been set by the bootloader.

## Building the Application

Build on `*nix*` is easy using an installed ARM compiler `gcc-arm-none-eabi` or/and RISC-V compiler `riscv32-unknown-elf`

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
