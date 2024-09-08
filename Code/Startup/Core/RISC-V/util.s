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
.section ".text", "ax"
.align 4
.globl BlockingDelay
.type  BlockingDelay, @function


BlockingDelay:
               addi a0, a0, -1 
               bnez a0, BlockingDelay
               ret


.size BlockingDelay, .-BlockingDelay

