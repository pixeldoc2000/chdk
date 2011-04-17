#include "stubs_asm.h"

DEF(zoom_status, 0xB9DC)                			// SD940 103c, 103b, 102c  	
DEF(movie_status, 0x6228 + 0x38)        			// SD940 103c, 103b, 102c	
DEF(physw_status, 0x31B78)							// SD940 103c, 103b, 102c
DEF(physw_run, 0x1C38 + 0x0C)   					// SD940 103c, 103b, 102c	
DEF(FlashParamsTable, 0xFFB972DC)					//** @ FFA759FC
DEF(zoom_busy, 0x61B8 + 0x14)						// SD940 103c, 103b, 102c
DEF(focus_busy, 0x6070 + 8)							// SD940 103c, 103b, 102c
DEF(canon_menu_active, 0x2D44 + 4 )     			// SD940 103c, 103b, 102c
DEF(canon_shoot_menu_active, 0x7750+1)  			// SD940 103c, 103b, 102c
DEF(recreview_hold, 0x73D0 + 0xD0)      			// SD940 103c, 103b, 102c	
DEF(some_flag_for_af_scan, 0x673C) 					// SD940 103c, 103b, 102c
DEF(levent_table,0xFFB41F14) 						//** @ FF966D58
DEF(playrec_mode, 0x2A78+0x4)						// SD940 103c, 103b, 102c
DEF(enabled_refresh_physical_screen, 0x8C20+0x20)   // SD940 103c, 103b, 102c


// will need to fix these if we care about dng support
DEF(some_f_for_dng, 0xDEAD) 				// TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD) 			// TODO NOT FOUND!

