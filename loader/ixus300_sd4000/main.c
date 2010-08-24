static void __attribute__((noreturn)) shutdown();
static void __attribute__((noreturn)) panic(int cnt);

extern long *blob_chdk_core;
extern long *blob_copy_and_reset;
extern long blob_chdk_core_size;
extern long blob_copy_and_reset_size;


void __attribute__((noreturn)) my_restart() 
{
    /*
    // DEBUG LED STUFF
    #define DEBUG_LED (void*)0xC0220130    // Greed Led at th Backside
    #define DEBUG_LED_DELAY 10000000
    volatile long *pDebugLed = (void*)DEBUG_LED;
    int DebugLedCounter;
    DebugLedCounter = DEBUG_LED_DELAY; *pDebugLed = 0x46;  while (DebugLedCounter--) { asm("nop\n nop\n"); };
    DebugLedCounter = DEBUG_LED_DELAY; *pDebugLed = 0x44;  while (DebugLedCounter--) { asm("nop\n nop\n"); };
    */
    // OK

    void __attribute__((noreturn)) (*copy_and_restart)(char *dst, char *src, long length);

    int i;
    for (i=0; i<(blob_copy_and_reset_size/sizeof(long)); i++){
        ((long*)(RESTARTSTART))[i] = blob_copy_and_reset[i];
    }

    copy_and_restart = (void*)RESTARTSTART;
    copy_and_restart((void*)MEMISOSTART, (char*)blob_chdk_core, blob_chdk_core_size);
}

//#define LED_PR 0xc0220084
//#define LED_PR 0xC02200D4
#define LED_PR 0xC0220130

static void __attribute__((noreturn)) shutdown()
{
    //volatile long *p = (void*)0xc02200a0;       // what does this LED? Powe
    volatile long *p = (void*)LED_PR;       // turned off later, so assumed to be power
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;  // led off.

    while(1);
}


static void __attribute__((noreturn)) panic(int cnt)
{
    volatile long *p=(void*)LED_PR;
    int i;

    for(;cnt>0;cnt--){
        p[0]=0x46;

        for(i=0;i<0x200000;i++){
            asm ("nop\n");
            asm ("nop\n");
        }
        p[0]=0x44;
        for(i=0;i<0x200000;i++){
            asm ("nop\n");
            asm ("nop\n");
        }
    }
    shutdown();
}
