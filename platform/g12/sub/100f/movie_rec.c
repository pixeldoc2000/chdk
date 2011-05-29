#include "conf.h"

void change_video_tables(int a, int b){
}

void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// @ FF987094
void __attribute__((naked,noinline)) movie_record_task(){ 

 asm volatile(
"                STMFD   SP!, {R2-R8,LR} \n"
"                LDR     R8, =0x2710 \n"
"                LDR     R4, =0x7290 \n"
"                MOV     R7, #1 \n"
"                LDR     R6, =0xFF986D84 \n"
"                MOV     R5, #0 \n"

"loc_FF9870AC: \n"
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
"                BNE     loc_FF9871C4 \n"
"                LDR     R0, [SP,#4] \n"
"                LDR     R1, [R0] \n"
"                SUB     R1, R1, #2 \n"
"                CMP     R1, #0xA \n"
"                ADDLS   PC, PC, R1,LSL#2 \n"

"                B       loc_FF9871C4 \n"
"loc_FF9870F0: \n"
"                B       loc_FF987178 \n"
"loc_FF9870F4: \n"
"                B       loc_FF987198 \n"
"loc_FF9870F8: \n"
"                B       loc_FF9871A8 \n"
"loc_FF9870FC: \n"
"                B       loc_FF9871B0 \n"
"loc_FF987100: \n"
"                B       loc_FF987180 \n"
"loc_FF987104: \n"
"                B       loc_FF9871B8 \n"
"loc_FF987108: \n"
"                B       loc_FF987188 \n"
"loc_FF98710C: \n"
"                B       loc_FF9871C4 \n"
"loc_FF987110: \n"
"                B       loc_FF9871C0 \n"
"loc_FF987114: \n"
"                B       loc_FF987148 \n"
"loc_FF987118: \n"
"                B       loc_FF98711C \n"

"loc_FF98711C: \n"
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
"                B       loc_FF987164 \n"

"loc_FF987148: \n"
//"; jumptable entry 9 \n"
"                STR     R5, [R4,#0x40] \n"
"                STR     R5, [R4,#0x30] \n"
"                STR     R6, [R4,#0xB4] \n"
"                LDR     R0, [R4,#0xC] \n"
"                ADD     R0, R0, #1 \n"
"                STR     R0, [R4,#0xC] \n"
"                STR     R7, [R4,#0x44] \n"

"loc_FF987164: \n"
"                LDR     R2, =0xFF985F9C \n"
"                LDR     R1, =0xB3E0C \n"
"                LDR     R0, =0xFF986098 \n"
"                BL      sub_FF8532D0 \n"
"                B       loc_FF9871C4 \n"

"loc_FF987178: \n"
//"; jumptable entry 0            ; LOCATION: MovieRecorder.c:0 \n"

"		BL	unlock_optical_zoom\n" 			// added to unlock the zoom

"                BL      sub_FF986EAC \n"
"                B       loc_FF9871C4 \n"

"loc_FF987180: \n"
//"; jumptable entry 4            ; LOCATION: MovieRecorder.c:2032 \n"
"                BL      sub_FF9867EC \n"

                "LDR     R0, =0x7318-4\n" // <----   -4 //+ set in sub_FF9867EC above
                "BL      set_quality\n"                 //+ reset here to user value

"                B       loc_FF9871C4 \n"

"loc_FF987188: \n"
//"; jumptable entry 6 \n"
"				LDR		R1, [R0,#0x18] \n"
"				LDR		R0, [R0,#4] \n"
"                BL      sub_FFB00134 \n"
"                B       loc_FF9871C4 \n"

"loc_FF987198: \n"
//"; jumptable entry 1 \n"
"                LDR     R0, [R4,#0x44] \n"
"                CMP     R0, #5 \n"
"                STRNE   R7, [R4,#0x34] \n"
"                B       loc_FF9871C4 \n"

"loc_FF9871A8: \n"
//"; jumptable entry 2            ; LOCATION: MovieRecorder.c:1000 \n"
"                BL      sub_FF986434 \n"
"                B       loc_FF9871C4 \n"

"loc_FF9871B0: \n"
//"; jumptable entry 3            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF9860E4 \n"
"                B       loc_FF9871C4 \n"

"loc_FF9871B8: \n"
//"; jumptable entry 5            ; LOCATION: MovieRecorder.c:100 \n"
"                BL      sub_FF985F28 \n"
"                B       loc_FF9871C4 \n"

"loc_FF9871C0: \n"
//"; jumptable entry 8            ; LOCATION: MovieRecorder.c:0 \n"
"                BL      sub_FF9875F4 \n"

"loc_FF9871C4: \n"
//"; jumptable default entry \n"
//"; jumptable entry 7 \n"
"                LDR     R1, [SP,#4] \n"
"				 MOV	 R3, #0x5F0 \n"
"                STR     R5, [R1] \n"
"                STR     R3, [SP] \n"
"                LDR     R0, [R4,#0x28] \n"
"                LDR     R3, =0xFF985D8C \n" //;aMovierecorder_
"                MOV     R2, R8 \n"
"                BL      sub_FF83ADB4 \n"
"                B       loc_FF9870AC \n"
 );
}

