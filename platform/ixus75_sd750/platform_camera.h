// Camera - IXUS75_SD750 - platform_camera.h

// This file contains the various settings values specific to the IXUS75_SD750 camera.
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

/*
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    */
    
    #undef  CAM_SWIVEL_SCREEN               // Camera has rotated LCD screen
    #undef CAM_USE_ZOOM_FOR_MF            // Zoom lever can be used for manual focus adjustments
    #undef  CAM_ADJUSTABLE_ALT_BUTTON       // ALT-button can be set from menu
    #undef CAM_REMOTE                     // Camera supports USB-remote
    #define CAM_MULTIPART               1   // Camera supports SD-card multipartitioning 
    #define CAM_HAS_ZOOM_LEVER          1   // Camera has dedicated zoom buttons
    #undef  CAM_DRAW_EXPOSITION             // Output expo-pair on screen (for cameras which (sometimes) don't do that)
    #undef CAM_HAS_ERASE_BUTTON           // Camera has dedicated erase button
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define  CAM_HAS_ND_FILTER         1      // Camera has build-in ND filter
    #undef CAM_CAN_SD_OVER_NOT_IN_MF      // Camera allows subject distance (focus) override when not in manual focus mode
    #undef CAM_CAN_SD_OVERRIDE            // Camera allows to do subject distance override
    #undef CAM_HAS_MANUAL_FOCUS           // Camera has manual focus mode
    #define CAM_HAS_USER_TV_MODES       1   // Camera has tv-priority or manual modes with ability to set tv value
    #define  CAM_SHOW_OSD_IN_SHOOT_MENU   1   // On some cameras Canon shoot menu has additional functionality and useful in this case to see CHDK OSD in this mode  
//    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO // adress for zoom_status missing, probably more
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1 // Camera can unlock optical zoom in video (if it is locked)
    #define  CAM_FEATURE_FEATHER        1     // Cameras with "feather" or touch wheel.
    #undef CAM_HAS_IS                     // Camera has image stabilizer

//    #define  CAM_CONSOLE_LOG_ENABLED   1      // Development: internal camera stdout -> A/stdout.txt        
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      689833,  1000000, -198299, 1000000, -101299, 1000000, \
      -164267, 1000000, 667466,  1000000,  74132,  1000000, \
       -36515,  1000000, 123872,   1000000,  248498, 1000000
    
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
//----------------------------------------------------------

