# Nature of Code, in C
A new version of [Nature of Code (original site)](https://natureofcode.com/) has been released on github.<br>
https://github.com/nature-of-code/noc-book-2023

This repo collates my C implementations of the book's exercises and lessons.<br>
Minimal dependencies with no OOP, containers, complex build systems, or other convoluted nonsense.

# Libraries
- [Raylib](https://github.com/raysan5/raylib) for graphics/sound
- [Chipmunk](https://github.com/slembcke/Chipmunk2D) for physics (TBD)

# Building
Builds are generated via dead-simple .bat files.

- `.\build.bat <whatever>.c` to get an executable from that .c file.
- `.\debug.bat <whatever>.c` to generate .pdb files and launch into RemedyBG.

# Current Tools
- VSCode for editing
- [RemedyBG](https://remedybg.itch.io/remedybg) for debugging
- clang for compiling (installed via MSYS2) 
- mingw for C headers (installed via MSYS2)
- Windows 10 
