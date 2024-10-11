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

OsStatusType osSchedule(void);

boolean osIsCat2IntContext(void);

uint32 osDispatcher(uint32 StackPtr);
uint32 osGetHighPrioReadyTaskIdx(const uint32 prio);
uint32 osGetIntNestingLevel(void);
uint32 osGetMaximumStackUsage(uint32 TaskId);
uint32 osGetSavedStackPointer(void);
uint32 osIntCallDispatch(uint32 StackPtr);
uint64 osGetSystemTicksCounter(void);
uint64 osGetSystemTicksElapsedTime(uint64 prvTicks);
uint8_t osRemapPhyToLogicalCoreId(uint8_t PhysicalCoreId);

void OsIsr_UndefinedFunc(void);
void osAlarmsManagement(void);
void osClearTaskPrioReady(const uint32 prio);
void osDecNestingDepthLevel(void);
void osDisableIntNesting(void);
void osEnableIntNesting(void);
void osErrTaskExitWithoutTerminate(void);
void osIncNestingDepthLevel(void);
void osKernelError(OsStatusType err);
void osRunCat2Isr(void);
void osSetTaskPrioReady(const uint32 prio);
void osStoreStackPointer(uint32 StackPtrValue);


ISR(SysTickTimer);
ISR(UndefinedFunc);

#endif
