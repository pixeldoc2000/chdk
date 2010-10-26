#include "platform.h"

// RAM addresses

// Description from SD890

// sensor size for camera.h (like SX210)
// ROM:FFB292D0 0xF32880 = 15935616 (hook_raw_size)
// 15935616 / 12 * 8 =  10623744    (12 Bit RAW)
// ROM:FFB28EEC 0xEE8 = 3816 pixel
// ROM:FFB28EF4 0xAE0 = 2784 pixel
// 3816 * 2784 = 10623744

// ROM:FFB29270, like SX210
// search String "CRAW BUFF"
char *hook_raw_image_addr() {
    return (char*)0x4132C0A0;           // first RAW buffer address
    //return (char*)0x40AFF8A0;         // second RAW buffer address
    //return (char*)0x44CF6800;         // third RAW buffer address
}

/*
// ROM:FFB2926C 0x4132C0A0 First RAW address
// ROM:FFB60E70 Table contains first RAW address mentioned in SD990
// function ROM:FF87ED4C referens the table with first RAW address (SsImgProcBuf.c)
// ROM:FF87ED50 0x2CCC
// ROM:FF87ED7C 0xC
char *hook_raw_image_addr() {
    return (char*) (*(int*)(0x2CCC + 0xC)? 0x46000000 : 0x4132C0A0);
}
*/

// ROM:FFB292D0, like SX210
// search String "CRAW BUFF SIZE"
long hook_raw_size() {
    return 0xF32880;
}

void *vid_get_viewport_live_fb() {
    return (void*)0;
}

/*
// ?!?
// Live picture buffer (shoot not pressed)
// ROM:FF84FB50 ?!?
void *vid_get_viewport_live_fb() {
    //void **fb=(void **)0x21E8;      // ?!?
    //void **fb=(void **)0x21EC;      // ?!?
    void **fb=(void **)0x21F8;      // ROM:FF85078C ?!? more or less guesswork
    unsigned char buff = *((unsigned char*)0x204C);   // ROM:FF850904
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}
*/

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
    return (void*)0x40471000;    // ROM:FF919AD4 or ROM:FFA347DC or ROM:FF85B154
}

// Live picture buffer (shoot half-pressed)
// search for String "VRAM Address" (like SX10)
// or search for String "MaxY %ld MinY %ld" and look below
void *vid_get_viewport_fb() {
    return (void*)0x40587700;    // ROM:FFB25ED8 or ROM:FFB25DFC
}

// ?!?
// possible future use
void *vid_get_viewport_fb_d() {
    return (void*)(*(int*)0x2AA4);         // ROM:FF874770 0x2A50 + 0x54
}

// vid_* stuff is related to BmpDDev() stuff (ROM:FF919A78 and other) and LiveImage.c

// ROM:FF9013D8 0x2D0 = 720 ?!?
// SD990 ROM:FF83CFC8 ?!?
//long vid_get_bitmap_screen_width() { return 320; }
//long vid_get_bitmap_screen_width() { return 360; }
long vid_get_bitmap_screen_width() { return 480; }
//long vid_get_bitmap_screen_width() { return 720; }
//long vid_get_bitmap_screen_width() { return 960; }

long vid_get_bitmap_screen_height() { return 240; }
//long vid_get_bitmap_screen_height() { return 270; }
//long vid_get_bitmap_screen_height() { return 360; }

//int vid_get_viewport_width() { return 360; }    // viewport is still 360, even though live view is 720 (from SD990)
int vid_get_viewport_width() { return 480; }

/*
int vid_get_viewport_width() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?480:360;
}
*/

//long vid_get_viewport_height() { return 240; }
long vid_get_viewport_height() { return 270; }

// ?!?
// search for String "9999" (like SX10) and SD990
//ROM:FFA04F74                 SUBS    R12, R5, #0x2700
//ROM:FFA04F78                 SUBCSS  R12, R12, #0xF
//ROM:FFA04F7C                 BCC     loc_FFA04F90
//ROM:FFA04F80                 LDR     R0, =0xA15B8 <---
//ROM:FFA04F84                 ADR     R1, a9999       ; "9999"
//ROM:FFA04F88                 BL      eventproc_export_sprintf
char *camera_jpeg_count_str() {
    return (char*)0xA15B8;
}

// if buffer width was to small, Logo was shown as distorted "row" on Display
//long vid_get_bitmap_buffer_width() { return 360; }
//long vid_get_bitmap_buffer_width() { return 720; }
long vid_get_bitmap_buffer_width() { return 960; }      // working

//long vid_get_bitmap_buffer_height() { return 240; }
long vid_get_bitmap_buffer_height() { return 270; }
//long vid_get_bitmap_buffer_height() { return 360; }
