
NSTUB(eventproc_export_memShow, 0xff810dc8)

NSTUB(eventproc_export_strlen, 0xff814030)

NSTUB(eventproc_export_CreateTask, 0xff81e83c)

NSTUB(eventproc_export_ExitTask, 0xff81eacc)

NSTUB(eventproc_export_RotateConsoleZOder, 0xff81f21c)

NSTUB(eventproc_export_CPrintf, 0xff81f42c)
NSTUB(eventproc_export_CPutChar, 0xff81f488)
NSTUB(eventproc_export_GetCh, 0xff81f4b4)
NSTUB(eventproc_export_GetStringWithPrompt, 0xff81f504)
NSTUB(eventproc_export_OpenConsole, 0xff81f564)
NSTUB(eventproc_export_CloseConsole, 0xff81f6d0)

NSTUB(eventproc_export_StartRedirectUART, 0xff81fdcc)
NSTUB(eventproc_export_StopRedirectUART, 0xff81fee4)

NSTUB(eventproc_export_sprintf, 0xff820590)

NSTUB(eventproc_export_strcpy, 0xff820610)
NSTUB(eventproc_export_strcmp, 0xff820628)
NSTUB(eventproc_export_memcmp, 0xff82066c)

NSTUB(eventproc_export_Fopen_Fut, 0xff83686c)
NSTUB(eventproc_export_Fclose_Fut, 0xff8368ac)
NSTUB(eventproc_export_Fread_Fut, 0xff836958)
NSTUB(eventproc_export_Fwrite_Fut, 0xff8369ac)

NSTUB(eventproc_export_Fseek_Fut, 0xff836a4c)

NSTUB(eventproc_export_Open, 0xff836d4c)
NSTUB(eventproc_export_Close, 0xff836db8)

NSTUB(eventproc_export_Read, 0xff836e44)
NSTUB(eventproc_export_Write, 0xff836e48)

NSTUB(eventproc_export_Lseek, 0xff836ed4)
NSTUB(eventproc_export_OpenForScrip, 0xff836ef4)

NSTUB(eventproc_export_NewTaskShell, 0xff837320)

NSTUB(eventproc_export_ExMem, 0xff837338)
NSTUB(eventproc_export_CameraLog, 0xff83738c)

NSTUB(eventproc_export_DryShell, 0xff837528)

NSTUB(eventproc_export_CreateCountingSemaphore, 0xff839c64)
NSTUB(eventproc_export_DeleteSemaphore, 0xff839cbc)

NSTUB(eventproc_export_TakeSemaphore, 0xff839d68)
NSTUB(eventproc_export_GiveSemaphore, 0xff839e38)

NSTUB(eventproc_export_SleepTask, 0xff83a0a0)

NSTUB(eventproc_export_TurnOffE1, 0xff83b9b8)

NSTUB(eventproc_export_memcpy, 0xff83fae8)

NSTUB(eventproc_export_ChangePowerState, 0xff85f9bc)

NSTUB(eventproc_export_HdmiSimulateModeStop, 0xff85ff00)
NSTUB(eventproc_export_HdmiSimulateModeStart, 0xff85ff28)

NSTUB(eventproc_export_HdmiHpd5VOutput, 0xff85fff4)
NSTUB(eventproc_export_LockHdmiState, 0xff86012c)
NSTUB(eventproc_export_EdidDump, 0xff860174)
NSTUB(eventproc_export_HdmiRegDump, 0xff86023c)

NSTUB(eventproc_export_WriteToRom, 0xff8886c8)
NSTUB(eventproc_export_EraseSectorOfRom, 0xff888758)

NSTUB(eventproc_export_UnLoadScript, 0xff888920)

NSTUB(eventproc_export_LoadScript, 0xff888a1c)

NSTUB(eventproc_export_GetTimeOfSystem, 0xff8898cc)

NSTUB(eventproc_export_PutsCameraLogEvent, 0xff88c5fc)
NSTUB(eventproc_export_ShowCameraLogInfo, 0xff88c640)

NSTUB(eventproc_export_ShowCameraLog, 0xff88c6ac)
NSTUB(eventproc_export_StartCameraLog, 0xff88c6fc)

NSTUB(eventproc_export_StopCameraLog, 0xff88c8c0)

NSTUB(eventproc_export_OpLog_Stop, 0xff88cf5c)

NSTUB(eventproc_export_OpLog_WriteToROM, 0xff88cfb8)

NSTUB(eventproc_export_OpLog_ReadFromROM, 0xff88cfc8)
NSTUB(eventproc_export_OpLog_ReadFromSD, 0xff88d014)
NSTUB(eventproc_export_OpLog_WriteToSD, 0xff88d454)
NSTUB(eventproc_export_OpLog_Get, 0xff88d8a8)
NSTUB(eventproc_export_OpLog_Play, 0xff88d8c8)

