/******************************************************************************************
  Filename    : SysTickTimer.c
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : System timer driver implementation
  
******************************************************************************************/

#include "SysTickTimer.h"

//=========================================================================================
// Functions
//=========================================================================================

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void SysTickTimer_Init(void)
{
  pSTK_CTRL->u32Register     = 0;
  pSTK_VAL->u32Register      = 0;
  pSTK_CTRL->bits.u1CLOCKSRC = SYS_TICK_CLKSRC_PROCESSOR_CLOCK;
  pSTK_CTRL->bits.u1TICKINT  = SYS_TICK_ENABLE_INT;
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
void SysTickTimer_Start(uint32 timeout)
{
  pSTK_LOAD->u32Register   = timeout;
  pSTK_CTRL->bits.u1ENABLE = SYS_TICK_ENABLE_TIMER;
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
void SysTickTimer_Reload(uint32 timeout)
{
  pSTK_LOAD->u32Register   = timeout;
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
void SysTickTimer_Stop(void)
{
  pSTK_CTRL->bits.u1ENABLE = 0U;
}