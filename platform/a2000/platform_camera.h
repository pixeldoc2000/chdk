// Camera - A2000 - platform_camera.h

// This file contains the various settings values specific to the A2000 camera.
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

	////////////////////////////////
	// Sure values
	////////////////////////////////
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3720  
    #define CAM_RAW_ROWS                2772  

    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736


    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

    ////////////////////////////////
    // Almost sure, sensor data taken from 
    // ixus870_sd880 which should have same sensor..
    ////////////////////////////////
    #undef CAM_SENSOR_BITS_PER_PIXEL
    #undef CAM_WHITE_LEVEL
    #undef CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #define cam_CFAPattern              0x02010100 // Red  Green  Green  Blue
    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000 
    #define cam_CalibrationIlluminant1  1 // Daylight

    // cropping (from ixus870_sd880)
    #define CAM_ACTIVE_AREA_X1          14
    #define CAM_ACTIVE_AREA_Y1          8
    #define CAM_ACTIVE_AREA_X2          3682
    #define CAM_ACTIVE_AREA_Y2          2764

    #undef  CAM_HAS_MANUAL_FOCUS
// for the purposes of CHDK, the FACE button is treated as the erase button
//    #undef  CAM_HAS_ERASE_BUTTON
//----------------------------------------------------------

