::@echo off

set RAYLIB_INCLUDE_DIR=C:\raylib\raylib\src
set RAYLIB_LIB_DIR=C:\raylib\raylib\src
set RAYLIB_RES_FILE=C:\raylib\raylib\src\raylib.rc.data
set COMPILER_DIR=C:\raylib\w64devkit\bin
set PATH=%PATH%;%COMPILER_DIR%
set FILENAME=%1
set FILENAME_FULL_PATH=%~f1
cd %~dp0

cmd /c if exist %FILENAME_FULL_PATH%.exe del /F %FILENAME_FULL_PATH%.exe

mingw32-make %FILENAME% -B PLATFORM=PLATFORM_DESKTOP RAYLIB_PATH=C:\raylib\raylib

set FILENAME_FULL_PATH=%~dp0\game
cmd /c if exist %FILENAME_FULL_PATH%.exe %FILENAME_FULL_PATH%.exe

cmd /c if exist %FILENAME_FULL_PATH%.exe del /F %FILENAME_FULL_PATH%.exe