NSTUB(eventproc_export_OpLog_Start, 0xff88d9f8)

NSTUB(eventproc_export_StartWDT, 0xff88e2b4)
NSTUB(eventproc_export_StopWDT, 0xff88e318)

NSTUB(eventproc_export_GetBuildDate, 0xff88e408)
NSTUB(eventproc_export_GetBuildTime, 0xff88e410)
NSTUB(eventproc_export_GetFirmwareVersion, 0xff88e418)

NSTUB(eventproc_export_CheckSumAll, 0xff88e524)
NSTUB(eventproc_export_RomCheckSum, 0xff88e714)

NSTUB(eventproc_export_CreateController, 0xff893154)
NSTUB(eventproc_export_DeleteController, 0xff893210)

NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff89339c)

NSTUB(eventproc_export_GetSelfControllerHandle, 0xff8934cc)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff893948)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff893994)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff893a0c)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff893a68)
NSTUB(eventproc_export, 0xff893a80)

NSTUB(eventproc_export_IsControlEventActive, 0xff895844)
NSTUB(eventproc_export_UiEvnt_SetLogicalEventActive, 0xff8958b4)
NSTUB(eventproc_export_SetScriptMode, 0xff895904)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff895938)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff895948)

NSTUB(eventproc_export_UnlockMainPower, 0xff895acc)
NSTUB(eventproc_export_LockMainPower, 0xff895b78)
NSTUB(eventproc_export_SetAutoShutdownTime, 0xff895bec)

NSTUB(eventproc_export_HardwareDefectWithRestart, 0xff895dcc)
NSTUB(eventproc_export_HardwareDefect, 0xff895e1c)

NSTUB(eventproc_export_PTM_AllResetToFactorySetting, 0xff89603c)
NSTUB(eventproc_export_PTM_AllReset, 0xff89604c)

NSTUB(eventproc_export_PTM_SetCurrentCaptureMode, 0xff8964d8)

NSTUB(eventproc_export_PTM_GetWorkingCaptureMode, 0xff8965a0)
NSTUB(eventproc_export_PTM_SetCurrentItem, 0xff8965a4)

NSTUB(eventproc_export_PTM_GetCurrentItem, 0xff8965b0)

NSTUB(eventproc_export_PTM_NextItem, 0xff89661c)
NSTUB(eventproc_export_PTM_PrevItem, 0xff896620)

NSTUB(eventproc_export_PTM_IsEnableItem, 0xff896630)
NSTUB(eventproc_export_PTM_SetProprietyEnable, 0xff896634)

NSTUB(eventproc_export_PTM_BackupUIProperty, 0xff89664c)
NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff896650)

NSTUB(eventproc_export_0, 0xff899538)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff89e550)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff89e58c)

NSTUB(eventproc_export_GUISrv_StartGUISystem, 0xff8ab980)

NSTUB(eventproc_export_atol, 0xff8ac1a0)

NSTUB(eventproc_export_GetLatestHVPosition, 0xff91aeac)

NSTUB(eventproc_export_SetSDPwrPort, 0xff96c73c)
NSTUB(eventproc_export_GetAdVBattBottom, 0xff96c768)
NSTUB(eventproc_export_GetAdChValue, 0xff96c76c)
NSTUB(eventproc_export_BeepDrive, 0xff96c770)
NSTUB(eventproc_export_BeepDriveComp, 0xff96c774)
NSTUB(eventproc_export_VbattGet, 0xff96c778)
NSTUB(eventproc_export_LEDDrive, 0xff96c77c)
NSTUB(eventproc_export_ShowPhySwStatus, 0xff96c780)
NSTUB(eventproc_export_SetRawSWCheckMode, 0xff96c790)
NSTUB(eventproc_export_OnPrintPhySw, 0xff96c7a0)
NSTUB(eventproc_export_OffPrintPhySw, 0xff96c7b0)
NSTUB(eventproc_export_GetSwitchStatus, 0xff96c7c0)
NSTUB(eventproc_export_ShowSDStatus, 0xff96c7c4)
NSTUB(eventproc_export_GetSDDetect, 0xff96c7d4)
NSTUB(eventproc_export_GetSDProtect, 0xff96c7d8)
NSTUB(eventproc_export_SetIgnoreAVJACK, 0xff96c7dc)
NSTUB(eventproc_export_GetDialEventId, 0xff96c7ec)
NSTUB(eventproc_export_GetBatteryCoverClose, 0xff96c7f0)
NSTUB(eventproc_export_IsHvSensorExist, 0xff96c7f4)

