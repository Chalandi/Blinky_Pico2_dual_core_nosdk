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
  return((uint32_t)(riscv_read_csr(RVCSR_MCAUSE_OFFSET) >> 31) == 0ul ? FALSE : TRUE);
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
void osSetInterruptPriorityMask(uint32 level) /*osSetInterruptPriorityMask*/
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
uint32 osGetInterruptPriorityMask(void) /*osGetInterruptPriorityMask*/
{
  //return(PFIC->ITHRESDR.reg >> 4);
  return 0;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsRunCat2Isr
///
/// \descr  This function is the entry point of all category 2 interrupts
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
  OsHwPltfmSavedIntState = riscv_read_clear_csr(RVCSR_MSTATUS_OFFSET, RVCSR_MSTATUS_MIE_BITS);
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
  riscv_write_csr(RVCSR_MSTATUS_OFFSET, OsHwPltfmSavedIntState);
}
