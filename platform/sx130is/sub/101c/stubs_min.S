/*
*********************
SX130IS 101.c firmware
**********************
sikahr
12-2010
stubs_min.S
*/

// all addresses found by similarity to S95

#include "stubs_asm.h"



// DEF(zoom_busy, 0x7070+0x14)					// S95 @FF9809C8              
   DEF(zoom_busy, 0x6A78+0x1C)					// @FF963B60
/*
ROM:FF963B60 ; =============== S U B R O U T I N E =======================================
ROM:FF963B60
ROM:FF963B60 ; LOCATION: ZoomLensController.c:0
ROM:FF963B60
ROM:FF963B60                 EXPORT _sub_FF963B60__ZoomLensController.c__0
ROM:FF963B60 _sub_FF963B60__ZoomLensController.c__0  ; DATA XREF: _sub_FF963BF0__ZoomLensController.c__135+B0o
ROM:FF963B60                                         ; _sub_FF963CAC__ZoomLensController.c__156+B0o ...
ROM:FF963B60                 STMFD   SP!, {R4-R6,LR}
ROM:FF963B64                 LDR     R4, =0x6A78   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF963B68                 LDR     R0, [R4,#0x20]
ROM:FF963B6C                 CMP     R0, #0
ROM:FF963B70                 LDREQ   R1, =0x36F
ROM:FF963B74                 ADREQ   R0, aZoomlenscontro ; "ZoomLensController.c"
ROM:FF963B78                 BLEQ    DebugAssert
ROM:FF963B7C                 LDR     R1, =0x7530
ROM:FF963B80                 LDR     R0, [R4,#0x40]
ROM:FF963B84                 MOV     R3, #0x370
ROM:FF963B88                 ADR     R2, aZoomlenscontro ; "ZoomLensController.c"
ROM:FF963B8C                 BL      sub_FF83A488
ROM:FF963B90                 MOV     R0, #1
ROM:FF963B94                 MOV     R5, #0
ROM:FF963B98                 STR     R0, [R4,#0x14]
ROM:FF963B9C                 STR     R5, [R4,#0x1C]  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF963BA0                 BL      loc_FFA9FE98
ROM:FF963BA4                 STR     R0, [R4,#8]
ROM:FF963BA8                 LDR     R0, [R4,#0x40]
ROM:FF963BAC                 BL      eventproc_export_GiveSemaphore ; LOCATION: KerSem.c:0
ROM:FF963BB0                 LDR     R1, [R4,#0x20]
ROM:FF963BB4                 LDR     R0, [R4,#0x24]
ROM:FF963BB8                 BLX     R1
ROM:FF963BBC                 STR     R5, [R4,#0x18]
ROM:FF963BC0                 LDR     R0, [R4,#0x44]
ROM:FF963BC4                 LDMFD   SP!, {R4-R6,LR}
ROM:FF963BC8                 B       eventproc_export_GiveSemaphore ; LOCATION: KerSem.c:0
ROM:FF963BC8 ; End of function _sub_FF963B60__ZoomLensController.c__0
*/



//DEF(focus_busy, 0x6f28 + 8)					// S95 @FF97BEC8  
  DEF(focus_busy, 0x6970 + 8)					// @FF95FD30 

