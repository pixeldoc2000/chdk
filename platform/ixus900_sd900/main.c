#include "../generic/main.c"

static const int fl_tbl[] = {4600, 6140, 7560, 9110, 10830, 12670, 14690, 17300};   // exif value for each zoom step (3x zoom lens)
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 47946   // 60345 for 1/2.5" sensor, 47946 for 1/1.8" sensor

const int zoom_points = NUM_FL;

long get_vbatt_min() {
    return 3500;
}

long get_vbatt_max() {
    return 4100;
}

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/10000;
}

int get_focal_length(int zp) {
    if (zp<0) return fl_tbl[0];
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1];
    else return fl_tbl[zp];
}

int get_zoom_x(int zp) {
    if (zp<1) return 10;
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1]*10/fl_tbl[0];
    else return fl_tbl[zp]*10/fl_tbl[0];
}

// Mapping between camera mode and PROPCASE_SHOOTING_MODE
static struct {
    int hackmode;
    int canonmode;
} modemap[] = {   // PROPCASE 0, check with CHDK debug menu option "Show Parameter Data 0"
    {MODE_AUTO,               32768},
    {MODE_M,                  33772},
    {MODE_DIGITAL_MACRO,      33288},
    {MODE_STITCH,             33290},
    {MODE_COLOR_ACCENT,       33305},
    {MODE_MY_COLORS,          33306},   // mode M "color swap" ???
    //{MODE_NIGHT_SNAPSHOT,     16395},   // mode SCN NIGHT SNAPSHOT ???
    {MODE_SCN_NIGHT,          16395},   // mode SCN NIGHT SNAPSHOT ???
    {MODE_SCN_PORTRAIT,       16397},
    {MODE_SCN_KIDS_PETS,      16399},
    {MODE_SCN_INDOOR,         16400},
    {MODE_SCN_FOLIAGE,        16401},
    {MODE_SCN_SNOW,           16402},
    {MODE_SCN_BEACH,          16403},
    {MODE_SCN_FIREWORK,       16404},
    {MODE_SCN_WATER,          16405},   // mode SCN "underwater" ???
    {MODE_SCN_AQUARIUM,       16406},
    {MODE_SCN_ISO_3200,       16411},
    {MODE_VIDEO_STD,          2596},
    {MODE_VIDEO_COLOR_ACCENT, 2594},
    {MODE_VIDEO_COLOR_SWAP,   2595},
    {MODE_VIDEO_COMPACT,      2598},
    {MODE_VIDEO_HIRES,        2599},
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[2] & 0x4000)?MODE_REC:MODE_PLAY;
    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
        if (modemap[i].canonmode == t) {
            return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
        }
    }
    return (mode);
}
