/******************************************************************************************
  Filename    : core_arch.h
  
  Core        : Hazard3 RISC-V
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.08.2024
  
  Description : RISC-V macros for Raspberry Pi Pico 2
  
******************************************************************************************/

#ifndef __CORE_ARCH_H__
#define __CORE_ARCH_H__

#include "riscv.h"

#define CORE_ARCH_SEND_EVENT_INST()    __asm("slt x0, x0, x1")
#define CORE_ARCH_DISABLE_INTERRUPTS() riscv_clear_csr(RVCSR_MSTATUS_OFFSET, 0x08ul)
#define CORE_ARCH_ENABLE_INTERRUPTS()  riscv_set_csr(RVCSR_MSTATUS_OFFSET, 0x08ul)

#endif //__CORE_ARCH_H__
