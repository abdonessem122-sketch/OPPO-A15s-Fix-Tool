#include "tee.h"
void enter_monitor(void);
#include <stdint.h>
int check_mode(){
    uint32_t cel;
    __asm__ volatile("mrs %0, cpsr" : "=r"(cpsr));
    mode= (cpsr >> 2) & 0x3;
    if(mode==0x16){return 0;}else{return -1;}
}

uint64_t smc_chandler(u64 r0,u64 r1,u64 r2,u64 r3){

   u32 result;
   tee_dispatch(r0,r1,r2,r3);
   return result;
}

u32 tee_dispatch(u32 cmd,u32 arg1,u32 arg2,u32 arg3){
   switch(cmd){
      case 0x81000001: {
      }}
}

void hacked_tee_boot_entry(void){
    enter_monitor();
}

void apmcu_icache_invalidate(){
    asm volatile ("mcr p15, 0, %0 , c7, c5, 0" :: "r"(0));
}

void apmcu_isb(){
    asm volatile ("ISB");
}

void apmcu_disable_icache(){
    uint32_t r0=0;
    asm volatile ("mcr p15, 0, %0, c7, c5, 6" :: "r"(r0)); // Flush entire branch target cache
    asm volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r"(r0));
    asm volatile ("bic %0,%0,#0x1800" : "=r"(r0) : "r"(r0)); // I+Z bits
    asm volatile ("mcr p15, 0, %0, c1, c0, 0" :: "r"(r0));
}

void apmcu_disable_smp(){
    uint32_t r0=0;
    asm volatile ("mrc p15, 0, %0, c1, c0, 1" : "=r"(r0));
    asm volatile ("bic %0,%0,#0x40" : "=r"(r0) : "r"(r0)); // SMP bit
    asm volatile ("mcr p15, 0, %0, c1, c0, 1" :: "r"(r0));
}


int in_el3_by_da_args(void){
            apmcu_icache_invalidate();
            apmcu_disable_icache();
            apmcu_isb();
            apmcu_disable_smp();
            void (*jump_addr)(void)=hacked_tee_boot_entry;
            DownloadArg *da_arg;
            da_arg = (DownloadArg*)(0x0010DC00 - sizeof(DownloadArg)); // CFG_DA_RAM_ADDR 0x10DC00 or 0x402000000
            da_arg->magic = 0x58885168;
            da_arg->ver   = 1;
            da_arg->flags = 1|2; //DA_FLAG_SKIP_PLL_INIT | DA_FLAG_SKIP_EMI_INIT;
            __asm__ volatile("MOV r4, r1");   /* r4 argument */ //init.s
            __asm__ volatile("MOV r5, r2");   /* r5 argument */
            __asm__ volatile("MOV r7, r3");   /* r3 = TEE boot entry, relocate to r7 */
            __asm__ volatile("ldr r7,%0"::"r"(hacked_tee_boot_entry));
           __asm__ volatile("mov r5, %0\n"
                        "mov r4, %1\n"
                        "mov r3, %2\n"
                        : : "r"((uint32_t)sizeof(DownloadArg)), "r"((uint32_t)da_arg), "r"(jump_addr) : "r5", "r4", "r3");
            
}

void default_handler(){
while(1) asm("wfi");
}