/*
ROM:FF95FD2C _sub_FF95FD2C__FocusLensController.c__203 ; CODE XREF: sub_FF86B4C4+14p
ROM:FF95FD2C                                         ; _sub_FF8759DC__LensController.c__1168+368p ...
ROM:FF95FD2C                 STMFD   SP!, {R4-R6,LR}
ROM:FF95FD30                 LDR     R4, =0x6970 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF95FD34                 MOV     R5, R0
ROM:FF95FD38                 LDR     R0, [R4,#0xC]
ROM:FF95FD3C                 CMP     R0, #1
ROM:FF95FD40                 LDREQ   R0, [R4,#4]
ROM:FF95FD44                 ADDEQ   R0, R0, #2
ROM:FF95FD48                 STREQ   R0, [R4,#4]
ROM:FF95FD4C                 LDMEQFD SP!, {R4-R6,PC}
ROM:FF95FD50                 LDR     R0, [R4]
ROM:FF95FD54                 CMP     R0, #0
ROM:FF95FD58                 MOVEQ   R1, #0xCB
ROM:FF95FD5C                 ADREQ   R0, aFocuslenscontr ; "FocusLensController.c"
ROM:FF95FD60                 BLEQ    DebugAssert
ROM:FF95FD64                 LDR     R1, =0x7530
ROM:FF95FD68                 LDR     R0, [R4,#0x24]
ROM:FF95FD6C                 MOV     R3, #0xCC
ROM:FF95FD70                 ADR     R2, aFocuslenscontr ; "FocusLensController.c"
ROM:FF95FD74                 BL      sub_FF83A488
ROM:FF95FD78                 MOV     R0, R5
ROM:FF95FD7C                 BL      sub_FF95FD14
ROM:FF95FD80                 CMP     R0, #1
ROM:FF95FD84                 LDRNE   R0, [R4,#0x24]
ROM:FF95FD88                 BNE     loc_FF95FDB8
ROM:FF95FD8C                 LDR     R0, [R4,#8] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF95FD90                 CMP     R0, #0
ROM:FF95FD94                 MOVNE   R1, #0xCE
ROM:FF95FD98                 ADRNE   R0, aFocuslenscontr ; "FocusLensController.c"
ROM:FF95FD9C                 BLNE    DebugAssert
ROM:FF95FDA0                 LDR     R0, [R4,#4]
ROM:FF95FDA4                 ADD     R0, R0, #2
ROM:FF95FDA8                 STR     R0, [R4,#4]
ROM:FF95FDAC                 LDR     R0, [R4,#0x24]
ROM:FF95FDB0                 BL      eventproc_export_GiveSemaphore ; LOCATION: KerSem.c:0
ROM:FF95FDB4                 LDR     R0, [R4,#0x20]
ROM:FF95FDB8
ROM:FF95FDB8 loc_FF95FDB8                            ; CODE XREF: _sub_FF95FD2C__FocusLensController.c__203+5Cj
ROM:FF95FDB8                 LDMFD   SP!, {R4-R6,LR}
ROM:FF95FDBC                 B       eventproc_export_GiveSemaphore ; LOCATION: KerSem.c:0
ROM:FF95FDBC ; End of function _sub_FF95FD2C__FocusLensController.c__203
*/  



//DEF(zoom_status, 0x835C) 					// S95 @FF9C21F0
  DEF(zoom_status, 0xCE70) 	        // @FFAC3A9C
/*
ROM:FFAC3A94 sub_FFAC3A94                            ; CODE XREF: sub_FFAC4454+3Cp
ROM:FFAC3A94                                         ; sub_FFAC4454+360p ...
ROM:FFAC3A94                 STMFD   SP!, {R3-R11,LR}
ROM:FFAC3A98                 SUB     R12, R0, #0x800
ROM:FFAC3A9C                 LDR     R7, =0xCE70 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FFAC3AA0                 SUBS    R12, R12, #0x58
ROM:FFAC3AA4                 MOV     R11, R1
ROM:FFAC3AA8                 MOV     R5, R0
ROM:FFAC3AAC                 MOV     R4, R2
ROM:FFAC3AB0                 BNE     loc_FFAC3AD0
ROM:FFAC3AB4                 BL      GetVRAMHPixelsSize_10
ROM:FFAC3AB8                 CMP     R0, #0
ROM:FFAC3ABC                 BEQ     locret_FFAC3B8C
ROM:FFAC3AC0                 LDRB    R0, [R7,#3]
ROM:FFAC3AC4                 CMP     R0, #0
ROM:FFAC3AC8                 BNE     locret_FFAC3B8C
ROM:FFAC3ACC                 B       loc_FFAC3C30

*/



