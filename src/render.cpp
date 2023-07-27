/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/07/27 12:25:27 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"

render::render(int aliasing, float openGL_min, float openGL_max, int width, int height, std::string name)
{
	std::cout << "creation" << std::endl;
	if (glfw_init() == -1)
		clear();
	set_hint(aliasing, openGL_min, openGL_max);
	if (create_window(width, height, name) == -1)
		clear();
	set_callback();
	set_context();
	if (glew_init() == -1)
		clear();
}

render::~render()
{
	std::cout << "destruction" << std::endl;
	glfwTerminate();
}

float	*render::make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces)
{
	float	*result = new float[faces.size() * 3]; //dont forget delete[]
	vec3	tmp(0, 0, 0);
	int		i;

	i = 0;
	while (i < faces.size())
	{
		// tmp = vertices[faces[i] - 1];
		/*std::cout << "tessst" << std::endl;
		std::cout << vertices[faces[i] - 1]._v[0];
		std::cout << "==============" << std::endl;*/
		result[3 * i] = tmp._v[0];
		result[3 * i + 1] = tmp._v[1];
		result[3 * i + 2] = tmp._v[2];

		/*std::cout << std::endl << "mega float res = " << std::endl;
		std::cout << result[3 * i] << ", ";
		std::cout << result[3 * i + 1] << ", ";
		std::cout << result[3 * i + 2] << std::endl;*/
		i++;
	}

		exit(0);
	return (result);
}

void	render::draw_triangle(std::vector<float> vertices, std::vector<unsigned int> faces)
{
	float					angle = 0;
	int		i;
	std::vector<float>	tmp;
	std::vector<float> 	vertex(4);
	float					*mega_float;

	GLfloat 			new_vertex[faces.size() * 3];

	//_original_vertex = vertex_buffer;
	//_current_vertex = static_cast<float *>(_original_vertex);
	create_vertex_array();
	//glGenBuffers(1, &_vertexBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(*vertex_buffer) * 27, vertex_buffer, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	GLuint		programID = LoadShaders("shader/vertex_shader.vert", "shader/frag_shader.frag"); //tmp


	static const GLfloat color_buffer[] =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.5f,
		0.0f, 0.2f, 0.3f,
		0.2f, 0.3f, 0.0f,
		0.8f, 0.6f, 0.4f,
		0.9f, 0.1f, 0.5f,
	};


	GLuint	colorbuffer;

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer
		(
		 1,
		 3,
		 GL_FLOAT,
		 GL_FALSE,
		 0,
		 (void*)0
		);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

	mega_float = make_mega_float(vertices, faces);


	while (!glfwWindowShouldClose(_window))
	{
		glClearColor(0, 255, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		i = 0;
		while (i < faces.size() * 3)
		{
			/*std::vector<float>	test(4, 0);
			test[0] = 0 + (angle / 100);
			test[1] = (0);
			test[2] = (0);
			test[3] = (0);

			std::vector<float>	factor(4, 0);
			factor[0] = 1;
			factor[1] = 1;
			factor[2] = 1 + (angle / 10);
			factor[3] = 1;*/



			vertex[0] = mega_float[3 * i];
			vertex[1] = mega_float[3 * i + 1];
			vertex[2] = mega_float[3 * i + 2];
			vertex[3] = 0;
			std::cout << std::endl << "rotate before = " << std::endl;
			std::cout << vertex[0] << ", ";
			std::cout << vertex[1] << ", ";
			std::cout << vertex[2] << std::endl;

			//tmp = matrice.rotate(vertex, angle, _rotate_axis);
			/*std::cout << std::endl << "rotate res = " << std::endl;
			std::cout << tmp[0] << ", ";
			std::cout << tmp[1] << ", ";
			std::cout << tmp[2] << ", ";
			std::cout << tmp[3] << std::endl;*/

			/*tmp = matrice.translate(tmp, test);
			  std::cout << "translate res = " << std::endl;
			  std::cout << tmp[0] << ", ";
			  std::cout << tmp[1] << ", ";
			  std::cout << tmp[2] << ", ";
			  std::cout << tmp[3] << std::endl;*/

			/*tmp = matrice.scale(tmp, factor);
			  std::cout << "scale res = " << std::endl;
			  std::cout << tmp[0] << ", ";
			  std::cout << tmp[1] << ", ";
			  std::cout << tmp[2] << ", ";
			  std::cout << tmp[3] << std::endl;*/

			/*new_vertex[3 * i] = tmp[0];
			new_vertex[3 * i + 1] = tmp[1];
			new_vertex[3 * i + 2] = tmp[2];*/


			new_vertex[3 * i] = vertex[0];
			new_vertex[3 * i + 1] = vertex[1];
			new_vertex[3 * i + 2] = vertex[2];

			std::cout << "final res = " << std::endl;
			std::cout << new_vertex[3 * i] << ", ";
			std::cout << new_vertex[3 * i + 1] << ", ";
			std::cout << new_vertex[3 * i + 2] << std::endl;
			i++;
		}
		if (angle == 360)
			angle = 0;
		else
			angle++;
		glBufferData(GL_ARRAY_BUFFER, sizeof(*new_vertex) * (faces.size() * 3), new_vertex, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glVertexAttribPointer
			(
			 0,
			 3,
			 GL_FLOAT,
			 GL_FALSE,
			 0,
			 (void*)0
			);


		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);
		glUseProgram(programID);
		glfwSwapBuffers(_window);
		glfwSetWindowUserPointer(_window, this);
		glfwPollEvents();
	}
}

void	render::create_vertex_array()
{
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);
}

int		render::glew_init()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew init failed :(" << std::endl;
		return (-1);
	}
	return (1);
}

void	render::set_context()
{
	glfwMakeContextCurrent(_window);
	glewExperimental = true;
}

void	render::set_callback()
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(_window, key_callback);
}

int		render::create_window(int width, int height, std::string name)
{
	_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!_window)
	{
		std::cout << "GLFW Init failed :(" << std::endl;
		return (-1);
	}
	return (1);
}

void	render::set_hint(int aliasing, float openGL_min, float openGL_max)
{
	glfwWindowHint(GLFW_SAMPLES, aliasing);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGL_min);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGL_max);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int		render::glfw_init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init failed :(" << std::endl;
		return (-1);
	}
	return (1);
}

void	render::clear() //comment on sait dans le main qu'il y a eu un clear et stop le prgm ?
{
	glfwTerminate();
}

void	render::error_callback(int error, const char *description)
{
	(void)error;
	std::cout << "Error : " << description << std::endl;
}

void	render::change_rotate_axis(int key)
{
	if (key == GLFW_KEY_RIGHT)
		_rotate_axis = 'x';
	else if (key == GLFW_KEY_UP)
		_rotate_axis = 'y';
	else if (key == GLFW_KEY_DOWN)
		_rotate_axis = 'z';
}

void	render::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	void *data = glfwGetWindowUserPointer(window);  
	render *w = static_cast<render *>(data);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else
		w->change_rotate_axis(key);

}
