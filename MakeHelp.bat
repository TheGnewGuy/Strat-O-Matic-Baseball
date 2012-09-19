@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by BASEBALL.HPJ. >"hlp\Baseball.hm"
echo. >>"hlp\Baseball.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Baseball.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Baseball.hm"
echo. >>"hlp\Baseball.hm"
echo // Prompts (IDP_*) >>"hlp\Baseball.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Baseball.hm"
echo. >>"hlp\Baseball.hm"
echo // Resources (IDR_*) >>"hlp\Baseball.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Baseball.hm"
echo. >>"hlp\Baseball.hm"
echo // Dialogs (IDD_*) >>"hlp\Baseball.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Baseball.hm"
echo. >>"hlp\Baseball.hm"
echo // Frame Controls (IDW_*) >>"hlp\Baseball.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Baseball.hm"
REM -- Make help for Project BASEBALL


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Baseball.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Baseball.hlp" goto :Error
if not exist "hlp\Baseball.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Baseball.hlp" Debug
if exist Debug\nul copy "hlp\Baseball.cnt" Debug
if exist Release\nul copy "hlp\Baseball.hlp" Release
if exist Release\nul copy "hlp\Baseball.cnt" Release
echo.
goto :done

:Error
echo hlp\Baseball.hpj(1) : error: Problem encountered creating help file

:done
echo.