//DEF(canon_menu_active, 0x324c + 4)			// S95 @FF896FC0  
DEF(canon_menu_active, 0x3034 + 4)			//  @FF88E340
  
/*
ROM:FF88E33C sub_FF88E33C                            ; CODE XREF: sub_FF89C1E4+6D4p
ROM:FF88E33C                                         ; sub_FF89E5A4+2FCp
ROM:FF88E33C                 STMFD   SP!, {R4,LR}
ROM:FF88E340                 LDR     R4, =0x3034 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF88E344                 LDR     R0, [R4,#4]
ROM:FF88E348                 MOV     R1, R4
ROM:FF88E34C                 CMP     R0, R1
ROM:FF88E350                 LDMNEFD SP!, {R4,PC}
ROM:FF88E354                 LDR     R0, [R4,#0x28]
ROM:FF88E358                 CMP     R0, #0
ROM:FF88E35C                 BNE     loc_FF88E36C
ROM:FF88E360                 BL      sub_FF88E954
ROM:FF88E364                 MOV     R0, #1
ROM:FF88E368                 STR     R0, [R4,#0x28]
ROM:FF88E36C
ROM:FF88E36C loc_FF88E36C                            ; CODE XREF: sub_FF88E33C+20j
ROM:FF88E36C                 BL      sub_FF8A8A1C
ROM:FF88E370                 BL      nullsub_79
ROM:FF88E374                 BL      sub_FF978A78
ROM:FF88E378                 BL      _sub_FF97D974__MenuContainer.c__0 ; LOCATION: MenuContainer.c:0
ROM:FF88E37C                 STR     R0, [R4,#4]
ROM:FF88E380                 LDR     R0, =0x854
ROM:FF88E384                 BL      sub_FF892EAC
ROM:FF88E388                 LDR     R0, =0x858
ROM:FF88E38C                 BL      sub_FF892EAC
ROM:FF88E390                 BL      sub_FF979204
ROM:FF88E394                 BL      sub_FF978D30
ROM:FF88E398                 BL      sub_FF9B4034
ROM:FF88E39C                 LDR     R0, [R4,#4]
ROM:FF88E3A0                 BL      _sub_FF97DBD4__MenuContainer.c__1696 ; LOCATION: MenuContainer.c:1696
ROM:FF88E3A4                 MOV     R0, #0
ROM:FF88E3A8                 BL      sub_FF9A9848
ROM:FF88E3AC                 BL      sub_FF88E1B8
ROM:FF88E3B0                 BL      _sub_FF8A8A80__Window.c__0 ; LOCATION: Window.c:0
ROM:FF88E3B4                 LDR     R0, [R4,#4]
ROM:FF88E3B8                 LDMFD   SP!, {R4,LR}
ROM:FF88E3BC                 B       sub_FF97E40C
ROM:FF88E3BC ; End of function sub_FF88E33C


*/



//DEF(movie_status, 0x7128 + 0x44)			// S95 @FF985B9C
  DEF(movie_status, 0x6B68 + 0x44)      // @FF96932C
