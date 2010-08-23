#include "stubs_asm.h"

//NHSTUB(SleepTask,                               0xFF83A0A0)    // eventproc_export_SleepTask()
NHSTUB(CreateTask,                                0xFF81E83C)    // eventproc_export_CreateTask()
NHSTUB(ExitTask,                                  0xFF81EACC)    // eventproc_export_ExitTask()
NHSTUB(AllocateMemory,                            0xFFAB8CF0)    // OK

NHSTUB(ExecuteEventProcedure,                     0xFF88B948)    // OK

//NHSTUB(mkdir,                                     0xFFC153D0)
//NHSTUB(open,                                      0xFF81A9E4)    // OK
//NHSTUB(write,                                     0xFF81ACDC)    // OK
//NHSTUB(close,                                     0xFF81AA94)    // OK
//NHSTUB(lseek,                                     0xFFC1516C)
//NHSTUB(read,                                      0xFF81AC7C)    // OK


NHSTUB(EnterToCompensationEVF, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(ExitFromCompensationEVF, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(GetCurrentAvValue, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(GetDrive_FreeClusters, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(GetZoomLensCurrentPoint, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(GetZoomLensCurrentPosition, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(Lseek, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(PT_PlaySound, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(ReadFastDir, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(RefreshPhysicalScreen, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(Remove, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(TurnOffBackLight, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(TurnOnBackLight, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(kbd_pwr_off, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(kbd_pwr_on, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(kbd_read_keys, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(openfastdir, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(qsort, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(readfastdir, 0xFFC00958)    // ToDo: nullsub_1
NHSTUB(rename, 0xFFC00958)    // ToDo: nullsub_1

NSTUB(Unmount_FileSystem, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(Mount_FileSystem, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(rewinddir, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(DoAFLock, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(UnlockAF, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(SetScriptMode, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(PostLEDMessage, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(UnsetZoomForMovie, 0xFFC00958)    // ToDo: nullsub_1
NSTUB(SetZoomActuatorSpeedPercent, 0xFFC00958)    // ToDo: nullsub_1
