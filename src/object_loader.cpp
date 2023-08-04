#include "../headers/object_loader.hpp"
#include <iomanip>

// TODO: add error check
static void	get_info(std::string line, std::vector<float> &buffer, int ignore)
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

static void	get_uv_info(std::string line, std::vector<float> &buffer)
{
	try
	{
		std::string xyz[2];
		size_t i = 0;
		size_t last = 3; size_t next = 0;
		while ((next = line.find(' ', last)) != std::string::npos)
		{
			xyz[i] =  line.substr(last, next-last);
			buffer.push_back(std::stof(xyz[i]));
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
void	set_arrays(std::string line, unsigned int &v, unsigned int &u, unsigned int &n)
{
	try
	{
		size_t	next = 0, last = 0;
		bool	first = true;
		while ((next = line.find('/', last)) != std::string::npos)
		{
			if (first)
				v = std::stoi(line.substr(last, last - next));
			else
				u = std::stoi(line.substr(last, last - next));
			last = next + 1;
			first = !first;
		}
		n = std::stoi(line.substr(last));
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
	return ;
}

static void	parsing_error(std::string line, size_t ln)
{
	std::cout << "wrong format at line " << ln << " : [" << line << "]" << std::endl;
	exit(-1);
}

// Parses faces info if there are only spaces

size_t			count_char(std::string line, char to_count)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	while ((index = line.find(to_count, index)) != std::string::npos)
	{
		count++;
		index++;
	}
	return (count);
}


static void	handle_slash(std::string line, std::vector<unsigned int> &uv_indices, std::vector<unsigned int> &normal_indices, std::vector<unsigned int> &faces)
{
	unsigned int	vertex_index[6], uv_index[6], normal_index[6];
	size_t			slash_count;
	size_t			index;
	size_t			prev_index;
	size_t			i;
	std::string		sub;

	slash_count = count_char(line, '/');
	index = 2;
	prev_index = index;
	i = 0;
	if (slash_count == 6) // triangle
	{
		while ((index = line.find(" ", index)) != std::string::npos)
		{
			sub = line.substr(prev_index, index - prev_index);
			prev_index = ++index;
			set_arrays(sub, vertex_index[i], uv_index[i], normal_index[i]);
			i++;
			std::cout << "sub = " << sub << std::endl;
		}
		sub = line.substr(prev_index, index - prev_index);
		//std::cout << "sub = " << sub << std::endl;
		set_arrays(sub, vertex_index[i], uv_index[i], normal_index[i]);
		//std::cout << "vert = " << vertex_index[0] << " " << vertex_index[1] << " " << vertex_index[2] << std::endl;
		//std::cout << "uv = " << uv_index[0] << " " << uv_index[1] << " " << uv_index[2] << std::endl;
		//std::cout << "normal = " << normal_index[0] << " " << normal_index[1] << " " << normal_index[2] << std::endl;
	}
	else if (slash_count == 8) // cube
	{
		while ((index = line.find(" ", index)) != std::string::npos)
		{
			sub = line.substr(prev_index, index - prev_index);
			prev_index = ++index;
			set_arrays(sub, vertex_index[i], uv_index[i], normal_index[i]);
			i++;
			std::cout << "sub = " << sub << std::endl;
		}
		sub = line.substr(prev_index, index - prev_index);
		set_arrays(sub, vertex_index[i], uv_index[i], normal_index[i]);
		std::cout << "sub = " << sub << std::endl;
		std::cout << "vert = " << vertex_index[0] << " " << vertex_index[1] << " " << vertex_index[2] << " " << vertex_index[3] << std::endl;
		std::cout << "uv = " << uv_index[0] << " " << uv_index[1] << " " << uv_index[2] << " " << uv_index[3] << std::endl;
		std::cout << "normal = " << normal_index[0] << " " << normal_index[1] << " " << normal_index[2] << " " << normal_index[3] << std::endl;
		
		i--;
	}
	else
	{
		//parsing error
	}
	index = 0;
	while (index <= i)
	{
		uv_indices.push_back(uv_index[index]);
		normal_indices.push_back(normal_index[index]);
		faces.push_back(vertex_index[index]);
		index++;
	}
	faces.push_back(vertex_index[0]);
	faces.push_back(vertex_index[2]);
	faces.push_back(vertex_index[3]);
}


// Parses faces info if there are only spaces

static void	handle_spaces(std::string line, std::vector<unsigned int> vertex_indices)
{
	size_t last = 2; size_t next = 0;
	try
	{
		while((next = line.find(' ', last)) != std::string::npos)
		{
			std::string	debug = line.substr(last, next-last);
			last = next + 1;
			vertex_indices.push_back(std::stoi(debug));
		}
		std::string	debug = line.substr(last);
		vertex_indices.push_back(std::stoi(debug));
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

// PARSING
// Parses the obj file and store infos to vectors
// Currently handles v, vt, vf, f
// TODO: add support for texture, s(?) and mat(?)

int	load_object(const char *path, std::vector<float> &vertices, std::vector<float> &uv, std::vector<float> &normals, std::vector<unsigned int> &faces)
{
	std::vector<unsigned int> vertex_indices, uv_indices, normal_indices;
	std::ifstream	file(path);
	size_t	ln = 0;

	if (!file.is_open())
	{
		std::cout << "couldn't read file at path: " << path << "are you sure the file exists?" << std::endl;
		exit(-1);
	}
	std::string	line;
	while (std::getline(file, line))
	{
		ln++;
		if (line[0] == 'v' && line[1] == ' ')
			get_info(line, vertices, 2);
		else if (line[0] == 'v' && line[1] == 't')
		{
			if (line[2] == ' ')
				get_uv_info(line, uv);
			else
				parsing_error(line, ln);
		}
		else if (line[0] == 'v' && line[1] == 'n')
		{
			if (line[2] == ' ')
				get_info(line, normals, 3);
			else
				parsing_error(line, ln);
		}
		else if (line[0] == 'f')
		{
			if (line[1] != ' ')
				parsing_error(line, ln);
			if (line.find('/') != std::string::npos)
				handle_slash(line, uv_indices, normal_indices, faces);
			else if (line.find(' ', 3) != std::string::npos)
				handle_spaces(line, vertex_indices);
		}
		else if (line[0] != '#' && line[0])
			parsing_error(line, ln);
	}
	return (0);
}
