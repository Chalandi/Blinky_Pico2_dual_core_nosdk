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
// Defines
//------------------------------------------------------------------------------------------------------------------
#define OS_INTERRUPT_NESTED_API_CALL_MARKER    (1ul << 31)

//------------------------------------------------------------------------------------------------------------------
/// \brief  osRunCat2Isr
///
/// \descr  This function is the entry point of all category 2 interrupts
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
 void osRunCat2Isr(void)
{
  const uint32 IntId        = osGetActiveInterruptVectorId();
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  if(OCB_Cfg[osActiveCore]->pInt->osIsrLookupTablePtr[IntId].type == NOT_NESTED)
  {
    /* disable the nesting of the current interrupt priority level but keep it enabled for category 1 interrupts */
    osSetInterruptPriorityMask(OCB_Cfg[osActiveCore]->pInt->osIntCat1LowestPrioLevel);
  }

  /* enable interrupt nesting before calling the ISR */
  osEnableIntNesting();

  /* call the appropriate interrupt service routine */
  OCB_Cfg[osActiveCore]->pInt->osIsrLookupTablePtr[IntId].IsrFunc();
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
void osIncNestingDepthLevel(void)
{
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  /* called by the OS with interrupt disabled, no need to lock the internal resource */
  if(0 == osIsInterruptDisabled())
    osKernelError(E_OS_ENABLEDINT);

  OCB_Cfg[osActiveCore]->OsInterruptNestingDepth++;

  if(OCB_Cfg[osActiveCore]->OsInterruptNestingDepth >= OS_INTERRUPT_NESTING_DEPTH_LEVEL)
    osKernelError(E_OS_KERNEL_PANIC);
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
void osDecNestingDepthLevel(void)
{
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  /* called by the OS with interrupt disabled, no need to lock the internal resource */
  if(0 == osIsInterruptDisabled())
    osKernelError(E_OS_ENABLEDINT);

  OCB_Cfg[osActiveCore]->OsInterruptNestingDepth--;

  if(OCB_Cfg[osActiveCore]->OsInterruptNestingDepth >= OS_INTERRUPT_NESTING_DEPTH_LEVEL)
    osKernelError(E_OS_KERNEL_PANIC);
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
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());
  uint32 osInterruptNestingDepth = 0;

  /* might or might not be called durring interrupt nesting */

  OS_SuspendAllInterrupts();
  osInterruptNestingDepth = OCB_Cfg[osActiveCore]->OsInterruptNestingDepth;
  OS_ResumeAllInterrupts();

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

//------------------------------------------------------------------------------------------------------------------
/// \brief  osIsCat2IntContext
///
/// \descr  This function checks if the cpu is in category 2 interrupt context or not.
///
/// \param  void
///
/// \return boolean: TRUE -> Category 2 interrupt context, FALSE -> none category 2 interrupt context
//------------------------------------------------------------------------------------------------------------------
boolean osIsCat2IntContext(void)
{
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());
  return((boolean)OCB_Cfg[osActiveCore]->OsCat2InterruptLevel);
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
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  /* check for nested call */
  if((OCB_Cfg[osActiveCore]->OsInterruptSavedGlobalMask & OS_INTERRUPT_NESTED_API_CALL_MARKER) != 0)
  {
    /* susspend is called before calling Resume first */
    DISABLE_INTERRUPTS();
    for(;;);
  }
  else
  {
    /* Get the global mask prio */
    OCB_Cfg[osActiveCore]->OsInterruptSavedGlobalMask = (osGetInterruptGlobalMask() | OS_INTERRUPT_NESTED_API_CALL_MARKER);
  }

  /* Disable all interrupts */
  DISABLE_INTERRUPTS();
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
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  if((OCB_Cfg[osActiveCore]->OsInterruptSavedGlobalMask & OS_INTERRUPT_NESTED_API_CALL_MARKER) == 0)
  {
    /* Resume is called without calling suspend first */
    DISABLE_INTERRUPTS();
    for(;;);
  }
  else
  {
    OCB_Cfg[osActiveCore]->OsInterruptSavedGlobalMask &= ~(OS_INTERRUPT_NESTED_API_CALL_MARKER); 
  }

  if(OCB_Cfg[osActiveCore]->OsInterruptSavedGlobalMask)
  {
    ENABLE_INTERRUPTS();
  }
  else
  {
    DISABLE_INTERRUPTS();
  }
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
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  /* check for nested call */
  if((OCB_Cfg[osActiveCore]->OsInterruptSavedPrioLevel & OS_INTERRUPT_NESTED_API_CALL_MARKER) != 0)
  {
    /* OS_SuspendOSInterrupts nested a previous OS_SuspendOSInterrupts call */
    DISABLE_INTERRUPTS();
    for(;;);
  }
  else
  {
    /* Get the active interrupt priority level */
    OCB_Cfg[osActiveCore]->OsInterruptSavedPrioLevel = (osGetInterruptPriorityMask() | OS_INTERRUPT_NESTED_API_CALL_MARKER);
  }

  /* Disable OS interrupts */
  osSetInterruptPriorityMask(OCB_Cfg[osActiveCore]->pInt->osIntCat1LowestPrioLevel);
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
  const uint32 osActiveCore = osGetLogicalCoreId(osGetCoreId());

  if((OCB_Cfg[osActiveCore]->OsInterruptSavedPrioLevel & OS_INTERRUPT_NESTED_API_CALL_MARKER) == 0)
  {
    /* OS_ResumeOSInterrupts is called without calling OS_SuspendOSInterrupts first */
    DISABLE_INTERRUPTS();
    for(;;);
  }
  else
  {
    OCB_Cfg[osActiveCore]->OsInterruptSavedPrioLevel &= ~(OS_INTERRUPT_NESTED_API_CALL_MARKER); 
  }

  /* Restore the global mask prio */
  osSetInterruptPriorityMask(OCB_Cfg[osActiveCore]->OsInterruptSavedPrioLevel);
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
  osKernelError(E_OS_DISABLEDINT);
  for(;;);
}
