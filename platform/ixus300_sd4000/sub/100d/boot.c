#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void boot();


#define DEBUG_LED 0xC02200C4

void boot() {    //#fs
    long *canon_data_src = (void*)0xFFC206D4;    // ROM:FF810130 ?!?
    long *canon_data_dst = (void*)0x1900;        // ROM:FF810134
    long canon_data_len = 0xf0c4 - 0x1900;       // data_end - data_start ?!?
    long *canon_bss_start = (void*)0xf0c4;       // just after data ?!?
    long canon_bss_len = 0x9d024 - 0xf0c4;       // ?!?

    long i;

    // Code taken from VxWorks CHDK. Changes CPU speed?
    asm volatile (
        "MRC     p15, 0, R0,c1,c0\n"
        "ORR     R0, R0, #0x1000\n"
        "ORR     R0, R0, #4\n"
        "ORR     R0, R0, #1\n"
        "MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
        canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
        canon_bss_start[i]=0;

/*    asm volatile (
        "MRC     p15, 0, R0,c1,c0\n"
        "ORR     R0, R0, #0x1000\n"
        "BIC     R0, R0, #4\n"
        "ORR     R0, R0, #1\n"
        "MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
*/

    // jump to init-sequence that follows the data-copy-routine 
    asm volatile ("B      sub_FF810354_my\n");
}; //#fe


// init
void __attribute__((naked,noinline)) sub_FF810354_my() {    //#fs
        asm volatile (
                "LDR     R0, =0xFF8103CC\n"
                "MOV     R1, #0\n"
                "LDR     R3, =0xFF810404\n"
            "loc_FF810360:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FF810360\n"
                "LDR     R0, =0xFF810404\n"
                "MOV     R1, #0x4B0\n"
                "LDR     R3, =0xFF810618\n"
            "loc_FF81037C:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FF81037C\n"
                "MOV     R0, #0xD2\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "MOV     R0, #0xD3\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "LDR     R0, =0x6C4\n"
                "LDR     R2, =0xEEEEEEEE\n"
                "MOV     R3, #0x1000\n"
            "loc_FF8103B0:\n"
                "CMP     R0, R3\n"
                "STRCC   R2, [R0],#4\n"
                "BCC     loc_FF8103B0\n"
                //"BL      sub_FF811198\n"    // original
                "BL      sub_FF811198_my\n"    // +
        );
} //#fe

void __attribute__((naked,noinline)) sub_FF811198_my() { //#fs
        asm volatile (
                //"STR     LR, [SP,#var_4]!
                "STR     LR, [SP,#-4]!\n"       // inspired by original CHDK-code
                "SUB     SP, SP, #0x74\n"
                "MOV     R0, SP\n"
                "MOV     R1, #0x74\n"
                "BL      sub_FFB59A1C\n"
                "MOV     R0, #0x53000\n"
                "STR     R0, [SP,#0x78-0x74]\n"

                //"LDR     R0, =0x14B394\n"    // original
                "LDR     R0, =new_sa\n"        // +
                "LDR     R0, [R0]\n"           // +

                "LDR     R2, =0x379C00\n"
                "LDR     R1, =0x3724A8\n"
                "STR     R0, [SP,#0x78-0x70]\n"
                "SUB     R0, R1, R0\n"
                "ADD     R3, SP, #0x78-0x6C\n"
                "STR     R2, [SP,#0x78-0x78]\n"
                "STMIA   R3, {R0-R2}\n"
                "MOV     R0, #0x22\n"
                "STR     R0, [SP,#0x78-0x60]\n"
                "MOV     R0, #0x68\n"
                "STR     R0, [SP,#0x78-0x5C]\n"
                "LDR     R0, =0x19B\n"

                //"LDR     R1, =sub_FF815E58\n"    // original uHwSetup()
                "LDR     R1, =uHwSetup_my\n"       // +

                "STR     R0, [SP,#0x78-0x58]\n"
                "MOV     R0, #0x96\n"
                "STR     R0, [SP,#0x78-0x54]\n"
                "MOV     R0, #0x78\n"
                "STR     R0, [SP,#0x78-0x50]\n"
                "MOV     R0, #0x64\n"
                "STR     R0, [SP,#0x78-0x4C]\n"
                "MOV     R0, #0\n"
                "STR     R0, [SP,#0x78-0x48]\n"
                "STR     R0, [SP,#0x78-0x44]\n"
                "MOV     R0, #0x10\n"
                "STR     R0, [SP,#0x78-0x1C]\n"
                "MOV     R0, #0x800\n"
                "STR     R0, [SP,#0x78-0x18]\n"
                "MOV     R0, #0xA0\n"
                "STR     R0, [SP,#0x78-0x14]\n"
                "MOV     R0, #0x280\n"
                "STR     R0, [SP,#0x78-0x10]\n"
                "MOV     R0, SP\n"
                "MOV     R2, #0\n"
                "BL      sub_FF813404\n"
                "ADD     SP, SP, #0x74\n"
                "LDR     PC, [SP],#4\n"
        );
};    //#fe

// ROM:FF815E58
void __attribute__((naked,noinline)) uHwSetup_my() {    //#fs
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FF810B20\n"
                "BL      sub_FF81A244\n"       // dmSetup()
                "CMP     R0, #0\n"
                //"ADRLT   R0, =0xFF815F6C\n"      // "dmSetup"
                "LDRLT   R0, =0xFF815F6C\n"      // + "dmSetup"
                "BLLT    sub_FF815F4C\n"       // err_init_task()
                "BL      sub_FF815A94\n"       // termDriverInit()
                "CMP     R0, #0\n"
                //"ADRLT   R0, =0xFF815F74\n"      // "termDriverInit"
                "LDRLT   R0, =0xFF815F74\n"      // + "termDriverInit"
                "BLLT    sub_FF815F4C\n"       // err_init_task()
                //"ADR     R0, =0xFF815F84\n"    // "/_term"
                "LDR     R0, =0xFF815F84\n"    // + "/_term"
                "BL      sub_FF815B7C\n"       // termDeviceCreate()
                "CMP     R0, #0\n"
                //"ADRLT   R0, =0xFF815B7C\n"    // "termDeviceCreate"
                "LDRLT   R0, =0xFF815B7C\n"    // + "termDeviceCreate"
                "BLLT    sub_FF815F4C\n"       // err_init_task()
                //"ADR     R0, =0xFF815F84\n"    // "/_term"
                "LDR     R0, =0xFF815F84\n"    // + "/_term"
                "BL      sub_FF813BF0\n"       // stdioSetup()
                "CMP     R0, #0\n"
                //"ADRLT   R0, =0xFF813BF0\n"    // "stdioSetup"
                "LDRLT   R0, =0xFF813BF0\n"    // + "stdioSetup"
                "BLLT    sub_FF815F4C\n"       // err_init_task()
                "BL      sub_FF819C3C\n"       // stdlibSetup()
                "CMP     R0, #0\n"
                //"ADRLT   R0, =0xFF815FAC\n"    // "stdlibSetup"
                "LDRLT   R0, =0xFF815FAC\n"    // + "stdlibSetup"
                "BLLT    sub_FF815F4C\n"       // err_init_task()
                "BL      sub_FF81167C\n"       // armlib_setup()
                "CMP     R0, #0\n"
                //"ADRLT   R0, =0xFF815FB8\n"    // "armlib_setup"
                "LDRLT   R0, =0xFF815FB8\n"    // + "armlib_setup"
                "BLLT    sub_FF815F4C\n"       // err_init_task()
                "LDMFD   SP!, {R4,LR}\n"

                // "B       sub_FF81FAF0\n"    // taskcreate_Startup() ROM:FF81FAF0
                "B       CreateTask_Startup_my\n"    // +
        );
}; //#fe

