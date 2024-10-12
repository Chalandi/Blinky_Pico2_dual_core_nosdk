/******************************************************************************************
  Filename    : main.c
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : Application main function
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include "Platform_Types.h"
#include "Cpu.h"
#include "Gpio.h"
#include "OsAPIs.h"

//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// Prototypes
//=============================================================================
void main_Core0(void);
void main_Core1(void);
void BlockingDelay(uint32 delay);

//=============================================================================
// Globals
//=============================================================================
#ifdef DEBUG
  volatile boolean boHaltCore0 = TRUE;
  volatile boolean boHaltCore1 = TRUE;
#endif

//-----------------------------------------------------------------------------------------
/// \brief  main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
int main(void)
{
  /* Run the main function of the core 0, it will start the core 1 */
  main_Core0();

  /* Synchronize with core 1 */
  RP2350_MulticoreSync((uint32_t)HW_PER_SIO->CPUID.reg);

  /* start the OS */
  OS_StartOS(APP_MODE_DEFAULT);
}

//-----------------------------------------------------------------------------------------
/// \brief  main_Core0 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void main_Core0(void)
{
#ifdef DEBUG
  while(boHaltCore0);
#endif

#ifdef CORE_FAMILY_ARM
  /* Disable interrupts on core 0 */
  __asm volatile("CPSID i");
#endif

  /* Output disable on pin 25 */
  LED_GREEN_CFG();
  LED_RED_CFG();

  /* Start the Core 1 and turn on the led to be sure that we passed successfully the core 1 initiaization */
  if(TRUE == RP2350_StartCore1())
  {
#ifndef RP2350_TINY_BOARD
    LED_GREEN_ON();
#else
    LED_GREEN_OFF();
#endif
  }
  else
  {
    /* Loop forever in case of error */
    while(1)
    {
      __asm volatile("NOP");
    }
  }

}

//-----------------------------------------------------------------------------------------
/// \brief  main_Core1 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
  volatile uint64_t* pMTIMECMP = (volatile uint64_t*)&(HW_PER_SIO->MTIMECMP.reg);
  volatile uint64_t* pMTIME    = (volatile uint64_t*)&(HW_PER_SIO->MTIME.reg);

void main_Core1(void)
{
#ifdef DEBUG
  while(boHaltCore1);
#endif

  /* Note: Core 1 is started with interrupt enabled by the BootRom */

  /* Clear the stiky bits of the FIFO_ST on core 1 */
  HW_PER_SIO->FIFO_ST.reg = 0xFFu;

#ifdef CORE_FAMILY_ARM

  /* Setting EXTEXCLALL allows external exclusive operations to be used in a configuration with no MPU.
  This is because the default memory map does not include any shareable Normal memory.*/
  SCnSCB->ACTLR |= (1ul<<29);

  __asm volatile("DSB");

  /* Clear all pending interrupts on core 1 */
  NVIC->ICPR[0] = (uint32)-1;

  /* enable FPU */
  *(volatile unsigned int*)0xE000ED8C |= ((1ul<<11) | (1ul<<10));
  *(volatile unsigned int*)0xE000ED88 |= ((3ul<<22) | (3ul<<20));

#endif

  /* Synchronize with core 0 */
  RP2350_MulticoreSync((uint32_t)HW_PER_SIO->CPUID.reg);

  /* start the OS */
  //OS_StartOS(APP_MODE_DEFAULT);

  while(1)
  {
    __asm("nop");
  }
}
