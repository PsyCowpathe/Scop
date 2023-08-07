#ifndef SHADER_HPP
# define SHADER_HPP

#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Shader
{
	public:

		Shader();
		~Shader();

	GLuint load_shaders(const char * vertex_file_path,const char * fragment_file_path);
};


#endif