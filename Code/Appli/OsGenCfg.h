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
      OS_RESOURCE_DEF(RES_SCHEDULER, RES_SCHEDULER_PRIO, { 1,1 })
    OS_RESOURCE_END

  
  //=============================================================================
  //  EI Interrupts Configuration
  //=============================================================================

  OS_INTERRUPT_BEGIN
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   0  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   1  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   2  Non maskable Interrupt  cannot be stopped or preempted     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   3  Exception interrupt                                        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   4  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   5  Callback interrupt in machine mode                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   6  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   7  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   8  Callback interrupt in user mode                            */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*   9  Breakpoint callback interrupt                              */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  10  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  11  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(SysTickTimer, 15, NESTED)  /*  12  System Tick Timer                                          */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  13  Reserved                                                   */
    OS_INTERRUPT_CATx_DEF(OsDispatchHandler, 15, NESTED)  /*  14  Software interrupt                                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  15  Reserved                                                   */
    OS_INTERRUPT_CAT2_DEF(WindowWatchdogInt, 2, NOT_NESTED)  /*  16  Window Watchdog interrupt                                  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  17  PVD through EXTI line detection interrupt                  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  18  Tamper interrupt                                           */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  19  RTC global interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  20  Flash global interrupt                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  21  RCC global interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  22  EXTI Line0 interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  23  EXTI Line1 interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  24  EXTI Line2 interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  25  EXTI Line3 interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  26  EXTI Line4 interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  27  DMA1 Channel1 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  28  DMA1 Channel2 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  29  DMA1 Channel3 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  30  DMA1 Channel4 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  31  DMA1 Channel5 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  32  DMA1 Channel6 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  33  DMA1 Channel7 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  34  ADC global interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  35  CAN1 TX interrupts                                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  36  CAN1 RX0 interrupts                                        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  37  CAN1 RX1 interrupt                                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  38  CAN1 SCE interrupt                                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  39  EXTI Line[9:5] interrupts                                  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  40  TIM1 Break interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  41  TIM1 Update interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  42  TIM1 Trigger and Commutation interrupts                    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  43  TIM1 Capture Compare interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  44  TIM2 global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  45  TIM3 global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  46  TIM4 global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  47  I2C1 event interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  48  I2C1 error interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  49  I2C2 event interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  50  I2C2 error interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  51  SPI1 global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  52  SPI2 global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  53  USART1 global interrupt                                    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  54  USART2 global interrupt                                    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  55  USART3 global interrupt                                    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  56  EXTI Line[15:10] interrupts                                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  57  RTC Alarms through EXTI line interrupt                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  58  USB Device WakeUp from suspend through EXTI Line Interrupt */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  59  TIM8 Break interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  60  TIM8 Update interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  61  TIM8 Trigger and Commutation interrupts                    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  62  TIM8 Capture Compare interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  63  RNG interrupt                                              */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  64  FSMC global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  65  SDIO global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  66  TIM5 global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  67  SPI3 global interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  68  UART4 global interrupt                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  69  UART5 global interrupt                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  70  TIM6 Basic interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  71  TIM8 Basic interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  72  DMA2 Channel1 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  73  DMA2 Channel2 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  74  DMA2 Channel3 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  75  DMA2 Channel4 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  76  DMA2 Channel5 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  77  Ethernet global interrupt                                  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  78  Ethernet Wakeup through EXTI line interrupt                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  79  CAN2 TX interrupts                                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  80  CAN2 RX0 interrupts                                        */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  81  CAN2 RX1 interrupt                                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  82  CAN2 SCE interrupt                                         */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  83  OTG_FS                                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  84  USBHSWakeup                                                */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  85  USBHS                                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  86  DVP global Interrupt interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  87  UART6 global interrupt                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  88  UART7 global interrupt                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  89  UART8 global interrupt                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  90  TIM9 Break interrupt                                       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  91  TIM9 Update interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  92  TIM9 Trigger and Commutation interrupts                    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  93  TIM9 Capture Compare interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  94  TIM10 Break interrupt                                      */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  95  TIM10 Update interrupt                                     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  96  TIM10 Trigger and Commutation interrupts                   */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  97  TIM10 Capture Compare interrupt                            */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  98  DMA2 Channel6 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /*  99  DMA2 Channel7 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* 100  DMA2 Channel8 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* 101  DMA2 Channel9 global interrupt                             */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* 102  DMA2 Channel10 global interrupt                            */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* 103  DMA2 Channel11 global interrupt                            */
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
  #define OS_FE_INTERRUPT_ENABLED           0
  #define OS_INTERRUPT_ENABLED              1

  //=============================================================================
  //  Clock Configuration
  //=============================================================================
  #define OS_SYS_TICK_US_VAL        1000U

  //=============================================================================
  //  Interrupt Mask Configuration
  //=============================================================================
  #define OS_INT_CAT1_LOWEST_PRIO_LEVEL       1UL


OS_CONFIG_END
