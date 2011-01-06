#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"


extern long link_bss_start;
extern long link_bss_end;
extern void boot();


void startup() {
    long *bss = &link_bss_start;
    long *ptr;

    //debug_led(1);
    //debug_led(0);

    // sanity check
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)) {
        started();
        shutdown();
    }

    // initialize .bss senment
    while (bss<&link_bss_end)
        *bss++ = 0;

    //debug_led(1);
    //debug_led(0);

    boot();
}

// F/2.0 - 5.3
// 4.9 - 18.6mm
static const int fl_tbl[] = {5800, 6420, 7060, 7700, 8340, 9950, 11550, 13160, 14750, 17150, 19570, 22760, 26750, 30750, 34800};    // ToDo, convert a focus position to a focal length (* 1000), http://chdk.setepontos.com/index.php?topic=5722.msg59333#msg59333
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 60345    // ToDo, convert a camera focal length to a 35mm effective focal length, http://chdk.setepontos.com/index.php?topic=5722.msg59333#msg59333

const int zoom_points = NUM_FL;

// ToDo, http://chdk.setepontos.com/index.php?topic=5722.msg59333#msg59333
int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/10000;
}

// ToDo
int get_focal_length(int zp) {
    if (zp<0) return fl_tbl[0];
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1];
    else return fl_tbl[zp];
}

// ToDo
int get_zoom_x(int zp) {
    if (zp<1) return 10;
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1]*10/fl_tbl[0];
    else return fl_tbl[zp]*10/fl_tbl[0];
}

/*
int rec_switch_state(void) {
    return (physw_status[1] & 0x02000000);
}
*/

// Battery default min. Voltage
long get_vbatt_min() {
    return 3200;    // ToDo: use real value, this is just a guess
}

// Battery default max. Voltage
long get_vbatt_max() {
    return 4100;    // ToDo: use real value, this is just a guess
}

// NEXT: platform/ixus300_sd4000/sub/100d/boot.c boot()
