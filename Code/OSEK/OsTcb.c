// ******************************************************************************************************
// Filename    : OsTcb.c
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
// Description : Task Control Block definition
// 
// ******************************************************************************************************

#include"OsTcb.h"

#ifdef __OS_SINGLE_CORE__

/***************************************************/
/*            X Macro System Generation            */
/***************************************************/

#define OS_GEN_DATA_STRUCT
#include"OsGenCfg.h"
#undef OS_GEN_DATA_STRUCT

#define OS_GEN_TCB
#include"OsGenCfg.h"
#undef OS_GEN_TCB

#define OS_GEN_OCB_PER_CORE
#include"OsGenCfg.h"
#undef OS_GEN_OCB_PER_CORE

#define OS_GEN_OCB
#include"OsGenCfg.h"
#undef OS_GEN_OCB

#else

const osObjectCoreAsgn_t osTaskCoreAsgnLookupTable[] = { {.local_id=0, .pinned_core=0}, //T1
                                                         {.local_id=1, .pinned_core=0}, //T2
                                                         {.local_id=0, .pinned_core=1}, //T3
                                                         {.local_id=1, .pinned_core=1}  //T4
                                                       };





const osObjectCoreAsgn_t osAlarmCoreAsgnLookupTable[] = { {.local_id=0, .pinned_core=0}, //ALARM_BLINK_BLUE_LED_FAST
                                                          {.local_id=1, .pinned_core=0}, //ALARM_BLINK_BLUE_LED_SLOW
                                                          {.local_id=0, .pinned_core=1}, //ALARM_BLINK_RED_LED_FAST
                                                          {.local_id=1, .pinned_core=1}  //ALARM_BLINK_RED_LED_SLOW
                                                        };


const uint8_t osResourceCoreAsgnLookupTable[4/*res*/][2/*core*/] = { {0, 0}, //RES_
                                                                     {1, 0}, //RES_
                                                                     {0, 1}, //RES_
                                                                     {1, 1}  //RES_
                                                                   };



