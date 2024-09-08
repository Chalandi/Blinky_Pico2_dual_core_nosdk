/******************************************************************************************
  Filename    : IntVect.c
  
  Core        : Hazard3 RISC-V
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.08.2024
  
  Description : Interrupt vector tables for Raspberry Pi Pico 2
  
******************************************************************************************/

#include "riscv.h"

//=============================================================================
// Types definition
//=============================================================================
typedef void (*InterruptHandler)(void);

__attribute__((interrupt)) void Isr_MachineExternalInterrupt(void);
void UndefinedHandler(void);
void UndefinedHandler(void) { for(;;); }

//=============================================================================
// Functions prototype
//=============================================================================
void _start_c0(void);
void _start_c1 (void) __attribute__((weak, alias("UndefinedHandler")));
void __CORE0_STACK_TOP(void);
void __CORE1_STACK_TOP(void);

/* Exception handler */
void Isr_InstructionAddressMisaligned (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_InstructionAccessFault       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_IllegalInstruction           (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_Breakpoint                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LoadAddressMisaligned        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LoadAccessFault              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_StoreAddressMisaligned       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_StoreAccessFault             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EnvironmentCallFromUmode     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EnvironmentCallFromMmode     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_MachineSoftwareInterrupt     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_MachineTimerInterrupt        (void) __attribute__((weak, alias("UndefinedHandler")));

/* Default peripheral interrupts handler */
void TIMER0_IRQ_0_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER0_IRQ_1_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER0_IRQ_2_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER0_IRQ_3_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_0_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_1_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_2_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_3_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void PWM_IRQ_WRAP_0_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void PWM_IRQ_WRAP_1_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_0_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_1_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_2_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_3_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void USBCTRL_IRQ_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void PIO0_IRQ_0_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO0_IRQ_1_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO1_IRQ_0_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO1_IRQ_1_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO2_IRQ_0_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO2_IRQ_1_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_BANK0_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_BANK0_NS_IRQn(void)  __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_QSPI_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_QSPI_NS_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_FIFO_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_BELL_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_FIFO_NS_IRQn(void)  __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_BELL_NS_IRQn(void)  __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_MTIMECMP_IRQn(void) __attribute__((weak, alias("UndefinedHandler")));
void CLOCKS_IRQ_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void SPI0_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void SPI1_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void UART0_IRQ_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void UART1_IRQ_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void ADC_IRQ_FIFO_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void I2C0_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void I2C1_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void OTP_IRQ_IRQn(void)          __attribute__((weak, alias("UndefinedHandler")));
void TRNG_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void PLL_SYS_IRQ_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void PLL_USB_IRQ_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void POWMAN_IRQ_POW_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void POWMAN_IRQ_TIMER_IRQn(void) __attribute__((weak, alias("UndefinedHandler")));

//=============================================================================
// Dummy Interrupt vector table for Core0 (to keep the startup code generic and supporting both ARM and RISC-V initialization from bootROM)
//=============================================================================
const InterruptHandler __attribute__((section(".intvect_c0"), aligned(4))) __INTVECT_Core0[2] =
{
    (InterruptHandler)&__CORE0_STACK_TOP,
    (InterruptHandler)&_start_c0
};

//=============================================================================
// Dummy Interrupt vector table Core1 (to keep the startup code generic and supporting both ARM and RISC-V initialization from bootROM)
//=============================================================================
const InterruptHandler __attribute__((section(".intvect_c1"), aligned(4))) __INTVECT_Core1[2] =
{
    (InterruptHandler)&__CORE1_STACK_TOP,
    (InterruptHandler)&_start_c1
};

//=====================================================================================================
// RISC-V Exception lookup table
//=====================================================================================================
const InterruptHandler __Exception_LookupTable[] =
{
    /* Core-Local Exceptions */
    (InterruptHandler)&Isr_InstructionAddressMisaligned,  /* 0  - Instruction address misaligned */
    (InterruptHandler)&Isr_InstructionAccessFault,        /* 1  - Instruction access fault       */
    (InterruptHandler)&Isr_IllegalInstruction,            /* 2  - Illegal instruction            */
    (InterruptHandler)&Isr_Breakpoint,                    /* 3  - Breakpoint                     */
    (InterruptHandler)&Isr_LoadAddressMisaligned,         /* 4  - Load address misaligned        */
    (InterruptHandler)&Isr_LoadAccessFault,               /* 5  - Load access fault              */
    (InterruptHandler)&Isr_StoreAddressMisaligned,        /* 6  - Store/AMO address misaligned   */
    (InterruptHandler)&Isr_StoreAccessFault,              /* 7  - Store/AMO access fault         */
    (InterruptHandler)&Isr_EnvironmentCallFromUmode,      /* 8  - Environment call from U-mode   */
    (InterruptHandler)&UndefinedHandler,                  /* 9  - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 10 - Reserved                       */
    (InterruptHandler)&Isr_EnvironmentCallFromMmode,      /* 11 - Environment call from M-mode   */
};

//=============================================================================
// RP2350 Peripheral interrupt table
//=============================================================================
const InterruptHandler __Interrupt_LookupTable[] =
{
    (InterruptHandler)&TIMER0_IRQ_0_IRQn,
    (InterruptHandler)&TIMER0_IRQ_1_IRQn,
    (InterruptHandler)&TIMER0_IRQ_2_IRQn,
    (InterruptHandler)&TIMER0_IRQ_3_IRQn,
    (InterruptHandler)&TIMER1_IRQ_0_IRQn,
    (InterruptHandler)&TIMER1_IRQ_1_IRQn,
    (InterruptHandler)&TIMER1_IRQ_2_IRQn,
    (InterruptHandler)&TIMER1_IRQ_3_IRQn,
    (InterruptHandler)&PWM_IRQ_WRAP_0_IRQn,
    (InterruptHandler)&PWM_IRQ_WRAP_1_IRQn,
    (InterruptHandler)&DMA_IRQ_0_IRQn,
    (InterruptHandler)&DMA_IRQ_1_IRQn,
    (InterruptHandler)&DMA_IRQ_2_IRQn,
    (InterruptHandler)&DMA_IRQ_3_IRQn,
    (InterruptHandler)&USBCTRL_IRQ_IRQn,
    (InterruptHandler)&PIO0_IRQ_0_IRQn,
    (InterruptHandler)&PIO0_IRQ_1_IRQn,
    (InterruptHandler)&PIO1_IRQ_0_IRQn,
    (InterruptHandler)&PIO1_IRQ_1_IRQn,
    (InterruptHandler)&PIO2_IRQ_0_IRQn,
    (InterruptHandler)&PIO2_IRQ_1_IRQn,
    (InterruptHandler)&IO_IRQ_BANK0_IRQn,
    (InterruptHandler)&IO_IRQ_BANK0_NS_IRQn,
    (InterruptHandler)&IO_IRQ_QSPI_IRQn,
    (InterruptHandler)&IO_IRQ_QSPI_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_FIFO_IRQn,
    (InterruptHandler)&SIO_IRQ_BELL_IRQn,
    (InterruptHandler)&SIO_IRQ_FIFO_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_BELL_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_MTIMECMP_IRQn,
    (InterruptHandler)&CLOCKS_IRQ_IRQn,
    (InterruptHandler)&SPI0_IRQ_IRQn,
    (InterruptHandler)&SPI1_IRQ_IRQn,
    (InterruptHandler)&UART0_IRQ_IRQn,
    (InterruptHandler)&UART1_IRQ_IRQn,
    (InterruptHandler)&ADC_IRQ_FIFO_IRQn,
    (InterruptHandler)&I2C0_IRQ_IRQn,
    (InterruptHandler)&I2C1_IRQ_IRQn,
    (InterruptHandler)&OTP_IRQ_IRQn,
    (InterruptHandler)&TRNG_IRQ_IRQn,
    (InterruptHandler)&PLL_SYS_IRQ_IRQn,
    (InterruptHandler)&PLL_USB_IRQ_IRQn,
    (InterruptHandler)&POWMAN_IRQ_POW_IRQn,
    (InterruptHandler)&POWMAN_IRQ_TIMER_IRQn,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0
 };

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void Isr_MachineExternalInterrupt(void)
{
  /* get the IRQ ID of the pending interrupt */
  const uint32_t IntId = (const uint32_t)(riscv_read_csr(RVCSR_MEINEXT_OFFSET) >> 2ul);

  if(IntId < 50ul)
  {
    /* call the appropriate interrupt service routine */
    __Interrupt_LookupTable[IntId]();
  }

}
