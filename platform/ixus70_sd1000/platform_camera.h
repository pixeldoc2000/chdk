// Camera - IXUS70_SD1000 - platform_camera.h

// This file contains the various settings values specific to the IXUS70_SD1000 camera.
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

    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_MULTIPART               1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      652674,  1000000, -172074, 1000000, -107575, 1000000, \
      -139063, 1000000, 594517,  1000000,  60252,  1000000, \
       -9088,  1000000, 82013,   1000000,  238048, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1
//----------------------------------------------------------

