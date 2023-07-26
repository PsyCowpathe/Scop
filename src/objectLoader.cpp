#include "../headers/loadObject.hpp"
#include <iomanip>

void	getInfo(std::string line, std::vector<vec3> &buffer, int ignore)
{
	std::string xyz[3];
	vec3		test(0, 0, 0);
	size_t i = 0;
	size_t last = ignore; size_t next = 0;
	while ((next = line.find(' ', last)) != std::string::npos)
	{
		xyz[i] =  line.substr(last, next-last);
		test._v[i] = std::stof(xyz[i]);
		std::cout << xyz[i] << std::endl;
		last = next + 1;
		i++;
	}
	xyz[2] = line.substr(last);
	test._v[2] = std::stof(xyz[2]);
	buffer.push_back(test);
}

void	getUvInfo(std::string line, std::vector<vec2> &buffer)
{
	std::cout << "getting uv info" << std::endl;
	std::string xyz[2];
	vec2		test(0, 0);
	size_t i = 0;
	size_t last = 3; size_t next = 0;
	while ((next = line.find(' ', last)) != std::string::npos)
	{
		std::cout << "i: " << i << std::endl;
		xyz[i] =  line.substr(last, next-last);
		std::cout << "xyz " << xyz[i] << std::endl;
		test._v[i] = std::stof(xyz[i]);
		std::cout << xyz[i] << std::endl;
		last = next + 1;
		i++;
	}
	xyz[1] = line.substr(last);
	test._v[1] = std::stof(xyz[1]);
	buffer.push_back(test);
}

int	loadObject(const char *path, std::vector<vec3> &vertices, std::vector<vec2> &uv, std::vector<vec3> &normals)
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
			getInfo(line, vertices, 2);
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
			getUvInfo(line, uv);
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			getInfo(line, normals, 3);
	}
	std::cout << vertices.size() << std::endl;
	std::cout << uv.size() << std::endl;
	std::cout << normals.size() << std::endl;
	std::cout << "end" << std::endl;
	return (0);
}