#include "lolevel.h"
#include "platform.h"
#include "core.h"
//#include "stdlib.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;


// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

/*----------------------------------------------------------------------
	taskCreateHook()
-----------------------------------------------------------------------*/

void taskCreateHook(context_t **context) { 
 task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

// physw is done directly to avoid wasting stack space
// if(!_strcmp(tcb->name, "PhySw"))           tcb->entry = (void*)mykbd_task; 
 if(!_strcmp(tcb->name, "CaptSeqTask"))     tcb->entry = (void*)capt_seq_task; 
 if(!_strcmp(tcb->name, "InitFileModules")) tcb->entry = (void*)init_file_modules_task;
 if(!_strcmp(tcb->name, "ExpDrvTask"))      tcb->entry = (void*)exp_drv_task;
 if(!_strcmp(tcb->name, "RotaryEncoder"))   tcb->entry = (void*)JogDial_task_my;
 if(!_strcmp(tcb->name, "MovieRecord"))     tcb->entry = (void*)movie_record_task;
}

/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) boot()
{

    asm volatile (
	
"		LDR	R1, =0xC0410000 \n"
"		MOV	R0, #0 \n"
"		STR	R0, [R1] \n"
"		MOV	R1, #0x78 \n"
"		MCR	p15, 0,	R1,c1,c0 \n"
"		MOV	R1, #0 \n"
"		MCR	p15, 0,	R1,c7,c10, 4 \n"
"		MCR	p15, 0,	R1,c7,c5 \n"
"		MCR	p15, 0,	R1,c7,c6 \n"
"		MOV	R0, #0x3D \n"
"		MCR	p15, 0,	R0,c6,c0 \n"
"		MOV	R0, #0xC000002F \n"
"		MCR	p15, 0,	R0,c6,c1 \n"
"		MOV	R0, #0x33 \n"
"		MCR	p15, 0,	R0,c6,c2 \n"
"		MOV	R0, #0x40000033 \n"
"		MCR	p15, 0,	R0,c6,c3 \n"
"		MOV	R0, #0x80000017 \n"
"		MCR	p15, 0,	R0,c6,c4 \n"
"		LDR	R0, =0xFF80002D \n"
"		MCR	p15, 0,	R0,c6,c5 \n"
"		MOV	R0, #0x34 \n"
"		MCR	p15, 0,	R0,c2,c0 \n"
"		MOV	R0, #0x34 \n"
"		MCR	p15, 0,	R0,c2,c0, 1 \n"
"		MOV	R0, #0x34 \n"
"		MCR	p15, 0,	R0,c3,c0 \n"
"		LDR	R0, =0x3333330 \n"
"		MCR	p15, 0,	R0,c5,c0, 2 \n"
"		LDR	R0, =0x3333330 \n"
"		MCR	p15, 0,	R0,c5,c0, 3 \n"
"		MRC	p15, 0,	R0,c1,c0 \n"
"		ORR	R0, R0,	#0x1000 \n"
"		ORR	R0, R0,	#4 \n"
"		ORR	R0, R0,	#1 \n"
"		MCR	p15, 0,	R0,c1,c0 \n"
"		MOV	R1, #0x80000006 \n"
"		MCR	p15, 0,	R1,c9,c1 \n"
"		MOV	R1, #6 \n"
"		MCR	p15, 0,	R1,c9,c1, 1 \n"
"		MRC	p15, 0,	R1,c1,c0 \n"
"		ORR	R1, R1,	#0x50000 \n"
"		MCR	p15, 0,	R1,c1,c0 \n"
"		LDR	R2, =0xC0200000 \n"
"		MOV	R1, #1 \n"
"		STR	R1, [R2,#0x10C] \n"
"		MOV	R1, #0xFF \n"
"		STR	R1, [R2,#0xC] \n"
"		STR	R1, [R2,#0x1C] \n"
"		STR	R1, [R2,#0x2C] \n"
"		STR	R1, [R2,#0x3C] \n"
"		STR	R1, [R2,#0x4C] \n"
"		STR	R1, [R2,#0x5C] \n"
"		STR	R1, [R2,#0x6C] \n"
"		STR	R1, [R2,#0x7C] \n"
"		STR	R1, [R2,#0x8C] \n"
"		STR	R1, [R2,#0x9C] \n"
"		STR	R1, [R2,#0xAC] \n"
"		STR	R1, [R2,#0xBC] \n"
"		STR	R1, [R2,#0xCC] \n"
"		STR	R1, [R2,#0xDC] \n"
"		STR	R1, [R2,#0xEC] \n"
"		STR	R1, [R2,#0xFC] \n"
"		LDR	R1, =0xC0400008 \n"
"		LDR	R2, =0x430005 \n"
"		STR	R2, [R1] \n"
"		MOV	R1, #1 \n"
"		LDR	R2, =0xC0243100 \n"
"		STR	R2, [R1] \n"
"		LDR	R2, =0xC0242010 \n"
"		LDR	R1, [R2] \n"
"		ORR	R1, R1,	#1 \n"
"		STR	R1, [R2] \n"
"		LDR	R0, =0xFFC08428 \n"
"		LDR	R1, =0x1900 \n"
"		LDR	R3, =0xEE70 \n"
"loc_FF81013C: \n"
"		CMP	R1, R3 \n"
"		LDRCC	R2, [R0],#4 \n"
"		STRCC	R2, [R1],#4 \n"
"		BCC	loc_FF81013C \n"
"		LDR	R1, =0x166210 \n"
"		MOV	R2, #0 \n"
"loc_FF810154: \n"
"		CMP	R3, R1 \n"
"		STRCC	R2, [R3],#4 \n"
"		BCC	loc_FF810154 \n"
//"		B	loc_FF810354 \n"
"		B	loc_FF810354_my \n"		// patched --------------->		
		
    );
};

