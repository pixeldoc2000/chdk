#define PARAM_FILE_COUNTER      0x34   // ??? 0x34 , 0x37 count of available camera params?

#include "platform.h"

// PROPCASE_AV (68)
// take a picture at every zoom step, note each PROPCASE_AV value, repead this with very bright pictures where camera puts in ND (photograph a lamp). Than look at the Aperture EXIF of the picture.
const ApertureSize aperture_sizes_table[] = {
    { 9, 294, "2.8"},   // Zoom 2.8x, without ND
    {10, 309, "3.2"},
    {11, 328, "3.5"},
    {12, 353, "3.5"},
    {13, 385, "4.0"},
    {14, 416, "4.5"},
    {15, 449, "4.9"},   // Zoom 4.9x, without ND
    {16, 556, "8.0 ND"},   // Zoom 2.8x , with canon ND (very bright)
    {17, 571, "8.0 ND"},
    {18, 590, "9.0 ND"},
    {19, 615, "10.0 ND"},
    {20, 647, "11.0 ND"},
    {21, 678, "13.0 ND"},
    {22, 711, "14.1 ND"},   // Zoom 4.9x , with canon ND (very bright)
};

// PROPCASE_TV (69) ROM:FF9AFCCC
// value are more or less generic. look at max. supported Shutter speed "1/2000" at technical specs in manual (pdf canon website)
const ShutterSpeed shutter_speeds_table[] = {
    // # , PropCase value, displayed string, shutter value
    {-12, -384, "15", 15000000},   // PROPCASE_TV = 65152, 1000000 * 15 = 15000000
    {-11, -352, "13", 13000000},   // 65184
    {-10, -320, "10", 10000000},   // 65218
    { -9, -288, "8",   8000000},   // 65248
    { -8, -256, "6",   6000000},   // 65280
    { -7, -224, "5",   5000000},   // 65312
    { -6, -192, "4",   4000000},   // 65344
    { -5, -160, "3.2", 3200000},   // 65376
    { -4, -128, "2.5", 2500000},   // 65408
    { -3,  -96, "2",   2000000},   // 65440
    { -2,  -64, "1.6", 1600000},   // 65472
    { -1,  -32, "1.3", 1300000},   // 65504
    {  0,    0, "1",   1000000},   // PROPCASE_TV = 0
    {  1,   32, "0.8",  800000},   // PROPCASE_TV = 32, 1000000 / 0.8 = 800000
    {  2,   64, "0.6",  600000},   // ...
    {  3,   96, "0.5",  500000},
    {  4,  128, "0.4",  400000},
    {  5,  160, "0.3",  300000},
    {  6,  192, "1/4",  250000},
    {  7,  224, "1/5",  200000},
    {  8,  256, "1/6",  166667},
    {  9,  288, "1/8",  125000},
    { 10,  320, "1/10", 100000},
    { 11,  352, "1/13",  76923},
    { 12,  384, "1/15",  66667},
    { 13,  416, "1/20",  50000},
    { 14,  448, "1/25",  40000},
    { 15,  480, "1/30",  33333},
    { 16,  512, "1/40",  25000},
    { 17,  544, "1/50",  20000},
    { 18,  576, "1/60",  16667},
    { 19,  608, "1/80",  12500},
    { 20,  640, "1/100", 10000},
    { 21,  672, "1/125",  8000},
    { 22,  704, "1/160",  6250},
    { 23,  736, "1/200",  5000},
    { 24,  768, "1/250",  4000},
    { 25,  800, "1/320",  3125},
    { 26,  832, "1/400",  2500},
    { 27,  864, "1/500",  2000},
    { 28,  896, "1/640",  1563},
    { 29,  928, "1/800",  1250},
    { 30,  960, "1/1000", 1000},
    { 31,  992, "1/1250",  800},
    { 32, 1024, "1/1600",  625},
    { 33, 1056, "1/2000",  500},
};

// PROPCASE_ISO_MODE (25/26)
// go through every ISO setting in manual mode and note PROPCASE_ISO_MODE value
const ISOTable iso_table[] = {
    {-1,     1,    "HI", -1},
    { 0,     0,  "Auto", -1},
    { 1,    80,    "80", -1},
    { 2,   100,   "100", -1},
    { 3,   200,   "200", -1},
    { 4,   400,   "400", -1},
    { 5,   800,   "800", -1},
    { 6,  1600,  "1600", -1},
};

#include "../generic/shooting.c"

long get_file_next_counter() {
    return get_file_counter();
}

long get_target_file_num() {
    long n;
    n = get_file_next_counter();
    n = (n>>4)&0x3FFF;
    return n;
}

long get_target_dir_num() {
    long n;
    n = get_file_next_counter();
    n = (n>>18)&0x3FF;
    return n;
}

int circle_of_confusion = 5;    // :-)

// gets PROPCASE_TV value and compare it with shutter_speeds_table
char* shooting_get_tv_str() {
    short int tvv;
    long i;
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++) {
        if (shutter_speeds_table[i].prop_id >= tvv)
            return (char*)shutter_speeds_table[i].name;
    }
    return (void*)"?";
}

// gets PROPCASE_AV value and compare it with aperture_sizes_table
char* shooting_get_av_str() {
    short int avv;
    long i;
    _GetPropertyCase(PROPCASE_AV, &avv, sizeof(avv));
    for (i=0;i<AS_SIZE;i++) {
        if (aperture_sizes_table[i].prop_id == avv)
            return (char*)aperture_sizes_table[i].name;
    }
    return (char*) "?";
}

// Get PROPCASE_ISO_MODE and compare it with iso_table
char* shooting_get_iso_str() {
    short int isov;
    long i;
    _GetPropertyCase(PROPCASE_ISO_MODE, &isov, sizeof(isov));
    for (i=0;i<ISO_SIZE;i++) {
        if (iso_table[i].prop_id == isov)
            return (char*)iso_table[i].name;
    }
    return (char*) "?";
}
