// *****************************************************************************
// Filename    : OsHwPltfm.h
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

#ifndef __HARDWARE_PLATFORM_H__
#define __HARDWARE_PLATFORM_H__

#include"Platform_Types.h"
#include"OsAsm.h"

#define OS_GEN_NOT
#include"OsGenCfg.h"
#undef  OS_GEN_NOT

#define SCB_ICSR 0xE000ED04UL
#define SET_PENDSV()         (*(volatile uint32*)(SCB_ICSR)) |= 1UL<<28
#define CLEAR_PENDSV()       (*(volatile uint32*)(SCB_ICSR)) &= ~(1UL<<28)
#define osDispatch()         SET_PENDSV(); __asm("DSB"); __asm("NOP")

#define ENABLE_INTERRUPTS()       __asm("CPSIE I")
#define DISABLE_INTERRUPTS()      __asm("CPSID I")

#define GET_ICSR_VECTACTIVE()   ((*(volatile uint32*)(SCB_ICSR)) & (uint32)0x1FUL)

#define NVIC_ISERx ((volatile uint32 *)(0xE000E100UL))
#define NVIC_IPRx  ((volatile uint8 *) (0xE000E400UL))
#define SCB_SHPRx  ((volatile uint8 *) (0xE000ED18UL))
#define NVIC_ISPRx ((volatile uint8 *) (0xE000E200UL))

//=========================================================================================
// SYSTICK
//=========================================================================================
typedef union
{
 struct
 {
  unsigned long u1ENABLE : 1;
  unsigned long u1TICKINT : 1;
  unsigned long u1CLOCKSRC : 1;
  unsigned long : 13;
  unsigned long u1COUNTFLAG : 1;
  unsigned long : 15;
 }bits;

 unsigned long u32Register;

}stStkCtrl;

typedef union
{
 struct
 {
  unsigned long u24RELOAD : 24;
  unsigned long : 8;
 }bits;

 unsigned long u32Register;

}stStkLoad;

typedef union
{
 struct
 {
  unsigned long u24CURRENT : 24;
  unsigned long : 8;
 }bits;

 unsigned long u32Register;

}stStkVal;

typedef union
{
 struct
 {
  unsigned long u24TENMS : 24;
  unsigned long : 6;
  unsigned long u1SKEW : 1;
  unsigned long u1NOREF : 1;
 }bits;

 unsigned long u32Register;

}stStkCalib;


#define SYS_TICK_BASE_REG (0xE000E010UL)

#define pSTK_CTRL   ((volatile stStkCtrl* const) (SYS_TICK_BASE_REG + 0x00))
#define pSTK_LOAD   ((volatile stStkLoad* const) (SYS_TICK_BASE_REG + 0x04))
#define pSTK_VAL    ((volatile stStkVal* const)  (SYS_TICK_BASE_REG + 0x08))
#define pSTK_CALIB  ((volatile stStkCalib* const)(SYS_TICK_BASE_REG + 0x0C))

#define AHB_FREQ_MHZ      225U
#define OS_SYS_TICK_MS(x)    ((unsigned long)(AHB_FREQ_MHZ * x * 1000UL) - 1UL)
#define OS_SYS_TICK_US(x)    ((unsigned long)(AHB_FREQ_MHZ * x) - 1UL)

#define SYS_TICK_CLKSRC_AHB          1U
#define SYS_TICK_CLKSRC_AHB_DIV_8    0U
#define SYS_TICK_ENABLE_INT          1U
#define SYS_TICK_ENABLE_TIMER        1U

uint32 osGetPMR(void);
void   osSetPMR(uint32 level);
uint32 OsGetEIIC(void);
void   Ostm_Start(void);
void   Ostm_Init(void);
#endif