void __attribute__((naked,noinline)) loc_FF810354_my() {

    //*(int*)0x1934 = (int)taskCreateHook;
    *(int*)0x1938 = (int)taskCreateHook;
    *(int*)0x193C = (int)taskCreateHook;
    
	
	// SX130 @FF85F4F8

	// fix for correct power-on
	// must also comment out function in taskcreate_Startup_my
	//SX130
	if ((*(int*) 0xC0220118) & 1)			// look at play switch
		*(int*)(0x2478) = 0x100000;		// start in play mode
	else
		*(int*)(0x2478) = 0x200000;		// start in rec mode	
	
	
	asm volatile (
	
"		LDR	R0, =0xFF8103CC \n"
"		MOV	R1, #0 \n"
"		LDR	R3, =0xFF810404 \n"
"loc_FF810360: \n"
"		CMP	R0, R3 \n"
"		LDRCC	R2, [R0],#4 \n"
"		STRCC	R2, [R1],#4 \n"
"		BCC	loc_FF810360 \n"
"		LDR	R0, =0xFF810404 \n"
"		MOV	R1, #0x4B0 \n"
"		LDR	R3, =0xFF810618 \n"
"loc_FF81037C: \n"
"		CMP	R0, R3 \n"
"		LDRCC	R2, [R0],#4 \n"
"		STRCC	R2, [R1],#4 \n"
"		BCC	loc_FF81037C \n"
"		MOV	R0, #0xD2 \n"
"		MSR	CPSR_cxsf, R0 \n"
"		MOV	SP, #0x1000 \n"
"		MOV	R0, #0xD3 \n"
"		MSR	CPSR_cxsf, R0 \n"
"		MOV	SP, #0x1000 \n"
"		LDR	R0, =0x6C4 \n"
"		LDR	R2, =0xEEEEEEEE \n"
"		MOV	R3, #0x1000 \n"
"loc_FF8103B0: \n"
"		CMP	R0, R3 \n"
"		STRCC	R2, [R0],#4 \n"
"		BCC	loc_FF8103B0 \n"
//"		BL	sub_FF811198 \n"
"		BL	sub_FF811198_my \n"		// patched  ------------->
	

  );
}

