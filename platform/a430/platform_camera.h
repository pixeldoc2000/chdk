// Camera - A430 - platform_camera.h

// This file contains the various settings values specific to the A430 camera.
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

	#define CAM_PROPSET						1

	#define CAM_RAW_ROWPIX					2392  // for 4 MP 1/3" sensor size
	#define CAM_RAW_ROWS					1752  // for 4 MP 1/3" sensor size

	#undef  CAM_USE_ZOOM_FOR_MF
	#undef  CAM_HAS_ZOOM_LEVER
	#define CAM_DRAW_EXPOSITION				1
	#undef  CAM_HAS_ERASE_BUTTON
	#undef  CAM_HAS_IRIS_DIAPHRAGM
	#define CAM_HAS_ND_FILTER				1
	#undef  CAM_HAS_MANUAL_FOCUS
	#undef  CAM_HAS_USER_TV_MODES
	#define CAM_SHOW_OSD_IN_SHOOT_MENU		1
	#undef  CAM_HAS_IS
	#define CAM_CAN_MUTE_MICROPHONE			1
	#define CAM_AF_SCAN_DURING_VIDEO_RECORD	1
	#define CAM_EV_IN_VIDEO					1
	// pattern
	#define cam_CFAPattern 0x01000201  // Green Blue Red Green
	// color
	#define CAM_COLORMATRIX1                                \
      479627,  1000000, -156240, 1000000,  -84926, 1000000, \
     -215238,  1000000,  534902, 1000000,   60219, 1000000, \
      -96906,  1000000,  148194, 1000000,  191583, 1000000

	#define CAM_CONSOLE_LOG_ENABLED			1
	#define cam_CalibrationIlluminant1		1 // Daylight
	// cropping
	#define CAM_JPEG_WIDTH			2272
	#define CAM_JPEG_HEIGHT			1704
	#define CAM_ACTIVE_AREA_X1		0
	#define CAM_ACTIVE_AREA_Y1		8
	#define CAM_ACTIVE_AREA_X2		2336
	#define CAM_ACTIVE_AREA_Y2		1748
	// camera name
	#define PARAM_CAMERA_NAME		3 // parameter number for GetParameterData
	#define CAM_BRACKETING			1
//	#define CAM_MULTIPART			1
//----------------------------------------------------------

