// Camera - A650 - platform_camera.h

// This file contains the various settings values specific to the A650 camera.
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
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4104   // for 12 MP
    #define CAM_RAW_ROWS                3048   // for 12 MP
    
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_CAN_MUTE_MICROPHONE     1

    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      913762, 1000000, -261578, 1000000, -135582, 1000000, \
     -99049,  1000000, 1067089, 1000000,   61442, 1000000, \
      48717,  1000000, 96802,   1000000,  412056, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  4000
    #define CAM_JPEG_HEIGHT 3000
    #define CAM_ACTIVE_AREA_X1 52
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 4076
    #define CAM_ACTIVE_AREA_Y2 3030
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

    #define DNG_EXT_FROM ".CR2"
//----------------------------------------------------------

