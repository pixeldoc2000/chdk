#include "stubs_asm.h"

#define NULLSUB 0xFF810B04						//	nullsub_1

NHSTUB(ExpCtrlTool_StartContiAE, 0xFF844034)	// SD940 103b matched with SD940 103c ExpCtrl
NHSTUB(MakeAFScan, 0xFF940510)					// SD940 103b matched with SD940 103c FF9406CC SsPrepareSeqBase

//** subs in signatures_dryos.h but not auto found 

NHSTUB(EnterToCompensationEVF , 0xFF8369D4)		// SD940 103b matched with SD940 103c ShootSeqAPI
NHSTUB(ExitFromCompensationEVF  , 0xFF836A18)	// SD940 103b matched with SD940 103c CameraLog.c

NHSTUB(TurnOffBackLight , 0xFF897658)			// SD940 103b matched with SD940 103c FF8976A8 "TurnOffBackLight"
NHSTUB(TurnOnBackLight, 0xFF897640)				// SD940 103b matched with SD940 103c FF897690 "TurnOnBackLight"

NHSTUB(Lseek , 0xFF8354D0)						// SD940 103b matched with SD940 103c Lseek

NHSTUB(PT_PlaySound , 0xFF879714)				// SD940 103b matched with SD940 103c FF879764 Audiohandle was FF879748 - changed by ww

NHSTUB(openfastdir , 0xFFA4CFD0)				// SD940 103b matched with SD940 103c FFA4D18C ReadFDir
NHSTUB(readfastdir , 0xFFA4D104)				// SD940 103b matched with SD940 103c FFA4D2C0 Cobj4PTP.c_

NHSTUB(RefreshPhysicalScreen , 0xFF9D1EB0)		// per SD940-1.03c SD90 101a & SD980 1.01c ScreenUnLock
NHSTUB(ScreenLock, 0xFF9D1C88)					// SD940 103b matched with SD940 103c FF9D1E44 ScreenLock
NHSTUB(ScreenUnlock,0xFF9D1CC8) 				// SD940 103b matched with SD940 103c FF9D1E44 next subroutine after ScreenLock

NHSTUB(Remove , 0xFF8353E8)						// SD940 103b matched with SD940 103c Near identical subroutine
NHSTUB(rename , 0xFF835490)						// SD940 103b matched with SD940 103c Sub immediately after eventproc_export_Write
NHSTUB(UIFS_WriteFirmInfoToFile , 0xFF956748)	// SD940 103b matched with SD940 103c Sub immediately after FirmInfoMenu.c

//** subs not in signatures_dryos.h

NHSTUB(platformsub_kbd_fetch_data, 0xFF858DF8)	//SD940 103b matched with SD940 103c GetKbdState

NHSTUB(SetScriptMode, 0xFF810F4C)				// SD940 103b matched with SD940 103c SetScriptMode
NHSTUB(LEDDrive, 0xFF8582F4)					// SD940 103b matched with SD940 103c eventproc_export_LEDDrive
NHSTUB(apex2us, 0xFF9D53A0)						// SD940 103b matched with SD940 103c FF9D555C v similar looking routine
NHSTUB(WriteSDCard, 0xFF92666C)					// SD940 103b matched with SD940 103c FF926538 v similar looking routine
NHSTUB(UnlockAF, 0xFF8368B4)					// SD940 103b matched with SD940 103c
NHSTUB(DoAFLock, 0xFF83687C)					// SD940 103b matched with SD940 103c
NHSTUB(UnsetZoomForMovie, 0xFF9712F0)			// SD940 103b matched with SD940 103c FF9714AC "ZoomCon_UnsetZoomForMovie"

NHSTUB(PutInNdFilter, 0xFFA67C14)				// SD940 103b matched with SD940 103c FFA67DD0 v similar looking routine
NHSTUB(PutOutNdFilter, 0xFFA67C38)				// SD940 103b matched with SD940 103c FFA67DF4 v similar looking routine

