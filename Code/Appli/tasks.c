

/*******************************************************************************************************************
** Includes
*******************************************************************************************************************/
#include"OsTcb.h"
#include"OsAPIs.h"


volatile uint32 AlarmCycleValue = 0;

//===============================================================================================================================
// OS TASK : T1
//===============================================================================================================================
TASK(T1)
{
  static uint32 T1AliveCounter = 0;
  OsEventMaskType OsWaitEventMask = EVT_BLINK_BLUE_LED_FAST;
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
        T1AliveCounter++;
        /* blink led here !*/
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
  static uint32 T2AliveCounter = 0;
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
