#ifndef PROPSET4_H
#define PROPSET4_H

/*
constants for propset 4
WARNING:
The build uses tools/gen_propset_lua.sed to generate propset4.lua from this file
*/

#define PROPCASE_FLASH_SYNC_CURTAIN              64
#define PROPCASE_SUBJECT_DIST2                   65
#define PROPCASE_AV                              23
#define PROPCASE_MIN_AV                          25
#define PROPCASE_USER_AV                         26
#define PROPCASE_BRACKET_MODE                    29
#define PROPCASE_SHOOTING_MODE                   49
#define PROPCASE_QUALITY                         57
#define PROPCASE_DIGITAL_ZOOM_MODE               91		// Digital Zoom Mode/State 0 = off/standard, 2 = 1.7x, 3 = 2.1x
#define PROPCASE_DIGITAL_ZOOM_STATE              94		// Digital Zoom Mode/State 0 = Digital Zoom off, 1 = Digital Zoom on
#define PROPCASE_DIGITAL_ZOOM_POSITION           95
#define PROPCASE_DRIVE_MODE                      102
#define PROPCASE_OVEREXPOSURE                    103
#define PROPCASE_DISPLAY_MODE                    105
#define PROPCASE_EV_CORRECTION_1                 107

#define PROPCASE_BV                              34
#define PROPCASE_DELTA_SV                        79
#define PROPCASE_FLASH_ADJUST_MODE               121
#define PROPCASE_FLASH_FIRE                      122
#define PROPCASE_FOCUS_MODE                      133
#define PROPCASE_FLASH_MANUAL_OUTPUT             141
#define PROPCASE_FLASH_MODE                      143
#define PROPCASE_IS_MODE                         145
#define PROPCASE_ISO_MODE                        149

// SX30 & G12 values
#define	PROPCASE_AE_LOCK						 3		// 0 = AE not locked, 1 = AE locked
#define	PROPCASE_AF_FRAME						 8		// 1 = FlexiZone, 2 = Face AiAF / Tracking AF
#define	PROPCASE_CONTINUOUS_AF					 12		// 0 = Continuous AF off, 1 = Continuous AF on
#define	PROPCASE_SERVO_AF						 299	// 0 = Servo AF off, 1 = Servo AF on
#define PROPCASE_METERING_MODE                   157
#define PROPCASE_OPTICAL_ZOOM_POSITION           199
#define PROPCASE_SHOOTING                        210
#define PROPCASE_EV_CORRECTION_2                 211
#define PROPCASE_IS_FLASH_READY                  212
#define PROPCASE_RESOLUTION                      222
#define PROPCASE_ORIENTATION_SENSOR              223
#define PROPCASE_TIMER_MODE                      227
#define PROPCASE_SUBJECT_DIST1                   249
#define PROPCASE_SV_MARKET                       250
#define PROPCASE_SV                              251
#define PROPCASE_TV	                             266
#define PROPCASE_USER_TV                         268
#define PROPCASE_WB_ADJ                          273
#define PROPCASE_ASPECT_RATIO                    300

#endif
