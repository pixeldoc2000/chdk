#include "stubs_asm.h"

// --- not found by finsig
NHSTUB(EnterToCompensationEVF, 0xFF810B1C)          // ToDo: nullsub_1
NHSTUB(ExitFromCompensationEVF, 0xFF810B1C)         // ToDo: nullsub_1
NHSTUB(GetCurrentAvValue, 0xFF810B1C)               // ToDo: nullsub_1
NHSTUB(GetDrive_FreeClusters, 0xFF810B1C)           // ToDo: nullsub_1
NHSTUB(GetZoomLensCurrentPoint, 0xFF810B1C)         // ToDo: nullsub_1
NHSTUB(GetZoomLensCurrentPosition, 0xFF810B1C)      // ToDo: nullsub_1
NHSTUB(Lseek, 0xFF810B1C)                           // ToDo: nullsub_1
NHSTUB(PT_PlaySound, 0xFF810B1C)                    // ToDo: nullsub_1
NHSTUB(ReadFastDir, 0xFF810B1C)                     // ToDo: nullsub_1
NHSTUB(RefreshPhysicalScreen, 0xFFA12124)           // ?!? search String "ScreenUnLock"
NHSTUB(Remove, 0xFF810B1C)                          // ToDo: nullsub_1
NHSTUB(TurnOffBackLight, 0xFF810B1C)                // ToDo: nullsub_1
NHSTUB(TurnOnBackLight, 0xFF810B1C)                 // ToDo: nullsub_1
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF810B1C)        // ToDo: nullsub_1
NHSTUB(kbd_pwr_off, 0xFF810B1C)                     // ?!? does not exist like SD990
NHSTUB(kbd_pwr_on, 0xFF810B1C)                      // ?!? does not exist like SD990
NHSTUB(kbd_read_keys, 0xFF8347D4)                   // ?!?
NHSTUB(openfastdir, 0xFF810B1C)                     // ToDo: nullsub_1
NHSTUB(qsort, 0xFF810B1C)                           // ToDo: nullsub_1
NHSTUB(readfastdir, 0xFF810B1C)                     // ToDo: nullsub_1
NHSTUB(rename, 0xFF810B1C)                          // ToDo: nullsub_1
NHSTUB(rewinddir, 0xFF810B1C)                        // ToDo: nullsub_1
NHSTUB(DoAFLock, 0xFF810B1C)                         // ToDo: nullsub_1
NHSTUB(UnlockAF, 0xFF810B1C)                         // ToDo: nullsub_1
NHSTUB(SetScriptMode, 0xFF810B1C)                    // ToDo: nullsub_1
NHSTUB(PostLEDMessage, 0xFF810B1C)                   // ToDo: nullsub_1
NHSTUB(UnsetZoomForMovie, 0xFF810B1C)                // ToDo: nullsub_1
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810B1C)      // ToDo: nullsub_1
NHSTUB(PutInNdFilter, 0xFF810B1C)                    // ToDo: nullsub_1
NHSTUB(PutOutNdFilter, 0xFF810B1C)                   // ToDo: nullsub_1


// --- Those aren't used or don't exist in DryOS (like A720)
NHSTUB(Mount_FileSystem, 0xFF810B1C)                 // ToDo: nullsub_1
NHSTUB(Unmount_FileSystem, 0xFF810B1C)               // ToDo: nullsub_1


