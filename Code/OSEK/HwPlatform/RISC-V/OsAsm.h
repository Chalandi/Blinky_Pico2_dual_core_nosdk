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

#ifndef pFunc
typedef void (*pFunc)(void);
#endif

void OsDispatchHandler(void);
void OsCat2IsrIrqWrapper(void);
void OsStartNewTask(uint32 StackFramePtr, pFunc TaskFuncPtr);
void OsGetCurrentSP(uint32* CurrentSpPtr);

#endif
