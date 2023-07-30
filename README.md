# Project Title

Scop : a C++ program which can open & visualize 3D .obj files.

## Description

This version is still very basic, no matrices, thus no transfomations.
No .obj support.

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

## Help for use on Windows/wsl
Works on Win10, WSL2, GeForce GTX 950.

### If program segfaults at exit
* First, update your GPU drivers, (or check for compatibility with the Linux distro https://docs.nvidia.com/cuda/wsl-user-guide/index.html#nvidia-compute-software-support-on-wsl-2)
* Maybe installing mesa helped ? (I also enabled systemd in WSL as suggested here : https://docs.nvidia.com/cuda/wsl-user-guide/index.html#nvidia-compute-software-support-on-wsl-2)
* Try a good old :
```
sudo apt upgrade
```
* Try this less safe option if needed (warning : this is destructive, as it removes previous version of old packages from your system, and can take up to 1 hour to complete and may also include useless packages)
```
sudo apt full-upgrade
```

=> Any other advise for common problems or issues ?
