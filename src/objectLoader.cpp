#include "../headers/loadObject.hpp"

int	loadObject(const char *path, std::vector<vec3> &vertices, std::vector<vec3> &uv, std::vector<vec3> &normals)
{
	std::ifstream	file(path);
	if (!file.is_open())
	{
		std::cout << "couldn't read file at path: " << path << "are you sure the file exists?" << std::endl;
		return (-1);
	}
	std::string	line;
	std::string	header;
	std::getline(file, header);
	if (header[0] == '#')
		std::cout << "[" << header << "]" << std::endl;
	else
	{
		file.clear();
		file.seekg(0);
	}
	while (std::getline(file, line))
	{
		// if (line[0] != '#')
		// 	std::cout << line << std::endl;
		if (line[0] == 'v' && line[1] == ' ')
			std::cout << line << std::endl;
	}
	return (0);
}