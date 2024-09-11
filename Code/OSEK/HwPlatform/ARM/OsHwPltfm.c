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

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsGetEIIC
///
/// \descr  This function return the ISR number.
///
/// \param  void
///
/// \return uint32: ISR number
//------------------------------------------------------------------------------------------------------------------
uint32 OsGetEIIC(void)
{
  return(GET_ICSR_VECTACTIVE());
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
void Ostm_Init(void)
{
  pSTK_CTRL->u32Register = 0;
  pSTK_LOAD->bits.u24RELOAD = OS_SYS_TICK_MS(1);
  pSTK_VAL->u32Register = 0;
  pSTK_CTRL->bits.u1CLOCKSRC = SYS_TICK_CLKSRC_AHB_DIV_8;
  pSTK_CTRL->bits.u1TICKINT = SYS_TICK_ENABLE_INT;
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
void Ostm_Start(void)
{
  pSTK_CTRL->bits.u1ENABLE = SYS_TICK_ENABLE_TIMER;
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
  __attribute__((weak)) extern const Isr_t IsrLookupTable[];
  __attribute__((weak)) ISR(Undefined);

  uint32 IntPrioBit = OsHwGetInterruptPrioBits();

  for (uint32 InterruptIndex = 0; InterruptIndex < osNbrOfInterrupts; InterruptIndex++)
  {
    if (IsrLookupTable[InterruptIndex].IsrFunc != pISR(Undefined))
    {
      if((InterruptIndex == 4U) || (InterruptIndex == 5U)  || (InterruptIndex == 6U) || (InterruptIndex == 11U) || (InterruptIndex == 14U) || (InterruptIndex == 15U))
      {
        /* set the system handler priority level */
        SCB_SHPRx[InterruptIndex - 4U] = ((uint8)IsrLookupTable[InterruptIndex].Prio << (8U - IntPrioBit));
      }
      else if(InterruptIndex > 15U)
      {
        /* set the NVIC interrupt priority level */
        NVIC_IPRx[InterruptIndex - 16U] = ((uint8)IsrLookupTable[InterruptIndex].Prio << (8U - IntPrioBit));

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
void osSetPMR(uint32 level)
{
  uint32 IntPrioBit = OsHwGetInterruptPrioBits();
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
uint32 osGetPMR(void)
{
  uint32 level = 0;
  uint32 IntPrioBit = OsHwGetInterruptPrioBits();
  OsGetSysBasepriReg((uint32*)&level);
  return((level >> (8U - IntPrioBit)));
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
void osMaskNestedIntPrio(uint32 PrioLevel)
{
 /* mask the category2 under the current nested priority */
  uint32 IntPrioBit = OsHwGetInterruptPrioBits();
  OsSetSysBasepriReg((PrioLevel << (8U - IntPrioBit)));
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
void osMaskNonNestedIntPrio(uint32 PrioLevel)
{
  (void)PrioLevel;
  uint32 IntPrioBit = OsHwGetInterruptPrioBits();
  /* mask the category2 non nested interrupts */
  OsSetSysBasepriReg((OS_CAT1_PRIO_MASK << (8U - IntPrioBit)));
}

//------------------------------------------------------------------------------------------------------------------
///     STUBS
//------------------------------------------------------------------------------------------------------------------
void OsIsr_FeUndefinedFunc(void) {}


