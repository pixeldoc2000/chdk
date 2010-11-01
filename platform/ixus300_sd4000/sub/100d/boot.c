#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

const char * const new_sa = &_end;

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

// Forward declarations
void JogDial_task_my(void);

/*
// old Task Hook stuff
void taskCreateHook(int *p) {
    p-=17;
    // if(p[0]==0x0)  p[0]=(int)capt_seq_task;
    //if(p[0]==0xFF96BD30) p[0]=(int)movie_record_task;
    // task_InitFileModules
    if(p[0]==0xFF8995E0) p[0]=(int)init_file_modules_task;
    if(p[0]==0xFF861B68) p[0]=(int)JogDial_task_my;
}
// like SX10
void taskCreateHook2(int *p) {
    p-=17;
    if(p[0]==0xFF8995E0) p[0]=(int)init_file_modules_task;
}
*/

void taskHook(context_t **context) {    //#fs
    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));
    if(!_strcmp(tcb->name, "PhySw"))           tcb->entry = (void*)mykbd_task;
    if(!_strcmp(tcb->name, "CaptSeqTask"))     tcb->entry = (void*)capt_seq_task;
    if(!_strcmp(tcb->name, "InitFileModules")) tcb->entry = (void*)init_file_modules_task;
    if(!_strcmp(tcb->name, "MovieRecord"))     tcb->entry = (void*)movie_record_task;
    if(!_strcmp(tcb->name, "ExpDrvTask"))      tcb->entry = (void*)exp_drv_task;
    if(!_strcmp(tcb->name, "RotarySw"))        tcb->entry = (void*)JogDial_task_my;
}    //#fe

void CreateTask_spytask() {    //#fs
    _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}    //#fe

/*
// old
void boot() {    //#fs
    long *canon_data_src = (void*)0xFFC206D4;    // ROM:FF810130
    long *canon_data_dst = (void*)0x1900;        // ROM:FF810134
    long canon_data_len = 0xF244 - 0x1900;       // ROM:FF810138 data_end - data_start
    long *canon_bss_start = (void*)0xF244;       // ROM:FF810138 just after data
    long canon_bss_len = 0x14B394 - 0xF244;      // ROM:FF81014C

    long i;

    //debug_led(1);
    //debug_led(0);

    // Code taken from VxWorks CHDK. Change CPU speed!
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

    // see http://chdk.setepontos.com/index.php/topic,2972.msg30712.html#msg30712
    *(int*)0x1938=(int)taskCreateHook;           // ROM:FF810698
    *(int*)0x193C=(int)taskCreateHook2;          // ROM:FF8106D8

    // ROM:FF861134 similar to SX10, G11
    *(int*)(0x24B8)=(*(int*)0xC0220110)&1 ? 0x400000 : 0x200000;   // replacement for correct power-on ?!?

    //debug_led(1);
    //debug_led(0);

    // jump to init-sequence that follows the data-copy-routine
    //asm volatile("B      sub_FF810354\n");
    asm volatile("B      sub_FF810354_my\n");    // +
}; //#fe
*/

// ROM:FF81000C
void __attribute__((naked,noinline)) boot() {
    asm volatile (
            "LDR     R1, =0xC0410000\n"
            "MOV     R0, #0\n"
            "STR     R0, [R1]\n"
            "MOV     R1, #0x78\n"
            "MCR     p15, 0, R1,c1,c0\n"
            "MOV     R1, #0\n"
            "MCR     p15, 0, R1,c7,c10, 4\n"
            "MCR     p15, 0, R1,c7,c5\n"
            "MCR     p15, 0, R1,c7,c6\n"
            "MOV     R0, #0x3D\n"
            "MCR     p15, 0, R0,c6,c0\n"
            "MOV     R0, #0xC000002F\n"
            "MCR     p15, 0, R0,c6,c1\n"
            "MOV     R0, #0x35\n"
            "MCR     p15, 0, R0,c6,c2\n"
            "MOV     R0, #0x40000035\n"
            "MCR     p15, 0, R0,c6,c3\n"
            "MOV     R0, #0x80000017\n"
            "MCR     p15, 0, R0,c6,c4\n"
            "LDR     R0, =0xFF80002D\n"
            "MCR     p15, 0, R0,c6,c5\n"
            "MOV     R0, #0x34\n"
            "MCR     p15, 0, R0,c2,c0\n"
            "MOV     R0, #0x34\n"
            "MCR     p15, 0, R0,c2,c0, 1\n"
            "MOV     R0, #0x34\n"
            "MCR     p15, 0, R0,c3,c0\n"
            "LDR     R0, =0x3333330\n"
            "MCR     p15, 0, R0,c5,c0, 2\n"
            "LDR     R0, =0x3333330\n"
            "MCR     p15, 0, R0,c5,c0, 3\n"
            "MRC     p15, 0, R0,c1,c0\n"
            "ORR     R0, R0, #0x1000\n"
            "ORR     R0, R0, #4\n"
            "ORR     R0, R0, #1\n"
            "MCR     p15, 0, R0,c1,c0\n"
            "MOV     R1, #0x80000006\n"
            "MCR     p15, 0, R1,c9,c1\n"
            "MOV     R1, #6\n"
            "MCR     p15, 0, R1,c9,c1, 1\n"
            "MRC     p15, 0, R1,c1,c0\n"
            "ORR     R1, R1, #0x50000\n"
            "MCR     p15, 0, R1,c1,c0\n"
            "LDR     R2, =0xC0200000\n"
            "MOV     R1, #1\n"
            "STR     R1, [R2,#0x10C]\n"
            "MOV     R1, #0xFF\n"
            "STR     R1, [R2,#0xC]\n"
            "STR     R1, [R2,#0x1C]\n"
            "STR     R1, [R2,#0x2C]\n"
            "STR     R1, [R2,#0x3C]\n"
            "STR     R1, [R2,#0x4C]\n"
            "STR     R1, [R2,#0x5C]\n"
            "STR     R1, [R2,#0x6C]\n"
            "STR     R1, [R2,#0x7C]\n"
            "STR     R1, [R2,#0x8C]\n"
            "STR     R1, [R2,#0x9C]\n"
            "STR     R1, [R2,#0xAC]\n"
            "STR     R1, [R2,#0xBC]\n"
            "STR     R1, [R2,#0xCC]\n"
            "STR     R1, [R2,#0xDC]\n"
            "STR     R1, [R2,#0xEC]\n"
            "STR     R1, [R2,#0xFC]\n"
            "LDR     R1, =0xC0400008\n"
            "LDR     R2, =0x430005\n"
            "STR     R2, [R1]\n"
            "MOV     R1, #1\n"
            "LDR     R2, =0xC0243100\n"
            "STR     R2, [R1]\n"
            "LDR     R2, =0xC0242010\n"
            "LDR     R1, [R2]\n"
            "ORR     R1, R1, #1\n"
            "STR     R1, [R2]\n"
            "LDR     R0, =0xFFC206D4\n"          // canon_data_src
            "LDR     R1, =0x1900\n"              // MEMBASEADDR
            "LDR     R3, =0xF244\n"
        "loc_FF81013C:\n"
            "CMP     R1, R3\n"
            "LDRCC   R2, [R0],#4\n"
            "STRCC   R2, [R1],#4\n"
            "BCC     loc_FF81013C\n"
            "LDR     R1, =0x14B394\n"            // MEMISOSTART
            "MOV     R2, #0\n"
        "loc_FF810154:\n"
            "CMP     R3, R1\n"
            "STRCC   R2, [R3],#4\n"
            "BCC     loc_FF810154\n"
            //"B       sub_FF810354\n"
            "B       sub_FF810354_my\n"          // +
    );
}    //#fe


void __attribute__((naked,noinline)) sub_FF810354_my() {    //#fs
    // ToDo: verify the Hooks are working, like SX210
    *(int*)0x1934=(int)taskHook;   //was 1934 in sx200 if 1938 hangs
    *(int*)0x1938=(int)taskHook;

    // Power Button detection (short press = playback mode, long press = record mode)
    // replacement for sub_FF834580
    *(int*)(0x24B8)= (*(int*)0xC0220110)&1 ? 0x400000 : 0x200000;    // ROM:FF861138, value 0x200000 and 0x400000 must be in reverse order, else detection is reversed too

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
            //"B       sub_FF811198_my\n"          // Todo: B instead of BL ?!?

            // ToDo: shouldn't we continue with original function ?!? Most other Port does not...
            //asm volatile ("B      sub_FF8103CC\n");
    );
}    //#fe

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
            "LDRLT   R0, =0xFF815F6C\n"          // compiler does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            "BL      sub_FF815A94\n"             // termDriverInit()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815F74\n"        // "termDriverInit"
            "LDRLT   R0, =0xFF815F74\n"          // compiler does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            //"ADR     R0, =0xFF815F84\n"        // "/_term"
            "LDR     R0, =0xFF815F84\n"          // compiler does not like ADR
            "BL      sub_FF815B7C\n"             // termDeviceCreate()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815B7C\n"        // "termDeviceCreate"
            "LDRLT   R0, =0xFF815B7C\n"          // compiler does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            //"ADR     R0, =0xFF815F84\n"        // "/_term"
            "LDR     R0, =0xFF815F84\n"          // compiler does not like ADR
            "BL      sub_FF813BF0\n"             // stdioSetup()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF813BF0\n"        // "stdioSetup"
            "LDRLT   R0, =0xFF813BF0\n"          // compiler does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            "BL      sub_FF819C3C\n"             // stdlibSetup()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815FAC\n"        // "stdlibSetup"
            "LDRLT   R0, =0xFF815FAC\n"          // compiler does not like ADRLT
            "BLLT    sub_FF815F4C\n"             // err_init_task()
            "BL      sub_FF81167C\n"             // armlib_setup()
            "CMP     R0, #0\n"
            //"ADRLT   R0, =0xFF815FB8\n"        // "armlib_setup"
            "LDRLT   R0, =0xFF815FB8\n"          // compiler does not like ADRLT
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
            //"BL      sub_FF834580\n"           // + disabled for correct Power Button detection
            //"BL      j_nullsub_214\n"
            "BL      sub_FF839F18\n"
            "LDR     R1, =0x3CE000\n"
            "MOV     R0, #0\n"
            "BL      sub_FF83A360\n"
            "BL      sub_FF83A10C\n"             // KerSys.c:548
            "MOV     R3, #0\n"
            "STR     R3, [SP,#8-8]\n"

            //"ADR     R3, =0xFF81FA8C\n"        // original: task_Startup()
            //"LDR     R3, =0xFF81FA8C\n"        // compiler does not like ADR
            "LDR     R3, =task_Startup_my\n"     // +

            "MOV     R2, #0\n"
            "MOV     R1, #0x19\n"
            //"ADR     R0, =0xFF81FB7C\n"        // "Startup"
            "LDR     R0, =0xFF81FB7C\n"          // compiler does not like ADR
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
            "BL      sub_FF83BD30\n"             // j_nullsub_217
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

            "BL      sub_FF834434\n"             // taskcreate_PhySw()
            //"BL      taskcreate_PhySw_my\n"      // +

            "BL      sub_FF8379F8\n"             // task_ShootSeqTask()
            //"BL      task_ShootSeqTask_my\n"     // +

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
    );
}; //#fe

/*
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
            "BL      sub_FF87BE2C_my\n"          // +
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
            "BL      sub_FF87CAAC\n"
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
            "STR     R3, [SP]\n"   // +

            //"LDR     R3, =0xFF87D2D8\n"        // LOCATION: SsShootTask.c:13
            "LDR     R3, =capt_seq_task\n"    // +

            //"ADR     R0, sub_FF87D900\n"       // "CaptSeqTask"
            "LDR     R0, =0xFF87D900\n"          // compiler does not like ADR
            "MOV     R2, #0x1000\n"
            "MOV     R1, #0x17\n"
            "BL      sub_FF83A160\n"             // KernelCreateTask() LOCATION: KernelMisc.c:19
            "LDMFD   SP!, {R3-R5,PC}\n"
    );
};    //#fe
*/

/*
// ROM:FF834434
void __attribute__((naked,noinline)) taskcreate_PhySw_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R3-R5,LR}\n"
            "LDR     R4, =0x1C28\n"
            "LDR     R0, [R4,#0x10]\n"
            "CMP     R0, #0\n"
            "BNE     loc_FF834468\n"
            "MOV     R3, #0\n"
            "STR     R3, [SP]\n"

            //"ADR     R3, FF834400\n"           // task_PhySw()
            //"LDR     R3, =0xFF834400\n"        // compiler does not like ADR
            "LDR     R3, =mykbd_task\n"          // +
            //"MOV     R2, #0x800\n"
            "MOV     R2, #0x2000\n"              // + stack size for new task_PhySw so we don't have to do stack switch

            "MOV     R1, #0x17\n"
            //"ADR     R0, 0xFF83464C\n"         // "PhySw"
            "LDR     R0, =0xFF83464C\n"          // compiler does not like ADR
            "BL      sub_FF83A160\n"             // KernelCreateTask() LOCATION: KernelMisc.c:19
            "STR     R0, [R4,#0x10]\n"
        "loc_FF834468:\n"
            "BL      sub_FF861F04\n"             // taskcreate_RotarySw()
            "BL      sub_FF88DA70\n"
            "BL      sub_FF835CE4\n"             // IsFactoryMode()
            "CMP     R0, #0\n"
            "LDREQ   R1, =0x32EA0\n"
            "LDMEQFD SP!, {R3-R5,LR}\n"
            "BEQ     sub_FF88D9F8\n"             // eventproc_export_OpLog.Start()
            "LDMFD   SP!, {R3-R5,PC}\n"
    );
};    //#fe
*/

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
            "BL      sub_FF88FF58_my\n"          // +
            "BL      core_spytask_can_start\n"   // + safe to start CHDK SpyTask
            "CMP     R4, #0\n"
            "MOVEQ   R0, R5\n"
            "LDMEQFD SP!, {R4-R6,LR}\n"
            "MOVEQ   R1, #0\n"
            "BEQ     sub_FF893994\n"             // eventproc_export_PostLogicalEventToUI()
            "LDMFD   SP!, {R4-R6,PC}\n"
    );
};    //#fe

// ROM:FF861B68
// actually Task Name is task_RotarySw() not task_JogDial()
void __attribute__((naked,noinline)) JogDial_task_my() {
    asm volatile (
            "STMFD   SP!, {R4-R11,LR}\n"
            "SUB     SP, SP, #0x2C\n"
            "BL      sub_FF861F54\n"             // LOCATION: JogDial.c:14
            "LDR     R1, =0x24CC\n"
            "LDR     R9, =0xFFB5F800\n"
            "MOV     R0, #0\n"
            "ADD     R2, SP, #0x14\n"
            "ADD     R3, SP, #0x18\n"
            "ADD     R10, SP, #0xC\n"
            "ADD     R8, SP, #0x10\n"
            "MOV     R7, #0\n"
        "loc_FF861B94:\n"
            "ADD     R3, SP, #0x18\n"
            "ADD     R12, R3, R0,LSL#1\n"
            "ADD     R2, SP, #0x14\n"
            "STRH    R7, [R12]\n"
            "ADD     R12, R2, R0,LSL#1\n"
            "STRH    R7, [R12]\n"
            "STR     R7, [R8,R0,LSL#2]\n"
            "STR     R7, [R10,R0,LSL#2]\n"
            "ADD     R0, R0, #1\n"
            "CMP     R0, #1\n"
            "BLT     loc_FF861B94\n"
        "loc_FF861BC0:\n"
            "LDR     R0, =0x24CC\n"
            "MOV     R2, #0\n"
            "LDR     R0, [R0,#8]\n"
            "ADD     R1, SP, #0x4\n"
            "BL      sub_FF83994C\n"             // LOCATION: KerQueue.c:0
            "TST     R0, #1\n"
            "MOVNE   R1, #0x25C\n"
            //"ADRNE   R0, =0xFF861E8C\n"          // "JogDial.c"
            "LDRNE   R0, =0xFF861E8C\n"          // compiler does not like ADRNE
            "BLNE    sub_FF81EB14\n"             // DebugAssert()

            // disable JodDial Task in ALT mode
            // like G11
            //------------------  added code ---------------------
        "labelA:\n"
            "LDR     R0, =jogdial_stopped\n"
            "LDR     R0, [R0]\n"
            "CMP     R0, #1\n"
            "BNE     labelB\n"
            "MOV     R0, #40\n"
            "BL      _SleepTask\n"
            "B       labelA\n"
        "labelB:\n"
            //------------------  original code ------------------

            "LDR     R0, [SP,#0x4]\n"
            "AND     R4, R0, #0xFF\n"
            "AND     R0, R0, #0xFF00\n"
            "CMP     R0, #0x100\n"
            "BEQ     loc_FF861C44\n"
            "CMP     R0, #0x200\n"
            "BEQ     loc_FF861C7C\n"
            "CMP     R0, #0x300\n"
            "BEQ     loc_FF861ED8\n"
            "CMP     R0, #0x400\n"
            "BNE     loc_FF861BC0\n"
            "CMP     R4, #0\n"
            "LDRNE   R1, =0x30E\n"
            //"ADRNE   R0, =0xFF861E8C\n"        // "JogDial.c"
            "LDRNE   R0, =0xFF861E8C\n"          // compiler does not like ADRNE
            "BLNE    sub_FF81EB14\n"             // DebugAssert()
            "LDR     R2, =0xFFB5F7EC\n"
            "ADD     R0, R4, R4,LSL#2\n"
            "LDR     R1, [R2,R0,LSL#2]\n"
            "STR     R7, [R1]\n"
            "MOV     R1, #1\n"
            "ADD     R0, R2, R0,LSL#2\n"
        "loc_FF861C38:\n"
            "LDR     R0, [R0,#8]\n"
            "STR     R1, [R0]\n"
            "B       loc_FF861BC0\n"
        "loc_FF861C44:\n"
            "LDR     R5, =0x24DC\n"
            "LDR     R0, [R5,R4,LSL#2]\n"
            "BL      sub_FF83A8E4\n"
            //"ADR     R2, loc_FF861AD0\n"
            "LDR     R2, =0xFF861AD0\n"          // compiler does not like ADR
            "MOV     R1, R2\n"
            "ORR     R3, R4, #0x200\n"
            "MOV     R0, #0x28\n"
            "BL      sub_FF83A800\n"
            "TST     R0, #1\n"
            "CMPNE   R0, #0x15\n"
            "STR     R0, [R10,R4,LSL#2]\n"
            "BEQ     loc_FF861BC0\n"
            "LDR     R1, =0x271\n"
            "B       loc_FF861E7C\n"
        "loc_FF861C7C:\n"
            "LDR     R1, =0xFFB5F7EC\n"
            "ADD     R0, R4, R4,LSL#2\n"
            "STR     R0, [SP,#0x28]\n"
            "ADD     R0, R1, R0,LSL#2\n"
            "STR     R0, [SP,#0x24]\n"
            "LDR     R0, [R0,#4]\n"
            "LDR     R0, [R0]\n"
            "MOV     R2, R0,ASR#16\n"
            "ADD     R0, SP, #0x18\n"
            "ADD     R0, R0, R4,LSL#1\n"
            "STR     R0, [SP,#0x20]\n"
            "STRH    R2, [R0]\n"
            "ADD     R0, SP, #0x14\n"
            "ADD     R0, R0, R4,LSL#1\n"
            "STR     R0, [SP,#0x1C]\n"
            "LDRSH   R3, [R0]\n"
            "SUB     R0, R2, R3\n"
            "CMP     R0, #0\n"
            "BNE     loc_FF861D0C\n"
            "LDR     R0, [R8,R4,LSL#2]\n"
            "CMP     R0, #0\n"
            "BEQ     loc_FF861E34\n"
            "LDR     R5, =0x24DC\n"
            "LDR     R0, [R5,R4,LSL#2]\n"
            "BL      sub_FF83A8E4\n"
            //"ADR     R2, sub_FF861ADC\n"       // JogDial.c:824
            "LDR     R2, =0xFF861ADC\n"          // compiler does not like ADR
            "MOV     R1, R2\n"
            "ORR     R3, R4, #0x300\n"
            "MOV     R0, #0x1F4\n"
            "BL      sub_FF83A800\n"
            "TST     R0, #1\n"
            "CMPNE   R0, #0x15\n"
            "STR     R0, [R5,R4,LSL#2]\n"
            "BEQ     loc_FF861E34\n"
            "LDR     R1, =0x28E\n"
            "B       loc_FF861E2C\n"
        "loc_FF861D0C:\n"
            "MOV     R1, R0\n"
            "RSBLT   R0, R0, #0\n"
            "MOVLE   R5, #0\n"
            "MOVGT   R5, #1\n"
            "CMP     R0, #0xFF\n"
            "BLS     loc_FF861D4C\n"
            "CMP     R1, #0\n"
            "RSBLE   R0, R3, #0xFF\n"
            "ADDLE   R0, R0, #0x7F00\n"
            "ADDLE   R0, R0, R2\n"
            "RSBGT   R0, R2, #0xFF\n"
            "ADDGT   R0, R0, #0x7F00\n"
            "ADDGT   R0, R0, R3\n"
            "ADD     R0, R0, #0x8000\n"
            "ADD     R0, R0, #1\n"
            "EOR     R5, R5, #1\n"
        "loc_FF861D4C:\n"
            "STR     R0, [SP,#0x8]\n"
            "LDR     R0, [R8,R4,LSL#2]\n"
            "CMP     R0, #0\n"
            "BEQ     loc_FF861D9C\n"
            "LDR     R1, =0xFFB5F7E4\n"
            "ADD     R1, R1, R4,LSL#3\n"
            "LDR     R1, [R1,R5,LSL#2]\n"
            "CMP     R1, R0\n"
            "BEQ     loc_FF861DB8\n"
            "ADD     R11, R4, R4,LSL#1\n"
            "ADD     R6, R9, R11,LSL#2\n"
            "LDRB    R0, [R6,#9]\n"
            "CMP     R0, #1\n"
            "LDREQ   R0, [R6,#4]\n"
            "BLEQ    sub_FF89583C\n"
            "LDRB    R0, [R6,#8]\n"
            "CMP     R0, #1\n"
            "BNE     loc_FF861DB8\n"
            "LDR     R0, [R9,R11,LSL#2]\n"
            "B       loc_FF861DB4\n"
        "loc_FF861D9C:\n"
            "ADD     R0, R4, R4,LSL#1\n"
            "ADD     R1, R9, R0,LSL#2\n"
            "LDRB    R1, [R1,#8]\n"
            "CMP     R1, #1\n"
            "BNE     loc_FF861DB8\n"
            "LDR     R0, [R9,R0,LSL#2]\n"
        "loc_FF861DB4:\n"
            "BL      sub_FF89583C\n"
        "loc_FF861DB8:\n"
            "LDR     R0, =0xFFB5F7E4\n"
            "LDR     R1, [SP,#0x8]\n"
            "ADD     R6, R0, R4,LSL#3\n"
            "LDR     R0, [R6,R5,LSL#2]\n"
            "BL      sub_FF89576C\n"
            "LDR     R0, [R6,R5,LSL#2]\n"
            "STR     R0, [R8,R4,LSL#2]\n"
            "LDR     R0, [SP,#0x20]\n"
            "LDR     R1, [SP,#0x1C]\n"
            "LDRH    R0, [R0]\n"
            "STRH    R0, [R1]\n"
            "ADD     R0, R4, R4,LSL#1\n"
            "ADD     R0, R9, R0,LSL#2\n"
            "LDRB    R0, [R0,#9]\n"
            "CMP     R0, #1\n"
            "BNE     loc_FF861E34\n"
            "LDR     R5, =0x24DC\n"
            "LDR     R0, [R5,R4,LSL#2]\n"
            "BL      sub_FF83A8E4\n"
            //"ADR     R2, sub_FF861ADC\n"       // LOCATION: JogDial.c:824
            "LDR     R2, =0xFF861ADC\n"          // compiler does not like ADR
            "MOV     R1, R2\n"
            "ORR     R3, R4, #0x300\n"
            "MOV     R0, #0x1F4\n"
            "BL      sub_FF83A800\n"
            "TST     R0, #1\n"
            "CMPNE   R0, #0x15\n"
            "STR     R0, [R5,R4,LSL#2]\n"
            "BEQ     loc_FF861E34\n"
            "MOV     R1, #0x2E8\n"
        "loc_FF861E2C:\n"
            //"ADR     R0, =0xFF861E8C\n"        // "JogDial.c"
            "LDR     R0, =0xFF861E8C\n"          // compiler does not like ADR
            "BL      sub_FF81EB14\n"             // DebugAssert()
        "loc_FF861E34:\n"
            "ADD     R0, R4, R4,LSL#1\n"
            "ADD     R0, R9, R0,LSL#2\n"
            "LDRB    R0, [R0,#0xA]\n"
            "CMP     R0, #1\n"
            "BNE     loc_FF861EBC\n"
            "LDR     R0, =0x24CC\n"
            "LDR     R0, [R0,#0xC]\n"
            "CMP     R0, #0\n"
            "BEQ     loc_FF861EBC\n"
            //"ADR     R2, loc_FF861AD0\n"
            "LDR     R2, =0xFF861AD0\n"          // compiler does not like ADR
            "MOV     R1, R2\n"
            "ORR     R3, R4, #0x400\n"
            "BL      sub_FF83A800\n"
            "TST     R0, #1\n"
            "CMPNE   R0, #0x15\n"
            "STR     R0, [R10,R4,LSL#2]\n"
            "BEQ     loc_FF861BC0\n"
            "LDR     R1, =0x2F3\n"
        "loc_FF861E7C:\n"
            //"ADR     R0, =0xFF861E8C\n"        // "JogDial.c"
            "LDR     R0, =0xFF861E8C\n"          // compiler does not like ADR
            "BL      sub_FF81EB14\n"             // DebugAssert()
            "B       loc_FF861BC0\n"

        "loc_FF861EBC:\n"
            "LDR     R1, =0xFFB5F7EC\n"
            "LDR     R0, [SP,#0x28]\n"
            "LDR     R0, [R1,R0,LSL#2]\n"
            "STR     R7, [R0]\n"
            "LDR     R0, [SP,#0x24]\n"
            "MOV     R1, #1\n"
            "B       loc_FF861C38\n"
        "loc_FF861ED8:\n"
            "LDR     R0, [R8,R4,LSL#2]\n"
            "CMP     R0, #0\n"
            "MOVEQ   R1, #0x300\n"
            //"ADREQ   R0, =0xFF861E8C\n"        // "JogDial.c"
            "LDREQ   R0, =0xFF861E8C\n"          // compiler does not like ADREQ
            "BLEQ    sub_FF81EB14\n"             // DebugAssert()
            "ADD     R0, R4, R4,LSL#1\n"
            "ADD     R0, R9, R0,LSL#2\n"
            "LDR     R0, [R0,#4]\n"
            "BL      sub_FF89583C\n"
            "STR     R7, [R8,R4,LSL#2]\n"
            "B       loc_FF861BC0\n"
    );
}

void __attribute__((naked,noinline)) sub_FF88FF58_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4,LR}\n"
            "MOV     R0, #3\n"
            //"BL      sub_FF871A04\n"           // LOCATION: Mounter.c:0
            "BL      sub_FF871A04_my\n"          // +
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
            "LDREQ   R0, =0xFF8714C4\n"          // "Mounter.c"
            "BLEQ    sub_FF81EB14\n"             // DebugAssert()
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
            //"BL      sub_FF87162C\n"
            "BL      sub_FF87162C_my\n"          // +
            "MOV     R5, R0\n"
            "MOV     R0, R6\n"
            "BL      sub_FF87185C\n"             // LOCATION: Mounter.c:0
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
            //"ADREQ   R0, =0xFF871B00\n"        // "EMEM MOUNT ERROR!!!""
            "LDREQ   R0, =0xFF871B00\n"          // compiler does not like ADREQ
            //"BEQ     0xFF81177C\n"               // qPrintf()
            "BEQ     sub_FF81177C\n"               // fix gcc 4.5.1 compiler error
            "LDMFD   SP!, {R4-R8,PC}\n"
    );
};    //#fe

void __attribute__((naked,noinline)) sub_FF87162C_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4-R6,LR}\n"
            "MOV     R5, R0\n"
            "LDR     R0, =0x384C8\n"
            "ADD     R4, R0, R5,LSL#7\n"
            "LDR     R0, [R4,#0x6C]\n"
            "TST     R0, #2\n"
            "MOVNE   R0, #1\n"
            "LDMNEFD SP!, {R4-R6,PC}\n"
            "LDR     R0, [R4,#0x38]\n"
            "MOV     R1, R5\n"
            //"BL      sub_FF87134C\n"           // LOCATION: Mounter.c:0
            "BL      sub_FF87134C_my\n"          // +
            "CMP     R0, #0\n"
            "LDRNE   R0, [R4,#0x38]\n"
            "MOVNE   R1, R5\n"
            "BLNE    sub_FF8714E8\n"             // LOCATION: Mounter.c:0
            "LDR     R2, =0x38548\n"
            "ADD     R1, R5, R5,LSL#4\n"
            "LDR     R1, [R2,R1,LSL#2]\n"
            "CMP     R1, #4\n"
            "BEQ     loc_FF87168C\n"
            "CMP     R0, #0\n"
            "LDMEQFD SP!, {R4-R6,PC}\n"
            "MOV     R0, R5\n"
            "BL      sub_FF870E44\n"
        "loc_FF87168C:\n"
            "CMP     R0, #0\n"
            "LDRNE   R1, [R4,#0x6C]\n"
            "ORRNE   R1, R1, #2\n"
            "STRNE   R1, [R4,#0x6C]\n"
            "LDMFD   SP!, {R4-R6,PC}\n"
    );
};    //#fe

