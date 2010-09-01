#include "stubs_asm.h"

// RAM addresses

// --- allready changed but unshure if 100% correct
DEF(physw_status, 0x32E94)    // ROM:FF8347D4, in ShowPhySwStatus() search "GpioStatus"

DEF(physw_run, 0x1C34)    // ROM:FF834400, in task_PhySw() 0x1C28 + 0xC = 0x1C34

// ROM:FF860864                 LDR     R0, =0x24A4 <---
// ROM:FF860868                 STMFD   SP!, {R4,LR}
// ROM:FF86086C                 LDR     R0, [R0,#8] <---
// ROM:FF860870                 BL      sub_FF839B50
// ROM:FF860874                 TST     R0, #1
// ROM:FF860878                 LDMNEFD SP!, {R4,LR}
// ROM:FF86087C                 MOVNE   R1, #0x42
// ROM:FF860880                 ADRNE   R0, aLeddrv_c   ; "LEDDrv.c"
// ROM:FF860884                 BNE     DebugAssert
// ROM:FF860888                 LDMFD   SP!, {R4,PC}
DEF(led_table, 0x24AC) // R0 -> 0x24A4 + 0x8

DEF(playrec_mode,0x2D78) // ROM:FF838AE4 (ROM:FF882328) search for String "MenuIn" 0x2D74 + 4 ?!?

// like SX210
// ROM:FFA13398                 STMFD   SP!, {R4,LR}
// ROM:FFA1339C                 LDR     R4, =0x92AC  <---
// ROM:FFA133A0                 LDR     R0, [R4,#0x20] <---
// ROM:FFA133A4                 CMN     R0, #1
// ROM:FFA133A8                 LDREQ   R1, =0x5BC
// ROM:FFA133AC                 ADREQ   R0, aWindow_c   ; "Window.c"
DEF(enabled_refresh_physical_screen, 0x92CC)    // ROM:FFA1339C 0x92AC + 0x20 = 0x92CC

// --- ToDo
DEF(FlashParamsTable,0xFFE7D1B4)
DEF(zoom_busy, 0x9DC0)  //0x9DAC + 0x14
DEF(focus_busy, 0x9D50) //  0x9CB8
DEF(canon_menu_active,0xB55C)
DEF(canon_shoot_menu_active,0xAE15)   // 0xAE14+1
DEF(recreview_hold, 0xABE8) // 0xAB38+0xB0
DEF(movie_status, 0x5570)  // 0x5538 + 0x38
DEF(some_flag_for_af_scan, 0xD688)
DEF(zoom_status, 0xD7C4)
DEF(some_f_for_dng, 0x8934)
DEF(second_ext_for_dng, 0x8954)
DEF(levent_table,0xFFE60474)
