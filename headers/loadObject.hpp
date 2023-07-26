#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "pseudoVec3.hpp"
#include "pseudoVec2.hpp"

int	loadObject(const char *path, std::vector<vec3> &vertices, std::vector<vec2> &uv, std::vector<vec3> &normals, std::vector<unsigned int> &faces);
