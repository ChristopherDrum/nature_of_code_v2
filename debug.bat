@echo off

@REM Set up build folder
set BUILD_DIR=debug
mkdir %BUILD_DIR%

@REM Build the DLL, if you have one
@REM CMD /C .\debug_plugin.bat plug %BUILD_DIR%

pushd %BUILD_DIR%


@REM Copy over our shared files (resources, libraries, dlls)
@REM Windows needs .dll files to be at the .exe level
xcopy "..\resources" ".\resources" /e/h/c/i/y
@REM xcopy "..\libraries\*.dll" ".\" /e/h/c/i/y
@REM xcopy "..\libraries\*.pdb" ".\" /e/h/c/i/y


@REM compiler flags and library search paths
set CFLAGS=-Wall -Wextra -std=c99 -v -pedantic -g -gcodeview -fuse-ld=lld -Wl,--pdb=

set INCLUDE=-ID:\_Development\_Libraries\raylib\include -IC:\msys64\mingw64\include -IC:\msys64\usr\include -ID:\_Development\raylib\raylib\src

set LIB=-L.\ -LC:\msys64\mingw64\lib -LD:\_Development\_Libraries\raylib\lib -LD:\msys64\usr\lib

set LINK=-lOpenGL32 -lGdi32 -lWinMM -lraylib


@REM To get clang to work...
@REM Install msys2. Uninstall all other installations of LLVM, mingw, gcc, etc. as we had done through choco and other standalone installers. Clean up your mess first, then...
@REM pacman -S mingw-w64-x86_64-clang
@REM pacman -S mingw-w64-x86_64-clang-tools-extra
@REM pacman -S mingw-w64-x86_64-lld
@REM which gets us a clang that targets x86_64-w64-windows-gnu, rather than x86_64-pc-windows-msvc, with the linker we need for .pdb file generation (for RemedyBG)
@REM Then, this thread showed the flags necessary compile and link in one go: https://stackoverflow.com/questions/74416539/clang-14-does-not-generate-pdb-file
@REM see https://blog.llvm.org/2017/08/llvm-on-windows-now-supports-pdb-debug.html
@REM The above stackoverflow has a comment that answered the final question. lld isn't installed when mingw-clang is installed.
@REM ONLY install the mingw64 environment tools and libraries; keep it all the same. Don't be tempted by clang64-prefixed tools; that's a completely separate beast I don't understand
@REM And that gave us the current setup, which generates .pdb file for debugging and is working as expected in RemedyBG. Success!!

clang %CFLAGS% ..\%1.c -o %1.exe %INCLUDE% %LIB% %LINK%
D:\_Development\remedybg_latest\remedybg.exe -g -q %1.exe 
@REM .\%1_debug_session.rdbg