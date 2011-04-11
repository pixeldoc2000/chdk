// Camera - A610 - platform_camera.h

// This file contains the various settings values specific to the A610 camera.
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

    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_MULTIPART               1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
    #define CAM_EXT_TV_RANGE            1

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      15887,  10000, -6524, 10000, -1622, 10000,           \
     -5467,   10000, 13449, 10000,  2209, 10000,           \
     -1325,   10000, 1859,  10000,  5172, 10000
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 14
    #define CAM_ACTIVE_AREA_Y1 10
    #define CAM_ACTIVE_AREA_X2 2626
    #define CAM_ACTIVE_AREA_Y2 1966
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

    #define DNG_EXT_FROM ".DPS"
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support
//----------------------------------------------------------

