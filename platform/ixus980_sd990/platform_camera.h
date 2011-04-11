// Camera - IXUS980_SD990 - platform_camera.h

// This file contains the various settings values specific to the IXUS980_SD990 camera.
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

    #define CAM_PROPSET                 2 // all values checked so far match propset 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4480 // 14.7 MP 12bpp
    #define CAM_RAW_ROWS                3348   

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #define  CAM_HAS_MANUAL_FOCUS		1
    #define  CAM_HAS_USER_TV_MODES		1 //include M/P ? needed to make Tv bracketing work
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU 1
    #undef  CAM_VIDEO_CONTROL
    #undef CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT    0x40000000
    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    2

	#undef CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127
    #define CAM_HAS_JOGDIAL             1
//    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_VIDEO_QUALITY_ONLY          1  
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
	#undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
	#undef CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)

    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color preliminary
    #define CAM_COLORMATRIX1                               \
      837237, 1000000, -290137, 1000000, -128156, 1000000, \
      -127762, 1000000, 643909, 1000000,  52973,  1000000, \
      4446,  1000000, 88354,   1000000,  224246, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping 
    #define CAM_JPEG_WIDTH  4416
    #define CAM_JPEG_HEIGHT 3312
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 4444
    #define CAM_ACTIVE_AREA_Y2 3324
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData sd990: OK

    // copied from DavidBs D10 stuff
    #undef CAM_USES_ASPECT_CORRECTION
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

    #undef ASPECT_XCORRECTION
    #define ASPECT_XCORRECTION(x)   ( ((x)<<1) )

    // Note color palette affects grids!
    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)   ( (x) )

    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )

    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x)
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )

    // Note color palette affects games!
	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240
	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (through new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

   #define CAM_ZEBRA_ASPECT_ADJUST 1

//    #define DNG_EXT_FROM ".CR2"
//----------------------------------------------------------

