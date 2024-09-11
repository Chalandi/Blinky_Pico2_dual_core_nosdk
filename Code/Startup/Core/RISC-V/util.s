/******************************************************************************************
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
******************************************************************************************/

.file "util.s"

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl BlockingDelay
.type  BlockingDelay, @function


BlockingDelay:
               addi a0, a0, -1 
               bnez a0, BlockingDelay
               ret


.size BlockingDelay, .-BlockingDelay

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl arch_spin_lock
.type  arch_spin_lock, @function


arch_spin_lock:  lr.w a1, (a0)
                 bne zero, a1, arch_spin_lock
                 add a1, zero, 1
                 sc.w t0, a1, (a0)
                 bnez t0, arch_spin_lock
                 ret

.size arch_spin_lock, .-arch_spin_lock

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl arch_spin_unlock
.type  arch_spin_unlock, @function


arch_spin_unlock: lr.w a1, (a0)
                  add a2, zero, 1
                  bne a2, a1, arch_spin_unlock
                  sc.w t0, zero, (a0)
                  bnez t0, arch_spin_unlock
                  ret

.size arch_spin_unlock, .-arch_spin_unlock

