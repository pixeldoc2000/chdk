#include "stubs_asm.h"

// ROM addresses

// used to point non existing or not found functions to empty sub
#define NULLSUB 0xFF810B1C

// --- not found by sigfinder
NHSTUB(Lseek, 0xFF836ED4)                            // OK, same as lseek, like G11
NHSTUB(RefreshPhysicalScreen, 0xFFA12124)            // OK, search String "ScreenUnLock", like G11
NHSTUB(ScreenLock, 0xFFA1356C)                       // search String "ScreenLock", G11 is different
NHSTUB(ScreenUnLock, 0xFFA12124)                     // aka. RefreshPhysicalScreen, search String "ScreenUnLock", G11 is different
NHSTUB(Remove, 0xFF836DEC)                           // OK!, like G11, SX200 is different but referens is same, llibtst.lua os.remove pass on file but fail on directory, wrong ?!?
NHSTUB(kbd_read_keys, 0xFF8347D4)                    // OK!!
NHSTUB(openfastdir, 0xFFA95C90)                      // OK, AKA. opendir, looks simular to A720, like G11
NHSTUB(readfastdir, 0xFFA95DE4)                      // maybe ok, looks simular to A720, G11 is different but referens is same
NHSTUB(ReadFastDir, 0xFFA95DE4)                      // aka. readfastdir
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF984AB4)         // OK!, eventproc
//NHSTUB(SetScriptMode, 0xFF895904)                  // eventproc
NHSTUB(SetScriptMode, 0xFF810F6C)                    // OK!, like SX210 and G11
//NHSTUB(UnlockAF, 0xFF83831C)                         // OK!, like SX210 and G11
NHSTUB(UnlockAF, 0xFF87A920)                         // PT_UnlockAF, like D10
//NHSTUB(DoAFLock, 0xFF8382E4)                         // OK!, like SX210 and G11
NHSTUB(DoAFLock, 0xFF87A910)                         // PT_DoAFLock, like D10

NHSTUB(GiveSemaphore, 0xFF839E38)                    // OK!!, eventproc, like G11
NHSTUB(GetDrive_FreeClusters, 0xFF871E90)            // OK!, like SX210 and G11, UI does show free space
NHSTUB(PT_PlaySound, 0xFF8840B8)                     // OK!, like SX210 and G11, plays sound on CHDK startup
//NHSTUB(rename, 0xFF83669C)                         // maybe OK, like SX210
NHSTUB(rename, 0xFF836E94)                           // maybe OK, like G11
NHSTUB(qsort, 0xFFB0B1F8)                            // maybe OK, like SX210, G11 and D10 are different but referens is same
NHSTUB(EnterToCompensationEVF, 0xFF8383E4)           // OK, like SX210 and G11
NHSTUB(ExitFromCompensationEVF, 0xFF838428)          // OK, like SX210 and G11
NHSTUB(PostLEDMessage, 0xFF860C6C)                   // like SX210
NHSTUB(TurnOffBackLight, 0xFF8A4980)                 // OK, like G11
NHSTUB(TurnOnBackLight, 0xFF8A4968)                  // OK, like G11
NHSTUB(GetZoomLensCurrentPoint, 0xFF965E54)          // OK, like SX210, G11 is different but referens is same
NHSTUB(GetZoomLensCurrentPosition, 0xFFAA9298)       // OK, like SX210, G11 is different but referens is same
NHSTUB(GetCurrentAvValue, 0xFF9644F8)                // OK, like SX210, G11 is different but referens is same
NHSTUB(PutInNdFilter, 0xFFB2056C)                    // OK, like G11, referens from Function Table (ROM:FFC2AE64)
NHSTUB(PutOutNdFilter, 0xFFB205A4)                   // OK, like G11, referens from Function Table (ROM:FFC2AE5C)


// Multi Partition Support
//NHSTUB(ReadSDCard, 0xFF9522B0)                     // probably, like SD990
// "Make bootable" does nothing, "Debug Parameters -> Create card with two partitions" cause shutdown (create_partitions())
NHSTUB(WriteSDCard, 0xFF952494)                      // shutdown
//NHSTUB(WriteSDCard, 0xFF9522B0)                    // shutdown
//NHSTUB(WriteSDCard, 0xFF95266C)                    // shutdown


