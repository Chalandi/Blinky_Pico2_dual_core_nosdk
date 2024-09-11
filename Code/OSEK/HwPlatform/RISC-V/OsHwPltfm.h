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


//=========================================================================================
// Definitions
//=========================================================================================
#define osDispatch()              //*(volatile uint32*)(0xE000F000ul) |= 0x80000000; __asm("FENCE.I")

#define ENABLE_INTERRUPTS()       //csr_set_bits_mstatus(MSTATUS_MIE_BIT_MASK)
#define DISABLE_INTERRUPTS()      //csr_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK)

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
uint32 osGetPMR(void);
void osSetPMR(uint32 level);
void osHwTimerInit(void);
void osHwTimerStart(void);
void osHwTimerReload(void);
void osRestoreSavedIntState(void);
void osSaveAndDisableIntState(void);
void OsCatchAllCpuExceptions(void);
void OsIsr_SysTickTimerFunc(void);
uint32 osGetHwIntNestingLevel(void);

#endif
