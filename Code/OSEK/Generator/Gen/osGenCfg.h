
// **********************************************************************************************************************
//                                                  OSEK OS Configuration
// **********************************************************************************************************************

// **********************************************************************************************************************
// Filename        : osGenCfg.h
//
// Author          : Amine Chalandi
//
// Owner           : Amine Chalandi
//
// Generator       : OilGenTool
//
// Generation Time : 01.10.2024 05:18:06
//
// Description     : Auto-generated OS Configuration file please do not modify it manually !!!
//
// **********************************************************************************************************************

#include "OsGenMac.h"


//=============================================================================
// OS Configuration Summary
//=============================================================================
/*
  OS:
  ╒════════╤═════════════════════════════════╕
  │ Name   │ Properties                      │
  ╞════════╪═════════════════════════════════╡
  │ MyOSEK │ OsMulticore        =  TRUE      │
  │        │ OsStartupHook      =  TRUE      │
  │        │ OsErrorHook        =  TRUE      │
  │        │ OsShutdownHook     =  TRUE      │
  │        │ OsPreTaskHook      =  TRUE      │
  │        │ OsPostTaskHook     =  TRUE      │
  │        │ OsStackCheck       =  TRUE      │
  │        │ OsCpuFrequency     =  16.000000 │
  │        │ OsMaxVectorEntries =  113       │
  │        │ OsTickTime         =  1000      │
  ╘════════╧═════════════════════════════════╛

  Tasks:
  ╒═══════════════╤════════╤════════════╤════════════╤══════════════╤═════════════╤══════════════╤════════════════════╕
  │ Task          │ Type   │ Schedule   │   Priority │   Activation │ Autostart   │ Stack size   │   Wait events mask │
  ╞═══════════════╪════════╪════════════╪════════════╪══════════════╪═════════════╪══════════════╪════════════════════╡
  │ OSTASK_TASK01 │ AUTO   │ FULL       │          0 │            1 │ TRUE        │ 0x800        │                  7 │
  ├───────────────┼────────┼────────────┼────────────┼──────────────┼─────────────┼──────────────┼────────────────────┤
  │ OSTASK_TASK02 │ AUTO   │ FULL       │          1 │            1 │ TRUE        │ 800          │                  7 │
  ├───────────────┼────────┼────────────┼────────────┼──────────────┼─────────────┼──────────────┼────────────────────┤
  │ OSTASK_TASK03 │ AUTO   │ FULL       │          3 │            1 │ TRUE        │ 800          │                  5 │
  ╘═══════════════╧════════╧════════════╧════════════╧══════════════╧═════════════╧══════════════╧════════════════════╛
  Total number of tasks: 3

  Task's events: 
  ╒═══════════════╤═══════════════╕
  │ Task          │ Events        │
  ╞═══════════════╪═══════════════╡
  │ OSTASK_TASK01 │ OSEVT_EVENT01 │
  │               │ OSEVT_EVENT02 │
  │               │ OSEVT_EVENT03 │
  ├───────────────┼───────────────┤
  │ OSTASK_TASK02 │ OSEVT_EVENT03 │
  │               │ OSEVT_EVENT02 │
  │               │ OSEVT_EVENT01 │
  ├───────────────┼───────────────┤
  │ OSTASK_TASK03 │ OSEVT_EVENT03 │
  │               │ OSEVT_EVENT01 │
  ╘═══════════════╧═══════════════╛

  Task's resources: 
  ╒═══════════════╤══════════════════╕
  │ Task          │ Resources        │
  ╞═══════════════╪══════════════════╡
  │ OSTASK_TASK01 │ OSRES_RESOURCE01 │
  │               │ OSRES_RESOURCE02 │
  ├───────────────┼──────────────────┤
  │ OSTASK_TASK02 │ OSRES_RESOURCE02 │
  │               │ OSRES_RESOURCE01 │
  ├───────────────┼──────────────────┤
  │ OSTASK_TASK03 │ OSRES_RESOURCE01 │
  ╘═══════════════╧══════════════════╛

  Events:
  ╒═══════════════╤════════╕
  │ EVENT         │ MASK   │
  ╞═══════════════╪════════╡
  │ OSEVT_EVENT01 │ 0x1    │
  ├───────────────┼────────┤
  │ OSEVT_EVENT02 │ 0x2    │
  ├───────────────┼────────┤
  │ OSEVT_EVENT03 │ 0x4    │
  ╘═══════════════╧════════╛
  Total number of events: 3

  Resources:
  ╒══════════════════╤════════════════════╤════════════╤════════╕
  │ Resource         │   Priority ceiling │ Property   │   Mask │
  ╞══════════════════╪════════════════════╪════════════╪════════╡
  │ OSRES_RESOURCE01 │                  4 │ STANDARD   │      7 │
  ├──────────────────┼────────────────────┼────────────┼────────┤
  │ OSRES_RESOURCE02 │                  2 │ STANDARD   │      3 │
  ├──────────────────┼────────────────────┼────────────┼────────┤
  │ RES_SCHEDULER    │                  5 │ STANDARD   │      7 │
  ╘══════════════════╧════════════════════╧════════════╧════════╛
  Total number of resources: 3

  Priority Scheme:
  ╒══════════════════╤════════════╕
  │ Name             │   Priority │
  ╞══════════════════╪════════════╡
  │ OSTASK_TASK01    │          0 │
  ├──────────────────┼────────────┤
  │ OSTASK_TASK02    │          1 │
  ├──────────────────┼────────────┤
  │ OSRES_RESOURCE02 │          2 │
  ├──────────────────┼────────────┤
  │ OSTASK_TASK03    │          3 │
  ├──────────────────┼────────────┤
  │ OSRES_RESOURCE01 │          4 │
  ├──────────────────┼────────────┤
  │ RES_SCHEDULER    │          5 │
  ╘══════════════════╧════════════╛
  Total levels of priority: 6

  Alarms:
  ╒═════════════════╤═════════════╤═════════════╤═══════════════╤═══════════════╤═══════════════╤═════════════╤═════════════════════╕
  │ Name            │ Alarmtime   │ Cycletime   │ Event         │ Task          │ Action        │ Autostart   │ Callback            │
  ╞═════════════════╪═════════════╪═════════════╪═══════════════╪═══════════════╪═══════════════╪═════════════╪═════════════════════╡
  │ OSALARM_ALARM01 │ -           │ -           │ OSEVT_EVENT01 │ OSTASK_TASK01 │ SETEVENT      │ FALSE       │ -                   │
  ├─────────────────┼─────────────┼─────────────┼───────────────┼───────────────┼───────────────┼─────────────┼─────────────────────┤
  │ OSALARM_ALARM02 │ -           │ -           │ -             │ OSTASK_TASK02 │ ACTIVATETASK  │ FALSE       │ -                   │
  ├─────────────────┼─────────────┼─────────────┼───────────────┼───────────────┼───────────────┼─────────────┼─────────────────────┤
  │ OSALARM_ALARM03 │ 0           │ 5           │ -             │ -             │ ALARMCALLBACK │ TRUE        │ OsTickTimerCallback │
  ╘═════════════════╧═════════════╧═════════════╧═══════════════╧═══════════════╧═══════════════╧═════════════╧═════════════════════╛
  Total number of alarms: 3

  Interrupts:
  ╒═════════╤════════════╤══════════╤════════╤═══════════╕
  │ Name    │   Category │   Vector │   Prio │ Nesting   │
  ╞═════════╪════════════╪══════════╪════════╪═══════════╡
  │ ISR_000 │          2 │        0 │      0 │ FALSE     │
  ├─────────┼────────────┼──────────┼────────┼───────────┤
  │ ISR_001 │          2 │        1 │      0 │ FALSE     │
  ╘═════════╧════════════╧══════════╧════════╧═══════════╛
  Total number of used interrupts: 2
  Total number of CPU interrupts : 113
*/

