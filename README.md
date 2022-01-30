# Why "Angles"?  
Well, I incorrectly translated word "Уголки" to English. I believe correct 
name of this game is "Corners".

# Prerequisites
 * GCC with C++20 support
 * Cmake >=3.12
 * GLFW 3.x
 * GLEW

# Building
Building on Linux only (I am sorry). But you can download built binaries for 
Windows and Linux in "[releases](https://github.com/edomin/angles/releases)" 
section of this repo.

Manually for Linux:
```
$ mkdir cmake_build
$ cd cmake_build
$ cmake ..
$ make
$ cd ..
```

With shortcut for Linux:
```
$ make build_release
```

With shortcut for Windows:
```
$ make build_release toolchain=x86_64-w64-mingw32
```

# Controls
Left mouse button - choose boy  
Right mouse button - move boy  
Esc - Quit game  

# Copying
Source code under CC0 
Sprites of selected cells and game endings' text (files "gimp/frames.xcf" and 
"gimp/text.xcf") are under CC0

Third-party graphics used in this game: 

* [Stone floor](https://opengameart.org/content/stone-floor-tiles) (CC0) 
* [RPG Characters](https://opengameart.org/content/rpg-character-sprites) (CC0)