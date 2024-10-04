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
/// \descr  This function is the entry point of all category 2 interrupts
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
    /* disable the nesting of the current interrupt priority level but keep it enabled for category 1 interrupts */
    osSetInterruptPriorityMask(OS_INT_CAT1_LOWEST_PRIO_LEVEL);
  }

  /* enable interrupt nesting before calling the ISR */
  osEnableIntNesting();

  /* call the appropriate interrupt service routine */
  IsrLookupTable[IntId].IsrFunc();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsIncNestingDepthLevel(void)
{
  /* called by the OS with interrupt disabled, no need to lock the internal resource */
  if(0 == OsGetSysPrimaskReg())
    OsKernelError(E_OS_ENABLEDINT);

  OCB_Cfg.OsInterruptNestingDepth++;

  if(OCB_Cfg.OsInterruptNestingDepth >= OS_INTERRUPT_NESTING_DEPTH_LEVEL)
    OsKernelError(E_OS_KERNEL_PANIC);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsDecNestingDepthLevel(void)
{
  /* called by the OS with interrupt disabled, no need to lock the internal resource */
  if(0 == OsGetSysPrimaskReg())
    OsKernelError(E_OS_ENABLEDINT);

  OCB_Cfg.OsInterruptNestingDepth--;

  if(OCB_Cfg.OsInterruptNestingDepth >= OS_INTERRUPT_NESTING_DEPTH_LEVEL)
    OsKernelError(E_OS_KERNEL_PANIC);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
uint32 osGetIntNestingLevel(void)
{
  uint32 osInterruptNestingDepth = 0;

  /* might or might not be called durring interrupt nesting */

  osSaveAndDisableIntState();
  osInterruptNestingDepth = OCB_Cfg.OsInterruptNestingDepth;
  osRestoreSavedIntState();

  return osInterruptNestingDepth;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osDisableIntNesting(void)
{
  DISABLE_INTERRUPTS();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osEnableIntNesting(void)
{
  ENABLE_INTERRUPTS();
}