//=============================================================================
// OS Configuration
//=============================================================================
OS_CONFIG_BEGIN

  //=============================================================================
  //  Tasks Configuration
  //=============================================================================
    OS_TASK_BEGIN
        OS_TASK_DEF(OSTASK_TASK01, 0, 0x800, 1, OS_AUTOSTART, EXTENDED, FULL_PREEMPT)
        OS_TASK_DEF(OSTASK_TASK02, 1, 800, 1, OS_AUTOSTART, EXTENDED, FULL_PREEMPT)
        OS_TASK_DEF(OSTASK_TASK03, 3, 800, 1, OS_AUTOSTART, EXTENDED, FULL_PREEMPT)
    OS_TASK_END

  //=============================================================================
  //  Events Configuration
  //=============================================================================
    OS_EVENT_BEGIN
        OS_EVENT_DEF(OSEVT_EVENT01, 0x1)
        OS_EVENT_DEF(OSEVT_EVENT02, 0x2)
        OS_EVENT_DEF(OSEVT_EVENT03, 0x4)
    OS_EVENT_END

  //=============================================================================
  //  Alarms Configuration
  //=============================================================================
    OS_ALARM_BEGIN
        OS_ALARM_DEF(OSALARM_ALARM01, SETEVENT, OSEVT_EVENT01, OSTASK_TASK01, 0)
        OS_ALARM_DEF(OSALARM_ALARM02, ACTIVATETASK, 0, OSTASK_TASK02, 0)
        OS_ALARM_DEF(OSALARM_ALARM03, ALARMCALLBACK, 0, 0, OsTickTimerCallback)
    OS_ALARM_END

  //=============================================================================
  //  Resource Configuration
  //=============================================================================
    OS_RESOURCE_BEGIN
        OS_RESOURCE_DEF(OSRES_RESOURCE01, 4, 7)
        OS_RESOURCE_DEF(OSRES_RESOURCE02, 2, 3)
        OS_RESOURCE_DEF(RES_SCHEDULER, 5, 7)
    OS_RESOURCE_END

  //=============================================================================
  //  Interrupts Configuration
  //=============================================================================
    OS_INTERRUPT_BEGIN
        OS_INTERRUPT_CAT2_DEF(ISR_000, 0, NOT_NESTED)  /* Interrupt vector 0 */
        OS_INTERRUPT_CAT2_DEF(ISR_001, 0, NOT_NESTED)  /* Interrupt vector 1 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 2 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 3 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 4 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 5 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 6 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 7 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 8 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 9 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 10 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 11 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 12 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 13 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 14 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 15 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 16 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 17 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 18 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 19 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 20 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 21 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 22 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 23 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 24 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 25 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 26 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 27 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 28 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 29 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 30 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 31 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 32 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 33 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 34 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 35 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 36 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 37 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 38 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 39 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 40 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 41 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 42 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 43 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 44 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 45 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 46 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 47 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 48 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 49 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 50 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 51 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 52 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 53 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 54 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 55 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 56 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 57 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 58 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 59 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 60 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 61 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 62 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 63 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 64 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 65 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 66 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 67 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 68 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 69 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 70 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 71 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 72 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 73 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 74 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 75 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 76 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 77 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 78 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 79 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 80 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 81 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 82 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 83 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 84 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 85 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 86 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 87 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 88 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 89 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 90 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 91 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 92 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 93 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 94 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 95 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 96 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 97 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 98 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 99 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 100 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 101 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 102 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 103 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 104 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 105 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 106 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 107 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 108 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 109 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 110 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 111 */
        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector 112 */
    OS_INTERRUPT_END

  //=============================================================================
  //  Hooks Configuration
  //=============================================================================
    #define STARTUPHOOK            TRUE
    #define ERRORHOOK              TRUE
    #define SHUTDOWNHOOK           TRUE
    #define PRETASKHOOK            TRUE
    #define POSTTASKHOOK           TRUE

  //=============================================================================
  //  Macros
  //=============================================================================
    #define OsStackCheck()             TRUE
    #define OsCpuFrequency()           16000000
    #define OsMaxVectorEntries()       113
    #define OsTickTime()               1000

OS_CONFIG_END
