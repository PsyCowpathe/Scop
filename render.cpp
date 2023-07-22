/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/07/22 18:57:17 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.hpp"

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

std::vector<float>	render::rotate_on_x(float x, float y, float z, int angle)
{
	float				new_angle;
	std::vector<float>	result;
	int					i;

	new_angle = angle * (M_PI / 180);
	std::cout << "cos = " << cosf(new_angle) << std::endl;
	std::cout << "sin = " << sinf(new_angle) << std::endl;
	float matrice[9] = {1, 0, 0, 0, cosf(new_angle), (sinf(new_angle) * -1), 0,
							sinf(new_angle), cosf(new_angle)};
	float vector[3] = {x, y, z};
	i = 0;
	while (i < 3)
	{
		result.push_back(matrice[3 * i] * vector[0] + matrice[3 * i + 1] * vector[1] + matrice[3 * i + 2] * vector[2]);
		std::cout << result.back() << std::endl;
		i++;
	}
	return (result);
}

void	render::draw_triangle(const GLfloat vertex_buffer[])
{
	int		angle = 0;
	std::vector<float> tmp;
	GLfloat new_vertex[9];
	create_vertex_array();
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*vertex_buffer) * 9, vertex_buffer, GL_STATIC_DRAW);

	GLuint		programID = LoadShaders("shader/vertex_shader.vert", "shader/frag_shader.frag"); //tmp

	int		i;

	while (!glfwWindowShouldClose(_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		i = 0;
		while (i < 3)
		{
			tmp = rotate_on_x(vertex_buffer[3 * i], vertex_buffer[3 * i + 1], vertex_buffer[3 * i + 2], angle);
			new_vertex[3 * i] = tmp[0];
			new_vertex[3 * i + 1] = tmp[1];
			new_vertex[3 * i + 2] = tmp[2];
			i++;
		}
		if (angle == 360)
			angle = 0;
		else
			angle++;
		glBufferData(GL_ARRAY_BUFFER, sizeof(*new_vertex) * 9, new_vertex, GL_STATIC_DRAW);


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
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		glUseProgram(programID);
		glfwSwapBuffers(_window);
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

void	render::clear() //comment on sait dans le main qu'il y a eu un clear ??
{
	glfwTerminate();
}

void	render::error_callback(int error, const char *description)
{
	(void)error;
	std::cout << "Error : " << description << std::endl;
}

void	render::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
