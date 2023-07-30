#ifndef SHADER_HPP
# define SHADER_HPP


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <X11/X.h>
#include <X11/Xlib.h>

class Shader
{

	public:

		Shader();
		~Shader();

};

GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif