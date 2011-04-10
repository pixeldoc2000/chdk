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

void boot() { //#fs
    long *canon_data_src = (void*)0xFFEBFB4C;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xd700 - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xd700; // just after data
    long canon_bss_len = 0xa47e0 - 0xd700;

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
    asm volatile ("B      sub_FFC001a4_my\n");
}; //#fe


// init
void __attribute__((naked,noinline)) sub_FFC001a4_my() { //#fs
        asm volatile (
                "LDR     R0, =0xFFC0021C\n"
                "MOV     R1, #0\n"
                "LDR     R3, =0xFFC00254\n"

        "loc_FFC001B0:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001B0\n"

                "LDR     R0, =0xFFC00254\n"
                "MOV     R1, #0x4B0\n"
                "LDR     R3, =0xFFC00468\n"

        "loc_FFC001CC:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001CC\n"
                "MOV     R0, #0xD2\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "MOV     R0, #0xD3\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "LDR     R0, =0x6C4\n" //???
                "LDR     R2, =0xEEEEEEEE\n"
                "MOV     R3, #0x1000\n"

        "loc_FFC00200:\n"
                "CMP     R0, R3\n"
                "STRCC   R2, [R0],#4\n"
                "BCC     loc_FFC00200\n"

                //"BL      sub_FFC00FA0\n"
                "BL      sub_FFC00FA0_my\n"
        );
} //#fe

void __attribute__((naked,noinline)) sub_FFC00FA0_my() { //#fs
        asm volatile (
              //"STR     LR, [SP,#0xFFFFFFFC]!\n"
              "STR     LR, [SP,#-4]!\n"         // inspired by original CHDK-code
              "SUB     SP, SP, #0x74\n"
              "MOV     R0, SP\n"
              "MOV     R1, #0x74\n"
              "BL      sub_FFE58D68\n"
              "MOV     R0, #0x53000\n"
              "STR     R0, [SP,#0x74-0x70]\n"//?????????...
        );
//              "LDR     R0, =0xE47E0\n"          // 0xa47e0 + 0x40000, note: 0x20000 *should* have been enough, but our code was overwritten...
                                                // ...thus we push the memory pool a little more up (0x30000 = 192k)
        asm volatile (
              "LDR     R0, =new_sa\n"
              "LDR     R0, [R0]\n"
        );
        asm volatile (
              "LDR     R2, =0x279C00\n"
              "LDR     R1, =0x272968\n"
              "STR     R0, [SP,#0x74-0x6C]\n"
              "SUB     R0, R1, R0\n"
              "ADD     R3, SP, #0x74-0x68\n"
              "STR     R2, [SP,#0x74-0x74]\n"
              "STMIA   R3, {R0-R2}\n"
              "MOV     R0, #0x22\n"
              "STR     R0, [SP,#0x74-0x5C]\n"
              "MOV     R0, #0x68\n"
              "STR     R0, [SP,#0x74-0x58]\n"
              "LDR     R0, =0x19B\n"
              "MOV     R1, #0x64\n"
              //"STRD     R0, [SP,#0x74-0x54]\n"        // "strd not supported by cpu" claims gcc
              "STR      R0, [SP,#0x74-0x54]\n"          // split in two single-word STRs
              "STR      R1, [SP,#0x74-0x50]\n"

              "MOV     R0, #0x78\n"
              //"STRD     R0, [SP,#0x74-0x4C]\n"        // "strd not supported by cpu" claims gcc
              "STR      R0, [SP,#0x74-0x4C]\n"          // split in two single-word STRs
              "STR      R1, [SP,#0x74-0x48]\n"

              "MOV     R0, #0\n"
              "STR     R0, [SP,#0x74-0x44]\n"
              "STR     R0, [SP,#0x74-0x40]\n"
              "MOV     R0, #0x10\n"
              "STR     R0, [SP,#0x74-0x18]\n"
              "MOV     R0, #0x800\n"
              "STR     R0, [SP,#0x74-0x14]\n"
              "MOV     R0, #0xA0\n"
              "STR     R0, [SP,#0x74-0x10]\n"
              "MOV     R0, #0x280\n"
              "STR     R0, [SP,#0x74-0x0C]\n"

              //"LDR     R1, =0xFFC04DA4\n"         // uHwSetup = 0xFFC04DA4
              "LDR     R1, =uHwSetup_my\n"         // followup to own function

              "MOV     R0, SP\n"
              "MOV     R2, #0\n"
              "BL      sub_FFC02D58\n"
              "ADD     SP, SP, #0x74\n"
              "LDR     PC, [SP],#4\n"
        );
}; //#fe

