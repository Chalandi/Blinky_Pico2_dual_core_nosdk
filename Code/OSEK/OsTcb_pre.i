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
    OsTcbType** pTcb;
    OsAlarmConfigType** pAlarm;
    OsResourceConfigType** pRes;
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
typedef struct
{
    pIsrFunc IsrFunc;
    uint8 Prio;
    OsInterruptNestingType type;
} OsInterruptConfigType;
typedef struct
{
    pIsrFunc IsrFunc;
} FeIsr_t;

typedef enum eTaskId_core0 {
    T1,
    T2,
    OS_INVALID_TASK
};
typedef enum {
    EVT_BLINK_BLUE_LED_FAST = (1UL << 0),
    EVT_BLINK_BLUE_LED_SLOW = (1UL << 1),
    OS_INVALID_EVENT
} eEventId;
typedef enum eAlarmId_core0 {
    ALARM_BLINK_BLUE_LED_FAST,
    ALARM_BLINK_BLUE_LED_SLOW,
    OS_INVALID_ALARM
};
typedef enum eResourceId_core0 {
    RES_SCHEDULER,
    OS_INVALID_RESOURCE
};

typedef enum eTaskId_core1 {
    T5,
    T4,
    OS_INVALID_TASK
};
typedef enum {
    EVT_BLINK_RED_LED_FAST = (1UL << 0),
    EVT_BLINK_RED_LED_SLOW = (1UL << 1),
    OS_INVALID_EVENT
} eEventId;
typedef enum eAlarmId_core1 {
    ALARM_BLINK_RED_LED_FAST,
    ALARM_BLINK_RED_LED_SLOW,
    OS_INVALID_ALARM
};
typedef enum eResourceId_core1 {
    RES_SCHEDULER,
    OS_INVALID_RESOURCE
};

void OsTask_T1Func(void);
void OsTask_T2Func(void);

extern const OsInterruptConfigType IsrLookupTable_core0[];
extern void OsIsr_UndefinedFunc(void);
extern void OsIsr_SysTickTimerFunc(void);

void OsTask_T5Func(void);
void OsTask_T4Func(void);

extern const OsInterruptConfigType IsrLookupTable_core1[];
extern void OsIsr_UndefinedFunc(void);
extern void OsIsr_SysTickTimerFunc(void);



extern volatile Ocb_t* OCB_Cfg[];

