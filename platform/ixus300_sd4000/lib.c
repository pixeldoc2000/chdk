#include "platform.h"

void shutdown() {
    volatile long *p = (void*)0xC0220130;

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

#define LED_DEBUG 0xC0220130    // Green Led (backside)
//#define DEBUG_LED_DELAY 2500000    // use beforce change CPU speed in boot.c
#define DEBUG_LED_DELAY 9000000    // use after change CPU speed in boot.c

void debug_led(int state) {
    volatile long *p=(void*)LED_DEBUG;

    if (state)
        p[0]=0x46;
    else
        p[0]=0x44;

    // delay loop
    int i;
    for (i=0; i<DEBUG_LED_DELAY; i++)
        asm("nop\n nop\n");
}

#define LED_AF 0xc0220080

int get_flash_params_count(void) {
    return 114;
}
