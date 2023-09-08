@echo off

@REM Eventually this should set a compilation flag I think
@REM For hot reloading to work, this BUILD_DIR cannot be named "release"
@REM Fought this bug for hours; ANY other folder name works :shrug:
@REM Don't forget to update build_plugin.bat to match!
set BUILD_DIR=release
mkdir %BUILD_DIR%

@REM Build the plug-in
@REM CMD /C .\build_plugin.bat plug %BUILD_DIR%

pushd %BUILD_DIR%


@REM Copy over our shared files (resources, libraries, other?)
@REM Windows needs .dll files to be at the .exe level
xcopy "..\resources" ".\resources" /e/h/c/i/y
@REM xcopy "..\libraries\*.dll" ".\" /e/h/c/i/y


@REM compiler flags and library search paths
@REM -fuse-ld=lld is super important!
@REM I think this gets the raylib.dll in place to override the Windows functions of the same names (PlaySound() in particular was my trouble)
set CFLAGS=-Wall -std=c99 -v -fuse-ld=lld

set INCLUDE=-ID:\_Development\_Libraries\raylib\include -IC:\msys64\clang64\include -IC:\msys64\usr\include  -ID:\_Development\raylib\raylib\src

set LIB=-L.\ -LC:\msys64\clang64\lib -LD:\_Development\_Libraries\raylib\lib

set LINK=-lOpenGL32 -lGdi32 -lWinMM -lraylib -lxml2 -lcurl

@REM Remember! gcc needs the source file declared BEFORE any l commands!
clang %CFLAGS% ..\%1.c -o %1.exe %INCLUDE% %LIB% %LINK%

.\%1.exe