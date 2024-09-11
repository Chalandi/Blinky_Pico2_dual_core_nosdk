/******************************************************************************************
  Filename    : OsHwSchedPrio.s

  Core        : RISC-V RV32IMAC

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 13.01.2023

  Description : This function is searching for the highest ready task

******************************************************************************************/

.file "OsHwSchedPrio.s"

.section ".text"
.align 4
.globl  OsHwSearchForHighPrio
.type OsHwSearchForHighPrio, %function
.extern OsSchedPrioTypeSize
.extern OsHwSchedPrioReg
.extern __os_sw_clz

.equ osNoReadyTaskIsFound, 0xA0A0F5F5UL

OsHwSearchForHighPrio:
                       addi sp, sp, -4
                       sw ra, 0(sp)
                       la a0, OsSchedPrioTypeSize
                       lw a3, 0(a0)
                       addi a3, a3, -4
                       la a1, OsHwSchedPrioReg
                       add a1, a1, a3
.L_ContinueSearching:
                       lw a0, 0(a1)
                       addi sp, sp, -4*4
                       sw a1, 0(sp)
                       sw a2, 4(sp)
                       sw a3, 8(sp)
                       sw a4, 12(sp)
                       jal __os_sw_clz
                       lw a1, 0(sp)
                       lw a2, 4(sp)
                       lw a3, 8(sp)
                       lw a4, 12(sp)
                       addi sp, sp, 4*4
                       mv a2, a0
                       li a4, 32
                       bne a2, a4, .L_ReadyTaskFound
                       addi a1, a1, -4
                       addi a3, a3, -4
                       bgeu a3, zero, .L_ContinueSearching
                       la a0, osNoReadyTaskIsFound
                       lw ra, 0(sp)
                       addi sp, sp, 4
                       ret
.L_ReadyTaskFound:
                       li a0, 31
                       srli a3, a3, 2
                       slli a3, a3, 5
                       sub a0, a0, a2
                       add a0, a0, a3
                       lw ra, 0(sp)
                       addi sp, sp, 4
                       ret

.size OsHwSearchForHighPrio, .-OsHwSearchForHighPrio

