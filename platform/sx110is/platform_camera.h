// Camera - SX110IS - platform_camera.h

// This file contains the various settings values specific to the SX110IS camera.
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

	#define CAM_COLORMATRIX1                               \
      530200, 1000000, -42600,  1000000, -33000,  1000000, \
     -525400,  1000000, 1092700,  1000000,  223700,  1000000, \
     -103700,  1000000, 117900,   1000000,  421600,  1000000
    #define CAM_ACTIVE_AREA_X1 8
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3688
    #define CAM_ACTIVE_AREA_Y2 2772

    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1
    #define CAM_RAW_ROWPIX              3720  
    #define CAM_RAW_ROWS                2772  
    #undef CAM_SYNCH 
    #define CAM_CAN_MUTE_MICROPHONE     1 
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_REAR_CURTAIN            1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1 
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
    #undef  CAM_USE_ZOOM_FOR_MF
	#undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
	#undef CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	// black level set to 128 per reports on the forum
    #undef  CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             128
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
      #define cam_CalibrationIlluminant1 1 // Daylight
      #define CAM_JPEG_WIDTH  3456 
      #define CAM_JPEG_HEIGHT 2592
     
     
  //----------------------------------------------------------
  