void __attribute__((naked,noinline)) uHwSetup_my() { //#fs
        asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FFC0094C\n"
              "BL      sub_FFC0972C\n"          // _dmSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xffc04eb8\n"       // FFC04EB8 aDmsetup
              "BLLT    sub_FFC04E98\n"          // FFC04E98  _err_init_task
              "BL      sub_FFC049C8\n"          // _termDriverInit
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EC0\n"       // aTermdriverinit
              "BLLT    sub_FFC04E98\n"          // FFC04E98  _err_init_task
              "LDR     R0, =0xFFc04ED0\n"       // a_term
              "BL      sub_FFC04AB4\n"          // _termDeviceCreate
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04ED8\n"       // aTermdevicecrea
              "BLLT    sub_FFC04E98\n"          // FFC04E98  _err_init_task
              "LDR     R0, =0xFFc04ED0\n"       // a_term
              "BL      sub_FFc03564\n"          // _stdioSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EEC\n"       // aStdiosetup
              "BLLT    sub_FFC04E98\n"          // FFC04E98  _err_init_task
              "BL      sub_FFc092B4\n"          // _stdlibSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EEC\n"       // aStdlibsetup
              "BLLT    sub_FFC04E98\n"          // FFC04E98  _err_init_task
              "BL      sub_FFC014B8\n"          // _armlib_setup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04F04\n"       // aArmlib_setup
              "BLLT    sub_FFC04E98\n"          // FFC04E98  _err_init_task
              "LDMFD   SP!, {R4,LR}\n"
              //"B       _CreateTaskStartup\n"   // FFC0DCDC
              "B       CreateTask_Startup_my\n"

        );
}; //#fe

void __attribute__((naked,noinline)) CreateTask_Startup_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R3,LR}\n"
                //"BL      j_nullsub_212\n"
                "BL      sub_FFC1979C\n"
                "CMP     R0, #0\n"

                // different from a720!!!
                /*
                "LDREQ   R0, =0xC0220000\n"
                "LDREQ   R1, [R0,#0xB8]\n"
                "TSTEQ   R1, #1\n"
                "BNE     loc_FFC0DD08\n"
                */
                "BNE     loc_FFC0CDB4\n"
                "BL      sub_FFC119D8\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC0CDB4\n"
                "LDR     R1, =0xC0220000\n"

                "MOV     R1, #0x44\n"
                "STR     R1, [R0,#0x4C]\n"
        "loc_FFC0CDB0:\n"
                "B       loc_FFC0CDB0\n"
        "loc_FFC0CDB4:\n"
                //"BL      j_nullsub_214\n"
                //"BL      j_nullsub_213\n"
                "BL      sub_FFC17B24\n"
                //different from a720!!!
                "LDR     R1, =0x2CE000\n"// ??? ?????? ??? 0x300000 ???-?? ????...
                "MOV     R0, #0\n"
                "BL      sub_FFC17D6C\n"
                "BL      sub_FFC17D18\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
                //"ADR     R3, sub_FFC0CD28\n"     //Startup
                "LDR     R3, =task_Startup_my\n"      // followup to own function
                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFFC0CDFC\n"
                "BL      sub_FFC0B8E0\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) task_Startup_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC051BC\n"  // uRegClockSave
                "BL      sub_FFC12B3C\n"
                "BL      sub_FFC0FE14\n"
                //"BL      j_nullsub_217\n"
                "BL      sub_FFC199A4\n"
                //"BL      sub_FFC19864\n"  // StartDiskboot
        );

        CreateTask_spytask();

        asm volatile (
                "BL      sub_FFC19B58\n"
                "BL      sub_FFC199F4\n"
                "BL      sub_FFC17064\n"
                "BL      sub_FFC19B5C\n"
        );

        CreateTask_PhySw();

        asm volatile (
                //"BL      sub_FFC118F0\n"        // CreateTask_PhySw - checks buttons and acts accordingly

                "BL      sub_FFC14A34_my\n"        // divert to intercept task_ShootSeqTask
                "BL      sub_FFC19B74\n"
                //"BL      nullsub_2\n"
                "BL      sub_FFC10DC4\n"
                "BL      sub_FFC19564\n"
                "BL      sub_FFC11420\n"
                "BL      sub_FFC10CC4\n"
                "BL      sub_FFC1A4C0\n" //TODO: m.b. comment
                //"BL      sub_FFC1A4C0_my\n"     // divert for SDHC-bootdisk-support //TODO: m.b. uncomment
                "BL      sub_FFC10C80\n"

                // modification: BL instead of B to last function to control action after its return
                "BL       sub_FFC05070\n"
                "LDMFD   SP!, {R4,PC}\n"        // restore stack to PC instead of LR to return to caller
        );
}; //#fe

