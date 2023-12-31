#ifndef SHADER_HPP
# define SHADER_HPP

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

GLuint load_shaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
