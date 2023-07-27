#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int	loadObject(const char *path, std::vector<float> &vertices, std::vector<float> &uv, std::vector<float> &normals, std::vector<unsigned int> &faces);
