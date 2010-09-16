#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6DB0;    // ?!? ROM:FF970AA0 at taskcreate_ShutterSoundTask()

#include "../../../generic/capt_seq.c"

// ROM:FF87D2D8 task_CaptSeqTask()
//void __attribute__((naked,noinline)) capt_seq_task() {
void __attribute__((naked,noinline)) task_CaptSeqTask_my() {
    asm volatile (
            "STMFD   SP!, {R3-R9,LR}\n"
            "LDR     R6, =0x2C7C\n"
            "LDR     R4, =0x396C4\n"
            "MOV     R9, #1\n"
            "MOV     R7, #0\n"
        "loc_FF87D2EC:\n"
            "LDR     R0, [R6,#4]\n"
            "MOV     R2, #0\n"
            "MOV     R1, SP\n"
            "BL      sub_FF83994C\n"             // LOCATION: KerQueue.c:0
            "TST     R0, #1\n"
            "BEQ     loc_FF87D318\n"
            "LDR     R1, =0x5BE\n"
            "LDR     R0, =0xFF87CE68\n"          // "SsShootTask.c"
            "BL      sub_FF81EB14\n"             // DebugAssert()
            "BL      sub_FF81EACC\n"             // eventproc_export_ExitTask()
            "LDMFD   SP!, {R3-R9,PC}\n"
        "loc_FF87D318:\n"
            "LDR     R0, [SP]\n"
            "LDR     R1, [R0]\n"
            "CMP     R1, #0x1D\n"
            "ADDLS   PC, PC, R1,LSL#2\n"
            "B       loc_FF87D62C\n"
        "loc_FF87D32C:\n"
            "B       loc_FF87D3A4\n"
        "loc_FF87D330:\n"
            "B       loc_FF87D408\n"
        "loc_FF87D334:\n"
            "B       loc_FF87D4BC\n"
        "loc_FF87D338:\n"
            "B       loc_FF87D4D0\n"
        "loc_FF87D33C:\n"
            "B       loc_FF87D4C8\n"
        "loc_FF87D340:\n"
            "B       loc_FF87D4D8\n"
        "loc_FF87D344:\n"
            "B       loc_FF87D4E0\n"
        "loc_FF87D348:\n"
            "B       loc_FF87D4E8\n"
        "loc_FF87D34C:\n"
            "B       loc_FF87D540\n"
        "loc_FF87D350:\n"
            "B       loc_FF87D568\n"
        "loc_FF87D354:\n"
            "B       loc_FF87D54C\n"
        "loc_FF87D358:\n"
            "B       loc_FF87D558\n"
        "loc_FF87D35C:\n"
            "B       loc_FF87D560\n"
        "loc_FF87D360:\n"
            "B       loc_FF87D570\n"
        "loc_FF87D364:\n"
            "B       loc_FF87D578\n"
        "loc_FF87D368:\n"
            "B       loc_FF87D580\n"
        "loc_FF87D36C:\n"
            "B       loc_FF87D588\n"
        "loc_FF87D370:\n"
            "B       loc_FF87D590\n"
        "loc_FF87D374:\n"
            "B       loc_FF87D59C\n"
        "loc_FF87D378:\n"
            "B       loc_FF87D5A4\n"
        "loc_FF87D37C:\n"
            "B       loc_FF87D5AC\n"
        "loc_FF87D380:\n"
            "B       loc_FF87D5B4\n"
        "loc_FF87D384:\n"
            "B       loc_FF87D5BC\n"
        "loc_FF87D388:\n"
            "B       loc_FF87D5C8\n"
        "loc_FF87D38C:\n"
            "B       loc_FF87D5D0\n"
        "loc_FF87D390:\n"
            "B       loc_FF87D5D8\n"
        "loc_FF87D394:\n"
            "B       loc_FF87D5E0\n"
        "loc_FF87D398:\n"
            "B       loc_FF87D5E8\n"
        "loc_FF87D39C:\n"
            "B       loc_FF87D5F4\n"
        "loc_FF87D3A0:\n"
            "B       loc_FF87D638\n"
        "loc_FF87D3A4:\n"                        // jumptable FF87D324 entry 0
            "BL      sub_FF87DC9C\n"             // SsPrepareSeq.c
            "BL      sub_FF87AD78\n"
            "LDR     R0, [R4,#0x24]\n"
            "CMP     R0, #0\n"
            "BEQ     loc_FF87D638\n"
            "BL      sub_FF87CB48\n"
            "MOV     R5, R0\n"
            "LDR     R0, [R4,#0x24]\n"
            "CMP     R0, #0\n"
            "BEQ     loc_FF87D3EC\n"
            "MOV     R0, #0xC\n"
            "BL      sub_FF882264\n"
            "TST     R0, #1\n"
            "STRNE   R9, [R6,#0x10]\n"
            "LDRNE   R0, [R5,#8]\n"
            "ORRNE   R0, R0, #0x40000000\n"
            "STRNE   R0, [R5,#8]\n"
            "BNE     loc_FF87D638\n"
        "loc_FF87D3EC:\n"
            "MOV     R0, R5\n"
            "BL      sub_FF87CDEC\n"
            "MOV     R0, R5\n"
            "BL      sub_FF970A8C\n"             // taskcreate_ShutterSoundTask()
            "TST     R0, #1\n"
            "STRNE   R9, [R6,#0x10]\n"
            "B       loc_FF87D638\n"
        "loc_FF87D408:\n"                        // jumptable FF87D324 entry 1
            "LDR     R1, [R4,#0x24]\n"
            "CMP     R1, #0\n"
            "BNE     loc_FF87D4AC\n"
            "LDR     R1, [R4,#0xB0]\n"
            "CMP     R1, #1\n"
            "BNE     loc_FF87D488\n"
            "LDRH    R1, [R4]\n"
            "LDR     R12, =0x820C\n"
            "CMP     R1, R12\n"
            "LDRNEH  R1, [R4,#0x92]\n"
            "CMPNE   R1, #3\n"
            "LDRNE   R0, [R0,#0xC]\n"
            "LDRNE   R0, [R0,#0xC]\n"
            "CMPNE   R0, #1\n"
            "BLS     loc_FF87D458\n"
            "BL      sub_FF832E04\n"             // LOCATION: Battery.c:0
            "TST     R0, #1\n"
            "BEQ     loc_FF87D4AC\n"
            "BL      sub_FF8822CC\n"
            "B       loc_FF87D498\n"
        "loc_FF87D458:\n"
            "MOV     R0, #0xC\n"
            "BL      sub_FF882264\n"
            "TST     R0, #1\n"
            "BEQ     loc_FF87D4AC\n"
            "LDR     R0, [SP]\n"
            "MOV     R1, #1\n"
            "LDR     R2, [R0,#0xC]\n"
            "MOV     R0, #1\n"
            "BL      sub_FF87B788\n"             // LOCATION: SsShootCtrl.c:0
            "BL      sub_FF971700\n"
            "BL      sub_FF87B434\n"
            "B       loc_FF87D638\n"
        "loc_FF87D488:\n"
            "MOV     R0, #0xC\n"
            "BL      sub_FF882264\n"
            "TST     R0, #1\n"
            "BEQ     loc_FF87D4AC\n"
        "loc_FF87D498:\n"
            "LDR     R0, [SP]\n"
            "MOV     R1, #1\n"
            "LDR     R2, [R0,#0xC]\n"
            "MOV     R0, #1\n"
            "B       loc_FF87D538\n"
        "loc_FF87D4AC:\n"
            "LDR     R0, [SP]\n"
            "BL      sub_FF87D754\n"
        "loc_FF87D4B4:\n"
            "STR     R7, [R4,#0x24]\n"
            "B       loc_FF87D638\n"
        "loc_FF87D4BC:\n"                        // jumptable FF87D324 entry 2
            "MOV     R0, #1\n"
            "BL      sub_FF87DF40\n"             // LOCATION: SsPrepareSeq.c:0
            "B       loc_FF87D638\n"
        "loc_FF87D4C8:\n"                        // jumptable FF87D324 entry 4
            "BL      sub_FF87D924\n"
            "B       loc_FF87D4B4\n"
        "loc_FF87D4D0:\n"                        // jumptable FF87D324 entry 3
            "BL      sub_FF87DC7C\n"
            "B       loc_FF87D4B4\n"
        "loc_FF87D4D8:\n"                        // jumptable FF87D324 entry 5
            "BL      sub_FF87DC84\n"
            "B       loc_FF87D638\n"
        "loc_FF87D4E0:\n"                        // jumptable FF87D324 entry 6
            "BL      sub_FF87DE50\n"             // SsPrepareSeq.c 0
            "B       loc_FF87D544\n"
        "loc_FF87D4E8:\n"                        // jumptable FF87D324 entry 7
            "LDR     R5, [R0,#0xC]\n"
            "BL      sub_FF87DC8C\n"
            "MOV     R0, R5\n"
            "BL      sub_FF96F8A4\n"             // LOCATION: SsPrePreSeq.c:1024
            "TST     R0, #1\n"
            "MOV     R8, R0\n"
            "BNE     loc_FF87D528\n"
            "BL      sub_FF88F7F0\n"             // LOCATION: PropertyCase.c:0
            "STR     R0, [R5,#0x18]\n"
            "MOV     R0, R5\n"
            "BL      sub_FF9709A4\n"             // LOCATION: SsCaptureSeq.c:1
            "MOV     R0, R5\n"
            "BL      sub_FF970D48\n"             // LOCATION: SsCaptureSeq.c:0
            "MOV     R8, R0\n"
            "LDR     R0, [R5,#0x18]\n"
            "BL      sub_FF88FA28\n"             // LOCATION: PropertyCase.c:0
        "loc_FF87D528:\n"
            "BL      sub_FF87DC7C\n"
            "MOV     R2, R5\n"
            "MOV     R1, #9\n"
            "MOV     R0, R8\n"
        "loc_FF87D538:\n"
            "BL      sub_FF87B788\n"             // SsShootCtrl.c 0
            "B       loc_FF87D638\n"
        "loc_FF87D540:\n"                        // jumptable FF87D324 entry 8
            "BL      sub_FF87DEB8\n"             // SsPrepareSeq.c 0
        "loc_FF87D544:\n"
            "BL      sub_FF87AD78\n"
            "B       loc_FF87D638\n"
        "loc_FF87D54C:\n"                        // jumptable FF87D324 entry 10
            "LDR     R0, [R4,#0x54]\n"
            "BL      sub_FF87E3B0\n"             // SsMovieRec.c 186
            "B       loc_FF87D638\n"
        "loc_FF87D558:\n"                        // jumptable FF87D324 entry 11
            "BL      sub_FF87E688\n"             // SsMovieRec.c 2
            "B       loc_FF87D638\n"
        "loc_FF87D560:\n"                        // jumptable FF87D324 entry 12
            "BL      sub_FF87E720\n"             // SsMovieRec.c 632
            "B       loc_FF87D638\n"
        "loc_FF87D568:\n"                        // jumptable FF87D324 entry 9
            "BL      sub_FF87DC7C\n"
            "B       loc_FF87D638\n"
        "loc_FF87D570:\n"                        // jumptable FF87D324 entry 13
            "BL      sub_FF96FAD0\n"
            "B       loc_FF87D638\n"
        "loc_FF87D578:\n"                        // jumptable FF87D324 entry 14
            "BL      sub_FF96FCE4\n"
            "B       loc_FF87D638\n"
        "loc_FF87D580:\n"                        // jumptable FF87D324 entry 15
            "BL      sub_FF96FD7C\n"             // SsExpCompSeq.c 115
            "B       loc_FF87D638\n"
        "loc_FF87D588:\n"                        // jumptable FF87D324 entry 16
            "BL      sub_FF96FE4C\n"
            "B       loc_FF87D638\n"
        "loc_FF87D590:\n"                        // jumptable FF87D324 entry 17
            "MOV     R0, #0\n"
            "BL      sub_FF9700B4\n"
            "B       loc_FF87D638\n"
        "loc_FF87D59C:\n"                        // jumptable FF87D324 entry 18
            "BL      sub_FF970214\n"
            "B       loc_FF87D638\n"
        "loc_FF87D5A4:\n"                        // jumptable FF87D324 entry 19
            "BL      sub_FF9702B0\n"             // SsMFSeq.c 110
            "B       loc_FF87D638\n"
        "loc_FF87D5AC:\n"                        // jumptable FF87D324 entry 20
            "BL      sub_FF970390\n"             // SsMFSeq.c 188
            "B       loc_FF87D638\n"
        "loc_FF87D5B4:\n"                        // jumptable FF87D324 entry 21
            "BL      sub_FF87E0C8\n"
            "B       loc_FF87D638\n"
        "loc_FF87D5BC:\n"                        // jumptable FF87D324 entry 22
            "BL      sub_FF87E170\n"
            "BL      sub_FF83794C\n"
            "B       loc_FF87D638\n"
        "loc_FF87D5C8:\n"                        // jumptable FF87D324 entry 23
            "BL      sub_FF96FF18\n"
            "B       loc_FF87D638\n"
        "loc_FF87D5D0:\n"                        // jumptable FF87D324 entry 24
            "BL      sub_FF96FF84\n"             // SsChgExpSeq.c 440
            "B       loc_FF87D638\n"
        "loc_FF87D5D8:\n"                        // jumptable FF87D324 entry 25
            "BL      sub_FF880858\n"
            "B       loc_FF87D638\n"
        "loc_FF87D5E0:\n"                        // jumptable FF87D324 entry 26
            "BL      sub_FF8808E0\n"
            "B       loc_FF87D638\n"
        "loc_FF87D5E8:\n"                        // jumptable FF87D324 entry 27
            "BL      sub_FF88093C\n"
            "BL      sub_FF8808FC\n"
            "B       loc_FF87D638\n"
        "loc_FF87D5F4:\n"                        // jumptable FF87D324 entry 28
            "MOV     R0, #1\n"
            "BL      sub_FF971874\n"
            "MOV     R0, #1\n"
            "BL      sub_FF9719A8\n"
            "LDRH    R0, [R4,#0x94]\n"
            "CMP     R0, #4\n"
            "LDRNEH  R0, [R4]\n"
            "SUBNE   R12, R0, #0x8200\n"
            "SUBNES  R12, R12, #0x2A\n"
            "BNE     loc_FF87D638\n"
            "BL      sub_FF8808E0\n"
            "BL      sub_FF880E50\n"
            "BL      sub_FF880D60\n"             // LOCATION: SsLiveFunc.c:0
            "B       loc_FF87D638\n"
        "loc_FF87D62C:\n"                        // jumptable FF87D324 default entry
            "LDR     R1, =0x72C\n"
            //"ADR     R0, 0xFF87CE68\n"         // "SsShootTask.c"
            "LDR     R0, =0xFF87CE68\n"          // compiler does not like ADR
            "BL      sub_FF81EB14\n"             // DebugAssert()
            "loc_FF87D638:\n"                    // jumptable FF87D324 entry 29
            "LDR     R0, [SP]\n"
            "LDR     R1, [R0,#4]\n"
            "LDR     R0, [R6]\n"
            "BL      sub_FF8873E4\n"
            "LDR     R5, [SP]\n"
            "LDR     R0, [R5,#8]\n"
            "CMP     R0, #0\n"
            "LDREQ   R1, =0x132\n"
            "LDREQ   R0, =0xFF87CE68\n"          // "SsShootTask.c"
            "BLEQ    sub_FF81EB14\n"             // DebugAssert()
            "STR     R7, [R5,#8]\n"
            "B       loc_FF87D2EC\n"
     );
}
