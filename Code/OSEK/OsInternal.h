// *****************************************************************************
// Filename    : OsInternal.h
// 
// OS          : OSEK 2.2.3  
// 
// CC          : ECC1/BCC1
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.12.2017
// 
// Description : OS internal services
// 
// *****************************************************************************

#ifndef __OS_INTERNAL_H__
#define __OS_INTERNAL_H__

#include"OsTypes.h"

boolean OsIsInterruptContext(void);
boolean OsIsInterruptEILevelContext(void);
boolean OsIsCat2IntContext(void);

void osErrorHook(OsStatusType Error);
void osPreTaskHook(void);
void osPostTaskHook(void);
void osStartupHook(void);
void osShutdownHook(OsStatusType Error);

void osAlarmsManagement(void);
uint64 OsGetSystemTicksCounter(void);
uint64 OsGetSystemTicksElapsedTime(uint64 prvTicks);

uint32 OsHwSearchForHighPrio(void);
void OsSetTaskPrioReady(const uint32 prio);
void OsClearTaskPrioReady(const uint32 prio);
uint32 OsGetHighPrioReadyTaskIdx(const uint32 prio);

void OsStartNewTask(uint32 StackFramePtr, pFunc TaskFuncPtr);
void OsKernelError(OsStatusType err);

uint32 osGetMaximumStackUsage(uint32 TaskId);

void osInitInterrupts(void);
void osMaskNestedIntPrio(uint32 PrioLevel);
void osMaskNonNestedIntPrio(uint32 PrioLevel);

uint32 OsDispatcher(uint32 StackPtr);
void OsStoreStackPointer(uint32 StackPtrValue);
uint32 OsGetSavedStackPointer(void);
uint32 OsIntCallDispatch(uint32 StackPtr);
void OsRunCat2Isr(void);
void osErrTaskExitWithoutTerminate(void);
void OsSetIntVectTableAddress(uint32* address);

#endif
