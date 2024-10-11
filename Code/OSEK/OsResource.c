// *****************************************************************************************************************
// Filename    : OsResource.c
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
/// \brief  OS_GetResource
///
/// \descr  This call serves to enter critical sections in the code that are assigned to the resource referenced 
///         by <ResID>. A critical section shall always be left using ReleaseResource
///
/// \param  OsResourceType ResID: Reference to resource
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_GetResource(OsResourceType ResID)
{
  if(ResID < OS_NUMBER_OF_RESOURCES)
  {
    if(((OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pRes[ResID]->AuthorizedTask & (1ul << OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx)) != 0) &&
       OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pRes[ResID]->CurrentOccupiedTask == OS_INVALID_TASK)
    {
      /* The resource is available */

      /* reserve the resource to the current task */
      OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pRes[ResID]->CurrentOccupiedTask = OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx;

      /* Set the ceilling prio of the resource to the current task */
      OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->CeilingPrio = OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pRes[ResID]->ResCeilingPrio;
      OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->Prio = OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->CeilingPrio;

      return(E_OK);
    }
    else
    {
      /* Resource is occupied by another task */
      osInternalError(E_OS_ACCESS);
    }
        
  }
  else
  {
    osInternalError(E_OS_ID);
  }      
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ReleaseResource
///
/// \descr  ReleaseResource is the counterpart of GetResource and serves to leave critical sections in the code 
///         that are assigned to the resource referenced by <ResID>
///
/// \param  OsResourceType ResID: Reference to resource
///
/// \return OsStatusType
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_ReleaseResource(OsResourceType ResID)
{
  if(ResID < OS_NUMBER_OF_RESOURCES)
  {
    if(OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pRes[ResID]->CurrentOccupiedTask == OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx)
    {
      /* Release the resource */
      OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pRes[ResID]->CurrentOccupiedTask = OS_INVALID_TASK;
      
      /* Set the default prio to the current task */
      OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->CeilingPrio = 0;
      OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->Prio = OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->pTcb[OCB_Cfg[osRemapPhyToLogicalCoreId(osGetCoreId())]->CurrentTaskIdx]->FixedPrio;

      /* Call the scheduler */
      (void)osSchedule();

      return(E_OK);
    }
    else
    {
      osInternalError(E_OS_NOFUNC);
    }
  }
  else
  {
    osInternalError(E_OS_ID);
  }  
}