/*
ROM:FF969320 ; =============== S U B R O U T I N E =======================================
ROM:FF969320
ROM:FF969320 ; LOCATION: MovieRecorder.c:0
ROM:FF969320
ROM:FF969320                 EXPORT _sub_FF969320__MovieRecorder.c__0
ROM:FF969320 _sub_FF969320__MovieRecorder.c__0       ; CODE XREF: sub_FF969BC8:loc_FF969CB4p
ROM:FF969320
ROM:FF969320 var_88          = -0x88
ROM:FF969320 var_7C          = -0x7C
ROM:FF969320 var_78          = -0x78
ROM:FF969320 var_74          = -0x74
ROM:FF969320 var_70          = -0x70
ROM:FF969320 var_6C          = -0x6C
ROM:FF969320 var_68          = -0x68
ROM:FF969320 var_64          = -0x64
ROM:FF969320 var_60          = -0x60
ROM:FF969320 var_54          = -0x54
ROM:FF969320 var_3C          = -0x3C
ROM:FF969320 var_38          = -0x38
ROM:FF969320 var_34          = -0x34
ROM:FF969320 var_30          = -0x30
ROM:FF969320 var_2C          = -0x2C
ROM:FF969320 var_28          = -0x28
ROM:FF969320
ROM:FF969320                 STMFD   SP!, {R4-R11,LR}
ROM:FF969324                 SUB     SP, SP, #0x64
ROM:FF969328                 MOV     R8, #0
ROM:FF96932C                 LDR     R6, =0x6B68   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF969330                 MOV     R4, R0
ROM:FF969334                 STR     R8, [SP,#0x88+var_34]
ROM:FF969338                 STR     R8, [SP,#0x88+var_3C]
ROM:FF96933C                 LDR     R0, [R6,#0x44]   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF969340                 MOV     R11, #4
ROM:FF969344                 CMP     R0, #3
ROM:FF969348                 STREQ   R11, [R6,#0x44]
ROM:FF96934C                 LDR     R0, [R6,#0xB4]
ROM:FF969350                 MOV     R9, #0
ROM:FF969354                 MOV     R7, #0
ROM:FF969358                 MOV     R5, #1
ROM:FF96935C                 BLX     R0
ROM:FF969360                 LDR     R0, [R6,#0x44]
ROM:FF969364                 CMP     R0, #6
*/



//DEF(enabled_refresh_physical_screen, 0xA0D4) // S95 @FF8B7F0C, @FFA4760C
DEF(enabled_refresh_physical_screen, 0x9458) // @FF8A8AD8, @FFA09440 
/*
ROM:FFA09440 sub_FFA09440                            ; CODE XREF: sub_FF8A788C+48p
ROM:FFA09440                                         ; _sub_FF8A8ABC__Window.c__0+1Cp
ROM:FFA09440                 LDR     R0, =0x9458 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FFA09444                 LDRB    R1, [R0]
ROM:FFA09448                 BIC     R1, R1, #1
ROM:FFA0944C                 STRB    R1, [R0]
ROM:FFA09450                 BX      LR
ROM:FFA09450 ; End of function sub_FFA09440

*/



//DEF(led_table, 0x25d4 + 0x04)				// S95 @FF864814   
  DEF(led_table, 0x2464 + 0x04)	      // @FF85EFEC
/*
ROM:FF85EFE8 ; =============== S U B R O U T I N E =======================================
ROM:FF85EFE8
ROM:FF85EFE8
ROM:FF85EFE8 sub_FF85EFE8                            ; CODE XREF: sub_FF83C19C+64p
ROM:FF85EFE8
ROM:FF85EFE8 var_18          = -0x18
ROM:FF85EFE8
ROM:FF85EFE8                 STMFD   SP!, {R3-R7,LR}
ROM:FF85EFEC                 LDR     R4, =0x2464 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF85EFF0                 LDR     R0, [R4]
ROM:FF85EFF4                 CMP     R0, #0
ROM:FF85EFF8                 BNE     locret_FF85F0F0
ROM:FF85EFFC                 MOV     R0, #0x340
ROM:FF85F000                 BL      _sub_FF83A5B0__Memory.c__66 ; LOCATION: Memory.c:66
ROM:FF85F004                 MOV     LR, R4
ROM:FF85F008                 STR     R0, [R4,#4]  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF85F00C                 MOV     R4, #1
ROM:FF85F010                 MOV     R1, #0
ROM:FF85F014                 MOV     R3, #0xD
ROM:FF85F018                 MOV     R12, #0xFF
ROM:FF85F01C                 MOV     R5, #0
*/



