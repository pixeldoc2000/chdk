#include "stubs_asm.h"

NHSTUB(PostLEDMessage, 0xFFC30AFC) // ???????? != forum
NHSTUB(MakeAFScan,  0xFFDE1F0C) //???????! != forum
NHSTUB(UIFS_WriteFirmInfoToFile, 0xffd0cf48) // should write 'A/FirmInfo.txt' //IDA
NHSTUB(UnlockAF, 0xffc158CC) //????????? !!!
NHSTUB(SetScriptMode, 0xffc5c5f4)

NHSTUB(SleepTask, 0xFFC17CAC)  //perfect match to 720
NHSTUB(CreateTask, 0xFFC0B8E0) //perfect match to 720
NHSTUB(ExitTask, 0xFFC0BB70) //perfect match to 720
NHSTUB(AllocateMemory, 0xFFDE4FD0)		//perfect match to 720
NHSTUB(ExecuteEventProcedure, 0xFFC5459C) //
NHSTUB(FreeMemory, 0xFFDE4FC8)				// * EXPORT FreeMemory  not found automatically, but it's above AllocateMemory in both firms
NHSTUB(GetCurrentTargetDistance, 0xFFD04C7C)  //
NHSTUB(GetSystemTime, 0xFFDE5028) //EXPORT GetSystemTime
NHSTUB(ints_disable, 0xFFC00578)
NHSTUB(ints_enable, 0xFFC005A0)
NHSTUB(memcmp, 0xFFC0D90C)
NHSTUB(memcpy, 0xFFC6F708)
NHSTUB(memset, 0xFFD70E34)
NHSTUB(Close, 0xFFC13B7C)
NHSTUB(Open, 0xFFC13B54)
NHSTUB(Read, 0xFFC0A15C)
NHSTUB(Write, 0xFFC13C28)
NHSTUB(Lseek, 0xFFC13CBC)
NHSTUB(strcmp, 0xFFC0D8A4)
NHSTUB(strcpy, 0xFFC0D88C)
NHSTUB(strlen, 0xFFC0D8E8)
NHSTUB(TakeSemaphore, 0xFFC0B774)
NHSTUB(vsprintf, 0xFFC0D80C)
NHSTUB(GetFocusLensSubjectDistance, 0xFFDE10C0) //needs verification just above the qprintf
NHSTUB(GetZoomLensCurrentPoint, 0xFFD08940)  // needs verification
NHSTUB(GetZoomLensCurrentPosition, 0xFFE99BE0)		// should be correct now
NHSTUB(RefreshPhysicalScreen, 0xFFD70A80)
NHSTUB(GetPropertyCase, 0xFFC5819C)			// 70% but seems right
NHSTUB(SetPropertyCase, 0xFFC5809C)				// initially mistaken for FFC5819C which is GetPropertyCase
NHSTUB(VbattGet, 0xFFD0BED8) 					// which goes to B sub_ffc105e8 which is identical to VbattGet from 720
NHSTUB(kbd_read_keys, 0xFFC11C24)
NHSTUB(kbd_p1_f, 0xFFC11D28)
NHSTUB(kbd_p1_f_cont, 0xFFC11D34)
NHSTUB(kbd_p2_f, 0xFFC11560)
NHSTUB(kbd_pwr_on, 0xFFC318FC)  //FFC318FC
NHSTUB(kbd_pwr_off, 0xFFC00948)				// nullsubbed NOT FOUND prev value ffc370c0
NHSTUB(kbd_read_keys_r2, 0xFFC3138C)
NHSTUB(mkdir, 0xFFC13F20)
NHSTUB(GetParameterData, 0xFFD2CE50)
NHSTUB(SetParameterData, 0xFFD2CDC0)
NHSTUB(IsStrobeChargeCompleted, 0xFFC981B0)
NHSTUB(open, 0xFFC09EC4)
NHSTUB(write, 0xFFC0A1BC)
NHSTUB(close, 0xFFC09F74)
NHSTUB(lseek, 0xFFC13CBC)     // = Lseek was nullsubbed FFC00948
NHSTUB(read, 0xFFC0A15C)
NHSTUB(Fopen_Fut, 0xFFC13564)
NHSTUB(Fwrite_Fut, 0xFFC136A4)
NHSTUB(Fclose_Fut, 0xFFC135A4)
NHSTUB(Fread_Fut, 0xFFC13650)
NHSTUB(Fseek_Fut, 0xFFC13744)
NHSTUB(Remove, 0xFFC13BC4)
NHSTUB(rename, 0xFFC13C50)
NHSTUB(LockMainPower, 0xFFC5C808)
NHSTUB(UnlockMainPower, 0xFFC5C75C)
NHSTUB(GetCurrentAvValue, 0xFFD05B84)
NHSTUB(MoveFocusLensToDistance, 0xFFE330B8)		// low percent but seems right
NHSTUB(MoveZoomLensWithPoint, 0xFFDE1870)		// same
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00948) // NOT FOUND, set to nullsub same on 720
NHSTUB(_log, 0xFFE5A024)
NHSTUB(_log10, 0xFFE58F68)
NHSTUB(_pow, 0xFFE590D8) //
NHSTUB(_sqrt, 0xFFE5B38C)
NHSTUB(malloc, 0xFFC039C4)
NHSTUB(free, 0xFFC03A98)
NHSTUB(FreeUncacheableMemory, 0xFFC17E5C)			// *
NHSTUB(AllocateUncacheableMemory, 0xFFC17E28)	// *
NHSTUB(rand, 0xFFC0DA14)
NHSTUB(srand, 0xFFC0DA08)
NHSTUB(stat, 0xFFC13D88)						// *
NHSTUB(openfastdir, 0xFFDCE7CC)
NHSTUB(readfastdir, 0xFFDCE860)
NHSTUB(closefastdir, 0xFFDCE930)
NHSTUB(qsort, 0xFFD7133C)
// NHSTUB(strstr, 0xFFD62534) 		// NOT FOUND, commented in a720 also
NHSTUB(strncpy, 0xFFC1D80C)//traced with STRNEB  R1, [R3],#1
NHSTUB(strrchr, 0xFFC6F5A0)//traced with AND     R3, R1, #0xFF
NHSTUB(strncmp, 0xFFC6F530)
NHSTUB(strchr, 0xFFC6F57C)
NHSTUB(strcat, 0xFFC6F4F4)					// Best match: 56% but 1 line sub identical to a720
NHSTUB(strtol, 0xFFC1DA44)
NHSTUB(time, 0xFFC52170)
NHSTUB(LocalTime, 0xFFC522BC)
NHSTUB(UpdateMBROnFlash, 0xFFC3D754)
NHSTUB(opendir, 0xFFDCE7CC)
NHSTUB(ReadFastDir, 0xFFDCE860)		// not sure if needed, but a720 lists both with same address
NHSTUB(closedir, 0xFFDCE930)
NHSTUB(UnsetZoomForMovie, 0xFFD31F0C)
//NHSTUB(PostLEDMessage, 0xFFC00948)	// NOT FOUND null stubbed
NHSTUB(LEDDrive, 0xFFC30F6C)
NHSTUB(TurnOnMic, 0xFFC31F80)
NHSTUB(TurnOffMic, 0xFFC31FAC)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFC219FC) // FFC219FC
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFC218B8)
//NHSTUB(MakeAFScan,  0xFFC00948) 	// NOT FOUND, have to look around.... maybe 0xFFDD4AA4
NHSTUB(SetAE_ShutterSpeed, 0xFFE3579C)
NHSTUB(NewTaskShell, 0xFFC57C60)  // listed above... starts new shell on Console. GUI output?
//NHSTUB(UIFS_WriteFirmInfoToFile, 0xFFD220A8) // listed above... should write 'A/FirmInfo.txt'
NHSTUB(dumpMemoryToFile, 0xFFC141F4)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
NHSTUB(utime, 0xFFC00948)
//NHSTUB(CreatePhysicalVram,		 0xFFC00948)
//NHSTUB(CreateTaskStrict,			 0xFFC00948)
//NHSTUB(DisableDispatch,			 0xFFC00948)
//NHSTUB(DisplayImagePhysicalScreen,	 0xFFC00948)
//NHSTUB(EnableDispatch,			 0xFFC00948)
//NHSTUB(ioctl,				 0xFFC00948)
//NHSTUB(iosDevAdd,			 0xFFC00948)
//NHSTUB(iosDrvInstall,			 0xFFC00948)
//NHSTUB(memPartAlloc,			 0xFFC00948)
//NHSTUB(memPartFindMax,			 0xFFC00948)
//NHSTUB(PhySw_testgpio,			 0xFFC00948)
//NHSTUB(ProtectFile,			 0xFFC00948)
//NHSTUB(taskCreateHookAdd,		 0xFFC00948)
//NHSTUB(taskDeleteHookAdd,		 0xFFC00948)
//NHSTUB(taskIdListGet,			 0xFFC00948)
NHSTUB(taskLock,				 0xFFC00948)
NHSTUB(taskUnlock,			 0xFFC00948)
NHSTUB(Mount_FileSystem,			 0xFFC00948)
NHSTUB(Unmount_FileSystem,		 0xFFC00948)
NHSTUB(rewinddir,			 0xFFC00948)
NHSTUB(CreatePhysicalVram,		 0xFFC00948)
NHSTUB(CreateTaskStrict,			 0xFFC00948)
NHSTUB(DisableDispatch,			 0xFFC00948)
NHSTUB(DisplayImagePhysicalScreen,	 0xFFC00948)
NHSTUB(EnableDispatch,			 0xFFC00948)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFC00948)
NHSTUB(MakeDirectory,			 0xFFC00948)
NHSTUB(PhySw_testgpio,			 0xFFC00948)
NHSTUB(ProtectFile,			 0xFFC00948)
NHSTUB(chdir,				 0xFFC00948)
NHSTUB(ioctl,				 0xFFC00948)
NHSTUB(iosDevAdd,			 0xFFC00948)
NHSTUB(iosDrvInstall,			 0xFFC00948)
NHSTUB(isalpha,				 0xFFC00948)
NHSTUB(isdigit,				 0xFFC00948)
NHSTUB(islower,				 0xFFC00948)
NHSTUB(isspace,				 0xFFC00948)
NHSTUB(isupper,				 0xFFC00948)
NHSTUB(localtime,			 0xFFC00948)
NHSTUB(readdir,				 0xFFC00948)
NHSTUB(strpbrk,				 0xFFC00948)
NHSTUB(taskCreateHookAdd,		 0xFFC00948)
NHSTUB(taskDeleteHookAdd,		 0xFFC00948)
NHSTUB(taskIdListGet,			 0xFFC00948)
NHSTUB(taskName,			 0xFFC00948)
NHSTUB(taskResume,			 0xFFC00948)
NHSTUB(taskSuspend,			 0xFFC00948)
NHSTUB(GetBatteryTemperature, 0xFFC33A38)
NHSTUB(GetCCDTemperature, 0xFFC339C8)
NHSTUB(GetOpticalTemperature, 0xFFC33AA8)
NHSTUB(PT_PlaySound, 0xFFC47374)
NHSTUB(EnterToCompensationEVF, 0xFFC15AA4)
NHSTUB(ExitFromCompensationEVF, 0xFFC15BF0)
NHSTUB (DoAFLock,  0xFFC157B4)
// NHSTUB(DeleteFile_Fut, 0xFFC13428)					// best match 75%, 79% in 720
// NHSTUB(Feof_Fut, 0xFFC13790)			// a720 says not found, but it looks right
// NHSTUB(Fflush_Fut, 0xFFC137CC)		// not 100% sure but looks right
// NHSTUB(Fgets_Fut, 0xFFC136F8)
// NHSTUB(MakeDirectory_Fut, 0xFFC1349C)			// low percent but seems right
// NHSTUB(RenameFile_Fut, 0xFFC133D4)
// NHSTUB(SetAutoShutdownTime, 0xFFC5C87C)
// NHSTUB(SetFileTimeStamp, 0xFFC13E58)
// NHSTUB(CloseFastDir, 0xFFDCE930)
// NHSTUB(mktime_ext, 0xFFC6FF74)
// NHSTUB(strftime, 0xFFC6F97C)
//NHSTUB(MoveZoomLensWithPosition, 0xFFDE18B4)		// not at all in entry.S but added myself
//NHSTUB(GetOpticalTemperature, 0xFFC33AA8)		//listed above
// NHSTUB(strncpy, 0xFFC0E84C)		// NOT FOUND, go to nullsub
// NHSTUB(strrchr, 0xFFC71BCC)   // NOT FOUND, go to nullsub
//NHSTUB(GetCurrentAvValue, 0xFFD05A14)		// FOUND,see up, left in case that's bad... // add with nullsub? MAYBE  FFD05A14, FFCFFCA8 in a720

