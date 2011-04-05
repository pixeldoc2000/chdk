/*
*********************
SX130IS 101.c firmware
**********************
sikahr
12-2010
lib.c
*/

#include "platform.h"

char *hook_raw_image_addr()   
{
/*
ROM:FFB102F0                 LDR     R6, =0x41F3B020  <<<<<<<<<<<<<<<
ROM:FFB102F4                 LDR     R4, =0x41876740
ROM:FFB102F8                 LDR     R5, =0x409A0520
ROM:FFB10328                 BL      sub_FF93AC08
ROM:FFB1032C                 MOV     R1, R4
ROM:FFB10330                 ADR     R0, aImgVramBuffP ; "IMG VRAM BUFF   %p"
ROM:FFB10334                 BL      sub_FF93AC08
ROM:FFB10338                 MOV     R1, R5
ROM:FFB1033C                 ADR     R0, aThumVramBuffP ; "THUM VRAM BUFF  %p"
ROM:FFB10340                 BL      sub_FF93AC08
ROM:FFB10344                 MOV     R1, R6
ROM:FFB10348                 ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"
ROM:FFB1034C                 BL      sub_FF93AC08
ROM:FFB10350                 LDR     R1, =0x11CA240  <<<<<<<<<<<<<<
ROM:FFB10354                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
*/
	return (char*)(0x41F3B020);
}

/*
ROM:FFB0FF90 ; ---------------------------------------------------------------------------
ROM:FFB0FF90
ROM:FFB0FF90 loc_FFB0FF90                            ; CODE XREF: sub_FFB0FF50+10j
ROM:FFB0FF90                 MOV     R0, #0xFF0    	// raw sensor size X - 4080
ROM:FFB0FF94                 STR     R0, [R1]
ROM:FFB0FF98                 LDR     R0, =0xBE8	    // raw sensor size Y - 3048
ROM:FFB0FF9C                 STR     R0, [R1,#4]
ROM:FFB0FFA0                 MOV     R0, #0xFA0	    // cropped size X - 4000
ROM:FFB0FFA4                 STR     R0, [R1,#8]
ROM:FFB0FFA8                 SUB     R0, R0, #0x3E8 // cropped size Y - (4000 - 1000) = 3000
ROM:FFB0FFAC
ROM:FFB0FFAC loc_FFB0FFAC                            ; CODE XREF: sub_FFB0FF50+3Cj
ROM:FFB0FFAC                 STR     R0, [R1,#0xC]
ROM:FFB0FFB0                 MOV     R0, #0
ROM:FFB0FFB4                 BX      LR
ROM:FFB0FFB4 ; End of function sub_FFB0FF50

*/

/*
Raw buffer size 0x11CA240 / 12 * 8 = 0xBDC180 pixels  ( RAW 12 bit per pixel)
4080  *  3048  = 12435840 pixels
0xFF0 *  0xBE8 = 0xBDC180 pixels
same senzor as SX200, SX20 ( probably?)

ROM:FF9397C8 loc_FF9397C8                            ; CODE XREF: sub_FF939780+3Cj
ROM:FF9397C8                 LDR     R1, =0x41F3B020
ROM:FF9397CC                 MOV     R2, #0xFF0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF9397D0                 LDR     R3, =0xBE8 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF9397D4                 STMFA   SP, {R1,R2}
ROM:FF9397D8                 ADR     R0, aCrwaddressLxCr ; " CrwAddress %lx, CrwSize H %ld V %ld\r"


*/
long hook_raw_size() 
{
		return 0x11CA240;
}



// Live picture buffer (shoot not pressed) 
void *vid_get_viewport_live_fb()
{


    return 0x0;

}




