#include "stubs_asm.h"

NHSTUB(PostLEDMessage, 0xFFC30AFC) // ???????? != forum
NHSTUB(MakeAFScan,  0xFFDE1F0C) //???????! != forum
NHSTUB(UIFS_WriteFirmInfoToFile, 0xffd0cf48) // should write 'A/FirmInfo.txt' //IDA
NHSTUB(UnlockAF, 0xffc158CC) //????????? !!!
NHSTUB(SetScriptMode, 0xffc5c5f4)

NHSTUB(GetCurrentTargetDistance, 0xFFD04C7C)  //
NHSTUB(ints_disable, 0xFFC00578)
NHSTUB(ints_enable, 0xFFC005A0)
NHSTUB(GetFocusLensSubjectDistance, 0xFFDE10C0) //needs verification just above the qprintf
NHSTUB(GetZoomLensCurrentPoint, 0xFFD08940)  // needs verification
NHSTUB(GetZoomLensCurrentPosition, 0xFFE99BE0)		// should be correct now
NHSTUB(VbattGet, 0xFFD0BED8) 					// which goes to B sub_ffc105e8 which is identical to VbattGet from 720
NHSTUB(kbd_read_keys, 0xFFC11C24)
NHSTUB(kbd_p1_f, 0xFFC11D28)
NHSTUB(kbd_p1_f_cont, 0xFFC11D34)
NHSTUB(kbd_p2_f, 0xFFC11560)
NHSTUB(kbd_pwr_on, 0xFFC318FC)  //FFC318FC
NHSTUB(kbd_pwr_off, 0xFFC00948)				// nullsubbed NOT FOUND prev value ffc370c0
NHSTUB(kbd_read_keys_r2, 0xFFC3138C)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00948) // NOT FOUND, set to nullsub same on 720
NHSTUB(strcat, 0xFFC6F4F4)					// Best match: 56% but 1 line sub identical to a720
NHSTUB(UnsetZoomForMovie, 0xFFD31F0C)
NHSTUB(LEDDrive, 0xFFC30F6C)
NHSTUB(TurnOnMic, 0xFFC31F80)
NHSTUB(TurnOffMic, 0xFFC31FAC)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFC219FC) // FFC219FC
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFC218B8)
NHSTUB(SetAE_ShutterSpeed, 0xFFE3579C)
NHSTUB(NewTaskShell, 0xFFC57C60)  // listed above... starts new shell on Console. GUI output?
NHSTUB(dumpMemoryToFile, 0xFFC141F4)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
NHSTUB(utime, 0xFFC00948)
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
// NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFC00948)
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
NHSTUB(EnterToCompensationEVF, 0xFFC15AA4)
NHSTUB (DoAFLock,  0xFFC157B4)
