// Camera - S95 - platform_camera.h

// This file contains the various settings values specific to the S95 camera.
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

    #define CAM_DRYOS_2_3_R39			1
    #define CAM_PROPSET                 4
    #define CAM_DRYOS                   1
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_RAW_ROWPIX              3744
    #define CAM_RAW_ROWS                2784
    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10
    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH	10
	#define CAM_QUALITY_OVERRIDE 1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL             1
	#undef CAM_HAS_ERASE_BUTTON
    #undef  CAM_CONSOLE_LOG_ENABLED         // Development: internal camera stdout -> A/stdout.txt
    #define CAM_BRACKETING              1
	#undef  CAM_VIDEO_CONTROL
	#define CAM_VIDEO_QUALITY_ONLY		1
    #define CAM_MULTIPART               1
    #define CAM_EXT_TV_RANGE            1
    #undef OPT_CURVES
    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000  // S94 100E @FF89100C
	#define CAM_SHOW_OSD_IN_SHOOT_MENU  1

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #undef  CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #undef  CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127

    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_YCORRECTION  0  //only uses mappings on x coordinate

    //games mappings
	#undef GAMES_SCREEN_WIDTH
	#define GAMES_SCREEN_WIDTH 360
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_HEIGHT 240

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    7

    #undef ASPECT_XCORRECTION
	#define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )
	#undef ASPECT_GAMES_XCORRECTION
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )       //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

    #undef ASPECT_VIEWPORT_XCORRECTION
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
    #undef ASPECT_VIEWPORT_YCORRECTION
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )
    #undef EDGE_HMARGIN
    #define EDGE_HMARGIN 28

    #define DNG_SUPPORT    1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    //need fixing *****************************************************
    #define CAM_COLORMATRIX1                               \
      14134, 1000000, -5576, 1000000, -1527, 1000000, \
     -1991,  1000000, 10719,  1000000, 1273,   1000000, \
      -1158,   1000000, 1929,   1000000, 3581,  1000000
    #define cam_CalibrationIlluminant1 17 // Standard Light A

    // cropping
    #define CAM_JPEG_WIDTH  3600
    #define CAM_JPEG_HEIGHT 2700
    #define CAM_ACTIVE_AREA_X1 52
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3648
    #define CAM_ACTIVE_AREA_Y2 2736

   #define CAM_ZEBRA_ASPECT_ADJUST 1

   // todo - we may need this to save memory
    //#define CAM_ZEBRA_NOBUF 1

//----------------------------------------------------------
