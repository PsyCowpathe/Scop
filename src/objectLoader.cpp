#include "../headers/loadObject.hpp"

void	getInfo(std::string line)
{
	size_t last = 1; size_t next = 0;
	while ((next = line.find(' ', last)) != std::string::npos)
	{

		std::cout << line.substr(last, next-last) << std::endl;
		last = next + 1;
	}
	std::cout << line.substr(last) << std::endl;
	return ;
}

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
		{
			getInfo(line);
			// std::cout << getInfo(line) << std::endl;
			// std::cout << line << std::endl;
		}
	}
	std::cout << "end" << std::endl;
	return (0);
}