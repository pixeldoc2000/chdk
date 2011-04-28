#include "platform.h"
#include "lolevel.h"

void shutdown() {
    volatile long *p = (void*)0xC0223030;    // Red AF Led (front)

    asm(
        "MRS     R1, CPSR\n"
        "AND     R0, R1, #0x80\n"
        "ORR     R1, R1, #0x80\n"
        "MSR     CPSR_cf, R1\n"
        :::"r1","r0"
    );

    *p = 0x44;

    while(1);
}

//#define LED_DEBUG 0xC0220130    // Green Led (backside)
#define LED_DEBUG 0xc0220134    // Red Led (backside)
//#define LED_DEBUG 0xC0223030    // Red AF Led (front)

#define DEBUG_LED_DELAY 2500000    // use beforce change CPU speed in boot.c
//#define DEBUG_LED_DELAY 50000000    // use after change CPU speed in boot.c

void debug_led(int state) {
    volatile long *p=(void*)LED_DEBUG;

    if (state)
        p[0]=0x46;
    else
        p[0]=0x44;

    // delay loop
    int i;
    for (i=0; i<DEBUG_LED_DELAY; i++)
        asm("nop\n nop\n");
}

#define LED_AF 0xC0223030

// ROM:FF997634 near PropertyTableManagerCore (from SD990) ?!?
//ROM:FF997624                 LDREQ   R0, =aPropertytablemanagerco ; "PropertyTableManagerCore.c"
//ROM:FF997628                 MOVEQ   R1, R6
//ROM:FF99762C                 BLEQ    DebugAssert
//ROM:FF997630                 BIC     R4, R4, #0x4000
//ROM:FF997634                 CMP     R4, #0x94 <---
int get_flash_params_count(void) {
    return 148;     // 0x94 = 148
}

/*
// redraw issus, Canon Menu does not show and display does not refresh properly
void vid_bitmap_refresh() {
    extern int enabled_refresh_physical_screen;

    _ScreenLock();
    enabled_refresh_physical_screen=1;
    // *(int*)0x926C=3;    // ROM:FFA114FC, like SX210
    // *(int*)0x926C=2;    // ?!?
    *(int*)0x926C=1;    // better than 3
    _RefreshPhysicalScreen(1);
}
*/

/*
// like ixus870_sd880, cause massiv redraw issus
void vid_bitmap_refresh() {
    extern int enabled_refresh_physical_screen; // screen lock counter
    int old_val = enabled_refresh_physical_screen;
    if ( old_val == 0 ) {
        _ScreenLock(); // make sure code is called at least once
    } else {
        enabled_refresh_physical_screen=1; // forces actual redraw
    }
    _RefreshPhysicalScreen(1); // unlock/refresh

    // restore original situation
    if ( old_val > 0 ) {
        _ScreenLock();
        enabled_refresh_physical_screen = old_val;
    }
}
*/

// Force Screen to refresh like original Firmware
// from SX210, thanks asm1989
void vid_bitmap_refresh() {
    extern int enabled_refresh_physical_screen;
    extern int full_screen_refresh;

    // asm1989: i've tried refreshphysical screen (screen unlock) and that caused the canon and
    // function menu to not display at all. This seems to work and is called in a similar
    // way in other places where original OSD should be refreshed.
    extern void _LockAndRefresh();   // wrapper function for screen lock
    extern void _UnlockAndRefresh();   // wrapper function for screen unlock

    _LockAndRefresh();

    enabled_refresh_physical_screen=1;
    full_screen_refresh=3;   // found in ScreenUnlock underneath a CameraLog.c call

    _UnlockAndRefresh();
}

/*
// make redraw issus worse
void vid_turn_off_updates() {
    //_ScreenLock();
    _LockAndRefresh();
}
*/

/*
// make redraw issus worse
void vid_turn_on_updates() {
    //_RefreshPhysicalScreen(1);
    _UnlockAndRefresh(1);
}
*/

// ROM:FFB9FA10 DCD aRotatejogdialright ; "RotateJogDialRight"
// ROM:FFB9FA14 DCD 0x876
// ROM:FFB9FA18 DCD 2
void JogDial_CW(void) {
    _PostLogicalEventForNotPowerType(0x876, 2);  // RotateJogDialRight at levent_table
}

// ROM:FFB9FA1C DCD aRotatejogdialleft  ; "RotateJogDialLeft"
// ROM:FFB9FA20 DCD 0x877
// ROM:FFB9FA24 DCD 2
void JogDial_CCW(void) {
    _PostLogicalEventForNotPowerType(0x877, 2);  // RotateJogDialLeft at levent_table
}

// ToDo
void camera_set_led(int led, int state, int bright) {
    static char led_table[7]={0,1,2,3,9,14,15};
    _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

// Bitmap Pixel Size
// ROM:FF919AC4   0x3C0 = 960 pixel
// ROM:FF919AC0   0x10E = 270 pixel
// ROM:FF9013D8   0x2D0 = 720 pixel
// ROM:FF9013E0   0xF0  = 240 pixel
// ROM:FF85B138 #240
// ROM:FF85B148 #480
// ROM:FF85B160 #720
// ROM:FF85B174 #960

// http://chdk.setepontos.com/index.php?topic=3410.msg32043#msg32043

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

// ROM:FF9013D8 0x2D0 = 720 ?!?
// SD990 ROM:FF83CFC8 ?!?
long vid_get_bitmap_screen_width() {
    //return 320;
    //return 360;
    return 480;
    //return 720;
    //return 960;
}

long vid_get_bitmap_screen_height() {
    return 240;
    //return 270;
    //return 360;
}

// if buffer width was to small, CHDK Logo was shown as distorted "row" on Display
long vid_get_bitmap_buffer_width() {
    //return 360;
    //return 480;
    //return 720;
    return 960;    // working
}

long vid_get_bitmap_buffer_height() {
    //return 240;
    return 270;
    //return 360;
    //return 480;
}

/*
int vid_get_viewport_width() {
    //return 360;    // viewport is still 360, even though live view is 720 (from SD990)
    return 480;
    //return ((mode_get()&MODE_MASK) == MODE_PLAY)?480:360;     // return different width in PLAYBACK/RECORD mode
}
*/

// http://chdk.setepontos.com/index.php?topic=6037.msg62190#msg62190
int vid_get_viewport_width() {
    //if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 0)    // On 16:9 (Widescreen) resolution PROPCASE_ASPECT_RATIO = 0
    //    return 480;
    //else
        return 360;
}

/*
int vid_get_viewport_xoffset() {
    if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 0)
        return 0;
    else
        return 60;
}

int vid_get_viewport_image_offset() {
    return (vid_get_viewport_yoffset() * vid_get_viewport_buffer_width() + vid_get_viewport_xoffset()) * 3;
}

int vid_get_viewport_row_offset() {
    return (vid_get_viewport_buffer_width() - vid_get_viewport_width()) * 3;
}
*/

long vid_get_viewport_height() {
    //return 240;
    return 270;
}

/*
// from SX30, suggested by philmoz
long vid_get_viewport_height() {
    if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1)    // Wide screen top & bottom 30 pixels not used in viewport
        return 180;
    return 240;
}

// from SX30, suggested by philmoz
int vid_get_viewport_yoffset() {
    if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1)    // Wide screen top & bottom 30 pixels not used in viewport
        return 30;
    return 0;
}
*/
