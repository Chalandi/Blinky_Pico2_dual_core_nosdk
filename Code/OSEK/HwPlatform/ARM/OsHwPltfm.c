// *****************************************************************************
// Filename    : OsHwPltDep.c
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.12.2017
// 
// Description : Hardware Platform definition for ARM Cortex-M4
// 
// *****************************************************************************

#include"OsTypes.h"
#include"OsHwPltfm.h"
#include"OsInternal.h"
#include"OsTcb.h"

#define USE_OS_PRIO
uint32 osRemapOsPriorityValue(uint32 level, uint32 IntPrioBit);

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsInterruptContext
///
/// \descr  This function check the cpu mode (thread or interrupt).
///
/// \param  void
///
/// \return boolean: TRUE -> Cpu in interrupt context, FALSE -> Cpu not in interrupt context
//------------------------------------------------------------------------------------------------------------------
boolean OsIsInterruptContext(void)
{
  return((GET_ICSR_VECTACTIVE() == 0) ? FALSE : TRUE);
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void osHwTimerInit(void)
{
  SysTickTimer_Init();
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void osHwTimerStart(void)
{
  SysTickTimer_Start(SYS_TICK_MS(1));
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void osHwTimerReload(void)
{
  SysTickTimer_Reload(SYS_TICK_MS(1));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osInitInterrupts
///
/// \descr  Init the cat2 interrupts
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osInitInterrupts(void)
{
  __attribute__((weak)) extern const uint32 osNbrOfInterrupts;
  __attribute__((weak)) extern const OsInterruptConfigType IsrLookupTable[];
  __attribute__((weak)) ISR(Undefined);

  uint32 IntPrioBit = OsHwGetInterruptPrioBits();

  for (uint32 InterruptIndex = 0; InterruptIndex < osNbrOfInterrupts; InterruptIndex++)
  {
    if (IsrLookupTable[InterruptIndex].IsrFunc != pISR(Undefined))
    {
      if((InterruptIndex == 4U) || (InterruptIndex == 5U)  || (InterruptIndex == 6U) || (InterruptIndex == 11U) || (InterruptIndex == 14U) || (InterruptIndex == 15U))
      {
        /* set the system handler priority level */
        SCB_SHPRx[InterruptIndex - 4U] = ((uint8)osRemapOsPriorityValue(IsrLookupTable[InterruptIndex].Prio, IntPrioBit) << (8U - IntPrioBit));
      }
      else if(InterruptIndex > 15U)
      {
        /* set the NVIC interrupt priority level */
        NVIC_IPRx[InterruptIndex - 16U] = ((uint8)osRemapOsPriorityValue(IsrLookupTable[InterruptIndex].Prio, IntPrioBit) << (8U - IntPrioBit));

        /* enable the NVIC interrupt */
        NVIC_ISERx[(InterruptIndex - 16U) / 32U] = (1UL << ((InterruptIndex - 16U) % 32U));
      }
      else
      {
        /* priority non configurable */
      }
    }
  }
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
void osSetInterruptPriorityMask(uint32 level)
{
  uint32 IntPrioBit = OsHwGetInterruptPrioBits();

  level = osRemapOsPriorityValue(level, IntPrioBit);

  OsSetSysBasepriReg((level << (8U - IntPrioBit)));
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
uint32 osGetInterruptPriorityMask(void)
{
  uint32 level = 0;
  uint32 IntPrioBit = OsHwGetInterruptPrioBits();

  OsGetSysBasepriReg((uint32*)&level);
  level >>= (8U - IntPrioBit);

  return(osRemapOsPriorityValue(level, IntPrioBit));
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
uint32 osRemapOsPriorityValue(uint32 level, uint32 IntPrioBit)
{
#ifdef USE_OS_PRIO
  /* note: remap the level prio: ARM is using lower value for highest prio 
     contrary to the OS which uses lower value for lower prio */
  if(level > ((1ul << IntPrioBit) -1))
  {
    level = (1ul << IntPrioBit) - 1;
  }

  level = ((1ul << IntPrioBit) - 1) - level;
#endif
  return(level);
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
void osSaveAndDisableIntState(void)
{
}

void osRestoreSavedIntState(void)
{
}

#if 0
void OsRunCat2Isr(void)
{
  /* run ISR */
  CALL_ISR(SysTickTimer);
}
#endif
//------------------------------------------------------------------------------------------------------------------
/// \brief  osGetActiveInterruptVectorId
///
/// \descr  This function returns the id of the active interrupt vector.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
uint32 osGetActiveInterruptVectorId(void)
{
  return(GET_ICSR_VECTACTIVE());
}