//DEF(FlashParamsTable,0xFFC72314)			// S95 @FFB0F19C             
  DEF(FlashParamsTable,0xFFBE82AC)      // @FFAC165C 
/*
ROM:FFAC165C ; =============== S U B R O U T I N E =======================================
ROM:FFAC165C
ROM:FFAC165C
ROM:FFAC165C sub_FFAC165C                            ; CODE XREF: sub_FFAC23AC+10p
ROM:FFAC165C                                         ; _sub_FFAC243C__ParameterManager.c__87+1Cp ...
ROM:FFAC165C                 LDR     R1, =off_FFBE82AC  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FFAC1660                 LDR     R0, [R1,R0,LSL#2]
ROM:FFAC1664                 BX      LR
ROM:FFAC1664 ; End of function sub_FFAC165C
*/



//DEF(levent_table,0xFFBF5C5C)				// S95 @FF9B8348         
  DEF(levent_table,0xFFB97A20)        // @FF990690
/*
ROM:FF990690 ; =============== S U B R O U T I N E =======================================
ROM:FF990690
ROM:FF990690
ROM:FF990690 sub_FF990690                            ; CODE XREF: sub_FF891328+4p
ROM:FF990690                                         ; sub_FF891D34+8p ...
ROM:FF990690                 LDR     R0, =off_FFB97A20   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF990694                 BX      LR
ROM:FF990694 ; End of function sub_FF990690
ROM:FF990694
ROM:FF990694 ; ---------------------------------------------------------------------------
ROM:FF990698 off_FF990698    DCD off_FFB97A20        ; DATA XREF: sub_FF990690r
*/



//DEF(playrec_mode, 0x2f74+0x4)				// S95 @FF889094        
  DEF(playrec_mode, 0x2D60+0x4)       // @FF8805CC   0x4   ????????????? 
/*
ROM:FF8805CC ; =============== S U B R O U T I N E =======================================
ROM:FF8805CC
ROM:FF8805CC ; "DryOS Canon Firmware; A720-based"
ROM:FF8805CC ; Attributes: library function
ROM:FF8805CC
ROM:FF8805CC unknown_libname_44                      ; CODE XREF: sub_FF83985C+4p
ROM:FF8805CC                                         ; _sub_FF87F930__SsZoomCtrl.c__6+4Cp ...
ROM:FF8805CC                 LDR     R0, =0x2D60    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF8805D0                 LDR     R0, [R0]
ROM:FF8805D4                 BX      LR
ROM:FF8805D4 ; End of function unknown_libname_44
*/



//DEF(physw_status, 0x34CB4)                // S95 @FF8340C8       
  DEF(physw_status, 0x32B34)                // @FF833D94
//DEF(physw_run, 0x1C30 + 0x0C)            	// S95 @FF8340A4       
  DEF(physw_run, 0x1C30 + 0x0C)             // @FF833D70
  /*
ROM:FF833D6C ; =============== S U B R O U T I N E =======================================
ROM:FF833D6C
ROM:FF833D6C
ROM:FF833D6C sub_FF833D6C                            ; CODE XREF: sub_FF83C19C+38p
ROM:FF833D6C                 STMFD   SP!, {R4,R5,LR}
ROM:FF833D70                 LDR     R4, =0x1C30   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF833D74                 SUB     SP, SP, #0x74
ROM:FF833D78                 LDR     R0, [R4,#0xC] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF833D7C                 CMP     R0, #1
ROM:FF833D80                 BEQ     loc_FF833E4C
ROM:FF833D84                 LDR     R0, =0x32B58
ROM:FF833D88                 BL      _sub_FF85F210__PhySwConfig.c__0 ; LOCATION: PhySwConfig.c:0
ROM:FF833D8C                 BL      sub_FF85FBF4
ROM:FF833D90                 BL      sub_FF834658
ROM:FF833D94                 LDR     R1, =0x32B34 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF833D98                 MOV     R0, #2
ROM:FF833D9C                 ADD     R2, R1, #0x24
ROM:FF833DA0                 SUB     R5, R2, #0x18
ROM:FF833DA4
*/



