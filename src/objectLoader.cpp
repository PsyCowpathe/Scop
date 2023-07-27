#include "../headers/loadObject.hpp"
#include <iomanip>

// TODO: add error check
static void	getInfo(std::string line, std::vector<float> &buffer, int ignore)
{
	try
	{
		std::string xyz[3];
		size_t i = 0;
		size_t last = ignore; size_t next = 0;
		while ((next = line.find(' ', last)) != std::string::npos)
		{
			xyz[i] =  line.substr(last, next-last);
				buffer.push_back(std::stof(xyz[i]));
			// std::cout << xyz[i] << std::endl;
			last = next + 1;
			i++;
		}
		xyz[2] = line.substr(last);
		buffer.push_back(std::stof(xyz[2]));
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
}

static void	getUvInfo(std::string line, std::vector<float> &buffer)
{
	try
	{
		std::cout << "getting uv info" << std::endl;
		std::string xyz[2];
		size_t i = 0;
		size_t last = 3; size_t next = 0;
		while ((next = line.find(' ', last)) != std::string::npos)
		{
			xyz[i] =  line.substr(last, next-last);
			buffer.push_back(std::stof(xyz[i]));
			// std::cout << xyz[i] << std::endl;
			last = next + 1;
			i++;
		}
		xyz[1] = line.substr(last);
		buffer.push_back(std::stof(xyz[1]));
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
}

// stoi throws an exception when failing
// it's ugly as hell sorry
void	setArrays(std::string line, unsigned int &v, unsigned int &u, unsigned int &n)
{
	try
	{
		size_t	next = 0, last = 0;
		bool	first = true;
		while ((next = line.find('/', last)) != std::string::npos)
		{
			std::cout << "[" << line.substr(last, last - next) << "]" << std::endl;
			if (first)
			{
				v = std::stoi(line.substr(last, last - next));
				std::cout << "V" << v << std::endl;
			}
			else
			{
				u = std::stoi(line.substr(last, last - next));
				std::cout << "U" << u << std::endl;
			}
			last = next + 1;
			first = !first;
		}
		n = std::stoi(line.substr(last));
		std::cout << "FK[" << n << "]" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
	return ;
}

static void	parsingError(std::string line, size_t ln)
{
	std::cout << "wrong format at line " << ln << " : [" << line << "]" << std::endl;
	exit(0);
}

int	loadObject(const char *path, std::vector<float> &vertices, std::vector<float> &uv, std::vector<float> &normals, std::vector<unsigned int> &faces)
{
	std::vector<unsigned int> vertex_indices, uv_indices, normal_indices;
	std::ifstream	file(path);
	size_t	ln = 0;

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
		ln++;
		std::cout << line << std::endl;
		if (line[0] == 'v' && line[1] == ' ')
			getInfo(line, vertices, 2);
		else if (line[0] == 'v' && line[1] == 't')
		{
			std::cout << "LINE VT" << std::endl;
			if (line[2] == ' ')
				getUvInfo(line, uv);
			else
				parsingError(line, ln);
		}
		else if (line[0] == 'v' && line[1] == 'n')
		{
			if (line[2] == ' ')
				getInfo(line, normals, 3);
			else
				parsingError(line, ln);
		}
		else if (line[0] == 'f')
		{
			if (line[1] != ' ')
				parsingError(line, ln);
			unsigned int	vertex_index[3], uv_index[3], normal_index[3];
			int i = 0;
			size_t last = 2; size_t next = 0;
			while ((next = line.find(' ', last)) != std::string::npos)
			{
				std::string debug =  line.substr(last, next-last);
				setArrays(debug, vertex_index[i], uv_index[i], normal_index[i]);
				std::cout << "DEBUG" << debug << std::endl;
				last = next + 1;
				i++;
			}
			std::string	end = line.substr(last);
			std::cout << "END" << end << std::endl;
			setArrays(end, vertex_index[2], uv_index[2], normal_index[2]);
			vertex_indices.push_back(vertex_index[0]);
			vertex_indices.push_back(vertex_index[1]);
			vertex_indices.push_back(vertex_index[2]);
			uv_indices.push_back(uv_index[0]);
			uv_indices.push_back(uv_index[1]);
			uv_indices.push_back(uv_index[2]);
			normal_indices.push_back(normal_index[0]);
			normal_indices.push_back(normal_index[1]);
			normal_indices.push_back(normal_index[2]);
			faces.push_back(vertex_index[0]);
			faces.push_back(vertex_index[1]);
			faces.push_back(vertex_index[2]);
		}
		else if (line[0] != '#')
			parsingError(line, ln);
	}
	std::cout << vertices.size() << std::endl;
	std::cout << uv.size() << std::endl;
	std::cout << normals.size() << std::endl;
	std::cout << "end" << std::endl;
	return (0);
}