// ROM:FF81FAF0
void __attribute__((naked,noinline)) CreateTask_Startup_my() { //#fs 
        asm volatile (
                "STMFD   SP!, {R3,LR}\n"
                //"BL      j_nullsub_213\n"
                "BL      sub_FF83BCF0\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF81FB34\n"
                "BL      sub_FF835D6C\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FF81FB34\n"
                "BL      sub_FF834574\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF81FB34\n"
                "BL      sub_FF833BDC\n"
                "LDR     R1, =0xC0220000\n"
                "MOV     R0, #0x44\n"
                "STR     R0, [R1,#0x1C]\n"
                "BL      sub_FF833DCC\n"
            "loc_FF81FB30:\n"
                "B       loc_FF81FB30\n"
            "loc_FF81FB34:\n"
                "BL      sub_FF834580\n"
                //"BL      j_nullsub_214\n"
                "BL      sub_FF839F18\n"
                "LDR     R1, =0x3CE000\n"
                "MOV     R0, #0\n"
                "BL      sub_FF83A360\n"
                "BL      sub_FF83A10C\n"    // KerSys.c:548
                "MOV     R3, #0\n"
                "STR     R3, [SP,#8-8]\n"

                //"ADR     R3, =0xFF81FA8C\n"    // original: task_Startup()
                "LDR     R3, task_Startup_my\n"    // + ROM:FF81FA8C

                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
                //"ADR     R0, =0xFF81FB7C\n"    // "Startup"
                "LDR     R0, =0xFF81FB7C\n"    // + "Startup"
                "BL      sub_FF81E83C\n"       // eventproc_export_CreateTask() KerTask.c:163
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

// ROM:FF81FA8C
void __attribute__((naked,noinline)) task_Startup_my() { //#fs 
        
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FF81650C\n"    // taskcreate_ClockSave()
                "BL      sub_FF835674\n"
                "BL      sub_FF833808\n"
                //"BL      j_nullsub_217\n"
                "BL      sub_FF83BF1C\n"

                //"BL      sub_FF83BDC4\n"    // StartSdInit() -> StartDiskboot()
        );
        CreateTask_spytask();    // +

        asm volatile (
                "BL      sub_FF83C0C0\n"
                "BL      sub_FF8322E4\n"
                "BL      sub_FF83BF4C\n"
                "BL      sub_FF8396BC\n"
                "BL      sub_FF83C0C4\n"

                //"BL      sub_FF834434\n"    // taskcreate_PhySw()
        );
        //CreateTask_PhySw();    // +
        debug_led(1);

        asm volatile (
                "BL      sub_FF8379F8\n"     // ToDo: task_ShootSeqTask Mod here ?

                "BL      sub_FF83C0DC\n"
                //"BL      nullsub_201\n"
                "BL      sub_FF833254\n"    // "Battery.c:0\n"
                "BL      sub_FF83BAC8\n"    // taskcreate_Bye()
                "BL      sub_FF8337BC\n"
                "BL      sub_FF8331F0\n"
                "BL      sub_FF832318\n"
                "BL      sub_FF83CB24\n"
                "BL      sub_FF8331C8\n"

                //"LDMFD   SP!, {R4,LR}\n"
                //"B       sub_FF81662C\n"    // "MLHClock.c:992"
                "BL      sub_FF81662C\n"    // BL instead of B to last function to control action after its return
                "LDMFD   SP!, {R4,LR}\n"    // +
        );
}; //#fe

void CreateTask_spytask() {    //#fs
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

};    //#fe

void CreateTask_PhySw() { //#fs 
        _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
}; //#fe
