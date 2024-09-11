// *****************************************************************************
// Filename    : OsTypes.h
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
// Description : Os types definition header file
// 
// *****************************************************************************

#ifndef __OS_TYPES_H__
#define __OS_TYPES_H__

#include"Platform_Types.h"
#include"OsHwPltfm.h"
#include"OsGenPrioTypes.h"

typedef void (*pTaskFunc)(void);
typedef void (*pIsrFunc)(void);

typedef enum 
{
  PRE_READY = 0,
  READY,
  WAITING,
  RUNNING,
  SUSPENDED,
  INVALID_STATE
}OsTaskStateType;


typedef enum 
{
  BASIC = 0,
  EXTENDED
}OsTasksType;

typedef enum 
{
  NONE_PREEMPT = 0,
  FULL_PREEMPT
}OsTasksSchedType;

typedef enum
{
  CORE0 = 0,
  CORE1,
  CORE2,
  CORE3,
  CORE4,
  CORE5,
  CORE6,
  CORE7,
  CORE8,
  CORE9,
}OsCoreIdType;

typedef enum 
{
  E_OK                       = 0,
  E_OS_ACCESS                = 1,
  E_OS_CALLEVEL              = 2,
  E_OS_ID                    = 3,
  E_OS_LIMIT                 = 4,
  E_OS_NOFUNC                = 5,
  E_OS_RESOURCE              = 6,
  E_OS_STATE                 = 7,
  E_OS_VALUE                 = 8,
  E_OS_SERVICEID             = 9,
  E_OS_ILLEGAL_ADDRESS       = 10,
  E_OS_MISSINGEND            = 11,
  E_OS_DISABLEDINT           = 12,
  E_OS_STACKFAULT            = 13,
  E_OS_PROTECTION_MEMORY     = 14,
  E_OS_PROTECTION_TIME       = 15,
  E_OS_PROTECTION_ARRIVAL    = 16,
  E_OS_PROTECTION_LOCKED     = 17,
  E_OS_PROTECTION_EXCEPTION  = 18,
  E_OS_SYS_ASSERTION         = 20,
  E_OS_SYS_ABORT             = 21,
  E_OS_SYS_API_ERROR         = 23,
  E_OS_SYS_ALARM_MANAGEMENT  = 24,
  E_OS_SYS_WARNING           = 25,
  E_OS_KERNEL_PANIC          = 26
}OsStatusType;

typedef enum
{
  ALARM_SET_EVENT = 0,
  ALARM_ACTIVE_TASK,
  ALARM_CALLBACK
}OsAlarmActionType;

typedef enum
{
  ALARM_FREE = 0,
  ALARM_USED
}OsAlarmStatusType;

typedef enum
{
  ALARM_ONE_SHOT = 0,
  ALARM_CYCLIC
}OsAlarmCounterType;

typedef enum
{
  ALARM_RELATIVE = 0,
  ALARM_ABSOLUTE
}OsAlarmCategoryType;

typedef enum
{
  NOT_NESTED = 0,
  NESTED
}OsInterruptNestingType;

/* OS TYPES */
typedef unsigned int OsTaskType;
typedef unsigned int OsEventMaskType;
typedef OsEventMaskType* OsEventMaskRefType;
typedef OsTaskType* OsTaskRefType; 
typedef OsTaskStateType* OsTaskStateRefType;
typedef unsigned int OsResourceType;
typedef unsigned int OsAppModeType;
typedef unsigned int OsAlarmType;
typedef unsigned int OsTickType;
typedef OsTickType* OsTickRefType;

/* TCB & OCB typedef */

typedef struct
{
  const    pTaskFunc         function;
  const    uint32            FixedPrio;
  const    uint32            Autostart;
  const    uint32            pstack_top;
  const    uint32            pstack_bot;
           uint32            pCurrentStackPointer;
           OsTaskStateType   TaskStatus;
           uint32            Prio;
           uint32            CeilingPrio;
           uint32            SetEvtMask;
           uint32            WaitEvtMask;
           uint32            MaxAllowedMultipleActivation;
           uint32            MultipleActivation;
           OsTasksType       TaskType;
           OsTasksSchedType  TaskSchedType;
}OsTcbType;

