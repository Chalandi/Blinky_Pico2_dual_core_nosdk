// *****************************************************************************************************************
// Filename    : OsTask.c
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
// Description : Task management implementation
// 
// *****************************************************************************************************************

//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
#include"OsTcb.h"
#include"OsAPIs.h"


//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_GetTaskID
///
/// \descr  GetTaskID returns the information about the TaskID of the task which is currently running.
///
/// \param  OsTaskRefType TaskID: Reference to the task which is currently running
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_GetTaskID(OsTaskRefType TaskID)
{
  *TaskID = OCB_Cfg.CurrentTaskIdx;
  return(E_OK);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_GetTaskState
///
/// \descr  Returns the state of a task (running, ready, waiting, suspended) at the time of calling GetTaskState.
///
/// \param          OsTaskType TaskID (In): Task reference
///         OsTaskStateRefType State (out): Reference to the state of the task <TaskID>
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_GetTaskState(OsTaskType TaskID, OsTaskStateRefType State)
{
  if(TaskID < OS_INTERNAL_TASK_ID)
  {
    *State = OCB_Cfg.pTcb[TaskID]->TaskStatus;

    if(*State == PRE_READY)
    {
      *State = READY; /* Change PRE_READY to READY to be conform to OSEK SPEC */
    }
    return(E_OK);
  }
  else
  {
    osInternalError(E_OS_ID);
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ActivateTask
///
/// \descr  The task <TaskID> is transferred from the suspended state into the ready state. 
///         The operating system ensures that the task code is being executed from the first statement.
///
/// \param  OsTaskType TaskID : Task reference
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_ActivateTask(OsTaskType TaskID)
{
  if(TaskID < OS_INTERNAL_TASK_ID)
  {
    if(OCB_Cfg.pTcb[TaskID]->TaskStatus == SUSPENDED)
    {
      OCB_Cfg.pTcb[TaskID]->TaskStatus = PRE_READY;

      /* set the current task's ready bit */
      OsSetTaskPrioReady(OCB_Cfg.pTcb[TaskID]->Prio);
      
      if(OCB_Cfg.pTcb[TaskID]->TaskType == BASIC)
      {
        OCB_Cfg.pTcb[TaskID]->MultipleActivation++;
      }

      /* Call the scheduler */
      (void)OS_Schedule();

      return(E_OK);
    }
    else if((OCB_Cfg.pTcb[TaskID]->TaskType == BASIC) && (OCB_Cfg.pTcb[TaskID]->MultipleActivation < OCB_Cfg.pTcb[TaskID]->MaxAllowedMultipleActivation))
    {
      OCB_Cfg.pTcb[TaskID]->MultipleActivation++;
      return(E_OK);
    }
    else
    {
      osInternalError(E_OS_LIMIT);
    }
  }
  else
  {
    osInternalError(E_OS_ID);
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_TerminateTask
///
/// \descr  This service causes the termination of the calling task. 
///         The calling task is transferred from the running state into the suspended state. 
///
/// \param  void
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_TerminateTask(void)
{
  if(  OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->CeilingPrio != 0 &&
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio != OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->FixedPrio)
  {
    osInternalError(E_OS_RESOURCE);
  }
  else if(TRUE == OsIsInterruptContext())
  {
    osInternalError(E_OS_CALLEVEL);
  }   
  else
  {
    if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskType == BASIC)
    {
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->MultipleActivation--;

      if(0 != OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->MultipleActivation)
      {
        OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = PRE_READY;
      }
      else
      {
        /* Set the new task state */
        OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = SUSPENDED;
      }
    }
    else
    {
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = SUSPENDED;
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->SetEvtMask = 0;
    }

    /* Call the scheduler */
    (void)OS_Schedule();
    
    return(E_OK);
  }  
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ChainTask
///
/// \descr  This service causes the termination of the calling task. 
///         After termination of the calling task a succeeding task <TaskID> is activated. 
///         Using this service, it ensures that the succeeding task starts to run at the earliest after 
///         the calling task has been terminated. 
///
/// \param  OsTaskType TaskID: Reference to the sequential succeeding task to be activated.
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_ChainTask(OsTaskType TaskID)
{
  if( OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->CeilingPrio != 0 &&
      OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio != OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->FixedPrio)
  {
    osInternalError(E_OS_RESOURCE);
  }
  else if(TRUE == OsIsInterruptContext())
  {
    osInternalError(E_OS_CALLEVEL);
  } 
  else if(TaskID >= OS_INTERNAL_TASK_ID)
  {
    osInternalError(E_OS_ID);
  }
  else
  {
    if(TaskID == OCB_Cfg.CurrentTaskIdx)
    {
      /* If the succeeding task is identical with the current task, this does not result in multiple requests. 
      The task is not transferred to the suspended state, but will immediately become ready again.*/

      (void)OS_Schedule();
    
      return(E_OK);
    }
    else
    {
      if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskType == BASIC)
      {
        OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->MultipleActivation--;

        if(0 != OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->MultipleActivation)
        {
          OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = PRE_READY;
          OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->MultipleActivation++;
          if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->MultipleActivation > OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->MaxAllowedMultipleActivation)
          {
            osInternalError(E_OS_LIMIT);
          }
        }
        else
        {
          OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = SUSPENDED;
        }

        OCB_Cfg.pTcb[TaskID]->MultipleActivation++;

        if(OCB_Cfg.pTcb[TaskID]->MultipleActivation > OCB_Cfg.pTcb[TaskID]->MaxAllowedMultipleActivation)
        {
          osInternalError(E_OS_LIMIT);
        }
      }
      else
      {
        OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = SUSPENDED;
        OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->SetEvtMask = 0;
      }

      if(OCB_Cfg.pTcb[TaskID]->TaskStatus == SUSPENDED)
      {
        OCB_Cfg.pTcb[TaskID]->TaskStatus = PRE_READY;

       /* set the current task's ready bit */
       OsSetTaskPrioReady(OCB_Cfg.pTcb[TaskID]->Prio);
      }

      (void)OS_Schedule();
    
      return(E_OK);
    }
  }
}