// --- NULLSTUBS (not found by sigfinder)
NHSTUB(UnsetZoomForMovie, NULLSUB)                // nullsub_1, does not exist since canon firmware allow Zoom for Movie
NHSTUB(SetZoomActuatorSpeedPercent, NULLSUB)      // ToDo: nullsub_1


// --- Those aren't used or don't exist in DryOS (like A720 and other)
NHSTUB(Mount_FileSystem, NULLSUB)                 // nullsub_1
NHSTUB(Unmount_FileSystem, NULLSUB)               // nullsub_1
NHSTUB(rewinddir, NULLSUB)                        // nullsub_1
NHSTUB(kbd_pwr_off, NULLSUB)                      // nullsub_1, does not exist, like SD990
NHSTUB(kbd_pwr_on, NULLSUB)                       // nullsub_1, does not exist, like SD990


// --- stubs_entry.S (sigfinder)
// ROM:FF96CBFC register libc function
//NHSTUB(AllocateMemory, 0xffab8cf0)                 // OK!! (malloc)
//NHSTUB(AllocateMemory, 0xFF814100)                 // malloc, is the actual function, other are just jumps
//NHSTUB(AllocateUncacheableMemory, 0xff83a41c)      // OK!!
//NHSTUB(Close, 0xff836db8)                          // OK!!!, eventproc
//NHSTUB(CreateTask, 0xff81e83c)                     // OK!!, eventproc
//NHSTUB(DeleteFile_Fut, 0xff836730)                 // OK!
//NHSTUB(ExecuteEventProcedure, 0xFF88B9C0)          // cause shutdown, referens from FactoryMode Stuff and eventproc_export_ExecuteEventProcedure()
//NHSTUB(ExecuteEventProcedure, 0xFF88B948)          // sigfinder, like SD990, OK
//NHSTUB(ExitTask, 0xff81eacc)                       // OK!, eventproc
//NHSTUB(Fclose_Fut, 0xff8368ac)                     // OK!, eventproc
//NHSTUB(Feof_Fut, 0xff836a98)                       // OK!
//NHSTUB(Fflush_Fut, 0xff836ad4)                     // OK!!
//NHSTUB(Fgets_Fut, 0xff836a00)                      // OK!
//NHSTUB(Fopen_Fut, 0xff83686c)                      // OK!, eventproc
//NHSTUB(Fread_Fut, 0xff836958)                      // OK!, eventproc
//NHSTUB(FreeMemory, 0xffab8ce8)                     // OK!, eventproc
//NHSTUB(FreeUncacheableMemory, 0xff83a45c)          // OK!!
//NHSTUB(Fseek_Fut, 0xff836a4c)                      // OK!, eventproc
//NHSTUB(Fwrite_Fut, 0xff8369ac)                     // OK!, eventproc
//NHSTUB(GetBatteryTemperature, 0xff8652a0)          // OK
//NHSTUB(GetCCDTemperature, 0xff86522c)              // OK
//NHSTUB(GetDrive_ClusterSize, 0xff871e30)           // maybe ok, like D10
//NHSTUB(GetDrive_TotalClusters, 0xff871e64)         // maybe ok
//NHSTUB(GetFocusLensSubjectDistance, 0xff9629b8)    // maybe ok
//NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xff962d40) // maybe ok
//NHSTUB(GetOpticalTemperature, 0xff865314)          // maybe ok
//NHSTUB(GetParameterData, 0xff9975f4)               // OK!, like SX210
//NHSTUB(GetPropertyCase, 0xff88f660)                // OK!
//NHSTUB(GetSystemTime, 0xffab8d48)                  // OK!!, eventproc
//NHSTUB(IsStrobeChargeCompleted, 0xff8da44c)
//NHSTUB(IsStrobeChargeCompleted, 0xFF8DA424)        // maybe ok
NHSTUB(IsStrobeChargeCompleted, 0xFF8DA44C)          // like SX210
//NHSTUB(LocalTime, 0xff88923c)                      // OK
//NHSTUB(LockMainPower, 0xff895b78)                  // OK!
//NHSTUB(MakeDirectory_Fut, 0xff8367a4)              // OK, like SD990
//NHSTUB(MoveFocusLensToDistance, 0xffb228b0)
NHSTUB(MoveFocusLensToDistance, 0xFFB2289C)          // ?!?
//NHSTUB(MoveZoomLensWithPoint, 0xffab6b64)          // maybe ok
//NHSTUB(NewTaskShell, 0xff88f06c)                   // OK
//NHSTUB(Open, 0xff86f13c)                           // sigfinder, WRONG ?
//NHSTUB(Open, 0xFF81A9E4)                           // open, don't cause shutdown
//NHSTUB(Open, 0xFF836D4C)                           // eventproc, like SX210, cause shutdown
//NHSTUB(PostLogicalEventForNotPowerType, 0xff893948) // OK!!, eventproc
//NHSTUB(PostLogicalEventToUI, 0xff893994)           // OK!, eventproc
//NHSTUB(Read, 0xff81ac7c)                           // OK!!
//NHSTUB(RenameFile_Fut, 0xff836868)                 // sigfinder, WRONG!, does not point to function start
NHSTUB(RenameFile_Fut, 0xFF83669C)                   // OK, like SD990 and G11
//NHSTUB(SetAutoShutdownTime, 0xff895bec)            // OK
//NHSTUB(SetCurrentCaptureModeType, 0xff89e550)      // OK
//NHSTUB(SetFileTimeStamp, 0xff9514c0)               // sigfinder, WRONG!, does not point to function start
NHSTUB(SetFileTimeStamp, 0xFF837054)                 // maybe ok, like G11 and SX210
//NHSTUB(SetLogicalEventActive, 0xff8958b4)          // OK
//NHSTUB(SetParameterData, 0xff997564)               // maybe ok
//NHSTUB(SetPropertyCase, 0xff88f530)                // maybe ok
//NHSTUB(SleepTask, 0xff83a0a0)                      // OK eventproc
//NHSTUB(TakeSemaphore, 0xff839d68)                  // OK eventproc
//NHSTUB(UnlockMainPower, 0xff895acc)                // OK eventproc
//NHSTUB(UpdateMBROnFlash, 0xff813f98)               // WRONG
//NHSTUB(UpdateMBROnFlash, 0xFF871CB0)               // sigfinder, OK!
//NHSTUB(VbattGet, 0xff8330d8)                       // OK, eventproc
//NHSTUB(_log, 0xffb5b348)
//NHSTUB(_log10, 0xffb59fd4)
//NHSTUB(_pow, 0xffb5a144)
//NHSTUB(_sqrt, 0xffb5cf50)
//NHSTUB(close, 0xff81aa94)                          // OK!!!, like D10
//NHSTUB(closedir, 0xffa95e28)                       // does not point to function start
NHSTUB(closedir, 0xFFA95C40)                         // OK, like SX210
//NHSTUB(closefastdir, 0xffa95e28)                   // sigfinder, WRONG!, does not point to function start
NHSTUB(closefastdir, 0xFFA95C40)                     // aka. closedir
//NHSTUB(free, 0xff81415c)                           // OK!
//NHSTUB(kbd_p1_f, 0xff83484c)                       // OK
//NHSTUB(kbd_p1_f_cont, 0xff834858)                  // OK
//NHSTUB(kbd_p2_f, 0xff8340d0)                       // maybe ok
//NHSTUB(kbd_read_keys_r2, 0xff86122c)               // OK!
//NHSTUB(lseek, 0xff836ee0)                          // sigfinder, WRONG!, does not point to function start
NHSTUB(lseek, 0xFF836ED4)                            // OK, same as Lseek
//NHSTUB(malloc, 0xff814100)                         // OK!, referens from AllocateUncacheableMemory, D10 is different
//NHSTUB(memcmp, 0xff82066c)                         // OK!!, eventproc, like D10
//NHSTUB(memcpy, 0xff83fae8)                         // OK!!, eventproc, like D10
//NHSTUB(memset, 0xffa15ddc)                         // OK!, eventproc
//NHSTUB(mkdir, 0xff837254)                          // OK!, like SX210 and G11
//NHSTUB(mktime_ext, 0xff8ac9f0)                     // OK!, like SD990 and G11
//NHSTUB(open, 0xff81a9e4)                           // OK!!!, like D10
//NHSTUB(opendir, 0xffa95c90)                        // looks OK, AKA openfastdir, D10 is different
//NHSTUB(rand, 0xff820774)                           // OK
//NHSTUB(read, 0xff81ac7c)                           // OK!
//NHSTUB(srand, 0xff820768)                          // OK
//NHSTUB(stat, 0xff836f1c)                           // OK, like G11
//NHSTUB(strcat, 0xff813f5c)                         // WRONG, does point to strncpy
NHSTUB(strcat, 0xFF8AC1AC)                           // OK!!, like G11 and D10
//NHSTUB(strchr, 0xff813fe4)                         // OK!!, like D10
//NHSTUB(strcmp, 0xff820628)                         // OK
//NHSTUB(strcpy, 0xff820610)                         // OK
//NHSTUB(strftime, 0xff8ac3f8)                       // OK, like G11
//NHSTUB(strlen, 0xff814030)                         // OK
//NHSTUB(strncmp, 0xff813f98)                        // OK!, like D10
//NHSTUB(strncpy, 0xff813f5c)                        // OK!
//NHSTUB(strrchr, 0xff83fac0)                        // sigfinder, WRONG!
NHSTUB(strrchr, 0xFF814008)                          // OK!!, like G11 and D10
//NHSTUB(strtol, 0xff83fdc8)                         // OK
//NHSTUB(strtolx, 0xff83fbcc)                        // OK
//NHSTUB(time, 0xff88981c)                           // looks simular to A720
//NHSTUB(vsprintf, 0xff8205d4)                       // OK!
//NHSTUB(write, 0xff81acdc)                          // OK, like SD990 and G11
//NHSTUB(Write, 0xff836e48)                          // OK, eventproc, like SX210 and G11
//NHSTUB(Restart, 0xff83bbfc)                        // maybe OK, like G11


