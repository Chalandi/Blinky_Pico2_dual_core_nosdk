// *****************************************************************************
// Filename    : OsHwPltfm.c
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 18.01.2023
// 
// Description : Hardware platform implementation for WCH RISC-V CH32V307
// 
// *****************************************************************************

//=========================================================================================
// Includes
//=========================================================================================
#include"OsTypes.h"
#include"OsHwPltfm.h"
#include"OsInternal.h"
#include"OsTcb.h"

//=========================================================================================
// Functions Prototype
//=========================================================================================
ISR(SysTickTimer);

//=========================================================================================
// Globals
//=========================================================================================
volatile uint32 OsHwPltfmSavedIntState = 0;

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsInterruptContext
///
/// \descr  This function check the cpu mode (thread or interrupt).
///
/// \param  void
///
/// \return boolean: TRUE -> Cpu is in interrupt context, FALSE -> Cpu is not in interrupt context
//------------------------------------------------------------------------------------------------------------------
boolean OsIsInterruptContext(void)
{
  //return((boolean)(PFIC->GISR.bit.GACTSTA));
  return 0;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osRestoreSavedIntState
///
/// \descr  This function return the interrupt nesting level status
///
/// \param  void
///
/// \return uint32 current nesting level
//------------------------------------------------------------------------------------------------------------------
uint32 osGetHwIntNestingLevel(void)
{
/*
  uint8 u8CurrentNestingLevel = PFIC->GISR.bit.NESTSTA;

  switch(u8CurrentNestingLevel)
  {
    case 0x03: u8CurrentNestingLevel = 2u; break;
    case 0x07: u8CurrentNestingLevel = 3u; break;
    case 0x0F: u8CurrentNestingLevel = 4u; break;
    case 0x1F: u8CurrentNestingLevel = 5u; break;
    case 0x3F: u8CurrentNestingLevel = 6u; break;
    case 0x7F: u8CurrentNestingLevel = 7u; break;
    case 0xFF: u8CurrentNestingLevel = 8u; break;
    default:
    break;
  }

  return((uint32)(u8CurrentNestingLevel));
*/
return 1;
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
  /* enable machine timer interrupt */
  riscv_set_csr(RVCSR_MIE_OFFSET, RVCSR_MIE_MTIE_BITS);

  /* configure machine timer to use 150 MHz */
  HW_PER_SIO->MTIME_CTRL.bit.FULLSPEED = 1;
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
  volatile uint64_t* pMTIMECMP = (volatile uint64_t*)&(HW_PER_SIO->MTIMECMP.reg);
  volatile uint64_t* pMTIME    = (volatile uint64_t*)&(HW_PER_SIO->MTIME.reg);
  /* set next timeout (machine timer is enabled by default) */
  *pMTIMECMP = *pMTIME + 150000ul; //1ms
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
  volatile uint64_t* pMTIMECMP = (volatile uint64_t*)&(HW_PER_SIO->MTIMECMP.reg);
  volatile uint64_t* pMTIME    = (volatile uint64_t*)&(HW_PER_SIO->MTIME.reg);
  /* set next timeout (machine timer is enabled by default) */
  *pMTIMECMP = *pMTIME + 150000ul; //1ms
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
#if 0
  uint32 u32IntRegOffset    = 0;
  uint32 u32IntBitPosition  = 0;
  
  OsSetIntVectTableAddress((uint32*)&osIntVectTable);

  for(uint32 IntId = 0; IntId <= 103; IntId++)
  {
    u32IntRegOffset    = (uint32)(IntId / 32u);
    u32IntBitPosition  = (uint32)(IntId - (32u*u32IntRegOffset));
    
    if(IsrLookupTable[IntId].IsrFunc != pISR(Undefined))
    {
      /* configure the interrupt's priority */
      *((volatile uint8*)((uint32)(&PFIC->IPRIOR0) + IntId)) = (uint8)((IsrLookupTable[IntId].Prio) << 4u);

      /* enable the interrupt */
      *((volatile uint32*)((uint32)(&PFIC->IENR1.reg) + sizeof(uint32)*u32IntRegOffset)) |= (uint32)(1ul << u32IntBitPosition);
    }
    else
    {
      /* disable the interrupt */
      *((volatile uint32*)((&PFIC->IRER1.reg) + sizeof(uint32)*u32IntRegOffset)) |= (uint32)(1ul << u32IntBitPosition);
    }
  }

  /* configure the interrupt system control
    8 nested levels, 3 preemption bits, no Hardware stack */
  osSetINTSYSCR(0x0E);
#endif
}

ISR(WindowWatchdogInt);
ISR(WindowWatchdogInt)
{
 __asm("nop");
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
  (void)level;
  //PFIC->ITHRESDR.reg = (uint32)level << 4;
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
  //return(PFIC->ITHRESDR.reg >> 4);
  return 0;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsRunCat2Isr
///
/// \descr  This function is the entry point of all category 2 interrupts (PLIC).
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsRunCat2Isr(void)
{
  CALL_ISR(SysTickTimer);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsCatchAllCpuExceptions
///
/// \descr  This function handle all CPU exceptions.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsCatchAllCpuExceptions(void)
{
  DISABLE_INTERRUPTS();
  for(;;);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osSaveAndDisableIntState
///
/// \descr  This function save and disable the CPU interrupt state.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osSaveAndDisableIntState(void)
{
  //OsHwPltfmSavedIntState = csr_read_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osRestoreSavedIntState
///
/// \descr  This function restore the saved CPU interrupt state.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osRestoreSavedIntState(void)
{
  //csr_write_mstatus(OsHwPltfmSavedIntState);
}
