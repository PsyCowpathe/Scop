# Project Title

Scop : a C++ program which can open & visualize 3D .obj files.

## Description

This version is a merge attempt between master and my still very basic, no matrices, thus no transfomations. No .obj support. version !
(No they don't really "work together" for now but at least conflicts are resolved)

## Getting Started

### Dependencies

* C++ (Linux : g++ pkg)
* OpenGL
* Glew :
```
sudo apt-get install libglew-dev
```
* GLFW (window & input events management) :
```
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```
* -lXi compile flag
```
sudo apt-get install libxi-dev
```

### Compiling
```
make
```


### Executing program

```
./scop
```

### Controls
```
Arrow key : Change rotation axis
0 (!numpad) : Stop rotation
WASD : Moov the camera on X and Z axis
Space/Shift : Moov the camera on Y axis
L : Enable/Disable texture
M : Enable/Disable wireframe mod
R : Reset camera
F5 : Switch from small to large screen size
F3 : Minecraft style debug informations
Echap : Quit
```

## Help for use on Windows/wsl
Works on Win10, WSL2, GeForce GTX 950.

### If program segfaults at exit and/or glxinfo -B segfaults or gives errors
* For Win11, you should update your WSL kernel to version : 1.3.15, by typing in powershell :
```
wsl --update --pre-release
```

* First, update your GPU drivers
* Follow this : https://gist.github.com/Mluckydwyer/8df7782b1a6a040e5d01305222149f3c
  Installing mesa, etc.
  ```
  apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
  ```
  and then setting up a window server if needed (win10)
* I also enabled systemd in WSL https://devblogs.microsoft.com/commandline/systemd-support-is-now-available-in-wsl/

If none of the above worked :
* Reboot wsl (wsl --shutdown in a windows terminal) and/or your PC.
* Try a good old :
```
sudo apt upgrade
```
* Try this less safe option if needed (warning : this is destructive, as it removes previous version of old packages from your system, and can take up to 1 hour to complete and may also include useless packages)
```
sudo apt full-upgrade
```

=> Any other advise for common problems or issues ?
