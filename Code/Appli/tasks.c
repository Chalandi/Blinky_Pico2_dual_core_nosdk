

/*******************************************************************************************************************
** Includes
*******************************************************************************************************************/
#include"OsTcb.h"
#include"OsAPIs.h"
#include "Gpio.h"

//===============================================================================================================================
// OS TASK : T1
//===============================================================================================================================
TASK(T1)
{
  OsEventMaskType OsWaitEventMask = EVT_BLINK_BLUE_LED_FAST | EVT_TOGGLE_BLUE_LED;
  OsEventMaskType Events = 0;
  (void)OS_SetRelAlarm(ALARM_BLINK_BLUE_LED_FAST,0,1000);

  for(;;)
  {
    if(E_OK == OS_WaitEvent(OsWaitEventMask))
    {
      (void)OS_GetEvent((OsTaskType)T1, &Events);

      if((Events & EVT_BLINK_BLUE_LED_FAST) == EVT_BLINK_BLUE_LED_FAST)
      {
        OS_ClearEvent(EVT_BLINK_BLUE_LED_FAST);
        LED_GREEN_TOGGLE();
      }

      if((Events & EVT_TOGGLE_BLUE_LED) == EVT_TOGGLE_BLUE_LED)
      {
        OS_ClearEvent(EVT_TOGGLE_BLUE_LED);
        LED_BLUE_TOGGLE();
      }
    }
    else
    {
      OS_TerminateTask();
    }
  }
}

//===============================================================================================================================
// OS TASK : T2
//===============================================================================================================================
TASK(T2)
{
  static uint32 T2AliveCounter  = 0;
  static uint32 AlarmCycleValue = 0;
  OsEventMaskType OsWaitEventMask = EVT_BLINK_BLUE_LED_SLOW;
  OsEventMaskType Events = 0;
  (void)OS_SetRelAlarm(ALARM_BLINK_BLUE_LED_SLOW,0,10000);

  for(;;)
  {
    if(E_OK == OS_WaitEvent(OsWaitEventMask))
    {
      (void)OS_GetEvent((OsTaskType)T2, &Events);

      if((Events & EVT_BLINK_BLUE_LED_SLOW) == EVT_BLINK_BLUE_LED_SLOW)
      {
        OS_ClearEvent(EVT_BLINK_BLUE_LED_SLOW);
        T2AliveCounter++;
        
        if(T2AliveCounter % 2ul == 0ul)
        {
          AlarmCycleValue = 1000;
        }
        else
        {
          AlarmCycleValue = 250;
        }
        OS_CancelAlarm(ALARM_BLINK_BLUE_LED_FAST);
        OS_SetRelAlarm(ALARM_BLINK_BLUE_LED_FAST,0,AlarmCycleValue);
      }
    }
    else
    {
      OS_TerminateTask();
    }
  }
}
//===============================================================================================================================
// OS TASK : T3
//===============================================================================================================================
TASK(T3)
{
  OsEventMaskType OsWaitEventMask = EVT_BLINK_RED_LED_FAST;
  OsEventMaskType Events = 0;
  (void)OS_SetRelAlarm(ALARM_BLINK_RED_LED_FAST,0,1000);

  for(;;)
  {
    if(E_OK == OS_WaitEvent(OsWaitEventMask))
    {
      (void)OS_GetEvent((OsTaskType)T3, &Events);

      if((Events & EVT_BLINK_RED_LED_FAST) == EVT_BLINK_RED_LED_FAST)
      {
        OS_ClearEvent(EVT_BLINK_RED_LED_FAST);
        LED_RED_TOGGLE();
        OS_SetEvent(T1, EVT_TOGGLE_BLUE_LED);
      }
    }
    else
    {
      OS_TerminateTask();
    }
  }
}

//===============================================================================================================================
// OS TASK : T4
//===============================================================================================================================
TASK(T4)
{
  static uint32 T4AliveCounter  = 0;
  static uint32 AlarmCycleValue = 0;
  OsEventMaskType OsWaitEventMask = EVT_BLINK_RED_LED_SLOW;
  OsEventMaskType Events = 0;
  (void)OS_SetRelAlarm(ALARM_BLINK_RED_LED_SLOW,0,10000);

  for(;;)
  {
    if(E_OK == OS_WaitEvent(OsWaitEventMask))
    {
      (void)OS_GetEvent((OsTaskType)T4, &Events);

      if((Events & EVT_BLINK_RED_LED_SLOW) == EVT_BLINK_RED_LED_SLOW)
      {
        OS_ClearEvent(EVT_BLINK_RED_LED_SLOW);
        T4AliveCounter++;
        
        if(T4AliveCounter % 2ul == 0ul)
        {
          AlarmCycleValue = 1000;
        }
        else
        {
          AlarmCycleValue = 250;
        }
        OS_CancelAlarm(ALARM_BLINK_RED_LED_FAST);
        OS_SetRelAlarm(ALARM_BLINK_RED_LED_FAST,0,AlarmCycleValue);
      }
    }
    else
    {
      OS_TerminateTask();
    }
  }
}

