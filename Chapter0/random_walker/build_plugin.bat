@echo off

set CFLAGS=-Wall -std=c99 -v -shared -fPIC -fuse-ld=lld

set INCLUDE=-ID:\_Development\_Libraries\raylib\include -IC:\msys64\mingw64\include

set LIB=-L.\

set LINK=-lOpenGL32 -lGdi32 -lWinMM

@REM Online it looked harder than this to make a .dll but maybe things have gotten easier over time?
clang %CFLAGS% .\%1.c -o .\%2\%1.dll .\libraries\raylib.dll %INCLUDE% %LIB% %LINK%

@REM According to this page, if we stop using gcc, like switching over to Visual Studio for example, the .dll created by gcc can't be as easily linked to. Rather, we need to make an "import library" as well
@REM https://gernotklingler.com/blog/creating-using-shared-libraries-different-compilers-different-operating-systems/
