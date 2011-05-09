// camera.h

// This file contains the default values for various settings that may change across camera models.
// Setting values specific to each camera model can be found in the platform/XXX/platform_camera.h file for camera.

// If adding a new settings value put a suitable default value in here, along with documentation on
// what the setting does and how to determine the correct value.
// If the setting should not have a default value then add it here using the '#undef' directive
// along with appropriate documentation.

#ifndef CAMERA_H
#define CAMERA_H

//==========================================================
// Camera-dependent settings
//==========================================================

//----------------------------------------------------------
// Default values
//----------------------------------------------------------

#undef  CAM_DRYOS                               // Camera is DryOS-based
#undef  CAM_PROPSET                             // Camera's properties group (the generation)

#undef  CAM_SWIVEL_SCREEN                       // Camera has rotated LCD screen
#define CAM_USE_ZOOM_FOR_MF         1           // Zoom lever can be used for manual focus adjustments
#undef  CAM_ADJUSTABLE_ALT_BUTTON               // ALT-button can be set from menu
#define CAM_REMOTE                  1           // Camera supports USB-remote
#undef  SYNCHABLE_REMOTE_NOT_ENABLED            // Disable support for synchable remote switch (in kbd.c) TODO only used by one camera ???
#define CAM_SYNCH                   1           // Camera supports SDM precision synch
#undef  CAM_MULTIPART                           // Camera supports SD-card multipartitioning
#define CAM_HAS_ZOOM_LEVER          1           // Camera has dedicated zoom buttons
#undef  CAM_DRAW_EXPOSITION                     // Output expo-pair on screen (for cameras which (sometimes) don't do that)
#define CAM_HAS_ERASE_BUTTON        1           // Camera has dedicated erase button
#define CAM_HAS_IRIS_DIAPHRAGM      1           // Camera has real diaphragm mechanism
#undef  CAM_HAS_ND_FILTER                       // Camera has build-in ND filter
#define CAM_CAN_SD_OVER_NOT_IN_MF   1           // Camera allows subject distance (focus) override when not in manual focus mode
#define CAM_CAN_SD_OVERRIDE         1           // Camera allows to do subject distance override
#define CAM_HAS_MANUAL_FOCUS        1           // Camera has manual focus mode
#define CAM_HAS_USER_TV_MODES       1           // Camera has tv-priority or manual modes with ability to set tv value
#undef  CAM_SHOW_OSD_IN_SHOOT_MENU              // On some cameras Canon shoot menu has additional functionality and useful in this case to see CHDK OSD in this mode
#define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1 // Camera can unlock optical zoom in video (if it is locked)
#undef  CAM_FEATURE_FEATHER                     // Cameras with "feather" or touch wheel.
#define CAM_HAS_IS                  1           // Camera has image stabilizer
#undef  CAM_HAS_JOGDIAL                         // Camera has a "jog dial"

#undef  CAM_CONSOLE_LOG_ENABLED                 // Development: internal camera stdout -> A/stdout.txt
#define CAM_CHDK_HAS_EXT_VIDEO_MENU 1           // In CHDK for this camera realized adjustable video compression
#undef  CAM_CAN_MUTE_MICROPHONE                 // Camera has function to mute microphone

#define CAM_EMUL_KEYPRESS_DELAY     40          // Delay to interpret <alt>-button press as longpress
#define CAM_EMUL_KEYPRESS_DURATION  5           // Length of keypress emulation

#define CAM_MENU_BORDERWIDTH        30          // Related to screen layout somehow.
                                                // TODO someone explain what this does, probably doesn't really belong here

#undef  CAM_AF_SCAN_DURING_VIDEO_RECORD         // CHDK can make single AF scan during video record
#undef  CAM_HAS_VIDEO_BUTTON                    // Camera can take stills in video mode, and vice versa
#undef  CAM_EV_IN_VIDEO                         // CHDK can change exposure in video mode
#define CAM_VIDEO_CONTROL           1           // pause / unpause video recordings
#undef  CAM_VIDEO_QUALITY_ONLY                  // Override Video Bitrate is not supported

#define ZOOM_OVERRIDE               0           // Shall zoom-override be used? default 0 becoz not implemented right now

#undef  CAM_REAR_CURTAIN                        // Camera do not have front/rear curtain flash sync in menu
#undef  CAM_BRACKETING                          // Cameras that have bracketing (focus & ev) in original firmware already, most likely s- & g-series (propcase for digic III not found yet!)
#undef  CAM_EXT_TV_RANGE                        // CHDK can make exposure time longer than 64s
#define CAM_CHDK_PTP                1           // include CHDK PTP support

#define CAM_UNCACHED_BIT            0x10000000  // bit indicating the uncached memory

#define CAM_MAKE                    "Canon"
#define CAM_SENSOR_BITS_PER_PIXEL   10          // Bits per pixel. 10 is standard, 12 is supported except for curves
#define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
#define CAM_BLACK_LEVEL             31

#define CAM_BITMAP_PALETTE          1           // which color set is used for this camera

#undef CAM_HAS_VARIABLE_ASPECT                  // can switch between 16:9 and 4:3

// by nandoide sept-2009
// zebra adjust buffer height: show use at sx200is: needed for save memory space
#define ZEBRA_HMARGIN0              0

// aspect corrections
#define CAM_USES_ASPECT_CORRECTION  0           // if true, camera uses a modified graphics primitives to draw with exact display aspect-ratio.
                                                // Could slow the graphics output (but not perceived on sx200is), but adds rectangle drawing optimizations to compensate.
                                                // To extend to other cameras see sx200is camera.h comments in  and comments on core gui_draw.c