void *vid_get_bitmap_fb()
{
/*
ROM:FF9177B8 ; =============== S U B R O U T I N E =======================================
ROM:FF9177B8
ROM:FF9177B8 ; LOCATION: BmpDDev.c:0
ROM:FF9177B8
ROM:FF9177B8                 EXPORT _sub_FF9177B8__BmpDDev.c__0
ROM:FF9177B8 _sub_FF9177B8__BmpDDev.c__0             ; CODE XREF: sub_FFA0D168+48p
ROM:FF9177B8                 STMFD   SP!, {R4-R8,LR}
ROM:FF9177BC                 LDR     R8, =0x5BA0
ROM:FF9177C0                 MOV     R4, R0
ROM:FF9177C4                 LDR     R0, [R8,#0x10]
ROM:FF9177C8                 MOV     R5, R1
ROM:FF9177CC                 CMP     R0, #1
ROM:FF9177D0                 LDREQ   R1, =0x17F
ROM:FF9177D4                 ADREQ   R0, aBmpddev_c  ; "BmpDDev.c"
ROM:FF9177D8                 MOV     R7, R3
ROM:FF9177DC                 MOV     R6, R2
ROM:FF9177E0                 BLEQ    DebugAssert
ROM:FF9177E4                 CMP     R4, #0
ROM:FF9177E8                 CMPNE   R5, #0
ROM:FF9177EC                 CMPNE   R6, #0
ROM:FF9177F0                 CMPNE   R7, #0
ROM:FF9177F4                 LDREQ   R1, =0x182
ROM:FF9177F8                 ADREQ   R0, aBmpddev_c  ; "BmpDDev.c"
ROM:FF9177FC                 BLEQ    DebugAssert
ROM:FF917800                 MOV     R0, #0x2D0   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Height  0x2D0 dec 720
ROM:FF917804                 MOV     R1, #0xF0    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Width  0xF0   dec 240
ROM:FF917808                 STR     R0, [R4]
ROM:FF91780C                 STR     R1, [R5]
ROM:FF917810                 STR     R0, [R6]
ROM:FF917814                 LDR     R0, =0x403F1000 <<<<<<<<<<<<<<<<<
ROM:FF917818                 STR     R0, [R7]
ROM:FF91781C                 MOV     R0, #1
ROM:FF917820                 STR     R0, [R8,#0x10]
ROM:FF917824                 MOV     R0, #0
ROM:FF917828                 LDMFD   SP!, {R4-R8,PC}
ROM:FF917828 ; End of function _sub_FF9177B8__BmpDDev.c__0
ROM:FF917828
ROM:FF91782C
*/
	return (void*)0x403F1000;                              
}


// Live picture buffer (shoot half-pressed) 
void *vid_get_viewport_fb()
{
/*
ROM:FFB0CEB8 loc_FFB0CEB8                            ; CODE XREF: sub_FFB0CE7C+28j
ROM:FFB0CEB8                 MOV     R2, R7
ROM:FFB0CEBC                 MOV     R1, R6
ROM:FFB0CEC0                 MOV     R0, R5
ROM:FFB0CEC4                 BL      sub_FF85263C
ROM:FFB0CEC8                 LDR     R1, =0x40507700  <<<<<<<<<<<<<<<<<<<
ROM:FFB0CECC                 LDR     R0, =0x3F480
ROM:FFB0CED0                 STR     R1, [R4]
ROM:FFB0CED4                 STR     R0, [R4,#4]
ROM:FFB0CED8                 ADR     R0, aVramAddressP ; "VRAM Address  : %p\r"
ROM:FFB0CEDC                 BL      sub_FF93AC08
ROM:FFB0CEE0                 LDR     R1, [R4,#4]
ROM:FFB0CEE4                 ADR     R0, aVramSize0xX ; "VRAM Size     : 0x%x\r"
ROM:FFB0CEE8                 BL      sub_FF93AC08
ROM:FFB0CEEC                 MOV     R0, #0
ROM:FFB0CEF0                 LDMFD   SP!, {R4-R8,PC}
ROM:FFB0CEF0 ; End of function sub_FFB0CE7C
*/


	return (void*)0x40507700;                              
}

// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d()
{

/*
ROM:FF872090 ; =============== S U B R O U T I N E =======================================
ROM:FF872090
ROM:FF872090 ; LOCATION: ImagePlayer.c:0
ROM:FF872090
ROM:FF872090                 EXPORT _sub_FF872090__ImagePlayer.c__0
ROM:FF872090 _sub_FF872090__ImagePlayer.c__0         ; CODE XREF: _sub_FF882734__VisualHandle.c__154+1B4 p
ROM:FF872090                                         ; sub_FF882908+94 p ...
ROM:FF872090                 STMFD   SP!, {R1-R7,LR}
ROM:FF872094                 LDR     R7, =0x2710
ROM:FF872098                 LDR     R5, =0x2A70   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF87209C                 LDR     R3, =0x6CE
ROM:FF8720A0                 LDR     R2, =aImageplayer_c ; "ImagePlayer.c"
ROM:FF8720A4                 LDR     R0, [R5,#0x4C]
ROM:FF8720A8                 MOV     R1, R7
ROM:FF8720AC                 BL      sub_FF83A488
ROM:FF8720B0                 MOV     R0, #1
ROM:FF8720B4                 BL      sub_FF871280
ROM:FF8720B8                 CMN     R0, #1
ROM:FF8720BC                 BEQ     loc_FF87218C
ROM:FF8720C0                 LDR     R4, =0x37A4C
ROM:FF8720C4                 ADD     R1, R0, R0,LSL#2
ROM:FF8720C8                 LDR     R0, [R4,R1,LSL#2]
ROM:FF8720CC                 MOV     R3, #0
ROM:FF8720D0                 ADR     R2, sub_FF871988
ROM:FF8720D4                 ADD     R12, R4, R1,LSL#2
ROM:FF8720D8                 STR     R0, [R5,#0x58]   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF8720DC                 LDR     R1, [R12,#0xC]
ROM:FF8720E0                 STMEA   SP, {R1-R3}
ROM:FF8720E4                 LDR     R3, [R12,#8]
ROM:FF8720E8                 MOV     R2, #0
ROM:FF8720EC                 MOV     R1, #0
ROM:FF8720F0                 BL      _sub_FF918DA8__ImgDDev.c__6 ; LOCATION: ImgDDev.c:6
ROM:FF8720F4                 TST     R0, #1
ROM:FF8720F8                 LDRNE   R1, =0x6F4
ROM:FF8720FC                 LDRNE   R0, =aImageplayer_c ; "ImagePlayer.c"
*/

    return (void*)(*(int*) (0x2A70+0x58));       
} 

char *camera_jpeg_count_str()
/*
ROM:FF9FF420 loc_FF9FF420                            ; CODE XREF: sub_FF9FF35C+50 j
ROM:FF9FF420                 SUBS    R12, R0, #0x2700
ROM:FF9FF424                 SUBCSS  R12, R12, #0xF
ROM:FF9FF428                 BCC     loc_FF9FF43C
ROM:FF9FF42C                 LDR     R0, =0xB33A4  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF9FF430                 ADR     R1, a9999       ; "9999"
ROM:FF9FF434                 BL      eventproc_export_sprintf
ROM:FF9FF438                 B       loc_FF9FF44C
ROM:FF9FF43C ; ---------------------------------------------------------------------------
*/
{
 return (void*)0xB33A4;
}

long vid_get_bitmap_screen_width()
{
    return 320;    
}

long vid_get_bitmap_screen_height()
{
    return 240;
}

int vid_get_viewport_width()
{
    return 360;
}

long vid_get_viewport_height()
{
    return 240;
}


long vid_get_bitmap_buffer_width() { return 720; } 

long vid_get_bitmap_buffer_height() { return 240; } 



//Copied from S95 section  END

/*
//  NEW NEW NEW
//  Need checking

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}
*/ 

/*
Note copied from SX110 IS
GetBatteryTemperature usually will get back temperature of battery compartment/batteries. GetBatteryTemperature is implemented in Canon's firmware for SX120IS.
Firmware entry point is identified (0xFFC394D8) but function is not usable. Camera will crash if Canon's GetBatteryTemperature is called by CHDK.
To avoid a crash Canon's GetBatteryTemperature must not called. As long CHDK general code do not distinguish between cameras that support or don't support GetBatteryTemperature, 
this function will be implemented as specific CHDK-code. It returns always with -99 (which means -99° Celsius or -146° Fahrenheit).
Original entry point in Canon's firmware is disabled (in stubs_entry.S).
*/

int _GetBatteryTemperature()
{
      return -99;
}
 
 
