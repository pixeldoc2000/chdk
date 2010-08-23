#include "platform.h"

void shutdown() {
    volatile long *p = (void*)0xC02200C4;

    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0"
    );

    *p = 0x44;

    while(1);
}


#define LED_PR 0xC02200C4    // Green Led (backside)

void debug_led(int state) {
    volatile long *p=(void*)LED_PR;
    if (state)
        p[0]=0x46;
    else
        p[0]=0x44;
}

#define LED_AF 0xc0220080

int get_flash_params_count(void) {
    return 114;
}
