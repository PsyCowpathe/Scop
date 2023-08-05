#ifndef IMG_LOADER_HPP
# define IMG_LOADER_HPP

#pragma once
#include "fstream"
#include <stdint.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int load_bmp(const char* location, GLuint &texture);

#endif