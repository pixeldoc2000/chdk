#include "platform.h"

// RAM addresses

/*
RAW Address
ROM:FF93B994    LDR     R2, =3816       ; RAW H Pixel
ROM:FF93B998    LDR     R1, =0x4132C0A0
ROM:FF93B99C    MOV     R3, #2784       ; RAW V Pixel
ROM:FF93B9A0    ADR     R0, aCrwaddressLxCr ; " CrwAddress %lx, CrwSize H %ld V %ld\r"

ROM:FFB60E70 RAW Buffer Table
ROM:FF87ED4C referens the table with first RAW address (SsImgProcBuf.c)

called by Getcaptureinfodata() (ROM:FFB28F14)
ROM:FFB28EAC sub_FFB28EAC
ROM:FFB28EEC    LDR     R0, =3816       ; RAW H Pixel
ROM:FFB28EF0    STR     R0, [R1]
ROM:FFB28EF4    MOV     R0, #2784       ; RAW V Pixel
ROM:FFB28EF8    STR     R0, [R1,#4]
ROM:FFB28EFC    MOV     R0, #3648       ; JPEG H Pixel
ROM:FFB28F00    STR     R0, [R1,#8]
ROM:FFB28F04    MOV     R0, #2736       ; JPEG V Pixel

sensor size for camera.h (like SX210)
ROM:FFB292D0    0xF32880 = 15935616 (hook_raw_size)
15935616 / 12 * 8 =  10623744    (12 Bit RAW)
ROM:FFB28EEC    0xEE8 = 3816 pixel
ROM:FFB28EF4    0xAE0 = 2784 pixel
3816 * 2784 = 10623744
*/

// Note: RAW files are only readable if Program support SD4000 RAW (very unlikely because RAW has not defined File Format because it's RAW sensor data). Use DNG!
// ROM:FFB29270, like SX210
// search String "CRAW BUFF" (IDA Name: aCrawBuffP)
// like G11
// DNG colors are incorrect if cam_CFAPattern is wrong
char *hook_raw_image_addr() {
    // RAW single buffer (if one address always have valid image)
    //return (char*)0x4132C0A0;         // first RAW buffer address, first shoot is invalid, second shoot is good, further shoots are ofter invalid
    //return (char*)0x40AFF8A0;         // second RAW buffer address
    //return (char*)0x44CF6800;         // third RAW buffer address

    //return (char*)0x420F7932;         // ROM:FFB60E74
    //return (char*)0x46DCB892;         // ROM:FFB60E74
    //return (char*)0x47209000;         // ROM:FFB29258    // cause shutdown

    // RAW multi buffer
    // like SD990 & SD900
    // ROM:FF87ED50 0x2CCC
    // ROM:FF87ED7C 0xC
    return (char*) (*(int*)(0x2CCC + 0xC)? 0x46000000 : 0x4132C0A0);    // looks like every RAW is valid
    //return (char*) (*(int*)(0x2CCC + 0x18)? 0x46000000 : 0x4132C0A0);
    //return (char*) (*(int*)(0x2CCC + 0xC)? 0x4132C0A0 : 0x46000000);
    //return (char*) (*(int*)(0x2CCC + 0x8)? 0x4132C0A0 : 0x46000000);
    //return (char*) (*(int*)0x2CCC ? 0x4132C0A0 : 0x46000000);
    //return (char*) (*(int*)0x2CCC ? 0x46000000 : 0x4132C0A0);
}

/*** RAW buffer size
ROM:FFB292D0    LDR     R1, =0xF32880   <---
ROM:FFB292D4    ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
***/
long hook_raw_size() {
    return 0xF32880;    // 15935616
}

// vid_* stuff is related to BmpDDev() stuff (ROM:FF919A78 and other) and LiveImage.c

// ToDo: ?!?
/*** Live picture buffer (shoot not pressed)
ROM:FFB25ED8    LDR     R1, =0x40587700   <---
ROM:FFB25EDC    LDR     R0, =0x54600   <---
...
ROM:FFB25EE8    ADR     R0, aVramAddressP ; "VRAM Address  : %p\r"
***/
/*
void *vid_get_viewport_live_fb() {
    //return (void*)0;
    return (void*)0x405DBD00;   // 0x40587700 + 0x54600
}
*/

// ToDo: ?!?
// Live picture buffer (shoot not pressed)
// ROM:FF84FB50 ?!?
void *vid_get_viewport_live_fb() {
    //void **fb=(void **)0x21E8;      // ?!?
    //void **fb=(void **)0x21EC;      // ?!?
    void **fb=(void **)0x21F8;      // ROM:FF85078C ?!? more or less guesswork
    unsigned char buff = *((unsigned char*)0x204C);   // ROM:FF850904
    if (buff == 0) {
        buff = 2;
    } else {
        buff--;
    }
    return fb[buff];
}

// OSD buffer
// like SX10
// search dispcon* functions and BmpDDev.c
// ROM:FF919AB8    ADREQ   R0, aBmpddev_c  ; "BmpDDev.c"
// ROM:FF919ABC    BLEQ    DebugAssert
// ROM:FF919AC0    LDR     R1, =0x10E
// ROM:FF919AC4    MOV     R0, #0x3C0
// ROM:FF919AC8    STR     R0, [R4]
// ROM:FF919ACC    STR     R1, [R5]
// ROM:FF919AD0    STR     R0, [R6]
// ROM:FF919AD4    LDR     R0, =0x40471000 <---
void *vid_get_bitmap_fb() {
    return (void*)0x40471000;    // ROM:FF919AD4 or ROM:FFA347DC or ROM:FF85B154
}

/*** Live picture buffer (shoot half-pressed)
search for String "VRAM Address" (like SX10)
or search for String "MaxY %ld MinY %ld" and look below
ROM:FFB25ED8    LDR     R1, =0x40587700    <---
...
ROM:FFB25EE8    ADR     R0, aVramAddressP ; "VRAM Address  : %p\r"
***/
void *vid_get_viewport_fb() {
    return (void*)0x40587700;    // ROM:FFB25ED8 or ROM:FFB25DFC
}

// ?!?
// possible future use
void *vid_get_viewport_fb_d() {
    return (void*)(*(int*)0x2AA4);    // ROM:FF874770 0x2A50 + 0x54
}

// search for String "9999" (IDA Name: a9999)
// ROM:FFA04F80    LDR     R0, =0xA15B8    ; <---
// ROM:FFA04F84    ADR     R1, a9999       ; "9999"
char *camera_jpeg_count_str() {
    return (char*)0xA15B8;
}
