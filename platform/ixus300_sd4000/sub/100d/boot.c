#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_spytask();
void JogDial_task_my(void);
void boot();

void taskCreateHook(int *p) {
 p-=17;
// if (p[0]==0x)  p[0]=(int)capt_seq_task;
//if (p[0]==0xFF96BD30)  p[0]=(int)movie_record_task;
// task_InitFileModules
 if (p[0]==0xFF8995E0)  p[0]=(int)init_file_modules_task;
//if (p[0]==0xFF861B68)  p[0]=(int)JogDial_task_my;
}
// ??? from sx10
void taskCreateHook2(int *p) {
 p-=17;
 if (p[0]==0xFF8995E0)  p[0]=(int)init_file_modules_task;
}


void boot() {    //#fs
    long *canon_data_src = (void*)0xFFC206D4;    // ROM:FF810130
    long *canon_data_dst = (void*)0x1900;        // ROM:FF810134
    long canon_data_len = 0xF244 - 0x1900;       // ROM:FF810138 data_end - data_start
    long *canon_bss_start = (void*)0xF244;       // ROM:FF810138 just after data
    long canon_bss_len = 0x14B394 - 0xF244;      // ROM:FF81014C

    long i;

    //debug_led(1);
    //debug_led(0);

    // Code taken from VxWorks CHDK. Changes CPU speed!
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

    // ##############################################################################################################################
    // Camera did shutdown cause by messed up filessystem on SD-Card
    // Remember to reformat your sd-card and copy fresh files to avoid strange error / crash / shutdown or check filesystem
    // also delete chdk config file may help
    // ##############################################################################################################################

    // see http://chdk.setepontos.com/index.php/topic,2972.msg30712.html#msg30712
    *(int*)0x1938=(int)taskCreateHook;           // ROM:FF810698 = 0x1938 ?!?
    //*(int*)0x1930=(int)taskCreateHook;           // from SD990
    *(int*)0x193C=(int)taskCreateHook2;          // ROM:FF8106D8 = 0x193C ?!?
    //*(int*)0x1934=(int)taskCreateHook2;          // from SD990

    // ROM:FF861134 similar to SX10 (but no +4 and values are >> 8)
    // Search on 0x12345678 finds function called by this (near kbd_p1_f)
    *(int*)(0x24B8)= (*(int*)0xC0220110)&1 ? 0x400000 : 0x200000; // replacement of sub_FF834580 for correct power-on.
    //*(int*)(0x2588)= (*(int*)0xC02200F8)&1 ? 0x200000 : 0x100000; // from SD990, replacement of sub_FF8219D8 for correct power-on.

    debug_led(1);
    debug_led(0);

    // jump to init-sequence that follows the data-copy-routine
    asm volatile ("B      sub_FF810354_my\n");
    //asm volatile ("B      sub_FF810354\n");
}; //#fe

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

            //"BL      sub_FF811198\n"           // original
            "BL      sub_FF811198_my\n"          // +
    );
} //#fe

void __attribute__((naked,noinline)) sub_FF811198_my() { //#fs
    asm volatile (
          "STR     LR, [SP,#-4]!\n"
          "SUB     SP, SP, #0x74\n"
          "MOV     R0, SP\n"
          "MOV     R1, #0x74\n"
          "BL      sub_FFB59A1C\n"
          "MOV     R0, #0x53000\n"
          "STR     R0, [SP,#4]\n"

          //"LDR     R0, =0x14B394\n"            // original
          "LDR     R0, =new_sa\n"                // +
          "LDR     R0, [R0]\n"                   // +

          "LDR     R2, =0x379C00\n"
          "LDR     R1, =0x3724A8\n"
          "STR     R0, [SP,#8]\n"
          "SUB     R0, R1, R0\n"
          "ADD     R3, SP, #0xC\n"
          "STR     R2, [SP]\n"
          "STMIA   R3, {R0-R2}\n"
          "MOV     R0, #0x22\n"
          "STR     R0, [SP,#0x18]\n"
          "MOV     R0, #0x68\n"
          "STR     R0, [SP,#0x1C]\n"
          "LDR     R0, =0x19B\n"

          //"LDR     R1, =sub_FF815E58\n"        // original uHwSetup()
          "LDR     R1, =uHwSetup_my\n"           // +

          "STR     R0, [SP,#0x20]\n"
          "MOV     R0, #0x96\n"
          "STR     R0, [SP,#0x24]\n"
          "MOV     R0, #0x78\n"
          "STR     R0, [SP,#0x28]\n"
          "MOV     R0, #0x64\n"
          "STR     R0, [SP,#0x2C]\n"
          "MOV     R0, #0\n"
          "STR     R0, [SP,#0x30]\n"
          "STR     R0, [SP,#0x34]\n"
          "MOV     R0, #0x10\n"
          "STR     R0, [SP,#0x5C]\n"
          "MOV     R0, #0x800\n"
          "STR     R0, [SP,#0x60]\n"
          "MOV     R0, #0xA0\n"
          "STR     R0, [SP,#0x64]\n"
          "MOV     R0, #0x280\n"
          "STR     R0, [SP,#0x68]\n"
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
            "BL      sub_FF81A244\n"             // dmSetup()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815F6C\n"        // "dmSetup"
            "LDRLT   R0, =0xFF815F6C\n"          // + gcc does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            "BL      sub_FF815A94\n"             // termDriverInit()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815F74\n"        // "termDriverInit"
            "LDRLT   R0, =0xFF815F74\n"          // + gcc does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            //"ADR     R0, =0xFF815F84\n"        // "/_term"
            "LDR     R0, =0xFF815F84\n"          // + gcc does not like ADR
            "BL      sub_FF815B7C\n"             // termDeviceCreate()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815B7C\n"        // "termDeviceCreate"
            "LDRLT   R0, =0xFF815B7C\n"          // + gcc does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            //"ADR     R0, =0xFF815F84\n"        // "/_term"
            "LDR     R0, =0xFF815F84\n"          // + gcc does not like ADR
            "BL      sub_FF813BF0\n"             // stdioSetup()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF813BF0\n"        // "stdioSetup"
            "LDRLT   R0, =0xFF813BF0\n"          // + gcc does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            "BL      sub_FF819C3C\n"             // stdlibSetup()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815FAC\n"        // "stdlibSetup"
            "LDRLT   R0, =0xFF815FAC\n"          // + gcc does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            "BL      sub_FF81167C\n"             // armlib_setup()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815FB8\n"        // "armlib_setup"
            "LDRLT   R0, =0xFF815FB8\n"          // + gcc does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            "LDMFD   SP!, {R4,LR}\n"

            //"B       sub_FF81FAF0\n"           // taskcreate_Startup() ROM:FF81FAF0
            "B       taskcreate_Startup_my\n"    // +
    );
}; //#fe