void __attribute__((naked,noinline)) sub_FF811198_my() {

	asm volatile (
	
"		STR	LR, [SP,#-4]! \n"
"		SUB	SP, SP,	#0x74 \n"
"		MOV	R0, SP \n"
"		MOV	R1, #0x74 \n"
"		BL	sub_FFB4A170 \n"
"		MOV	R0, #0x53000 \n"
"		STR	R0, [SP,#0x4] \n"

// Use original heap address - CHDK loaded at 0xF000000
// Loading CHDK at 0x166210 leaves too little memory and camera crashes
"		LDR	R0, =0x166210 \n"
//"		LDR	R0, =new_sa \n"			// added -------------->
//"		LDR	R0, [R0] \n"			// added -------------->

"		LDR	R1, =0x2F9C00 \n"
"		STR	R0, [SP,#0x8] \n"
"		RSB	R0, R0,	#0x1F80 \n"
"		ADD	R0, R0,	#0x2F0000 \n"
"		STR	R0, [SP,#0xC] \n"
"		LDR	R0, =0x2F1F80 \n"
"		STR	R1, [SP,#0x0] \n"
"		STRD	R0, [SP,#0x10] \n"
"		MOV	R0, #0x22 \n"
"		STR	R0, [SP,#0x18] \n"
"		MOV	R0, #0x68 \n"
"		STR	R0, [SP,#0x1C] \n"
"		LDR	R0, =0x19B \n"
//"		LDR	R1, =sub_FF815EE0 \n"
"		LDR	R1, =sub_FF815EE0_my \n"	// patched -------------->

"		B	sub_FF8111F0 \n " 		// Return to firmware ----------->

	);
}

void __attribute__((naked,noinline)) sub_FF815EE0_my() {
	asm volatile (
	
"		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF810B20 \n"
"		BL	sub_FF81A33C \n"
"		CMP	R0, #0 \n"
//"		ADRLT	R0, aDmsetup \n"	// "dmSetup"
"		LDRLT	R0, =0xFF815FF4 \n"
"		BLLT	sub_FF815FD4 \n" // err_init_task
"		BL	sub_FF815B1C \n"
"		CMP	R0, #0 \n"
//"		ADRLT	R0, aTermdriverinit \n" // "termDriverInit"
"		LDRLT	R0, =0xFF815FFC \n"
"		BLLT	sub_FF815FD4 \n" // err_init_task
//"		ADR	R0, a_term \n"	// "/_term"
"		LDR	R0, =0xFF81600C \n"
"		BL	sub_FF815C04 \n"
"		CMP	R0, #0 \n"
//"		ADRLT	R0, aTermdevicecrea \n" // "termDeviceCreate"
"		LDRLT	R0, =0xFF816014 \n"
"		BLLT	sub_FF815FD4 \n" // err_init_task
//"		ADR	R0, a_term \n"	// "/_term"
"		LDR	R0, =0xFF81600C \n"
"		BL	sub_FF813CA4 \n"
"		CMP	R0, #0 \n"
//"		ADRLT	R0, aStdiosetup \n"	// "stdioSetup"
"		LDRLT	R0, =0xFF816028 \n" 
"		BLLT	sub_FF815FD4 \n" // err_init_task
"		BL	sub_FF819CC4 \n"
"		CMP	R0, #0 \n"
//"		ADRLT	R0, aStdlibsetup \n" // "stdlibSetup"
"		LDRLT	R0, =0xFF816034 \n"
"		BLLT	sub_FF815FD4 \n" // err_init_task
"		BL	sub_FF81167C \n"
"		CMP	R0, #0 \n"
//"		ADRLT	R0, aArmlib_setup \n" // "armlib_setup"
"		LDRLT	R0, =0xFF816040 \n"
"		BLLT	sub_FF815FD4 \n" // err_init_task
"		LDMFD	SP!, {R4,LR} \n"
"		B	taskcreate_Startup_my \n"
	
	);
}

void __attribute__((naked,noinline)) taskcreate_Startup_my() {

    asm volatile (
	
"		STMFD	SP!, {R3,LR} \n"
//"		BL	j_nullsub_197 \n"
"		BL	sub_FF83BF3C \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF81FB98 \n"
"		BL	sub_FF835D84 \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF81FB98 \n"
"		BL	sub_FF834394 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF81FB98 \n"
"		BL	sub_FF833A50 \n"
"		LDR	R1, =0xC0220000 \n"
"		MOV	R0, #0x44 \n"
"		STR	R0, [R1,#0x80] \n"
"		BL	sub_FF833C44 \n"
"loc_FF81FB94: \n"
"		B	loc_FF81FB94 \n"
"loc_FF81FB98: \n"
//"		BL	sub_FF8343A0 \n" // remove for correct power on (hold pwr button for rec)
//"		BL	j_nullsub_198 \n"
"		BL	sub_FF83A158 \n"
"		LDR	R1, =0x34E000 \n"
"		MOV	R0, #0 \n"
"		BL	sub_FF83A5A0 \n"
"		BL	sub_FF83A34C \n"
"		MOV	R3, #0 \n"
"		STR	R3, [SP] \n"
//"		ADR	R3, task_Startup \n"
"		LDR	R3, =task_Startup_my \n"	// Patched ----------->

"		B	sub_FF81FBC0 \n"		// Return to firmware ----------->
	);
}

