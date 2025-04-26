// *****************************************************************************************************************
// Filename    : OsCrossCore.c
// 
// OS          : OSEK 2.2.3
// 
// CC          : ECC1/BCC1
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 14.10.2024
// 
// Description : cross core service implementation
// 
// *****************************************************************************************************************

//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
#include"OsAPIs.h"
#include"OsInternal.h"
#include"OsTcb.h"
#include"OsHwPltfm.h"

//------------------------------------------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------
// Types
//------------------------------------------------------------------------------------------------------------------
typedef enum
{
  OS_CROSS_CORE_SERVICE_SET_EVENT = 0,
  OS_CROSS_CORE_SERVICE_GET_EVENT,
  OS_CROSS_CORE_SERVICE_ACTIVATE_TASK,
  OS_CROSS_CORE_SERVICE_GET_TASK_STATE,
  OS_CROSS_CORE_SERVICE_GET_ALARM,
  OS_CROSS_CORE_SERVICE_SET_REL_ALARM,
  OS_CROSS_CORE_SERVICE_SET_ABS_ALARM,
  OS_CROSS_CORE_SERVICE_CANCEL_ALARM,
  OS_CROSS_CORE_SERVICE_SHUTDOWN_ALL_CORES,
  OS_CROSS_CORE_TOTAL_NUMBER_OF_SUPPORTED_SERVICES
}OsCrossCoreServiceType;

typedef OsStatusType (*osCrossCoreExecuteFuncType)(uint32_t* pRequest);

