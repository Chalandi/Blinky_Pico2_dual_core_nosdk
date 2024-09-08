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
#include "SysTickTimer.h"

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

  /* endless loop on the core 0 */
  for(;;);

  /* never reached */
  return(0);
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
#ifdef CORE_FAMILY_ARM
  LED_GREEN_CFG();
  LED_GREEN_OFF();
#else
  LED_RED_CFG();
  LED_RED_OFF();
#endif

  /* Start the Core 1 and turn on the led to be sure that we passed successfully the core 1 initiaization */
  if(TRUE == RP2350_StartCore1())
  {
    LED_BLUE_CFG();
    LED_BLUE_OFF();
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
  __asm volatile("DSB");

  /* Clear all pending interrupts on core 1 */
  NVIC->ICPR[0] = (uint32)-1;

#endif

  /* Synchronize with core 0 */
  RP2350_MulticoreSync((uint32_t)HW_PER_SIO->CPUID.reg);


#ifdef CORE_FAMILY_RISC_V

  /* configure the machine timer for 1Hz interrupt window */
  #include "riscv.h"

  /* enable machine timer interrupt */
  riscv_set_csr(RVCSR_MIE_OFFSET, 0x80ul);

  /* enable global interrupt */
  riscv_set_csr(RVCSR_MSTATUS_OFFSET, 0x08ul);

  /* configure machine timer to use 150 MHz */
  HW_PER_SIO->MTIME_CTRL.bit.FULLSPEED = 1;

  /* set next timeout (machine timer is enabled by default) */
  *pMTIMECMP = *pMTIME + 150000000ul; //1s

  LED_GREEN_CFG();
#endif

  while(1)
  {
#ifdef CORE_FAMILY_ARM
    #define DELAY 10000000
    LED_GREEN_TOGGLE();
#else
    #define DELAY 10000000
#endif

    BlockingDelay(DELAY);
  }
}


#ifdef CORE_FAMILY_RISC_V
__attribute__((interrupt)) void Isr_MachineTimerInterrupt(void);

void Isr_MachineTimerInterrupt(void)
{
  *pMTIMECMP = *pMTIME + 150000000ul;

  LED_RED_TOGGLE();
}

#endif

