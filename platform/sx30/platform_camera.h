// Camera - SX30 - platform_camera.h

// This file contains the various settings values specific to the SX30 camera.
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

	#define CAM_PROPSET					4
	#define CAM_DRYOS					1
	#define CAM_DRYOS_2_3_R39			1

	#define CAM_RAW_ROWPIX				4464
	#define CAM_RAW_ROWS				3276

	#define CAM_SWIVEL_SCREEN			1
	#define CAM_ADJUSTABLE_ALT_BUTTON	1
	#undef  CAM_CAN_SD_OVER_NOT_IN_MF
	#undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
	#define CAM_HAS_VIDEO_BUTTON		1
	#define CAM_VIDEO_QUALITY_ONLY		1
	#define CAM_BRACKETING				1
	#undef  CAM_VIDEO_CONTROL
	#define CAM_MULTIPART				1
	#define CAM_HAS_JOGDIAL				1
	#undef  CAM_USE_ZOOM_FOR_MF
	#undef  CAM_UNCACHED_BIT			// shut up compiler
	#define CAM_UNCACHED_BIT			0x40000000

	#undef DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT             2   // use .CR2 

    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH	10

	// bayer sensor pattern
	#define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green

	#define	CAM_DNG_EXPOSURE_BIAS		0,0		// Specify DNG exposure bias value to 0 (to override default of -0.5 in the dng.c code)

	// TODO - Still needs work 
	#define cam_CalibrationIlluminant1	1 // Daylight
	#define CAM_COLORMATRIX1                               \
	  1301431, 1000000,  -469837, 1000000, -102652, 1000000, \
	  -200195, 1000000,   961551, 1000000,  238645, 1000000, \
	   -16441, 1000000,   142319, 1000000,  375979, 1000000

	// cropping
	#define CAM_JPEG_WIDTH				4368 //4320
	#define CAM_JPEG_HEIGHT				3254 //3240
	#define CAM_ACTIVE_AREA_X1			24
	#define CAM_ACTIVE_AREA_Y1			10
	#define CAM_ACTIVE_AREA_X2			(4464-72)
	#define CAM_ACTIVE_AREA_Y2			(3276-12)
	// camera name
	#define PARAM_CAMERA_NAME			4 // parameter number for GetParameterData
	#undef  CAM_SENSOR_BITS_PER_PIXEL
	#undef  CAM_WHITE_LEVEL
	#undef  CAM_BLACK_LEVEL
	#define CAM_SENSOR_BITS_PER_PIXEL	12
	#define CAM_WHITE_LEVEL				((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	#define CAM_BLACK_LEVEL				127

	#define CAM_EXT_TV_RANGE			1
	#define CAM_QUALITY_OVERRIDE		1

	// copied from the SX200 which has the same video buffer size
	#undef CAM_USES_ASPECT_CORRECTION
	#undef CAM_USES_ASPECT_YCORRECTION
	#define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
	#define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

    #define CAM_ZEBRA_ASPECT_ADJUST 1
    #define CAM_ZEBRA_NOBUF 1

	#undef CAM_BITMAP_PALETTE
	#define CAM_BITMAP_PALETTE		7

	//zebra letterbox for saving memory
	#undef ZEBRA_HMARGIN0
	#define ZEBRA_HMARGIN0  30 //this 30 rows are not used by the display buffer is 720x240 effective, no 960x270, i.e. (270-240) reduction in widht possible but not done (more difficult to manage it and slower).
  
	#undef EDGE_HMARGIN
	#define EDGE_HMARGIN 2
	
	#define	CAM_DATE_FOLDER_NAMING	1

	#define	CAM_STARTUP_CRASH_FILE_OPEN_FIX	1				// enable fix for camera crash at startup when opening the conf / font files
															// see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_KEY_CLICK_DELAY 150 // SX30 appears to need extra delay for clicks
//----------------------------------------------------------
