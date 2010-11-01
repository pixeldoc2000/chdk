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

// ToDo: switch_mode_usb() does not work, used by PTPcam chdk cli "mode" command
/*
// PTP stuff
extern void _set_control_event(int);
extern void _PB2Rec();
extern void _Rec2PB();
int switch_mode_usb(int mode) {
  if ( mode == 0 ) {
    _Rec2PB();
    //_set_control_event(0x80000902); // 0x10A5 ConnectUSBCable
    //_set_control_event(0x10A5); // 0x10A5 ConnectUSBCable
    _PostLogicalEventForNotPowerType(0x10A5, 2);  // ConnectUSBCable at levent_table
  } else if ( mode == 1 ) {
    //_set_control_event(0x902); // 0x10A6 DisconnectUSBCable
    //_set_control_event(0x10A6); // 0x10A6 DisconnectUSBCable
    _PostLogicalEventForNotPowerType(0x10A6, 2);  // DisconnectUSBCable at levent_table
    _PB2Rec();
  } else {
    return 0;
  }

  return 1;
}
*/
