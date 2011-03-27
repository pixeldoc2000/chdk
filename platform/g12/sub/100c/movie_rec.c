#include "conf.h"

void change_video_tables(int a, int b){
}

void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// @ FF987088
void __attribute__((naked,noinline)) movie_record_task(){ 

 asm volatile(
"                STMFD   SP!, {R2-R10,LR} \n"
"                LDR     R9, =0x5EE \n"
"                LDR     R8, =0x2710 \n"
"                LDR     R4, =0x7290 \n"
"                MOV     R7, #1 \n"
"                LDR     R6, =0xFF986D90 \n"
"                MOV     R5, #0 \n"

"loc_FF9870A4: \n"
"                LDR     R0, [R4,#0x24] \n"
"                MOV     R2, #0 \n"
"                ADD     R1, SP, #4 \n"
"                BL      sub_FF83A460 \n"
"                LDR     R0, [R4,#0x2C] \n"
"                CMP     R0, #0 \n"
"                LDRNE   R0, [R4,#0xC] \n"
"                CMPNE   R0, #2 \n"
"                LDRNE   R0, [R4,#0x44] \n"
"                CMPNE   R0, #6 \n"
"                BNE     loc_FF9871BC \n"
"                LDR     R0, [SP,#4] \n"
"                LDR     R1, [R0] \n"
"                SUB     R1, R1, #2 \n"
"                CMP     R1, #0xA \n"
"                ADDLS   PC, PC, R1,LSL#2 \n"

"                B       loc_FF9871BC \n"
"loc_FF9870E8: \n"
"                B       loc_FF987170 \n"
"loc_FF9870EC: \n"
"                B       loc_FF987190 \n"
"loc_FF9870F0: \n"
"                B       loc_FF9871A0 \n"
"loc_FF9870F4: \n"
"                B       loc_FF9871A8 \n"
"loc_FF9870F8: \n"
"                B       loc_FF987178 \n"
"loc_FF9870FC: \n"
"                B       loc_FF9871B0 \n"
"loc_FF987100: \n"
"                B       loc_FF987180 \n"
"loc_FF987104: \n"
"                B       loc_FF9871BC \n"
"loc_FF987108: \n"
"                B       loc_FF9871B8 \n"
"loc_FF98710C: \n"
"                B       loc_FF987140 \n"
"loc_FF987110: \n"
"                B       loc_FF987114 \n"

"loc_FF987114: \n"
//"; jumptable entry 10 \n"
"                STR     R5, [R4,#0x40] \n"
"                STR     R5, [R4,#0x30] \n"
"                STR     R5, [R4,#0x34] \n"
"                STRH    R5, [R4,#6] \n"
"                STR     R6, [R4,#0xB4] \n"
"                LDR     R0, [R4,#0xC] \n"
"                ADD     R0, R0, #1 \n"
"                STR     R0, [R4,#0xC] \n"
"                MOV     R0, #6 \n"
"                STR     R0, [R4,#0x44] \n"
"                B       loc_FF98715C \n"

"loc_FF987140: \n"
//"; jumptable entry 9 \n"
"                STR     R5, [R4,#0x40] \n"
"                STR     R5, [R4,#0x30] \n"
"                STR     R6, [R4,#0xB4] \n"
"                LDR     R0, [R4,#0xC] \n"
"                ADD     R0, R0, #1 \n"
"                STR     R0, [R4,#0xC] \n"
"                STR     R7, [R4,#0x44] \n"

"loc_FF98715C: \n"
"                LDR     R2, =0xFF985FA4 \n"
"                LDR     R1, =0xB3E0C \n"
"                LDR     R0, =0xFF9860A0 \n"
"                BL      sub_FF8532D0 \n"
"                B       loc_FF9871BC \n"

"loc_FF987170: \n"
//"; jumptable entry 0            ; LOCATION: MovieRecorder.c:0 \n"

"		BL	unlock_optical_zoom\n" 			// added to unlock the zoom

"                BL      sub_FF986EA0 \n"
"                B       loc_FF9871BC \n"

"loc_FF987178: \n"
//"; jumptable entry 4            ; LOCATION: MovieRecorder.c:2032 \n"
"                BL      sub_FF9867F8 \n"

                "LDR     R0, =0x7318-4\n" // <----   -4 //+ set in sub_FF9867F8 above
                "BL      set_quality\n"                 //+ reset here to user value

"                B       loc_FF9871BC \n"

"loc_FF987180: \n"
//"; jumptable entry 6 \n"
"				LDR		R1, [R0,#0x18] \n"
"				LDR		R0, [R0,#4] \n"
"                BL      sub_FFAFFF84 \n"
"                B       loc_FF9871BC \n"

"loc_FF987190: \n"
//"; jumptable entry 1 \n"
"                LDR     R0, [R4,#0x44] \n"
"                CMP     R0, #5 \n"
"                STRNE   R7, [R4,#0x34] \n"
"                B       loc_FF9871BC \n"

"loc_FF9871A0: \n"
//"; jumptable entry 2            ; LOCATION: MovieRecorder.c:1000 \n"
"                BL      sub_FF986440 \n"
"                B       loc_FF9871BC \n"

"loc_FF9871A8: \n"
//"; jumptable entry 3            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF9860EC \n"
"                B       loc_FF9871BC \n"

"loc_FF9871B0: \n"
//"; jumptable entry 5            ; LOCATION: MovieRecorder.c:100 \n"
"                BL      sub_FF985F30 \n"
"                B       loc_FF9871BC \n"

"loc_FF9871B8: \n"
//"; jumptable entry 8            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF9875E4 \n"

"loc_FF9871BC: \n"
//"; jumptable default entry \n"
//"; jumptable entry 7 \n"
"                LDR     R1, [SP,#4] \n"
"                STR     R5, [R1] \n"
"                LDR     R3, =0xFF985D8C \n" //;aMovierecorder_
"                MOV     R2, R8 \n"
"                STR     R9, [SP] \n"
"                LDR     R0, [R4,#0x28] \n"
"                BL      sub_FF83ADB4 \n"
"                B       loc_FF9870A4 \n"
 );
}

