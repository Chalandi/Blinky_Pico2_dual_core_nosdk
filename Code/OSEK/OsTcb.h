// *****************************************************************************
// Filename    : OsTcb.h
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
// Description : Task Control Block definition header file
// 
// *****************************************************************************

#ifndef __TCB_H__
#define __TCB_H__

#include"OsTypes.h"
#include"OsGenPrioTypes.h"

#ifdef __OS_SINGLE_CORE__
/***************************************************/
/*            X Macro System Generation            */
/***************************************************/
#define OS_GEN_ENUM
#include"OsGenCfg.h"
#undef OS_GEN_ENUM

#define OS_GEN_FUNC_PROTO
#include"OsGenCfg.h"
#undef OS_GEN_FUNC_PROTO


#define RES_SCHEDULER_PRIO (uint32)((sizeof(OsSchedPrioType) * 4ul) - 1ul)


/* OS Configuration Block */
extern volatile Ocb_t* OCB_Cfg[];
#else

typedef enum {
    T1,
    T2,
    T3,
    T4,
    OS_INVALID_TASK,
    OS_NUMBER_OF_TASKS = OS_INVALID_TASK
}OsTaskId_t;

#define OS_NUMBER_OF_LOCAL_TASKS_ON_CORE0   2
#define OS_NUMBER_OF_LOCAL_TASKS_ON_CORE1   2
#define OS_INTERNAL_TASK_ID  OS_INVALID_TASK

#define EVT_BLINK_BLUE_LED_FAST (1UL << 0)
#define EVT_BLINK_BLUE_LED_SLOW (1UL << 1)
#define EVT_BLINK_RED_LED_FAST  (1UL << 0)
#define EVT_BLINK_RED_LED_SLOW  (1UL << 1)


typedef enum {
    ALARM_BLINK_BLUE_LED_FAST,
    ALARM_BLINK_BLUE_LED_SLOW,
    ALARM_BLINK_RED_LED_FAST,
    ALARM_BLINK_RED_LED_SLOW,
    OS_INVALID_ALARM,
    OS_NUMBER_OF_ALARMS = OS_INVALID_ALARM
}OsAlarmId_t;

typedef enum {
    RES_SCHEDULER,
    OS_INVALID_RESOURCE,
    OS_NUMBER_OF_RESOURCES = OS_INVALID_RESOURCE
}OsResourceId_t;

void OsTask_T1Func(void);
void OsTask_T2Func(void);
void OsTask_T3Func(void);
void OsTask_T4Func(void);


extern const OsIntIsrLtType IsrLookupTable_core0[];
extern const OsIntIsrLtType IsrLookupTable_core1[];

extern const osObjectCoreAsgn_t osTaskCoreAsgnLookupTable[];
extern const osObjectCoreAsgn_t osAlarmCoreAsgnLookupTable[];
extern const uint8_t osResourceCoreAsgnLookupTable[4/*res*/][2/*core*/];

extern const uint8 osLogicalToPhysicalCoreIdMapping[2];

extern void  OsIsr_UndefinedFunc(void);
extern void  osDispatchHandler(void);
extern void  OsIsr_SysTickTimerFunc(void);

extern volatile Ocb_t* OCB_Cfg[];

#endif /*__OS_SINGLE_CORE__*/

#endif
