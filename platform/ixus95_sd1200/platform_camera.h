// Camera - IXUS95_SD1200 - platform_camera.h

// This file contains the various settings values specific to the IXUS95_SD1200 camera.
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

	#define CAM_PROPSET                  2 
	#define CAM_DRYOS                    1

	#define CAM_RAW_ROWPIX               3720
	#define CAM_RAW_ROWS                 2772

	#undef   CAM_HAS_ERASE_BUTTON
	#define  CAM_USE_ZOOM_FOR_MF         1
	#define  CAM_MULTIPART               1
	#undef   CAM_HAS_IRIS_DIAPHRAGM
	#define  CAM_HAS_ND_FILTER           1

	#undef CAM_SYNCH

	#define CAM_HAS_ZOOM_LEVER          1

	#undef  CAM_HAS_MANUAL_FOCUS
	#define  CAM_HAS_USER_TV_MODES		 1 
	#define  CAM_SHOW_OSD_IN_SHOOT_MENU	 1
	#define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1
	//#define CAM_AF_SCAN_DURING_VIDEO_RECORD       1
	#undef CAM_AF_SCAN_DURING_VIDEO_RECORD		//TODO: change to define and find NSTUB    
	#define  CAM_CHDK_HAS_EXT_VIDEO_MENU	 1

	#define CAM_HAS_IS						 1
	#undef CAM_HAS_JOGDIAL

	#undef   CAM_VIDEO_CONTROL
	#define  CAM_VIDEO_QUALITY_ONLY		 	1

	//#define CAM_EXT_TV_RANGE            1

	#undef   CAM_UNCACHED_BIT            // shut up compiler
	#define  CAM_UNCACHED_BIT            0x40000000

	#undef   CAM_BITMAP_PALETTE
	#define  CAM_BITMAP_PALETTE          2

	#define CAM_QUALITY_OVERRIDE 1	
	#undef   CAM_SENSOR_BITS_PER_PIXEL
	#define  CAM_SENSOR_BITS_PER_PIXEL   12
	#undef   CAM_WHITE_LEVEL
	#define  CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	#undef   CAM_BLACK_LEVEL
	#define  CAM_BLACK_LEVEL             127

	// pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue

	// color preliminary
	// from para in forum
	#define  CAM_COLORMATRIX1                             \
    1484685, 1000000, -530958, 1000000, -208054, 1000000, \
    143142, 1000000, 793552, 1000000, 83907, 1000000, \
    146290, 1000000, -44679, 1000000, 430414, 1000000

	#define  cam_CalibrationIlluminant1 1 // Daylight

	// cropping 
	#define  CAM_JPEG_WIDTH  3648
	#define  CAM_JPEG_HEIGHT 2736
	#define  CAM_ACTIVE_AREA_X1 8
	#define  CAM_ACTIVE_AREA_Y1 12
	#define  CAM_ACTIVE_AREA_X2 3692
	#define  CAM_ACTIVE_AREA_Y2 2772

	// camera name
	#define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

	// aspect correction
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

	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240
	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (trhough new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #define CAM_ZEBRA_ASPECT_ADJUST 1
	// camera has very little free memory
    #define CAM_ZEBRA_NOBUF 1
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support

//----------------------------------------------------------


//==========================================================
// S-Series
//==========================================================
