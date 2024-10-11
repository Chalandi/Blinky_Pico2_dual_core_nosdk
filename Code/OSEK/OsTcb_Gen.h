typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned long uint32;
typedef signed long sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;
typedef void (*pFunc)(void);
typedef enum {
    FALSE = 0,
    TRUE
} boolean;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short int __int16_t;
typedef short unsigned int __uint16_t;
typedef long int __int32_t;
typedef long unsigned int __uint32_t;
typedef long long int __int64_t;
typedef long long unsigned int __uint64_t;
typedef signed char __int_least8_t;
typedef unsigned char __uint_least8_t;
typedef short int __int_least16_t;
typedef short unsigned int __uint_least16_t;
typedef long int __int_least32_t;
typedef long unsigned int __uint_least32_t;
typedef long long int __int_least64_t;
typedef long long unsigned int __uint_least64_t;
typedef long long int __intmax_t;
typedef long long unsigned int __uintmax_t;
typedef int __intptr_t;
typedef unsigned int __uintptr_t;

typedef __int8_t int8_t;
typedef __uint8_t uint8_t;
typedef __int16_t int16_t;
typedef __uint16_t uint16_t;
typedef __int32_t int32_t;
typedef __uint32_t uint32_t;
typedef __int64_t int64_t;
typedef __uint64_t uint64_t;
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;
typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;
typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;
typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
typedef int int_fast8_t;
typedef unsigned int uint_fast8_t;
typedef int int_fast16_t;
typedef unsigned int uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
typedef long long int int_fast64_t;
typedef long long unsigned int uint_fast64_t;
void osDispatchHandler(void);
void osCat2IsrWrapper(void);
void osStartNewTask(uint32_t StackFramePtr, pFunc TaskFuncPtr);
void osGetCurrentSP(uint32_t* CurrentSpPtr);
void OsGetPSR(uint32_t* CurrentPsr);
void OsSetSysCtrlReg(uint32_t CtrlRegValue);
void OsGetSysCtrlReg(uint32_t* CtrlRegValue);
void OsSetSysBasepriReg(uint32_t BasepriRegValue);
void OsGetSysBasepriReg(uint32_t* BasepriRegValue);
uint32_t OsGetSysPrimaskReg(void);
uint32_t OsHwGetInterruptPrioBits(void);
uint32_t osHwSearchForHighPrio(void);

