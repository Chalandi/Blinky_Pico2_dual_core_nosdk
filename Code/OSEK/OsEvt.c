// *****************************************************************************************************************
// Filename    : OsEvent.c
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
// Description : Event & resource mechanism implementation
// 
// *****************************************************************************************************************

//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
#include"OsTcb.h"
#include"OsAPIs.h"

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_SetEvent
///
/// \descr  The events of task <TaskID> are set according to the event mask <Mask>. 
///         Calling SetEvent causes the task <TaskID> to be transferred to the ready state, 
///         if it was waiting for at least one of the events specified in <Mask>.
///
/// \param  OsTaskType TaskID    : Reference to the task for which one or several events are to be set
///         OsEventMaskType Mask : Mask of the events to be set
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_SetEvent(OsTaskType TaskID, OsEventMaskType Mask)
{
  if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->TaskType == BASIC)
  {
    osInternalError(E_OS_ACCESS);
  }
  else if(TaskID >= OS_INTERNAL_TASK_ID)
  {
    osInternalError(E_OS_ID);
  }
  else if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->TaskStatus == SUSPENDED)
  {
    osInternalError(E_OS_STATE);
  }  
  else
  {
    OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->SetEvtMask |= Mask;
    
    if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->TaskStatus == WAITING)
    {
      if((OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->SetEvtMask & OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->WaitEvtMask) != 0)
      {  
        /* Switch state to Ready */
        OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->TaskStatus = READY;

        /* set the task's ready bit */
        osSetTaskPrioReady(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->Prio);

        /* Call the scheduler */
        (void)osSchedule();
      }
    }
    return(E_OK);
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ClearEvent
///
/// \descr  The events of the extended task calling ClearEvent are cleared according to the event mask <Mask>. 
///
/// \param  OsEventMaskType Mask : Mask of the events to be clear
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_ClearEvent(OsEventMaskType Mask)
{
  if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->TaskType == BASIC)
  {
    osInternalError(E_OS_ACCESS);
  }
  else if(TRUE == osIsInterruptContext())
  {
    osInternalError(E_OS_CALLEVEL);
  }  
  else
  {
    OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->SetEvtMask &=(OsEventMaskType)(~Mask);
    return(E_OK);
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_GetEvent
///
/// \descr  This service returns the current state of all event bits of the task <TaskID>, 
///         not the events that the task is waiting for.
///
/// \param         OsTaskType TaskID (in) : Task whose event mask is to be returned
///         OsEventMaskRefType Event (out): Reference to the memory of the return data
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_GetEvent(OsTaskType TaskID, OsEventMaskRefType Event)
{
  if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->TaskType == BASIC)
  {
    osInternalError(E_OS_ACCESS);
  }
  else if(TaskID >= OS_INTERNAL_TASK_ID)
  {
    osInternalError(E_OS_ID);
  }
  else if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->TaskStatus == SUSPENDED)
  {
    osInternalError(E_OS_STATE);
  }  
  else
  {
    *Event = OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[TaskID]->SetEvtMask;
    return(E_OK);    
  }  
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_WaitEvent
///
/// \descr  The state of the calling task is set to waiting, unless at least one of the events specified in <Mask> 
///         has already been set. 
///
/// \param  OsEventMaskType Mask : Mask of the events waited for
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_WaitEvent(OsEventMaskType Mask)
{
  if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->CeilingPrio != 0 || OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->Prio != OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->FixedPrio)
  {  
    osInternalError(E_OS_RESOURCE);
  }
  else if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->TaskType == BASIC)
  { 
    osInternalError(E_OS_ACCESS);
  }
  else if(TRUE == osIsInterruptContext())
  {
    osInternalError(E_OS_CALLEVEL);
  }   
  else
  {  
    /* Store the new event mask*/
    OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->WaitEvtMask = Mask;
    
    /* Check if the event waiting for is already set */
    if((OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->SetEvtMask & OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->WaitEvtMask) == 0)
    {
      /* event not present -> set current task to waiting */
      OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->TaskStatus = WAITING;
      
      /* Call the scheduler */
      (void)osSchedule();  
    }    
    
    return(E_OK);
  }
}
      
