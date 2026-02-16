.global enter_monitor
.global monitor_stack_top
.global monitor_vector
.global smc_entry
monitor_stack_top:
   .space 0x2000
.align 11
monitor_vector:
   b sync_el3
   b irq_el3
   b fiq_el3
   b serr_el3
   b smc_entry


enter_monitor:
   //ldr x0,=monitor_stack_top
   mrs x1, SPSel
   mov x0, #1
   msr SPSel, x0
   ldr x0, =monitor_stack_top
   mov sp, x0

   //msr SP_EL3, x0 //msr SP_EL3,x0
   ldr x0,=monitor_vector
   msr VBAR_EL3,x0
   mrs x1,SCR_EL3
   orr x1,x1,#(1<<0)
   msr SCR_EL3,x1

sync_el3:
   b default_handler

irq_el3:
   b default_handler
fiq_el3:
   b default_handler
serr_el3:
   b default_handler