// ROM:FF81FAF0
void __attribute__((naked,noinline)) taskcreate_Startup_my() { //#fs
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
            //"BL      sub_FF834580\n"           // + removed for correct power-on on 'on/off' button (SD990)
            //"BL      j_nullsub_214\n"
            "BL      sub_FF839F18\n"
            "LDR     R1, =0x3CE000\n"
            "MOV     R0, #0\n"
            "BL      sub_FF83A360\n"
            "BL      sub_FF83A10C\n"             // KerSys.c:548
            "MOV     R3, #0\n"
            "STR     R3, [SP,#8-8]\n"

            //"ADR     R3, =0xFF81FA8C\n"        // original: task_Startup()
            //"LDR     R3, =0xFF81FA8C\n"        // + gcc does not like ADR
            "LDR     R3, =task_Startup_my\n"     // + ROM:FF81FA8C

            "MOV     R2, #0\n"
            "MOV     R1, #0x19\n"
            //"ADR     R0, =0xFF81FB7C\n"        // "Startup"
            "LDR     R0, =0xFF81FB7C\n"          // + gcc does not like ADR
            "BL      sub_FF81E83C\n"             // eventproc_export_CreateTask() KerTask.c:163
            "MOV     R0, #0\n"
            "LDMFD   SP!, {R12,PC}\n"
    );
}; //#fe

// ROM:FF81FA8C
void __attribute__((naked,noinline)) task_Startup_my() { //#fs 
    asm volatile (
            "STMFD   SP!, {R4,LR}\n"
            "BL      sub_FF81650C\n"             // taskcreate_ClockSave()
            "BL      sub_FF835674\n"
            "BL      sub_FF833808\n"
            "BL      sub_FF83BD30\n"             // j_nullsub_217\n"
            "BL      sub_FF83BF1C\n"

            //"BL      sub_FF83BDC4\n"           // original: StartSdInit() -> StartDiskboot()
    );

    CreateTask_spytask();                        // +

    //debug_led(1);
    //debug_led(0);

    asm volatile (
            "BL      sub_FF83C0C0\n"
            "BL      sub_FF8322E4\n"
            "BL      sub_FF83BF4C\n"
            "BL      sub_FF8396BC\n"
            "BL      sub_FF83C0C4\n"
    );

    //CreateTask_PhySw();                        // + not here, next call does this and jogdial

    //debug_led(1);
    //debug_led(0);

    asm volatile (
            //"BL      sub_FF834434\n"           // taskcreate_PhySw()
            "BL      taskcreate_PhySw_my\n"      // +
            //"BL      sub_FF8379F8\n"           // task_ShootSeqTask()
            //"BL      task_ShootSeqTask_my\n"   // +

            "BL      sub_FF83C0DC\n"
            //"BL      sub_FF8316A8\n"           // nullsub_201\n"
            "BL      sub_FF833254\n"             // "Battery.c:0\n"
            "BL      sub_FF83BAC8\n"             // taskcreate_Bye()
            "BL      sub_FF8337BC\n"
            "BL      sub_FF8331F0\n"             // taskcreate_BatteryTask()
            "BL      sub_FF832318\n"
            "BL      sub_FF83CB24\n"             // taskcreate_FactoryModeController()
            "BL      sub_FF8331C8\n"             // taskcreate_Ui()
            "LDMFD   SP!, {R4,LR}\n"
            "B       sub_FF81662C\n"             // "MLHClock.c:992"
            //"BL      sub_FF81662C\n"           // BL instead of B to last function to control action after its return
    );
}; //#fe

