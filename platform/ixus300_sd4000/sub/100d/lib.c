#include "platform.h"

// Description from SD890

// ?!?
// found in taskcreate_ImageSensorTask
//ROM:FF84E1F4                 STMFD   SP!, {R3-R9,LR}
//ROM:FF84E1F8                 LDR     R4, =0x1FC4 <---
//ROM:FF84E1FC                 MOV     R5, R0
//ROM:FF84E200                 LDR     R0, [R4]
void *hook_raw_fptr() {
    //return (void*)0;
    return (void*)0x1FC4;
}

// ?!?
void *hook_raw_ret_addr() {
    return (void*)0;         // DUMMY
}

// ?!?
char *hook_raw_image_addr() {
    //return (char*)0x10F6C860;
    return (char*)0;         // DUMMY
}

// ROM:FFAAFF70
// search String "CRAW BUFF SIZE"
long hook_raw_size() {
    return 0x1574D00;
}

// ?!?
// Live picture buffer (shoot not pressed)
// ROM:FF84FB50 ?!?
void *vid_get_viewport_live_fb() {
    return (void*)0;
    /*
    void **fb=(void **)0x21EC;
    unsigned char buff = *((unsigned char*)0x2084);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
    */
}

// OSD buffer
// like SX10
// search dispcon* functions and BmpDDev.c
// ROM:FF919A78                 STMFD   SP!, {R4-R8,LR}
// ROM:FF919A7C                 LDR     R8, =0x59F0
// ROM:FF919A80                 MOV     R4, R0
// ROM:FF919A84                 LDR     R0, [R8,#0x10]
// ROM:FF919A88                 MOV     R5, R1
// ROM:FF919A8C                 CMP     R0, #1
// ROM:FF919A90                 LDREQ   R1, =0x13F
// ROM:FF919A94                 ADREQ   R0, aBmpddev_c  ; "BmpDDev.c"
// ROM:FF919A98                 MOV     R7, R3
// ROM:FF919A9C                 MOV     R6, R2
// ROM:FF919AA0                 BLEQ    DebugAssert
// ROM:FF919AA4                 CMP     R4, #0
// ROM:FF919AA8                 CMPNE   R5, #0
// ROM:FF919AAC                 CMPNE   R6, #0
// ROM:FF919AB0                 CMPNE   R7, #0
// ROM:FF919AB4                 LDREQ   R1, =0x142
// ROM:FF919AB8                 ADREQ   R0, aBmpddev_c  ; "BmpDDev.c"
// ROM:FF919ABC                 BLEQ    DebugAssert
// ROM:FF919AC0                 LDR     R1, =0x10E
// ROM:FF919AC4                 MOV     R0, #0x3C0
// ROM:FF919AC8                 STR     R0, [R4]
// ROM:FF919ACC                 STR     R1, [R5]
// ROM:FF919AD0                 STR     R0, [R6]
// ROM:FF919AD4                 LDR     R0, =0x40471000 <---
// ROM:FF919AD8                 STR     R0, [R7]
// ROM:FF919ADC                 MOV     R0, #1
// ROM:FF919AE0                 STR     R0, [R8,#0x10]
// ROM:FF919AE4                 MOV     R0, #0
// ROM:FF919AE8                 LDMFD   SP!, {R4-R8,PC}
void *vid_get_bitmap_fb() {
    return (void*)0x40471000;   // ROM:FF919AD4 or ROM:FFA347DC or ROM:FF85B154
}

// Live picture buffer (shoot half-pressed)
// search for String "VRAM Address" (like SX10)
// or search for String "MaxY %ld MinY %ld" and look below
void *vid_get_viewport_fb() {
    //return (void*)0x1065A4D0; // 0x107D5FD0
    return (void*)0x40587700; // ROM:FFB25ED8 or ROM:FFB25DFC
}

// ?!?
// possible future use
void *vid_get_viewport_fb_d() {
    //return (void*)(*(int*)0x540C);  //5410
    return (void*)(*(int*)0);         // DUMMY
}

//long vid_get_bitmap_screen_width() { return 360; }
long vid_get_bitmap_screen_width() { return 720; }

long vid_get_bitmap_screen_height() { return 240; }

int vid_get_viewport_width() { return 360; }    // viewport is still 360, even though live view is 720 (from SD990)

long vid_get_viewport_height() { return 240; }

// ?!?
// search for String "9999" (like SX10)
//ROM:FFA04F74                 SUBS    R12, R5, #0x2700
//ROM:FFA04F78                 SUBCSS  R12, R12, #0xF
//ROM:FFA04F7C                 BCC     loc_FFA04F90
//ROM:FFA04F80                 LDR     R0, =0xA15B8 <---
//ROM:FFA04F84                 ADR     R1, a9999       ; "9999"
//ROM:FFA04F88                 BL      eventproc_export_sprintf
char *camera_jpeg_count_str() {
    return (char*)0xA15B8;
}

//long vid_get_bitmap_buffer_width() { return 360; }
long vid_get_bitmap_buffer_width() { return 720; }

long vid_get_bitmap_buffer_height() { return 240; }
