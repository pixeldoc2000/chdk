#include "stubs_asm.h"

# Confirmed
NHSTUB(qsort,							0xFFB5FBDC)	// ok (comp 1.00c)
NHSTUB(strtol,							0xFF840954)	// ok (comp 1.00c)
NHSTUB(EnterToCompensationEVF,			0xFF838D24)	// ok (comp 1.00c)
NHSTUB(ExitFromCompensationEVF,			0xFF838D68)	// ok (comp 1.00c)
NHSTUB(GetBatteryTemperature,			0xff868f80)	// ok (comp 1.00c)
NHSTUB(GetCCDTemperature,				0xff868f0c)	// ok (comp 1.00c)
NHSTUB(GetCurrentAvValue,				0xff97fcb8)	// ok (comp 1.00c)
NHSTUB(GetParameterData,				0xFF9BECF0)	// ok (comp 1.00c)
NHSTUB(GetZoomLensCurrentPoint,			0xFF9819E0)	// ok (comp 1.00c)
NHSTUB(GetZoomLensCurrentPosition,		0xFFAF6880)	// ok (comp 1.00c)
NHSTUB(PT_PlaySound,					0xFF88A140)	// ok (comp 1.00c)
NHSTUB(ReadFastDir,						0xFFAE2C20)	// ok (comp 1.00c)
NHSTUB(readfastdir,						0xFFAE2C20) // alias for ReadFastDir
NHSTUB(Remove,							0xFF837114)	// ok (comp 1.00c)
NHSTUB(SetParameterData,				0xFF9BEBC8)	// ok (comp 1.00c)
NHSTUB(TurnOffBackLight,				0xFF8ABD94)	// ok (comp 1.00c)
NHSTUB(TurnOnBackLight,					0xFF8ABD7C)	// ok (comp 1.00c)
NHSTUB(Lseek,							0xFF8371FC)	// ok (comp 1.00c)
NHSTUB(free,							0xFF814244)	// ok (comp 1.00c)
NHSTUB(ExitTask,						0xff81eb30)	// ok (comp 1.00c)
NHSTUB(FreeUncacheableMemory,			0xff83af70)	// ok (comp 1.00c)
NHSTUB(GetDrive_ClusterSize,			0xff876948)	// ok (comp 1.00c)
NHSTUB(GetDrive_TotalClusters,			0xff87697c)	// ok (comp 1.00c)
NHSTUB(GetDrive_FreeClusters,			0xFF8769A8)	// ok (comp 1.00c)
NHSTUB(GetFocusLensSubjectDistance,		0xff97e348)	// ok (comp 1.00c)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xff97e794)	// ok (comp 1.00c)
NHSTUB(GetOpticalTemperature,			0xff868ff4)	// ok (comp 1.00c)
NHSTUB(GetPropertyCase,					0xff8954f0)	// ok (comp 1.00c)
NHSTUB(GetSystemTime,					0xFFB08EE8)	// ok (comp 1.00c)
NHSTUB(IsStrobeChargeCompleted,			0xff8ea5f0)	// ok (comp 1.00c)
NHSTUB(LockMainPower,					0xff89c204)	// ok (comp 1.00c)
NHSTUB(MakeDirectory_Fut,				0xff836acc)	// ok (comp 1.00c)
NHSTUB(MoveFocusLensToDistance,			0xFFB72148)	// ok (comp 1.00c)
NHSTUB(MoveZoomLensWithPoint,			0xFFB051B8)	// ok (comp 1.00c)
NHSTUB(NewTaskShell,					0xff894f0c)	// ok (comp 1.00c)
NHSTUB(Close,							0xFF8370E0)	// ok (eventproc_export_Close)
NHSTUB(Open,							0xFF837074)	// wrapper for 'open' to give buffered/asynch I/O ?
NHSTUB(open,							0xFF81AADC)	// 
NHSTUB(PostLogicalEventForNotPowerType, 0xff899b70)	// ok (comp 1.00c)
NHSTUB(PostLogicalEventToUI,			0xff899bbc)	// ok (comp 1.00c)
NHSTUB(RenameFile_Fut,					0xFF8369C4)	// ok (comp 1.00c)
NHSTUB(rename,							0xFF8369C4) // same as RenameFile_Fut
NHSTUB(SetAutoShutdownTime,				0xff89c278)	// ok (comp 1.00c)
NHSTUB(SetCurrentCaptureModeType,		0xff8a4d44)	// ok (comp 1.00c)
NHSTUB(SetFileTimeStamp,				0xFF83737C)	// ok (comp 1.00c)
NHSTUB(SetLogicalEventActive,			0xff89bf40)	// ok (comp 1.00c)
NHSTUB(SetPropertyCase,					0xff8953c8)	// ok (comp 1.00c)
NHSTUB(SleepTask,						0xff83abb4)	// ok (comp 1.00c)
NHSTUB(TakeSemaphore,					0xff83a87c)	// ok (comp 1.00c)
NHSTUB(UnlockMainPower,					0xff89c158)	// ok (comp 1.00c)
NHSTUB(VbattGet,						0xff833180)	// ok (comp 1.00c)
NHSTUB(closedir,						0xFFAE2A7C)	// ok (comp 1.00c)
NHSTUB(closefastdir,					0xFFAE2A7C) // same as closedir
NHSTUB(kbd_p1_f,						0xff834a6c)	// ok (comp 1.00c)
NHSTUB(kbd_p1_f_cont,					0xff834a78)	// ok (comp 1.00c)
NHSTUB(kbd_read_keys,					0xFF8349F4)	// ok (comp 1.00c)
NHSTUB(kbd_p2_f,						0xff8342bc)	// ok (comp 1.00c)
NHSTUB(kbd_read_keys_r2,				0xFF864D8C)	// ok (comp 1.00c)
NHSTUB(lseek,							0xFF8371FC) // same as Lseek
NHSTUB(mkdir,							0xff83757c)	// ok (comp 1.00c)
NHSTUB(opendir,							0xFFAE2ACC)	// ok (comp 1.00c)
NHSTUB(openfastdir,						0xFFAE2ACC) // same as opendir
NHSTUB(reboot_fw_update,				0xFFAE8040)	// ok (comp 1.00c)
NHSTUB(strcat,							0xFF8B5328)	// ok (comp 1.00c)
NHSTUB(strchr,							0xff8140b4)	// ok (comp 1.00c)
NHSTUB(strlen,							0xFF814100)	// ok (comp 1.00c)
NHSTUB(strncpy,							0xff81402c)	// ok (comp 1.00c)
NHSTUB(strrchr,							0xFF8140D8)	// ok (comp 1.00c)
NHSTUB(time,							0xff88f66c)	// ok (comp 1.00c)
NHSTUB(MakeAFScan,						0xFF98AA10)	// ok (comp 1.00c)
NHSTUB(ExpCtrlTool_StopContiAE,			0xFF8475EC)	// ok ?
NHSTUB(ExpCtrlTool_StartContiAE,		0xFF847454)	// ok ?
NHSTUB(UnsetZoomForMovie,				0xFF9C57DC)	// ok (comp 1.00c)
NHSTUB(LEDDrive,						0xFF8647EC)	// ok (comp 1.00c)
NHSTUB(SetScriptMode,					0xFF89BF90)	// ok (comp 1.00c)
//NHSTUB(UnlockAndRefresh,				0xFF8B3A68)	// ok (comp 1.00c)
NHSTUB(RefreshPhysicalScreen,			0xFF8B3A68) // alias for UnlockAndRefresh
//NHSTUB(LockAndRefresh,				    0xFF8B50E4)	// ok (comp 1.00c)
NHSTUB(ScreenLock,						0xFF8B4C98)	// ok (comp 1.00c)
NHSTUB(ScreenUnlock,					0xFF8B4CFC)	// ok (comp 1.00c)
NHSTUB(apex2us,							0xFFA5C248)	// ok (comp 1.00c)
NHSTUB(WriteSDCard,						0xFF96E820)	// ok (comp 1.00c)
NHSTUB(GetKbdState,						0xFF865678)	// ok (comp 1.00c)
NHSTUB(UnlockAF,						0xFF838978)	// ok (comp 1.00c)
NHSTUB(DoAFLock,						0xFF838940)	// ok (comp 1.00c)
NHSTUB(GetImageFolder,					0xFF95F2FC)	// function before 'GetCameraObjectTmpPath ERROR' string
NHSTUB(UpdateMBROnFlash,				0xFF8767C8) // Search for 'BOOTDISK', function branches to this at end (after setting up R0,R1,R2)
NHSTUB(exmem_alloc,						0xFF88FFD8)	// search for ExMem.AllocCacheable (from reyalp)
NHSTUB(PutInNdFilter,                   0xFFB0501C)
NHSTUB(PutOutNdFilter,                  0xFFB05040)
NHSTUB(PT_MoveDigitalZoomToWide,		0xFF87F5C0)
NHSTUB(rand,							0xFFA5B370)	// search for 0x41C64E6D. Function before this value is rand.
NHSTUB(srand,							0xFFA5B364)	// search for 0x41C64E6D. Function before rand is srand.
NHSTUB(MoveIrisWithAv,					0xFFB04A28)

