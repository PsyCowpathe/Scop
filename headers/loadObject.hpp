#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "pseudoVec3.hpp"

int	loadObject(const char *path, std::vector<vec3> &vertices, std::vector<vec3> &uv, std::vector<vec3> &normals);