void __attribute__((naked,noinline)) task_ShootSeqTask_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4,LR}\n"
            "MOV     R1, #0\n"
            "MOV     R0, #0\n"
            "BL      sub_FF83A1B8\n"             // LOCATION: KernelMisc.c:43
            "LDR     R4, =0x1C80\n"
            "STR     R0, [R4,#0x10]\n"
            "BL      sub_FF8822DC\n"
            "BL      sub_FF883B38\n"             // taskcreate_SsTask()
            "BL      sub_FF881468\n"
            //"BL      sub_FF87BE2C\n"
            "BL      sub_FF87BE2C_my\n"         // +
            "BL      sub_FF8825C0\n"
            "LDR     R0, [R4,#0x10]\n"
            "LDMFD   SP!, {R4,LR}\n"
            "MOV     R1, #0x1000\n"
            "B       sub_FF8873E4\n"
    );
};    //#fe

void __attribute__((naked,noinline)) sub_FF87BE2C_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4,LR}\n"
            "LDR     R4, =0x2C28\n"
            "LDR     R0, [R4,#0x20]\n"
            "CMP     R0, #0\n"
            "BNE     loc_FF87BEA8\n"
            //"BL      nullsub_204\n"
            "MOV     R1, #1\n"
            "MOV     R0, #0\n"
            "BL      sub_FF83A1DC\n"             // LOCATION: KernelMisc.c:55
            "STR     R0, [R4,#0x18]\n"
            "MOV     R0, #0\n"
            "MOV     R1, #1\n"
            "BL      sub_FF83A1DC\n"             // LOCATION: KernelMisc.c:55
            "STR     R0, [R4,#4]\n"
            "MOV     R0, #0\n"
            "MOV     R1, #8\n"
            "BL      sub_FF83A1B8\n"             // LOCATION: KernelMisc.c:43
            "STR     R0, [R4,#0x1C]\n"
            "BL      sub_FF87C114\n"
            "BL      sub_FF87C89C\n"
            "MOV     R0, #0\n"
            "STR     R0, [R4,#0x14]\n"
            "ADD     R0, R4, #0x24\n"
            "MOV     R1, #0\n"
            "STR     R1, [R0],#4\n"
            "STR     R1, [R0]\n"
            //"BL      loc_FF87CAAC\n"
            "BL      sub_FF87CAAC\n"             // +
            "BL      sub_FF8827C0\n"
            "BL      sub_FF87FDCC\n"
            //"BL      sub_FF87D668\n"           // taskcreate_CaptSeqTask()
            "BL      sub_FF87D668_my\n"          // +
            "BL      sub_FF87E7EC\n"
        "loc_FF87BEA8:\n"
            "MOV     R0, #1\n"
            "STR     R0, [R4,#0x20]\n"
            "LDMFD   SP!, {R4,PC}\n"
    );
};    //#fe

void __attribute__((naked,noinline)) sub_FF87D668_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R3-R5,LR}\n"
            "LDR     R2, =0x395F8\n"
            "MOV     R0, #0\n"
            "MOV     R1, #0\n"
        "loc_FF87D678:\n"
            "ADD     R3, R2, R0,LSL#4\n"
            "ADD     R0, R0, #1\n"
            "CMP     R0, #5\n"
            "STR     R1, [R3,#8]\n"
            "BCC     loc_FF87D678\n"
            "BL      sub_FF87E230\n"
            //"BL      nullsub_208\n"
            "BL      sub_FF971AF4\n"
            "MOV     R1, #5\n"
            "MOV     R0, #0\n"
            "BL      sub_FF83A194\n"             // LOCATION: KernelMisc.c:31
            "LDR     R4, =0x2C7C\n"
            "LDR     R1, =0x101DFF\n"
            "STR     R0, [R4,#4]\n"
            "MOV     R0, #0\n"
            "BL      sub_FF83A1B8\n"             // LOCATION: KernelMisc.c:43
            "STR     R0, [R4]\n"
            "MOV     R0, #0\n"
            "MOV     R1, #1\n"
            "BL      sub_FF83A1DC\n"             // LOCATION: KernelMisc.c:55
            "STR     R0, [R4,#8]\n"
            "MOV     R3, #0\n"
            //"STR     R3, [SP,#0x10+var_10]\n"
            "STR     R3, [SP]\n"   // +

            //"LDR     R3, =sub_FF87D2D8\n"      // LOCATION: SsShootTask.c:13
            "LDR     R3, =0xFF87D2D8\n"          // +
            //"LDR     R3, =task_CaptSeqTask_my\n"    // + ToDo

            //"ADR     R0, sub_FF87D900\n"       // "CaptSeqTask"
            "LDR     R0, =0xFF87D900\n"          // +
            "MOV     R2, #0x1000\n"
            "MOV     R1, #0x17\n"
            "BL      sub_FF83A160\n"             // KernelCreateTask() LOCATION: KernelMisc.c:19
            "LDMFD   SP!, {R3-R5,PC}\n"
    );
};    //#fe