#define CAM_USES_ASPECT_YCORRECTION 0

// menu, alt (default)
#define ASPECT_XCORRECTION(x)  ( ((x)<<1) )     // see comments on 200is
#define ASPECT_YCORRECTION(y)  ( (y) )          // no correction the same for coordinate y. I think there are no cameras actually needing both corrections.
// viewport, defaults used if there is no aspect correction
#define ASPECT_VIEWPORT_XCORRECTION(x) ( (x) )  // see comments on 200is
#define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )  // no correction

#define EDGE_HMARGIN                0           // define sup and inf screen margins on edge overlay without overlay.  Necessary to save memory buffer space. sx200is needs values other than 0
// end of section by nandoid

#undef CAM_QUALITY_OVERRIDE                     // camera may need shooting quality override (sx200is lacks SuperFine quality)

#undef CAM_ZEBRA_ASPECT_ADJUST                  // zebra needs to account for real bitmap size being different from what lib.c reports
                                                // also used by some cameras with normal bitmap layouts for memory saving ?
#undef CAM_ZEBRA_NOBUF                          // zebra draws directly on bitmap buffer. Requires above as well

#undef CAM_DATE_FOLDER_NAMING                   // set if camera uses date based folder naming (Option "Create Folder" in Canon Menu) and get_target_dir_name is implemented

#undef CAM_KEY_CLICK_DELAY                      // additional delay between press and release for scripted click
#define CAM_KEY_PRESS_DELAY         20          // delay after a press - TODO can we combine this with above ?
#define CAM_KEY_RELEASE_DELAY       20          // delay after a release - TODO do we really need to wait after release ?

#undef  CAM_DATE_FOLDER_NAMING                  // Camera uses date for naming image folders

#undef  CAM_STARTUP_CRASH_FILE_OPEN_FIX         // enable fix for camera crash at startup when opening the conf / font files
                                                // see http://chdk.setepontos.com/index.php?topic=6179.0

// RAW & DNG related values
#define DNG_SUPPORT                 1           // Camera supports DNG format for saving of RAW images
#define DEFAULT_RAW_EXT             1           // extension to use for raw (see raw_exts in conf.c)
#undef  CAM_RAW_ROWPIX                          // Number of pixels in RAW row (physical size of the sensor)
#undef  CAM_RAW_ROWS                            // Number of rows in RAW (physical size of the sensor)
#undef  CAM_JPEG_WIDTH                          // Default crop size (width) stored in DNG (to match camera JPEG size)
#undef  CAM_JPEG_HEIGHT                         // Default crop size (height) stored in DNG (to match camera JPEG size)
#undef  CAM_ACTIVE_AREA_X1                      // Define usable area of the sensor
#undef  CAM_ACTIVE_AREA_Y1                      // Define usable area of the sensor
#undef  CAM_ACTIVE_AREA_X2                      // Define usable area of the sensor
#undef  CAM_ACTIVE_AREA_Y2                      // Define usable area of the sensor
#undef  cam_CFAPattern                          // Camera Bayer sensor data layout
#undef  CAM_COLORMATRIX1                        // DNG color profile matrix
#undef  cam_CalibrationIlluminant1              // DNG color profile illuminant
#undef  CAM_DNG_EXPOSURE_BIAS                   // Specify DNG exposure bias value (to override default of -0.5 in the dng.c code)
#undef  DNG_EXT_FROM                            // Extension in the cameras known extensions to replace with .DNG to allow DNG
                                                // files to be transfered over standard PTP. Only applicable to older cameras

// Games definitions
#define GAMES_SCREEN_WIDTH            360        // Logical screen width for games
#define GAMES_SCREEN_HEIGHT            240       // Logical screen height for games
#define ASPECT_GAMES_XCORRECTION(x)    ((x)<<1)  // Aspect ratio correction for games. Default for games is 360x240 logical screen. Physical camera screen is
#define ASPECT_GAMES_YCORRECTION(y)    (y)       // 720x240 so x*2 needed for X axis correction, no correction for Y.

// Grid definitions
#define ASPECT_GRID_XCORRECTION(x)    (x)        // Aspect ratio correction for grids. Grids are designed on a 360x240 logical screen size which matches the
#define ASPECT_GRID_YCORRECTION(y)    (y)        // default CHDK logical screen size so no correction needed.

#undef    PARAM_CAMERA_NAME                      // parameter number for GetParameterData to get camera name


#undef  CAM_FIRMWARE_MEMINFO                    // Use 'GetMemInfo' (dryos) or 'memPartInfoGet'/'memPartFindMax' (vxworks)
                                                // function in firmware to get free memory details
                                                // GetMemInfo should be found correctly by the gensig/finsig signature
                                                // finder for all dryos based cameras.

#undef CAM_NO_MEMPART_INFO                      // VXWORKS camera does not have memPartInfoGet, fall back to memPartFindMax
//----------------------------------------------------------
// Override Default values for Camera if necessary
//----------------------------------------------------------

// Include the settings file for the camera model currently being compiled.
#include "platform_camera.h"

//==========================================================
// END of Camera-dependent settings
//==========================================================


// curves only work in 10bpp for now
#if CAM_SENSOR_BITS_PER_PIXEL != 10
#undef OPT_CURVES
#endif

#ifndef OPT_PTP
#undef CAM_CHDK_PTP
#endif

#endif /* CAMERA_H */
