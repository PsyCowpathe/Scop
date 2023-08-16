#pragma once

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#include "Shader.hpp"
#include "Vector2.hpp"

void	initText(const char *path);
void	printText(const char *text, int x, int y, int size);
void	cleanupText();
GLuint	loadDDS(const char * imagepath);