// ROM:FF834434
void __attribute__((naked,noinline)) taskcreate_PhySw_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R3-R5,LR}\n"
            "LDR     R4, =0x1C28\n"
            "LDR     R0, [R4,#0x10]\n"
            "CMP     R0, #0\n"
            "BNE     loc_FF834468\n"
            "MOV     R3, #0\n"
            //"STR     R3, [SP,#0x10+var_10]\n"
            "STR     R3, [SP]\n"

            //"ADR     R3, FF834400\n"           // task_PhySw()
            //"LDR     R3, FF834400\n"           // +
            "LDR     R3, =mykbd_task\n"          // +
            //"MOV     R2, #0x800\n"
            "MOV     R2, #0x2000\n"              // stack size for new task_PhySw so we don't have to do stack switch

            "MOV     R1, #0x17\n"
            //"ADR     R0, aPhysw      ; "PhySw"\n"
            "LDR     R0, =0xFF83464C\n"         // + "PhySw"
            "BL      sub_FF83A160\n"            // KernelCreateTask() LOCATION: KernelMisc.c:19
            "STR     R0, [R4,#0x10]\n"
        "loc_FF834468:\n"
            "BL      sub_FF861F04\n"
            "BL      sub_FF88DA70\n"
            //"BL      IsFactoryMode\n"
            "BL      sub_FF835CE4\n"             // + IsFactoryMode()
            "CMP     R0, #0\n"
            "LDREQ   R1, =0x32EA0\n"
            "LDMEQFD SP!, {R3-R5,LR}\n"
            //"BEQ     eventproc_export_OpLog.Start\n"
            "BEQ     sub_FF88D9F8\n"             // + eventproc_export_OpLog.Start()
            "LDMFD   SP!, {R3-R5,PC}\n"
    );
};    //#fe

// ROM:FF8995E0
void __attribute__((naked,noinline)) init_file_modules_task() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4-R6,LR}\n"
            "BL      sub_FF88FF2C\n"
            "LDR     R5, =0x5006\n"
            "MOVS    R4, R0\n"
            "MOVNE   R1, #0\n"
            "MOVNE   R0, R5\n"
            "BLNE    sub_FF893994\n"             // eventproc_export_PostLogicalEventToUI()
            //"BL      sub_FF88FF58\n"
            "BL      sub_FF88FF58_my\n"
            "BL      core_spytask_can_start\n"   // + safe to start CHDK SpyTask
            "CMP     R4, #0\n"
            "MOVEQ   R0, R5\n"
            "LDMEQFD SP!, {R4-R6,LR}\n"
            "MOVEQ   R1, #0\n"
            "BEQ     sub_FF893994\n"             // eventproc_export_PostLogicalEventToUI()
            "LDMFD   SP!, {R4-R6,PC}\n"
    );
};    //#fe

void __attribute__((naked,noinline)) sub_FF88FF58_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4,LR}\n"
            "MOV     R0, #3\n"
            //"BL      sub_FF871A04\n"             // LOCATION: Mounter.c:0
            "BL      sub_FF871A04_my\n"           // +
            //"BL      nullsub_84\n"
            "LDR     R4, =0x3034\n"
            "LDR     R0, [R4,#4]\n"
            "CMP     R0, #0\n"
            "BNE     loc_FF88FF90\n"
            "BL      sub_FF870C4C\n"
            "BL      sub_FF9426C4\n"
            "BL      sub_FF870C4C\n"
            "BL      sub_FF86D070\n"
            "BL      sub_FF870B4C\n"
            "BL      sub_FF942760\n"
        "loc_FF88FF90:\n"
            "MOV     R0, #1\n"
            "STR     R0, [R4]\n"
            "LDMFD   SP!, {R4,PC}\n"
    );
};    //#fe

void __attribute__((naked,noinline)) sub_FF871A04_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4-R8,LR}\n"
            "MOV     R8, R0\n"
            "BL      sub_FF871984\n"             // LOCATION: Mounter.c:0
            "LDR     R1, =0x384C8\n"
            "MOV     R6, R0\n"
            "ADD     R4, R1, R0,LSL#7\n"
            "LDR     R0, [R4,#0x6C]\n"
            "CMP     R0, #4\n"
            "LDREQ   R1, =0x83F\n"
            //"LDREQ   R0, =aMounter_c\n"        // "Mounter.c"
            "LDREQ   R0, =0xFF8714C4\n"          // +
            //"BLEQ    DebugAssert\n"
            "BLEQ    sub_FF81EB14\n"             // + DebugAssert()
            "MOV     R1, R8\n"
            "MOV     R0, R6\n"
            "BL      sub_FF87123C\n"             // LOCATION: Mounter.c:0
            "LDR     R0, [R4,#0x38]\n"
            "BL      sub_FF8720A4\n"
            "CMP     R0, #0\n"
            "STREQ   R0, [R4,#0x6C]\n"
            "MOV     R0, R6\n"
            "BL      sub_FF8712CC\n"
            "MOV     R0, R6\n"
            "BL      sub_FF87162C\n"
            "MOV     R5, R0\n"
            "MOV     R0, R6\n"
            //"BL      sub_FF87185C\n"             // LOCATION: Mounter.c:0
            "BL      sub_FF87185C_my\n"          // + correct sub ?!?, is different to SD990
            "LDR     R6, [R4,#0x3C]\n"
            "AND     R7, R5, R0\n"
            "CMP     R6, #0\n"
            "LDR     R1, [R4,#0x38]\n"
            "MOVEQ   R0, #0x80000001\n"
            "MOV     R5, #0\n"
            "BEQ     loc_FF871AB4\n"
            "MOV     R0, R1\n"
            "BL      sub_FF870DB4\n"
            "CMP     R0, #0\n"
            "MOVNE   R5, #4\n"
            "CMP     R6, #5\n"
            "ORRNE   R0, R5, #1\n"
            "BICEQ   R0, R5, #1\n"
            "CMP     R7, #0\n"
            "BICEQ   R0, R0, #2\n"
            "ORREQ   R0, R0, #0x80000000\n"
            "BICNE   R0, R0, #0x80000000\n"
            "ORRNE   R0, R0, #2\n"
        "loc_FF871AB4:\n"
            "CMP     R8, #7\n"
            "STR     R0, [R4,#0x40]\n"
            "LDMNEFD SP!, {R4-R8,PC}\n"
            "MOV     R0, R8\n"
            "BL      sub_FF8719D4\n"
            "CMP     R0, #0\n"
            "LDMEQFD SP!, {R4-R8,LR}\n"
            //"ADREQ   R0, aEmemMountError ; "EMEM MOUNT ERROR!!!\n"\n"
            //"ADREQ   R0, =0xFF871B00\n"          // "EMEM MOUNT ERROR!!!""
            "LDREQ   R0, =0xFF871B00\n"          // + gcc does not like ADREQ
            //"BEQ     qPrintf\n"
            "BEQ     0xFF81177C\n"               // qPrintf()
            "LDMFD   SP!, {R4-R8,PC}\n"
    );
};    //#fe