typedef struct
{
           OsTickType             InitTicks;
           OsTickType             InitCycles;
  const    OsEventMaskType        Event;
  const    OsTaskType             TaskId;
  const    OsAlarmActionType      Action;
  const    uint32                 AutoStart;
           OsAlarmStatusType      Status;
           OsAlarmCounterType     Alarmtype;
           OsAlarmCategoryType    AlarmCategory;
           OsTickType             AlarmCheckPoint;
           pTaskFunc              CallBackFunc;
}OsAlarmConfigType;

typedef struct
{
  const uint32 ResCeilingPrio;
  uint32 CurrentOccupiedTask;
  const uint32* const AuthorizedTask;
}OsResourceConfigType;

typedef OsAlarmConfigType** OsAlarmBaseRefType;

typedef struct
{
  OsTcbType**             pTcb;
  OsAlarmConfigType**     pAlarm;
  OsResourceConfigType**  pRes;
  uint32                  OsIsRunning;
  uint32                  HighPrioReadyTaskIdx;
  uint32                  CurrentTaskIdx;
  uint64                  OsSysTickCounter;
  uint32                  OsIntCallDispatcher;
  uint32                  OsLockDispatcher;
  uint32                  OsCat2InterruptLevel;
  uint32                  OsCurrentSystemStackPtr;
  uint32                  OsInterruptNestingDepth;
  uint32                  OsInterruptNestingSavedLevel;
  uint32                  OsInterruptSavedLevel;
  uint32                  OsIntNestSavedStackPointer[8];
}Ocb_t;

typedef struct
{
  pIsrFunc               IsrFunc;
  uint8                  Prio;
  OsInterruptNestingType type;
}OsInterruptConfigType;


typedef struct
{
  pIsrFunc IsrFunc;
}FeIsr_t;

#define TASK(x)                void OsTask_##x##Func(void)
#define ISR(x)                 void OsIsr_##x##Func(void)
#define CALL_ISR(x)            OsIsr_##x##Func()
#define ALARMCALLBACK(x)       void OsAlarmCallback_##x##Func(void)
#define pTASK(x)               (pTaskFunc)&OsTask_##x##Func
#define pISR(x)                (pIsrFunc)&OsIsr_##x##Func
#define pALARMCALLBACK(x)      (pIsrFunc)&OsAlarmCallback_##x##Func
#define osInternalError(x)     OsKernelError(x); return(x)

#define PRAGMA(x) _Pragma(#x)

#if defined(__ghs__)

#define CREATE_STACK(x,y)  PRAGMA(ghs startdata)                                                     \
                           PRAGMA(ghs section bss=".osTaskStacks")                                   \
                           uint32 Stack_T_##x[(y/sizeof(uint32))];                                   \
                           PRAGMA(ghs section bss=default)                                           \
                           PRAGMA(ghs enddata)                                                       \
                           const uint32 Stack_T_##x##_Size = ((y / sizeof(uint32)) * sizeof(uint32))

#elif defined(__GNUC__)

#define SECTION_NAME(x)    #x

#define CREATE_STACK(x,y)  uint32 __attribute__((section(SECTION_NAME(.osTaskStack_##x)))) Stack_T_##x[(y/4)];       \
                           const uint32 Stack_T_##x##_Size = ((y / 4) * 4)

#else
  #error "used compiler is not supported !"
#endif

#define pTSTACK(x)    (uint32)(&Stack_T_##x[(sizeof(Stack_T_##x)/sizeof(uint32))-1])
#define pBSTACK(x)    (uint32)(&Stack_T_##x[0])
#define STACK_SIZE(x) (uint32)(Stack_T_##x##_Size)

  
#define OS_DeclareTask(TaskId)
#define OS_DeclareResource(ResId)
#define OS_DeclareEvent(Event)
#define OS_DeclareAlarm(AlarmId)

#define OS_AUTOSTART    (uint32)1
#define OS_NO_AUTOSTART (uint32)0

#define ALARM_AUTOSTART    (uint32)1
#define ALARM_NO_AUTOSTART (uint32)0

#define APP_MODE_DEFAULT (OsAppModeType)0
#define APP_MODE APP_MODE_DEFAULT

#define OS_FALSE 0U
#define OS_TRUE  1U

#define OS_STACK_MAGIC_MARKER 0xB16B00B5UL

#endif

