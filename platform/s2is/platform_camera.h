// Camera - S2IS - platform_camera.h

// This file contains the various settings values specific to the S2IS camera.
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

    #undef  CAM_SYNCH   
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define  CAM_HAS_VIDEO_BUTTON       1
    #undef  CAM_VIDEO_CONTROL
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      547708,  1000000, -143462, 1000000,  -99243, 1000000, \
     -186838,  1000000, 663925,  1000000,   50970, 1000000, \
     -5810,    1000000, 79162,   1000000,  266988, 1000000

    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 14
    #define CAM_ACTIVE_AREA_Y1 10
    #define CAM_ACTIVE_AREA_X2 2626
    #define CAM_ACTIVE_AREA_Y2 1966
    // camera name
    #define PARAM_CAMERA_NAME 2 // parameter number for GetParameterData
    #define CAM_BRACKETING              1
    #define DNG_EXT_FROM ".DPS"
//----------------------------------------------------------