void OsTask_T1Func(void);
uint32_t /*__attribute__((section(".osTaskStack_T1")))*/ Stack_T_T1[(1024 / 4)];
const uint32_t Stack_T_T1_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T1 = { (pTaskFunc)&OsTask_T1Func, 1, (uint32_t)1, (uint32_t)(&Stack_T_T1[(sizeof(Stack_T_T1) / sizeof(uint32_t)) - 1]), (uint32_t)(&Stack_T_T1[0]), (uint32_t)(&Stack_T_T1[(sizeof(Stack_T_T1) / sizeof(uint32_t)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };
void OsTask_T2Func(void);
uint32_t /*__attribute__((section(".osTaskStack_T2")))*/ Stack_T_T2[(1024 / 4)];
const uint32_t Stack_T_T2_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T2 = { (pTaskFunc)&OsTask_T2Func, 5, (uint32_t)1, (uint32_t)(&Stack_T_T2[(sizeof(Stack_T_T2) / sizeof(uint32_t)) - 1]), (uint32_t)(&Stack_T_T2[0]), (uint32_t)(&Stack_T_T2[(sizeof(Stack_T_T2) / sizeof(uint32_t)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };

void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_BLUE_LED_FAST = { 0, 0, EVT_BLINK_BLUE_LED_FAST, T1, ALARM_SET_EVENT, (uint32_t)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };
void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_BLUE_LED_SLOW = { 0, 0, EVT_BLINK_BLUE_LED_SLOW, T2, ALARM_SET_EVENT, (uint32_t)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };

static OsResourceConfigType OsResource_RES_SCHEDULER_core0 = { (uint32_t)((sizeof(OsSchedPrioType) * 4ul) - 1ul), OS_NUMBER_OF_LOCAL_TASKS_ON_CORE0, 7 };


const OsIntIsrLtType IsrLookupTable_core0[] = {
#ifdef CORE_FAMILY_ARM
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
    { (pIsrFunc)&osDispatchHandler, (uint8)4, (OsInterruptNestingType)NESTED },
    { (pIsrFunc)&OsIsr_SysTickTimerFunc, (uint8)4, (OsInterruptNestingType)NOT_NESTED },
#endif
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
#ifdef CORE_FAMILY_ARM
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
#else
    { (pIsrFunc)&OsIsr_SysTickTimerFunc, (uint8)4, (OsInterruptNestingType)NOT_NESTED },
#endif
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

void OsTask_T3Func(void);
uint32_t /*__attribute__((section(".osTaskStack_T3")))*/ Stack_T_T3[(1024 / 4)];
const uint32_t Stack_T_T3_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T3 = { (pTaskFunc)&OsTask_T3Func, 1, (uint32_t)1, (uint32_t)(&Stack_T_T3[(sizeof(Stack_T_T3) / sizeof(uint32_t)) - 1]), (uint32_t)(&Stack_T_T3[0]), (uint32_t)(&Stack_T_T3[(sizeof(Stack_T_T3) / sizeof(uint32_t)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };
void OsTask_T4Func(void);
uint32_t /*__attribute__((section(".osTaskStack_T4")))*/ Stack_T_T4[(1024 / 4)];
const uint32_t Stack_T_T4_Size = ((1024 / 4) * 4);
static OsTcbType OsTcb_T4 = { (pTaskFunc)&OsTask_T4Func, 5, (uint32_t)1, (uint32_t)(&Stack_T_T4[(sizeof(Stack_T_T4) / sizeof(uint32_t)) - 1]), (uint32_t)(&Stack_T_T4[0]), (uint32_t)(&Stack_T_T4[(sizeof(Stack_T_T4) / sizeof(uint32_t)) - 1]), SUSPENDED, 0, 0, 0, 0, 1, 0, EXTENDED, FULL_PREEMPT };

void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_RED_LED_FAST = { 0, 0, EVT_BLINK_RED_LED_FAST, T3, ALARM_SET_EVENT, (uint32_t)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };
void OsAlarmCallback_0Func(void) __attribute__((weak));
static OsAlarmConfigType OsAlarm_ALARM_BLINK_RED_LED_SLOW = { 0, 0, EVT_BLINK_RED_LED_SLOW, T4, ALARM_SET_EVENT, (uint32_t)0, ALARM_FREE, 0, 0, 0, (pIsrFunc)&OsAlarmCallback_0Func };

static OsResourceConfigType OsResource_RES_SCHEDULER_core1 = { (uint32_t)((sizeof(OsSchedPrioType) * 4ul) - 1ul), OS_NUMBER_OF_LOCAL_TASKS_ON_CORE1, 7 };

const OsIntIsrLtType IsrLookupTable_core1[] = {
#ifdef CORE_FAMILY_ARM
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
    { (pIsrFunc)&osDispatchHandler, (uint8)4, (OsInterruptNestingType)NESTED },
    { (pIsrFunc)&OsIsr_SysTickTimerFunc, (uint8)4, (OsInterruptNestingType)NOT_NESTED },
#endif
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
#ifdef CORE_FAMILY_ARM
    { (pIsrFunc)&OsIsr_UndefinedFunc, (uint8)0, (OsInterruptNestingType)NOT_NESTED },
#else
    { (pIsrFunc)&OsIsr_SysTickTimerFunc, (uint8)4, (OsInterruptNestingType)NOT_NESTED },
#endif
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

OsInterruptConfigType OsInterruptsConfig_core0 = {  (sizeof(IsrLookupTable_core0) / sizeof(OsIntIsrLtType)),
                                                    (OsIntIsrLtType*)&IsrLookupTable_core0[0],
                                                 };

OsInterruptConfigType OsInterruptsConfig_core1 = {  (sizeof(IsrLookupTable_core1) / sizeof(OsIntIsrLtType)),
                                                    (OsIntIsrLtType*)&IsrLookupTable_core1[0],
                                                 };

static const OsTcbType* OsTasksConfig_core0[OS_NUMBER_OF_LOCAL_TASKS_ON_CORE0] = {
    &OsTcb_T1,
    &OsTcb_T2,
};

static const OsAlarmConfigType* OsAlarmsConfig_core0[] = {
    &OsAlarm_ALARM_BLINK_BLUE_LED_FAST,
    &OsAlarm_ALARM_BLINK_BLUE_LED_SLOW,
};
static const OsResourceConfigType* OsResourcesConfig_core0[] = {
    &OsResource_RES_SCHEDULER_core0,
};

static const OsTcbType* OsTasksConfig_core1[] = {
    &OsTcb_T3,
    &OsTcb_T4,
};

static const OsAlarmConfigType* OsAlarmsConfig_core1[] = {
    &OsAlarm_ALARM_BLINK_RED_LED_FAST,
    &OsAlarm_ALARM_BLINK_RED_LED_SLOW,
};
static const OsResourceConfigType* OsResourcesConfig_core1[] = {
    &OsResource_RES_SCHEDULER_core1,
};

static Ocb_t OCB_LcCfg_core0 = {
    (OsTcbType**)&OsTasksConfig_core0[0],

    (OsAlarmConfigType**)&OsAlarmsConfig_core0[0],

    (OsResourceConfigType**)&OsResourcesConfig_core0[0],

    (OsInterruptConfigType*)&OsInterruptsConfig_core0,

    0, 0, OS_NUMBER_OF_LOCAL_TASKS_ON_CORE0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, {0}, {0},
    sizeof(OsTasksConfig_core0)/sizeof(OsTcbType*),
    sizeof(OsAlarmsConfig_core0)/sizeof(OsAlarmConfigType*),
    sizeof(OsResourcesConfig_core0)/sizeof(OsResourceConfigType*)
};


static Ocb_t OCB_LcCfg_core1 = {
    (OsTcbType**)&OsTasksConfig_core1[0],

    (OsAlarmConfigType**)&OsAlarmsConfig_core1[0],

    (OsResourceConfigType**)&OsResourcesConfig_core1[0],

    (OsInterruptConfigType*)&OsInterruptsConfig_core1,

    0, 0, OS_NUMBER_OF_LOCAL_TASKS_ON_CORE1, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, {0}, {0},
    sizeof(OsTasksConfig_core1)/sizeof(OsTcbType*),
    sizeof(OsAlarmsConfig_core1)/sizeof(OsAlarmConfigType*),
    sizeof(OsResourcesConfig_core1)/sizeof(OsResourceConfigType*)
};

volatile Ocb_t* OCB_Cfg[] = {
    (Ocb_t*)&OCB_LcCfg_core0,
    (Ocb_t*)&OCB_LcCfg_core1,
};

const uint8 osLogicalToPhysicalCoreIdMapping[2] = {0, /* Physical core */
                                                   1 /* Physical core */
                                                  };



//volatile Ocb_t* OCB_Cfg = OCB_Cfg[osGetLogicalCoreId(osGetCoreId())];


#endif