void __attribute__((naked,noinline)) task_Startup_my() {

   	asm volatile (
"		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF816594 \n"
"		BL	sub_FF8354FC \n"
"		BL	sub_FF833714 \n"
//"		BL	j_nullsub_201 \n"
"		BL	sub_FF83C16C \n"
//"		BL	sub_FF83C014 \n"		// Skip starting diskboot.bin again
"		BL	sub_FF83C308 \n"
"		BL	sub_FF832474 \n"
"		BL	sub_FF83C19C \n"
"		BL	sub_FF8398FC \n"
"		BL	sub_FF83C30C \n"

//"		BL	taskcreate_PhySw \n"
"		BL	CreateTask_PhySw \n"			// our keyboard task
"		BL	CreateTask_spytask \n"			// chdk initialization

"		B	sub_FF81FB24 \n"		// Return to firmware ----------->
	);

}


/*----------------------------------------------------------------------
	spytask
-----------------------------------------------------------------------*/
void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}


/*----------------------------------------------------------------------
	CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask() {
	_CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}

void __attribute__((naked,noinline)) CreateTask_PhySw() {

    asm volatile (

"		STMFD	SP!, {R3-R5,LR} \n"
"		LDR	R4, =0x1C30 \n"
"		LDR	R0, [R4,#0x10] \n"
"		CMP	R0, #0 \n"
"		BNE	sub_FF8342B0 \n"
"		MOV	R3, #0 \n"
"		STR	R3, [SP] \n"
//"		ADR	R3, task_PhySw \n"
//"		MOV	R2, #0x800 \n"

"		LDR	R3, =mykbd_task \n"		// PhySw Task patch
"		MOV	R2, #0x2000 \n"			// larger stack

"		B	sub_FF8342A0 \n"		// Return to firmware ----------->
	);
	
}


/*----------------------------------------------------------------------
	init_file_modules_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) init_file_modules_task() {
	asm volatile (
"		STMFD	SP!, {R4-R6,LR} \n"
"		BL	sub_FF88E06C \n"
"		LDR	R5, =0x5006 \n"
"		MOVS	R4, R0 \n"
"		MOVNE	R1, #0 \n"
"		MOVNE	R0, R5 \n"
"		BLNE	sub_FF891DDC \n"		// eventproc_export_PostLogicalEventToUI
//"		BL	sub_FF88E098 \n"
"		BL	sub_FF88E098_my \n"		// patched ------------->
"		BL	core_spytask_can_start \n"	// added ------------->

"		B	sub_FF897958 \n"		// Return to firmware ----------->
	);
}

void __attribute__((naked,noinline)) sub_FF88E098_my() {
	asm volatile (
	
	
"		STMFD	SP!, {R4,LR} \n"
"		MOV	R0, #3 \n"
//"		BL	sub_FF8705CC \n"				
"		BL	sub_FF8705CC_my \n"		// patched ------------->
//"		BL	nullsub_72 \n"

"		B	sub_FF88E0A8 \n"		// Return to firmware ----------->
	);
}

void __attribute__((naked,noinline)) sub_FF8705CC_my() {
	asm volatile (
	
"		STMFD	SP!, {R4-R8,LR} \n"
"		MOV	R8, R0 \n"
"		BL	sub_FF87054C \n"
"		LDR	R1, =0x37988 \n"
"		MOV	R6, R0 \n"
"		ADD	R4, R1,	R0,LSL#7 \n"
"		LDR	R0, [R4,#0x6C] \n"
"		CMP	R0, #4 \n"
"		LDREQ	R1, =0x83F \n"
"		LDREQ	R0, =0xFF87008C \n"	// "Mounter.c"
"		BLEQ	_DebugAssert \n"
"		MOV	R1, R8 \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF86FE00 \n"
"		LDR	R0, [R4,#0x38] \n"
"		BL	sub_FF870C2C \n"
"		CMP	R0, #0 \n"
"		STREQ	R0, [R4,#0x6C] \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF86FE90 \n"
"		MOV	R0, R6 \n"
//"		BL	sub_FF8701F4 \n"
"		BL	sub_FF8701F4_my \n"		// patched ------------->

"		B	sub_FF870624 \n"		// Return to firmware ----------->
	);
}

void __attribute__((naked,noinline)) sub_FF8701F4_my() {
	asm volatile (
	
"		STMFD	SP!, {R4-R6,LR} \n"
"		MOV	R5, R0 \n"
"		LDR	R0, =0x37988 \n"
"		ADD	R4, R0,	R5,LSL#7 \n"
"		LDR	R0, [R4,#0x6C] \n"
"		TST	R0, #2 \n"
"		MOVNE	R0, #1 \n"
"		LDMNEFD	SP!, {R4-R6,PC} \n"
"		LDR	R0, [R4,#0x38] \n"
"		MOV	R1, R5 \n"
//"		BL	sub_FF86FF14 \n"
"		BL	sub_FF86FF14_my \n"		// patched ------------->

"		B	sub_FF870220 \n"		// Return to firmware ----------->
	);
}

void __attribute__((naked,noinline)) sub_FF86FF14_my() {
	asm volatile (
"		STMFD	SP!, {R4-R10,LR} \n"
"		MOV	R9, R0 \n"
"		LDR	R0, =0x37988 \n"
"		MOV	R8, #0 \n"
"		ADD	R5, R0,	R1,LSL#7 \n"
"		LDR	R0, [R5,#0x3C] \n"
"		MOV	R7, #0 \n"
"		CMP	R0, #7 \n"
"		MOV	R6, #0 \n"
"		ADDLS	PC, PC,	R0,LSL#2 \n"
"		B	sub_FF87006C \n"
"loc_FF86FF40: \n"
"		B	loc_FF86FF78 \n"
"loc_FF86FF44: \n"
"		B	loc_FF86FF60 \n"
"loc_FF86FF48: \n"
"		B	loc_FF86FF60 \n"
"loc_FF86FF4C: \n"
"		B	loc_FF86FF60 \n"
"loc_FF86FF50: \n"
"		B	loc_FF86FF60 \n"
"loc_FF86FF54: \n"
"		B	sub_FF870064 \n"
"loc_FF86FF58: \n"
"		B	loc_FF86FF60 \n"
"loc_FF86FF5C: \n"
"		B	loc_FF86FF60 \n"
"loc_FF86FF60: \n"
// jumptable FF86FF38 entries 1-4,6,7
"		MOV	R2, #0 \n"
"		MOV	R1, #0x200 \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF888184 \n"
"		MOVS	R4, R0 \n"
"		BNE	loc_FF86FF80 \n"
"loc_FF86FF78: \n"
// jumptable FF86FF38 entry 0
"		MOV	R0, #0 \n"
"		LDMFD	SP!, {R4-R10,PC} \n"
"loc_FF86FF80: \n"
"		LDR	R12, [R5,#0x50] \n"
"		MOV	R3, R4 \n"
"		MOV	R2, #1 \n"
"		MOV	R1, #0 \n"
"		MOV	R0, R9 \n"
"		BLX	R12 \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF86FFAC \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF8882D4 \n"
"		B	loc_FF86FF78 \n"
"loc_FF86FFAC: \n"
"		LDR	R1, [R5,#0x64] \n"
"		MOV	R0, R9 \n"
"		BLX	R1 \n"

//------------------  begin added code ---------------
		"MOV	R1, R4\n"           //  pointer to MBR in R1
		"BL	mbr_read_dryos\n"   //  total sectors count in R0 before and after call

		// Start of DataGhost's FAT32 autodetection code
		// Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
		// According to the code below, we can use R1, R2, R3 and R12.
		// LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
		// that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
		"MOV	R12, R4\n"                    // Copy the MBR start address so we have something to work with
		"MOV	LR, R4\n"                     // Save old offset for MBR signature
		"MOV	R1, #1\n"                     // Note the current partition number
		"B	dg_sd_fat32_enter\n"          // We actually need to check the first partition as well, no increments yet!
   "dg_sd_fat32:\n"
		"CMP	R1, #4\n"                     // Did we already see the 4th partition?
		"BEQ	dg_sd_fat32_end\n"            // Yes, break. We didn't find anything, so don't change anything.
		"ADD	R12, R12, #0x10\n"            // Second partition
		"ADD	R1, R1, #1\n"                 // Second partition for the loop
   "dg_sd_fat32_enter:\n"
		"LDRB	R2, [R12, #0x1BE]\n"          // Partition status
		"LDRB	R3, [R12, #0x1C2]\n"          // Partition type (FAT32 = 0xB)
		"CMP	R3, #0xB\n"                   // Is this a FAT32 partition?
		"CMPNE	R3, #0xC\n"                   // Not 0xB, is it 0xC (FAT32 LBA) then?
		"BNE	dg_sd_fat32\n"                // No, it isn't.
		"CMP	R2, #0x00\n"                  // It is, check the validity of the partition type
		"CMPNE	R2, #0x80\n"
		"BNE	dg_sd_fat32\n"                // Invalid, go to next partition
											   // This partition is valid, it's the first one, bingo!
		"MOV	R4, R12\n"                    // Move the new MBR offset for the partition detection.

   "dg_sd_fat32_end:\n"
		// End of DataGhost's FAT32 autodetection code
//------------------  end added code ---------------

"		LDRB	R1, [R4,#0x1C9] \n"
"		LDRB	R3, [R4,#0x1C8] \n"
"		LDRB	R12, [R4,#0x1CC] \n"
"		MOV	R1, R1,LSL#24 \n"
"		ORR	R1, R1,	R3,LSL#16 \n"
"		LDRB	R3, [R4,#0x1C7] \n"
"		LDRB	R2, [R4,#0x1BE] \n"
//"		LDRB	LR, [R4,#0x1FF] \n"		// Replaced below
"		ORR	R1, R1,	R3,LSL#8 \n"
"		LDRB	R3, [R4,#0x1C6] \n"
"		CMP	R2, #0 \n"
"		CMPNE	R2, #0x80 \n"
"		ORR	R1, R1,	R3 \n"
"		LDRB	R3, [R4,#0x1CD] \n"
"		MOV	R3, R3,LSL#24 \n"
"		ORR	R3, R3,	R12,LSL#16 \n"
"		LDRB	R12, [R4,#0x1CB] \n"
"		ORR	R3, R3,	R12,LSL#8 \n"
"		LDRB	R12, [R4,#0x1CA] \n"
"		ORR	R3, R3,	R12 \n"
//"		LDRB	R12, [R4,#0x1FE] \n"		// Replaced below

"		LDRB	R12, [LR,#0x1FE]\n"            // New! First MBR signature byte (0x55)
"		LDRB	LR, [LR,#0x1FF]\n"             //      Last MBR signature byte (0xAA)

"		B	sub_FF87000C \n"		// Return to firmware ----------->

	);
}

/*----------------------------------------------------------------------
	JogDial_task_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) JogDial_task_my()
{
	asm volatile (
"		STMFD	SP!, {R4-R11,LR} \n"
"		SUB	SP, SP,	#0x1C \n"
"		BL	sub_FF860118 \n"
"		LDR	R1, =0x2480 \n"
"		LDR	R6, =0xFFB4F590 \n"
"		MOV	R0, #0 \n"
"		ADD	R3, SP,	#0x10 \n"
"		ADD	R12, SP, #0x14 \n"
"		ADD	R10, SP, #0x8 \n"
"		MOV	R2, #0 \n"
"		ADD	R9, SP,	#0xC \n"
"loc_FF85FDAC: \n"
"		ADD	R12, SP, #0x14 \n"
"		ADD	LR, R12, R0,LSL#1 \n"
"		MOV	R2, #0 \n"
"		ADD	R3, SP,	#0x10 \n"
"		STRH	R2, [LR] \n"
"		ADD	LR, R3,	R0,LSL#1 \n"
"		STRH	R2, [LR] \n"
"		STR	R2, [R9,R0,LSL#2] \n"
"		STR	R2, [R10,R0,LSL#2] \n"
"		ADD	R0, R0,	#1 \n"
"		CMP	R0, #1 \n"
"		BLT	loc_FF85FDAC \n"
"loc_FF85FDDC: \n"
"		LDR	R0, =0x2480 \n"
"		MOV	R2, #0 \n"
"		LDR	R0, [R0,#8] \n"
"		MOV	R1, SP \n"
"		BL	sub_FF839B8C \n"
"		CMP	R0, #0 \n"
"		LDRNE	R1, =0x262 \n"
//"		ADRNE	R0, aRotaryencoder_ \n" // "RotaryEncoder.c"
"		LDRNE	R0, =0xFF86003C \n"
"		BLNE	_DebugAssert \n"
"		LDR	R0, [SP] \n"
"		AND	R4, R0,	#0xFF \n"
"		AND	R0, R0,	#0xFF00 \n"
"		CMP	R0, #0x100 \n"
"		BEQ	loc_FF85FE4C \n"
"		CMP	R0, #0x200 \n"
"		BEQ	loc_FF85FE84 \n"
"		CMP	R0, #0x300 \n"
"		BEQ	loc_FF86007C \n"
"		CMP	R0, #0x400 \n"
"		BNE	loc_FF85FDDC \n"
"		CMP	R4, #0 \n"
"		LDRNE	R1, =0x2ED \n"
//"		ADRNE	R0, aRotaryencoder_ \n"// "RotaryEncoder.c"
"		LDRNE	R0, =0xFF86003C \n"
"		BLNE	_DebugAssert \n"
"		RSB	R0, R4,	R4,LSL#3 \n"
"		LDR	R0, [R6,R0,LSL#2] \n"
"loc_FF85FE44: \n"
"		BL	sub_FF8600FC \n"
"		B	loc_FF85FDDC \n"
"loc_FF85FE4C: \n"
//------------------  begin added code ---------------
"labelA: \n"
		"LDR	R0, =jogdial_stopped\n"
		"LDR	R0, [R0]\n"
		"CMP	R0, #1\n"
		"BNE	labelB\n"			// continue on if jogdial_stopped = 0
		"MOV	R0, #40\n"
		"BL	_SleepTask\n"			// jogdial_stopped=1 -- give time back to OS and suspend jogdial task
		"B	labelA\n"
"labelB: \n" 
//------------------  end added code -----------------

"		LDR	R7, =0x248C \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83AB24 \n"
//"		ADR	R2, unk_FF85FCCC \n"
"		LDR	R2, =0xFF85FCCC \n"
"		MOV	R1, R2 \n"
"		ORR	R3, R4,	#0x200 \n"
"		MOV	R0, #0x28 \n"
"		BL	sub_FF83AA40 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R10,R4,LSL#2] \n"
"		BEQ	loc_FF85FDDC \n"
"		MOV	R1, #0x274 \n"
"		B	loc_FF860028 \n"
"loc_FF85FE84: \n"
"		RSB	R5, R4,	R4,LSL#3 \n"
"		LDR	R0, [R6,R5,LSL#2] \n"
"		LDR	R1, =0xC0240104 \n"
"		LDR	R0, [R1,R0,LSL#8] \n"
"		MOV	R2, R0,ASR#16 \n"
"		ADD	R0, SP,	#0x14 \n"
"		ADD	R0, R0,	R4,LSL#1 \n"
"		STR	R0, [SP,#0x18] \n"
"		STRH	R2, [R0] \n"
"		ADD	R0, SP,	#0x10 \n"
"		ADD	R11, R0, R4,LSL#1 \n"
"		LDRSH	R3, [R11] \n"
"		SUB	R0, R2,	R3 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF85FF04 \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF85FFE4 \n"
"		LDR	R7, =0x248C \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83AB24 \n"
//"		ADR	R2, sub_FF85FCD8 \n"
"		LDR	R2, =0xFF85FCD8 \n"
"		MOV	R1, R2 \n"
"		ORR	R3, R4,	#0x300 \n"
"		MOV	R0, #0x1F4 \n"
"		BL	sub_FF83AA40 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R7,R4,LSL#2] \n"
"		BEQ	loc_FF85FFE4 \n"
"		LDR	R1, =0x28D \n"
"		B	loc_FF85FFDC \n"
"loc_FF85FF04: \n"
"		MOV	R1, R0 \n"
"		RSBLT	R0, R0,	#0 \n"
"		MOVLE	R7, #0 \n"
"		MOVGT	R7, #1 \n"
"		CMP	R0, #0xFF \n"
"		BLS	loc_FF85FF44 \n"
"		CMP	R1, #0 \n"
"		RSBLE	R0, R3,	#0xFF \n"
"		ADDLE	R0, R0,	#0x7F00 \n"
"		ADDLE	R0, R0,	R2 \n"
"		RSBGT	R0, R2,	#0xFF \n"
"		ADDGT	R0, R0,	#0x7F00 \n"
"		ADDGT	R0, R0,	R3 \n"
"		ADD	R0, R0,	#0x8000 \n"
"		ADD	R0, R0,	#1 \n"
"		EOR	R7, R7,	#1 \n"
"loc_FF85FF44: \n"
"		STR	R0, [SP,#0x4] \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		ADDEQ	R0, R6,	R5,LSL#2 \n"
"		LDREQ	R0, [R0,#8] \n"
"		BEQ	loc_FF85FF7C \n"
"		ADD	R8, R6,	R5,LSL#2 \n"
"		ADD	R1, R8,	R7,LSL#2 \n"
"		LDR	R1, [R1,#0x10] \n"
"		CMP	R1, R0 \n"
"		BEQ	loc_FF85FF80 \n"
"		LDR	R0, [R8,#0xC] \n"
"		BL	sub_FF893C28 \n"
"		LDR	R0, [R8,#8] \n"
"loc_FF85FF7C: \n"
"		BL	sub_FF893C28 \n"
"loc_FF85FF80: \n"
"		ADD	R0, R6,	R5,LSL#2 \n"
"		ADD	R7, R0,	R7,LSL#2 \n"
"		LDR	R0, [R7,#0x10] \n"
"		LDR	R1, [SP,#0x4] \n"
"		BL	sub_FF893B50 \n"
"		LDR	R0, [R7,#0x10] \n"
"		LDR	R7, =0x248C \n"
"		STR	R0, [R9,R4,LSL#2] \n"
"		LDR	R0, [SP,#0x18] \n"
"		LDRH	R0, [R0] \n"
"		STRH	R0, [R11] \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83AB24 \n"
//"		ADR	R2, sub_FF85FCD8 \n"
"		LDR	R2, =0xFF85FCD8 \n"
"		MOV	R1, R2 \n"
"		ORR	R3, R4,	#0x300 \n"
"		MOV	R0, #0x1F4 \n"
"		BL	sub_FF83AA40 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R7,R4,LSL#2] \n"
"		BEQ	loc_FF85FFE4 \n"
"		LDR	R1, =0x2CF \n"
"loc_FF85FFDC: \n"
//"		ADR	R0, aRotaryencoder_ \n" // "RotaryEncoder.c"
"		LDR	R0, =0xFF86003C \n"
"		BL	_DebugAssert \n"
"loc_FF85FFE4: \n"
"		ADD	R0, R6,	R5,LSL#2 \n"
"		LDR	R0, [R0,#0x18] \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF860074 \n"
"		LDR	R0, =0x2480 \n"
"		LDR	R0, [R0,#0x10] \n"
"		CMP	R0, #0 \n"
"loc_FF860000: \n"
"		BEQ	loc_FF860074 \n"
//"		ADR	R2, unk_FF85FCCC \n"
"		LDR	R2, =0xFF85FCCC \n"
"		MOV	R1, R2 \n"
"		ORR	R3, R4,	#0x400 \n"
"		BL	sub_FF83AA40 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R10,R4,LSL#2] \n"
"		BEQ	loc_FF85FDDC \n"
"		LDR	R1, =0x2D6 \n"
"loc_FF860028: \n"
//"		ADR	R0, aRotaryencoder_ \n" // "RotaryEncoder.c"
"		LDR	R0, =0xFF86003C \n"
"		BL	_DebugAssert \n"
"		B	loc_FF85FDDC \n"
"loc_FF860074: \n"
"		LDR	R0, [R6,R5,LSL#2] \n"
"		B	loc_FF85FE44 \n"
"loc_FF86007C: \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		MOVEQ	R1, #0x2E0 \n"
//"		ADREQ	R0, aRotaryencoder_ \n" // "RotaryEncoder.c"
"		LDREQ	R0, =0xFF86003C \n"
"		BLEQ	_DebugAssert \n"
"		RSB	R0, R4,	R4,LSL#3 \n"
"		ADD	R0, R6,	R0,LSL#2 \n"
"		LDR	R0, [R0,#0xC] \n"
"		BL	sub_FF893C28 \n"
"		MOV	R2, #0 \n"
"		STR	R2, [R9,R4,LSL#2] \n"
"		B	loc_FF85FDDC \n"
	);
}