void __attribute__((naked,noinline)) sub_FF87185C_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R3-R9,LR}\n"
            "MOV     R5, R0\n"
            //"ADR     R0, unk_FF871AEC\n"
            "LDR     R0, =0xFF871AEC\n"          // +
            "LDR     R0, [R0]\n"
            "LDR     R9, =0x384C8\n"
            //"STR     R0, [SP,#0x20+var_20]\n"
            "STR     R0, [SP]\n"                 // +
            "ADD     R4, R9, R5,LSL#7\n"
            "LDR     R0, [R4,#0x6C]\n"
            "TST     R0, #4\n"
            "MOVNE   R0, #1\n"
            "BNE     locret_FF8718C8\n"
            "LDR     R0, [R4,#0x3C]\n"
            "LDR     R6, =0x2A18\n"
            "CMP     R0, #6\n"
            "MOV     R8, #1\n"
            "MOV     R7, #0\n"
            "ADDLS   PC, PC, R0,LSL#2\n"
            "B       loc_FF871928\n"
        "loc_FF8718A4:\n"
            "B       loc_FF8718C0\n"
        "loc_FF8718A8:\n"
            "B       loc_FF8718CC\n"
        "loc_FF8718AC:\n"
            "B       loc_FF8718CC\n"
        "loc_FF8718B0:\n"
            "B       loc_FF8718CC\n"
        "loc_FF8718B4:\n"
            "B       loc_FF8718CC\n"
        "loc_FF8718B8:\n"
            "B       loc_FF8718E4\n"
        "loc_FF8718BC:\n"
            "B       loc_FF8718CC\n"
        "loc_FF8718C0:\n"
            //jumptable FF87189C entry 0
            "MOV     R0, #0\n"
            "STR     R7, [R4,#0x6C]\n"
            "locret_FF8718C8:\n"
            "LDMFD   SP!, {R3-R9,PC}\n"
        "loc_FF8718CC:\n"
            //jumptable FF87189C entries 1-4,6
            "LDR     R0, [R4,#0x38]\n"
            "BL      sub_FF870DB4\n"
            "CMP     R0, #0\n"
            "STREQ   R7, [R6,#0x10]\n"
            "STRNE   R8, [R6,#0x10]\n"
            "B       loc_FF871934\n"
        "loc_FF8718E4:\n"
            //jumptable FF87189C entry 5
            "MOV     R2, #0\n"
            "MOV     R1, #0x8000\n"
            "MOV     R0, #0\n"
            "STR     R8, [R6,#0x10]\n"
            "BL      sub_FF889FD0\n"
            "MOV     R6, R0\n"
            "MOV     R2, R4\n"
            "MOV     R1, #0x8000\n"
            "BL      sub_FF951714\n"             // LOCATION: RamDisk.c:396
            "LDR     R0, [R9,R5,LSL#7]\n"
            "MOV     R1, R6\n"
            "STR     R0, [R4,#0x50]\n"
            "LDR     R0, [R4,#4]\n"
            "STR     R0, [R4,#0x54]\n"
            "MOV     R0, R5\n"
            "BL      sub_FF870EF8\n"
            "B       loc_FF871934\n"
        "loc_FF871928:\n"
            //jumptable FF87189C default entry
            "LDR     R1, =0x6A6\n"
            //"ADR     R0, aMounter_c  ; "Mounter.c"\n"
            "LDR     R0, =0xFF8714C4\n"          // + "Mounter.c"
            //"BL      DebugAssert\n"
            "BL      sub_FF81EB14\n"             // + DebugAssert()
        "loc_FF871934:\n"
            "MOV     R0, R5\n"
            "BL      sub_FF870B54\n"             // LOCATION: DriveLetterManager.c:147
            //"STRB    R0, [SP,#0x20+var_20]\n"
            "STRB    R0, [SP]\n"                 // +
            "MOV     R0, R5\n"
            "MOV     R1, SP\n"
            "BL      sub_FF87172C\n"
            "CMN     R0, #1\n"
            "BNE     loc_FF871974\n"
            "LDR     R1, =0x38548\n"
            "ADD     R0, R5, R5,LSL#4\n"
            "STR     R7, [R1,R0,LSL#2]\n"
            "LDR     R1, [R4,#0x6C]\n"
            "MOV     R0, #0\n"
            "BIC     R1, R1, #6\n"
        "loc_FF87196C:\n"
            "STR     R1, [R4,#0x6C]\n"
            "LDMFD   SP!, {R3-R9,PC}\n"
        "loc_FF871974:\n"
            "LDR     R1, [R4,#0x6C]\n"
            "MOV     R0, #1\n"
            "ORR     R1, R1, #4\n"
            "B       loc_FF87196C\n"
    );
};    //#fe

