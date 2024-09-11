/******************************************************************************************
  Filename    : OsSwClz.s

  Core        : RISC-V RV32IMAC

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 13.01.2023

  Description : Software implementation of the count leading zero instruction (clz)

******************************************************************************************/

.file "OsSwClz.s"


.section .text
.globl __os_sw_clz
.type __os_sw_clz, @function
.align 4

__os_sw_clz:
             li a3, 32
             beq a0, zero, .L_end
             li a1, 32
             li a3, 0
             mv a2, a3
             not a2,a2
.L_continue:
             srli a1, a1, 1
             beq a1, zero, .L_end
             sll a2, a2, a1
             and a4, a0, a2
             bne a4, zero, .L_continue
             sll a0, a0, a1
             add a3, a3, a1
             j .L_continue
.L_end:
             mv a0, a3
             ret

.size __os_sw_clz, .-__os_sw_clz