// --- stubs_entry.S (auto sig finder)
//NHSTUB(AllocateMemory, 0xffab8cf0)                 OK
//NHSTUB(AllocateUncacheableMemory, 0xff83a41c)      maybe ok
//NHSTUB(Close, 0xff836db8)                          does point to eventproc_export_Close
NHSTUB(Close, 0xFF81AA94)                            OK
//NHSTUB(CreateTask, 0xff81e83c)                     OK eventproc
//NHSTUB(DeleteFile_Fut, 0xff836730)
// ERROR: EnterToCompensationEVF is not found!
//NHSTUB(ExecuteEventProcedure, 0xff88b9c0)          maybe ok, there are two simular functions
NHSTUB(ExecuteEventProcedure, 0xFF88B948)            // ?!?
// ERROR: ExitFromCompensationEVF is not found!
//NHSTUB(ExitTask, 0xff81eacc)                       OK
//NHSTUB(Fclose_Fut, 0xff8368ac)                     OK
//NHSTUB(Feof_Fut, 0xff836a98)
//NHSTUB(Fflush_Fut, 0xff836ad4)
//NHSTUB(Fgets_Fut, 0xff836a00)
//NHSTUB(Fopen_Fut, 0xff83686c)                      OK
//NHSTUB(Fread_Fut, 0xff836958)                      OK
//NHSTUB(FreeMemory, 0xffab8ce8)                     maybe ok
//NHSTUB(FreeUncacheableMemory, 0xff83a45c)
//NHSTUB(Fseek_Fut, 0xff836a4c)                      OK
//NHSTUB(Fwrite_Fut, 0xff8369ac)                     OK
//NHSTUB(GetBatteryTemperature, 0xff8652a0)          maybe ok
//NHSTUB(GetCCDTemperature, 0xff86522c)              maybe ok
// ERROR: GetCurrentAvValue is not found!
//NHSTUB(GetDrive_ClusterSize, 0xff871e30)           maybe ok
// ERROR: GetDrive_FreeClusters is not found!
//NHSTUB(GetDrive_TotalClusters, 0xff871e64)         maybe ok
//NHSTUB(GetFocusLensSubjectDistance, 0xff9629b8)    maybe ok
//NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xff962d40) maybe ok
//NHSTUB(GetOpticalTemperature, 0xff865314)          maybe ok
//NHSTUB(GetParameterData, 0xff9975f4)               maybe ok
//NHSTUB(GetPropertyCase, 0xff88f660)                OK
//NHSTUB(GetSystemTime, 0xffab8d48)                  OK
// ERROR: GetZoomLensCurrentPoint is not found!
// ERROR: GetZoomLensCurrentPosition is not found!
//NHSTUB(IsStrobeChargeCompleted, 0xff8da44c)
NHSTUB(IsStrobeChargeCompleted, 0xFF8DA424)          // ?!?
//NHSTUB(LocalTime, 0xff88923c)
//NHSTUB(LockMainPower, 0xff895b78)                  OK
// ERROR: Lseek is not found!
//NHSTUB(MakeDirectory_Fut, 0xff8367a4)              maybe ok
//NHSTUB(MoveFocusLensToDistance, 0xffb228b0)
NHSTUB(MoveFocusLensToDistance, 0xFFB2289C)          // ?!?
//NHSTUB(MoveZoomLensWithPoint, 0xffab6b64)          maybe ok
//NHSTUB(NewTaskShell, 0xff88f06c) OK
//NHSTUB(Open, 0xff86f13c)
// ERROR: PT_PlaySound is not found!
//NHSTUB(PostLogicalEventForNotPowerType, 0xff893948) OK
//NHSTUB(PostLogicalEventToUI, 0xff893994)           OK
//NHSTUB(Read, 0xff81ac7c)                           OK
// ERROR: ReadFastDir is not found!
// ERROR: RefreshPhysicalScreen is not found!
// ERROR: Remove is not found!
//NHSTUB(RenameFile_Fut, 0xff836868)                 WRONG
// ALT: NHSTUB(RenameFile_Fut, 0xffa79a44) // 8/7
// ALT: NHSTUB(RenameFile_Fut, 0xffa79a94) // 8/7
//NHSTUB(SetAutoShutdownTime, 0xff895bec)            OK
//NHSTUB(SetCurrentCaptureModeType, 0xff89e550)      OK
//NHSTUB(SetFileTimeStamp, 0xff9514c0)               maybe ok
//NHSTUB(SetLogicalEventActive, 0xff8958b4)          OK
//NHSTUB(SetParameterData, 0xff997564)               wrong?
//NHSTUB(SetPropertyCase, 0xff88f530)                maybe ok
//NHSTUB(SleepTask, 0xff83a0a0)                      OK eventproc
//NHSTUB(TakeSemaphore, 0xff839d68)                  OK eventproc
// ERROR: TurnOffBackLight is not found!
// ERROR: TurnOnBackLight is not found!
// ERROR: UIFS_WriteFirmInfoToFile is not found!
//NHSTUB(UnlockMainPower, 0xff895acc)                OK eventproc
//NHSTUB(UpdateMBROnFlash, 0xff813f98)
//NHSTUB(VbattGet, 0xff8330d8)                       maybe ok
//NHSTUB(Write, 0xff836e48)                          OK eventproc
//NHSTUB(_log, 0xffb5b348)
//NHSTUB(_log10, 0xffb59fd4)
//NHSTUB(_pow, 0xffb5a144)
//NHSTUB(_sqrt, 0xffb5cf50)
//NHSTUB(close, 0xff81aa94)                          OK
//NHSTUB(closedir, 0xffa95e28)                       does not point to function start
//NHSTUB(closefastdir, 0xffa95e28)                   same as closedir
//NHSTUB(free, 0xff81415c)                           maybe ok
//NHSTUB(kbd_p1_f, 0xff83484c)                       looks ok
//NHSTUB(kbd_p1_f_cont, 0xff834858)                  looks ok
//NHSTUB(kbd_p2_f, 0xff8340d0)                       maybe ok
// ERROR: kbd_pwr_off is not found!
// ERROR: kbd_pwr_on is not found!
// ERROR: kbd_read_keys is not found!
//NHSTUB(kbd_read_keys_r2, 0xff86122c)               OK
//NHSTUB(lseek, 0xff836ee0) does not point to function start
//NHSTUB(malloc, 0xff814100)                         OK
//NHSTUB(memcmp, 0xff82066c)                         OK
//NHSTUB(memcpy, 0xff83fae8)                         OK
//NHSTUB(memset, 0xffa15ddc)                         OK
//NHSTUB(mkdir, 0xff837254)                          maybe ok
//NHSTUB(mktime_ext, 0xff8ac9f0)
//NHSTUB(open, 0xff81a9e4)                           OK
//NHSTUB(opendir, 0xffa95c90)                        looks OK
// ERROR: openfastdir is not found!
// ERROR: qsort is not found!
//NHSTUB(rand, 0xff820774)
//NHSTUB(read, 0xff81ac7c)                           OK
// ERROR: readfastdir is not found!
// ERROR: rename is not found!
//NHSTUB(srand, 0xff820768)
//NHSTUB(stat, 0xff836f1c)
//NHSTUB(strcat, 0xff813f5c)
//NHSTUB(strchr, 0xff813fe4)                         maybe ok
//NHSTUB(strcmp, 0xff820628)                         OK
//NHSTUB(strcpy, 0xff820610)                         OK
//NHSTUB(strftime, 0xff8ac3f8)
//NHSTUB(strlen, 0xff814030)                         OK
//NHSTUB(strncmp, 0xff813f98)
//NHSTUB(strncpy, 0xff813f5c)
//NHSTUB(strrchr, 0xff83fac0)
// ALT: NHSTUB(strrchr, 0xff8ac1c0) // 18/8
//NHSTUB(strtol, 0xff83fdc8)
//NHSTUB(strtolx, 0xff83fbcc)
//NHSTUB(time, 0xff88981c)                           looks ok
//NHSTUB(vsprintf, 0xff8205d4)
//NHSTUB(write, 0xff81acdc)                          OK


// --- DEBUG Stuff
//NHSTUB(GetLogToFile, 0xFF975780)