NHSTUB(set_control_event, 0xFF88A50C)			// SD940 103b matched with SD940 103c changed by ww to FF88A50C to match 103C
NHSTUB(closefastdir, 0xFFA4CF8C)				// SD940 103b matched with SD940 103c FFA4D148 v similar looking routine 
NHSTUB(ExitTask, 0xff81e844)					//	SD940 103b matched with SD940 103c
NHSTUB(free, 0xff814138)						//	SD940 103b matched with SD940 103c
NHSTUB(FreeUncacheableMemory, 0xff8388d8)		//	SD940 103b matched with SD940 103c
NHSTUB(GetBatteryTemperature, 0xff85bd0c)		//	SD940 103b matched with SD940 103c
NHSTUB(GetCCDTemperature, 0xff85bc98)			//	SD940 103b matched with SD940 103c
NHSTUB(GetCurrentAvValue, 0xFF936564)			// SD940 103b matched with SD940 103c ff936720
NHSTUB(GetFocusLensSubjectDistance, 0xFF935730)	//	SD940 103b matched with SD940 103c ff9358ec v similar looking routine 
NHSTUB(GetOpticalTemperature, 0xff85bd80)		//	SD940 103b matched with SD940 103c
NHSTUB(GetParameterData, 0xFF96B3D4)			//	SD940 103b matched with SD940 103c ff96b590 v similar looking routine
NHSTUB(GetPropertyCase, 0xFF884954)				//	SD940 103b matched with SD940 103c ff8849a4 v similar looking routine v close by
NHSTUB(GetSystemTime, 0xFFA69D3C)				//	SD940 103b matched with SD940 103c ffa69ef8 GetSystemTime
NHSTUB(GetZoomLensCurrentPoint, 0xFF93A7B4)		//	SD940 103b matched with SD940 103c ff93a970 v similar looking routine
NHSTUB(GetZoomLensCurrentPosition, 0xFFA5D94C)	//	SD940 103b matched with SD940 103c ffa5db08 v similar looking routine
NHSTUB(IsStrobeChargeCompleted, 0xFF8BC274)		//	SD940 103b matched with SD940 103c ff8bc2c4 v similar looking routine
NHSTUB(kbd_p1_f, 0xff8335d0)					//	SD940 103b matched with SD940 103c kbd_p1_f
NHSTUB(kbd_p1_f_cont, 0xff8335dc)				//	SD940 103b matched with SD940 103c kbd_p1_f
NHSTUB(kbd_read_keys, 0xff833554)				//	SD940 103b matched with SD940 103c
NHSTUB(kbd_read_keys_r2, 0xff8587b8) 			//	SD940 103b matched with SD940 103c
NHSTUB(LockMainPower, 0xFF88AA6C)				//	SD940 103b matched with SD940 103c ff88aabc eventproc_export_LockMainPower
NHSTUB(MakeDirectory_Fut, 0xff834db4)			//	SD940 103b matched with SD940 103c
NHSTUB(MoveFocusLensToDistance, 0xFFAD10F0)		//	SD940 103b matched with SD940 103c ffad12ac.  Tricky - determined offset for nearby line with text "A720-based" to identify drift as 1BC between firmwares
NHSTUB(MoveZoomLensWithPoint, 0xFFA67DB0)		//	SD940 103b matched with SD940 103c ffa67f6c
NHSTUB(NewTaskShell, 0xFF884418)				//	SD940 103b matched with SD940 103c ff884468 NewTaskShell
NHSTUB(PostLogicalEventForNotPowerType, 0xFF88A2A4) 	//	SD940 103b matched with SD940 103c ff88a2f4
NHSTUB(PostLogicalEventToUI, 0xFF88A2F0)		//	SD940 103b matched with SD940 103c ff88a340
NHSTUB(rand, 0xff8204e0)						//	SD940 103b matched with SD940 103c
NHSTUB(reboot_fw_update, 0xFFA52614)			//	SD940 103b matched with SD940 103c cffa527d0
NHSTUB(RenameFile_Fut, 0xFF834CAC)				//  SD940 103b matched with SD940 103c
NHSTUB(SetAutoShutdownTime, 0xFF88AAE0)			//	SD940 103b matched with SD940 103c ff88ab30 SetAutoShutdownTime
NHSTUB(SetCurrentCaptureModeType, 0xFF891B18)	//	SD940 103b matched with SD940 103c ff891b68 SetCurrentCaptureModeType
NHSTUB(SetFileTimeStamp, 0xFF835640)			//  SD940 103b matched with SD940 103c
NHSTUB(SetLogicalEventActive, 0xFF88A7E8)		//	SD940 103b matched with SD940 103c ff88a838 EXPORT eventproc_export_UiEvnt_SetLogicalEventActive
NHSTUB(SetParameterData, 0xFF96B344)			//	SD940 103b matched with SD940 103c ff96b500
NHSTUB(SetPropertyCase, 0xFF884858)				//	SD940 103b matched with SD940 103c ff8848a8
NHSTUB(SleepTask, 0xff83851c)					//	SD940 103b matched with SD940 103c
NHSTUB(srand, 0xff8204d4)						//  SD940 103b matched with SD940 103c
NHSTUB(stat, 0xff83550c) 						//	SD940 103b matched with SD940 103c 
NHSTUB(strcat, 0xFF89E260)						//  SD940 103b matched with SD940 103c FF89E2B0
NHSTUB(strchr, 0xff813fc0)						//	SD940 103b matched with SD940 103c
NHSTUB(strncpy, 0xff813f38)						//	SD940 103b matched with SD940 103c
NHSTUB(strrchr, 0xFF813FE4)						//  SD940 103b matched with SD940 103c
NHSTUB(strtol, 0xff83e128)						//	SD940 103b matched with SD940 103c
NHSTUB(TakeSemaphore, 0xff8381e4)				//	SD940 103b matched with SD940 103c TakeSemaphore
NHSTUB(time, 0xFF87EAF0)						//	SD940 103b matched with SD940 103c ff87eb40 SystemTime
NHSTUB(UnlockMainPower, 0xFF88A9C0)				//	SD940 103b matched with SD940 103c ff88aa10 UnlockMainPower
NHSTUB(GetImageFolder, 0xFF919028)                              // function before 'GetCameraObjectTmpPath ERROR' string

//** obsolete / unknown / not found subs

NHSTUB(kbd_pwr_on , NULLSUB)					//** not found in SD90 or SD940-102c
NHSTUB(kbd_pwr_off, NULLSUB)					//** 0xff858e10 = best match: 51% in finsig
NHSTUB(rewinddir, NULLSUB)						//** not found in SD90 or SD940-102c
NHSTUB(SetZoomActuatorSpeedPercent, NULLSUB)	//** not found in SD90 or SD940-102c
NHSTUB(Unmount_FileSystem, NULLSUB)				//** not found in SD90 or SD940-102c
NHSTUB(Mount_FileSystem, NULLSUB)				//** not found in SD90 or SD940-102c
