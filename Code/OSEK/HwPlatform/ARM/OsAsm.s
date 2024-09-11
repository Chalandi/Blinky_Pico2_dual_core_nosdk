/******************************************************************************************
  Filename    : OsAsm.s

  Core        : ARM Cortex®-M

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 26.10.2020

  Description : Context switch and ISR category 2 wrapper

******************************************************************************************/

.file "OsAsm.s"
.syntax unified

//-----------------------------------------------------------------------------------------------------------------
// \brief  OsDispatcher
//
// \descr  Context switcher
//
// \param  void
//
// \return void
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsDispatcher
.type   OsDispatcher, % function
.extern OS_Dispatcher

OsDispatcher:

  cpsid i
  push {r4 - r11, lr}
  tst lr, #0x10
  it eq
  vpusheq {S16-S31}
  mov r0,r13
  bl.w OS_Dispatcher
  mov r13,r0
  pop {r4 - r11, lr}
  tst lr, #0x10
  it eq
  vpopeq {S16-S31}
  cpsie i
  isb
  bx lr

// ----------------------------------------------------------------------------------------------------------------
// \brief  OsCat2IsrWrapper
// 
// \descr  Wrapper for all category 2 interrupts
// 
// \param  void
// 
// \return void
// ----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsCat2IsrWrapper
.type   OsCat2IsrWrapper, % function
.extern OsStoreStackPointer
.extern OsRunCat2Isr
.extern OsGetSavedStackPointer
.extern OsIntCallDispatch

OsCat2IsrWrapper:

  cpsid i
  push {r4 - r11, lr}
  tst lr, #0x10
  it eq
  vpusheq {S16-S31}
  mov r0,r13
  bl.w OsStoreStackPointer
  bl.w OsRunCat2Isr
  bl.w OsGetSavedStackPointer
  bl.w OsIntCallDispatch
  mov r13,r0
  pop {r4 - r11, lr}
  tst lr, #0x10
  it eq
  vpopeq {S16-S31}
  cpsie i
  isb
  bx lr

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsStartNewTask (OsStartNewTask(uint32 StackFramePtr, pFunc TaskFuncPtr))
///
/// \descr  This function start an OSEK Task for the 1st execution
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsStartNewTask
.type   OsStartNewTask, % function
.extern osErrTaskExitWithoutTerminate

OsStartNewTask:
  mov sp,r0
  movw r0, #0
  movt r0, #0x0100
  push {r0}
  orr r1, r1, #1
  push {r1}
  ldr r1, =osErrTaskExitWithoutTerminate
  push {r1}
  mov r0, #0
  push {r0}
  push {r0}
  push {r0}
  push {r0}
  push {r0}
  cpsie i
  movw r0, #0xFFF9
  movt r0, #0xFFFF
  bx r0

//-----------------------------------------------------------------------------------------------------------------
// \brief  OsGetCurrentSP : void OsGetCurrentSP(unsigned int* CurrentSpPtr)
//
// \descr  Get the current stack pointer register value
//
// \param  unsigned int* CurrentSpPtr (out): Current stack pointer register value
//
// \return void
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsGetCurrentSP
.type   OsGetCurrentSP, % function

OsGetCurrentSP:

  str r13,[r0]
  dsb
  bx lr

//-----------------------------------------------------------------------------------------------------------------
// \brief  OsGetPSR : void OsGetPSR(unsigned int* CurrentPsr)
//
// \descr  Get the program status register value
//
// \param  unsigned int* CurrentPsr (out): Current program status register value
//
// \return void
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsGetPSR
.type   OsGetPSR, % function

OsGetPSR:

  mrs r1, xpsr
  isb
  str r1,[r0]
  dsb
  bx lr

//-----------------------------------------------------------------------------------------------------------------
// \brief  OsSetSysCtrlReg : void OsSetSysCtrlReg(unsigned int CtrlRegValue)
//
// \descr  set the system CONTROL register
//
// \param  unsigned int CtrlRegValue
//
// \return void
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsSetSysCtrlReg
.type   OsSetSysCtrlReg, % function

OsSetSysCtrlReg:

 msr control, R0
 dsb
 bx lr

//-----------------------------------------------------------------------------------------------------------------
// \brief  OsGetSysCtrlReg : void OsGetSysCtrlReg(unsigned int* CtrlRegValue)
//
// \descr  get the system CONTROL register
//
// \param  unsigned int* CtrlRegValue
//
// \return void
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsGetSysCtrlReg
.type   OsGetSysCtrlReg, % function

OsGetSysCtrlReg:

 mrs r1, control
 isb
 str r1,[r0]
 dsb
 bx lr

 //-----------------------------------------------------------------------------------------------------------------
// \brief  OsSetSysBasepriReg : void OsSetSysBasepriReg(unsigned int BasepriRegValue)
//
// \descr  set the system basepri register
//
// \param  unsigned int BasepriRegValue
//
// \return void
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsSetSysBasepriReg
.type   OsSetSysBasepriReg, % function

OsSetSysBasepriReg:

 msr basepri, R0
 dsb
 bx lr

//-----------------------------------------------------------------------------------------------------------------
// \brief  OsGetSysBasepriReg : void OsGetSysBasepriReg(unsigned int* BasepriRegValue)
//
// \descr  get the system basepri register
//
// \param  unsigned int* BasepriRegValue
//
// \return void
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsGetSysBasepriReg
.type   OsGetSysBasepriReg, % function

OsGetSysBasepriReg:

 mrs r1, basepri
 isb
 str r1,[r0]
 dsb
 bx lr


 

//-----------------------------------------------------------------------------------------------------------------
// \brief  OsHwGetInterruptPrioBits : uint32 OsHwGetInterruptPrioBits(void)
//
// \descr  get the number of prio bit
//
// \param  void
//
// \return number of implemented interrupt prio bit in the NVIC
//-----------------------------------------------------------------------------------------------------------------
.thumb_func
.section ".text"
.align 4
.globl  OsHwGetInterruptPrioBits
.type OsHwGetInterruptPrioBits, %function

OsHwGetInterruptPrioBits:
                 movw r0, 0xE400
                 movt r0, 0xE000
                 mov  r1, #0xFF
                 str r1,[r0]
                 dsb
                 ldr r1,[r0]
                 dsb
                 mov r2, #0xFF
                 eor r1, r2
                 clz r2,r1
                 mov r0, #32
                 sub r0, r0, r2
                 bx lr


