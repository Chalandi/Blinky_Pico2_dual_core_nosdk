/******************************************************************************************
  Filename    : image_definition_block.c
  
  Core        : Hazard3 RISC-V
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.08.2024
  
  Description : Image definition block for Raspberry Pi Pico 2
  
******************************************************************************************/

#include "stdint.h"

extern void _start_c0(void);
extern uint32_t __CORE0_STACK_TOP;

const uint32_t __attribute__((section(".image_start_block"), aligned(4))) image_definition_Block[] =
{
    0xffffded3,
    0x11010142,
    0x00000344,
    (uint32_t)_start_c0,
    (uint32_t)&__CORE0_STACK_TOP,
    0x000004ff,
    0x00000000,
    0xab123579
};
