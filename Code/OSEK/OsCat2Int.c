// *****************************************************************************************************************
// Filename    : OsCat2Int.c
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
// Description : OS interrupt category 2 management implementation
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
/// \brief  OsRunCat2Isr
///
/// \descr  This function is the entry point of all category 2 interrupts (PLIC).
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
 __attribute__((weak)) void OsRunCat2Isr(void)
{
  /* get the active interrupt vector id */
  const uint32 IntId = osGetActiveInterruptVectorId();

  if(IsrLookupTable[IntId].type == NOT_NESTED)
  {
    /* disable the nesting of the current interrupt priority level (Cat1 interrupts will kept unmasked) */
    osSetInterruptPriorityMask(OS_INT_CAT1_LOWEST_PRIO_LEVEL);
  }

  /* enable global interrupt flag */
  ENABLE_INTERRUPTS();

  /* call the interrupt service routine */
  IsrLookupTable[IntId].IsrFunc();
}