void CreateTask_spytask() { //#fs
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

void CreateTask_PhySw() { //#fs
        _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC14A34_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x1C04\n"
                "MOV     R0, #0\n"
                "MOV     R1, #4\n"
                "STR     R0, [R4,#0xC]\n"
                "BL      sub_FFC0BC10\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #1\n"
                "BL      sub_FFC0BC34\n"
                "STR     R0, [R4,#8]\n"
                "BL      sub_FFC4C9A8\n"
                "BL      sub_FFC4DB7C\n"
                "BL      sub_FFC4BABC\n"
                "BL      sub_FFC48AAC_my\n"     // divert this for ShootSeqTask
                "BL      sub_FFC4CC68\n"
                "LDR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "MOV     R1, #0x1000\n"
                "B       sub_FFC173C8\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC48AAC_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x5270\n"
                "LDR     R0, [R4,#8]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC48B18\n"
                //"BL      nullsub_29\n"
                "MOV     R1, #1\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BC34\n"
                "STR     R0, [R4,#0xC]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC0BC10\n"
                "STR     R0, [R4,#0x10]\n"
                "BL      sub_FFC48DA4\n"
                "BL      sub_FFC492F4\n"   // continue here for task_ShootSeqTask (this is nonsense. We just need CaptSeqTask)
                "MOV     R0, #0\n"
                "STR     R0, [R4,#0x8]\n"
                "ADD     R0, R4, #0x14\n"
                "MOV     R1, #0\n"
                "STR     R1, [R0],#4\n"
                "STR     R1, [R0]\n"
                "BL      sub_FFC49494\n"
                "BL      sub_FFC4CE14\n"
                "BL      sub_FFC4B48C\n"
                "BL      sub_FFC49DC0_my\n"     // continue here for task_CaptSeqTask
                "BL      sub_FFC4AFD4\n"
        "loc_FFC48B18:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe
//UP!
void __attribute__((naked,noinline)) sub_FFC49DC0_my() { //#fs  // CreateTask_CaptSeqTask
        asm volatile (
                "STMFD   SP!, {R3-R5,LR}\n"
                "LDR     R2, =0x18320\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
        "loc_FFC49DD0:\n"
                "ADD     R3, R2, R0,LSL#4\n"
                "ADD     R0, R0, #1\n"
                "CMP     R0, #5\n"
                "STR     R1, [R3,#8]\n"
                "BCC     loc_FFC49DD0\n"
                "BL      sub_FFD0E290\n"
                "BL      sub_FFD0FE68\n"
                "MOV     R1, #5\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BBEC\n"
                "LDR     R4, =0x52A8\n"
                "LDR     R1, =0x1001FF\n"
                "STR     R0, [R4,#8]\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BC10\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #1\n"
                "BL      sub_FFC0BC34\n"
                "STR     R0, [R4,$0xC]\n"
                "MOV     R3, #0\n"
                //"STR     R3, [SP,#0x10+var_10]\n"
                "STR     R3, [SP]\n"
                //"LDR     R3, =0xFFC49B38\n"           // task_CaptSeqTask
                "LDR     R3, =task_CaptSeqTask_my\n"            // task_CaptSeqTask
                "LDR     R0, =0xFFC49EF4\n"             // aCaptseqtask ; "CaptSeqTask"
                "MOV     R2, #0x1000\n"
                "MOV     R1, #0x17\n"
                "BL      sub_FFC0BBB8\n"                // uKernelMiscCreateTask o. CreateTaskStrict
                "LDMFD   SP!, {R3-R5,PC}\n"
        ".ltorg\n"
        );
}; //#fe

