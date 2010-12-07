#ifndef PROPSET4_H
#define PROPSET4_H
/*
constants for propset 4
WARNING:
 The build uses tools/gen_propset_lua.sed to generate propset4.lua from this file
*/
#define PROPCASE_DRIVE_MODE                 102
#define PROPCASE_FOCUS_MODE                 133
#define PROPCASE_FLASH_MODE                 143     // SD4000
#define PROPCASE_FLASH_FIRE                 122
#define PROPCASE_FLASH_MANUAL_OUTPUT        141
#define PROPCASE_FLASH_ADJUST_MODE          121
#define PROPCASE_USER_TV                    266     // SD4000
#define PROPCASE_TV                         264
#define PROPCASE_USER_AV                    26      // SD4000
#define PROPCASE_AV                         23
#define PROPCASE_MIN_AV                     25
#define PROPCASE_SV                         249
#define PROPCASE_DELTA_SV                   79
#define PROPCASE_SV_MARKET                  248
#define PROPCASE_BV                         34
#define PROPCASE_SUBJECT_DIST1              247
#define PROPCASE_SUBJECT_DIST2              65
#define PROPCASE_ISO_MODE                   149     // SD4000
#define PROPCASE_SHOOTING                   208
#define PROPCASE_IS_FLASH_READY             210
#define PROPCASE_OVEREXPOSURE               103
#define PROPCASE_SHOOTING_MODE              49      // SD4000
#define PROPCASE_IS_MODE                    145
#define PROPCASE_QUALITY                    57
#define PROPCASE_RESOLUTION                 220
#define PROPCASE_EV_CORRECTION_1            107
#define PROPCASE_EV_CORRECTION_2            209
#define PROPCASE_ORIENTATION_SENSOR         221     // SD4000
#define PROPCASE_DIGITAL_ZOOM_STATE         94
#define PROPCASE_DIGITAL_ZOOM_POSITION      95
#define PROPCASE_DISPLAY_MODE               105
#define PROPCASE_BRACKET_MODE               29
#define PROPCASE_FLASH_SYNC_CURTAIN         64
#define PROPCASE_METERING_MODE              155     // SD4000
#define PROPCASE_WB_ADJ                     271     // SD4000
//#define PROPCASE_ASPECT_RATIO               294     // propset3.h
#define PROPCASE_ASPECT_RATIO               215     // changed on SD4000, was 294 in propset 3
#define PROPCASE_TIMER_MODE                 225
#define PROPCASE_OPTICAL_ZOOM_POSITION      197
#endif