void OsTask_T1Func(void);
uint32 __attribute__((section(".osTaskStack_T1"))) Stack_T_T1[(1024 / 4)];
const uint32 Stack_T_T1_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T1 = { (pTaskFunc)&OsTask_T1Func, 1, (uint32)1, (uint32)(&Stack_T_T1[(sizeof(Stack_T_T1) / sizeof(uint32)) - 1]), (uint32)(&Stack_T_T1[0]), (uint32)(&Stack_T_T1[(sizeof(Stack_T_T1) / sizeof(uint32)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };
void OsTask_T2Func(void);
uint32 __attribute__((section(".osTaskStack_T2"))) Stack_T_T2[(1024 / 4)];
const uint32 Stack_T_T2_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T2 = { (pTaskFunc)&OsTask_T2Func, 5, (uint32)1, (uint32)(&Stack_T_T2[(sizeof(Stack_T_T2) / sizeof(uint32)) - 1]), (uint32)(&Stack_T_T2[0]), (uint32)(&Stack_T_T2[(sizeof(Stack_T_T2) / sizeof(uint32)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };

void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_BLUE_LED_FAST = { 0, 0, EVT_BLINK_BLUE_LED_FAST, T1, ALARM_SET_EVENT, (uint32)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };
void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_BLUE_LED_SLOW = { 0, 0, EVT_BLINK_BLUE_LED_SLOW, T2, ALARM_SET_EVENT, (uint32)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };

static OsResourceConfigType OsResource_RES_SCHEDULER = { (uint32)((sizeof(OsSchedPrioType) * 4ul) - 1ul), OS_INVALID_TASK, 7 };

const OsInterruptConfigType IsrLookupTable_core0[] = {
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_SysTickTimerFunc, (uint8)4, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
};

void OsTask_T5Func(void);
uint32 __attribute__((section(".osTaskStack_T5"))) Stack_T_T5[(1024 / 4)];
const uint32 Stack_T_T5_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T5 = { (pTaskFunc)&OsTask_T5Func, 1, (uint32)1, (uint32)(&Stack_T_T5[(sizeof(Stack_T_T5) / sizeof(uint32)) - 1]), (uint32)(&Stack_T_T5[0]), (uint32)(&Stack_T_T5[(sizeof(Stack_T_T5) / sizeof(uint32)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };
void OsTask_T4Func(void);
uint32 __attribute__((section(".osTaskStack_T4"))) Stack_T_T4[(1024 / 4)];
const uint32 Stack_T_T4_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T4 = { (pTaskFunc)&OsTask_T4Func, 5, (uint32)1, (uint32)(&Stack_T_T4[(sizeof(Stack_T_T4) / sizeof(uint32)) - 1]), (uint32)(&Stack_T_T4[0]), (uint32)(&Stack_T_T4[(sizeof(Stack_T_T4) / sizeof(uint32)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };

void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_RED_LED_FAST = { 0, 0, EVT_BLINK_RED_LED_FAST, T1, ALARM_SET_EVENT, (uint32)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };
void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_RED_LED_SLOW = { 0, 0, EVT_BLINK_RED_LED_SLOW, T2, ALARM_SET_EVENT, (uint32)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };

static OsResourceConfigType OsResource_RES_SCHEDULER = { (uint32)((sizeof(OsSchedPrioType) * 4ul) - 1ul), OS_INVALID_TASK, 7 };

const OsInterruptConfigType IsrLookupTable_core1[] = {
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_SysTickTimerFunc, (uint8)4, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
};

const unsigned int osNbrOfInterrupts = sizeof(IsrLookupTable) / sizeof(OsInterruptConfigType);
const unsigned int osNbrOfExceptions = 0;

static const OsTcbType* OsTasksConfig_core0[OS_INVALID_TASK] = {
    &OsTcb_T1,
    &OsTcb_T2,
};

static const OsAlarmConfigType* OsAlarmsConfig_core0[OS_INVALID_ALARM] = {
    &OsAlarm_ALARM_BLINK_BLUE_LED_FAST,
    &OsAlarm_ALARM_BLINK_BLUE_LED_SLOW,
};
static const OsResourceConfigType* OsResourcesConfig_core0[OS_INVALID_RESOURCE] = {
    &OsResource_RES_SCHEDULER,
};

static const OsTcbType* OsTasksConfig_core1[OS_INVALID_TASK] = {
    &OsTcb_T5,
    &OsTcb_T4,
};

static const OsAlarmConfigType* OsAlarmsConfig_core1[OS_INVALID_ALARM] = {
    &OsAlarm_ALARM_BLINK_RED_LED_FAST,
    &OsAlarm_ALARM_BLINK_RED_LED_SLOW,
};
static const OsResourceConfigType* OsResourcesConfig_core1[OS_INVALID_RESOURCE] = {
    &OsResource_RES_SCHEDULER,
};

volatile Ocb_t OCB_Cfg_core0 = {
    (OsTcbType**)&OsTasksConfig_core0[0],
    (OsAlarmConfigType**)&OsAlarmsConfig_core0[0],
    (OsResourceConfigType**)&OsResourcesConfig_core0[0],

    0, 0, OS_INVALID_TASK, 0, 0, 0, 0, 0, 0, 0, 0, {0}, {0}
};
volatile Ocb_t OCB_Cfg_core1 = {
    (OsTcbType**)&OsTasksConfig_core1[0],
    (OsAlarmConfigType**)&OsAlarmsConfig_core1[0],
    (OsResourceConfigType**)&OsResourcesConfig_core1[0],
    0, 0, OS_INVALID_TASK, 0, 0, 0, 0, 0, 0, 0, 0, {0}, {0}
};

volatile Ocb_t* OCB_Cfg[] = {
    (volatile Ocb_t*)&OCB_Cfg_core0,
    (volatile Ocb_t*)&OCB_Cfg_core1,
};