void __attribute__((naked,noinline)) sub_FF87134C_my() {    //#fs
    asm volatile (
            "STMFD   SP!, {R4-R10,LR}\n"
            "MOV     R9, R0\n"
            "LDR     R0, =0x384C8\n"
            "MOV     R8, #0\n"
            "ADD     R5, R0, R1,LSL#7\n"
            "LDR     R0, [R5,#0x3C]\n"
            "MOV     R7, #0\n"
            "CMP     R0, #7\n"
            "MOV     R6, #0\n"
            "ADDLS   PC, PC, R0,LSL#2\n"
            "B       loc_FF8714A4\n"
        "loc_FF871378:\n"
            "B       loc_FF8713B0\n"
        "loc_FF87137C:\n"
            //"B       loc_FF871398\n"
            "B       sub_FF871398\n"
        "loc_FF871380:\n"
            //"B       loc_FF871398\n"
            "B       sub_FF871398\n"
        "loc_FF871384:\n"
            //"B       loc_FF871398\n"
            "B       sub_FF871398\n"
        "loc_FF871388:\n"
            //"B       loc_FF871398\n"
            "B       sub_FF871398\n"
        "loc_FF87138C:\n"
            "B       loc_FF87149C\n"
        "loc_FF871390:\n"
            //"B       loc_FF871398\n"
            "B       sub_FF871398\n"
        "loc_FF871394:\n"
            //"B       loc_FF871398\n"             // jumptable FF871370 entries 1-4,6,7
            "B       sub_FF871398\n"
            "MOV     R2, #0\n"
            "MOV     R1, #0x200\n"
            "MOV     R0, #2\n"
            "BL      sub_FF889FD0\n"             // ExMem.AllocUncacheable()
            "MOVS    R4, R0\n"
            "BNE     loc_FF8713B8\n"
        "loc_FF8713B0:\n"                        // jumptable FF871370 entry 0
            "MOV     R0, #0\n"
            "LDMFD   SP!, {R4-R10,PC}\n"
        "loc_FF8713B8:\n"
            "LDR     R12, [R5,#0x50]\n"
            "MOV     R3, R4\n"
            "MOV     R2, #1\n"
            "MOV     R1, #0\n"
            "MOV     R0, R9\n"
            "BLX     R12\n"
            "CMP     R0, #1\n"
            "BNE     loc_FF8713E4\n"
            "MOV     R0, #2\n"
            "BL      sub_FF88A11C\n"             // ExMemMan.c:0
            "B       loc_FF8713B0\n"
        "loc_FF8713E4:\n"
            "LDR     R1, [R5,#0x64]\n"
            "MOV     R0, R9\n"
            "BLX     R1\n"

        // FAT32 Partition support
            "MOV   R1, R4\n"                     // pointer to MBR in R1
            "BL    mbr_read_dryos\n"             // total sectors count in R0 before and after call
                                                 // requires "define CAM_MULTIPART 1", else you get undefined reference compiler error ;-)

        // Start of DataGhost's FAT32 autodetection code
            // Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
            // According to the code below, we can use R1, R2, R3 and R12.
            // LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
            // that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
            "MOV     R12, R4\n"                    // Copy the MBR start address so we have something to work with
            "MOV     LR, R4\n"                     // Save old offset for MBR signature
            "MOV     R1, #1\n"                     // Note the current partition number
            "B       dg_sd_fat32_enter\n"          // We actually need to check the first partition as well, no increments yet!
        "dg_sd_fat32:\n"
            "CMP     R1, #4\n"                     // Did we already see the 4th partition?
            "BEQ     dg_sd_fat32_end\n"            // Yes, break. We didn't find anything, so don't change anything.
            "ADD     R12, R12, #0x10\n"            // Second partition
            "ADD     R1, R1, #1\n"                 // Second partition for the loop
        "dg_sd_fat32_enter:\n"
            "LDRB    R2, [R12, #0x1BE]\n"          // Partition status
            "LDRB    R3, [R12, #0x1C2]\n"          // Partition type (FAT32 = 0xB)
            "CMP     R3, #0xB\n"                   // Is this a FAT32 partition?
            "CMPNE   R3, #0xC\n"                   // Not 0xB, is it 0xC (FAT32 LBA) then?
            "BNE     dg_sd_fat32\n"                // No, it isn't. Loop again.
            "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
            "CMPNE   R2, #0x80\n"
            "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                                   // This partition is valid, it's the first one, bingo!
            "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.
        "dg_sd_fat32_end:\n"
        // End of DataGhost's FAT32 autodetection code

            "LDRB    R1, [R4,#0x1C9]\n"
            "LDRB    R3, [R4,#0x1C8]\n"
            "LDRB    R12, [R4,#0x1CC]\n"
            "MOV     R1, R1,LSL#24\n"
            "ORR     R1, R1, R3,LSL#16\n"
            "LDRB    R3, [R4,#0x1C7]\n"
            "LDRB    R2, [R4,#0x1BE]\n"
            "LDRB    LR, [R4,#0x1FF]\n"
            "ORR     R1, R1, R3,LSL#8\n"
            "LDRB    R3, [R4,#0x1C6]\n"
            "CMP     R2, #0\n"
            "CMPNE   R2, #0x80\n"
            "ORR     R1, R1, R3\n"
            "LDRB    R3, [R4,#0x1CD]\n"
            "MOV     R3, R3,LSL#24\n"
            "ORR     R3, R3, R12,LSL#16\n"
            "LDRB    R12, [R4,#0x1CB]\n"
            "ORR     R3, R3, R12,LSL#8\n"
            "LDRB    R12, [R4,#0x1CA]\n"
            "ORR     R3, R3, R12\n"

            //"LDRB    R12, [R4,#0x1FE]\n"       // original
            "LDRB    R12, [LR,#0x1FE]\n"         // + First MBR signature byte (0x55), LR is original offset.
            "LDRB    LR, [LR,#0x1FF]\n"          // + Last MBR signature byte (0xAA), LR is original offset.
            //"MOV     R4, #0\n"                 // ToDo: required ?

            "BNE     loc_FF871470\n"
            "CMP     R0, R1\n"
            "BCC     loc_FF871470\n"
            "ADD     R2, R1, R3\n"
            "CMP     R2, R0\n"
            "CMPLS   R12, #0x55\n"
            "CMPEQ   LR, #0xAA\n"
            "MOVEQ   R7, R1\n"
            "MOVEQ   R6, R3\n"
            "MOVEQ   R4, #1\n"
            "BEQ     loc_FF871474\n"
        "loc_FF871470:\n"
            "MOV     R4, R8\n"
        "loc_FF871474:\n"
            "MOV     R0, #2\n"
            "BL      sub_FF88A11C\n"             // ExMemMan.c:0
            "CMP     R4, #0\n"
            "BNE     loc_FF8714B0\n"
            "LDR     R1, [R5,#0x64]\n"
            "MOV     R7, #0\n"
            "MOV     R0, R9\n"
            "BLX     R1\n"
            "MOV     R6, R0\n"
            "B       loc_FF8714B0\n"
        "loc_FF87149C:\n"                        // jumptable FF871370 entry 5
            "MOV     R6, #0x40\n"
            "B       loc_FF8714B0\n"
        "loc_FF8714A4:\n"                        // jumptable FF871370 default entry
            "LDR     R1, =0x597\n"
            //"ADR     R0, aMounter_c\n"         // "Mounter.c"
            "LDR     R0, =0xFF8714C4\n"          // Compilter does not like ADR
            "BL      sub_FF81EB14\n"             // DebugAssert()
        "loc_FF8714B0:\n"
            "STR     R7, [R5,#0x44]!\n"
            "STMIB   R5, {R6,R8}\n"
            "MOV     R0, #1\n"
            "LDMFD   SP!, {R4-R10,PC}\n"
    );
};    //#fe
