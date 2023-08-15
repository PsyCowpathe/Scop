#include "object_loader.hpp"
#include <iomanip>

static void	parsing_error(std::string line, size_t ln)
{
	std::cout << "wrong format at line " << ln << " : [" << line << "]" << std::endl;
	exit(-1);
}

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

// TODO: add error check
static void	get_info(std::string line, std::vector<float> &buffer, int ignore, size_t ln)
{
	try
	{
		std::string xyz[3];
		size_t i = 0;
		size_t last = ignore; size_t next = 0;
		size_t space_count;

		space_count = count_char(line, ' ');

		if (space_count != 3)
			parsing_error(line, ln);
		while ((next = line.find(' ', last)) != std::string::npos)
		{
			if (i > 1)
				parsing_error(line, ln);
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
		std::cout << e.what() << " at line : " << ln << std::endl;
		exit(0);
	}
}

static void	get_uv_info(std::string line, std::vector<float> &buffer, size_t ln)
{
	try
	{
		std::string xyz[2];
		size_t i = 0;
		size_t last = 3; size_t next = 0;
		size_t space_count;

		space_count = count_char(line, ' ');

		if (space_count != 2)
			parsing_error(line, ln);
		while ((next = line.find(' ', last)) != std::string::npos)
		{
			if (i > 0)
				parsing_error(line, ln);
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
		std::cout << e.what() << " at line : " << ln << std::endl;
		exit(0);
	}
}

// stoi throws an exception when failing
// it's ugly as hell sorry
void	set_arrays(std::string line, unsigned int &v, unsigned int &u, unsigned int &n, size_t ln)
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
		std::cout << e.what() << " at line : " << ln << std::endl;
		exit(0);
	}
	return ;
}



// Parses faces info if there are only spaces



static void	handle_slash(std::string line, std::vector<unsigned int> &uv_indices, std::vector<unsigned int> &normal_indices, std::vector<unsigned int> &vert_indices, size_t ln)
{
	unsigned int	vertex_index[4], uv_index[4], normal_index[4];
	size_t			slash_count;
	size_t			space_count;
	size_t			index;
	size_t			prev_index;
	size_t			i;
	std::string		sub;

	slash_count = count_char(line, '/');
	space_count = count_char(line, ' ');
	index = 2;
	prev_index = index;
	i = 0;
	while ((index = line.find(" ", index)) != std::string::npos)
	{
		sub = line.substr(prev_index, index - prev_index);
		prev_index = ++index;
		set_arrays(sub, vertex_index[i], uv_index[i], normal_index[i], ln);
		i++;
	}
	if ((space_count == 3 && (i != 2 || slash_count != 6)) || (space_count == 4 && (i != 3 || slash_count != 8)))
		parsing_error(line, ln);
	sub = line.substr(prev_index, index - prev_index);
	set_arrays(sub, vertex_index[i], uv_index[i], normal_index[i], ln);
	if (slash_count == 8)
		i--;
	index = 0;
	while (index <= i)
	{
		uv_indices.push_back(uv_index[index]);
		normal_indices.push_back(normal_index[index]);
		vert_indices.push_back(vertex_index[index]);
		index++;
	}
	if (slash_count == 8)
	{
		vert_indices.push_back(vertex_index[0]);
		vert_indices.push_back(vertex_index[2]);
		vert_indices.push_back(vertex_index[3]);
		uv_indices.push_back(uv_index[0]);
		uv_indices.push_back(uv_index[2]);
		uv_indices.push_back(uv_index[3]);
	}
}


// Parses faces info if there are only spaces

