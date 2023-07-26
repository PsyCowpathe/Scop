/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/07/26 13:13:23 by ckurt            ###   ########lyon.fr   */
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

float	*render::create_rotate_matrice(char rotate, float angle)
{
	float	tmp_x[9] = {1, 0, 0, 0, cosf(angle), (sinf(angle) * -1), 0, sinf(angle), cosf(angle)};
	float	tmp_y[9] = {cosf(angle), 0, sinf(angle), 0, 1, 0, sinf(angle) * -1, 0, cosf(angle)};
	float	tmp_z[9] = {cosf(angle), sinf(angle) * -1, 0, sinf(angle), cosf(angle), 0, 0, 0, 1};
	float	*matrice;
	int		i;

	i = 0;
	matrice = new float[9];
	while (i < 9)
	{
		if (rotate == 'x')
			matrice[i] = tmp_x[i];
		else if (rotate == 'y')
			matrice[i] = tmp_y[i];
		else if (rotate == 'z')
			matrice[i] = tmp_z[i];
		i++;
	}
	return (matrice);
}

std::vector<float>	render::rotate(std::vector<float> vertex, float angle, char rotate)
{
	std::vector<float>	result;
	int					i;
	float				*matrice;

	i = 0;
	matrice = create_rotate_matrice(rotate, angle *= (M_PI / 180));
	while (i < 3)
	{
		result.push_back(matrice[3 * i] * vertex[0] + matrice[3 * i + 1] * vertex[1] + matrice[3 * i + 2] * vertex[2]);
		i++;
	}
	delete[] matrice;
	return (result);
}

class	m4 {
	public:
		float	_m[16];
		m4 (float angle) {
			_m[0] = cosf(angle);
			_m[1] = -sinf(angle);
			_m[2] = 0.0f;
			_m[3] = 0.0f;
			_m[4] = sinf(angle);
			_m[5] = cosf(angle);
			_m[6] = 0.0f;
			_m[7] = 0.0f;
			_m[8] = 0.0f;
			_m[9] = 0.0f;
			_m[10] = 1.0f;
			_m[11] = 0.0f;
			_m[12] = 0.0f;
			_m[13] = 0.0f;
			_m[14] = 0.0f;
			_m[15] = 1.0f;
		}
};

GLuint	g_rotation_location;
void	render::draw_triangle(const GLfloat vertex_buffer[])
{
	float				angle = 0;
	int					i;
	int					frames = 0;
	float				last_time = glfwGetTime();
	std::vector<float>	tmp;
	std::vector<float> 	vertex(3);
	GLfloat 			new_vertex[9];

	create_vertex_array();
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*vertex_buffer) * 9, vertex_buffer, GL_STATIC_DRAW);

	GLuint		programID = LoadShaders("shader/vertex_shader.vert", "shader/frag_shader.frag"); //tmp


	while (!glfwWindowShouldClose(_window))
	{
		float	current_time = glfwGetTime();
		frames++;
		if (current_time - last_time >= 1.0)
		{
			std::cout << "fps: " << frames << " frame time: " << 1000.0/float(frames) << std::endl;
			frames = 0;
			last_time = glfwGetTime();
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m4	matrix4(angle);
		if (angle == 360)
			angle = 0;
		else
			angle += 0.01f;
		// glBufferData(GL_ARRAY_BUFFER, sizeof(*new_vertex) * 9, new_vertex, GL_STATIC_DRAW);
		glUniformMatrix4fv(g_rotation_location, 1, GL_TRUE, &matrix4._m[0]);

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
