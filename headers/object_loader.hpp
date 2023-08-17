#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

int	load_object(const char *path, std::vector<float> &vertices, std::vector<float> &uv, std::vector<float> &normals, std::vector<unsigned int> &faces, std::vector<unsigned int> &uv_indices);