NSTUB(eventproc_export_GetDateAndTime, 0xff96ca8c)

NSTUB(eventproc_export_EraseSignature, 0xff96cb40)

NSTUB(eventproc_export_Dump32, 0xff96cb64)
NSTUB(eventproc_export_Poke32, 0xff96cb78)
NSTUB(eventproc_export_Poke16, 0xff96cb88)
NSTUB(eventproc_export_Poke8, 0xff96cb98)

NSTUB(eventproc_export_Wait, 0xff96cbb4)

NSTUB(eventproc_export_ShowAllTaskInfo, 0xff96cbc8)

NSTUB(eventproc_export_UIFS_IsAvailableMovieRecOptZoom, 0xff96d508)
NSTUB(eventproc_export_UIFS_IsAvailableMovieRecDigZoom, 0xff96d510)
NSTUB(eventproc_export_UIFS_IsAvailableServoAF, 0xff96d518)
NSTUB(eventproc_export_UIFS_IsAvailableRecMenuAFMode, 0xff96d520)
NSTUB(eventproc_export_UIFS_IsAutoPopupDownStrobe, 0xff96d528)
NSTUB(eventproc_export_UIFS_IsAvailableAvTvMode, 0xff96d530)

NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff96d630)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff96d650)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff96d690)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff96d6d0)
NSTUB(eventproc_export_UIFS_OpenPopupStrobe, 0xff96d6f0)
NSTUB(eventproc_export_UIFS_ClosePopupStrobe, 0xff96d720)
NSTUB(eventproc_export_UIFS_MountExtFlash, 0xff96d750)
NSTUB(eventproc_export_UIFS_UnmountExtFlash, 0xff96d780)
NSTUB(eventproc_export_UIFS_ConnectVideo, 0xff96d7b0)
NSTUB(eventproc_export_UIFS_DisconnectVideo, 0xff96d7e0)
NSTUB(eventproc_export_UIFS_MoveZoomTo, 0xff96d810)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff96d814)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff96d818)
NSTUB(eventproc_export_UIFS_PostModeDial, 0xff96d81c)

NSTUB(eventproc_export_UIFS_CaptureNoneStop, 0xff96d848)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff96d84c)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff96d850)
NSTUB(eventproc_export_UIFS_StartClockMode, 0xff96d854)
NSTUB(eventproc_export_UIFS_EndClockMode, 0xff96d864)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff96d874)
NSTUB(eventproc_export_UIFS_WriteFirmInfoToFile, 0xff96d878)
NSTUB(eventproc_export_UIFS_GetMovieRecoadableNumber, 0xff96d87c)
NSTUB(eventproc_export_UIFS_GetStillShotableNumber, 0xff96d8c4)
NSTUB(eventproc_export_UIFS_ChangeShootState, 0xff96d8f8)

NSTUB(eventproc_export_UIFS_ShootSeqToUI, 0xff96d91c)

NSTUB(eventproc_export_UIFS_GetLastPath, 0xff96d940)
NSTUB(eventproc_export_UIFS_GetAvItemCount, 0xff96d978)
NSTUB(eventproc_export_UIFS_GetTvItemCount, 0xff96d9d0)
NSTUB(eventproc_export_UIFS_GetAvItem, 0xff96da28)
NSTUB(eventproc_export_UIFS_GetTvItem, 0xff96da64)
NSTUB(eventproc_export_UIFS_GetCurrentAvString, 0xff96db54)
NSTUB(eventproc_export_UIFS_GetCurrentTvString, 0xff96dbd4)
NSTUB(eventproc_export_UIFS_IsAvailableShots, 0xff96dc54)
NSTUB(eventproc_export_UIFS_GetNumberOfDisplayedImage, 0xff96dc58)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff96e650)

NSTUB(eventproc_export_GetLogToFile, 0xff975780)
NSTUB(eventproc_export_EraseLogSector, 0xff9757a8)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xff988e54)

NSTUB(eventproc_export_ExecuteResetFactoryWithRomWrite, 0xff997924)

NSTUB(eventproc_export_UIFS_Capture, 0xff99dc88)

NSTUB(eventproc_export_memset, 0xffa15ddc)

NSTUB(eventproc_export_sscanf, 0xffa15f10)

NSTUB(eventproc_export_MemoryChecker, 0xffab8858)
NSTUB(eventproc_export_VerifyByte, 0xffab88e8)

NSTUB(eventproc_export_SDump, 0xffab8ac8)

NSTUB(eventproc_export_Peek32, 0xffab8d10)
NSTUB(eventproc_export_Peek16, 0xffab8d18)
NSTUB(eventproc_export_Peek8, 0xffab8d20)

NSTUB(eventproc_export_MonSelEvent, 0xffab8dd0)

