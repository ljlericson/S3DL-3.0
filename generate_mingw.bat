@echo off

REM Set command
set CMAKE_CMD=cmake -G "MinGW Makefiles" -B buildGNU . -DVCPKG_TARGET_TRIPLET=x64-mingw-static

REM Run command
echo %CMAKE_CMD%
%CMAKE_CMD%

pause