# Misc
NHSTUB(DebugAssert,						0xFF81EB78)	// ok (comp 1.00c)
NHSTUB(PT_GetPropertyCaseString,		0xFF8954F0)	// ok (comp 1.00c)
NHSTUB(err_init_task,					0xFF815FD4)	// ok (comp 1.00c)

# Addresses for firmware task handlers (used in taskHook)
DEF(task_CaptSeq,						0xFF88261C)	// ok (comp 1.00c)
DEF(task_InitFileModules,				0xFF89FC7C)	// ok (comp 1.00c)
DEF(task_RotaryEncoder,					0xFF8657EC)	// ok (comp 1.00c)
DEF(task_MovieRecord,					0xFF987094)	// ok (comp 1.00c)
DEF(task_ExpDrv,						0xFF8CC0D0)	// ok (comp 1.00c)

# Missing
NHSTUB(kbd_pwr_off,						0xFF810B1C)								// ??? not on sx20 or s95
NHSTUB(kbd_pwr_on,						0xFF810B1C)								// ??? not on sx20 or s95
NHSTUB(UIFS_WriteFirmInfoToFile,		0xFF810B1C)	// Is this needed?
NHSTUB(rewinddir,						0xFF810B1C)
NHSTUB(SetZoomActuatorSpeedPercent,		0xFF810B1C)
NHSTUB(Unmount_FileSystem,				0xFF810B1C)
NHSTUB(Mount_FileSystem,				0xFF810B1C)
