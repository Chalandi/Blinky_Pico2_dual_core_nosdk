// *****************************************************************************
// Filename    : OsHwPltfm.h
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 18.01.2023
// 
// Description : Hardware platform header file for WCH RISC-V CH32V307
// 
// *****************************************************************************

#ifndef __HARDWARE_PLATFORM_H__
#define __HARDWARE_PLATFORM_H__

//=========================================================================================
// Includes
//=========================================================================================
#include"Platform_Types.h"
#include"OsAsm.h"

#define OS_GEN_NOT
#include"OsGenCfg.h"
#undef  OS_GEN_NOT

#include "core_arch.h"
#include "RP2350.h"

//=========================================================================================
// Definitions
//=========================================================================================
#define osDispatch()              HW_PER_SIO->RISCV_SOFTIRQ.reg = (1ul << (HW_PER_SIO->CPUID.reg)); __asm("fence"); riscv_set_csr(RVCSR_MIE_OFFSET, RVCSR_MIE_MSIE_BITS);

#define ENABLE_INTERRUPTS()       riscv_set_csr(RVCSR_MSTATUS_OFFSET, RVCSR_MSTATUS_MIE_BITS)
#define DISABLE_INTERRUPTS()      riscv_clear_csr(RVCSR_MSTATUS_OFFSET, RVCSR_MSTATUS_MIE_BITS)

#define osSetINTSYSCR(value)        //__asm volatile ("csrw    0x804, %0" : : "r" (value) :)
#define osMaskClearINTSYSCR(value)  //__asm volatile ("csrrc   zero, 0x804, %0" : : "r" (value) :)
#define osMaskSetINTSYSCR(value)    //__asm volatile ("csrrs   zero, 0x804, %0" : : "r" (value) :)

#define osDisableHwIntNesting()  //osMaskSetINTSYSCR(0x20)

//=========================================================================================
// SYSTICK
//=========================================================================================


//=========================================================================================
// Externs
//=========================================================================================
extern uint32 osIntVectTable;

//=========================================================================================
// Functions Prototype
//=========================================================================================
uint32 osGetInterruptPriorityMask(void);
void osSetInterruptPriorityMask(uint32 level);
void osHwTimerInit(void);
void osHwTimerStart(void);
void osHwTimerReload(void);
void osRestoreSavedIntState(void);
void osSaveAndDisableIntState(void);
void OsCatchAllCpuExceptions(void);
void OsIsr_SysTickTimerFunc(void);
uint32 osGetHwIntNestingLevel(void);

#endif
