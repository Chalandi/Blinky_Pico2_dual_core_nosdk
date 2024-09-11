// *****************************************************************************************************************
// Filename    : OsSched.c
// 
// OS          : OSEK 2.2.3  
// 
// CC          : ECC1/BCC1
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 31.01.2019
// 
// Description : OS Scheduler implementation
// 
// *****************************************************************************************************************
#include"OsAPIs.h"
#include"OsTcb.h"
#include"OsAsm.h"
#include"OsHwPltfm.h"

//=============================================================================
// Global Variables
//=============================================================================
volatile OsSchedPrioType OsHwSchedPrioReg;
const uint32 OsSchedPrioTypeSize = sizeof(OsSchedPrioType);

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  prio 
/// \param  TaskId 
///
/// \return void 
//-----------------------------------------------------------------------------
void OsSetTaskPrioReady(const uint32 prio)
{
  if(sizeof(OsSchedPrioType)/sizeof(unsigned long) >= ((prio / 32U) + 1U))
  {
    *((unsigned long*)&OsHwSchedPrioReg + (prio / 32U)) |= (unsigned long)(1UL << (prio % 32U));
  }
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  prio 
///
/// \return void 
//-----------------------------------------------------------------------------
void OsClearTaskPrioReady(const uint32 prio)
{
  if(sizeof(OsSchedPrioType)/sizeof(unsigned long) >= ((prio / 32U) + 1U))
  {
    *((unsigned long*)&OsHwSchedPrioReg + (prio / 32U)) &= ~((unsigned long)(1UL << (prio % 32U)));
  }
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  prio 
///
/// \return uint8 
//-----------------------------------------------------------------------------
uint32 OsGetHighPrioReadyTaskIdx(const uint32 prio)
{
  for(uint32 tcbIdx = 0; tcbIdx < OS_NUMBER_OF_TASKS; tcbIdx++)
  {
    /* search for the task that own the prio */
    if(OCB_Cfg.pTcb[tcbIdx]->Prio == prio)
    {
      return(tcbIdx);
    }
  }
  /* return the OS internal idle loop index */
  return((uint32)OS_INTERNAL_TASK_ID); 
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_Schedule
///
/// \descr  If a higher-priority task is ready, the internal resource of the task is released, 
///         the current task is put into the ready state, its context is saved and the higher-priority task
///         is executed. Otherwise the calling task is continued.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_Schedule(void)
{
  if(OCB_Cfg.CurrentTaskIdx < OS_INTERNAL_TASK_ID                                                  &&
     OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->CeilingPrio != 0                                        &&
     OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio != OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->FixedPrio &&
     FALSE == OsIsCat2IntContext())
  {
    osInternalError(E_OS_RESOURCE);
  }
  else if(TRUE == OsIsInterruptContext() && FALSE == OsIsCat2IntContext()) /* Cat1 Interrupt */
  {
    osInternalError(E_OS_CALLEVEL);
  }
  else
  {
    /* Enter the critical section */
    OS_SuspendAllInterrupts();

    /* Get the high prio task id */
    OCB_Cfg.HighPrioReadyTaskIdx = OsGetHighPrioReadyTaskIdx((uint32)OsHwSearchForHighPrio());

    /* Exit the critical section */
    OS_ResumeAllInterrupts();


    /* case1: the scheduler is called explicitly by the running task or by an interrupt cat 2 and a ready task is found */
    if(OCB_Cfg.CurrentTaskIdx < OS_INTERNAL_TASK_ID && OCB_Cfg.HighPrioReadyTaskIdx < OS_INTERNAL_TASK_ID)
    {
        /* check if we need to switch the context (Preemption case) */
        if((OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == RUNNING) && (OCB_Cfg.pTcb[OCB_Cfg.HighPrioReadyTaskIdx]->Prio > OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio))
        {
          if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskSchedType == FULL_PREEMPT)
          {
            /* Call osPostTaskHook */
            #if(OS_POSTTASKHOOK)
            osPostTaskHook();
            #endif

            /* change the state of the current task */
            OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = READY;

            /* set the current task's ready bit */
            OsSetTaskPrioReady(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio);

            if(OCB_Cfg.OsCat2InterruptLevel == OS_FALSE && OCB_Cfg.OsLockDispatcher == OS_FALSE)
            {
              /* Call the dispatcher */
              osDispatch();
              return(E_OK);
            }
            else if(OCB_Cfg.OsLockDispatcher == OS_TRUE)
            {
              return(E_OK);
            }
            else
            {
              /*  Scheduler is called in interrupt cat 2 context, the Dispatcher will be executed later after the ISR */
              OCB_Cfg.OsIntCallDispatcher = OS_TRUE;
              return(E_OK);
            }
          }
          else
          {
            /* Current task is a non-preemptable task */
            return(E_OK);
          }
        }
        else if (OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == SUSPENDED || OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == WAITING)
        {
          /* Call osPostTaskHook */
          #if(OS_POSTTASKHOOK)
          osPostTaskHook();
          #endif

          /* Call the dispatcher */
          osDispatch();
          return(E_OK);
        }
        else
        {
          /* nothing to do */
          return(E_OK);
        }
    }
    /* case 2: - System idle loop is active and the scheduler is called explicitly from an interrupt cat 2 and a ready task is found */
    else if(OCB_Cfg.CurrentTaskIdx == OS_INTERNAL_TASK_ID && OCB_Cfg.HighPrioReadyTaskIdx < OS_INTERNAL_TASK_ID)
    {
      if(OCB_Cfg.OsCat2InterruptLevel == OS_TRUE && OCB_Cfg.OsIsRunning == OS_TRUE)
      {
        /* call the dispatcher after the execution of ISR cat2 */
        OCB_Cfg.OsIntCallDispatcher = OS_TRUE;
        return(E_OK);
      }
      else
      {
        /* The scheduler is called during the OS startup, Dispatcher will be called at the end of the startup procedure */
        return(E_OK);
      }
    }
   /* case 3: the scheduler is called explicitly by the running task or by an interrupt cat 2 and no ready task is found */
    else if(OCB_Cfg.CurrentTaskIdx < OS_INTERNAL_TASK_ID && OCB_Cfg.HighPrioReadyTaskIdx == OS_INTERNAL_TASK_ID)
    {
      /* check the current task state */
      if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == RUNNING)
      {
        /* no context switch is needed */
        return(E_OK);
      }
      else
      {
        /* context switch need to be performed => System will goes to os internal idle loop */

        /* Call PostTaskHook */
        #if(OS_POSTTASKHOOK)
        osPostTaskHook();
        #endif

        if(OCB_Cfg.OsCat2InterruptLevel == OS_FALSE)
        {
          /* The scheduler is called outside an interrupt context */
          osDispatch();
          return(E_OK);
        }
        else
        {
          /* call the dispatcher after the execution of ISR cat2 */
          OCB_Cfg.OsIntCallDispatcher = OS_TRUE;
          return(E_OK);
        }
      }
    }
   /* case 4: System idle loop is active and the scheduler is called explicitly from an interrupt cat 2 and no ready task is found */
    else if(OCB_Cfg.CurrentTaskIdx == OS_INTERNAL_TASK_ID && OCB_Cfg.HighPrioReadyTaskIdx == OS_INTERNAL_TASK_ID)
    {
      /* no context switch is needed */
      return(E_OK);
    }
    else
    {
      osInternalError(E_OS_KERNEL_PANIC);
    }
  }
}
