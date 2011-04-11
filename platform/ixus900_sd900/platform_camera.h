// Camera - IXUS900_SD900 - platform_camera.h

// This file contains the various settings values specific to the IXUS900_SD900 camera.
// This file is referenced via the 'include/camera.h' file and should not be loaded directly.

// If adding a new settings value put a suitable default in 'include/camera.h',
// along with documentation on what the setting does and how to determine the correct value.
// If the setting should not have a default value then add it in 'include/camera.h'
// using the '#undef' directive along with appropriate documentation.

// Override any default values with your camera specific values in this file. Try and avoid
// having override values that are the same as the default value.

// When overriding a setting value there are two cases:
// 1. If removing the value, because it does not apply to your camera, use the '#undef' directive.
// 2. If changing the value it is best to use an '#undef' directive to remove the default value
//    followed by a '#define' to set the new value.

// When porting CHDK to a new camera, check the documentation in 'include/camera.h'
// for information on each setting. If the default values are correct for your camera then
// don't override them again in here.

    #define CAM_PROPSET                 1   // ToDo: test if correct

    #define CAM_RAW_ROWPIX              3672   // value from RAW file (3648px + 24px)
    #define CAM_RAW_ROWS                2760   // value from RAW file (2736 + 24px)

    //#undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION         1   // ToDo: test if required
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    //#undef  CAM_CAN_SD_OVER_NOT_IN_MF
    //#undef  CAM_CAN_SD_OVERRIDE
    #undef  CAM_HAS_IS
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1   // force CHDK OSD to show in record more
    #define CAM_FEATURE_FEATHER         1
    //#define CAM_CONSOLE_LOG_ENABLED     1   // ToDo: LOG stuff is disabled/removed
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_MULTIPART               1

    // pattern
    #define cam_CFAPattern 0x02010100   // Red  Green  Green  Blue
    // color (from G7)
    #define CAM_COLORMATRIX1                              \
      575419, 1000000,-185557, 1000000, -77898,  1000000, \
     -213702, 1000000, 733569, 1000000,   81514, 1000000, \
      -24604, 1000000, 131906, 1000000,  280378, 1000000
    /*
    // SD800
    #define CAM_COLORMATRIX1                               \
      661014, 1000000, -189364, 1000000, -115797, 1000000, \
     -168772, 1000000,  661827, 1000000,   47392, 1000000, \
      -35846, 1000000,  107148, 1000000,  233705, 1000000
    */
    #define cam_CalibrationIlluminant1 1   // ToDo: Daylight (first selectable Illuminant Calibration mode ?)

    // cropping
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 14   // ??? from G7, A640
    #define CAM_ACTIVE_AREA_Y1 8   // ??? from G7, A640
    //#define CAM_ACTIVE_AREA_X2 3672   // from RAW file
    //#define CAM_ACTIVE_AREA_Y2 2760   // from RAW file
    #define CAM_ACTIVE_AREA_X2 3682   // ??? from G7, A640, CAM_JPEG_WIDTH + 40
    #define CAM_ACTIVE_AREA_Y2 2764   // ??? from G7, A640, CAM_JPEG_HEIGHT + 40
    // camera name
    #define PARAM_CAMERA_NAME 4   // camera param id of EXIF camera model

    #define DNG_EXT_TO   ".DPS"		// Should this be 'DNG_EXT_FROM' ???
//----------------------------------------------------------