// DEBUG Stuff
NHSTUB(GetLogToFile, 0xFF975780)                     // this is where Event Procedure does jump (native call does shutdown camera), like G11
//NHSTUB(GetLogToFile, 0xFF975444)                   // directly points to function like A720
NHSTUB(dumpMemoryToFile, 0xFF836004)                 // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
NHSTUB(LogPrintf,0xFF88C920)                         // like D10

// video buffer stuff
NHSTUB(UnlockAndRefresh, 0xFFA13398)                 // SX20 102: ROM:FFA0498C, SX210: ROM:FFA1EDDC, search "Window Instance"
NHSTUB(LockAndRefresh, 0xFFA13354)                   // SX20 102: ROM:FFA048E8, SX210: ROM:FFA1ED98, search "Window Instance"


// PTP stuff
//NHSTUB(initialise_ptp_handlers_data, 0xFFA4E898)
NHSTUB(get_ptp_handler, 0xFFA4EC7C)
//NHSTUB(add_ptp_handler, 0xFFA4EABC)                // sigfinder address ok
NHSTUB(remove_ptp_handler, 0xFFA4EBB0)
NHSTUB(get_task_lists, 0xFF83544C)
NHSTUB(get_task_info, 0xFF813A38)
NHSTUB(PB2Rec, 0xFF898B40)                           // search String "AC:PB2Rec"
NHSTUB(Rec2PB, 0xFF897590)                           // search String "AC:Rec2PB"
//NHSTUB(set_control_event, 0xFF8955C4)              // via eventproc_export_IsControlEventActive (last call), levent_table contains control event id's (Logical Event Table)
//NHSTUB(set_control_event, 0xff895504)              // sigfinder ok (ptpcam --chdk mode command does work)
//NHSTUB(reboot_fw_update, 0xffa9b228)               // sigfinder address ok


NHSTUB(taskResume, 0xFF8955C4)                       // maybe

NHSTUB(GetImageFolder, 0xFF94337C)                   // like S95 and SD4500, function before 'GetCameraObjectTmpPath' string http://chdk.setepontos.com/index.php?topic=5641.msg58970#msg58970, for CAM_DATE_FOLDER_NAMING
//NHSTUB(GetImageFolder, 0xFF94345C)

NHSTUB(exmem_alloc, 0xFF88A17C)                      // = ExMem.AllocCacheable ?, experimental alternate memory allocation http://chdk.setepontos.com/index.php?topic=5980.0

NHSTUB(LEDDrive, 0xFF860C6C)                         // camera_set_led()