//------------------------------------------------------------------------------------------------------------------
// prototypes
//------------------------------------------------------------------------------------------------------------------
static void osCrossCoreSendRequest(uint32_t* pRequest, uint32_t* pResponse);
static OsStatusType osCrossCore_ExecuteSetEvent(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteGetEvent(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteActivateTask(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteGetTaskState(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteGetAlarm(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteSetRelAlarm(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteSetAbsAlarm(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteCancelAlarm(uint32_t* pRequest);
static OsStatusType osCrossCore_ExecuteShutdownAllCores(uint32_t* pRequest);

//------------------------------------------------------------------------------------------------------------------
// prototypes
//------------------------------------------------------------------------------------------------------------------
static const osCrossCoreExecuteFuncType osCrossCoreLookupTable[OS_CROSS_CORE_TOTAL_NUMBER_OF_SUPPORTED_SERVICES] = 
{
  &osCrossCore_ExecuteSetEvent,
  &osCrossCore_ExecuteGetEvent,
  &osCrossCore_ExecuteActivateTask,
  &osCrossCore_ExecuteGetTaskState,
  &osCrossCore_ExecuteGetAlarm,
  &osCrossCore_ExecuteSetRelAlarm,
  &osCrossCore_ExecuteSetAbsAlarm,
  &osCrossCore_ExecuteCancelAlarm,
  &osCrossCore_ExecuteShutdownAllCores
};

//------------------------------------------------------------------------------------------------------------------
// should be moved to MCAL or HwPlatform
//------------------------------------------------------------------------------------------------------------------
#include "core_arch.h"
#include "RP2350.h"

void Sio_Send(uint32_t data);
uint32_t Sio_SendAndReceive(uint32_t data);
uint32_t Sio_WaitTillReceive(void);
uint32_t Sio_ReceiveAndEcho(void);

void Sio_Send(uint32_t data)
{
  /* wait till fifo is ready to send */
  while(HW_PER_SIO->FIFO_ST.bit.RDY != 1UL);
  HW_PER_SIO->FIFO_WR.reg = data;
}

uint32_t Sio_SendAndReceive(uint32_t data)
{
  HW_PER_SIO->FIFO_WR.reg = data;

  /* wait for other core response */
  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);

  return(HW_PER_SIO->FIFO_RD.reg);
}

uint32_t Sio_WaitTillReceive(void)
{
  /* wait for other core response */
  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);
  return(HW_PER_SIO->FIFO_RD.reg);
}

uint32_t Sio_ReceiveAndEcho(void)
{
  uint32_t received_data = 0;

  /* wait for other core response */
  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);

  received_data = HW_PER_SIO->FIFO_RD.reg;

  HW_PER_SIO->FIFO_WR.reg = received_data;

  return(received_data);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr this function must be called with os interrupt disabled
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static void osCrossCoreSendRequest(uint32_t* pRequest, uint32_t* pResponse)
{
  /* get active core id */
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  /* get the active priority level */
  uint32_t OsInterruptSavedPrioLevel = osGetInterruptPriorityMask();

  /* disable cat2 interrupts by raising the priority level to the cat1 prio */
  osSetInterruptPriorityMask(OCB_Cfg[osActiveCore]->pInt->osIntCat1LowestPrioLevel);

  /* sending the request to the opposite core and waiting for echoing */
  for(uint32_t cpt=0; cpt < (pRequest[1] + 2ul); cpt++)
  {
    if(pRequest[cpt] != Sio_SendAndReceive(pRequest[cpt]))
    {
      /* something wrong with cross-core communication */
      osKernelError(E_OS_MULTICORE_COM_LOST);
    }
  }

  /* receive the response form the opposite core */
  for(uint32_t cpt=0; cpt < (pRequest[1] + 2ul); cpt++)
  {
    pResponse[cpt] = Sio_WaitTillReceive();
  }

  /* remove the pending cross core interrupt */
  osClearPendingInterrupt(25);

  /* restore the system prio level */
  osSetInterruptPriorityMask(OsInterruptSavedPrioLevel);

}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
ISR(osCrossCoreReceiveRequest)
{
   uint32_t OsCrossCoreBuffer[10];

   OsCrossCoreBuffer[0] = Sio_ReceiveAndEcho();
   OsCrossCoreBuffer[1] = Sio_ReceiveAndEcho();

   /* get the requested service information */
   for(uint32_t cpt=2; cpt < (OsCrossCoreBuffer[1] + 2ul); cpt++)
   {
    OsCrossCoreBuffer[cpt] = Sio_ReceiveAndEcho();
   }

   const OsCrossCoreServiceType osServiceId = (OsCrossCoreServiceType)OsCrossCoreBuffer[0];
   osCrossCoreExecuteFuncType osRequestedServiceHandler = (osCrossCoreExecuteFuncType)osCrossCoreLookupTable[osServiceId];

   if(osServiceId >= OS_CROSS_CORE_TOTAL_NUMBER_OF_SUPPORTED_SERVICES)
   {
    osKernelError(E_OS_MULTICORE_COM_LOST);
   }

   /* call the requested OS service */
   OsCrossCoreBuffer[2] = (osRequestedServiceHandler)(OsCrossCoreBuffer);

   /* send back the status to the requesting core */
   for(uint32_t cpt=0; cpt < (OsCrossCoreBuffer[1] + 2ul); cpt++)
   {
    Sio_Send(OsCrossCoreBuffer[cpt]);
   }

   /* clear pending cross core interrupt */
   osClearPendingInterrupt(25);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_SetEvent(OsTaskType TaskID, OsEventMaskType Mask)
{
  uint32_t Request[4] = {OS_CROSS_CORE_SERVICE_SET_EVENT, 2u, TaskID, Mask};
  uint32_t Response[4] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_GetEvent(OsTaskType TaskID, OsEventMaskRefType Event)
{
  uint32_t Request[4] = {OS_CROSS_CORE_SERVICE_GET_EVENT, 2u, TaskID, (uint32_t)Event};
  uint32_t Response[4] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_ActivateTask(OsTaskType TaskID)
{
  uint32_t Request[3] = {OS_CROSS_CORE_SERVICE_ACTIVATE_TASK, 1u, TaskID};
  uint32_t Response[3] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_GetTaskState(OsTaskType TaskID, OsTaskStateRefType State)
{
  uint32_t Request[4] = {OS_CROSS_CORE_SERVICE_GET_TASK_STATE, 2u, TaskID, (uint32_t)State};
  uint32_t Response[4] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_GetAlarm(OsAlarmType AlarmID, OsTickRefType Tick)
{
  uint32_t Request[4] = {OS_CROSS_CORE_SERVICE_GET_ALARM, 2u, (uint32_t)AlarmID, (uint32_t)Tick};
  uint32_t Response[4] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_SetRelAlarm(OsAlarmType AlarmID, OsTickType increment, OsTickType cycle)
{
  uint32_t Request[5] = {OS_CROSS_CORE_SERVICE_SET_REL_ALARM, 3u, (uint32_t)AlarmID, (uint32_t)increment, (uint32_t)cycle};
  uint32_t Response[5] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_SetAbsAlarm(OsAlarmType AlarmID, OsTickType start, OsTickType cycle)
{
  uint32_t Request[5] = {OS_CROSS_CORE_SERVICE_SET_ABS_ALARM, 3u, (uint32_t)AlarmID, (uint32_t)start, (uint32_t)cycle};
  uint32_t Response[5] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_CancelAlarm(OsAlarmType AlarmID)
{
  uint32_t Request[3] = {OS_CROSS_CORE_SERVICE_CANCEL_ALARM, 1u, (uint32_t)AlarmID};
  uint32_t Response[3] = {0};

  osCrossCoreSendRequest(Request, Response);

  return(Response[2]);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
OsStatusType osCrossCore_ShutdownAllCores(void)
{
  return(E_OK);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteSetEvent(uint32_t* pRequest)
{
  const OsTaskType TaskID    = (const OsTaskType)pRequest[2];
  const OsEventMaskType Mask = (const OsEventMaskType)pRequest[3];
  return(OS_SetEvent(TaskID, Mask));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteGetEvent(uint32_t* pRequest)
{
  const OsTaskType         TaskID = (const OsTaskType)pRequest[2];
  const OsEventMaskRefType Event  = (const OsEventMaskRefType)pRequest[3];
  return(OS_GetEvent(TaskID, Event));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteActivateTask(uint32_t* pRequest)
{
  const OsTaskType TaskID = (const OsTaskType)pRequest[2];
  return(OS_ActivateTask(TaskID));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteGetTaskState(uint32_t* pRequest)
{
  const OsTaskType         TaskID = (const OsTaskType)pRequest[2];
  const OsTaskStateRefType State  = (const OsTaskStateRefType)pRequest[3];
  return(OS_GetTaskState(TaskID, State));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteGetAlarm(uint32_t* pRequest)
{
  const OsAlarmType   AlarmID = (const OsAlarmType)pRequest[2];
  const OsTickRefType Tick    = (const OsTickRefType)pRequest[3];
  return(OS_GetAlarm(AlarmID, Tick));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteSetRelAlarm(uint32_t* pRequest)
{
  const OsAlarmType AlarmID   = (const OsAlarmType)pRequest[2];
  const OsTickType  increment = (const OsTickType)pRequest[3];
  const OsTickType  cycle     = (const OsTickType)pRequest[4];
  return(OS_SetRelAlarm(AlarmID, increment, cycle));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteSetAbsAlarm(uint32_t* pRequest)
{
  const OsAlarmType AlarmID = (const OsAlarmType)pRequest[2];
  const OsTickType  start   = (const OsTickType)pRequest[3];
  const OsTickType  cycle   = (const OsTickType)pRequest[4];
  return(OS_SetAbsAlarm(AlarmID, start, cycle));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteCancelAlarm(uint32_t* pRequest)
{
  const OsAlarmType AlarmID = (const OsAlarmType)pRequest[2];
  return(OS_CancelAlarm(AlarmID));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static OsStatusType osCrossCore_ExecuteShutdownAllCores(uint32_t* pRequest)
{
  (void)pRequest;
  #warning "ShutdownAllCores API not yet implemented !!!"
  return(E_OK);
}