//DEF(some_flag_for_af_scan, 0x7534)		// S95 @FF9894B4        
  DEF(some_flag_for_af_scan, 0x6F68)    // @FF96CC44
/*
ROM:FF96CC44 ; ---------------------------------------------------------------------------
ROM:FF96CC44
ROM:FF96CC44 loc_FF96CC44                            ; CODE XREF: sub_FF96CBF8+14j
ROM:FF96CC44                                         ; sub_FF96CBF8+18j ...
ROM:FF96CC44 ; jumptable FF96CC0C default entry
ROM:FF96CC44 ; jumptable FF96CC0C entries 0,2,3,6,7
ROM:FF96CC44                 LDR     R0, =0x6F68  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF96CC48                 LDR     R0, [R0]
ROM:FF96CC4C                 CMP     R0, #0
ROM:FF96CC50                 MOVNE   R4, #0
ROM:FF96CC54                 BL      _sub_FF96CB84__SsPrepareSeqBase.c__372 ; LOCATION: SsPrepareSeqBase.c:372
ROM:FF96CC58                 CMP     R0, #0
ROM:FF96CC5C                 BEQ     loc_FF96CC64
*/



//DEF(canon_shoot_menu_active, 0x8758 + 1)	// S95 @FF9D7B70          
  DEF(canon_shoot_menu_active, 0x7D88 + 1)  // @FF9A9330
/*
ROM:FF9A9330 ; =============== S U B R O U T I N E =======================================
ROM:FF9A9330
ROM:FF9A9330
ROM:FF9A9330 sub_FF9A9330                            ; CODE XREF: sub_FF8950D4+12Cp
ROM:FF9A9330                                         ; sub_FF99CC30+20p
ROM:FF9A9330                 LDR     R1, =0x7D88    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF9A9334                 MOV     R0, #0
ROM:FF9A9338                 STRB    R0, [R1]
ROM:FF9A933C                 STRB    R0, [R1,#1]    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF9A9340                 B       sub_FF9A94D8
ROM:FF9A9340 ; End of function sub_FF9A9330
*/



//DEF(recreview_hold, 0x81f8+0xE8)			// S95 @FF9BDC78
DEF(recreview_hold, 0x78E4+0xEC)        // @FF995494 
/*
ROM:FF995490 ; =============== S U B R O U T I N E =======================================
ROM:FF995490
ROM:FF995490
ROM:FF995490 sub_FF995490                            ; CODE XREF: sub_FF9978D0+228p
ROM:FF995490                                         ; sub_FF998A18+20p
ROM:FF995490                 STMFD   SP!, {R4-R6,LR}
ROM:FF995494                 LDR     R5, =0x78E4  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF995498                 LDR     R12, =0x1051
ROM:FF99549C                 MOV     R2, R0
ROM:FF9954A0                 LDR     R0, [R5,#0xEC]  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF9954A4                 LDR     R1, [R5,#0x64]
ROM:FF9954A8                 CMP     R2, R12
ROM:FF9954AC                 MOV     R4, #0
ROM:FF9954B0                 MOV     R3, #1
ROM:FF9954B4                 BEQ     loc_FF995654
ROM:FF9954B8                 BGT     loc_FF9954EC
ROM:FF9954BC                 MOV     R12, unk_FFFFF65F
ROM:FF9954C0                 ADD     R2, R2, R12
ROM:FF9954C4                 CMP     R2, #6
ROM:FF9954C8                 ADDLS   PC, PC, R2,LSL#2
ROM:FF9954CC                 B       loc_FF99566C
*/

DEF(full_screen_refresh, 0x9458)					// found in FFA09304