typedef union {
    struct
    {
        uint32 u1ENABLE : 1;
        uint32 u1TICKINT : 1;
        uint32 u1CLOCKSRC : 1;
        uint32 : 13;
        uint32 u1COUNTFLAG : 1;
        uint32 : 15;
    } bits;
    uint32 u32Register;
} stStkCtrl;
typedef union {
    struct
    {
        uint32 u24RELOAD : 24;
        uint32 : 8;
    } bits;
    uint32 u32Register;
} stStkLoad;
typedef union {
    struct
    {
        uint32 u24CURRENT : 24;
        uint32 : 8;
    } bits;
    uint32 u32Register;
} stStkVal;
typedef union {
    struct
    {
        uint32 u24TENMS : 24;
        uint32 : 6;
        uint32 u1SKEW : 1;
        uint32 u1NOREF : 1;
    } bits;
    uint32 u32Register;
} stStkCalib;
void SysTickTimer_Init(void);
void SysTickTimer_Start(uint32 timeout);
void SysTickTimer_Stop(void);
void SysTickTimer_Reload(uint32 timeout);
boolean osIsInterruptContext(void);
boolean osIsInterruptDisabled(void);
uint32 osGetActiveInterruptVectorId(void);
uint32 osGetInterruptPriorityMask(void);
void osCatchAllCpuExceptions(void);
void osHwTimerInit(void);
void osHwTimerReload(void);
void osHwTimerStart(void);
void osInitInterrupts(void);
void osRestoreSavedIntState(void);
void osSaveAndDisableIntState(void);
void osSetInterruptPriorityMask(uint32 level);
typedef struct
{
    unsigned long OsGroupPrioLevel1;
} OsSchedPrioType;
typedef void (*pTaskFunc)(void);
typedef void (*pIsrFunc)(void);
typedef enum {
    PRE_READY = 0,
    READY,
    WAITING,
    RUNNING,
    SUSPENDED,
    INVALID_STATE
} OsTaskStateType;
typedef enum {
    BASIC = 0,
    EXTENDED
} OsTasksType;
typedef enum {
    NONE_PREEMPT = 0,
    FULL_PREEMPT
} OsTasksSchedType;
typedef enum {
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
} OsCoreIdType;
typedef enum {
    E_OK = 0,
    E_OS_ACCESS = 1,
    E_OS_CALLEVEL = 2,
    E_OS_ID = 3,
    E_OS_LIMIT = 4,
    E_OS_NOFUNC = 5,
    E_OS_RESOURCE = 6,
    E_OS_STATE = 7,
    E_OS_VALUE = 8,
    E_OS_SERVICEID = 9,
    E_OS_ILLEGAL_ADDRESS = 10,
    E_OS_MISSINGEND = 11,
    E_OS_DISABLEDINT = 12,
    E_OS_STACKFAULT = 13,
    E_OS_PROTECTION_MEMORY = 14,
    E_OS_PROTECTION_TIME = 15,
    E_OS_PROTECTION_ARRIVAL = 16,
    E_OS_PROTECTION_LOCKED = 17,
    E_OS_PROTECTION_EXCEPTION = 18,
    E_OS_SYS_ASSERTION = 20,
    E_OS_SYS_ABORT = 21,
    E_OS_SYS_API_ERROR = 23,
    E_OS_SYS_ALARM_MANAGEMENT = 24,
    E_OS_SYS_WARNING = 25,
    E_OS_KERNEL_PANIC = 26,
    E_OS_ENABLEDINT = 27
} OsStatusType;
typedef enum {
    ALARM_SET_EVENT = 0,
    ALARM_ACTIVE_TASK,
    ALARM_CALLBACK
} OsAlarmActionType;
typedef enum {
    ALARM_FREE = 0,
    ALARM_USED
} OsAlarmStatusType;
typedef enum {
    ALARM_ONE_SHOT = 0,
    ALARM_CYCLIC
} OsAlarmCounterType;
typedef enum {
    ALARM_RELATIVE = 0,
    ALARM_ABSOLUTE
} OsAlarmCategoryType;
typedef enum {
    NOT_NESTED = 0,
    NESTED
} OsInterruptNestingType;

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
typedef struct
{
    const pTaskFunc function;
    const uint32 FixedPrio;
    const uint32 Autostart;
    const uint32 pstack_top;
    const uint32 pstack_bot;
    uint32 pCurrentStackPointer;
    OsTaskStateType TaskStatus;
    uint32 Prio;
    uint32 CeilingPrio;
    uint32 SetEvtMask;
    uint32 WaitEvtMask;
    uint32 MaxAllowedMultipleActivation;
    uint32 MultipleActivation;
    OsTasksType TaskType;
    OsTasksSchedType TaskSchedType;
} OsTcbType;
typedef struct
{
    OsTickType InitTicks;
    OsTickType InitCycles;
    const OsEventMaskType Event;
    const OsTaskType TaskId;
    const OsAlarmActionType Action;
    const uint32 AutoStart;
    OsAlarmStatusType Status;
    OsAlarmCounterType Alarmtype;
    OsAlarmCategoryType AlarmCategory;
    OsTickType AlarmCheckPoint;
    pTaskFunc CallBackFunc;
} OsAlarmConfigType;
typedef struct
{
    const uint32 ResCeilingPrio;
    uint32 CurrentOccupiedTask;
    const uint32 AuthorizedTask;
} OsResourceConfigType;
typedef OsAlarmConfigType** OsAlarmBaseRefType;

typedef struct
{
    pIsrFunc IsrFunc;
    uint8 Prio;
    OsInterruptNestingType type;
} OsIntIsrLtType;

typedef struct
{
    pIsrFunc IsrFunc;
} FeIsr_t;

typedef struct
{
  uint32_t              osNbrOfInterrupts;
  const OsIntIsrLtType* osIsrLookupTablePtr;
}OsInterruptConfigType;


typedef struct
{
    OsTcbType** pTcb;
    OsAlarmConfigType** pAlarm;
    OsResourceConfigType** pRes;
    OsInterruptConfigType* pInt;
    uint32 OsIsRunning;
    uint32 HighPrioReadyTaskIdx;
    uint32 CurrentTaskIdx;
    uint64 OsSysTickCounter;
    uint32 OsIntCallDispatcher;
    uint32 OsLockDispatcher;
    uint32 OsCat2InterruptLevel;
    uint32 OsCurrentSystemStackPtr;
    uint32 OsInterruptNestingDepth;
    uint32 OsInterruptNestingSavedLevel;
    uint32 OsInterruptSavedLevel;
    uint32 OsIntNestSavedStackPointer[8];
    uint32 OsIntNestSavedPrioLevel[8];
} Ocb_t;
