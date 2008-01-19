void __attribute__((naked,noinline)) init_file_modules_task(){
 asm volatile(
                "STMFD   SP!, {R4,LR}\n"
                "BL      _Unmount_FileSystem\n" // + 
                "BL      sub_FFEE1D70\n"
                "SUBS    R4, R0, #0\n"
                "MOV     R0, #0x5000\n"
                "MOV     R1, #0\n"
                "ADD     R0, R0, #6\n"
                "BEQ     loc_FFD99158\n"
                "BL      sub_FFD6CD44\n"  // PostLogicalEventToUI
"loc_FFD99158:\n"
                "BL      sub_FFEE1D9C_my\n"  // ----------->
                "MOV     R0, #0x5000\n"
                "CMP     R4, #0\n"
                "MOV     R1, R4\n"
                "ADD     R0, R0, #6\n"
                "LDMNEFD SP!, {R4,PC}\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFD6CD44\n" //  PostLogicalEventToUI
 );
}

void __attribute__((naked,noinline)) sub_FFEE1D9C_my(){
 asm volatile(
                "STR     LR, [SP,#-4]!\n"
                "BL      Mount_FileSystem_my\n"  //---------------->
                "LDR     R3, =0xAF68\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "BNE     loc_FFEE1DD8\n"
                "BL      sub_FFDBD45C\n"
                "AND     R0, R0, #0xFF\n"
                "BL      sub_FFC23638\n"
                "BL      sub_FFDBD45C\n"
                "AND     R0, R0, #0xFF\n"
                "BL      sub_FFC552AC\n"
                "BL      sub_FFDBD46C\n"
                "AND     R0, R0, #0xFF\n"
                "BL      sub_FFC2370C\n"
"loc_FFEE1DD8:\n"
                "LDR     R2, =0xAF64\n"
                "MOV     R3, #1\n"
                "STR     R3, [R2]\n"
                "LDR     PC, [SP],#4\n"

 );
}

