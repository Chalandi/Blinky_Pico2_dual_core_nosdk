// ***************************************************************************************
// Filename    : util.s
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 04.09.2024
// 
// Description : low-level utility functions
// 
// ***************************************************************************************

.file "util.s"

.syntax unified

.cpu cortex-m33

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.thumb_func
.section ".text", "ax"
.align 8
.globl BlockingDelay
.type  BlockingDelay, % function


BlockingDelay:
                      subs r0, r0, #1
                      bne BlockingDelay
                      bx lr

.size BlockingDelay, .-BlockingDelay

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.thumb_func
.section ".text", "ax"
.align 8
.globl arch_spin_lock
.type  arch_spin_lock, % function


arch_spin_lock:
                mov     r1, #1
.L_loop:
                ldaex   r2, [r0]
                cmp     r2, #0
                bne     .L_loop
                strex   r2, r1, [r0]
                cmp     r2, #0
                bne     .L_loop
                dmb
                bx      lr


.size arch_spin_lock, .-arch_spin_lock

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.thumb_func
.section ".text", "ax"
.align 8
.globl arch_spin_unlock
.type  arch_spin_unlock,  % function


arch_spin_unlock:
                  dmb
                  mov     r1, #0
                  stl     r1, [r0]
                  bx      lr


.size arch_spin_unlock, .-arch_spin_unlock

