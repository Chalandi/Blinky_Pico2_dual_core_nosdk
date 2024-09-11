// *****************************************************************************
// Filename    : OsAsm.h
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.12.2017
// 
// Description : OS low-level functions prototypes
// 
// *****************************************************************************

#ifndef __OS_ASM_H__
#define __OS_ASM_H__

void OsDispatcher(void);
void OsCat2IsrIrqWrapper(void);
void OsStartNewTask(uint32 StackFramePtr, pFunc TaskFuncPtr);
void OsGetCurrentSP(uint32* CurrentSpPtr);
void OsGetPSR(uint32* CurrentPsr);
void OsSetSysCtrlReg(uint32 CtrlRegValue);
void OsGetSysCtrlReg(uint32* CtrlRegValue);
void OsSetSysBasepriReg(uint32 BasepriRegValue);
void OsGetSysBasepriReg(uint32* BasepriRegValue);
uint32 OsHwGetInterruptPrioBits(void);

#endif
