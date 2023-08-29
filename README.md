# Scop

A C++ program which can open & visualize 3D .obj files.

### Executing program

```
./scop <obj_path> [-f (fullscreen)]
```

### Controls
```
Arrow keys  : Change rotation axis
0 (!numpad) : Stop rotation
WASD        : Move the camera on X and Z axis
CTRL        : Accelerate movement speed
Space/Shift : Move the camera on Y axis
L    : Enable/Disable texture
M    : Enable/Disable wireframe mod
R    : Reset camera
H    : Randomize object position
F5   : Switch from small to large screen size
F3   : Minecraft style debug informations
Echap : Quit
```


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


# Additionnal help for install/use on Windows/wsl
<details><summary>
Click here</summary>
<p>

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

</p>
</details>
