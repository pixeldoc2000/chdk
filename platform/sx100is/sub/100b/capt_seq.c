#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (2)
#define NR_OFF (1)

static long raw_save_stage;

void capt_seq_hook_raw_here()
{
    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available();
    while (raw_save_stage != RAWDATA_SAVED){
	_SleepTask(10);
    }
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}


void capt_seq_hook_set_nr()
{
    long *nrflag = (long*)0xA5FC;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = 1;
	break;
   case NOISE_REDUCTION_ON:
	*nrflag = 2;
	break;
    };
}

void __attribute__((naked,noinline)) sub_FFD15B24_my(){ 
 asm volatile(
                "STMFD   SP!, {R0-R10,LR}\n"
                "MOV     R6, #0\n"
                "MOV     R4, R0\n"
                "BL      sub_FFD16678\n"
                "MVN     R1, #0\n"
                "BL      sub_FFC19408\n"
                "MOV     R2, #4\n"
                "ADD     R1, SP, #8\n"
                "MOV     R0, #0x8A\n"
                "BL      sub_FFC5BC8C\n"
                "TST     R0, #1\n"
                "LDRNE   R1, =0x20A\n"
                "LDRNE   R0, =0xFFD15D2C\n"
                "BLNE    sub_FFC0C090\n"
                "LDR     R8, =0x1993C\n"
                "LDR     R5, =0x19890\n"
                "LDRSH   R1, [R8,#0xE]\n"
                "LDR     R0, [R5,#0x74]\n"
                "BL      sub_FFCDAF44\n"
                "BL      sub_FFC3A2AC\n"
                "LDR     R2, =0xA600\n"
                "ADD     R3, R4, #0x8C\n"
                "STRH    R0, [R4,#0x88]\n"
            //  "STRD    R2, [SP]\n"
                ".long	 0xE1CD20F0\n"
                "MOV     R1, R0\n"
                "LDRH    R0, [R5,#0x4C]\n"
                "LDRSH   R2, [R8,#0xC]\n"
                "LDR     R3, =0xA5FC\n"
                "BL      sub_FFD16B64\n"
                "BL      capt_seq_hook_set_nr\n"
                "B	 sub_FFD15B98\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC4DE14_my(){ 
 asm volatile(
                "STMFD   SP!, {R3-R7,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R5, =0x19890\n"
                "LDR     R0, [R4,#8]\n"
                "LDR     R6, =0x820A\n"
                "ORR     R0, R0, #1\n"
                "STR     R0, [R4,#8]\n"
                "LDRH    R0, [R5]\n"
                "CMP     R0, R6\n"
                "BEQ     loc_FFC4DEB0\n"
                "LDRH    R0, [R5,#0x7E]\n"
                "CMP     R0, #3\n"
                "BEQ     loc_FFC4DF14\n"
                "LDR     R0, [R4,#0xC]\n"
                "CMP     R0, #1\n"
                "BLS     loc_FFC4DEBC\n"
                "LDRH    R0, [R5,#0x7C]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC4DF14\n"
                "LDRH    R0, [R5,#0x78]\n"
                "CMP     R0, #2\n"
                "BNE     loc_FFC4DEC8\n"
                "BL      sub_FFD14538\n"
                "LDRH    R0, [R5]\n"
                "CMP     R0, R6\n"
                "BEQ     loc_FFC4DEB0\n"
                "LDRH    R0, [R5,#0x7E]\n"
                "CMP     R0, #3\n"
                "BEQ     loc_FFC4DF14\n"
                "LDR     R0, [R4,#0xC]\n"
                "CMP     R0, #1\n"
                "BLS     loc_FFC4DEBC\n"
                "LDRH    R0, [R5,#0x7C]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC4DF14\n"
                "LDRH    R0, [R5,#0x78]\n"
                "CMP     R0, #2\n"
                "BEQ     loc_FFC4DEF4\n"
                "B       loc_FFC4DEC8\n"
"loc_FFC4DEB0:\n"
                "LDRH    R0, [R5,#0x7E]\n"
                "CMP     R0, #3\n"
                "BEQ     loc_FFC4DF14\n"
"loc_FFC4DEBC:\n"
                "LDRH    R0, [R5,#0x7C]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC4DF14\n"
"loc_FFC4DEC8:\n"
                "LDRH    R0, [R5,#0x78]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC4DF14\n"
                "LDRH    R0, [R5]\n"
                "CMP     R0, R6\n"
                "LDRNE   R0, [R4,#0xC]\n"
                "CMPNE   R0, #1\n"
                "BLS     loc_FFC4DF14\n"
                "LDR     R0, [R4,#0x10]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC4DF14\n"
"loc_FFC4DEF4:\n"
                "LDR     R3, =0x20D\n"
                "LDR     R0, =0x5698\n"
                "STR     R3, [SP]\n"
                "LDR     R0, [R0,#0xC]\n"
                "LDR     R2, =0xEA60\n"
                "LDR     R3, =0xFFC4DD94\n"
                "MOV     R1, #0x40000000\n"
                "BL      sub_FFC518F4\n"
"loc_FFC4DF14:\n"
                "BL      sub_FFC4DCF8\n"
                "MOV     R0, #2\n"
                "BL      sub_FFC494FC\n"
                "BL      sub_FFD14154\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD147BC\n"
                "TST     R0, #1\n"
                "MOVNE   R2, R4\n"
                "LDMNEFD SP!, {R3-R7,LR}\n"
                "MOVNE   R1, #1\n"
                "BNE     sub_FFC4C740\n"
                "BL      sub_FFD27B0C\n"
                "BL      sub_FFC5BE1C\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD15A3C\n"
                "BL      sub_FFD1650C\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD15B24_my\n"         //----------->
                "BL      capt_seq_hook_raw_here\n"  //+
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BL      sub_FFC4C740\n"
                "BL      sub_FFD15F60\n"
                "CMP     R0, #0\n"
                "LDRNE   R0, [R4,#8]\n"
                "ORRNE   R0, R0, #0x2000\n"
                "STRNE   R0, [R4,#8]\n"
                "LDRH    R0, [R5,#0x7E]\n"
                "CMP     R0, #3\n"
                "BEQ     loc_FFC4DFA8\n"
                "LDRH    R0, [R5,#0x7C]\n"
                "CMP     R0, #0\n"
                "LDREQH  R0, [R5,#0x78]\n"
                "CMPEQ   R0, #2\n"
                "MOVEQ   R0, R4\n"
                "LDMEQFD SP!, {R3-R7,LR}\n"
                "BEQ     sub_FFD1458C\n"
"loc_FFC4DFA8:\n"
                "LDMFD   SP!, {R3-R7,PC}\n"
 );
}


void __attribute__((naked,noinline)) CaptSeqTask() //#fs
{
	asm volatile (
                "STMFD   SP!, {R3-R7,LR}\n"
                "LDR     R6, =0x5698\n"
"loc_FFC4E2B4:\n"
                "LDR     R0, [R6,#0x10]\n"
                "MOV     R2, #0\n"
                "MOV     R1, SP\n"
                "BL      sub_FFC19658\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFC4E2E0\n"
                "LDR     R1, =0x43F\n"
                "LDR     R0, =0xFFC4DD94\n"
                "BL      sub_FFC0C090\n"
                "BL      sub_FFC0BE48\n"
                "LDMFD   SP!, {R3-R7,PC}\n"
"loc_FFC4E2E0:\n"
                "LDR     R0, [SP]\n"
                "LDR     R1, [R0]\n"
                "CMP     R1, #0x1A\n"
                "ADDLS   PC, PC, R1,LSL#2\n"
                "B       loc_FFC4E488\n"
"loc_FFC4E2F4:\n"
                "B       loc_FFC4E360\n"
"loc_FFC4E2F8:\n"
                "B       loc_FFC4E368\n"
"loc_FFC4E2FC:\n"
                "B       loc_FFC4E370\n"
"loc_FFC4E300:\n"
                "B       loc_FFC4E384\n"
"loc_FFC4E304:\n"
                "B       loc_FFC4E37C\n"
"loc_FFC4E308:\n"
                "B       loc_FFC4E38C\n"
"loc_FFC4E30C:\n"
                "B       loc_FFC4E394\n"
"loc_FFC4E310:\n"
                "B       loc_FFC4E3A0\n"
"loc_FFC4E314:\n"
                "B       loc_FFC4E3F8\n"
"loc_FFC4E318:\n"
                "B       loc_FFC4E384\n"
"loc_FFC4E31C:\n"
                "B       loc_FFC4E400\n"
"loc_FFC4E320:\n"
                "B       loc_FFC4E408\n"
"loc_FFC4E324:\n"
                "B       loc_FFC4E410\n"
"loc_FFC4E328:\n"
                "B       loc_FFC4E418\n"
"loc_FFC4E32C:\n"
                "B       loc_FFC4E420\n"
"loc_FFC4E330:\n"
                "B       loc_FFC4E428\n"
"loc_FFC4E334:\n"
                "B       loc_FFC4E430\n"
"loc_FFC4E338:\n"
                "B       loc_FFC4E438\n"
"loc_FFC4E33C:\n"
                "B       loc_FFC4E440\n"
"loc_FFC4E340:\n"
                "B       loc_FFC4E448\n"
"loc_FFC4E344:\n"
                "B       loc_FFC4E450\n"
"loc_FFC4E348:\n"
                "B       loc_FFC4E45C\n"
"loc_FFC4E34C:\n"
                "B       loc_FFC4E468\n"
"loc_FFC4E350:\n"
                "B       loc_FFC4E470\n"
"loc_FFC4E354:\n"
                "B       loc_FFC4E478\n"
"loc_FFC4E358:\n"
                "B       loc_FFC4E480\n"
"loc_FFC4E35C:\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E360:\n"
                "BL      sub_FFD1419C\n"
                "BL      shooting_expo_param_override\n"  // +
                "B       loc_FFC4E398\n"
"loc_FFC4E368:\n"
                "BL      sub_FFC4DE14_my\n"     //---------------->
                "B       loc_FFC4E494\n"
"loc_FFC4E370:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD1432C\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E37C:\n"
                "BL      sub_FFD13E30\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E384:\n"
                "BL      sub_FFD14144\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E38C:\n"
                "BL      sub_FFD1414C\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E394:\n"
                "BL      sub_FFD1424C\n"
"loc_FFC4E398:\n"
                "BL      sub_FFC4C3A8\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E3A0:\n"
                "LDR     R4, [R0,#0xC]\n"
                "BL      sub_FFD14154\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD14BAC\n"
                "TST     R0, #1\n"
                "MOV     R5, R0\n"
                "BNE     loc_FFC4E3E0\n"
                "BL      sub_FFC5BE1C\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD15A3C\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD15FC0\n"
                "MOV     R5, R0\n"
                "LDR     R0, [R4,#0x14]\n"
                "BL      sub_FFC5C030\n"
"loc_FFC4E3E0:\n"
                "BL      sub_FFD14144\n"
                "MOV     R2, R4\n"
                "MOV     R1, #8\n"
                "MOV     R0, R5\n"
                "BL      sub_FFC4C740\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E3F8:\n"
                "BL      sub_FFD142A8\n"
                "B       loc_FFC4E398\n"
"loc_FFC4E400:\n"
                "BL      sub_FFD14E18\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E408:\n"
                "BL      sub_FFD14FD0\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E410:\n"
                "BL      sub_FFD15060\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E418:\n"
                "BL      sub_FFD15114\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E420:\n"
                "BL      sub_FFD153A0\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E428:\n"
                "BL      sub_FFD153F0\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E430:\n"
                "MOV     R0, #0\n"
                "B       loc_FFC4E454\n"
"loc_FFC4E438:\n"
                "BL      sub_FFD155B4\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E440:\n"
                "BL      sub_FFD15648\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E448:\n"
                "BL      sub_FFD15708\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E450:\n"
                "MOV     R0, #1\n"
"loc_FFC4E454:\n"
                "BL      sub_FFD15474\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E45C:\n"
                "BL      sub_FFD14478\n"
                "BL      sub_FFC4E5B0\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E468:\n"
                "BL      sub_FFD15230\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E470:\n"
                "BL      sub_FFD15308\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E478:\n"
                "BL      sub_FFC4DCF8\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E480:\n"
                "BL      sub_FFC15C28\n"
                "B       loc_FFC4E494\n"
"loc_FFC4E488:\n"
                "LDR     R1, =0x523\n"
                "LDR     R0, =0xFFC4DD94\n"
                "BL      sub_FFC0C090\n"
"loc_FFC4E494:\n"
                "LDR     R0, [SP]\n"
                "LDR     R1, [R0,#4]\n"
                "LDR     R0, [R6,#0xC]\n"
                "BL      sub_FFC193D4\n"
                "LDR     R4, [SP]\n"
                "LDR     R0, [R4,#8]\n"
                "CMP     R0, #0\n"
                "LDREQ   R0, =0xFFC4DD94\n"
                "MOVEQ   R1, #0xFC\n"
                "BLEQ    sub_FFC0C090\n"
                "MOV     R0, #0\n"
                "STR     R0, [R4,#8]\n"
                "B       loc_FFC4E2B4\n"
    );
} //#fe
