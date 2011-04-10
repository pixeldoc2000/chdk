#include "stubs_asm.h"

DEF(physw_status, 0x0EBDC)
DEF(physw_run, 0x1be4 + 0x0c)
DEF(FlashParamsTable,0xFFE9EF08) // found at 0xFFDF11FC //m.b. OK
DEF(zoom_busy, 0x7F4C)  //0x7F38 + 0x14 //OK
DEF(playrec_mode,0x5320) // OK!
//UP
DEF(focus_busy, 0x9D50) //  0x9CB8
DEF(canon_menu_active,0x8BD8 + 4) //m.b. OK
DEF(canon_shoot_menu_active,0x94B9)   // 0x94B8+1
DEF(recreview_hold, 0xABE8) // 0xAB38+0xB0

DEF(movie_status, 0x5570)  // 0x5538 + 0x38
DEF(some_flag_for_af_scan, 0xD688)
DEF(zoom_status, 0xD7C4)
DEF(some_f_for_dng, 0x8934)
DEF(second_ext_for_dng, 0x8954)
DEF(levent_table,0xFFE60474)

