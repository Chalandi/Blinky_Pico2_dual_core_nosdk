// **********************************************************************************************************************
//                                                  OSEK OS Configuration                                                
// **********************************************************************************************************************

// **********************************************************************************************************************
// Filename        : osGenCfg.h
// 
// Author          : Chalandi Amine
//
// Owner           : Chalandi Amine
// 
// Date            : 24.01.2023
// 
// Description     : OS Configuration file
// 
// **********************************************************************************************************************

#include "OsGenMac.h"


//=============================================================================
// OS Configuration
//=============================================================================

OS_CONFIG_BEGIN

    OS_TASK_BEGIN
      OS_TASK_DEF(T1, 1, 1024, 1, OS_AUTOSTART, EXTENDED, FULL_PREEMPT)
      OS_TASK_DEF(T2, 5, 1024, 1, OS_AUTOSTART, EXTENDED, FULL_PREEMPT)
    OS_TASK_END
    
    OS_EVENT_BEGIN
      OS_EVENT_DEF(EVT_BLINK_BLUE_LED_FAST, (1UL << 0))
      OS_EVENT_DEF(EVT_BLINK_BLUE_LED_SLOW, (1UL << 1))
    OS_EVENT_END
    
    OS_ALARM_BEGIN
      OS_ALARM_DEF(ALARM_BLINK_BLUE_LED_FAST, ALARM_SET_EVENT, EVT_BLINK_BLUE_LED_FAST, T1, 0)
      OS_ALARM_DEF(ALARM_BLINK_BLUE_LED_SLOW, ALARM_SET_EVENT, EVT_BLINK_BLUE_LED_SLOW, T2, 0)
    OS_ALARM_END
    
    OS_RESOURCE_BEGIN
      OS_RESOURCE_DEF(RES_SCHEDULER, RES_SCHEDULER_PRIO, 7)
    OS_RESOURCE_END

  
  //=============================================================================
  //  EI Interrupts Configuration
  //=============================================================================

  OS_INTERRUPT_BEGIN
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* NMI                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* HardFault               */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SVCall                  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT1_DEF(OsDispatchHandler, 4, NESTED)  /* OsDispatchHandler       */
    OS_INTERRUPT_CAT2_DEF(SysTickTimer, 4, NESTED)  /* OsCat2IsrWrapper        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER0_IRQ_0_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER0_IRQ_1_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER0_IRQ_2_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER0_IRQ_3_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER1_IRQ_0_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER1_IRQ_1_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER1_IRQ_2_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TIMER1_IRQ_3_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PWM_IRQ_WRAP_0_IRQn     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PWM_IRQ_WRAP_1_IRQn     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* DMA_IRQ_0_IRQn          */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* DMA_IRQ_1_IRQn          */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* DMA_IRQ_2_IRQn          */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* DMA_IRQ_3_IRQn          */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* USBCTRL_IRQ_IRQn        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PIO0_IRQ_0_IRQn         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PIO0_IRQ_1_IRQn         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PIO1_IRQ_0_IRQn         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PIO1_IRQ_1_IRQn         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PIO2_IRQ_0_IRQn         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PIO2_IRQ_1_IRQn         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* IO_IRQ_BANK0_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* IO_IRQ_BANK0_NS_IRQn    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* IO_IRQ_QSPI_IRQn        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* IO_IRQ_QSPI_NS_IRQn     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SIO_IRQ_FIFO_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SIO_IRQ_BELL_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SIO_IRQ_FIFO_NS_IRQn    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SIO_IRQ_BELL_NS_IRQn    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SIO_IRQ_MTIMECMP_IRQn   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* CLOCKS_IRQ_IRQn         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SPI0_IRQ_IRQn           */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* SPI1_IRQ_IRQn           */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* UART0_IRQ_IRQn          */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* UART1_IRQ_IRQn          */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* ADC_IRQ_FIFO_IRQn       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* I2C0_IRQ_IRQn           */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* I2C1_IRQ_IRQn           */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* OTP_IRQ_IRQn            */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* TRNG_IRQ_IRQn           */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PLL_SYS_IRQ_IRQn        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* PLL_USB_IRQ_IRQn        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* POWMAN_IRQ_POW_IRQn     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* POWMAN_IRQ_TIMER_IRQn   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Reserved                */
  OS_INTERRUPT_END

  //=============================================================================
  //  Hooks Configuration
  //=============================================================================
  #define OS_STARTUPHOOK            0
  #define OS_ERRORHOOK              0
  #define OS_SHUTDOWNHOOK           0
  #define OS_PRETASKHOOK            0
  #define OS_POSTTASKHOOK           0

  //=============================================================================
  //  Interrupt Configuration
  //=============================================================================
  #define OS_INTERRUPT_VECTOR_ENABLED 

  //=============================================================================
  //  Clock Configuration
  //=============================================================================
  #define OS_SYS_TICK_US_VAL        1000U

  //=============================================================================
  //  Interrupt Mask Configuration
  //=============================================================================
  #define OS_INT_CAT1_LOWEST_PRIO_LEVEL       8UL


OS_CONFIG_END
