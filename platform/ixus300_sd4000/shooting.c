#include "platform.h"

// Camera Parameter Number of Image Filenumber
// wrong PARAM_FILE_COUNTER cause camera shutdown if RAW is enabled or wrong number in RAW filename (for example always CRW_0001.CRW)
// use "Debug Paramenters -> Debug data display -> Params" to verify
// 0x93 = 147, count of available Camera Parameter
#define PARAM_FILE_COUNTER      0x3A

// PropertyCase 23 (and PROPCASE_USER_AV 26)
// Set AV Value in Canon Menu and watch PropertyCase Value with "Debug data display"
// ToDo: must id start from 1 because id = 0 is off ?
const ApertureSize aperture_sizes_table[] = {
    // id, prop_id, name (typedef for ApertureSize struct is in platform.h)
    {  0, 200, "2.0" },
    {  1, 224, "2.2" },
    {  2, 256, "2.5" },
    {  3, 288, "2.8" },
    {  4, 320, "3.2" },
    {  5, 352, "3.5" },
    {  6, 384, "4.0" },
    {  7, 416, "4.5" },
    {  8, 448, "5.0" },
    {  9, 480, "5.6" },
    { 10, 512, "6.3" },
    { 11, 544, "7.1" },
    { 12, 576, "8.0" },
};

// ToDo
// ROM:FFC15ED0
const ShutterSpeed shutter_speeds_table[] = {
    // id, prop_id, name, usec
    { -12, -384, "15", 15000000 },
    { -11, -352, "13", 13000000 },
    { -10, -320, "10", 10000000 },
    {  -9, -288, "8",   8000000 },
    {  -8, -256, "6",   6000000 },
    {  -7, -224, "5",   5000000 },
    {  -6, -192, "4",   4000000 },
    {  -5, -160, "3.2", 3200000 },
    {  -4, -128, "2.5", 2500000 },
    {  -3,  -96, "2",   2000000 },
    {  -2,  -64, "1.6", 1600000 },
    {  -1,  -32, "1.3", 1300000 },
    {   0,    0, "1",   1000000 },
    {   1,   32, "0.8",  800000 },
    {   2,   64, "0.6",  600000 },
    {   3,   96, "0.5",  500000 },
    {   4,  128, "0.4",  400000 },
    {   5,  160, "0.3",  300000 },
    {   6,  192, "1/4",  250000 },
    {   7,  224, "1/5",  200000 },
    {   8,  256, "1/6",  166667 },
    {   9,  288, "1/8",  125000 },
    {  10,  320, "1/10", 100000 },
    {  11,  352, "1/13",  76923 },
    {  12,  384, "1/15",  66667 },
    {  13,  416, "1/20",  50000 },
    {  14,  448, "1/25",  40000 },
    {  15,  480, "1/30",  33333 },
    {  16,  512, "1/40",  25000 },
    {  17,  544, "1/50",  20000 },
    {  18,  576, "1/60",  16667 },
    {  19,  608, "1/80",  12500 },
    {  20,  640, "1/100", 10000 },
    {  21,  672, "1/125",  8000 },
    {  22,  704, "1/160",  6250 },
    {  23,  736, "1/200",  5000 },
    {  24,  768, "1/250",  4000 },
    {  25,  800, "1/320",  3125 },
    {  26,  832, "1/400",  2500 },
    {  27,  864, "1/500",  2000 },
    {  28,  896, "1/640",  1563 },
    {  29,  928, "1/800",  1250 },
    {  30,  960, "1/1000", 1000 },
    {  31,  992, "1/1250",  800 },
    {  32, 1021, "1/1600",  625 },
    {  33, 1053, "1/2000",  500 },   // Canon Website says max. 1/2000
    //{  34, ????, "1/2500",  ??? },   // Manual says max. 1/2500 ?!?
};

// Propertycase 149
const ISOTable iso_table[] = {
    // id, prop_id, name, shutter_dfs_value
    {  0,    0, "Auto", -1},
    {  1,  125,  "125", -1},
    {  2,  200,  "200", -1},
    {  3,  400,  "400", -1},
    {  4,  800,  "800", -1},
    {  5, 1600, "1600", -1},
    {  6, 3200, "3200", -1},
};

/*
http://www.usa.canon.com/cusa/consumer/products/cameras/digital_cameras/powershot_sd4000_is?selectedName=Specifications
Shooting Modes:
Auto*, Av, Tv, P, Portrait, Night Snapshot, Kids & Pets, Indoor, Smart Shutter, High-Speed Burst, Low Light, Color Accent, Color Swap, Fisheye Effect, Miniature Effect, Beach, Foliage, Snow, Fireworks, Stitch Assist
Movie: 1280 x 720(30 fps), 640 x 480 (30 fps/), 320 x 240 (30 fps), 320 x 240 (240 fps, Super Slow Motion Movie)
*/

// PROPCASE 49
// Mapping between camera mode and PROPCASE_SHOOTING_MODE (modelist.h)
static const CapturemodeMap modemap[] = {
    { MODE_AUTO,               32768 },
    { MODE_P,                  32772 },
    { MODE_TV,                 32771 },
    { MODE_AV,                 32770 },
    { MODE_STITCH,             33292 },
    { MODE_SCN_FOLIAGE,        32789 },
    { MODE_SCN_SNOW,           32790 },
    { MODE_SCN_BEACH,          32791 },
    { MODE_SCN_FIREWORK,       32792 },
    { MODE_INDOOR,             32787 },
    { MODE_KIDS_PETS,          32786 },
    { MODE_NIGHT_SNAPSHOT,     32781 },
    { MODE_PORTRAIT,           32783 },
    { MODE_LOWLIGHT,           32801 },
    { MODE_COLOR_ACCENT,       33309 },
    { MODE_COLOR_SWAP,         33310 },
    //{ MODE_SMART_SHUTTER,      33321 }, // mode does not exist in chdk
    //{ MODE_FISHEYE,            33323 }, // mode does not exist in chdk
    //{ MODE_MINIATURE,          33324 },
    //{ MODE_HIGHSPEED_BURST,    32288 }, // mode does not exist in chdk
    { MODE_VIDEO_STD,          2612  },
    //{ MODE_VIDEO_SLOWMOTION,   2617  },
    { MODE_VIDEO_SPEED,        2617  }, // "Super Slow Motion Movie"
    { MODE_VIDEO_COLOR_SWAP,   2611  },
    { MODE_VIDEO_COLOR_ACCENT, 2610  },
};

#include "../generic/shooting.c"

const int dof_tbl[] = {5800, 6420, 7060, 7700, 8340, 9950, 11550, 13160, 14750, 17150, 19570, 22760, 26750, 30750, 34800};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

long get_file_next_counter() {
    return get_file_counter();
}

long get_target_file_num() {
    long n;

    n = get_file_next_counter();
    n = (n>>4)&0x3FFF;
    return n;
}

// Save RAW in correct (JPG) Folder
#if defined(CAM_DATE_FOLDER_NAMING)
    void get_target_dir_name(char *out) {
        extern void _GetImageFolder(char*,int,int,int);
        out[0] = 'A';
        _GetImageFolder(out+1,get_file_next_counter(),0x400,time(NULL));
        out[15] = '\0';
    }
#else
    long get_target_dir_num() {
        long n;

        n = get_file_next_counter();
        n = (n>>18)&0x3FF;
        return n;
    }
#endif

// ToDo
// Required for correct DOF calculation
// http://www.dofmaster.com/digital_coc.html#coccalculator
int circle_of_confusion = 5;
