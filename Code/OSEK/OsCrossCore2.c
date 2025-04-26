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

#include "core_arch.h"
#include "RP2350.h"
//------------------------------------------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------------------------------------------
#define CROSS_CORE_REQ_RES_HEADER_SIZE  3ul
#define IDX_0_CORE                      0ul
#define IDX_1_SERVICE                   1ul
#define IDX_2_REQUEST_SIZE              2ul
#define IDX_2_RESPONSE_SIZE             2ul
#define IDX_3_FIRST_PARAM               3ul
#define IDX_3_FIRST_STATUS              3ul

#define OS_CROSS_CORE_SET_EVENT_SERVICE (uint32_t)0u

static OsStatusType osCrossCore_ExecuteSetEvent(uint32_t* pRequest);

typedef OsStatusType (*osCrossCoreExecuteFuncType)(uint32_t* pRequest);

static const osCrossCoreExecuteFuncType osCrossCoreLookupTable[] = { &osCrossCore_ExecuteSetEvent,
                                                                     0
                                                                   };

static void osCrossCoreSendRequest(OsCoreId ActiveCore, OsCoreId TargetCore, uint32_t* pRequest, uint32_t* pResponse);

//------------------------------------------------------------------------------------------------------------------
// MCAL or HwPlatform
//------------------------------------------------------------------------------------------------------------------
#include "core_arch.h"

//------------------------------------------------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//------------------------------------------------------------------------------------------------------------------
static void osCrossCoreSendRequest(OsCoreId ActiveCore, OsCoreId TargetCore, uint32_t* pRequest, uint32_t* pResponse) /* this will be called with os interrupt disabled */
{
  /* 1- Disable os interrupt 
     2- Send Request (fill the HW FIFO and avoid anything that may trigger interrupt for error)
         when send the first request it must
     3- pull Response (poll the HW FIFO)
     4- Remove Pending interrupt on the sending core
     5- restore os interrupts (if running from task level)
     6- return the received response

     pRequest[0] ----> logic Id of the requesting Core
     pRequest[1] ----> Id of the requested os service
     pRequest[2] ----> number of parameters
     pRequest[3] ----> parameter 1 ...

     #define IDX_0_CORE              0
     #define IDX_1_SERVICE           1
     #define IDX_2_REQUEST_SIZE      2
     #define IDX_2_RESPONSE_SIZE     2
     #define IDX_3_FIRST_PARAM       3
     #define IDX_3_FIRST_STATUS      3

  */
  uint32_t OsInterruptSavedPrioLevel = 0;
  const uint32 osActiveCore          = osGetLogicalCoreId(osGetCoreId());
#if 0
  /* get the global mask prio */
  OsInterruptSavedPrioLevel = osGetInterruptPriorityMask();

  /* disable cat2 interrupts by raising the priority level to the cat1 prio */
  osSetInterruptPriorityMask(OCB_Cfg[osActiveCore]->pInt->osIntCat1LowestPrioLevel);
#else
  DISABLE_INTERRUPTS();
#endif
  /* acquiring the local spinlock */
  while(0);

  /* sending the request */
  for(uint32_t cpt=0; cpt < (pRequest[IDX_2_REQUEST_SIZE] + CROSS_CORE_REQ_RES_HEADER_SIZE); cpt++)
  {
    OCB_Cfg[TargetCore]->OsCrossCoreBuffer[cpt] = pRequest[cpt];
  }

  /* generate the cross core interrupt on the other core */
  HW_PER_SIO->DOORBELL_OUT_SET.reg |= (1ul << 0);

  /* wait for the response (other core will signal an interrupt to the requesting core) */
  while((HW_PER_SIO->DOORBELL_IN_SET.reg & (1ul << 0)) == 0);

  /* receive the response */
  for(uint32_t cpt=0; cpt < (pRequest[IDX_2_REQUEST_SIZE] + CROSS_CORE_REQ_RES_HEADER_SIZE); cpt++)
  {
    pResponse[cpt] = OCB_Cfg[ActiveCore]->OsCrossCoreBuffer[cpt];
  }

  /* clear the interrupt on the active core */
  HW_PER_SIO->DOORBELL_IN_CLR.reg |= (1ul << 0);

  /* Release the spin lock */
  while(0);

  #if 0
  /* restore the system prio level */
  osSetInterruptPriorityMask(OsInterruptSavedPrioLevel);
#else
  ENABLE_INTERRUPTS();
#endif
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
OsStatusType osCrossCore_SetEvent(OsCoreId ActiveCore, OsCoreId TargetCore, OsTaskType TaskID, OsEventMaskType Mask)
{
  uint32_t Request[5]  = {ActiveCore, OS_CROSS_CORE_SET_EVENT_SERVICE, 2u, TaskID, Mask};
  uint32_t Response[5] = {0};

  osCrossCoreSendRequest(ActiveCore, TargetCore, Request, Response); /* blocking call till we get a response */

  return(Response[IDX_3_FIRST_STATUS]);
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
  const OsTaskType TaskID    = (const OsTaskType)pRequest[IDX_3_FIRST_PARAM];
  const OsEventMaskType Mask = (const OsEventMaskType)pRequest[IDX_3_FIRST_PARAM + 1];

  pRequest[IDX_2_RESPONSE_SIZE] = 1;
  pRequest[IDX_3_FIRST_STATUS]  = (uint32_t)OS_SetEvent(TaskID, Mask);

  return(pRequest[IDX_3_FIRST_STATUS]);
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
  /* this interrupt will be triggered when this core receives requests from other core
     it must execute the request inside the ISR and send the response back

     pRequest[0] ----> logic Id of the requesting Core
     pRequest[1] ----> Id of the requested os service
     pRequest[2] ----> number of parameters
     pRequest[3] ----> parameter 1 ...

     pResponse[0] ----> logic Id of the responding Core
     pResponse[1] ----> Id of the requested os service + 0x40
     pResponse[2] ----> number of status
     pResponse[3] ----> status 1 ...

  */
  const uint32 osActiveCore     = osGetLogicalCoreId(osGetCoreId());

  /* disable nesting */
  while(0);

  const uint32 osTargetCore     = OCB_Cfg[osActiveCore]->OsCrossCoreBuffer[0];
  const uint32 RequestedService = OCB_Cfg[osActiveCore]->OsCrossCoreBuffer[1];

  /* call the appropriate OS service from lookup table */
  (void)(osCrossCoreLookupTable[RequestedService])((uint32_t*)OCB_Cfg[osActiveCore]->OsCrossCoreBuffer);

  OCB_Cfg[osTargetCore]->OsCrossCoreBuffer[IDX_0_CORE]    = osActiveCore;
  OCB_Cfg[osTargetCore]->OsCrossCoreBuffer[IDX_1_SERVICE] = RequestedService + 0x40;

  /* notify the requesting core */
  HW_PER_SIO->DOORBELL_OUT_SET.reg |= (1ul << 0);

  /* enable nesting */
  while(0);

}