static void	handle_spaces(std::string line, std::vector<unsigned int> &vert_indices, std::vector<unsigned int> &uv_indices, size_t ln)
{
	size_t 			last = 2;
	size_t 			next = 0;
	std::string		sub;
	unsigned int	vertex_index[4];
	unsigned int	uv_index[4] = {2, 4, 3, 1};
	int				i = 0;
	int				index = 0;
	size_t			space_count;

	try
	{
		space_count = count_char(line, ' ');
		if (space_count < 3 || space_count > 4 || count_char(line, '/') != 0)
			parsing_error(line, ln);
		while((next = line.find(' ', last)) != std::string::npos)
		{
			sub = line.substr(last, next-last);
			last = next + 1;
			vertex_index[i] = std::stoi(sub);
			i++;
		}
		sub = line.substr(last);
		vertex_index[i] = std::stoi(sub);
		if (space_count == 4)
			i--;
		while (index <= i)
		{
			vert_indices.push_back(vertex_index[index]);

			if (index == 0)
				uv_indices.push_back(uv_index[0]);
			else if (index == 1)
				uv_indices.push_back(uv_index[1]);
			//	uv_indices.push_back(uv_index[2]);
			else
				uv_indices.push_back(uv_index[2]);
			//	uv_indices.push_back(uv_index[3]);
			index++;
		}
		if (space_count == 4)
		{
			vert_indices.push_back(vertex_index[0]);
			vert_indices.push_back(vertex_index[2]);
			vert_indices.push_back(vertex_index[3]);
			uv_indices.push_back(uv_index[0]);
			uv_indices.push_back(uv_index[0]);
			uv_indices.push_back(uv_index[0]);
			//uv_indices.push_back(uv_index[2]);
			//uv_indices.push_back(uv_index[3]);
		}
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << " at line : " << ln << std::endl;
	}
}

// PARSING
// Parses the obj file and store infos to vectors
// Currently handles v, vt, vf, f
// TODO: refine support for texture (vt)

void	check_data(std::vector<float> vertices, std::vector<unsigned int> faces)
{
	float	max = 0;
	int		i = 0;
	int		index = 0;
	int		size = faces.size();
	(void) vertices;

	while (i < size)
	{
		if (faces[i] > max)
		{
			max = faces[i];
			index = i;
		}
		i++;
	}
	if (max > vertices.size() / 3)
	{
		std::cout << "wrong data in faces " << index / 3 << " : [" << faces[index] << "]" << std::endl;
		exit(-1);
	}
}

int	load_object(const char *path, std::vector<float> &vertices, std::vector<float> &uv, std::vector<float> &normals, std::vector<unsigned int> &faces, std::vector<unsigned int> &uv_indices)
{
	std::vector<unsigned int>	normal_indices;
	std::ifstream				file(path);
	std::string	line;
	std::vector<float> tmp = {0, 0, 0, 1, 1, 0, 1, 1};
	int			type = -1;

	size_t	ln = 0;

	if (!file.is_open())
	{
		std::cout << "couldn't read file at path: " << path << " are you sure the file exists?" << std::endl;
		exit(-1);
	}
	while (std::getline(file, line))
	{
		ln++;
		if (line[0] == 'v' && line[1] == ' ')
			get_info(line, vertices, 2, ln);
		else if (line[0] == 'v' && line[1] == 't')
		{
			if (line[2] == ' ')
				get_uv_info(line, uv, ln);
			else
				parsing_error(line, ln);
		}
		else if (line[0] == 'v' && line[1] == 'n')
		{
			if (line[2] == ' ')
				get_info(line, normals, 3, ln);
			else
				parsing_error(line, ln);
		}
		else if (line[0] == 'f')
		{
			if (line[1] != ' ')
				parsing_error(line, ln);
			if (line.find('/') != std::string::npos && (type == -1 || type == 1))
			{
				handle_slash(line, uv_indices, normal_indices, faces, ln);
				type = 1;
			}
			else if (line.find(' ', 3) != std::string::npos && (type == -1 || type == 2))
			{
				handle_spaces(line, faces, uv_indices, ln);
				uv = tmp;
				type = 2;
			}
		}
		else if (line[0] != '#' && line[0])
			parsing_error(line, ln);
	}
	check_data(vertices, faces);
	return (0);
}
