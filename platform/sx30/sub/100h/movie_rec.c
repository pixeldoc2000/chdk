#include "conf.h"

void change_video_tables(int a, int b){
}

void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// @ FF883348
void __attribute__((naked,noinline)) movie_record_task(){ 

 asm volatile(
"                STMFD   SP!, {R2-R10,LR} \n"
"                LDR     R9, =0x5AA \n"
"                LDR     R8, =0x2710 \n"
"                LDR     R4, =0x34E0 \n"
"                LDR     R7, =0xFF882FC4 \n"
"                MOV     R6, #0 \n"
"                MOV     R5, #1 \n"
"                ADD     R10, R9, #0x44 \n"

"loc_FF883368: \n"
"                LDR     R0, [R4,#0x24] \n"
"                MOV     R2, #0 \n"
"                ADD     R1, SP, #4 \n"
"                BL      sub_FF83A4C8 \n"
"                LDR     R2, =0xFF881594 \n"	// aMovierecorder_
"                LDR     R0, [R4,#0xD0] \n"
"                MOV     R3, R9 \n"
"                MOV     R1, R8 \n"
"                BL      _takeSemaphore \n"
"                LDR     R0, [R4,#0x2C] \n"
"                CMP     R0, #0 \n"
"                LDRNE   R0, [R4,#0xC] \n"
"                CMPNE   R0, #2 \n"
"                LDRNE   R0, [R4,#0x44] \n"
"                CMPNE   R0, #6 \n"
"                BNE     loc_FF8834B0 \n"
"                LDR     R0, [SP,#4] \n"
"                LDR     R1, [R0] \n"
"                SUB     R1, R1, #2 \n"
"                CMP     R1, #0xC \n"
"                ADDLS   PC, PC, R1,LSL#2 \n"
"                B       loc_FF8834B0 \n"
"loc_FF8833C0: \n"
"                B       loc_FF883458 \n"
"loc_FF8833C4: \n"
"                B       loc_FF883470 \n"
"loc_FF8833C8: \n"
"                B       loc_FF883480 \n"
"loc_FF8833CC: \n"
"                B       loc_FF883488 \n"
"loc_FF8833D0: \n"
"                B       loc_FF883460 \n"
"loc_FF8833D4: \n"
"                B       loc_FF883490 \n"
"loc_FF8833D8: \n"
"                B       loc_FF883468 \n"
"loc_FF8833DC: \n"
"                B       loc_FF8834B0 \n"
"loc_FF8833E0: \n"
"                B       loc_FF8834A0 \n"
"loc_FF8833E4: \n"
"                B       loc_FF8834A8 \n"
"loc_FF8833E8: \n"
"                B       loc_FF883498 \n"
"loc_FF8833EC: \n"
"                B       loc_FF883420 \n"
"loc_FF8833F0: \n"
"                B       loc_FF8833F4 \n"

"loc_FF8833F4: \n"
//"; jumptable FF8833B8 entry 12 \n"
"                STR     R6, [R4,#0x40] \n"
"                STR     R6, [R4,#0x30] \n"
"                STR     R6, [R4,#0x34] \n"
"                STRH    R6, [R4,#6] \n"
"                STR     R7, [R4,#0xB4] \n"
"                LDR     R0, [R4,#0xC] \n"
"                ADD     R0, R0, #1 \n"
"                STR     R0, [R4,#0xC] \n"
"                MOV     R0, #6 \n"
"                STR     R0, [R4,#0x44] \n"
"                B       loc_FF883444 \n"

"loc_FF883420: \n"
//"; jumptable FF8833B8 entry 11 \n"
"                LDR     R0, =0xFF882FC4 \n"
"                STR     R6, [R4,#0x40] \n"
"                STR     R0, [R4,#0xBC] \n"
"                STR     R6, [R4,#0x30] \n"
"                STR     R7, [R4,#0xB4] \n"
"                LDR     R0, [R4,#0xC] \n"
"                ADD     R0, R0, #1 \n"
"                STR     R0, [R4,#0xC] \n"
"                STR     R5, [R4,#0x44] \n"

"loc_FF883444: \n"
"                LDR     R2, =0xFF881ADC \n"
"                LDR     R1, =0x3B7E8 \n"
"                LDR     R0, =0xFF881C04 \n"
"                BL      sub_FF852E4C \n"
"                B       loc_FF8834B0 \n"

"loc_FF883458: \n"
//"; jumptable FF8833B8 entry 0            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF883104 \n"
"                B       loc_FF8834B0 \n"

"loc_FF883460: \n"
//"; jumptable FF8833B8 entry 4            ; LOCATION: MovieRecorder.c:2032 \n"
"                BL      sub_FF8829D4 \n"

                "LDR     R0, =0x3568-4\n" // <----   -4 //+ set in sub_FF8829D4 above
                "BL      set_quality\n"                 //+ reset here to user value

"                B       loc_FF8834B0 \n"

"loc_FF883468: \n"
//"; jumptable FF8833B8 entry 6 \n"
"                BL      sub_FF8839C0 \n"
"                B       loc_FF8834B0 \n"

"loc_FF883470: \n"
//"; jumptable FF8833B8 entry 1 \n"
"                LDR     R0, [R4,#0x44] \n"
"                CMP     R0, #5 \n"
"                STRNE   R5, [R4,#0x34] \n"
"                B       loc_FF8834B0 \n"

"loc_FF883480: \n"
//"; jumptable FF8833B8 entry 2            ; LOCATION: MovieRecorder.c:1000 \n"
"                BL      sub_FF882670 \n"
"                B       loc_FF8834B0 \n"

"loc_FF883488: \n"
//"; jumptable FF8833B8 entry 3            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF8822E4 \n"
"                B       loc_FF8834B0 \n"

"loc_FF883490: \n"
//"; jumptable FF8833B8 entry 5            ; LOCATION: MovieRecorder.c:100 \n"
"                BL      sub_FF881A64 \n"
"                B       loc_FF8834B0 \n"

"loc_FF883498: \n"
//"; jumptable FF8833B8 entry 10           ; LOCATION: MovieRecorder.c:100 \n"
"                BL      sub_FF883914 \n"
"                B       loc_FF8834B0 \n"

"loc_FF8834A0: \n"
//"; jumptable FF8833B8 entry 8            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF8821A8 \n"
"                B       loc_FF8834B0 \n"

"loc_FF8834A8: \n"
//"; jumptable FF8833B8 entry 9            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF88208C \n"
"                STR     R5, [R4,#0xF8] \n"

"loc_FF8834B0: \n"
//"; jumptable FF8833B8 default entry \n"
//"; jumptable FF8833B8 entry 7 \n"
"                LDR     R1, [SP,#4] \n"
"                LDR     R3, =0xFF881594 \n" //;aMovierecorder_
"                STR     R6, [R1] \n"
"                STR     R10, [SP] \n"
"                LDR     R0, [R4,#0x28] \n"
"                MOV     R2, R8 \n"
"                BL      sub_FF83AE1C \n"
"                LDR     R0, [R4,#0xD0] \n"
"                BL      _eventproc_export_GiveSemaphore \n" // ; LOCATION: KerSem.c:0 \n"
"                B       loc_FF883368 \n"
 );
}