// looks generic
void CreateTask_spytask() {    //#fs
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

};    //#fe

/*
// looks generic
void CreateTask_PhySw() {    //#fs
        _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
};    //#fe
*/

/*
// SDHC Support
void __attribute__((naked,noinline)) sub_FF83CB24_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4,LR}\n"
            "BL      sub_FF8966D8\n"
            "BL      sub_FF835CE4\n"             // IsFactoryMode()
            "CMP     R0, #1\n"
            "BNE     loc_FF83CB44\n"
            "BL      sub_FF89973C\n"
            "LDMFD   SP!, {R4,LR}\n"
            "B       sub_FF835D84\n"             // StartFactoryModeController()
        "loc_FF83CB44:\n"
            "BL      sub_FF8987AC\n"
            "LDR     R4, =0x1D7C\n"
            "LDR     R0, [R4,#4]\n"
            "CMP     R0, #0\n"
            "LDMNEFD SP!, {R4,PC}\n"
            "MOV     R1, #0\n"

            //"LDR     R0, =sub_FF83C6E8\n"
            "LDR     R0, =sub_FF83C6E8_my\n" // +

            "BL      sub_FF893154\n"             // eventproc_export_CreateController()
            "STR     R0, [R4,#4]\n"
            "LDMFD   SP!, {R4,PC}\n"
    );
};    //#fe

// SDHC Support
void __attribute__((naked,noinline)) sub_FF83C6E8_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4-R10,LR}\n"
            "MOV     R5, R1\n"
            "LDR     R1, =0x1D7C\n"
            "MOV     R4, R3\n"
            "LDR     R0, [R1,#0x14]\n"
            "CMP     R0, #1\n"
            "BNE     loc_FF83C70C\n"
            "BL      sub_FF896D3C\n"
            "B       loc_FF83C79C\n"
        "loc_FF83C70C:\n"
            "LDR     R6, =0x1168\n"
            "LDR     R8, =0x1005\n"
            "SUB     R12, R6, #1\n"
            "CMP     R5, R12\n"
            "MOV     R7, #1\n"
            "BEQ     loc_FF83C9CC\n"
            "BGT     loc_FF83C864\n"
            "LDR     R12, =0x10AD\n"
            "CMP     R5, R12\n"
            "BEQ     loc_FF83CA8C\n"
            "BGT     loc_FF83C7E0\n"
            "LDR     R12, =0x1003\n"
            "CMP     R5, R12\n"
            "BEQ     loc_FF83CA70\n"
            "BGT     loc_FF83C7A4\n"
            "SUB     R12, R5, #0x800\n"
            "SUBS    R12, R12, #3\n"
            "LDMEQFD SP!, {R4-R10,LR}\n"
            "BEQ     sub_FF83CF48\n"
            "SUB     R12, R5, #0x900\n"
            "SUBS    R12, R12, #0x45\n"
            "BEQ     loc_FF83CAD8\n"
            "LDR     R4, =0x9A3\n"
            "CMP     R5, R4\n"
            "SUBNE   R12, R5, #0x900\n"
            "SUBNES  R12, R12, #0xA5\n"
            "BNE     loc_FF83CAFC\n"
            "LDR     R0, [R1,#0xC]\n"
            "MOV     R6, R1\n"
            "SUB     R12, R0, #0x8000\n"
            "SUBS    R12, R12, #2\n"
            "BEQ     loc_FF83C79C\n"
            "LDR     R0, =0x10A5\n"
            "BL      sub_FF895844\n"             // eventproc_export_IsControlEventActive()
            "CMP     R0, #0\n"
            "BEQ     loc_FF83CA4C\n"
        "loc_FF83C79C:\n"
            "MOV     R0, #0\n"
            "LDMFD   SP!, {R4-R10,PC}\n"
        "loc_FF83C7A4:\n"
            "CMP     R5, R8\n"
            "BEQ     loc_FF83C7D8\n"
            "SUB     R12, R5, #0x1000\n"
            "LDR     R0, =0x10A3\n"
            "SUBS    R12, R12, #0xA9\n"
            "BEQ     loc_FF83CA80\n"
            "SUB     R12, R5, #0x1000\n"
            "SUBS    R12, R12, #0xAA\n"
            "BNE     loc_FF83CAFC\n"
            "BL      sub_FF895844\n"             // eventproc_export_IsControlEventActive()
            "CMP     R0, #0\n"
            "BNE     loc_FF83C79C\n"
        "loc_FF83C7D4:\n"
            "BL      sub_FF83CFE0\n"
        "loc_FF83C7D8:\n"
            "MOV     R1, R4\n"
            "B       loc_FF83CA58\n"
        "loc_FF83C7E0:\n"
            "LDR     R12, =0x1162\n"
            "CMP     R5, R12\n"
            "BEQ     loc_FF83CA60\n"
            "BGT     loc_FF83C82C\n"
            "SUB     R12, R5, #0x1000\n"
            "SUBS    R12, R12, #0xAE\n"
            "BEQ     loc_FF83C7D4\n"
            "SUB     R12, R5, #0x1000\n"
            "SUBS    R12, R12, #0xAF\n"
            "BEQ     loc_FF83CA8C\n"
            "SUB     R12, R5, #0x1000\n"
            "SUBS    R12, R12, #0xB0\n"
            "BEQ     loc_FF83C7D4\n"
            "SUB     R12, R5, #0x1000\n"
            "SUBS    R12, R12, #0xB2\n"
            "LDREQ   R0, =0x1008\n"
            "MOVEQ   R1, R4\n"
            "BEQ     loc_FF83CA78\n"
            "B       loc_FF83CAFC\n"
        "loc_FF83C82C:\n"
            "SUB     R12, R5, #0x1100\n"
            "SUBS    R12, R12, #0x63\n"
            "MOVEQ   R0, #0\n"
            "BEQ     loc_FF83C85C\n"
            "SUB     R12, R5, #0x1000\n"
            "SUBS    R12, R12, #0x164\n"
            "MOVEQ   R0, #1\n"
            "BEQ     loc_FF83C85C\n"
            "SUB     R12, R5, #0x1100\n"
            "SUBS    R12, R12, #0x65\n"
            "BNE     loc_FF83CAFC\n"
            "MOV     R0, #2\n"
        "loc_FF83C85C:\n"
            "BL      sub_FF83D010\n"
            "B       loc_FF83C79C\n"
        "loc_FF83C864:\n"
            "LDR     R0, =0x2027\n"
            "LDR     R2, =0x1D7C\n"
            "CMP     R5, R0\n"
            "LDR     R2, [R2,#0x20]\n"
            "SUB     R9, R0, #0xC\n"
            "SUB     R10, R0, #0x23\n"
            "BEQ     loc_FF83CA98\n"
            "BGT     loc_FF83C914\n"
            "LDR     R12, =0x2005\n"
            "MOV     R0, #0\n"
            "CMP     R5, R12\n"
            "BEQ     loc_FF83C908\n"
            "BGT     loc_FF83C8E0\n"
            "CMP     R5, R6\n"
            "BEQ     loc_FF83C9CC\n"
            "LDR     R6, =0x116A\n"
            "CMP     R5, R6\n"
            "BEQ     loc_FF83CA28\n"
            "SUB     R12, R5, #0x2000\n"
            "SUBS    R12, R12, #2\n"
            "BEQ     loc_FF83C908\n"
            "CMP     R5, R10\n"
            "BNE     loc_FF83CAFC\n"
            "MOV     R6, R1\n"
            "STR     R0, [R1,#0x20]\n"
            "BL      sub_FF83CD2C\n"
            "LDR     R0, [R6,#0x10]\n"
            "CMP     R0, #1\n"
            "BNE     loc_FF83C7D8\n"
            "BL      loc_FF896DB8\n"
            "B       loc_FF83C79C\n"
        "loc_FF83C8E0:\n"
            "LDR     R3, =0x1D7C\n"
            "SUB     R12, R5, #0x2000\n"
            "LDR     R3, [R3,#0x10]\n"
            "SUBS    R12, R12, #0x19\n"
            "BEQ     loc_FF83CAB0\n"
            "CMP     R5, R9\n"
            "BEQ     loc_FF83CA3C\n"
            "SUB     R12, R5, #0x2000\n"
            "SUBS    R12, R12, #0x1D\n"
            "BNE     loc_FF83CAFC\n"
        "loc_FF83C908:\n"
            "STR     R0, [R1,#0x20]\n"
            "BL      sub_FF83CD2C\n"
            "B       loc_FF83C7D8\n"
        "loc_FF83C914:\n"
            "CMP     R5, #0x3140\n"
            "BEQ     loc_FF83CACC\n"
            "BGT     loc_FF83C950\n"
            "SUB     R12, R5, #0x3000\n"
            "SUBS    R12, R12, #6\n"
            "BEQ     loc_FF83C7D8\n"
            "SUB     R12, R5, #0x3000\n"
            "SUBS    R12, R12, #0x10\n"
            "BEQ     loc_FF83CAF4\n"
            "SUB     R12, R5, #0x3000\n"
            "SUBS    R12, R12, #0x110\n"
            "SUBNE   R12, R5, #0x3100\n"
            "SUBNES  R12, R12, #0x11\n"
            "BEQ     loc_FF83C7D8\n"
            "B       loc_FF83CAFC\n"
        "loc_FF83C950:\n"
            "SUB     R12, R5, #0x3200\n"
            "SUBS    R12, R12, #1\n"
            "BEQ     loc_FF83CB1C\n"
            "SUB     R12, R5, #0x3200\n"
            "SUBS    R12, R12, #2\n"
            "BEQ     loc_FF83C7D8\n"
            "SUB     R12, R5, #0x6600\n"
            "SUBS    R12, R12, #0x59\n"
            "BNE     loc_FF83CAFC\n"
            "MOV     R0, R4\n"
            "BL      sub_FF89C824\n"
            "B       loc_FF83C79C\n"

        "loc_FF83C9CC:\n"
            "MOV     R4, R1\n"
            "STR     R7, [R1,#0x10]\n"
            "MOV     R1, #0\n"
            "MOV     R0, #0x54\n"
            "BL      sub_FF8A3108\n"
            "LDR     R0, [R4,#0x20]\n"
            "LDR     R4, =0x4508\n"
            "CMP     R0, #0\n"
            "BEQ     loc_FF83CA04\n"
            "BL      loc_FF896D6C\n"
            "B       loc_FF83CA1C\n"
        "loc_FF83C9F8:\n"
            "MOV     R0, R4\n"
            "BL      sub_FF884134\n"         // AudioHandle.c:0
            "B       loc_FF83C79C\n"
        "loc_FF83CA04:\n"
            "BL      sub_FF89A67C\n"
            "BL      sub_FF89A5B0\n"
            "BL      sub_FF8A09A8\n"
            "CMP     R0, #0\n"
            "BLNE    sub_FF89F4C4\n"
            "BL      sub_FF837B20\n"
            "CMP     R5, R6\n"
            "BNE     loc_FF83C79C\n"
            "B       loc_FF83C9F8\n"
        "loc_FF83CA28:\n"
            "MOV     R0, #1\n"
            "BL      loc_FF896E48\n"
            "MOV     R1, R6\n"
            "MOV     R0, R8\n"
            "B       loc_FF83CA78\n"
        "loc_FF83CA3C:\n"
            "CMP     R3, #1\n"
            "BNE     loc_FF83C7D8\n"
            "BL      loc_FF896D6C\n"
            "B       loc_FF83C79C\n"
        "loc_FF83CA4C:\n"
            "CMP     R5, R4\n"
            "STREQ   R7, [R6,#0x34]\n"
            "B       loc_FF83CB1C\n"
        "loc_FF83CA58:\n"
            "; sub_FF83C6E8+438j\n"
            "MOV     R0, R5\n"
            "B       loc_FF83CA78\n"
        "loc_FF83CA60:\n"
            "BL      sub_FF8A09A8\n"
            "CMP     R0, #0\n"
            "BLNE    sub_FF89F4C4\n"
            "B       loc_FF83C7D8\n"
        "loc_FF83CA70:\n"
            "BL      sub_FF83C64C\n"
            "MOV     R1, R4\n"
        "loc_FF83CA78:\n"
            "LDMFD   SP!, {R4-R10,LR}\n"
            "B       sub_FF8984DC\n"
        "loc_FF83CA80:\n"
            "BL      sub_FF895844\n"         // eventproc_export_IsControlEventActive()
            "CMP     R0, #0\n"
            "BNE     loc_FF83C79C\n"
        "loc_FF83CA8C:\n"
            "MOV     R0, R5\n"
            "LDMFD   SP!, {R4-R10,LR}\n"
            "B       sub_FF83C468\n"
        "loc_FF83CA98:\n"
            "MOV     R1, #0\n"
            "BL      sub_FF8984DC\n"
            "MOV     R1, #0\n"
            "MOV     R0, R9\n"
            "BL      sub_FF8984DC\n"
            "B       loc_FF83CAC0\n"
        "loc_FF83CAB0:\n"
            "CMP     R2, #0\n"
            "BEQ     loc_FF83C79C\n"
            "CMP     R3, #0\n"
            "BNE     loc_FF83C79C\n"
        "loc_FF83CAC0:\n"
            "MOV     R1, #0\n"
            "MOV     R0, R10\n"
            "B       loc_FF83CB14\n"
        "loc_FF83CACC:\n"
            "CMP     R2, #0\n"
            "BLEQ    sub_FF83CD2C\n"
            "B       loc_FF83C79C\n"
        "loc_FF83CAD8:\n"
            "TST     R4, #0x80000000\n"
            "MOVNE   R0, #1\n"
            "LDMNEFD SP!, {R4-R10,PC}\n"
            "BL      sub_FF8A2190\n"
            "CMP     R0, #0\n"
            "BLEQ    sub_FF8395D8\n"
            "B       loc_FF83C79C\n"
        "loc_FF83CAF4:\n"
            "BL      sub_FF8927FC\n"
            "B       loc_FF83C79C\n"
        "loc_FF83CAFC:\n"
            "; sub_FF83C6E8+DCj ...\n"
            "SUB     R0, R5, #0x1000\n"
            "SUB     R0, R0, #0x51\n"
            "CMP     R0, #0x39\n"
            "BCS     loc_FF83CB1C\n"
            "MOV     R0, 0xFFFFFFFF\n"
            "MOV     R1, #0\n"
        "loc_FF83CB14:\n"
            "BL      sub_FF8984DC\n"
            "B       loc_FF83C79C\n"
        "loc_FF83CB1C:\n"
            "MOV     R1, #0\n"
            "B       loc_FF83CA58\n"
    );
};    //#fe
*/
