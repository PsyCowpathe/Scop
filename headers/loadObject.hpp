#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "pseudoVec3.hpp"
#include "pseudoVec2.hpp"

int	loadObject(const char *path, std::vector<float> &vertices, std::vector<float> &uv, std::vector<float> &normals, std::vector<unsigned int> &faces);
