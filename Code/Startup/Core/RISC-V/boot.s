.file "boot.s"

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type _start_c0, @function
.align 4
.extern __CORE0_STACK_TOP
/*.extern _VectoredInterruptVectorTable*/
.extern Startup_Init
.globl _start_c0

_start_c0:
        /* disable all interrupts flag */
        li t0, ~0x08
        csrc mstatus, t0

        /* disable all specific interrupt sources */
        csrw mie, x0

        /* setup the stack pointer */
        la sp, __CORE0_STACK_TOP
       
        /* setup the direct interrupt handler */
        la t0, _VectoredInterruptVectorTable
        addi t0, t0, 1
        csrw mtvec, t0

        /* setup C/C++ runtime environment */
        jal  Startup_Init

.size _start_c0, .-_start_c0

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type _start_c1, @function
.align 4
.extern __CORE1_STACK_TOP
.extern _VectoredInterruptVectorTable
.extern main_Core1
.globl _start_c1

_start_c1:
        /* disable global interrupts flag */
        li t0, ~0x08
        csrc mstatus, t0

        /* disable all specific interrupt sources */
        csrw mie, x0

        /* setup the stack pointer */
        la sp, __CORE1_STACK_TOP
       
        /* setup the direct interrupt handler */
        la t0, _VectoredInterruptVectorTable
        addi t0, t0, 1
        csrw mtvec, t0

        /* jump to main entry of core1 (C/C++ runtime environment already done by core0) */
        jal  main_Core1

.size _start_c1, .-_start_c1


/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .riscv_intvect
.align 4
.type _VectoredInterruptVectorTable, @function
.globl OsDispatchHandler
.globl OsCat2IsrWrapper
.globl OsCatchAllCpuExceptions
.globl _VectoredInterruptVectorTable

_VectoredInterruptVectorTable:
                               j OsCatchAllCpuExceptions        /* Exceptions */
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j OsDispatchHandler              /* MachineSoftwareInterrupt (MSI) */
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j OsCat2IsrWrapper             /* MachineTimerInterrupt (MTI) --> The lowest priority interrupt level */
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j OsCat2IsrWrapper               /* MachineExternalInterrupt (MEI) --> The highest priority interrupt level */


.size _VectoredInterruptVectorTable, .-_VectoredInterruptVectorTable


.section .text
.type Isr_UndefinedHandler, @function
.align 4
Isr_UndefinedHandler: j Isr_UndefinedHandler
.size Isr_UndefinedHandler, .-Isr_UndefinedHandler



.section .text
.type AllExceptionsHandler, @function
.align 4
AllExceptionsHandler: j AllExceptionsHandler
.size AllExceptionsHandler, .-AllExceptionsHandler
