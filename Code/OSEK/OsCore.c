// *****************************************************************************************************************
// Filename    : OsCore.c
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
// Description : Operating system services implementation
// 
// *****************************************************************************************************************

//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
#include"OsAPIs.h"
#include"OsInternal.h"
#include"OsTcb.h"
#include"OsAsm.h"
#include"OsHwPltfm.h"

//------------------------------------------------------------------------------------------------------------------
// Static function prototypes
//------------------------------------------------------------------------------------------------------------------
static void osInitTimer(void);
static void osStartTimer(void);
static void osIdleLoop(void);

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_StartOS
///
/// \descr  The user can call this system service to start the operating system in a specific mode
///
/// \param  OsAppModeType Mode
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_StartOS(OsAppModeType Mode)
{
  (void) Mode;

  if(TRUE == OsIsInterruptContext())
  {
    return;
  }
  
  if(OS_NUMBER_OF_TASKS > 0)
  {
    /* INIT TCBs */
    for(uint32 tcbIdx = 0; tcbIdx < OS_NUMBER_OF_TASKS; tcbIdx++)
    {
      /* Init all stacks with the magic marker */
      const uint32 stack_size = (OCB_Cfg.pTcb[tcbIdx]->pstack_top - OCB_Cfg.pTcb[tcbIdx]->pstack_bot + sizeof(uint32)) / sizeof(uint32);

      for(uint32 offset = 0; offset < stack_size; offset++)
      {
        ((volatile uint32*)OCB_Cfg.pTcb[tcbIdx]->pstack_bot)[offset] = (uint32)OS_STACK_MAGIC_MARKER;
      }
      
      /* Set default tasks priorities */
      OCB_Cfg.pTcb[tcbIdx]->Prio = OCB_Cfg.pTcb[tcbIdx]->FixedPrio;
    }
    
    /* Init system tick timer */
    osInitTimer();
    
    /* Start all autostart task */
    for(uint32 tcbIdx = 0; tcbIdx < OS_NUMBER_OF_TASKS; tcbIdx++)
    {
      if(OCB_Cfg.pTcb[tcbIdx]->Autostart == OS_AUTOSTART && OCB_Cfg.pTcb[tcbIdx]->TaskStatus == SUSPENDED)
      {
        /* Switch to PRE_READY state */
        OCB_Cfg.pTcb[tcbIdx]->TaskStatus = PRE_READY;

        /* set the current task's ready bit */
        OsSetTaskPrioReady(OCB_Cfg.pTcb[tcbIdx]->Prio);
        
        /* Update the number of multiple activation */
        if(OCB_Cfg.pTcb[tcbIdx]->TaskType == BASIC)
        {
          OCB_Cfg.pTcb[tcbIdx]->MultipleActivation++;
        }
      }
    }

    /* Init Interrupts */
    osInitInterrupts();
    
    /* Call startup hook function */
    #if(OS_STARTUPHOOK)
    osStartupHook();
    #endif

    /* Enable the interrupts */
    ENABLE_INTERRUPTS();
    
    /* Start system tick timer */
    osStartTimer();

    /* Start all relative autostart alarms */
    for(uint32 alarmIdx = 0; alarmIdx < OS_NUMBER_OF_ALARMS; alarmIdx++)
    {
      if(OCB_Cfg.pAlarm[alarmIdx]->AutoStart == ALARM_AUTOSTART)
      {
        OS_SetRelAlarm((OsAlarmType)alarmIdx,OCB_Cfg.pAlarm[alarmIdx]->InitTicks,OCB_Cfg.pAlarm[alarmIdx]->InitCycles);
      }
    }
        
    /* Call Scheduler */
    (void)OS_Schedule();
    
    /* Set the OS running flag */
    OCB_Cfg.OsIsRunning = OS_TRUE;

    /* Call the dispatcher */
    osDispatch();
  }
  
  /* Infinite loop */
  osIdleLoop();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osInitTimer
///
/// \descr  Init the HW timer used as system tick timer
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void osInitTimer(void)
{
  osHwTimerInit();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osStartTimer
///
/// \descr  Start the HW timer used as system tick timer
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void osStartTimer(void)
{
  osHwTimerStart();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osReloadTimer
///
/// \descr  Reload the HW timer used as system tick timer
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void osReloadTimer(void)
{
  osHwTimerReload();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsDispatcher
///
/// \descr  Context switch engine
///
/// \param  uint32 StackPtr: Current stack pointer of the active task
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
uint32 OsDispatcher(uint32 StackPtr)
{

  /* Save the current stack pointer of the running task before switching the context */
  if(OCB_Cfg.CurrentTaskIdx < OS_INTERNAL_TASK_ID)
  {
    OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer = StackPtr;

    /* Check the stack pointer against stack overflow */
    if( (!(StackPtr <(uint32)(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pstack_top) &&
           StackPtr >= (uint32)(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pstack_bot)))  ||
       (*(uint32*)(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pstack_bot) != OS_STACK_MAGIC_MARKER)
      )
    {
      /* Stack overflow */
      osInternalError(E_OS_STACKFAULT);
    }
  }
  else
  {
    /* save the system stack */
    OCB_Cfg.OsCurrentSystemStackPtr = StackPtr;
  }

  /* Set the new current task */
  OCB_Cfg.CurrentTaskIdx = OCB_Cfg.HighPrioReadyTaskIdx;
  
  if(OCB_Cfg.CurrentTaskIdx < OS_INTERNAL_TASK_ID)  
  {  
    /* check if we need to create a new stack frame for the new task */
    if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == PRE_READY)
    {

      /* Update the current task state */
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = RUNNING;

      /* Clear the current task's ready bit */
      OsClearTaskPrioReady(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio);
      
      /* Call osPreTaskHook */
      #if(OS_PRETASKHOOK)
      osPreTaskHook();
      #endif
      
      /* Create Stack Frame for the 1st execution */
      const uint32 NewStackFramePtr = OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pstack_top;
      const pFunc  NewTaskPtr       = OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->function;

      /* Save the new stack ptr */
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer = NewStackFramePtr;

      /* Start the new task */
      OsStartNewTask(NewStackFramePtr, NewTaskPtr);

    }
    else if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == READY)
    {
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = RUNNING;

      /* Clear the current task's ready bit */
      OsClearTaskPrioReady(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio);
      
      /* Call osPreTaskHook */
      #if(OS_PRETASKHOOK)
      osPreTaskHook();
      #endif
    }
  }
  else
  {
    /* there is no ready task in the system 
       The OS will stay in endless loop until
       an event will be occurred */
    return(OCB_Cfg.OsCurrentSystemStackPtr);
  }
  return(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  Interrupt service routine
///
/// \descr  ISR of system tick interrupt
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
ISR(SysTickTimer)
{
  OCB_Cfg.OsSysTickCounter++;
  osAlarmsManagement();
  osReloadTimer();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsStoreStackPointer
///
/// \descr  Store the current stack pointer in case of category 2 interrupt
///
/// \param  uint32 StackPtrValue: Current stack pointer
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsStoreStackPointer(uint32 StackPtrValue)
{
  /* get the interrupt nesting level */
  const uint32 OsInterruptNestingDepth = osGetHwIntNestingLevel();

  /* save the interrupt nesting level stack pointer */
  OCB_Cfg.OsIntNestSavedStackPointer[OsInterruptNestingDepth - 1u] = StackPtrValue;

  /* store the preempted task context only in nested level 1,
     the other nesting interrupts will use the current stack */
  if(OsInterruptNestingDepth == 1u)
  {
    /* set the Cat2 interrupt flag */
    OCB_Cfg.OsCat2InterruptLevel = 1;

    if(OCB_Cfg.CurrentTaskIdx < OS_INTERNAL_TASK_ID)
    {
      /* preempted from task level */
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer = StackPtrValue; /* current task stack will be used */
    }
    else
    {
      /* preempted from OS level */
      OCB_Cfg.OsCurrentSystemStackPtr = StackPtrValue; /* system stack will be used */
    }
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsGetSavedStackPointer
///
/// \descr  return the saved stack pointer in case of category 2 interrupt
///
/// \param  void
///
/// \return uint32 : saved stack pointer
//------------------------------------------------------------------------------------------------------------------
uint32 OsGetSavedStackPointer(void)
{
  /* get the interrupt nesting level */
  const uint32 OsInterruptNestingDepth = osGetHwIntNestingLevel();

  if(OsInterruptNestingDepth == 1u)
  {
    if(OCB_Cfg.CurrentTaskIdx < OS_INTERNAL_TASK_ID)
    {
      return(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer);
    }
    else
    {
      return(OCB_Cfg.OsCurrentSystemStackPtr);
    }
  }
  else
  {
    return(OCB_Cfg.OsIntNestSavedStackPointer[OsInterruptNestingDepth - 1u]);
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIntCallDispatch
///
/// \descr  Call the dispatcher to switch the context if needed after an category 2 interrupt 
///
/// \param  uint32 StackPtr: Current stack pointer
///
/// \return uint32 : The new stack pointer after switching the context otherwise the last saved stack pointer
//------------------------------------------------------------------------------------------------------------------
uint32 OsIntCallDispatch(uint32 StackPtr)
{
  /* get the interrupt nesting level */
  const uint32 OsInterruptNestingDepth = osGetHwIntNestingLevel();

  if(OsInterruptNestingDepth == 1u)
  {
    /* Disable the Hw nesting */
    osDisableHwIntNesting();

    /* Reset the flag */
    OCB_Cfg.OsCat2InterruptLevel = 0;
    
    if(OCB_Cfg.OsIntCallDispatcher == 1)
    {
      /* The internal system state is changed by the ISR cat2 (an Event is triggered)
         at this point the OS will switch to the new context (target task context) */

      /* Reset the flag */
      OCB_Cfg.OsIntCallDispatcher = 0;

      /* Call the Dispatcher to execute the context switch process */
      return(OsDispatcher(StackPtr));
    }
    else
    {
      /* The system behavior is not changed by the ISR cat2
         The cpu will restore the context saved by the interrupt */
      return(StackPtr);
    }
  }
  else
  {
    /* in nesting interrupt behavior
       restore the stack pointer from the saved context */
    return(StackPtr);
  }
}  

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_GetActiveApplicationMode
///
/// \descr  This service returns the current application mode.
///
/// \param  void
///
/// \return OsAppModeType : The application mode
//------------------------------------------------------------------------------------------------------------------
OsAppModeType OS_GetActiveApplicationMode(void)
{
  return(APP_MODE);
}  

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ShutdownOS
///
/// \descr  The user can call this system service to abort the overall system (e.g. emergency off). 
///         The operating system also calls this function internally, 
///         if it has reached an undefined internal state and is no longer ready to run.
///
/// \param  OsStatusType Error: Error causing the shutdown of the OS
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_ShutdownOS(OsStatusType Error)
{
#if(OS_SHUTDOWNHOOK)
  osShutdownHook(Error);
#else
  (void)Error;
#endif
  
  DISABLE_INTERRUPTS();
  
  /* Kill all tasks */
  for(uint32 tcbIdx = 0; tcbIdx < OS_NUMBER_OF_TASKS; tcbIdx++)
  {
    OCB_Cfg.pTcb[tcbIdx]->TaskStatus = SUSPENDED;
  }
  for(;;);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osIdleLoop
///
/// \descr  This function is called by the dispatcher when no ready task is found.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void osIdleLoop(void)
{
  /* When no ready task is found the CPU will be waiting here for any event */
  for(;;);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsCat2IntContext
///
/// \descr  This function checks if the cpu is in category 2 interrupt context or not.
///
/// \param  void
///
/// \return boolean: TRUE -> Category 2 interrupt context, FALSE -> none category 2 interrupt context
//------------------------------------------------------------------------------------------------------------------
boolean OsIsCat2IntContext(void)
{
    return((boolean)OCB_Cfg.OsCat2InterruptLevel);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_DisableAllInterrupts
///
/// \descr  Disable all interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_DisableAllInterrupts(void)
{
  DISABLE_INTERRUPTS();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_EnableAllInterrupts
///
/// \descr  enable all interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_EnableAllInterrupts(void)
{
  ENABLE_INTERRUPTS();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_SuspendAllInterrupts
///
/// \descr  Suspend all interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_SuspendAllInterrupts(void)
{
  osSaveAndDisableIntState();
}  

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ResumeAllInterrupts
///
/// \descr  Resume all suspended interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_ResumeAllInterrupts(void)
{
  osRestoreSavedIntState();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_SuspendOSInterrupts
///
/// \descr  Suspend all OS interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_SuspendOSInterrupts(void)
{
  /* Get the global mask prio */
  OCB_Cfg.OsInterruptSavedLevel = osGetInterruptPriorityMask();

  /* Disable OS interrupts */
  osSetInterruptPriorityMask(OS_INT_CAT1_LOWEST_PRIO_LEVEL);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ResumeOSInterrupts
///
/// \descr  Resume all suspended OS interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_ResumeOSInterrupts(void)
{
  /* Restore the global mask prio */
  osSetInterruptPriorityMask(OCB_Cfg.OsInterruptSavedLevel);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsr_UndefinedFunc
///
/// \descr  default handler for EI level interrupt
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsIsr_UndefinedFunc(void)
{
  OsKernelError(E_OS_DISABLEDINT);
  for(;;);
}

//-----------------------------------------------------------------------------
/// \brief  OsGetSystemTicks
///
/// \descr  Get the system tick counter
///
/// \param  void
///
/// \return uint64 
//-----------------------------------------------------------------------------
uint64 OsGetSystemTicksCounter(void)
{
  return(OCB_Cfg.OsSysTickCounter);
}


//-----------------------------------------------------------------------------
/// \brief  OsGetSystemTicksElapsedTime
///
/// \descr  Get the system elapsed time relative to the prvTicks
///
/// \param  prvTicks : perivous system tick
///
/// \return uint64 
//-----------------------------------------------------------------------------
uint64 OsGetSystemTicksElapsedTime(uint64 prvTicks)
{
  return((uint64)(OCB_Cfg.OsSysTickCounter - prvTicks));
}

//-----------------------------------------------------------------------------
/// \brief  osErrTaskExitWithoutTerminate
///
/// \descr  Catch abnormal exit from task function
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void osErrTaskExitWithoutTerminate(void)
{
  DISABLE_INTERRUPTS();
  for(;;);
}

//-----------------------------------------------------------------------------
/// \brief  OsKernelError
///
/// \descr  Catch all internal OS errors
///
/// \param  err 
///
/// \return void 
//-----------------------------------------------------------------------------
void OsKernelError(OsStatusType err)
{
  DISABLE_INTERRUPTS();
  #if(OS_ERRORHOOK)
    osErrorHook(err);
  #else
    (void)err;
  #endif
    for(;;);
}

//-----------------------------------------------------------------------------
/// \brief  osGetMaximumStackUsage
///
/// \descr  Calculate the maximum stack usage during runtime
///
/// \param  TaskId 
///
/// \return uint32 
//-----------------------------------------------------------------------------
uint32 osGetMaximumStackUsage(uint32 TaskId)
{
  uint32* pStack = (uint32*)NULL;
  uint32 Bottom = OCB_Cfg.pTcb[TaskId]->pstack_bot;
  uint32 Top    = OCB_Cfg.pTcb[TaskId]->pstack_top;

  #define ALIGN4_ADDRESS(x) ((x) & (0xFFFFFFFCUL))

  while(sizeof(uint32) != (Top - Bottom))
  {
    pStack = (uint32*)(ALIGN4_ADDRESS(Bottom + ((Top - Bottom + sizeof(uint32)) / 2)));

    if(*pStack != OS_STACK_MAGIC_MARKER)
    {
       Top = (uint32)pStack;
    }
    else
    {
      Bottom = (uint32)pStack;
    }
  }
  return((uint32)(OCB_Cfg.pTcb[TaskId]->pstack_top) - Top + sizeof(uint32));
}

