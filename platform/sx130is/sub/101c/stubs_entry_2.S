#include "stubs_asm.h"

#define NULL_STUB 0xFF810B1C

// Not found

NHSTUB(EnterToCompensationEVF, 0xFF838628)     
NHSTUB(ExitFromCompensationEVF, 0xFF83866C)    
NHSTUB(GetCCDTemperature, 0xFF862FDC)          
NHSTUB(GetCurrentAvValue, 0xFF9625C0)          
NHSTUB(GetDrive_FreeClusters, 0xFF870A18)      
NHSTUB(GetParameterData, 0xFF993A0C)           
NHSTUB(GetZoomLensCurrentPoint, 0xFF963FC8)    
NHSTUB(GetZoomLensCurrentPosition, 0xFFA9FE7C) 
NHSTUB(Lseek, 0xFF836E18)                      
NHSTUB(PT_PlaySound, 0xFF8824E4)               
NHSTUB(ReadFastDir, 0xFFA8C488)                
NHSTUB(RefreshPhysicalScreen, 0xFF8A788C)      // 0xFF8A8D90 ?
NHSTUB(Remove, 0xFF836D30)                     
NHSTUB(SetParameterData, 0xFF993978)           
NHSTUB(TurnOffBackLight, 0xFF8A0584)           
NHSTUB(TurnOnBackLight, 0xFF8A056C)            
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF98420C)   
NHSTUB(kbd_read_keys, 0xFF834658)              
NHSTUB(openfastdir, 0xFFA8C334)                
NHSTUB(qsort, 0xFFAF8800)                      
NHSTUB(readfastdir, 0xFFA8C488)                
NHSTUB(free, 0xFF814244)                      
//NHSTUB(free, 0xFF83A5AC) // Test 
//NHSTUB(malloc, 0xFF83A5B0) // Test
NHSTUB(rename, 0xFF836DD8)                     
NHSTUB(strtol, 0xFF83FFE4)                     
NSTUB(GetBatteryTemperature, NULL_STUB)        // Does not work in SX130


// Less than 100%

NHSTUB(Close, 0xff836cfc)                                   
NHSTUB(ExitTask, 0xff81eb30)
NHSTUB(FreeUncacheableMemory, 0xff83a69c)
NHSTUB(GetDrive_ClusterSize, 0xff8709b8)
NHSTUB(GetDrive_TotalClusters, 0xff8709ec)
NHSTUB(GetFocusLensSubjectDistance, 0xff9609ac)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xff960df8)
NHSTUB(GetOpticalTemperature, 0xff8630c8)
NHSTUB(GetPropertyCase, 0xff88d7a0)
NHSTUB(GetSystemTime, 0xffab1a34)
NHSTUB(IsStrobeChargeCompleted, 0xff8d7004)
NHSTUB(LockMainPower, 0xff893fec)
NHSTUB(MakeDirectory_Fut, 0xff8366e8)
NHSTUB(MoveFocusLensToDistance, 0xffb0994c)
NHSTUB(MoveZoomLensWithPoint, 0xffaaea3c)
NHSTUB(NewTaskShell, 0xff88d1bc)
NHSTUB(Open, 0xFF836C90)                                   // orig:0xff86dcb0
NHSTUB(PostLogicalEventForNotPowerType, 0xff891d90)
NHSTUB(PostLogicalEventToUI, 0xff891ddc)
NHSTUB(RenameFile_Fut, 0xFF8365E0)                         // orig:0xff8367ac
NHSTUB(Restart, 0xff83be48)
NHSTUB(SetAutoShutdownTime, 0xff894060)
NHSTUB(SetCurrentCaptureModeType, 0xff89abfc)
NHSTUB(SetFileTimeStamp, 0xFF836F98)                       // orig:0xff94f194
NHSTUB(SetLogicalEventActive, 0xff893d38)
NHSTUB(SetPropertyCase, 0xff88d678)
NHSTUB(SleepTask, 0xff83a2e0)
NHSTUB(TakeSemaphore, 0xff839fa8)
NHSTUB(UnlockMainPower, 0xff893f40)
NHSTUB(UpdateMBROnFlash, 0xff870838)                       // same code on sx120 and d10, sikahr:0xff814068
NHSTUB(VbattGet, 0xff832fb4)
NHSTUB(closedir, 0xFFA8C2E4)                               // orig:0xffa8c4cc
NHSTUB(closefastdir, 0xFFA8C2E4)                           // orig:0xffa8c4cc
NHSTUB(kbd_p1_f, 0xff8346d0)
NHSTUB(kbd_p1_f_cont, 0xff8346dc)
NHSTUB(kbd_p2_f, 0xff833f18)
NHSTUB(kbd_read_keys_r2, 0xff85f5c4)
NHSTUB(lseek, 0xFF836E18)                                  // orig:0xff836e24
NHSTUB(mkdir, 0xff837198)
NHSTUB(opendir, 0xffa8c334)
NHSTUB(reboot_fw_update, 0xffa918a8)
NHSTUB(strcat, 0xFF8A8FE0)                                 // orig:0xff81402c 
NHSTUB(strchr, 0xff8140b4)
NHSTUB(strlen, 0xFF814100)                                 // orig:0xff8206ac
NHSTUB(strncpy, 0xff81402c)
NHSTUB(strrchr, 0xFF8140D8)                                // orig:0xff83fcdc
NHSTUB(time, 0xff8879c8)

// Missing from stubs_entry.s

NHSTUB(DoAFLock, 0xFF8384D8)                                
NHSTUB(LEDDrive, 0xFF85F1BC)                                // inner function like in sx120 and d10, sikahr:xFF96A8B0
NHSTUB(ScreenLock, 0xFF8A8A1C)                              // 0xFF8A8DB4 like in sx120 and d10?
NHSTUB(ScreenUnlock, 0xFF8A8A80)                            // 0xFF8A788C like in sx120 and d10?
//NHSTUB(ScreenLock, 0xFF8A8DB4)                            // does not draw Canon interface
//NHSTUB(ScreenUnlock, 0xFF8A788C)                          // does not draw Canon interface
NHSTUB(SetScriptMode, 0xFF893D88)                          
NHSTUB(UnlockAF, 0xFF838510)                  
NHSTUB(WriteSDCard, 0xFF950268)     
NHSTUB(apex2us, 0xFFA0E804)      
NHSTUB(GetImageFolder, 0xFF9419AC)							// function before 'GetCameraObjectTmpPath ERROR' string  
NHSTUB(GetKbdState, 0xFF85FC0C)  

NHSTUB(UnlockAndRefresh,				0xFF8A8D90) // seems to work
NHSTUB(LockAndRefresh,				    0xFF8A8DB4) // seems to work  
  
// These don't exist/aren't found in dryos
NHSTUB(Mount_FileSystem, NULL_STUB)
NHSTUB(Unmount_FileSystem, NULL_STUB) 
NHSTUB(rewinddir, NULL_STUB) 
NHSTUB(SetZoomActuatorSpeedPercent, NULL_STUB)

// Not needed
NHSTUB(kbd_pwr_on, NULL_STUB)                  
NHSTUB(kbd_pwr_off, NULL_STUB)


NHSTUB(rand, 0xFFA0D940)                    
NHSTUB(srand, 0xFFA0D934)



NHSTUB(DebugAssert, 0xFF81EB78)								// Usefull in tasks

// allocate from given EXMEM pool 
NHSTUB(exmem_alloc, 0xFF888334)
