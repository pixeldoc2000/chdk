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
#define PROPCASE_TV                         264     // SD4000
#define PROPCASE_USER_AV                    26      // SD4000
#define PROPCASE_AV                         23      // SD4000
#define PROPCASE_MIN_AV                     25
#define PROPCASE_SV                         249     // SD4000 249 = SvFix, 248 = SV
#define PROPCASE_DELTA_SV                   79
#define PROPCASE_SV_MARKET                  248
#define PROPCASE_BV                         34      // SD4000
#define PROPCASE_SUBJECT_DIST1              247
#define PROPCASE_SUBJECT_DIST2              65
#define PROPCASE_ISO_MODE                   149     // SD4000
#define PROPCASE_SHOOTING                   208     // https://github.com/emlyn/chdk/issues#issue/11 maybe PropSet 96 ?!?
#define PROPCASE_IS_FLASH_READY             210     // SD4000
#define PROPCASE_OVEREXPOSURE               103
#define PROPCASE_SHOOTING_MODE              49      // SD4000
#define PROPCASE_IS_MODE                    145     // SD4000 (IS Mode: 0 = Continous, 4 = Off, 2 = Shoot Only, 3 = Panning)
#define PROPCASE_QUALITY                    57      // SD4000 (Compression: 1 = Fine, 2 = Normal)
#define PROPCASE_RESOLUTION                 220     // SD4000 (0 = L, 1 = M1, 2 = M2, 3 = M3, 4 = S, 8 = Widescreen)
#define PROPCASE_EV_CORRECTION_1            107
#define PROPCASE_EV_CORRECTION_2            209
#define PROPCASE_ORIENTATION_SENSOR         221     // SD4000 (0, 270, 90)
#define PROPCASE_DIGITAL_ZOOM_STATE         94      // SD4000 (Digital Zoom: 0 = disabled, 1 = enabled (Setting default))
#define PROPCASE_DIGITAL_ZOOM_POSITION      95      // SD4000 (0 - 6)
#define PROPCASE_DISPLAY_MODE               105
#define PROPCASE_BRACKET_MODE               29
#define PROPCASE_FLASH_SYNC_CURTAIN         64
#define PROPCASE_METERING_MODE              155     // SD4000
#define PROPCASE_WB_ADJ                     271     // SD4000
#define PROPCASE_ASPECT_RATIO               294     // probably changed or not existing on SD4000, should this change if Widescreen resolution is in use ?!?
//#define PROPCASE_ASPECT_RATIO               215
#define PROPCASE_TIMER_MODE                 225     // SD4000 (Self Timer: 1 = Off, 2 = 10 Sec., 1 = 2 Sec., 3 = Custom Timer)
#define PROPCASE_OPTICAL_ZOOM_POSITION      197     // SD4000 (0 - 63, 0 = 1.0, 63 = 3.8x)
#endif