void __attribute__((naked,noinline)) Mount_FileSystem_my(){
 asm volatile(
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOV     R5, #0\n"
                "LDR     R6, =0x2C4A8\n"
                "MOV     R0, R5\n"
                "BL      sub_FFC5FCD4\n"
                "LDR     R0, [R6,#0x38]\n"
                "BL      sub_FFC5F394\n"
                "SUBS    R1, R0, #0\n"
                "MOV     R0, R5\n"
                "BNE     loc_FFC6032C\n"
                "LDR     R3, =0x2750\n"
                "LDR     R2, =0x2748\n"
                "STR     R1, [R3]\n"
                "LDR     R3, =0x274C\n"
                "STR     R1, [R2]\n"
                "STR     R1, [R3]\n"
"loc_FFC6032C:\n"
                "BL      sub_FFC5FD24\n"
                "MOV     R0, R5\n"
                "BL      sub_FFC6004C_my\n"  //---------------->
                "MOV     R4, R0\n"
                "MOV     R0, R5\n"
                "BL      sub_FFC600D4\n"
                "AND     R4, R4, R0\n"
                "MOV     R2, R4\n"
                "MOV     R0, R6\n"
                "LDR     R1, [R6,#0x3C]\n"
                "BL      sub_FFC6029C\n"
                "STR     R0, [R6,#0x40]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC6004C_my(){
 asm volatile(
                "STMFD   SP!, {R4-R7,LR}\n"
                "LDR     R7, =0x274C\n"
                "LDR     R3, [R7]\n"
                "MOV     R4, R0\n"
                "CMP     R3, #0\n"
                "ADD     R3, R4, R4,LSL#1\n"
                "RSB     R3, R4, R3,LSL#3\n"
                "LDR     R6, =0x2C4E0\n"
                "MOV     R5, R3,LSL#2\n"
                "MOV     R1, R4\n"
                "BNE     loc_FFC600C0\n"
                "LDR     R0, [R6,R5]\n"
                "BL      sub_FFC5FDE0_my\n"  //-------------->
                "SUBS    R3, R0, #0\n"
                "MOV     R1, R4\n"
                "BEQ     loc_FFC60098\n"
                "LDR     R0, [R6,R5]\n"
                "BL      sub_FFC5FF2C\n"
                "MOV     R3, R0\n"
"loc_FFC60098:\n"
                "CMP     R3, #0\n"
                "MOV     R0, R4\n"
                "BEQ     loc_FFC600AC\n"
                "BL      sub_FFC5F46C\n"
                "MOV     R3, R0\n"
"loc_FFC600AC:\n"
                "CMP     R3, #0\n"
                "MOV     R0, R3\n"
                "MOVNE   R3, #1\n"
                "STRNE   R3, [R7]\n"
                "LDMFD   SP!, {R4-R7,PC}\n"
"loc_FFC600C0:\n"
                "MOV     R0, #1\n"
                "LDMFD   SP!, {R4-R7,PC}\n"

 );
}

void __attribute__((naked,noinline)) sub_FFC5FDE0_my(){
 asm volatile(
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R5, R1\n"
                "MOV     R8, R5,LSL#1\n"
                "ADD     R3, R8, R5\n"
                "LDR     R2, =0x2C4E4\n"
                "SUB     SP, SP, #8\n"
                "RSB     R3, R5, R3,LSL#3\n"
                "LDR     R1, [R2,R3,LSL#2]\n"
                "MOV     R6, #0\n"
                "STR     R6, [SP]\n"
                "MOV     R7, R0\n"
                "STR     R6, [SP,#4]\n"
                "CMP     R1, #5\n"
                "LDRLS   PC, [PC,R1,LSL#2]\n"
                "B       loc_FFC5FEDC\n"
                ".long loc_FFC5FE80\n"
                ".long loc_FFC5FE34\n"
                ".long loc_FFC5FE34\n"
                ".long loc_FFC5FE34\n"
                ".long loc_FFC5FE34\n"
                ".long loc_FFC5FECC\n"
"loc_FFC5FE34:\n"
                "MOV     R0, #3\n"
                "MOV     R1, #0x200\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC02834\n"
                "SUBS    R6, R0, #0\n"
                "BEQ     loc_FFC5FF10\n"
                "ADD     R12, R8, R5\n"
                "RSB     R12, R5, R12,LSL#3\n"
                "LDR     R4, =0x2C4F4\n"
                "MOV     R0, R7\n"
                "MOV     R1, #0\n"
                "MOV     R2, #1\n"
                "MOV     R3, R6\n"
                "MOV     LR, PC\n"
                "LDR     PC, [R4,R12,LSL#2]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC5FE88\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC02904\n"
"loc_FFC5FE80:\n"
                "MOV     R0, #0\n"
                "B       loc_FFC5FF10\n"
"loc_FFC5FE88:\n"
                "MOV     R0, R7\n"
                "BL      sub_FFC70778\n"
                "MOV     R1, R0\n"
                "ADD     R2, SP, #4\n"
                "MOV     R3, SP\n"
                "MOV     R0, R6\n"

                "STMFD   SP!, {R4-R11,LR}\n" // +
                "BL      mbr_read\n"    //-----------> 
                "LDMFD   SP!, {R4-R11,LR}\n" // +

//              "BL      sub_FFC5F570\n"  // original function
                "MOV     R4, R0\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC02904\n"
                "CMP     R4, #0\n"
                "BNE     loc_FFC5FEE8\n"
                "MOV     R0, R7\n"
                "STR     R4, [SP,#4]\n"
                "BL      sub_FFC70778\n"
                "STR     R0, [SP]\n"
                "B       loc_FFC5FEE8\n"
"loc_FFC5FECC:\n"
                "MOV     R3, #0\n"
                "MOV     R2, #0x40\n"
                "STMEA   SP, {R2,R3}\n"
                "B       loc_FFC5FEE8\n"
"loc_FFC5FEDC:\n"
                "LDR     R0, =0xFFC5FBC8\n"  // aMounter_c
                "MOV     R1, #0x2B4\n"
                "BL      sub_FFC03CF8\n"  // DebugAssert
"loc_FFC5FEE8:\n"
                "LDR     R2, =0x2C4A8\n"
                "ADD     R3, R8, R5\n"
                "LDMFD   SP, {R0,R12}\n"
                "RSB     R3, R5, R3,LSL#3\n"
                "MOV     R3, R3,LSL#2\n"
                "ADD     R1, R2, #0x48\n"
                "ADD     R2, R2, #0x44\n"
                "STR     R0, [R1,R3]\n"
                "STR     R12, [R2,R3]\n"
                "MOV     R0, #1\n"
"loc_FFC5FF10:\n"
                "ADD     SP, SP, #8\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
 );
}

int mbr_read(char* mbr_sector, unsigned long drive_total_sectors, unsigned long *part_start_sector,  unsigned long *part_length){
// return value: 1 - success, 0 - fail
 
 int offset=0x10; // points to partition #2
 int valid;
  
 if ((mbr_sector[0x1FE]!=0x55) || (mbr_sector[0x1FF]!=0xAA)) return 0; // signature check 

 while(offset>=0) {
 
  *part_start_sector=(*(unsigned short*)(mbr_sector+offset+0x1C8)<<16) | *(unsigned short*)(mbr_sector+offset+0x1C6); 
  *part_length=(*(unsigned short*)(mbr_sector+offset+0x1CC)<<16) | *(unsigned short*)(mbr_sector+offset+0x1CA); 

  valid= (*part_start_sector<=drive_total_sectors) && 
         (*part_start_sector+*part_length<=drive_total_sectors) &&
         ((mbr_sector[offset+0x1BE]==0) || (mbr_sector[offset+0x1BE]==0x80)); // status: 0x80 (active) or 0 (non-active)

  if (valid && (mbr_sector[0x1C2+offset]==0x0B)) break;   // FAT32 secondary partition

  offset-=0x10;

 }

 return valid;
}

